#include<stdio.h>
#include "Constant.h"


int main(int argc, char* argv[])
{
	FILE* Input;
	char InputPath[MAX_PATH_SIZE];



	// check if path to psa code file was passed
	

	// check if psa code file exist 
	while (fopen_s(&Input, InputPath, "r") != 0)
	{
		printf("Plik o tej nazwie nie istnieje lub zostala podana zla sciezka.\nPodaj sciezke do pliku wejsciowego:\n");

		while (scanf_s("%s", InputPath, MAX_PATH_SIZE) == 0)
		{
			printf("Podaj sciezke do pliku wejsciowego:\n");
		}
	}

	// check if input file is psa or machine code
	if (IsPsaCodeFile(InputPath) == TRUE)
	{
		CompilePsaCode();
	}
	else // machine code
	{
		CompileMachineCode();
	}



	return 0;
}