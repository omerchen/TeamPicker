#include "DataSetHandler.h"

DataSetHandler::DataSetHandler(char* path): m_isInit(false)
{
	if (Init(path))
	{
		m_isInit = true;
	}
}

bool DataSetHandler::Init(char* path)
{
	if (m_isInit || path == nullptr)
	{
		return false;
	}

	if (m_fileHandler.Init(path, eFileOCMode_Manual))
	{
		m_isInit = true;
	}

	return m_isInit;
}

bool DataSetHandler::IsInit() const
{
	return m_isInit;
}

size_t DataSetHandler::ReadAll(GeneralPlayer**& playersArr)
{
	if (!IsInit() || !m_fileHandler.Seek(0))
	{
		return DATA_SET_HANDLER_ERROR;
	}

	if (!m_fileHandler.Open(eFileMode_Read))
	{
		return DATA_SET_HANDLER_ERROR;
	}

	// Validate the version
	uint8_t data_set_version;

	if (m_fileHandler.Read(&data_set_version, 1) != 1)
	{
		m_fileHandler.Close();
		return DATA_SET_HANDLER_ERROR;
	}

	if (data_set_version != VERSION)
	{
		m_fileHandler.Close();
		return DATA_SET_HANDLER_ERROR;
	}

	// Check the amount of players in the cur data set for allocating enough space
	size_t len;
	if (m_fileHandler.Read((uint8_t*)&len, sizeof(size_t) != sizeof(size_t)))
	{
		m_fileHandler.Close();
		return DATA_SET_HANDLER_ERROR;
	}

	// Allocating space
	playersArr = new GeneralPlayer*[len];

	for (int i = 0; i < len; i++)
	{
		ERole curRole;
		if (m_fileHandler.Read((uint8_t*)&curRole, sizeof(ERole) != sizeof(ERole)))
		{
			m_fileHandler.Close();
			return DATA_SET_HANDLER_ERROR;
		}

		switch (curRole)
		{
			eRole_GK:
			{
				playersArr[i] = (GeneralPlayer*)(new GKPlayer());
				if (m_fileHandler.Read((uint8_t*)(playersArr[i]), sizeof(GKPlayer) != sizeof(GKPlayer)))
				{
					m_fileHandler.Close();
					return DATA_SET_HANDLER_ERROR;
				}
				break;
			}

			eRole_Field:
			{
				playersArr[i] = (GeneralPlayer*)(new FieldPlayer());
				if (m_fileHandler.Read((uint8_t*)(playersArr[i]), sizeof(FieldPlayer) != sizeof(FieldPlayer)))
				{
					m_fileHandler.Close();
					return DATA_SET_HANDLER_ERROR;
				}
				break;
			}

			default:
			{
				for (int j = 0; j < i; j++)
				{
					delete playersArr[j];
				}

				delete[] playersArr;

				m_fileHandler.Close();
				return DATA_SET_HANDLER_ERROR;
			}
		}
	}

	m_fileHandler.Close();

	return len;
}

int8_t DataSetHandler::WriteAll(GeneralPlayer** playersArr, size_t len)
{
	if (playersArr == nullptr || !IsInit() || !m_fileHandler.Seek(0))
	{
		return DATA_SET_HANDLER_ERROR;
	}

	if (!m_fileHandler.Open(eFileMode_Write))
	{
		return DATA_SET_HANDLER_ERROR;
	}

	// write the version
	uint8_t cur_version = VERSION;
	if (!m_fileHandler.Write(&cur_version, 1))
	{
		m_fileHandler.Close();
		return DATA_SET_HANDLER_ERROR;
	}
	
	// write the amount of players
	if (!m_fileHandler.Write((uint8_t*)&len, sizeof(size_t)))
	{
		m_fileHandler.Close();
		return DATA_SET_HANDLER_ERROR;
	}

	for (int i = 0; i < len; i++)
	{
		if (!m_fileHandler.Write((uint8_t*)&(playersArr[i]->basic_info.role), sizeof(ERole)))
		{
			m_fileHandler.Close();
			return DATA_SET_HANDLER_ERROR;
		}
		
		switch (playersArr[i]->basic_info.role)
		{
			case eRole_GK:
			{
				if (!m_fileHandler.Write((uint8_t*)(playersArr[i]), sizeof(GKPlayer)))
				{
					m_fileHandler.Close();
					return DATA_SET_HANDLER_ERROR;
				}
				break;
			}

			case eRole_Field:
			{
				if (!m_fileHandler.Write((uint8_t*)(playersArr[i]), sizeof(FieldPlayer)))
				{
					m_fileHandler.Close();
					return DATA_SET_HANDLER_ERROR;
				}
				break;
			}

			default:
			{
				m_fileHandler.Close();
				return DATA_SET_HANDLER_ERROR;
			}
		}
	}

	m_fileHandler.Close();

	return len;
}