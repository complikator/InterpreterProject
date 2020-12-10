#include<stdio.h>
#include "Constant.h"
#include "Validation.h"
#include"Enums.h"

int main(int argc, char* argv[])
{
	char InputPath[MAX_PATH_SIZE];
	argv[1] = "example_input.txt"; argc = 2;
	// check if path to psa code file was passed
	CheckInputPathExistence(argc, argv, InputPath);

	// check if psa code file exist 
	CheckIfFileIsPossibleToOpen(InputPath);
	argv[2] = "psa_code";
	// check if input file is psa or machine code
	if (IsPsaCodeFile(argv[2]) == True)
	{
		CompilePsaCode(InputPath);
	}
	else // machine code
	{
		CompileMachineCode(InputPath);
	}



	return 0;
}