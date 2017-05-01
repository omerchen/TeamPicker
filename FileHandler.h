/**
* created by Omer Chen
* @since - APR 2017
*/

#pragma once

#include <stdint.h>
#include <stdio.h>
#include "Definitions.h"

// Magic numbers
#define FSEEK_SUCCESS_VALUE			(0)
#define REMOVE_SUCCESS_VALUE		(0)

// this enum indicate the FileHandler object whether open+close the file every start+end of method or wait for manually 
//																			opening+closing of the file by he programmer.
//	@NOTE OC = Open-Close
enum EFileOCMode
{
	eFileOCMode_Auto = 0,
	eFileOCMode_Manual,
	eFileOCMode_SIZE
};

//	this enum is for indicate the mode of using the file
//	@NOTE write will open it as 'ab' mode and read as 'rb' mode
enum EFileMode
{
	eFileMode_Read = 0,
	eFileMode_Write,
	eFileMode_SIZE
};

//	This class epresents a FileHandler class that wrap the file io methods of the standard lib
class FileHandler
{
public:
	// Ctor method
	FileHandler();

	// Dtor method
	~FileHandler();

	/**
	 * This method initializes the FileHandler object
	 *
	 * @param path -			path to the file (null termianted string)
	 * @param ocMode -		the operation mode of opening/closing the file
	 *
	 * @return (bool) - Whether the method success or not
	 *
	 * @note: you can initiate the object only once!
	 */
	bool Init(const char* path, EFileOCMode ocMode);

	/**
	 * This method check if the object already initiate
	 *
	 * @return (bool) - true if it is init, false if not
	 */
	bool IsInit() const;

	/**
	 * This method open the file
	 *
	 * @param fileMode -			the mode to open the file - Write or Read
	 *
	 * @return (bool) - Whether the method success or not
	 *
	 * @note			if the object is init on Auto OCFileMode you CAN'T use this method
	 * @note			you CAN'T open file twice without close it first
	 *
	 * @warning			be careful to use the correct mode before calling to read or write method
	 */
	bool Open(EFileMode fileMode);

	/**
	 * This method close the file
	 *
	 * @eturn (bool) - Whether the method success or not
	 *
	 * @note			if the object is init on Auto OCFileMode you CAN'T use this method
	 * @note			you CAN'T close file that isn't open yet
	 */
	bool Close();

	/**
	 * This method is for writing buffer into end of file
	 *
	 * @param buffer -				buffer of data in bytes to write into the end of the file
	 * @param length -				the length of the buffer (in bytes!)
	 *
	 * @return (bool) - Whether the method success or not
	 *
	 * @note			if the file is in Manual OCFileMode - Open it on WRITE MODE before using this method
	 */
	bool Write(const uint8_t* buffer, uint64_t length);

	/**
	 * This method is for reading buffer from file
	 *
	 * @param o_buffer -				output buffer to put the read data from the file
	 * @param maxLength -			the maximum amount of bytes to read from the file to the output buffer
	 *
	 * @return (uint64_t) - The exact amount of bytes that read from the file
	 *
	 * @note			if the file is in Manual OCFileMode - Open it on READ MODE before using this method
	 * @note			use offset to change the default cursor of the file handler to read from specific offset
	 */
	uint64_t Read(uint8_t* o_buffer, uint64_t maxLength);

	/**
	 * This method is for changing the cursor and the read-offset of the file-handler
	 *
	 * @param index -				the index of the first byte to read next time
	 *
	 * @return (bool) - Whether the method success or not
	 *
	 * @note			if the file is in Manual OCFileMode - you must make sure the file is close after using this
	 *																	method till next time you are using Read Method
	 * @note			the file doesn't need to be open when you using this method
	 */
	bool Seek(uint64_t index);

	/**
	 * This method is for check that the file is exist on the file-system of your os
	 *
	 * @return (bool) - true if the file is exist, false if not
	 */
	bool IsExist() const;

	/**
	 * This mehod is for remove the file from the file-system of your os
	 *
	 * @return (bool) - Whether the process success or not
	 *
	 * @note	the file must be close!! if it's open, the method will fail
	 */
	bool Remove() const; 

	/**
	 * This method indicate if the file is open or not
	 *
	 * @return (bool) - true if the file is open, false if is close
	 */
	bool IsOpen() const;

	/**
	 * This method indicate the current byte ndex to read in the file, the index is of the next byte that will read
	 *
	 * @return (bool) - The index of he next byte to read
	 *
	 * @note	if the object didn't init yet, it returns 0,so first make sure the object is init
	 */
	uint64_t GetIndex() const;

protected:
	/**
	 * This method open the file
	 *
	 * @param fileMode -			the mode to open the file - Write or Read
	 *
	 * @return (bool) - Whether the method success or not
	 *
	 * @note			you CAN'T open file twice without close it first
	 *
	 * @warning			be careful to use the correct mode before calling to read or write method
	 */
	bool SafeOpen(EFileMode fileMode);

	/**
	 * This method close the file
	 *
	 * @eturn (bool) - Whether the method success or not
	 */
	bool SafeClose();

private:
	bool			m_isInit;
	char*			m_path;
	uint64_t		m_cursorIndex;
	bool			m_isOpen;
	EFileOCMode		m_ocMode;
	EFileMode		m_fileMode;
	FILE*			m_file;
};