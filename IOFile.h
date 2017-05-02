/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include "Definitions.h"

#define INPUT_PATH		("input.txt")
#define OUTPUT_PATH		("output.txt")

struct TPInput
{
	char names[NAME_MAX_SIZE][PLAYERS_AMOUNT];
};

struct TPOutput
{
	char names[NAME_MAX_SIZE][TEAM_SIZE][TEAMS_AMOUNT];
};

class IOFile
{
public:
	static bool ReadInput(TPInput& o_input);
	static bool WriteOutput(TPOutput& output);
};
