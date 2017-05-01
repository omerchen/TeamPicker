/**
* created by Omer Chen
* @since - APR 2017
*/

#pragma once

#include "FileLogger.h"

FileLogger::FileLogger() : m_isInit(false)
{

}

FileLogger::~FileLogger()
{

}

bool FileLogger::Init(const char* path)
{
	if (m_isInit)
	{
		return false;
	}

	if (!m_fileHandler.IsInit())
	{
		if (m_fileHandler.Init(path, eFileOCMode_Auto))
		{
			m_isInit = true;
		}
	}
	
	return m_isInit;
}

bool FileLogger::Write(SLogMessage& message)
{
	if (!m_isInit)
	{
		return false;
	}

	switch (message.type)
	{
			case eLogType_Error:
			{
				char typeName[] = "ERROR:\n\t";
				if (!m_fileHandler.Write((uint8_t*)typeName, strlen(typeName)))
				{
					return false;
				}

				break;
			}

			case eLogType_Info:
			{
				char typeName[] = "Info:\n\t";
				if (!m_fileHandler.Write((uint8_t*)typeName, strlen(typeName)))
				{
					return false;
				}

				break;
			}

			case eLogType_Security:
			{
				char typeName[] = "Security:\n\t";
				if (!m_fileHandler.Write((uint8_t*)typeName, strlen(typeName)))
				{
					return false;
				}

				break;
			}

			case eLogType_Warning:
			{
				char typeName[] = "Warning:\n\t";
				if (!m_fileHandler.Write((uint8_t*)typeName, strlen(typeName)))
				{
					return false;
				}

				break;
			}

			default:
			{
				return false;
			}
	}

	if (!m_fileHandler.Write((uint8_t*)message.description, strlen(message.description)))
	{
		return false;
	}

	if (!m_fileHandler.Write((uint8_t*)("\n\t* method: "), 12))
	{
		return false;
	}

	if (!m_fileHandler.Write((uint8_t*)message.methodName, strlen(message.methodName)))
	{
		return false;
	}

	if (!m_fileHandler.Write((uint8_t*)("\n"), 1))
	{
		return false;
	}

	return true;
}

bool FileLogger::Write(ELogType type, char* description, char* methodName)
{
	SLogMessage logMessage;
	logMessage.description = description;
	logMessage.methodName = methodName;
	logMessage.type = type;


	return Write(logMessage);
}

bool FileLogger::Write(EErrorMessage error, char* methodName)
{
	SLogMessage logMessage;
	logMessage.methodName = methodName;
	logMessage.type = eLogType_Error;

	char description[STRING_MAX_SIZE] = {NULL_TERMINATOR};
	switch (error)
	{
		case eErrorMessage_BufferOverflow:
		{
			if (strcpy(description, "Buffer Overflow!") == nullptr)
			{
				return false;
			}

			break;
		}

		case eErrorMessage_IntagerOverflow:
		{
			if (strcpy(description, "Intager Overflow!") == nullptr)
			{
				return false;
			}

			break;
		}

		case eErrorMessage_InvalidParameter:
		{
			if (strcpy(description, "Invalid Parameter!") == nullptr)
			{
				return false;
			}

			break;
		}

		case eErrorMessage_NullParameter:
		{
			if (strcpy(description, "Null Parameter!") == nullptr)
			{
				return false;
			}

			break;
		}

		case eErrorMessage_NoError:
		{
			return false;
		}

		default:
		{
			return false;
		}
	}

	logMessage.description = description;

	return Write(logMessage);
}
