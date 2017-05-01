/**
* created by Omer Chen
* @since - APR 2017
*/

#pragma once

#include <stdint.h>
#include "Definitions.h"

//	This enum represents all the possible types for log message in the project
enum ELogType
{
	eLogType_Error = 0,
	eLogType_Info,
	eLogType_Warning,
	eLogType_Security,
	eLogType_SIZE
};

//	This enum represents all the possible errors message in the project
enum EErrorMessage
{
	eErrorMessage_NoError = 0,
	eErrorMessage_InvalidParameter,
	eErrorMessage_BufferOverflow,
	eErrorMessage_IntagerOverflow,
	eErrorMessage_NullParameter,
	eErrorMessage_SIZE
};

//	This struct represents a general log message
struct SLogMessage
{
	//	The type of the log message
	ELogType	type;

	//	Description of the log message in null terminated string
	char*		description;

	//	The name of the method where the log was written - null terminated string
	char*		methodName;
};