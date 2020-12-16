#include"Parsers.h"
#include"Constant.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"HelperStructs.h"
#include"Validation.h"
#include"Labels.h"

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

int GetDSVariableAmount(char* preparsedCommand, char** token)
{
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

	preparsedCommand = strtok_s(NULL, " \r\t\n*INTEGER", token);

	*result = '\0';
	// deletes white characters and INTEGER word
	// from command
	while (preparsedCommand != NULL)
	{
		strcat_s(result, MAX_LINE_SIZE, preparsedCommand);

		preparsedCommand = strtok_s(NULL, " \r\t\n*INTEGER", token);
	}

	if (strcmp(result, "") == 0)
	{
		return 1;
	}

	return atoi(result);
}

DcParameters* GetDCParameters(char* preparsedCommand, char** token)
{
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	int amount;
	int value;
	DcParameters* dcParams = NULL;

	preparsedCommand = strtok_s(NULL, " \r\t\n", token);

	*result = '\0';
	while (preparsedCommand != NULL)
	{
		strcat_s(result, MAX_LINE_SIZE, preparsedCommand);

		preparsedCommand = strtok_s(NULL, " \r\t\n", token);
	}

	// amount of cells to alloc is 0
	if (result[0] == 'I')
	{
		preparsedCommand = strtok_s(result, "INTEGER()", token);

		value = atoi(preparsedCommand);

		dcParams = (DcParameters*)malloc(sizeof(DcParameters));

		dcParams->Amount = 1;
		dcParams->Value = value;

		return dcParams;
	}
	else
	{
		preparsedCommand = strtok_s(result, "*", token);

		amount = atoi(preparsedCommand);

		preparsedCommand = strtok_s(NULL, "INTEGER()", token);

		value = atoi(preparsedCommand);

		dcParams = (DcParameters*)malloc(sizeof(DcParameters));

		dcParams->Amount = amount;
		dcParams->Value = value;

		return dcParams;
	}
}

void* GetCommandParameters(CommandType type, char* found, char** token)
{
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	R2RCommandParameters* r2rParams = NULL;
	R2MCommandParameters* r2mParams = NULL;
	MOCommandParameters* moParams = NULL;
	Label* label = NULL;

	*result = '\0';
	found = strtok_s(NULL, " \r\t\n", token);

	while (found != NULL)
	{
		strcat_s(result, MAX_LINE_SIZE, found);

		found = strtok_s(NULL, " \r\t\n", token);
	}
	switch (type)
	{
	case Register2Register:
		r2rParams = (R2RCommandParameters*)malloc(sizeof(R2RCommandParameters));
		found = strtok_s(result, ",", token);
		r2rParams->FirstRegister = atoi(found);
		found = strtok_s(NULL, " \r\t\n", token);
		r2rParams->SecondRegister = atoi(found);
		return r2rParams;

	case Register2Memory:
		found = strtok_s(result, ",", token);
		r2mParams = (R2MCommandParameters*)malloc(sizeof(R2MCommandParameters));
		r2mParams->Register = atoi(found);

		found = strtok_s(NULL, "()", token);

		if (IsNumber(*found) == True)
		{
			r2mParams->TargetDisplacement = atoi(found);
			found = strtok_s(NULL, "()", token);
			r2mParams->TargetRegister = atoi(found);
			return r2mParams;
		}
		else
		{
			label = GetLabelByName(found);

			r2mParams->TargetDisplacement = label->Displacement;
			r2mParams->TargetRegister = label->Register;

			return r2mParams;
		}

	case MemoryOnly:
		moParams = (MOCommandParameters*)malloc(sizeof(MOCommandParameters));
		if (IsNumber(*result) == False)
		{
			label = GetLabelByName(result);

			moParams->TargetDisplacement = label->Displacement;
			moParams->TargetRegister = label->Register;

			return moParams;
		}
		found = strtok_s(result, "()", token);
		moParams->TargetDisplacement = atoi(found);
		found = strtok_s(NULL, "()", token);
		moParams->TargetRegister = atoi(found);
		return moParams;

	}
}

char* ParseToHex(int value)
{
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

	sprintf_s(result, MAX_LINE_SIZE, "%08X", value);

	return result;
}

char* ParseCommandToHex(Command* command)
{
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	char* helper = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	*result = '\0';
	sprintf_s(helper, MAX_LINE_SIZE, "%02X", command->Code);
	strcat_s(result, MAX_LINE_SIZE, helper);

	if (command->commandType == Register2Register)
	{
		sprintf_s(helper, MAX_LINE_SIZE, "%X", command->FirstRegister);
		strcat_s(result, MAX_LINE_SIZE, helper);

		sprintf_s(helper, MAX_LINE_SIZE, "%X", command->SecondRegister);
		strcat_s(result, MAX_LINE_SIZE, helper);

		return result;
	}
	else
	{
		sprintf_s(helper, MAX_LINE_SIZE, "%X", command->FirstRegister);
		strcat_s(result, MAX_LINE_SIZE, helper);

		sprintf_s(helper, MAX_LINE_SIZE, "%X", command->TargetRegister);
		strcat_s(result, MAX_LINE_SIZE, helper);

		sprintf_s(helper, MAX_LINE_SIZE, "%04X", command->TargetDisplacement);
		strcat_s(result, MAX_LINE_SIZE, helper);

		return result;
	}

}

Command* GetCommandFromHex(char* string, int* displacement)
{
	char* found = NULL;
	char* token = NULL;
	Command* command = (Command*)malloc(sizeof(Command));
	int helper;
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	*result = '\0';

	found = strtok_s(string, " \n", &token);
	command->Code = strtol(found, NULL, 16);

	found = strtok_s(NULL, " \n", &token);
	helper = strtol(found, NULL, 16);
	command->FirstRegister = (helper>>4);
	helper %= 16;
	found = strtok_s(NULL, " \n", &token);

	if (found == NULL)
	{
		command->SecondRegister = helper;
		command->commandType = Register2Register;
		*displacement += 2;
		return command;
	}
	
	command->TargetRegister = helper;
	strcat_s(result, MAX_LINE_SIZE, found);
	found = strtok_s(NULL, " \n", &token);
	strcat_s(result, MAX_LINE_SIZE, found);

	command->TargetDisplacement = strtol(result, NULL, 16);
	command->CommandDisplacement = *displacement;

	command->commandType = command->FirstRegister > 0 ? Register2Memory : MemoryOnly;
	*displacement += 4;
	return command;
}