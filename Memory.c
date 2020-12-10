#include<stdio.h>
#include"Constant.h"
#include"Strings.h"
#include"Enums.h"
#include"Parsers.h"
#include<string.h>
#include"Memory.h"
#include"HelperStructs.h"

void InitMemory()
{
	CompilerMemory.ProgramData = (MemoryCell*)malloc(sizeof(MemoryCell) * INITIAL_MEMORY_SIZE);
	CompilerMemory.DataSectionInfo = (SectionInfo*)malloc(sizeof(SectionInfo));
	CompilerMemory.DataSectionInfo->Capacity = INITIAL_MEMORY_SIZE;
	CompilerMemory.DataSectionInfo->Total = 0;

	CompilerMemory.Commands = (Command**)malloc(sizeof(Command) * INITIAL_MEMORY_SIZE);
	CompilerMemory.CommandsInfo = (SectionInfo*)malloc(sizeof(SectionInfo));
	CompilerMemory.CommandsInfo->Capacity = INITIAL_MEMORY_SIZE;
	CompilerMemory.CommandsInfo->Total = 0;

	CompilerMemory.ProgramCounter = 0;
}

void ResizeCompilerMemory(int capacity)
{
	MemoryCell** cells = realloc(CompilerMemory.ProgramData, capacity);

	if (cells)
	{
		CompilerMemory.ProgramData = cells;
		CompilerMemory.DataSectionInfo->Capacity = capacity;
	}
}


MemoryCell* MakeMemoryCell(int value, Bool isActive)
{
	MemoryCell* newCell = (MemoryCell*)malloc(sizeof(MemoryCell));
	newCell->IsActive = isActive;
	newCell->Value = value;

	return newCell;
}

void AddCellsToMemory(int amount, Bool isActive, int value)
{
	while (amount--)
	{
		if (CompilerMemory.DataSectionInfo->Capacity = CompilerMemory.DataSectionInfo->Total)
		{
			ResizeCompilerMemory(CompilerMemory.DataSectionInfo->Capacity * 2);
		}

		CompilerMemory.ProgramData[CompilerMemory.DataSectionInfo->Total++] = MakeMemoryCell(value, isActive);
	}
}


void CreateProgramMemory(FILE* input)
{
	char line[MAX_LINE_SIZE];
	char* found = NULL;
	char* token = NULL;
	int amount;
	DcParameters* dcParams;

	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		DeleteCommentFromCommand(line);

		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		if (LabelInCommandExist(line) == True)
		{
			found = strtok_s(line, MAX_LINE_SIZE, &token);
			found = strtok_s(NULL, MAX_LINE_SIZE, &token);
		}
		else
		{
			found = strtok_s(line, MAX_LINE_SIZE, &token);
		}

		if (strcmp(found, "DS") == 0)
		{
			amount = GetDSVariableAmount(found, &token);
			AddCellsToMemory(amount, False, 0);
		}
		else
		{
			dcParams = GetDCParameters(found, &token);

			AddCellssToMemory(dcParams->Amount, True, dcParams->Value);
		}
	}

	fclose(input);
}

Command* MakeCommand(int code, CommandType commandType, int firstRegister, int secondRegister, int targetRegister, int targetDisplacement)
{
	Command* newCommand = (Command*)malloc(sizeof(Command));

	newCommand->Code = code;
	newCommand->commandType = commandType;
	newCommand->FirstRegister = firstRegister;
	newCommand->SecondRegister = secondRegister;
	newCommand->TargetRegister = targetRegister;
	newCommand->TargetDisplacement = targetDisplacement;

	return newCommand;
}

void ResizeCommandsCollection(int capacity)
{
	Command** commands = realloc(CompilerMemory.Commands, capacity);

	if (commands)
	{
		CompilerMemory.Commands = commands;
		CompilerMemory.CommandsInfo->Capacity = capacity;
	}
}

void AddCommand(int code, CommandType commandType, int firstRegister, int secondRegister, int targetRegister, int targetDisplacement)
{
	if (CompilerMemory.CommandsInfo->Capacity = CompilerMemory.CommandsInfo->Total)
	{
		ResizeCommandsCollection(CompilerMemory.CommandsInfo->Capacity * 2);
	}

	CompilerMemory.Commands[CompilerMemory.CommandsInfo->Total++] = MakeCommand(code, commandType, firstRegister, secondRegister, targetRegister, targetDisplacement);
}


void CreateCommands(FILE* input)
{
	char line[MAX_LINE_SIZE];
	char* found = NULL;
	char* token = NULL;
	char* charToCompare = NULL;
	R2RCommandParameters* r2rParams = NULL;
	R2MCommandParameters* r2mParams = NULL;
	MOCommandParameters* moParams = NULL;
	int code;

	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		DeleteCommentFromCommand(line);

		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		if (LabelInCommandExist(line) == True)
		{
			found = strtok_s(line, " \t\r", &token);
			found = strtok_s(NULL, " \t\r", &token);
		}
		else
		{
			found = strtok_s(line, " \t\r", &token);
		}

		charToCompare = (char*)malloc(sizeof(char) * 3);
		charToCompare[0] = found[1];
		charToCompare[1] = '\0';
		// register-register command
		if (strcmp(charToCompare, "R") == 0)
		{
			r2rParams = (R2RCommandParameters*)GetCommandParameters(Register2Register, found, &token);

			
		}

	}
}

void LoadCommands(char* filename)
{
	FILE* input;

	InitMemory();
	fopen_s(&input, filename, "r");

	CreateProgramMemory(input);

	CreateCommands(input);
}

