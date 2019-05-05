#ifndef MAT
#define MAT

#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

#define MAXSIZE 256					  /*Max string length*/
#define MATSIZE 4					  /*Matrixes' dimensions are (MATSIZE*MATSIZE)*/

enum errorCode {
	ILLEGAL_COMMA = 1,				  /*Error code for illegal comma*/
	UNDEFINED_COMMAND = 2,			  /*Error code for undefined command*/
	MISSING_PARAMETER = 3,			  /*Error code for missing parameter*/
	EXTRANEOUS_TEXT = 4,			  /*Error code for extra parameter(s)*/
	MULTIPLE_CONSECUTIVE_COMMAS = 5, /*Error code for multiple consecutive commas*/
	MISSING_COMMA = 6,				  /*Error code for missing comma*/
	UNDEFINED_MATRIX_NAME = 7,		  /*Error code for undefined matrix name*/
	PARAMETER_NOT_SCALAR = 8,		  /*Error code for parameter not being a scalar when it is expected to*/
	PARAMETER_NOT_REAL_NUMBER = 9   /*Error code for parameter not being a number when it is expected to*/

};

typedef double mat[MATSIZE][MATSIZE];

struct command {
	char *cmd;
	int argumentsc;
}; /*
	command: struct used in order to return 2 parameters for some functions. The 2 parameters are: 
	cmd: the command string
	argumentsc: number of arguments
*/

void prepError(int err, char *argumentsv);    /*returns a pointer to the error code given in err, and changes argumentsv to signal an error*/
void copyMat(double *mat1, double *mat2);		  /*copies mat1 into mat2*/
double *parseArgToMat(char *argumentsv); /*gets the next argument from argumentsv, and returns a pointer to the mat specified in that argument. if ther's any error, it returns the corresponding error code instead. cmdType used for error checking. assumes cmdType is a valid command*/
int add_sub_mul_mat(char *argumentsv, char *cmdType);   /*adds, multiplies or subtracts (depending on the value in cmdType) the second mat in argumentsv with the first mat in argumentsv and places the result in the third mat in argumentsv. if there's any error, returns the coresponding error code.*/
int getCommand(struct command commandStr);		  /*calls the command corresponding to the command in commandStr. if there's any error, returns the coresponding error code.*/
int print_mat(char *argumentsv);						  /*prints the passed matrix to the console. if there's any error, returns the coresponding error code.*/
int mul_mat(char *argumentsv);						  /*multiplies the first and second mats in argumentsv, and places the result in the third. if there's any error, returns the coresponding error code.*/
int read_mat(char *argumentsv, int argumentsc);				  /*reads a matrix into the specified matrix. if there's less then 16 values, the missing values are set to 0. if there's any error, returns the coresponding error code.*/
int mul_scalar(char *argumentsv);						  /*multiplies the matrix passed in the first argument by the number passed in the second argument and stores the value in the matrix passed in the third argument. if there's any error, returns the coresponding error code.*/
int trans_mat(char *argumentsv);						  /*transposes the matrix passed in the first argument and stores the result in the matrix passed in the second argument. if there's any error, returns the coresponding error code.*/
struct command readCommand(void);				  /*reads a command from the user*/

#endif