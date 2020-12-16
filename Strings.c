#include<string.h>
#include"Constant.h"
#include"Enums.h"

void DeleteCommentFromCommand(char* command)
{
	char* commentPosition = strchr(command, '/');

	if (commentPosition != NULL)
		*commentPosition = '\0';

	return;
}

Bool StringIsNullOrEmpty(char* string)
{
	char* helper = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	char* check = NULL;
	char* checkToken = NULL;

	strcpy_s(helper, MAX_LINE_SIZE, string);

	check = strtok_s(helper, " \r\t\n", &checkToken);

	if (check == NULL)
	{
		return True;
	}

	return False;
}

Bool LabelInCommandExist(char* command)
{
	if (command[0] != ' ' && command[0] != '/')
	{
		return True;
	}

	return False;
}

char* GenerateOutputPath(char* filename)
{
	char* outputPath = malloc(sizeof(char) * MAX_PATH_SIZE);
	char* helper = malloc(sizeof(char) * MAX_PATH_SIZE);

	strcpy_s(outputPath, MAX_PATH_SIZE, filename);
	helper = strrchr(outputPath, '.');
	*helper = '\0';
	strcat_s(outputPath, MAX_PATH_SIZE, "_out.txt");
	
	return outputPath;
}


char* DeleteWhitespaces(char* string)
{
	char* found = NULL;
	char* token = NULL;
	char* result = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	*result = '\0';

	found = strtok_s(string, " ", &token);

	while (found != NULL)
	{
		strcat_s(result, MAX_LINE_SIZE, found);

		found = strtok_s(NULL, " \n", &token);
	}

	return result;
}