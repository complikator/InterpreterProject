#include"Validation.h"
#include<stdio.h>
#include<string.h>

#include "Constant.h"
#include"Enums.h"

void CheckInputPathExistence(int argc, char* argv[], char* inputPath)
{
	if (argc == 1)
	{
		printf("Brak sciezki do pliku\nPodaj sciezke do pliku wejsciowego:\n");

		while (scanf_s("%s", inputPath, MAX_PATH_SIZE) == 0)
		{
			printf("Podaj sciezke do pliku wejsciowego:\n");
		}
	}
	else
	{
		strcpy_s(inputPath, MAX_PATH_SIZE * sizeof(char), argv[1]);
	}
}

void CheckIfFileIsPossibleToOpen(char* inputPath)
{
	FILE* input;
	while (fopen_s(&input, inputPath, "r") != 0)
	{
		printf("Plik o tej nazwie nie istnieje lub zostala podana zla sciezka.\nPodaj sciezke do pliku wejsciowego:\n");

		while (scanf_s("%s", inputPath, MAX_PATH_SIZE) == 0)
		{
			printf("Podaj sciezke do pliku wejsciowego:\n");
		}
	}
}

Bool IsPsaCodeFile(char* codeOption)
{
	if (strcmp(codeOption, "psa_code") == 0)
	{
		return True;
	}
	return False;
}

Bool IsNumber(char c)
{
	if (c >= '0' && c <= '9')
	{
		return True;
	}
	return False;
}