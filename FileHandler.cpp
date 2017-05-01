#include <string.h>
#include "FileHandler.h"
#include "Definitions.h"

FileHandler::FileHandler() : m_isInit(false), m_path(nullptr), m_cursorIndex(0), m_isOpen(false)
{
	
}

FileHandler::~FileHandler()
{
	// First, close the file f is open
	if (m_isInit && m_isOpen)
	{
		SafeClose();
	}

	// Then, free the path string from heap memory
	if (m_path != nullptr)
	{
		delete[] m_path;
	}

	// Prevent double free of the memory
	m_path = nullptr;
}

bool FileHandler::Init(const char* path, EFileOCMode ocMode)
{
	if (m_isInit  || path == nullptr || ocMode >= eFileOCMode_SIZE)
	{
		return false;
	}

	size_t pathLength = strlen(path);

	m_path = new char[pathLength + 1];

	m_path[pathLength] = NULL_TERMINATOR;

	if (strncpy(m_path, path, STRING_MAX_SIZE) == nullptr)
	{
		return false;
	}

	m_isInit = true;

	return true;
}

bool FileHandler::IsInit() const
{
	return m_isInit;
}

bool FileHandler::Open(EFileMode fileMode)
{
	if (!m_isInit || m_ocMode == eFileOCMode_Auto)
	{
		return false;
	}

	return SafeOpen(fileMode);
}

bool FileHandler::Close()
{
	if (!m_isInit || m_ocMode == eFileOCMode_Auto)
	{
		return false;
	}

	return SafeClose();
}

bool FileHandler::Write(const uint8_t* buffer, uint64_t length)
{
	if (!m_isInit || buffer == nullptr || length == 0)
	{
		return false;
	}

	if (!m_isOpen)
	{
		if (m_ocMode == eFileOCMode_Auto)
		{
			if (!SafeOpen(eFileMode_Write))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool returnValue = (fwrite(buffer, sizeof(uint8_t), length, m_file) == length);

	if (m_ocMode = eFileOCMode_Auto)
	{
		SafeClose();
	}

	return returnValue;
}

uint64_t FileHandler::Read(uint8_t* o_buffer, uint64_t maxLength)
{
	if (!m_isInit || o_buffer == nullptr || maxLength == 0)
	{
		return false;
	}

	if (!m_isOpen)
	{
		if (m_ocMode == eFileOCMode_Auto)
		{
			if (!SafeOpen(eFileMode_Read))
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	uint64_t readBytesAmount = fread(o_buffer, sizeof(uint8_t), maxLength, m_file);

	if (m_ocMode = eFileOCMode_Auto)
	{
		SafeClose();
	}

	return readBytesAmount;
}

bool FileHandler::Seek(uint64_t index)
{
	if (!m_isInit)
	{
		return false;
	}

	m_cursorIndex = index;

	return true;
}

bool FileHandler::IsExist() const
{
	if (!m_isInit)
	{
		return false;
	}

	FILE* tempFile;

	if ((tempFile = fopen(m_path, "rb")))
	{
		fclose(tempFile);
		return true;
	}

	return false;
}

bool FileHandler::Remove() const
{
	if (!m_isInit || m_isOpen)
	{
		return false;
	}

	return (remove(m_path) == REMOVE_SUCCESS_VALUE);
}

bool FileHandler::SafeOpen(EFileMode fileMode)
{
	if (!m_isInit || m_isOpen)
	{
		return false;
	}

	switch (fileMode)
	{
		eFileMode_Read:
		{
			m_file = fopen(m_path, "rb");
			break;
		}
		eFileMode_Write:
		{
			m_file = fopen(m_path, "ab");
			break;
		}
		default:
		{
			return false;
		}
	}

	if (m_file == nullptr)
	{
		return false;
	}

	m_isOpen = true;

	if (fileMode == eFileMode_Read)
	{
		if (fseek(m_file, m_cursorIndex, SEEK_SET) != FSEEK_SUCCESS_VALUE)
		{
			SafeClose();
			return false;
		}
	}

	return true;
}

bool FileHandler::SafeClose()
{
	if (!m_isInit || !m_isOpen)
	{
		return false;
	}

	fclose(m_file);
	m_isOpen = false;

	return true;
}

bool FileHandler::IsOpen() const
{
	return (m_isInit && m_isOpen);
}

uint64_t FileHandler::GetIndex() const
{
	if (!m_isInit)
	{
		return 0;
	}

	return m_cursorIndex;
}