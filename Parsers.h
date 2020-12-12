
#include"HelperStructs.h"
#include"Enums.h"
#include<string.h>
#include"Constant.h"


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

// gets command parameters from order section
void* GetCommandParameters(CommandType, char*, char**);

int GetInstructionCode(char*);

char* ParseToHex(int);

char* ParseCommandToHex(Command*);