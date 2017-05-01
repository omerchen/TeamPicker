/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include "Definitions.h"
#include "FileHandler.h"
#include "SPlayer.h"

// Magic Numbers
#define DATA_SET_HANDLER_ERROR		(-1)

/**
 * This class is to set/get/update the DataSet of vinter
 */
class DataSetHandler
{
public:
	DataSetHandler() : m_isInit(false){}

	DataSetHandler(char* path);

	bool Init(char* path);

	bool IsInit() const;

	size_t ReadAll(GeneralPlayer**& playersArr);

	int8_t WriteAll(GeneralPlayer** playersArr, size_t len);

private:
	bool m_isInit;
	FileHandler m_fileHandler;
	
};