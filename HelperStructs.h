#pragma once
#include"Enums.h"

typedef struct DcParameters {
	int Amount;
	int Value;
}DcParameters;

typedef struct
{
	int FirstRegister;
	int SecondRegister;
}R2RCommandParameters;

typedef struct
{
	int Register;
	int TargetRegister;
	int TargetDisplacement;
}R2MCommandParameters;

typedef struct
{
	int TargetRegister;
	int TargetDisplacement;
}MOCommandParameters;

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

	int CommandDisplacement;
}Command;



typedef struct {
	MemoryCell** ProgramData;
	SectionInfo* DataSectionInfo;
	Command** Commands;
	SectionInfo* CommandsInfo;
	int ProgramCounter;
	int Registers[17];

	Bool Zero;
	Bool Negative;
	Bool Positive;
} Memory;