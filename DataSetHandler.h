/**
* created by Omer Chen
* @since - MAY 2017
*/

#pragma once

#include <stddef.h>
#include <string.h>
#include "Definitions.h"
#include "FileHandler.h"
#include "SPlayer.h"

// Magic Numbers
#define DATA_SET_HANDLER_ERROR		(-1)


// Useful Macros
#define FREE_PLAYERS_ARR(arr, len)		{for(int i=0;i<len;i++){delete arr[i];}delete[] arr;}

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

	int64_t ReadAll(GeneralPlayer**& playersArr);

	int64_t WriteAll(GeneralPlayer** playersArr, int64_t len);

	int64_t AppendPlayer(GeneralPlayer* player);
	

private:
	bool m_isInit;
	FileHandler m_fileHandler;
	
};