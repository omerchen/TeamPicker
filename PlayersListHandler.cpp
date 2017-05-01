#include "PlayersListHandler.h"

bool PlayersListHandler::LoadDataSet(GeneralPlayer** ds, uint32_t size)
{
	if (ds == nullptr)
	{
		return false;
	}

	m_ds = ds;
	m_size = size;

	return true;
}

bool PlayersListHandler::FillListByNames(char* names[NAME_MAX_SIZE], GeneralPlayer** o_list, size_t size)
{
	if (m_ds == nullptr || m_size == PLAYERS_LIST_HANDLER_ERROR)
	{
		return false;
	}

	if (m_size < size || names == nullptr || o_list == nullptr)
	{
		return false;
	}

	for (int i = 0; i < size; i++)
	{
		bool name_found = false;

		for (int j = 0; j < m_size; j++)
		{
			if (strcmp(m_ds[j]->basic_info.name, names[i]) == 0)
			{
				o_list[i] = m_ds[j];
				name_found = true;
				break;
			}
		}

		if (!name_found)
		{
			return false;
		}
	}

	return true;
}