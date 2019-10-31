/**
 @file      simulation.h
 @brief     Describes methods to run a control system simulation.
 
This header describes mathods to run a control system simulation,
from a given time interval.

 @author    Guilherme S.S.
 @author    Brendo Otávio
 @version   1.0
 @date      03-10-2019  Guilherme S.S.

*/

#ifndef __SIMULATION_H
#define __SIMULATION_H

// C headers
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>
// User headers
#include "matrix.h"
#include "space_state.h"
#include "save_values.h"

// Thread for calculate input and output
static pthread_t tinput; /*!< Thread for input generation */
static pthread_t toutput; /*!< Thread for output generation */

// k simulation instant and k mutex
static pthread_mutex_t _k_mutex = PTHREAD_MUTEX_INITIALIZER; /*!< Semaphore to simulation time k protection */
static double k = 0; /*!< Simulation time k */

#define _MAX_TV_NSEC_VALUE             1000000000
/**
 * @brief Input simulation
 * @param arg Array of arguments with any type. In this function, must be
 * a double* type.
 */
void * calculateInputV(void * arg);

/**
 * @brief Output calculation and file generation through standart output,
 * @param arg Array of arguments with any type. In this function, must be
 * a double* type.
 */
void * calculateOutputV(void * arg);

/**
 * @brief Run a control system simulation from a time k0 to kf.
 * @param k0 Simulation initial time
 * @param kf Simulation end time
 * @param step Simulation step
 */
void runSimulation(double k0, double kf, double step);

#endif