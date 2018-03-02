#ifndef __ASSETSFILE_H__
#define __ASSETSFILE_H__

class AssetsFile
{
public:
	AssetsFile(unsigned int offset, unsigned int nameHash, unsigned int fileSize);
	~AssetsFile();

	int read(unsigned char* buff);
	unsigned int getSize(){return _size;};
	unsigned int getNameHash(){return _nameHash;};

private:
	bool _isCompressed;
	unsigned int _size;
	unsigned int _offset;
	unsigned int _nameHash;
};


#endif
