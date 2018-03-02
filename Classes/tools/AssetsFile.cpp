#include "AssetsFile.h"
#include "GetAssets.h"

AssetsFile::AssetsFile(unsigned int offset, unsigned int nameHash, unsigned int fileSize)
{
	_offset = offset;
	_nameHash = nameHash;
	_size = fileSize;
}

AssetsFile::~AssetsFile()
{

}

int AssetsFile::read(unsigned char* buff)
{
	return GetAssets::getInstance()->read(buff, _offset, _size);
}
