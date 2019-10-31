// User headers

#include "../includes/matrix.h"

void matrix_print(Matrix matrix)
{
    printf("\t%s (%dx%d)\n\n",matrix.name, matrix.rows, matrix.columns);

    // INIT values to 0
    for (uint8_t i = 0; i < matrix.rows; i++)
    {
        printf("\t|");
        for (uint8_t j = 0; j < matrix.columns; j++)
        {
            printf("\t%.2f\t", matrix.values[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

Matrix matrix_zeros(char * name, uint8_t rows, uint8_t columns)
{
    return matrix_create(name,rows,columns,0);
}

void matrix_zero(uint8_t rows, uint8_t columns, Matrix * matrix)
{
    matrix->rows = rows;
    matrix->columns = columns;
    for ( uint8_t i = 0; i < rows; i++ )
    {
        for ( uint8_t j = 0; j < columns; j++ )
        {
            (*matrix).values[i][j] = 0;
        }
    }
    return;
}

Matrix matrix_ones(char * name, uint8_t rows, uint8_t columns)
{
    return matrix_create(name,rows,columns,1);
}

Matrix matrix_create(char * name, uint8_t rows, uint8_t columns, double initValue)
{

    // Verify bounds
    if ( !matrix_validateBounds(rows,columns) )
    {
        fprintf(stderr,"Row or column out of bound!");
        exit(EXIT_FAILURE);
    }

    // INIT matrix
    Matrix matrix;
    strncpy(matrix.name,name,NAME_MAX_SIZE);
    matrix.rows = rows; // rows
    matrix.columns = columns; // columns

    // INIT values to 0
    for (uint8_t i = 0; i < rows; i++)
    {
        for (uint8_t j = 0; j < columns; j++)
        {
            matrix.values[i][j] = initValue;
        }
    }

    return matrix;
}

uint8_t matrix_validateBounds(uint8_t rows, uint8_t columns)
{
    return rows <= ROWS_MAX && columns <= COLUMNS_MAX
            && rows > 0 && columns > 0;
}

void matrix_addition(Matrix * matrix1, Matrix * matrix2, Matrix * matrixResult)
{

    // Verify if the matrixs has the same rows and columns
    if ( matrix1->rows != matrix2->rows || matrix1->columns != matrix2->columns )
    {
        fprintf(stderr,"Matrices doesn't have the same number of rows and columns!");
        exit(EXIT_FAILURE);
    }

    // INIT matrix
    matrixResult->rows = matrix1->rows;
    matrixResult->columns = matrix1->columns;
    matrix_zero(matrix1->rows,matrix1->columns,matrixResult);

    // Sum matrix 1 and 2 in newMatrix
    for (uint8_t i = 0; i < matrix1->rows; i++)
    {
        for (uint8_t j = 0; j < matrix1->columns; j++)
        {
            matrixResult->values[i][j] =
                matrix1->values[i][j] + matrix2->values[i][j];
        }
    }


}

Matrix matrix_subtraction(char * name, Matrix matrix1, Matrix matrix2)
{

    // Verify if the matrixs has the same rows and columns
    if ( matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns )
    {
        fprintf(stderr,
            "Matrices doesn't have the same number of rows and columns!");
        exit(EXIT_FAILURE);
    }

    // INIT matrix
    Matrix newMatrix = matrix_zeros(name,matrix1.rows,matrix1.columns);

    // Sum matrix 1 and 2 in newMatrix
    for (uint8_t i = 0; i < matrix1.rows; i++)
    {
        for (uint8_t j = 0; j < matrix1.columns; j++)
        {
            newMatrix.values[i][j] =
                matrix1.values[i][j] - matrix2.values[i][j];
        }
    }

    return newMatrix;
}

void matrix_multiplication(Matrix * matrix1, Matrix * matrix2, Matrix * matrixResult)
{

    //matrix_print(*matrix1);
    //matrix_print(*matrix2);

    // Verify if the matrixs has the same rows and columns
    if ( (*matrix1).columns != (*matrix2).rows )
    {
        fprintf(stderr,
            "Number of Matrix 1 columns isn't equal to Matrix 2 number of rows!");
        exit(EXIT_FAILURE);
    }

    // Rows of matrix1
    for (uint8_t i = 0; i < (*matrix1).rows; i++)
    {
        // Columns of matrix2
        for (uint8_t j = 0; j < (*matrix2).columns; j++)
        {
            // Columns of matrix1 in parallel with rows of matrix2
            for ( uint8_t k = 0; k < (*matrix1).columns; k++ )
            {
                (*matrixResult).values[i][j] +=
                    (*matrix1).values[i][k] * (*matrix2).values[k][j];
            }
        }
    }
}

Matrix matrix_constantAddition(Matrix matrix, double value)
{

    // Sum matrix 1 and 2 in newMatrix
    for (uint8_t i = 0; i < matrix.rows; i++)
    {
        for (uint8_t j = 0; j < matrix.columns; j++)
        {
            matrix.values[i][j] += value;
        }
    }

    return matrix;
}

Matrix matrix_constantSubtraction(Matrix matrix, double value)
{

    // Sum matrix 1 and 2 in newMatrix
    for (uint8_t i = 0; i < matrix.rows; i++)
    {
        for (uint8_t j = 0; j < matrix.columns; j++)
        {
            matrix.values[i][j] -= value;
        }
    }

    return matrix;
}

void matrix_constantMultiplication(Matrix * matrix, double value)
{

    // Sum matrix 1 and 2 in newMatrix
    for (uint8_t i = 0; i < (*matrix).rows; i++)
    {
        for (uint8_t j = 0; j < (*matrix).columns; j++)
        {
            (*matrix).values[i][j] *= value;
        }
    }
}

Matrix matrix_transpose(char * name, Matrix matrix)
{

    // New matrix
    Matrix newMatrix = matrix_zeros(name,matrix.columns,matrix.rows);

    for ( uint8_t i = 0; i < matrix.columns; i++ )
    {
        for ( uint8_t j = 0; j < matrix.rows; j++ )
        {
            newMatrix.values[i][j] = matrix.values[j][i];
        }
    }

    return newMatrix;

}

Matrix matrix_cofactor(char * name, Matrix matrix)
{
    // Verify is a square matrix 
    if ( !matrix_isSquare(matrix) )
    {
        fprintf(stderr,"Matrix isn't a square matrix!");
        exit(EXIT_FAILURE);
    // Verify if parameters are valid
    }

    // current row and column from new matrix
    Matrix newMatrix = matrix_zeros(name,matrix.rows,matrix.rows);

    for ( uint8_t row = 0; row < matrix.rows; row++ )
    {
        for ( uint8_t column = 0; column < matrix.rows; column++ )
        {
            Matrix tempMatrix = matrix_zeros(name,matrix.rows-1,matrix.rows-1);
            uint8_t i = 0, j = 0;
            // Looping for each element of the matrix
            for ( uint8_t m = 0; m < matrix.rows; m++ )
            {
                // Skip if is element row
                if ( m == row )
                {
                    continue;
                }
                for ( uint8_t n = 0; n < matrix.columns; n++ )
                {
                    // Skip if is element column
                    if ( n == column )
                    {
                        continue;
                    }

                    // Add value to new matrix
                    tempMatrix.values[i][j++] = matrix.values[m][n];

                    // Verify bounds
                    if ( j == matrix.columns - 1 )
                    {
                        j = 0;
                        i++;
                    }
                }

            }

            double det = matrix_determinant(tempMatrix);
            newMatrix.values[row][column] = pow(-1.0,row+column) * det;
        }
    }

    return newMatrix;
}

Matrix matrix_adjoint(char * name, Matrix matrix)
{
    return matrix_transpose(name,matrix_cofactor(name,matrix));
}

uint8_t matrix_isSquare(Matrix matrix)
{
    return matrix.rows == matrix.columns;
}

double matrix_determinant(Matrix matrix)
{
    // Verify is a square matrix 
    if ( !matrix_isSquare(matrix) )
    {
        fprintf(stderr,"Matrix isn't a square matrix!");
        exit(EXIT_FAILURE);
    // Verify if parameters are valid
    }

    uint8_t index; // Initialize result 
    double det = 1, num1,num2,total = 1;  
        
    // temporary array for storing row   
    double temp[matrix.rows + 1];   
        
    //loop for traversing the diagonal elements  
    for(uint8_t i = 0; i < matrix.rows; i++)    
    {  
        index = i; // initialize the index   
            
        //finding the index which has non zero value   
        while(matrix.values[index][i] == 0 && index < matrix.rows) {   
            index++;    
        }   
        if(index == matrix.rows) // if there is non zero element   
        {   
            // the determinat of matrix as zero   
            continue;   
                
        }   
        if(index != i)   
        {   
            //loop for swaping the diagonal element row and index row   
            for(uint8_t j = 0; j < matrix.rows; j++)   
            {   
                double temp = matrix.values[index][j];
                matrix.values[index][j] = matrix.values[i][j];
                matrix.values[i][j] = temp;      
            }   
            //determinant sign changes when we shift rows   
            //go through determinant properties   
            det = det*pow(-1,index-i);        
       }   
           
       //storing the values of diagonal row elements   
       for(uint8_t j = 0; j < matrix.rows; j++)   
       {   
           temp[j] = matrix.values[i][j];   
               
       }   
       //traversing every row below the diagonal element   
       for(uint8_t j = i+1; j < matrix.rows; j++)   
       {   
           num1 = temp[i]; //value of diagonal element   
           num2 = matrix.values[j][i]; //value of next row element   
               
           //traversing every column of row   
           // and multiplying to every row   
           for(uint8_t k = 0; k < matrix.rows; k++)   
           {   
               //multiplying to make the diagonal   
               // element and next row element equal   
               matrix.values[j][k] = (num1 * matrix.values[j][k]) - (num2 * temp[k]);   
                   
           }   
           total = total * num1; // Det(kA)=kDet(A);   
           }   
            
    }   
    
    //mulitplying the diagonal elements to get determinant   
    for(uint8_t i = 0; i < matrix.rows; i++)   
    {   
        det = det * matrix.values[i][i];   
            
    }  
    return (det/total); //Det(kA)/k=Det(A);   

}

/*Matrix matrix_invertion(Matrix matrix)
{
    // Verify matrix determinant
    double det = matrix_determinant(matrix);
    if ( det == 0 )
    {
        fprintf(stderr,"Matrix isn't invertable because determinant is 0!");
        exit(EXIT_FAILURE);
    }

    return matrix_constantMultiplication(
        matrix_adjoint(matrix.name,matrix), 1.0/det );

} */

void matrix_identity(uint8_t degree, Matrix * matrix)
{
    matrix_zero(degree,degree,matrix);
    for ( uint8_t i = 0; i < degree; i++ )
    {
        (*matrix).values[i][i] = 1;
    }
}