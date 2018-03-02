#include "GetAssets.h"

GetAssets* GetAssets::m_GetAssets = NULL;

unsigned int BKDRHash(const char* str)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	int len = strlen(str);
	for (int i = 0; i<len; i++)
	{
		hash = (hash*seed + str[i]) & 0xFFFFFFFF;
	}
	return hash & 0x7FFFFFFF;
}

void GetAssets::init(const char* fileName)
{
	CCFileUtils::sharedFileUtils()->addSearchPath((CCFileUtils::sharedFileUtils()->getWritablePath()).c_str());
	std::string fullPath = open(fileName);
	_file = NULL;
	_isValid = false;
	_fileName = fullPath;
	_file = fopen(fullPath.c_str(), "rb+");

	CCLOG("%s  strPath", fullPath.c_str());

	if (_file == NULL)
	{
		_file = fopen(fullPath.c_str(), "wb+");
		if (_file == NULL) return;
	}

	fseek(_file, 0, SEEK_END);
	_size = ftell(_file);
	fseek(_file, 0, SEEK_SET);

	_isValid = true;

	_packageHeader.fileAmount = 0;
	_packageHeader.fileEntryOffset = sizeof(PackageHeader);

	if (_size >= 8)
	{
		fread(&_packageHeader, 1, sizeof(PackageHeader), _file);

		readFileEntry();
	}
	else
	{
		fwrite(&_packageHeader, 1, sizeof(PackageHeader), _file);
	}
}

std::string GetAssets::open(const char* pFileName)
{
	if (!pFileName)
	{
		return "";
	}

	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	filePath += pFileName;
	FILE *pFp = fopen(filePath.c_str(), "r");

	if (pFp)
	{
		fclose(pFp);
		return filePath.c_str();
	}
	else
	{
		std::string strPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFileName);
		long len = 0;
		unsigned char* data = NULL;
		data = CCFileUtils::sharedFileUtils()->getFileData(strPath.c_str(), "rb", &len);
		std::string destPath = CCFileUtils::sharedFileUtils()->getWritablePath();
		destPath += pFileName;

		FILE *pFpCreate = fopen(destPath.c_str(), "wb");
		fwrite(data, sizeof(char), len, pFpCreate);
		fclose(pFpCreate);
		delete[]data;
		data = NULL;
		return destPath;
	}
}

std::string GetAssets::unPack(const char* pFileName)
{
	AssetsFile* ass = openFile(pFileName);
	unsigned char* buff = (unsigned char*)malloc(ass->getSize());;
	ass->read(buff);
	
	std::string filePath = CCFileUtils::sharedFileUtils()->getWritablePath();
	CCFileUtils::sharedFileUtils()->addSearchPath((CCFileUtils::sharedFileUtils()->getWritablePath()).c_str());
	filePath += pFileName;
	FILE *pFp = fopen(filePath.c_str(), "r");

	if (pFp)
	{
		fclose(pFp);
		return filePath.c_str();
	}
	else
	{
		std::string destPath = CCFileUtils::sharedFileUtils()->getWritablePath();
		destPath += pFileName;

		FILE *pFpCreate = fopen(destPath.c_str(), "wb");
		fwrite(buff, sizeof(char), ass->getSize(), pFpCreate);
		fclose(pFpCreate);
		delete[]buff;
		buff = NULL;
		return destPath;
	}
}

void GetAssets::readFileEntry()
{
	if (!_isValid) return;
	fseek(_file, _packageHeader.fileEntryOffset, SEEK_SET);
	for (int i = 0; i<_packageHeader.fileAmount; i++)
	{
		FileEntry entry;
		fread(&entry, 1, sizeof(FileEntry), _file);
		_vectorFileEntry.push_back(entry);
	}
}

AssetsFile* GetAssets::openFile(const char* fileName)
{
	unsigned int hash = BKDRHash(fileName);

	return openFile(hash);
}

int GetAssets::read(unsigned char* buff, unsigned int offset, unsigned int len)
{
	fseek(_file, offset, SEEK_SET);
	unsigned int r = fread(buff, 1, len, _file);
	return r;
}

AssetsFile* GetAssets::openFile(unsigned int hash)
{
	for (unsigned int i = 0; i<_vectorFileEntry.size(); i++)
	{
		FileEntry& entry = _vectorFileEntry[i];
		if (entry.flag != 2 &&entry.nameHash == hash)
		{
			AssetsFile* file = new AssetsFile(entry.offset, entry.nameHash, entry.fileSize);
			return file;
		}
	}
	return NULL;
}

CCTexture2D* GetAssets::getTexture2D(const char* name)
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	{
		AssetsFile* ass = openFile(name);
		unsigned char* buff = (unsigned char*)malloc(ass->getSize());

		ass->read(buff);
		CCImage* image = new CCImage();
		image->initWithImageData(buff, ass->getSize());
		CCTexture2D* texutre = new CCTexture2D();
		texutre->initWithImage(image);
		return texutre;
	}
	else
	{
// 		CCImage* image = new CCImage();
// 		image->initWithImageFile(name);
// 		CCTexture2D* texutre = new CCTexture2D();
// 		texutre->initWithImage(image);
// 		return texutre;
		AssetsFile* ass = openFile(name);
		unsigned char* buff = (unsigned char*)malloc(ass->getSize());

		ass->read(buff);
		CCImage* image = new CCImage();
		image->initWithImageData(buff, ass->getSize());
		CCTexture2D* texutre = new CCTexture2D();
		texutre->initWithImage(image);
		return texutre;
	}
	
}
