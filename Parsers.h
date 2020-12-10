#pragma once
#include"HelperStructs.h"

// deletes white characters from already preparsed command
// and returns amount of cells in memory to alloc
// string passed to a function must be a strtok function 
// product to work correctly
int GetDSVariableAmount(char*, char**);

// deletes white characters from already preparsed command
// returns amount and values of cells in memory to alloc
// string passed to a function must be a strtok function 
// product to work correctly
DcParameters* GetDCParameters(char*, char**);