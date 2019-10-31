/**
 @file      matrix.h
 @brief     Matrix Abstract Data Type
 
This header describes operations to the point-floating ADT Matrix.

 @author    Guilherme S.S.
 @author    Brendo Otávio
 @version   1.0
 @date      27-09-2019  Guilherme S.S.

 @todo      Add function as parameter to calculate values in matrix_creates
 @todo      Add function to perform an operation between values and pass as parameter
                to operation functions.
 @todo      Add matrix_random function
 @todo      Remove name in parameters and just assign same matrix name
 @todo      Add function to create a matrix with assigned values (array [][])
 @todo      Change functions to accept Matrix pointer as parameter instead of return a Matrix

*/

#ifndef __MATRIX_H
#define __MATRIX_H

// C headers
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS_MAX                10  /*!< Max number of rows */
#define COLUMNS_MAX             10  /*!< Max number of columns */
#define NAME_MAX_SIZE                10  /*!< Max name size */

/*! \struct Matrix
    \brief Abstract Data Type Matrix

    ADT Matrix represents a math matrix
 */
typedef struct
{
    char name[NAME_MAX_SIZE];
    uint8_t rows;  // rows
    uint8_t columns;  // columns 
    double values[ROWS_MAX][COLUMNS_MAX];
} Matrix;

/**
 * @brief Print matrix elements
 * @param matrix Matrix to be displayed
 */
void matrix_print(Matrix matrix);

/**
 * @brief Create a matrix with zeros (Zero Matrix)
 * @param name Matrix name
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns
 * @return Return a Zero Matrix
 * @deprecated
 */
Matrix matrix_zeros(char * name, uint8_t rows, uint8_t columns);

/**
 * @brief Create a matrix with zeros (Zero Matrix)
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns
 * @param matrix Pointer to zero matrix
 */
void matrix_zero(uint8_t rows, uint8_t columns, Matrix * matrix);

/**
 * @brief Create a matrix with ones
 * @param name Matrix name
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns
 * @return Return a matrix of ones
 */
Matrix matrix_ones(char * name, uint8_t rows, uint8_t columns);

/**
 * @brief Create a identity matrix, with ones in main
 *          diagonal.
 * @param degree Number of matrix rows and columns
 * @param matrix Pointer to matrix
 */
void matrix_identity(uint8_t degree, Matrix * matrix);

/**
 * @brief Create a matrix with random values
 * @param name Matrix name
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns
 * @return Return created matrix
 */
Matrix matrix_random(char * name, uint8_t rows, uint8_t columns);

/**
 * @brief Create a custom matrix with an initial value.
 * @param name Matrix name
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns]
 * @param initValues Initial values
 * @return Return created matrix
 */
Matrix matrix_create(char * name, uint8_t rows, uint8_t columns, double initValues);

/**
 * @brief Validate bounds of a matrix, considering ROWS_MAX
 *          and COLUMNS_MAX
 * @param rows Number of matrix rows
 * @param columns Number of matrix columns
 * @return Return true, if quantity of rows and columns are
 *          valids
 */
uint8_t matrix_validateBounds(uint8_t rows, uint8_t columns);

/**
 * @brief Perform a sum operation between two matrix
 * @param name Matrix name
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @param matrixOutput Pointer to Matrix Result
 */
void matrix_addition(Matrix * matrix1, Matrix * matrix2, Matrix * matrixOutput);

/**
 * @brief Perform a subtraction operation between two matrix
 * @param name Matrix name
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @return Return the subtraction of two matrix
 */
Matrix matrix_subtraction(char * name, Matrix matrix1, Matrix matrix2);

/**
 * @brief Perform a matrix product operation
 * @param name Matrix name
 * @param matrix1 First matrix
 * @param matrix2 Second matrix
 * @param matrixResult Pointer Matrix Result
 */
void matrix_multiplication(Matrix * matrix1, Matrix * matrix2, Matrix * matrixResult);

/**
 * @brief Perform a matrix addition operation by a constant value
 * @param matrix Matrix
 * @param value Constant value
 * @return Return a resulting matrix with value added
 */
Matrix matrix_constantAddition(Matrix matrix, double value);

/**
 * @brief Perform a matrix subtraction operation by a constant value
 * @param matrix Matrix
 * @param value Constant value
 * @return Return a resulting matrix with value subtracted
 */
Matrix matrix_constantSubtraction(Matrix matrix, double value);

/**
 * @brief Perform a matrix multiplication operation by a constant value
 * @param matrix Pointer to matrix
 * @param value Constant value
 */
void matrix_constantMultiplication(Matrix * matrix, double value);

/**
 * @brief Verify if matrix is square
 * @param matrix Matrix
 * @return Return 0 if matrix has equal number of rows and
 *          columns, return 1 otherwise.
 */
uint8_t matrix_isSquare(Matrix matrix);

/**
 * @brief Perform a matrix transpose operation
 * @param name Matrix name
 * @param matrix Matrix
 * @return Return the transpose of the matrix
 */
Matrix matrix_transpose(char * name, Matrix matrix);

/**
 * @brief Get matrix cofactor. Based on 
    https://www.geeksforgeeks.org/determinant-of-a-matrix/ and
    https://www.cs.rochester.edu/u/brown/Crypto/assts/projects/adj.html
 * @param name Matrix name
 * @param matrix Matrix
 * @return Return the determinant of the matrix
 */
Matrix matrix_cofactor(char * name, Matrix matrix);

/**
 * @brief Get adjoint matrix. Based on
 *    https://www.cs.rochester.edu/u/brown/Crypto/assts/projects/adj.html
 * @param name Matrix name
 * @param matrix Matrix
 * @return Return the adjoint of the matrix
 */
Matrix matrix_adjoint(char * name, Matrix matrix);

/**
 * @brief Determinant of a square matrix. Based on 
    https://www.geeksforgeeks.org/determinant-of-a-matrix/
 * @param matrix Matrix
 * @return Return the matrix determinant
 */
double matrix_determinant(Matrix matrix);

/**
 * @brief Invertion of a square matrix. Based on
 *    https://www.cs.rochester.edu/u/brown/Crypto/assts/projects/adj.html
 * @param matrix Matrix
 * @return Return the matrix invertion
 */
Matrix matrix_invertion(Matrix matrix);

#endif