#include "Compilers.h"
#include<stdio.h>
#include"Constant.h"
#include<string.h>
#include"Memory.h"
#include"Labels.h"
#include"Save.h"
#include"HelperStructs.h"

void UpdateSignOfLastOperation(int value)
{
	CompilerMemory.Zero = value == 0 ? True : False;
	CompilerMemory.Negative = value < 0 ? True : False;
	CompilerMemory.Positive = value > 0 ? True : False;
}

void PerformCommand(Command* command)	
{
	int number;

	switch (command->Code)
	{
	case AR:
		CompilerMemory.Registers[command->FirstRegister] += CompilerMemory.Registers[command->SecondRegister];

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case A:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		CompilerMemory.Registers[command->FirstRegister] += GetCellValue(number);

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case SR:
		CompilerMemory.Registers[command->FirstRegister] -= CompilerMemory.Registers[command->SecondRegister];

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case S:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		CompilerMemory.Registers[command->FirstRegister] -= GetCellValue(number);

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case MR:
		CompilerMemory.Registers[command->FirstRegister] *= CompilerMemory.Registers[command->SecondRegister];

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case M:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		CompilerMemory.Registers[command->FirstRegister] *= GetCellValue(number);

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case DR:
		CompilerMemory.Registers[command->FirstRegister] /= CompilerMemory.Registers[command->SecondRegister];

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case D:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		CompilerMemory.Registers[command->FirstRegister] /= GetCellValue(number);

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]);
		break;
	case CR:
		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister] - CompilerMemory.Registers[command->SecondRegister]);
		break;
	case C:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		UpdateSignOfLastOperation(CompilerMemory.Registers[command->FirstRegister]-GetCellValue(number));
		break;
	case J:
		number = command->TargetDisplacement + CompilerMemory.Registers[command->TargetRegister];

		CompilerMemory.ProgramCounter = GetCommandNumberByDisplacement(number);
		break;
	case JZ:
		number = command->TargetDisplacement  + CompilerMemory.Registers[command->TargetRegister] ;

		if (CompilerMemory.Zero == True)
		{
			CompilerMemory.ProgramCounter = GetCommandNumberByDisplacement(number);
		}
		break;
	case JP:
		number = command->TargetDisplacement  + CompilerMemory.Registers[command->TargetRegister] ;

		if (CompilerMemory.Positive == True)
		{
			CompilerMemory.ProgramCounter = GetCommandNumberByDisplacement(number);
		}
		break;
	case JN:
		number = command->TargetDisplacement  + CompilerMemory.Registers[command->TargetRegister] ;

		if (CompilerMemory.Negative == True)
		{
			CompilerMemory.ProgramCounter = GetCommandNumberByDisplacement(number);
		}
		break;
	case L:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		CompilerMemory.Registers[command->FirstRegister] = GetCellValue(number);
		break;
	case LR:
		CompilerMemory.Registers[command->FirstRegister] = CompilerMemory.Registers[command->SecondRegister];
		break;
	case LA:
		CompilerMemory.Registers[command->FirstRegister] = command->TargetDisplacement + CompilerMemory.Registers[command->TargetRegister];
		break;
	case ST:
		number = command->TargetDisplacement / 4 + CompilerMemory.Registers[command->TargetRegister] / 4;

		SetCellValue(number, CompilerMemory.Registers[command->FirstRegister]);
		break;
	case KILL:
		CompilerMemory.ProgramCounter = CompilerMemory.CommandsInfo->Total;
		break;
	}
	return True;
}

void ExecuteCommands()
{
	Command* command = NULL;

	while (CompilerMemory.ProgramCounter != CompilerMemory.CommandsInfo->Total)
	{
		command = GetCommand(CompilerMemory.ProgramCounter);

		CompilerMemory.ProgramCounter++;
		PerformCommand(command);
	}
}

void CompilePsaCode(char* filename)
{
	MakeLabels(filename);
	LoadCommands(filename);

	ExecuteCommands();

	GenerateOutputFile(filename);
}

void CompileMachineCode(char* filename) {}

