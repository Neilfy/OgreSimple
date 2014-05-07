//---------------------------------------------------------------------------

#ifndef CPictureLoaderH
#define CPictureLoaderH

#include <string>
using namespace std;
//---------------------------------------------------------------------------
#define WIDTHBYTES(i)           (unsigned int)((i+31)/32*4)

class CPictureLoader
{
protected:
	unsigned char *m_puchrDIB24;
	long m_nDIBBufferLength;
	long m_nWidth;
	long m_nHeight;
	unsigned char m_auchrTransColorRGB[3]; //透明色的BGR值
	bool m_bTransparent; //是否有透明色
	string m_strErrMsg;

protected:
	bool createDIB24Buffer(short nWidth, short nHeight);

public:
	CPictureLoader();
	~CPictureLoader();
	const unsigned char *GetDIB24();
	long GetImageHeight();
	long GetImageWidth();
	bool IsTransparent();
	void GetTransparentColor(unsigned char puchrColorRGB[3]);
	string getLastError();

	virtual bool LoadFromStream(const unsigned char* pBuffer, long nSize) = 0;
	
};
#endif
