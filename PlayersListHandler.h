/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include <string.h>
#include "Definitions.h"
#include "SPlayer.h"

// Magic Numbers
#define PLAYERS_LIST_HANDLER_ERROR		(-1)

class PlayersListHandler
{
public:
	PlayersListHandler() : m_ds(nullptr), m_size(PLAYERS_LIST_HANDLER_ERROR){}

	void Reset() { m_ds = nullptr; m_size = PLAYERS_LIST_HANDLER_ERROR; }

	bool LoadDataSet(GeneralPlayer** ds, uint32_t size);

	bool FillListByNames(char* names[NAME_MAX_SIZE], GeneralPlayer** o_list, size_t size);

private:
	GeneralPlayer** m_ds;
	int64_t m_size;
};