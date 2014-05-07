#ifndef _CJPGLoader_H
#define _CJPGLoader_H

#include "CPictureLoader.h"



class CJPGLoader : public CPictureLoader
{
protected:

private:
	const unsigned char *m_puchrFileData;
	long m_nFileSize;
	long m_nDataPointer;
	unsigned long imgWidth,imgHeight;
	unsigned long bufWidth,bufHeight;
	long m_nImageLen;
	
private:
	void init();
	void clear();
	
public:
	CJPGLoader();
	~CJPGLoader();

	bool LoadFromStream(const unsigned char* pBuffer, long nSize);    	
};

#endif