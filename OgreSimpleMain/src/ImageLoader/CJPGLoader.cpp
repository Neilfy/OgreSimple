#include "CJPGLoader.h"
#include <memory.h>
#include <math.h>
extern "C" {
#undef HAVE_BOOLEAN
 #include "./jpeg/jpeglib.h"
 #include "./jpeg/jerror.h"
}
#include "./jpeg/jmorecfg.h"
#include <setjmp.h>



struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;

////////////////////////////////////////////////////////////////////////////////
// Here's the routine that will replace the standard error_exit method:
////////////////////////////////////////////////////////////////////////////////

void my_error_exit (j_common_ptr cinfo)
{
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	char buffer[JMSG_LENGTH_MAX];

	/* Create the message */
	(*cinfo->err->format_message) (cinfo, buffer);

	/* Always display the message. */
	//MessageBox(NULL,buffer,"JPEG Fatal Error",MB_ICONSTOP);


	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

CJPGLoader::CJPGLoader()
{
	long i;
	m_nImageLen = 0;
	init();
}

CJPGLoader::~CJPGLoader()
{
	long i;
	clear();
}

void CJPGLoader::init()
{
}

void CJPGLoader::clear()
{
}

bool CJPGLoader::LoadFromStream(const unsigned char* pBuffer, long nSize)
{
	init();
	m_puchrFileData = pBuffer;
	m_nFileSize = nSize;
	m_nDataPointer = 0;
	/* This struct contains the JPEG decompression parameters and pointers to
	* working space (which is allocated as needed by the JPEG library).
	*/
	struct jpeg_decompress_struct cinfo;
	/* We use our private extension JPEG error handler. <CSC> */
	struct my_error_mgr jerr;
	/* More stuff */
	JSAMPARRAY buffer;	/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */

	/* In this example we want to open the input file before doing anything else,
	* so that the setjmp() error recovery below can assume the file is open.
	* VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
	* requires it in order to read binary files.
	*/

	/* Step 1: allocate and initialize JPEG decompression object */
	/* We set up the normal JPEG error routines, then override error_exit. */
	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error.
		* We need to clean up the JPEG object, close the input file, and return.
		*/
		jpeg_destroy_decompress(&cinfo);
		return false;
	}
	/* Now we can initialize the JPEG decompression object. */
	jpeg_create_decompress(&cinfo);

	/* Step 2: specify data source (eg, a file) */
	jpeg_mem_src(&cinfo, (unsigned char *)pBuffer, nSize);

	/* Step 3: read file parameters with jpeg_read_header() */
	(void) jpeg_read_header(&cinfo, TRUE);

	/* Step 4 <chupeev> handle decoder options*/



	/* Step 5: Start decompressor */
	jpeg_start_decompress(&cinfo);

	/* We may need to do some setup of our own at this point before reading
	* the data.  After jpeg_start_decompress() we have the correct scaled
	* output image dimensions available, as well as the output colormap
	* if we asked for color quantization.
	*/
	//Create the image using output dimensions <ignacio>
	//Create(cinfo.image_width, cinfo.image_height, 8*cinfo.output_components, CXIMAGE_FORMAT_JPG);
	createDIB24Buffer(cinfo.output_width, cinfo.output_height);

	if (!m_puchrDIB24) longjmp(jerr.setjmp_buffer, 1);  //<DP> check if the image has been created


	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	/* Step 6: while (scan lines remain to be read) */
	/*           jpeg_read_scanlines(...); */

	/* Here we use the library's state variable cinfo.output_scanline as the
	* loop counter, so that we don't have to keep track ourselves.
	*/
    if (cinfo.out_color_space == JCS_GRAYSCALE)
	{
		while (cinfo.output_scanline < cinfo.output_height) 
		{
			/* jpeg_read_scanlines expects an array of pointers to scanlines.
			 * Here the array is only one element long, but you could ask for
			 * more than one scanline at a time if that's more convenient.
			 */
			(void) jpeg_read_scanlines(&cinfo, buffer, 1);
			/* Assume put_scanline_someplace wants a pointer and sample count. */


			// assume all single component images are grayscale
			for(int i=0;i<cinfo.output_width;i++)
			{
				int offset = (cinfo.output_height-cinfo.output_scanline) * WIDTHBYTES(cinfo.output_width*24);
				//m_puchrDIB24[offset+i*3+3] = 255;
				m_puchrDIB24[offset+i*3+2] = *(buffer[0]+i);
				m_puchrDIB24[offset+i*3+0] = *(buffer[0]+i);
				m_puchrDIB24[offset+i*3+1] = *(buffer[0]+i);
			}		

		}
	}
    else
	{
		while (cinfo.output_scanline < cinfo.output_height) 
		{
			/* jpeg_read_scanlines expects an array of pointers to scanlines.
			 * Here the array is only one element long, but you could ask for
			 * more than one scanline at a time if that's more convenient.
			 */
			(void) jpeg_read_scanlines(&cinfo, buffer, 1);
			/* Assume put_scanline_someplace wants a pointer and sample count. */
			for(int i=0;i<cinfo.output_width;i++)
			{
//				int offset = (cinfo.output_height-cinfo.output_scanline) * WIDTHBYTES(cinfo.output_width*24);
				int offset = (cinfo.output_height-cinfo.output_scanline) * WIDTHBYTES(cinfo.output_width*24);
				m_puchrDIB24[offset+i*3+2] = *(buffer[0]+i * 3 + 2);
				m_puchrDIB24[offset+i*3+0] = *(buffer[0]+i * 3 + 0);
				m_puchrDIB24[offset+i*3+1] = *(buffer[0]+i * 3 + 1);
			}		
		}
	}

	/* Step 7: Finish decompression */
	(void) jpeg_finish_decompress(&cinfo);
	/* We can ignore the return value since suspension is not possible
	* with the stdio data source.
	*/

	/* Step 8: Release JPEG decompression object */
	/* This is an important step since it will release a good deal of memory. */
	jpeg_destroy_decompress(&cinfo);

	/* At this point you may want to check to see whether any corrupt-data
	* warnings occurred (test whether jerr.pub.num_warnings is nonzero).
	*/

	/* And we're done! */
	return true;
}


