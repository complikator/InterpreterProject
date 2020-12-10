#pragma once
#include"HelperStructs.h"
#include"Enums.h"
#include<string.h>
#include"Constant.h"


// deletes white characters from already preparsed command
// and returns amount of cells in memory to alloc
// string passed to a function must be a strtok function 
// product to work correctly
int GetDSVariableAmount(char*, char**);

// deletes white characters from already preparsed command
// returns amount and values of cells in memory to alloc
// string passed to a function must be a strtok function 
// product to work correctly
DcParameters* GetDCParameters(char*, char**);

// gets command parameters from order section
void* GetCommandParameters(CommandType, char*, char**);

int GetInstructionCode(char* instr)
{
	if (strcmp(instr, "AR") == 0)
	{
		return AR;
	}
	if (strcmp(instr, "A") == 0)
	{
		return A;
	}
	if (strcmp(instr, "SR") == 0)
	{
		return SR;
	}
	if (strcmp(instr, "S") == 0)
	{
		return S;
	}
	if (strcmp(instr, "MR") == 0)
	{
		return MR;
	}
	if (strcmp(instr, "M") == 0)
	{
		return M;
	}
	if (strcmp(instr, "DR") == 0)
	{
		return DR;
	}
	if (strcmp(instr, "D") == 0)
	{
		return D;
	}
	if (strcmp(instr, "CR") == 0)
	{
		return CR;
	}
	if (strcmp(instr, "C") == 0)
	{
		return C;
	}
	if (strcmp(instr, "J") == 0)
	{
		return J;
	}
	if (strcmp(instr, "JZ") == 0)
	{
		return JZ;
	}
	if (strcmp(instr, "JP") == 0)
	{
		return JP;
	}
	if (strcmp(instr, "JN") == 0)
	{
		return JN;
	}
	if (strcmp(instr, "L") == 0)
	{
		return L;
	}
	if (strcmp(instr, "LR") == 0)
	{
		return LR;
	}
	if (strcmp(instr, "LA") == 0)
	{
		return LA;
	}
	if (strcmp(instr, "ST") == 0)
	{
		return ST;
	}
}