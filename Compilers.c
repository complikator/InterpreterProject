#include "Compilers.h"
#include<stdio.h>
#include"Constant.h"
#include<string.h>


void CompilePsaCode(char* filename) 
{
	FILE* inputFile;

	MakeLabels(filename);
	
	fopen_s(&inputFile, filename, "r");


}

void CompileMachineCode(char* filename) {}

