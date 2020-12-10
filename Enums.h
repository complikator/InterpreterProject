#pragma once

typedef enum 
{
	Data,
	Order
}Section;

typedef enum
{
	True,
	False
}Bool;

typedef enum
{
	Register2Register,
	Register2Memory,
	MemoryOnly
}CommandType;