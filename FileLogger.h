/**
* created by Omer Chen
* @since - APR 2017
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SLogMessage.h"
#include "ILogger.h"
#include "FileHandler.h"

//	This class represents a file logger class
class	FileLogger : 
	public ILogger
{
public:
	FileLogger();

	~FileLogger();

	/**
	 * This method init the object
	 *
	 * @param path -				The path to the file to write the log into it
	 *
	 * return (bool) - Whether the method success or not
	 */
	bool Init(const char* path);

	/**
	 * This method is for writing log message
	 *
	 * @param message -			log message object
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	bool Write(SLogMessage& message);

	/**
	 * This method is for writing log message
	 *
	 * @param type -				the type of the message
	 * @param description -		description of the log message
	 * @param methodName -		the name of the method that the log was written
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	bool Write(ELogType type, char* description, char* methodName);

	/**
	 * This method is for writing log message
	 *
	 * @param error -			the specific error that was found
	 * @param methodName -		the name of the method that the log was written
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	bool Write(EErrorMessage error, char* methodName);

private:
	bool			m_isInit;
	FileHandler		m_fileHandler;
};
