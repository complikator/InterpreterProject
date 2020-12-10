#pragma once
#include<stdio.h>
#include"Enums.h"

// checks if input path already exist and get it if not
void CheckInputPathExistence(int, char*, char*);

// checks if it possible to open a file
void CheckIfFileIsPossibleToOpen(char*);

// determine if given file is psa code file
int IsPsaCodeFile(char*);

Bool IsNumber(char)