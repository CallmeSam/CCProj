#ifndef __DQ_GETASSETS_H__
#define __DQ_GETASSETS_H__
#include "cocos2d.h"
#include "AssetsFile.h"
USING_NS_CC;

#define TXURE_DATA(T) GetAssets::getInstance()->getTexture2D(T)
#define UNPACK(T) GetAssets::getInstance()->unPack(T)

struct FileEntry
{
	unsigned int offset;
	unsigned int nameHash;
	unsigned int fileSize;
	unsigned int flag;
};

struct PackageHeader
{
	unsigned int fileEntryOffset;
	int fileAmount;
};

class GetAssets
{
public:
	static GetAssets* m_GetAssets;
	static GetAssets* getInstance()
	{
		if (NULL == m_GetAssets)
		{
			m_GetAssets = new GetAssets();
		}
		return m_GetAssets;
	}
	
	std::vector<FileEntry> _vectorFileEntry;
	FILE* _file;
	bool _isValid;
	std::string _fileName;
	int _size;
	PackageHeader _packageHeader;
	void init(const char* fileName);
	CCTexture2D* getTexture2D(const char* name);
	//std::string* getTexture2D(const char* name);
	AssetsFile* openFile(const char* fileName);
	AssetsFile* openFile(unsigned int hash);
	int read(unsigned char* buff, unsigned int offset, unsigned int len);
	void readFileEntry();
	std::string open(const char* pFileName);
	std::string unPack(const char* name);
};

#endif