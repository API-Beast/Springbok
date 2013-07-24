#pragma once
#include <string>

struct FileInfo
{
	FileInfo(const std::string& path);
	operator bool();
	enum EType
	{
		Unknown,
		File,      /**< A regular File. */
		Directory, /**< A Directory. */
		//SymLink,   /**< A symbolic Link. */
		//FIFO,      /**<  */
		//Socket     /**< A Network Socket. */
	};
	bool Exists = false;      /**< Wheter the file or folder exists. */
	EType Type;               /**< The type of the file. */
	int LastModification = 0; /**< Seconds since last modifiation. */
	int Size = 0;             /**< Size of the file in Bytes. 0 for Directories. */
};