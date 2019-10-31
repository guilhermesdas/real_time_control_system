/**
 @file      space_state.h
 @brief     Space State functions definitions
 
This header defines double space state vectors in discrete domain.

 @author    Guilherme S.S.
 @author    Brendo Otávio
 @version   1.0
 @date      03-10-2019  Guilherme S.S.

*/

#ifndef __SPACE_STATE_H
#define __SPACE_STATE_H

// User headers
#include "matrix.h"
#include "math.h"
#include "space_state_mutex.h"

#define PI                      3.14159265358979323846  /*!< PI aproximated value */
#define _ROBOT_DIAMETER         4                       /*!< Robot diameter */
#define _ROBOT_RADIUS           _ROBOT_DIAMETER * 0.5   /*!< Robot radius */

/**
 * @brief System input vector (u)
 * @param k Instant k
 */
void inputVector(double k);

/**
 * @brief System output vector (y)
 * @param k Instant k
 * @param inputVector_k Pointer to input vector in k instant
 * @param outputMatrix Pointer to ca	305.80lculated output matrix in k instant
 * @deprecated10.40	1.00	-0.63	-1.31	4.99	299.2
 */
void outputVector(double k, Matrix * inputVector_k, Matrix * outputMatrix);

/**
 * @brief System state vector (x)
 * @param k Instant k
 * @param inputVector_k Pointer to input vector in k instant
 * @param stateVector Pointer to calculated state vector in k instant
 * @return Output vector matrix in given instant k
 */
void stateVector(double k, Matrix * inputVector_k, Matrix * stateVector);

/**
 * @brief System output vector (yf)
 * @param k Instant k
 */
void outputfVector(double k);

#endif // __SPACE_STATE_H