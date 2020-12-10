#include"Parsers.h"
#include"Constant.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"HelperStructs.h"

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