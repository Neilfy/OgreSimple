#include "CPictureLoader.h"



CPictureLoader::CPictureLoader()
{
	m_puchrDIB24 = 0;
	m_nDIBBufferLength = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_auchrTransColorRGB[0] = 0; //透明色的BGR值
	m_auchrTransColorRGB[1] = 0;
	m_auchrTransColorRGB[2] = 0; 
	m_bTransparent = false; //是否有透明色
}

CPictureLoader::~CPictureLoader()
{
	if (m_puchrDIB24 != 0)
	{
		delete[] m_puchrDIB24;
		m_puchrDIB24 = 0;
	}
}

bool CPictureLoader::createDIB24Buffer(short nWidth, short nHeight)
{
	if(nWidth <=0 || nHeight <= 0)
	{
		return false;
    }
	int widthB = (((nWidth * 3 + 3) >> 2) << 2);
	int need_len = widthB * nHeight;
	if(need_len > m_nDIBBufferLength)
	{
		if(m_puchrDIB24 != 0)
		{
			delete[] m_puchrDIB24;
			m_puchrDIB24 = 0;
			m_nWidth = 0;
			m_nHeight = 0;
			m_nDIBBufferLength = 0;
		}
		m_puchrDIB24 = new unsigned char[need_len];
		if(0 == m_puchrDIB24)
		{
			return false;
		}
		m_nDIBBufferLength = need_len;
	}
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	return true;
}


long CPictureLoader::GetImageHeight()
{
	return m_nHeight;
}

long CPictureLoader::GetImageWidth()
{
	return m_nWidth;
}

const unsigned char *CPictureLoader::GetDIB24()
{	
	return m_puchrDIB24;
}

bool CPictureLoader::IsTransparent()
{
	return m_bTransparent;
}

void CPictureLoader::GetTransparentColor(unsigned char puchrColorRGB[3])
{
	puchrColorRGB[0] = m_auchrTransColorRGB[0];
	puchrColorRGB[1] = m_auchrTransColorRGB[1];
	puchrColorRGB[2] = m_auchrTransColorRGB[2];
}

string CPictureLoader::getLastError()
{	
	return m_strErrMsg;
}
