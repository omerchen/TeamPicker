/**
* created by Omer Chen
* @since - APR 2017
*/

#pragma once

#include "SLogMessage.h"

//	This interface represents a generic logger class
class ILogger
{
public:
	/**
	 * This method is for writing log message
	 *
	 * @param message -			log message object
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	virtual bool Write(SLogMessage& message) = 0;

	/**
	 * This method is for writing log message
	 *
	 * @param type -				the type of the message
	 * @param description -		description of the log message
	 * @param methodName -		the name of the method that the log was written
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	virtual bool Write(ELogType type, char* description, char* methodName) = 0;

	/**
	 * This method is for writing log message
	 *
	 * @param error -			the specific error that was found
	 * @param methodName -		the name of the method that the log was written
	 *
	 * @return (bool) - Whether the method was done successfully or not
	 */
	virtual bool Write(EErrorMessage error, char* methodName) = 0;
};
