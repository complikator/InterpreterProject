#include"Save.h"
#include<stdio.h>
#include"Memory.h"
#include"Parsers.h"
#include"Strings.h"
#include<stdlib.h>
#include<share.h>

void WriteCellToFile(char* string, FILE* file)
{
	int i = 0;
	char charToWrite[2];

	for (i = 1; i <= 8; ++i)
	{
		charToWrite[0] = string[i - 1];
		charToWrite[1] = '\0';

		fputs(charToWrite, file);

		if (i % 2 == 0)
		{
			fputs(" ", file);
		}
	}
	fputs("\n", file);
}

void WriteCommandToFile(char* string, CommandType type, FILE* file)
{
	int i = 0;
	char charToWrite[2];
	int limit = type == Register2Register ? 4 : 8;

	for (i = 1; i <= limit; ++i)
	{
		charToWrite[0] = string[i - 1];
		charToWrite[1] = '\0';

		fputs(charToWrite, file);
		if (i % 2 == 0)
		{
			fputs(" ", file);
		}
	}
	fputs("\n", file);

}

void SaveDataSection(FILE* output)
{
	int i = 0;
	MemoryCell* cell = NULL;
	char* line = NULL;

	for (i = 0; i < CompilerMemory.DataSectionInfo->Total; ++i)
	{
		cell = GetCell(i);

		if (cell->IsActive == True)
		{
			line = ParseToHex(cell->Value);

			WriteCellToFile(line, output);
		}
		else
		{
			line = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
			line = "~~~~~~~~";

			WriteCellToFile(line, output);
		}
	}
	fputs("\n", output);
}

void SaveCommandSection(FILE* output)
{
	int i = 0;
	Command* command = NULL;
	char* line = NULL;

	for (i = 0; i < CompilerMemory.CommandsInfo->Total; ++i)
	{
		command = GetCommand(i);
		line = ParseCommandToHex(command);
		WriteCommandToFile(line, command->commandType, output);
	}
}

void GenerateOutputFile(char* filename)
{
	char* outputPath = NULL;
	FILE* output = NULL;
	errno_t err = NULL;

	outputPath = GenerateOutputPath(filename);

	err = fopen_s(&output, outputPath, "w");
	//output = _fsopen("example_input_out.txt", "wt", _SH_DENYWR);

	SaveDataSection(output);

	SaveCommandSection(output);
	fclose(output);

}