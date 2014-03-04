#include "FileInfo.h"
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <ctime>

FileInfo::FileInfo(const std::string& path)
{
	struct stat fileInfo;
	int failed = stat(path.c_str(), &fileInfo);
	Exists = !failed;
	if(Exists)
	{
		Type = File;
		/*if(fileInfo.st_mode & S_IFLNK)
			Type = SymLink;
		if(fileInfo.st_mode & S_IFIFO)
			Type = FIFO;
		if(fileInfo.st_mode & S_IFSOCK)
			Type = Socket;*/
		if(fileInfo.st_mode & S_IFDIR)
			Type = Directory;
		if(fileInfo.st_mode & S_IFREG)
			Type = File;
		
		LastModification = time(NULL) - fileInfo.st_mtime;
		Size = fileInfo.st_size;
	}
}

FileInfo::operator bool()
{
	return Exists;
}
