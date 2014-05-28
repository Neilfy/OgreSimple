#ifndef _CTgaLoader_H
#define _CTgaLoader_H
#pragma once
#include "CPictureLoader.h"


#define IMG_OK              0x1
#define IMG_ERR_NO_FILE     0x2
#define IMG_ERR_MEM_FAIL    0x4
#define IMG_ERR_BAD_FORMAT  0x8
#define IMG_ERR_UNSUPPORTED 0x40

class CTGALoader :public CPictureLoader
{
public:
	CTGALoader(void);
	~CTGALoader(void);
	bool LoadFromStream(const unsigned char* pBuffer, long nSize);
	int GetBPP();
	int GetWidth();
	int GetHeight();
	unsigned char* GetImg(void);       // Return a pointer to image data
	unsigned char* GetPalette(void);   // Return a pointer to VGA palette
	bool IsAlpha();
	void GetAlphaList(unsigned char *pAlphaList);
	void clear();
private:
	unsigned char *m_pData;
	unsigned char *m_pPalette;
	long m_nFileSize;
	long m_nDataPointer;
	unsigned char* m_pAlpha;
//	unsigned long ulImgWidth, ulImgHeight;
	unsigned long bufWidth, bufHeight;
	long m_nImageLen;
	char m_iBPP;
	short int m_bEnc;
	long unsigned m_lImageSize;
	unsigned char *GetPixel(int x, int y);

private:
	int ReadHeader();
	int LoadTgaRLEData();
	int LoadTgaPalette() ;
	int LoadRawData();
	void BGRtoRGB() ;
	void FlipImg();
	bool AlphaCreate();
	void AlphaSet(const long x,const long y,const unsigned level);
	unsigned char AlphaGet(const long x,const long y);

};


#endif

