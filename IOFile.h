/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Definitions.h"

#define INPUT_PATH		("input.txt")
#define OUTPUT_PATH		("output.txt")

struct TPInput
{
	char names[PLAYERS_AMOUNT][NAME_MAX_SIZE];
};

struct TPOutput
{
	char names[TEAMS_AMOUNT][TEAM_SIZE][NAME_MAX_SIZE];
};

class IOFile
{
public:
	static bool ReadInput(TPInput& o_input);
	static bool WriteOutput(TPOutput& output);
};
