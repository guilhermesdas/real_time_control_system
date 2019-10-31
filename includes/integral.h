/**
 @file      integral.h
 @brief     Integral operations in double functions
 
This header describes integral operations in double functions,
passed as function pointers.

 @author    Guilherme S.S.
 @author    Brendo Otávio
 @email		gsds@icomp.ufam.edu.br
 @version   1.0
 @date      03-10-2019  Guilherme S.S.

*/

#define N_ITERATIONS       1000

/**
 * @brief Calculate defined integral of a function from k0 to kf on discrete domain.
 * @param f Pointer to function to be integrated
 * @param k0 Initial time
 * @param kf End time
 * @return Result of 
 */
double integral(double (*f)(double k), double k0, double kf);