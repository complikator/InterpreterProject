#include"Parsers.h"
#include"Constant.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"HelperStructs.h"
#include"Validation.h"
#include"Labels.h"

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
		r2mParams->TargetDisplacement = atoi(found);
		found = strtok_s(NULL, "()", token);
		r2mParams->TargetRegister = atoi(found);
		return r2mParams;

	case MemoryOnly:
		if (IsNumber(*result) == False)
		{
			label = GetLabelByName(result);

			moParams->TargetDisplacement = label->Displacement;
			moParams->TargetRegister = label->Register;

			return moParams;
		}
		found = strtok_s(result, "()", token);
		moParams->TargetDisplacement = atoi(found);
		found - strtok_s(NULL, "()", token);
		moParams->TargetRegister = atoi(found);
		return moParams;

	}
}