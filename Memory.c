#include<stdio.h>
#include"Constant.h"
#include"Strings.h"
#include"Enums.h"
#include"Parsers.h"
#include<string.h>
#include"Memory.h"
#include"HelperStructs.h"
#include"Labels.h"
#include"Validation.h"
#include<stdlib.h>

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
	MemoryCell** cells = realloc(CompilerMemory.ProgramData, sizeof(MemoryCell*) * capacity);

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
	while (amount > 0)
	{
		if (CompilerMemory.DataSectionInfo->Capacity == CompilerMemory.DataSectionInfo->Total)
		{
			ResizeCompilerMemory(CompilerMemory.DataSectionInfo->Capacity * 2);
		}

		CompilerMemory.ProgramData[CompilerMemory.DataSectionInfo->Total++] = MakeMemoryCell(value, isActive);

		amount--;
	}
	return;
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
		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		DeleteCommentFromCommand(line);

		if (LabelInCommandExist(line) == True)
		{
			found = strtok_s(line, " \t\r", &token);
			found = strtok_s(NULL, " \t\r", &token);
		}
		else
		{
			found = strtok_s(line, " \t\r", &token);
		}

		if (strcmp(found, "DS") == 0)
		{
			amount = GetDSVariableAmount(found, &token);
			AddCellsToMemory(amount, False, 0);
		}
		else
		{
			dcParams = GetDCParameters(found, &token);

			AddCellsToMemory(dcParams->Amount, True, dcParams->Value);
		}
	}
}

Command* MakeCommand(int code, CommandType commandType, int firstRegister, int secondRegister, int targetRegister, int targetDisplacement, int commandDisplacement)
{
	Command* newCommand = (Command*)malloc(sizeof(Command));

	newCommand->Code = code;
	newCommand->commandType = commandType;
	newCommand->FirstRegister = firstRegister;
	newCommand->SecondRegister = secondRegister;
	newCommand->TargetRegister = targetRegister;
	newCommand->TargetDisplacement = targetDisplacement;
	newCommand->CommandDisplacement = commandDisplacement;

	return newCommand;
}

void ResizeCommandsCollection(int capacity)
{
	Command** commands = realloc(CompilerMemory.Commands, sizeof(Command*) * capacity);

	if (commands)
	{
		CompilerMemory.Commands = commands;
		CompilerMemory.CommandsInfo->Capacity = capacity;
	}
}

void AddCommand(int code, CommandType commandType, int firstRegister, int secondRegister, int targetRegister, int targetDisplacement, int commandDisplacement)
{
	if (CompilerMemory.CommandsInfo->Capacity == CompilerMemory.CommandsInfo->Total)
	{
		ResizeCommandsCollection(CompilerMemory.CommandsInfo->Capacity * 2);
	}

	CompilerMemory.Commands[CompilerMemory.CommandsInfo->Total++] = MakeCommand(code, commandType, firstRegister, secondRegister, targetRegister, targetDisplacement, commandDisplacement);
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
	int actualDisplacement = 0;

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

			if (strcmp(found, "KONIEC") == 0)
			{
				AddCommand(KILL, MemoryOnly, 0, 0, 0, 0, GetLabelByName("KONIEC")->Displacement);
				return;
			}

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
			code = GetInstructionCode(found);

			AddCommand(code, Register2Register, r2rParams->FirstRegister, r2rParams->SecondRegister, 0, 0, actualDisplacement);
			actualDisplacement += 2;
			continue;
		}

		charToCompare[0] = *found;
		charToCompare[1] = '\0';
		// jump command
		if (strcmp(charToCompare, "J") == 0)
		{
			moParams = (MOCommandParameters*)GetCommandParameters(MemoryOnly, found, &token);

			code = GetInstructionCode(found);

			AddCommand(code, MemoryOnly, 0, 0, moParams->TargetRegister, moParams->TargetDisplacement, actualDisplacement);
			actualDisplacement += 4;
			continue;
		}

		// register to memory command
		r2mParams = (R2MCommandParameters*)GetCommandParameters(Register2Memory, found, &token);
		code = GetInstructionCode(found);
		AddCommand(code, Register2Memory, r2mParams->Register, 0, r2mParams->TargetRegister, r2mParams->TargetDisplacement, actualDisplacement);
		actualDisplacement += 4;
	}
}

void LoadCommands(char* filename)
{
	FILE* input;

	InitMemory();
	fopen_s(&input, filename, "r");

	CreateProgramMemory(input);

	CreateCommands(input);

	fclose(input);
}

Command* GetCommand(int counter)
{
	return CompilerMemory.Commands[counter];
}

int GetCellValue(int number)
{
	return CompilerMemory.ProgramData[number]->Value;
}

int GetCommandNumberByDisplacement(int displacement)
{
	int i = 0;

	while (1)
	{
		if (GetCommand(i)->CommandDisplacement == displacement)
		{
			return i;
		}
		i++;
	}
}

void SetCellValue(int number, int value)
{

	CompilerMemory.ProgramData[number]->Value = value;
	CompilerMemory.ProgramData[number]->IsActive = True;
}

MemoryCell* GetCell(int number)
{
	return CompilerMemory.ProgramData[number];
}

LoadProgramMemory(FILE* input)
{
	char* line = (char*)malloc(sizeof(char) * MAX_LABEL_SIZE);

	while (fgets(line, MAX_LABEL_SIZE, input) != NULL)
	{
		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		DeleteCommentFromCommand(line);

		if (IsNumber(*line) == True)
		{
			line = DeleteWhitespaces(line);
			AddCellsToMemory(1, True, strtol(line, NULL, 16));
		}
		else
		{
			AddCellsToMemory(1, False, 0);
		}
	}
}

void LoadCommandsFromHex(FILE* input)
{
	char line[MAX_LINE_SIZE];
	Command* command = NULL;
	int displacement = 0;

	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		DeleteCommentFromCommand(line);

		command = GetCommandFromHex(line, &displacement);

		AddCommand(command->Code, command->commandType, command->FirstRegister, command->SecondRegister, command->TargetRegister, command->TargetDisplacement, command->CommandDisplacement);
	}
}

void LoadHexCommands(char* filename)
{
	FILE* input;

	InitMemory();
	fopen_s(&input, filename, "r");

	LoadProgramMemory(input);

	LoadCommandsFromHex(input);

	fclose(input);
}