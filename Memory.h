#pragma once
#include"Enums.h"
#include"HelperStructs.h"



Memory CompilerMemory;


void AddCellsToMemory(int, Bool, int);

void CreateProgramMemory(FILE*);

// reads data section lines from psa code 
// and make memory cells
void LoadCommands(char*);

Command* GetCommand(int);

int GetCellValue(int);

int GetCommandNumberByDisplacement(int);

void SetCellValue(int, int);

MemoryCell* GetCell(int);

void LoadHexCommands(char*);