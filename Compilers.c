#include "Compilers.h"
#include<stdio.h>
#include"Constant.h"
#include<string.h>
#include"Memory.h"

void CompilePsaCode(char* filename) 
{
	MakeLabels(filename);
	LoadCommands(filename);

}

void CompileMachineCode(char* filename) {}

