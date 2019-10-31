#include "../includes/space_state.h"


void inputVector(double k)
{

    // Get input matrix
    Matrix inputV_now;
    inputV_get(&inputV_now);
    matrix_zero(2,1,&inputV_now);

    // Definition (T from Transpose):
    // 0, k < 0
    // [ 1 0.2pi ] T, 0 <= k < 10
    // [ 1 -0.2pi ] T, k >= 10
 
    // Calculate from definition
    if ( k >= 0 && k < 10 )
    {
        inputV_now.values[0][0] = 1;
        inputV_now.values[1][0] = 0.2 * PI;
    } else if ( k >= 10 )
    {
        inputV_now.values[0][0] = 1;
        inputV_now.values[1][0] = -0.2 * PI;
    }

    // Set input matrix
    inputV_set(inputV_now);

}

void stateVector(double k, Matrix * inputVector_k, Matrix * stateMatrix)
{  
    matrix_zero(3,1,stateMatrix);

    double v = inputVector_k->values[0][0];
    double w = inputVector_k->values[1][0];

    stateMatrix->values[0][0] =  - v * cos ( w * k ) / w;
    stateMatrix->values[1][0] =  + v * sin ( w * k ) / w;
    stateMatrix->values[2][0] =  w * k; 

    // Get current output vector
    Matrix outputV_now; 
    outputV_now.rows = 3;
    outputV_now.columns = 1;
    outputV_get(&outputV_now);

    stateMatrix->values[0][0] =  outputV_now.values[0][0] + sin ( w * k );
    stateMatrix->values[1][0] =  outputV_now.values[1][0] + cos ( w * k );
    stateMatrix->values[2][0] =  outputV_now.values[2][0] + w * k;

      // State vector.
/*     Matrix aux;
    matrix_zero(3,2,&aux);

    // Get current output vector
    Matrix outputV_now; 
    outputV_now.rows = 3;
    outputV_now.columns = 1;
    outputV_get(&outputV_now);

    // Already know wk is the \angle
    double angle = outputV_now.values[2][0];

    // State auxiliar vector: constant
    aux.values[0][0] = sin(angle);
    aux.values[0][1] = 0;
    aux.values[1][0] = cos(angle);
    aux.values[1][1] = 0;
    aux.values[2][0] = 0;
    aux.values[2][1] = k;

    matrix_multiplication(&aux,inputVector_k,stateMatrix); */
    //matrix_addition()
}

void outputfVector(double k)
{

    // Get current input vector
    Matrix inputV_now; 
    inputV_now.rows = 2;
    inputV_now.columns = 1;
    inputV_get(&inputV_now);

    // Calculate state matrix
    Matrix stateVector_k;
    stateVector_k.rows = 3;
    stateVector_k.columns = 1;
    stateVector(k,&inputV_now,&stateVector_k);

    // Initialize
    // Vector: [ radius 0 0; 0 radius 0; 0 0 0 ]
    double angle = stateVector_k.values[2][1];
    Matrix outputfV;    
    outputfV.rows = 3;
    outputfV.columns = 3;
    matrix_zero(3,3,&outputfV);
    outputfV.values[0][0] = _ROBOT_RADIUS * cos(angle);
    outputfV.values[1][1] = _ROBOT_RADIUS * sin(angle);
    outputfV.values[2][2] = 0;
    
    // Final output matrix
    // Perform operation: x + yv * x
    Matrix outputMatrix;
    outputMatrix.rows = 3;
    outputMatrix.columns = 1;
    matrix_zero(3,1,&outputMatrix);
    matrix_multiplication(&outputfV,&stateVector_k,&outputMatrix);
    matrix_addition(&stateVector_k,&outputMatrix,&outputMatrix);

    outputV_set(outputMatrix);
    
    //matrix_print(*outputMatrix);
}