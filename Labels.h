#pragma once

typedef struct Label
{
	char* LabelName;
	int Displacement;
	int Register;
} Label;

typedef struct Labels
{
	Label** Labels;
	int Capacity;
	int Total;
}Labels;

Labels ActualLabels;


// make labels from psa code file
// add displacements and creates 
// labels collection
void MakeLabels(char*);

// inits labels collection with default size
void InitLabels();

void AddLabel(Label*);
Label* MakeLabel(char*, int*, int);
Label* GetLabelByName(char*);