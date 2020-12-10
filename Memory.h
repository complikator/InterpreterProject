#pragma once
#include"Enums.h"


typedef struct {
	int Value;
	Bool IsActive;
}MemoryCell;

typedef struct
{
	int Capacity;
	int Total;
}SectionInfo;

typedef struct
{
	int Code;
	CommandType commandType;
	int FirstRegister;
	int SecondRegister;
	int TargetRegister;
	int TargetDisplacement;
}Command;



typedef struct {
	MemoryCell** ProgramData;
	SectionInfo* DataSectionInfo;
	Command** Commands;
	SectionInfo* CommandsInfo;
	int ProgramCounter;
} Memory;

Memory CompilerMemory;


// reads data section lines from psa code 
// and make memory cells
void LoadCommands(char*);
