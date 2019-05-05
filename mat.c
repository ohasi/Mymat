/*
mat.c: This file houses the functions that manage all of the commands (add_mat, sub_mat, etc..),
	   and some other functions that help the functionality of the previously mentioned functions.
*/

#include "mat.h"

/*
add_sub_mul_mat: handles adding, subtracting, and multiplying matrixes. 
reads the matrixes from the argument list, copies them to internal matrixes, calculates the result with the internal matrixes and copies the result to the third matrix in the input.
param argumentsv: the argument list
param cmdName: the command's name (to know whether to add, subtract or multiply the matrixes)
return 0, or an error code if there was any error.
*/
int add_sub_mul_mat(char *argumentsv, char *cmdName) {
	int i, j, k;
	double *mat1, *mat2, *mat3; 
	mat tmp1, tmp2, tmp3;
	double currentMultiplicationValue;
	mat1 = parseArgToMat(argumentsv);
	mat2 = parseArgToMat(argumentsv);
	mat3 = parseArgToMat(argumentsv);
	if (*argumentsv == EOF)
		return (int)*(++argumentsv);
	copyMat(mat1, &tmp1[0][0]);
	copyMat(mat2, &tmp2[0][0]);
	copyMat(mat3, &tmp3[0][0]);
	i = 0;
	if (strcmp(cmdName, "add_mat") == 0)
		while (i++ < MATSIZE * MATSIZE)
			*((&tmp3[0][0]) + (i - 1)) = *((&tmp1[0][0]) + (i - 1)) + *((&tmp2[0][0]) + (i - 1));
	else if (strcmp(cmdName, "sub_mat") == 0)
		while (i++ < MATSIZE * MATSIZE)
			*((&tmp3[0][0]) + (i - 1)) = *((&tmp1[0][0]) + (i - 1)) - *((&tmp2[0][0]) + (i - 1));
	else if (strcmp(cmdName, "mul_mat") == 0) {
		currentMultiplicationValue = 0;
		for (i = 0; i < MATSIZE; i++)
			for (j = 0; j < MATSIZE; j++) {
				for (k = 0; k < MATSIZE; k++)
					currentMultiplicationValue += tmp1[i][k] * tmp2[k][j];
				tmp3[i][j] = currentMultiplicationValue;
				currentMultiplicationValue = 0;
			}
	}
	copyMat(&tmp3[0][0], mat3);
	return 0;
}

/*
print_mat: prints the given matrix to the standard output.
param argumentsv: the argument list, holding the matrix to print
return 0, or an error code if there was any error.
*/
int print_mat(char *argumentsv) {
	int i;
	double *mat = parseArgToMat(argumentsv);
	i = 0;
	if (*argumentsv == EOF)
		return (int)*(++argumentsv);
	else
		while (i++ < 16) {
			printf("%7g", *(mat + (i - 1)));
			if ((i % 4) == 0)
				printf("\n");
		}
	return 0;
}

/*
copyMat: copies mat1 into mat2 cell by cell
param mat1: the matrix to copy
param mat2: the matrix to copy to
*/
void copyMat(double *mat1, double *mat2) {
	int i = 0;
	while (i++ < 16)
		*(mat2 + (i - 1)) = *(mat1 + (i - 1));
}

/*
read_mat: reads arguments from argumentsv and places them in the internal matrix until there are no more arguments.
if there aren't enough arguments to fill the matrix, the remaining cells are 0.
then, copies the internal matrix into the specified matrix.
param argumentsv: the argument list
param argumentsc: the amount of arguments
return 0, or an error code if there was any error.
*/
int read_mat(char *argumentsv, int argumentsc) {
	int i, j;
	double *matr;
	mat result;
	char *nextArg;
	for (i = 0; i < 16; i++)
		*(&(result[0][0]) + i) = 0;
	i = j = 0;
	matr = parseArgToMat(argumentsv);
	argumentsc--;
	if (*argumentsv == EOF)
		return (int)*(++argumentsv);
	nextArg = strtok(NULL, ",\n");
	while (argumentsc-- > 0) {
		while (*nextArg == ' ')
			++nextArg;
		for (i = 0; *(nextArg + i) != '\0'; i++)
			if (!(isdigit(*(nextArg + i)) || (*(nextArg + i)) == '.' || (*(nextArg + i)) == ' ' || (*(nextArg + i)) == '+' || (*(nextArg + i)) == '-'))
				return PARAMETER_NOT_REAL_NUMBER;
		*(&(result[0][0]) + j++) = atof(nextArg);
		if (*(nextArg + strlen(nextArg) + 1) == '\n')
			return EXTRANEOUS_TEXT;
		nextArg = strtok(NULL, ",\n");
	}
	copyMat(&(result[0][0]), matr);
	return 0;
}

/*
mul_scalar: multiplies each cell in the specified matrix by the scalar
argumentsv: the argument list, holding the matrix name and the scalar.
return 0, or an error code if there was any error.
*/
int mul_scalar(char *argumentsv) {
	int i;
	double *mat1, *mat2;
	mat result;
	char *temp;
	double scalar;
	i = 0;
	mat1 = parseArgToMat(argumentsv);
	temp = strtok(NULL, ",");
	while (*temp == ' ')
		++temp;
	if (*temp == ',' || *(temp + 1) == ',')
		return MULTIPLE_CONSECUTIVE_COMMAS;
	else
		while (i++ < strlen(temp))
			if (!isdigit(*(temp + i - 1)))
				return PARAMETER_NOT_SCALAR;
	scalar = atof(temp);
	mat2 = parseArgToMat(argumentsv);
	if (*argumentsv == EOF)
		return (int)*(++argumentsv);
	i = 0;
	while (i++ < 16)
		*(mat2 + (i - 1)) = *(mat1 + (i - 1)) * scalar;
	copyMat(mat2, &(result[0][0]));
	return 0;
}

/*
trans_mat: rotates the given matrix counter-clockwise, and places the result in an internal matrix. then, copies the internal matrix to the result matrix
param argumentsv: the list of arguments
return 0, or an error code if there was any error.
*/
int trans_mat(char *argumentsv) {
	int i, j;
	mat transposedMat;
	double *mat1, *result;
	mat1 = parseArgToMat(argumentsv);
	result = parseArgToMat(argumentsv);
	if(*argumentsv == EOF)
		return (int) *(++argumentsv);
	i = 0;
	while (i++ < 4 * MATSIZE)
		*(&transposedMat[0][0] + (i - 1)) = 0;
	if (*argumentsv == EOF)
		return (int)*(++argumentsv);
	else
		for (i = 0; i < MATSIZE; i++)
			for (j = 0; j < MATSIZE; j++)
				transposedMat[i][j] = *(mat1 + (j * MATSIZE) + i);
	copyMat(&transposedMat[0][0], result);
	return 0;
}