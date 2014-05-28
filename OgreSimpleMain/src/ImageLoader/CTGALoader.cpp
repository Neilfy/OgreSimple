#include "CTGALoader.h"
#include "string.h"
#include "stdlib.h"
CTGALoader::CTGALoader(void)
{
	m_pAlpha = 0;
}

CTGALoader::~CTGALoader(void)
{
}

bool CTGALoader::LoadFromStream(const unsigned char* pBuffer, long nSize)
{
	m_pData = new unsigned char[nSize];
	memcpy(m_pData,pBuffer,nSize);
	int iRet = ReadHeader();
	if(iRet!=IMG_OK)
		return false;

	switch(m_bEnc)
	{
	case 1: // Raw Indexed
		{
			// Check filesize against header values
			if((m_lImageSize+18+m_pData[0]+768)>nSize)
				return false;

			// Double check image type field
			if(m_pData[1]!=1)
				return false;

			// Load image data
			iRet=LoadRawData();
			if(iRet!=IMG_OK)
				return false;

			// Load palette
			iRet=LoadTgaPalette();
			if(iRet!=IMG_OK)
				return false;

			break;
		}

	case 2: // Raw RGB
		{
			// Check filesize against header values
			if((m_lImageSize+18+m_pData[0])>nSize)
				return false;

			// Double check image type field
			if(m_pData[1]!=0)
				return false;

			// Load image data
			iRet=LoadRawData();
			if(iRet!=IMG_OK)
				return false;

		//	BGRtoRGB(); // Convert to RGB
			break;
		}

	case 9: // RLE Indexed
		{
			// Double check image type field
			if(m_pData[1]!=1)
				return false;

			// Load image data
			iRet=LoadTgaRLEData();
			if(iRet!=IMG_OK)
				return false;

			// Load palette
			iRet=LoadTgaPalette();
			if(iRet!=IMG_OK)
				return false;

			break;
		}

	case 10: // RLE RGB
		{
			// Double check image type field
			if(m_pData[1]!=0)
				return false;

			// Load image data
			iRet=LoadTgaRLEData();
			if(iRet!=IMG_OK)
				return false;

			BGRtoRGB(); // Convert to RGB
			break;
		}

	default:
		return false;
	}

	// Check flip bit
	//if((m_pData[17] & 0x20)==0) 
	//	FlipImg();

	// Release file memory
	delete [] m_pData;
	m_pData=NULL;
	
	return true;
	
}

int CTGALoader::ReadHeader() // Examine the header and populate our class attributes
{
	short ColMapStart,ColMapLen;
	short x1,y1,x2,y2;

	if(m_pData==NULL)
		return IMG_ERR_NO_FILE;

	if(m_pData[1]>1)    // 0 (RGB) and 1 (Indexed) are the only types we know about
		return IMG_ERR_UNSUPPORTED;

	m_bEnc=m_pData[2];     // Encoding flag  1 = Raw indexed image
	//                2 = Raw RGB
	//                3 = Raw greyscale
	//                9 = RLE indexed
	//               10 = RLE RGB
	//               11 = RLE greyscale
	//               32 & 33 Other compression, indexed

	if(m_bEnc>11)       // We don't want 32 or 33
		return IMG_ERR_UNSUPPORTED;


	// Get palette info
	memcpy(&ColMapStart,&m_pData[3],2);
	memcpy(&ColMapLen,&m_pData[5],2);

	// Reject indexed images if not a VGA palette (256 entries with 24 bits per entry)
	if(m_pData[1]==1) // Indexed
	{
		if(ColMapStart!=0 || ColMapLen!=256 || m_pData[7]!=24)
			return IMG_ERR_UNSUPPORTED;
	}

	// Get image window and produce width & height values
	memcpy(&x1,&m_pData[8],2);
	memcpy(&y1,&m_pData[10],2);
	memcpy(&x2,&m_pData[12],2);
	memcpy(&y2,&m_pData[14],2);

	m_nWidth=(x2-x1);
	m_nHeight=(y2-y1);

	if(m_nWidth<1 || m_nHeight<1)
		return IMG_ERR_BAD_FORMAT;

	// Bits per Pixel
	m_iBPP=m_pData[16];

	// Check flip / interleave byte
	if(m_pData[17]>32) // Interleaved data
		return IMG_ERR_UNSUPPORTED;

	// Calculate image size
	m_lImageSize=(m_nWidth * m_nHeight * (m_iBPP/8));

	return IMG_OK;
}


int CTGALoader::LoadRawData() // Load uncompressed image data
{
	short iOffset;

//	if(m_puchrDIB24 != NULL ) // Clear old data if present
//		delete [] m_puchrDIB24;
	m_puchrDIB24=new unsigned char[m_lImageSize];

	if(m_puchrDIB24==NULL)
		return IMG_ERR_MEM_FAIL;

	iOffset=m_pData[0]+18; // Add header to ident field size
	if(m_puchrDIB24[1]==1) // Indexed images
		iOffset+=768;  // Add palette offset

	memcpy(m_puchrDIB24,&m_pData[iOffset],m_lImageSize);

	return IMG_OK;
}


int CTGALoader::LoadTgaRLEData() // Load RLE compressed image data
{
	short iOffset,iPixelSize;
	unsigned char *pCur;
	unsigned long Index=0;
	unsigned char bLength,bLoop;

	// Calculate offset to image data
	iOffset=m_pData[0]+18;

	// Add palette offset for indexed images
	if(m_pData[1]==1)
		iOffset+=768; 

	// Get pixel size in bytes
	iPixelSize=m_iBPP/8;

	// Set our pointer to the beginning of the image data
	pCur=&m_pData[iOffset];

	// Allocate space for the image data
	if(m_puchrDIB24!=NULL)
		delete [] m_puchrDIB24;

	m_puchrDIB24=new unsigned char[m_lImageSize];

	if(m_puchrDIB24==NULL)
		return IMG_ERR_MEM_FAIL;

	// Decode
	while(Index<m_lImageSize) 
	{
		if(*pCur & 0x80) // Run length chunk (High bit = 1)
		{
			bLength=*pCur-127; // Get run length
			pCur++;            // Move to pixel data  

			// Repeat the next pixel bLength times
			for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize)
				memcpy(&m_puchrDIB24[Index],pCur,iPixelSize);

			pCur+=iPixelSize; // Move to the next descriptor chunk
		}
		else // Raw chunk
		{
			bLength=*pCur+1; // Get run length
			pCur++;          // Move to pixel data

			// Write the next bLength pixels directly
			for(bLoop=0;bLoop!=bLength;++bLoop,Index+=iPixelSize,pCur+=iPixelSize)
				memcpy(&m_puchrDIB24[Index],pCur,iPixelSize);
		}
	}

	return IMG_OK;
}


int CTGALoader::LoadTgaPalette() // Load a 256 color palette
{
	unsigned char bTemp;
	short iIndex,iPalPtr;

	// Delete old palette if present
	if(m_pPalette)
	{
		delete [] m_pPalette;
		m_pPalette=NULL;
	}

	// Create space for new palette
	m_pPalette=new unsigned char[768];

	if(m_pPalette==NULL)
		return IMG_ERR_MEM_FAIL;

	// VGA palette is the 768 bytes following the header
	memcpy(m_pPalette,&m_pData[m_pData[0]+18],768);

	// Palette entries are BGR ordered so we have to convert to RGB
	for(iIndex=0,iPalPtr=0;iIndex!=256;++iIndex,iPalPtr+=3)
	{
		bTemp=m_pPalette[iPalPtr];               // Get Blue value
		m_pPalette[iPalPtr]=m_pPalette[iPalPtr+2]; // Copy Red to Blue
		m_pPalette[iPalPtr+2]=bTemp;             // Replace Blue at the end
	}

	return IMG_OK;
}


void CTGALoader::BGRtoRGB() // Convert BGR to RGB (or back again)
{
	unsigned long Index,nPixels;
	unsigned char *bCur;
	unsigned char bTemp;
	short iPixelSize;

	// Set ptr to start of image
	bCur=m_puchrDIB24;

	// Calc number of pixels
	nPixels=m_nWidth*m_nHeight;

	// Get pixel size in bytes
	iPixelSize=m_iBPP/8;

	for(Index=0;Index!=nPixels;Index++)  // For each pixel
	{
		bTemp=*bCur;      // Get Blue value
		*bCur=*(bCur+2);  // Swap red value into first position
		*(bCur+2)=bTemp;  // Write back blue to last position

		bCur+=iPixelSize; // Jump to next pixel
	}
	return;
}

void CTGALoader::FlipImg() // Flips the image vertically (Why store images upside down?)
{
	unsigned char bTemp;
	unsigned char *pLine1, *pLine2;
	int iLineLen,iIndex;

	iLineLen=m_nWidth*(m_iBPP/8);
	pLine1=m_puchrDIB24;
	pLine2=&m_puchrDIB24[iLineLen * (m_nHeight - 1)];

	for( ;pLine1<pLine2;pLine2-=(iLineLen*2))
	{
		for(iIndex=0;iIndex!=iLineLen;pLine1++,pLine2++,iIndex++)
		{
			bTemp=*pLine1;
			*pLine1=*pLine2;
			*pLine2=bTemp;       
		}
	} 

	unsigned char *data;
	data = m_puchrDIB24;
	return;
}


bool CTGALoader::IsAlpha()
{
	return m_pAlpha == NULL?false:true;
}

void CTGALoader::GetAlphaList(unsigned char *pAlphaList)
{
	unsigned char * IsOK;
	IsOK = m_pAlpha;
	if(m_pAlpha)
	{
		memcpy(pAlphaList,m_pAlpha,m_nWidth * m_nHeight);
	}
}

bool CTGALoader::AlphaCreate()
{
	if (m_pAlpha==NULL) {
		m_pAlpha = (unsigned char*)malloc(m_nWidth * m_nHeight);
		if (m_pAlpha) memset(m_pAlpha,255,m_nWidth * m_nHeight);
	}
	return (m_pAlpha!=0);
}

////////////////////////////////////////////////////////////////////////////////
/**
 * Sets the alpha level for a single pixel 
 */
void CTGALoader::AlphaSet(const long x,const long y,const unsigned level)
{
	if (m_pAlpha) m_pAlpha[x+y*m_nWidth]=level;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * Gets the alpha level for a single pixel 
 */
unsigned char CTGALoader::AlphaGet(const long x,const long y)
{
	if (m_pAlpha) return m_pAlpha[x+y*m_nWidth];
	return 0;
}

int CTGALoader::GetBPP() 
{
	return m_iBPP;
}

void CTGALoader::clear()
{
	if(m_pAlpha)
		free(m_pAlpha);
	m_pAlpha = NULL;
}
int CTGALoader::GetWidth()
{
	return m_nWidth;
}

int CTGALoader::GetHeight()
{
	return m_nHeight;
}


unsigned char* CTGALoader::GetImg()
{
	return m_puchrDIB24;
}


unsigned char* CTGALoader::GetPalette()
{
	return m_pPalette;
}

unsigned char *CTGALoader::GetPixel(int x, int y)
{
	if ( x < 0 ) x = 0;
	if ( x >= m_nWidth ) x = m_nWidth-1;
	if ( y < 0 ) y = 0;
	if ( y >= m_nHeight ) y = m_nHeight-1;

	int bytes_per_pixel = m_iBPP / 8;
	int loc = (y * m_nWidth + x) * bytes_per_pixel;

	return m_puchrDIB24 + loc;
}


