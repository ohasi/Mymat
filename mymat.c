/*
mymat.c: handles input, output, and the passing of the mat type variables to other files.
*/

#include "mat.h"

#define isToken(c) (c != ' ' && c != '\t' && c != '\n' && c != EOF && c != '\0') ? TRUE : FALSE
/*      ^^^^^^^^^ checks if argument c is a token*/

#define TRUE 1	/*used for boolean-like expressions. true.*/
#define FALSE 0 /*used for boolean-like expressions. false.*/
#define IN 1    /*used when parsing. signals that the the parser is in a word.*/
#define OUT 0   /*used when parsing. signals that the the parser is not in a word.*/

mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F; /*declaring the matrixes*/

/*
main: initializes the matrixes, then asks the user to input a command and executes it. prints errors if there are any. 
stops when the user enters the command 'stop'.
returns 0, or the error code if there is any.
*/
int main() {
	int i, j, run, returnState;
	struct command commandStr;
	returnState = 0;
	run = TRUE;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			MAT_A[i][j] = MAT_B[i][j] = MAT_C[i][j] = MAT_D[i][j] = MAT_E[i][j] = MAT_F[i][j] = 0;
	while (run == TRUE) {
		printf("%s", "Please enter a command: ");
		commandStr = readCommand();
		returnState = getCommand(commandStr);
		if (returnState != 0)
			switch(returnState){
				case ILLEGAL_COMMA:
					printf("%s", "ILLEGAL_COMMA\n");
					break;
				case UNDEFINED_COMMAND:
					printf("%s", "UNDEFINED_COMMAND\n");
					break;
				case MISSING_PARAMETER:
					printf("%s", "MISSING_PARAMETER\n");
					break;
				case EXTRANEOUS_TEXT:
					printf("%s", "EXTRANEOUS_TEXT\n");
					break;
				case MULTIPLE_CONSECUTIVE_COMMAS:
					printf("%s", "MULTIPLE_CONSECUTIVE_COMMAS\n");
					break;
				case MISSING_COMMA:
					printf("%s", "MISSING_COMMA\n");
					break;
				case UNDEFINED_MATRIX_NAME:
					printf("%s", "UNDEFINED_MATRIX_NAME\n");
					break;
				case PARAMETER_NOT_SCALAR:
					printf("%s", "PARAMETER_NOT_SCALAR\n");
					break;
				case PARAMETER_NOT_REAL_NUMBER:
					printf("%s", "PARAMETER_NOT_REAL_NUMBER\n");
					break;
				default:
					printf("%d\n", returnState);
			}
		}
	return returnState;
	}

/*
readCommand: reads a command from the standar input, and parses it into a format that is friendly to the program.
turns any nubmer of spaces or tabs to one space, and counts hoe much arguments there are.
places /n/0 at the end of the command
returns a struct containing the command and number of arguments
*/
struct command readCommand(void) {
	int i;
	char *storedCmd = (char *)malloc(MAXSIZE * sizeof(char));
	int state = OUT;
	struct command toReturn;
	toReturn.cmd = (char *)malloc(MAXSIZE * sizeof(char));
	toReturn.argumentsc = 0;
	i = 0;
	fgets(storedCmd, MAXSIZE, stdin);
	while (*(storedCmd++) != '\n') {
		if (isToken(*(storedCmd - 1)) == TRUE) {
			if (*(storedCmd - 1) == ',')
				state = OUT;
			else if (state == OUT) {
				toReturn.argumentsc++;
				state = IN;
			}
			*(toReturn.cmd + i++) = *(storedCmd - 1);
		}
		else if (*(toReturn.cmd + (i - 1)) != ' ') {
			*(toReturn.cmd + (i++)) = ' ';
			state = OUT;
		}
	}
	*(toReturn.cmd + i++) = '\n';
	*(toReturn.cmd + i) = '\0';
	return toReturn;
}

/*
getCommand: calls the function coresponding to the command passed to is as a parameter.
param commandStr: a struct containing the command and the number of arguments
returns the value the function coresponding to the command passed to is as a parameter returns, or an error code if there's any error.
*/
int getCommand(struct command commandStr) {
	char *nextToken = strtok(commandStr.cmd, " \n");
	if(*(nextToken + strlen(nextToken) + 1) == ',' || *(nextToken + strlen(nextToken) + 2) == ',')
		return ILLEGAL_COMMA;
	else if (strcmp(nextToken, "add_mat") == 0) {
		if (commandStr.argumentsc != 4) {
			if (commandStr.argumentsc < 4)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else {
			commandStr.argumentsc--;
			return add_sub_mul_mat(commandStr.cmd + 8, "add_mat");
		}
	}
	else if (strcmp(nextToken, "sub_mat") == 0) {
		if (commandStr.argumentsc != 4) {
			if (commandStr.argumentsc < 4)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else {
			commandStr.argumentsc--;
			return add_sub_mul_mat(commandStr.cmd + 8, "sub_mat");
		}
	}
	else if (strcmp(nextToken, "mul_mat") == 0) {
		if (commandStr.argumentsc != 4) {
			if (commandStr.argumentsc < 4)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else {
			commandStr.argumentsc--;
			return add_sub_mul_mat(commandStr.cmd + 8, "mul_mat");
		}
	}
	else if (strcmp(nextToken, "read_mat") == 0) {
		if (commandStr.argumentsc < 3)
			return MISSING_PARAMETER;
		else
			return read_mat(commandStr.cmd + 9, commandStr.argumentsc - 1);
	}
	else if (strcmp(nextToken, "print_mat") == 0) {
		if (commandStr.argumentsc != 2) {
			if (commandStr.argumentsc < 2)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else
			return print_mat(commandStr.cmd + 10);
	}
	else if (strcmp(nextToken, "mul_scalar") == 0) {
		if (commandStr.argumentsc != 4) {
			if (commandStr.argumentsc < 4)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else {
			commandStr.argumentsc--;
			return mul_scalar(commandStr.cmd + 11);
		}
	}
	else if (strcmp(nextToken, "trans_mat") == 0)
	{
		if (commandStr.argumentsc != 3) {
			if (commandStr.argumentsc < 3)
				return MISSING_PARAMETER;
			else
				return EXTRANEOUS_TEXT;
		}
		else
			return trans_mat(commandStr.cmd + 10);
	}
	else if (strcmp(nextToken, "stop") == 0) {
		if (commandStr.argumentsc == 1)
			exit(0);
		else
			return EXTRANEOUS_TEXT;
	}
	else if (*(nextToken + strlen(nextToken) - 1) == ',' || *nextToken == ',')
		return ILLEGAL_COMMA;
	else
		return UNDEFINED_COMMAND;
	return 0;
}

/*
parseArgToMat: gets the next argument. if it's a name of a matrix, returns the matrix. 
otherwise, set argumentsv[0] to EOF, and argumentsv[1] to the error code.
param argumentsv: the argument list
*/
double *parseArgToMat(char *argumentsv) {
	char *arg;
	double *toReturn = 0;
	if (*argumentsv != EOF) {
		arg = strtok(NULL, ",\n");
		if(strlen(arg) == 1 || strlen(arg) == 2)
			prepError(MULTIPLE_CONSECUTIVE_COMMAS, argumentsv);
		else if(*(arg + strlen(arg) + 1) == '\n')
			prepError(EXTRANEOUS_TEXT, argumentsv);
		else if (*(arg - 1) == ',')
			prepError(MULTIPLE_CONSECUTIVE_COMMAS, argumentsv);
		else {
			if (*(arg + strlen(arg) - 1) == ' ')
				*(arg + strlen(arg) - 1) = '\0';
			while (*arg == ' ')
				++arg;
			if (strcmp(arg, "MAT_A") == 0)
				toReturn = &MAT_A[0][0];
			else if (strcmp(arg, "MAT_B") == 0)
				toReturn = &MAT_B[0][0];
			else if (strcmp(arg, "MAT_C") == 0)
				toReturn = &MAT_C[0][0];
			else if (strcmp(arg, "MAT_D") == 0)
				toReturn = &MAT_D[0][0];
			else if (strcmp(arg, "MAT_E") == 0)
				toReturn = &MAT_E[0][0];
			else if (strcmp(arg, "MAT_F") == 0)
				toReturn = &MAT_F[0][0];
			else
				prepError(UNDEFINED_MATRIX_NAME, argumentsv);
		}
	}
	return toReturn;
}

/*
prepError: modifies argumentsv to signal there's an error and tell what it is
sets argumentsv[0] to EOF and argumentsv[1] to err
param argumentsv: the string in which to signal an error
param err: the error code
*/
void prepError(int err, char *argumentsv){
	*argumentsv = EOF;
	*(argumentsv + 1) = err;
}