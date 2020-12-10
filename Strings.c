#include<string.h>
#include"Constant.h"


void DeleteCommentFromCommand(char* command)
{
	char* commentPosition = strchr(command, '/');

	if (commentPosition != NULL)
		*commentPosition = '\0';

	return;
}

int StringIsNullOrEmpty(char* string)
{
	char* helper = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	char* check = NULL;
	char* checkToken = NULL;

	strcpy_s(helper, MAX_LINE_SIZE, string);

	check = strtok_s(helper, " \r\t\n", &checkToken);

	if (check == NULL)
	{
		return TRUE;
	}

	return FALSE;
}

int LabelInCommandExist(char* command)
{
	if (command[0] != ' ' && command[0] != '/')
	{
		return TRUE;
	}

	return FALSE;
}