#include"Labels.h"
#include<stdio.h>
#include<string.h>
#include"Constant.h"
#include"HelperStructs.h"
#include"Enums.h"


void InitLabels()
{
	ActualLabels.Labels = (Label**)malloc(INITIAL_LABEL_AMOUNT * sizeof(Label));
	ActualLabels.Capacity = INITIAL_LABEL_AMOUNT;
	ActualLabels.Total = 0;
}

void ResizeActualLabels(int capacity)
{
	Label** labels = realloc(ActualLabels.Labels, capacity);

	if (labels)
	{
		ActualLabels.Labels = labels;
		ActualLabels.Capacity = capacity;
	}

	return;
}

void GetLabelFromCommand(char* line, int* displacement, Section sectionType)
{
	char* helper = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);
	Label* label = NULL;
	char* token = NULL;

	strcpy_s(helper, MAX_LABEL_SIZE, line);

	label = MakeLabel(strtok_s(helper, " \r\t", &token), displacement, sectionType == Data ? 15 : 14);

	AddLabel(label);
	return;
}

void UpdateDisplacement(char* line, int* displacement, Bool labelExist, Section	sectionType)
{
	char* found = NULL;
	char* token = NULL;
	int amount;
	DcParameters* dcParams;
	char* charToCompare = NULL;

	if (sectionType == Data)
	{
		if (labelExist == True)
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

			*displacement += 4 * amount;
		}
		else // it means that command is DC command
		{
			dcParams = GetDCParameters(found, &token);

			*displacement += 4 * (dcParams->Amount);
		}
	}
	else
	{
		if (labelExist == True)
		{
			found = strtok_s(line, " \t\r", &token);

			if (strcmp(found, "KONIEC") == 0)
			{
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

		if (strcmp(charToCompare, "R") == 0)
		{
			*displacement += 2;
		}
		else
		{
			*displacement += 4;
		}
	}
	return;
}

void MakeLabels(char* filename)
{
	// data section
	FILE* input = NULL;

	int actualDisplacement = 0;
	char line[MAX_LINE_SIZE];
	// end of data section

	InitLabels();

	fopen_s(&input, filename, "r");

	// goes through data section to find labels
	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		DeleteCommentFromCommand(line);

		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		if (LabelInCommandExist(line) == True)
		{
			GetLabelFromCommand(line, &actualDisplacement, Data);
			UpdateDisplacement(line, &actualDisplacement, True, Data);
			continue;
		}

		UpdateDisplacement(line, &actualDisplacement, False, Data);

	}
	actualDisplacement = 0;

	// goes through order section to find labels
	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		if (StringIsNullOrEmpty(line) == True)
		{
			break;
		}

		if (LabelInCommandExist(line) == True)
		{
			GetLabelFromCommand(line, &actualDisplacement, Order);
			UpdateDisplacement(line, &actualDisplacement, True, Order);
			continue;
		}
		UpdateDisplacement(line, &actualDisplacement, False, Order);
	}

	fclose(input);
}

Label* MakeLabel(char* labelName, int* displacement, int registerNumber)
{
	Label* newLabel = (Label*)malloc(sizeof(Label));
	newLabel->LabelName = (char*)malloc(sizeof(char) * MAX_LABEL_SIZE);
	strcpy_s(newLabel->LabelName, MAX_LABEL_SIZE, labelName);
	newLabel->Displacement = *displacement;
	newLabel->Register = registerNumber;

	return newLabel;
}

void AddLabel(Label* label)
{
	if (ActualLabels.Total == ActualLabels.Capacity)
	{
		ResizeActualLabels(ActualLabels.Capacity * 2);
	}

	ActualLabels.Labels[ActualLabels.Total++] = label;
}

Label* GetLabelByName(char* name)
{
	int i = 0;

	for (i = 0; i < ActualLabels.Total; ++i)
	{
		if (strcmp(name, (ActualLabels.Labels[i])->LabelName) == 0)
		{
			return ActualLabels.Labels[i];
		}
	}

	return NULL;
}
