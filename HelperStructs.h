#pragma once

typedef struct DcParameters {
	int Amount;
	int Value;
}DcParameters;

typedef struct
{
	int FirstRegister;
	int SecondRegister;
}R2RCommandParameters;

typedef struct
{
	int Register;
	int TargetRegister;
	int TargetDisplacement;
}R2MCommandParameters;

typedef struct
{
	int TargetRegister;
	int TargetDisplacement;
}MOCommandParameters;