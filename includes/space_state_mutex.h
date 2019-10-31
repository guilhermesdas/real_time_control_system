/**
 @file      space_state_mutex.h
 @brief     Space State mutex protection
 
This header defines get and set operations to double space state vectors 
with mutex protection

 @author    Guilherme S.S.
 @author    Brendo Otávio
 @version   1.0
 @date      25-10-2019  Guilherme S.S.

*/

#ifndef __SPACE_STATE_MUTEX_H
#define __SPACE_STATE_MUTEX_H

#include "matrix.h"
#include <time.h>
#include <pthread.h>

// 1 ms = 10^6 ns
#define _MS_TO_US(ms)    ms*1000    /*!< Milisseconds to microsseconds convertion */
#define _MS_TO_NS(ms)    ms*1000000 /*!< Milisseconds to microsseconds convertion */

// Input and Output vectors
static Matrix * _inputV_k; /*!< Input vector in instant k  */
static Matrix * _outputV_k; /*!< Output vector in instant k  */
// Input and Output semaphores for shared variables inputV and outputV
static pthread_mutex_t _inputV_mutex = PTHREAD_MUTEX_INITIALIZER; /*!< Input mutex  */
static pthread_mutex_t _outputV_mutex = PTHREAD_MUTEX_INITIALIZER; /*!< Output mutex  */

// Input vector thread safety operations

/**
 * @brief Initialize input vector and input vector mutex
 * @param rows Input vector rows
 * @param columns Input vector columns
 */
void inputV_init(int rows, int columns);

/**
 * @brief Set matrix values to input matrix
 * @param inputV Matrix to set in input vector
 */
void inputV_set(Matrix inputV);

/**
 * @brief Get input vector
 * @param inputV_k Matrix pointer to put input vector values
 */
void inputV_get(Matrix * inputV_k);

/**
 * @brief Print current input vector values
 */
void inputV_print();

/**
 * @brief Destroy input vector and input vector mutex.
 */
void inputV_destroy();

// Output vector thread safety operations

/**
 * @brief Initialize Output vector and Output vector mutex
 * @param rows Output vector rows
 * @param columns Output vector columns
 */
void outputV_init(int rows, int columns);

/**
 * @brief Set matrix values to Output matrix
 * @param outputV Matrix to set in Output vector
 */
void outputV_set(Matrix outputV);

/**
 * @brief Print current Output vector values
 */
void outputV_get(Matrix * outputV_k);

void outputV_wait(long ms);

/**
 * @brief Print current Output vector values
 */
void outputV_print();

/**
 * @brief Destroy Output vector and Output vector mutex.
 */
void outputV_destroy();


#endif // __SPACE_STATE_MUTEX_H