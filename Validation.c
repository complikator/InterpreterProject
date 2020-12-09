#include "Validation.h"
#include<stdio.h>

#include "Constant.h"

void CheckInputPath(int argc, char* argv, char* inputPath, FILE* input)
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