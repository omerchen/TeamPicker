#include "IOFile.h"

bool IOFile::ReadInput(TPInput& o_input)
{
	FILE* input_file = fopen(INPUT_PATH, "rb");

	if (input_file == nullptr)
	{
		return false;
	}

	for (int i = 0; i < PLAYERS_AMOUNT; i++)
	{
		int curIndex = 0;
		char curChar = getc(input_file);

		while (curChar != '\n' && curChar != '\r' && curChar != EOF)
		{
			if (curIndex < NAME_MAX_SIZE)
			{
				o_input.names[i][curIndex] = curChar;
			}

			curIndex++;
			curChar = getc(input_file);
		}

		o_input.names[i][curIndex] = NULL_TERMINATOR;
		
		do
		{
			curChar = getc(input_file);
		} while (curChar == '\n' || curChar == '\r');

		fseek(input_file, -1, SEEK_CUR);
	}

	return true;
}

bool IOFile::WriteOutput(TPOutput& output)
{
	return false;
}