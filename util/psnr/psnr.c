/**
 * @file
 * @brief PSNR comparison calculation
 *$RCSfile: psnr.c,v $
 *
 *   DESC : EEMBC PSNR Calculator
 *          Calculates PSNR of files using absolute distance 
 *          between two images.
 *
 * AUTHOR : Rick Foos, ECL, LLC
 *
 *  EEMBC : Consumer
 *
 *    CVS : $Revision: 1.5 $
 *          $Date: 2005/12/03 00:08:20 $
 *          $Author: rick $
 *          $Source: /cvs/eembc2/techtag/util/psnr/psnr.c,v $
 *          
 * NOTE   : 
 *
 *------------------------------------------------------------------------------
 *
 * HISTORY :
 *
 * $Log: psnr.c,v $
 * Revision 1.5  2005/12/03 00:08:20  rick
 * Set minimum to 0 when index=-1, and numframes=1. The -1 is a signal to psnr_write that match has occured.
 *
 * Revision 1.4  2005/12/02 21:11:53  rick
 * Add spotcmyk support.
 *
 * Revision 1.3  2005/11/17 01:06:23  rick
 * Full working tiffg4 version, modified psnr output to add more single file types.
 *
 * Revision 1.2  2005/11/16 20:44:57  rick
 * First Portable revision, with installed documentation, and MSVC/Windows compatibility. EEMBC Ignore Data/Time differences.
 *
 * Revision 1.1  2005/11/14 21:52:40  rick
 * Initial add of psnr with libtiff
 *
 *
 *------------------------------------------------------------------------------
 * Copyright (c) 1998-2005 by the EDN Embedded Microprocessor 
 * Benchmark Consortium (EEMBC), Inc. 
 * 
 * All Rights Reserved. This is licensed program product and 
 * is owned by EEMBC. The Licensee understands and agrees that the 
 * Benchmarks licensed by EEMBC hereunder (including methods or concepts 
 * utilized therein) contain certain information that is confidential 
 * and proprietary which the Licensee expressly agrees to retain in the 
 * strictest confidence and to use only in conjunction with the Benchmarks 
 * pursuant to the terms of this Agreement. The Licensee further agrees 
 * to keep the source code and all related documentation confidential and 
 * not to disclose such source code and/or related documentation to any 
 * third party. The Licensee and any READER of this code is subject to 
 * either the EEMBC Member License Agreement and/or the EEMBC Licensee 
 * Agreement. 
 * TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, EEMBC DISCLAIMS ALL 
 * WARRANTIES, EITHER EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, 
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 * PURPOSE, WITH REGARD TO THE BENCHMARKS AND THE ACCOMPANYING 
 * DOCUMENTATION. LICENSEE ACKNOWLEDGES AND AGREES THAT THERE ARE NO 
 * WARRANTIES, GUARANTIES, CONDITIONS, COVENANTS, OR REPRESENTATIONS BY 
 * EEMBC AS TO MARKETABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR OTHER 
 * ATTRIBUTES, WHETHER EXPRESS OR IMPLIED (IN LAW OR IN FACT), ORAL OR 
 * WRITTEN. 
 * 
 * Licensee hereby agrees by accessing this source code that all benchmark 
 * scores related to this code must be certified by ECL prior to publication 
 * in any media, form, distribution, or other means of conveyance of 
 * information subject to the terms of the EEMBC Member License Agreement 
 * and/or EEMBC Licensee Agreement. 
 * 
 * Other Copyright Notice (if any): 
 * 
 * For conditions of distribution and use, see the accompanying README file.
 * ===========================================================================*/

#include <string.h> /* strdup, strncmp */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> /* gcc toupper */
#include <sys/stat.h> /* stat, struct stat */
#include <math.h> /* log10, pow */
#include <limits.h> /* CHAR_BIT */
#include "tiffio.h"

/* These structures must be defined before proto.h */

/* AIFF Section. */

/** Force unsigned long alignment. */
typedef struct  blockAlign_struct {
    unsigned long   offset;
    unsigned long   blockSize;
} blockAlign;

/** AIFF information from header. */
typedef struct  IFF_AIFF_struct {
    short           numChannels;
    unsigned long   numSampleFrames;
    short           sampleSize;
    double          sampleRate;
    unsigned long   sampleType;
    blockAlign      blkAlgn;
} IFF_AIFF;

struct lame_global_struct {
  /* input description */
  unsigned long num_samples;  /* number of samples. default=2^32-1           */
  int num_channels;           /* input number of channels. default=2         */
  int in_samplerate;          /* input_samp_rate in Hz. default=44.1 kHz     */
  int sampleSize;			/* from iff_aiff, pcm width. */
  int framesize;			/* MPEG frame size */
  int frameNum;
  int lame_allocated_gfp;
};
typedef struct lame_global_struct lame_global_flags;
typedef lame_global_flags *lame_t;

/* AIFF Section End */

#include "proto.h"

/** @addtogroup eembc_util
 * @{ */
/** @addtogroup PSNR
 * @{ */

/** we need to know the host endian for aiff */
int bigendian=0;
/** Create a 32 bit big endian pattern */
#define LONG_PACK(a,b,c,d) ((long) (((long)(a))<<24) | (((long)(b))<<16) | \
                                   (((long)(c))<<8)  |((long)(d)))
/** Swap endian of 32 bits of data. */
#define SWAP(a) ( (((a)&0x000000ff)<<24) | (((a)&0x0000ff00)<<8) | \
                  (((a)&0x00ff0000)>>8)  | (((a)&0xff000000)>>24) )

/** Display program options */
void Usage(void)
{
const char *usage="Usage:  psnr {options}\n\
Options: \n\
         -x  <XDIM> Width in pixels of files\n\
         -y  <YDIM> Height in pixels of files\n\
         -c  <colormap> Colormap (format) of files\n\
         -n  <nframes> NUMBER of frames (0 for single file)\n\
         -s  <frame0> STARTING frame number\n";
const char *usage1="\
         -o  <output_enable [1,2,3]> output YUV12 as PGM\n\
		     Option 1 :\n\
             The High Intensity Image is suitable for showing\n\
             files that do not have many errors.\n\
             if (image1[i] == image2[i])\n\
                 imageZ[i] = 0;\n\
             else\n\
                 imageZ[i] = 0xFF;\n\
\n";
const char *usage2="\
		     Option 2 :\n\
             The Subtracted Image can be used, but it's not too visible \n\
             on similar datasets.\n\
             It is useful for finding artifacts, when looking through\n\
             a large number of frames.\n\
             imageZ[i]=abs(image1[i]-image2[i]);\n\
\n";
const char *usage3="\
		     Option 3 :\n\
             The Error Image is a slightly more viewable form of the\n\
             subtracted image. e(i,j)=2(f(i,j)-F(i,j))+128\n\
             imageZ[i] = 2*(image1[i]-image2[i])+128;\n\
\n\
Example:  psnr -x 320 -y 240 xxx.yuv yyy.Y\n\
\n";
printf("%s%s%s%s",usage,usage1,usage2,usage3);
/* Standard args error level is 2. */
exit(2);
}

/** Error messages to stdout, and stderr followed by exit 1.*/
void psnr_abort( const char *fmt, ... )
{
	int rv;
	va_list args;
	printf ("*** Failure: ");
	fprintf(stderr,
			"*** Failure: ");
	va_start( args, fmt );
	rv = vprintf(fmt,args);
	rv = vfprintf( stderr, fmt, args );
	va_end( args );
	exit(1);
}

/* Global Option Variables */

/** Width of image. */
int		XDIM=0;
/** Height of image. */
int		YDIM=0;
/** Reference file */
char	*fname1=NULL;
/** Comparison file */
char	*fname2=NULL;
/** Colormap of file. */
char	*colormap=NULL;
/** total number of frames */
int		nframes=0;
/** number of first frame, default 0 */
int 	frame0=0;
/** Flag to dump YUV12 as PGM */
int		output_enable=0;

/** Process command line options */
void Process_Options(int argc,char *argv[])
{
	int i, LastArg, NextArg;

	/* at least one argument should be present */
	if (argc<2) Usage();
	i = 1;
	/* command-line options are proceeded by '-' */
	while(i < argc)
	{
		/* check if this is the last argument */
		LastArg = ((argc-i)==1);

		/* 
		 * parse ahead to see if another flag immediately follows current
		 * argument (this is used to tell if a filename is missing) 
		 */
		if(!LastArg)
			NextArg = (argv[i+1][0]=='-');
		else
			NextArg = 0;

      /* second character, [1], after '-' is the switch */
      if(argv[i][0]=='-')
      {
         switch(toupper(argv[i][1]))
		 {
			/* third character. [2], is the value */

			case 'X':
				if(NextArg || LastArg)
				{
					printf("ERROR: -x must be followed by image width\n");
					Usage();
				}
				else
					XDIM = atoi(argv[++i]);
				break;

			case 'Y':
				if(NextArg || LastArg)
				{
					printf("ERROR: -y must be followed by image height\n");
					Usage();
				}
				else
					YDIM = atoi(argv[++i]);
				break;
			case 'C':
				if(NextArg || LastArg)
				{
					printf("ERROR: -c must be followed a Color Map\n");
					Usage();
				}
				else
					colormap = argv[++i];
				break;

			case 'N':
				if(NextArg || LastArg)
				{
					printf("ERROR: -n must be followed by the number of frames\n");
					Usage();
				}
				else
					nframes = atoi(argv[++i]);
				break;

			case 'S':
				if(NextArg || LastArg)
				{
					printf("ERROR: -s must be followed by the start frame number\n");
					Usage();
				}
				else
				frame0 = atoi(argv[++i]);
				break;
			case 'O':
				if(NextArg || LastArg)
				{
					printf("ERROR: -o must be followed by the error image format\n");
					Usage();
				}
				else
				output_enable = atoi(argv[++i]);
				break;
			default:
				printf("undefined option -%c ignored.",argv[i][1]);
				Usage();
		 } /* switch() */
	  } /* if argv[i][0] == '-' */
	  else
	  {
		  if (!fname1)
			  fname1 = argv[i];
		  else if (!fname2)
			  fname2 = argv[i];
		  else
		  {
			printf("ERROR: Too many file names");
	  		Usage();
		  }
	  }
	i++;
   } /* while() */


	/* options sense checking */

    /**
	 * check for two filename arguments 
	 * (there must always be two, at the very end of the command line arguments 
	 */
	if (!fname1 || !fname2)
	{
		printf("ERROR: you must supply a reference file, and a file to compare\n");
		Usage();
	}
	   
}
/** Paths for mpeg2 YUV files */
const char *gs_path[] = 
{"","../../","../../gs-output/","gs-output/","gs8/win32/",NULL};
/** Paths for mpeg2 YUV files */
const char *mpeg2dec_path[] = 
{"","../../","../../libyuv/","libyuv/","mpeg/mpeg2dec/win32/",NULL};
/** Paths for mpeg4 YUV files */
const char *mp4decode_path[] = 
{"","../../","../../libyuv/","libyuv/","mpeg4/mp4decode/win32/",NULL};
/** Path used to locate input files. */
const char	**path;

/** Check if we need to do byte swapping. */
int checkswap(int swap)
{
	int doswap=0;
	/* We seem to also need swapping on BE hosts.
	if (bigendian) return swap;
	 */
	doswap=(swap&0x000000ff)<<24;
	doswap|=(swap&0x0000ff00)<<8;
	doswap|=(swap&0x00ff0000)>>8;
	doswap|=(swap&0xff000000)>>24;
	return doswap;
}

/** returns the mean of the sum of squared distances 
between two integer PCM frames. */
double absdistq_frame(
				int buf1[2][1152],
				int buf2[2][1152])
{
	double	dist=0.0;
	int 	i,j;
	double	val;

	for (i=0;i<2;i++)
	{	
		val=0;
		for (j=0;j<1152;j++)
		{
			buf1[i][j]=checkswap(buf1[i][j]);
			buf2[i][j]=checkswap(buf2[i][j]);
			val+= (double)((long)buf1[i][j]-(long)buf2[i][j]) *
						  ((long)buf1[i][j]-(long)buf2[i][j]);
		}
	
		dist += (double)val*1.0;
	}
   return dist/(2.0*1152.0);
}

/** returns the mean of the sum of squared distances 
(SSD) between two images of dimensions x times y. */
double absdistq(int x,int y, 
				unsigned char* buf1, int stride1, 
				unsigned char* buf2, int stride2)
{
	double dist=0.;
	int i,j,val,numdif=0;

	for (i=0;i<y;i++)
	{	
		val=0;
		for (j=0;j<x;j++) {
			if (buf1[j]!=buf2[j])
				numdif++;
			val+= (buf1[j]-buf2[j])*(buf1[j]-buf2[j]);
		}
	
		dist += (double)val;
		buf1 += stride1;
		buf2 += stride2;
	}
   return dist/(x*y);
}

/** returns the mean of the sum of squared distances 
(SSD) between two images of dimensions x times y. */
double absdistqn(int x,int y, 
				unsigned char* buf1, int stride1, 
				unsigned char* buf2, int stride2, int numbits)
{
	double dist=0.;
	int i,j,k,val;
	int mask =  ~((-1)<<numbits);
	int numrots=8/numbits;
	char b1,b2;

	for (i=0;i<y;i++)
	{	
		val=0;
		/* for each byte */
		for (j=0;j<x;j++) {
			/* sum MSE for each packed quantity */
			for (k=0;k<numrots;k++) {
				b1=(buf1[j]>>(k*numbits)) & mask; 
				b2=(buf2[j]>>(k*numbits)) & mask; 
				val+= (b1-b2)*(b1-b2);
			}
		}
	
		dist += (double)val;
		buf1 += stride1;
		buf2 += stride2;
	}
   return dist/(x*y*numrots);
}

double noise_power(int x,int y, 
				unsigned char* ref, 
				unsigned char* actual, int numbits)
{
	double dist=0.;
	int i,j,k,val;
	int mask =  ~((-1)<<numbits);
	int numrots=8/numbits;
	char b1,b2;

	for (i=0;i<y;i++)
	{	
		val=0;
		/* for each byte */
		for (j=0;j<x;j++) {
			/* sum MSE for each packed quantity */
			for (k=0;k<numrots;k++) {
				b1=(ref[j]>>(k*numbits)) & mask; 
				b2=(actual[j]>>(k*numbits)) & mask; 
				val+= (b1-b2)*(b1-b2);
			}
		}
		ref+=x;
		actual+=x;
		dist += (double)val;
	}
	return dist;
}

double signal_power(int x,int y, 
				unsigned char* signal, int numbits)
{
	double dist=0.;
	int i,j,k,val;
	int mask =  ~((-1)<<numbits);
	int numrots=8/numbits;
	char b1;

	for (i=0;i<y;i++)
	{	
		val=0;
		/* for each byte */
		for (j=0;j<x;j++) {
			/* sum MSE for each packed quantity */
			for (k=0;k<numrots;k++) {
				b1=(signal[j]>>(k*numbits)) & mask; 
				val+= (b1)*(b1);
			}
		}
		signal+=x;
		dist += (double)val;
	}
	return dist;
}

/** return the PSNR between two 16 bit integer PCM frames.
Adjust for DATA size squared using pow. For 8 bits, 256*256.
For 16 bits, 0xFFFE0001. Even though the input is int, the
data can be 16 bits wide (i.e. (2**16-1)**2 in fortran).
*/
double PSNR_frame(int buf1[2][1152],int buf2[2][1152],double datawidth)
{
	/*printf("powpow: %lf\n",pow(pow(2,datawidth)-1,2));*/
	return 10*(log10(pow(pow(2,datawidth)-1,2))-log10(absdistq_frame(buf1,buf2)));
}

/** return the PSNR between two images.
this is a logarithmic measure for "quality" from the world of signal processing
if you don't know what it is, simply accept that higher values are better
*/
double PSNR(int x,int y, 
			unsigned char* buf1, int stride1, 
			unsigned char* buf2, int stride2)
{
	return 20.0*log10( 255.0 / sqrt(absdistq(x, y, buf1, stride1, buf2, stride2) ));
}

/** return the PSNR between two images.
this is a logarithmic measure for "quality" from the world of signal processing
if you don't know what it is, simply accept that higher values are better
*/
double PSNRpackedbits(int x,int y, 
			unsigned char* buf1, int stride1, 
			unsigned char* buf2, int stride2,int numbits)
{
	return 20.0*log10( 255.0 / sqrt(absdistqn(x, y, buf1, stride1, buf2, stride2, numbits) ));
}

double SNRpackedbits(int x,int y, 
			unsigned char* actual, int stride1, 
			unsigned char* ref, int stride2,int numbits)
{
	return 10.0*log10( signal_power(x,y,ref,numbits) / noise_power(x,y,ref,actual,numbits));
}

double SNR(int x,int y, 
			unsigned char* actual, int stride1, 
			unsigned char* ref, int stride2) 
{
	return SNRpackedbits(x,y,actual,stride1,ref,stride2,8);
}

/** Find and Open a file. */
FILE *psnrfind_file(const char *filename, const char *filemode,char **actualname)
{
	char	buf[FILENAME_MAX];
	int		i=0;
	FILE	*found_file=NULL;

	if ((strcmp(filename,"stdin")) == 0) 
		return fopen(filename,filemode);

	while (path[i] != NULL)
	{
		strcpy(buf,path[i]);
		strcat(buf,filename);
		if ((found_file = fopen(buf,filemode)) != NULL ) 
		{
			if (actualname)
				*actualname = (char *)strdup((char *)buf);
			return found_file;
		}
		i++;
	}
	return NULL;
}

/** Get file size using stat function. */
int getFilesize(const char *fname)
{
    int   length;
    struct  stat st;

    if (!fname || !*fname) 
		length=0;
    else
        if ((stat(fname,&st))==-1)
			length=0;
        else
			length = st.st_size;
    return length;
}

/** Split path on filetype. */
char *getFiletype(const char *fname)
{
	char *rv;
	if ((rv=strrchr(fname,'.'))!=NULL)
	{
		char *filepath;
		if ((filepath=strrchr(fname,'/')) && (filepath>rv)) return NULL;
		rv++;
	}
	return rv;
}
/** Load a file into a malloc'ed memory region. */
unsigned char *loadOpenfile(const char *fname,int *fsize,FILE *fd)
{
	unsigned char *buf;
	FILE *fdnull=fd;
	/* run the gamut, and return */
	if (!fdnull && ((fdnull=fopen(fname,"rb"))==NULL))
	{
		psnr_abort("File %s would not open.\n",fname);
	}
	if (!(*fsize = getFilesize(fname)))
	{
		printf("*** Failure: File %s is empty.\n",fname);
		fprintf(stderr,"*** Failure: File %s is empty.\n",fname);
		exit(1);
	}
	if (!(buf=malloc(*fsize)))
	{
		printf("*** Failure: Out of memory for %s, %d bytes\n",fname, *fsize);
		fprintf(stderr,
			"*** Failure: Out of memory for %s, %d bytes\n",fname, *fsize);
		exit(1);
	}
	if ((fread(buf,*fsize,1,fdnull))!=1)
	{
		free(buf);
		printf("*** Failure: Error reading %d bytes from %s\n",*fsize,fname);
		fprintf(stderr,
			"*** Failure: Error reading %d bytes from %s\n",*fsize,fname);
		exit(1);
	}
	fclose(fdnull);
	return buf;
}

/* TIFF Section */

static	int stoponfirstdiff = 1;
static	int stoponfirsttag = 1;
static	uint16 bitspersample = 1;
static	uint16 samplesperpixel = 1;
static	uint32 imagewidth;
static	uint32 imagelength;

static	int tiffcmp(TIFF*, TIFF*, unsigned char **img1, unsigned char **img2, int *expected_size);
static	int cmptags(TIFF*, TIFF*);
static	void ContigCompare(int, uint32, unsigned char*, unsigned char*, int);
static	void PrintDiff(uint32, int, uint32, int, int);
static	void SeparateCompare(int, int, uint32, unsigned char*, unsigned char*);
static	void eof(const char*, uint32, int);

#define	checkEOF(tif, row, sample) { \
	eof(TIFFFileName(tif), row, sample); \
	goto bad; \
}

static	int CheckShortTag(TIFF*, TIFF*, int, char*);
static	int CheckShort2Tag(TIFF*, TIFF*, int, char*);
static	int CheckShortArrayTag(TIFF*, TIFF*, int, char*);
static	int CheckLongTag(TIFF*, TIFF*, int, char*);
static	int CheckFloatTag(TIFF*, TIFF*, int, char*);
static	int CheckStringTag(TIFF*, TIFF*, int, char*);

static int
tiffcmp(TIFF* tif1, TIFF* tif2, unsigned char **img1, unsigned char **img2, int *expected_size)
{
	uint16 config1, config2;
	int s, size1, size2;
	uint32 row;
	unsigned char *buf1, *buf2, *pimg1, *pimg2,mask;

	/* caller can detect error if these are null. */
	*img1=*img2=NULL;

	if (!CheckShortTag(tif1, tif2, TIFFTAG_BITSPERSAMPLE, "BitsPerSample"))
		return (0);
	if (!CheckShortTag(tif1, tif2, TIFFTAG_SAMPLESPERPIXEL, "SamplesPerPixel"))
		return (0);
	if (!CheckLongTag(tif1, tif2, TIFFTAG_IMAGEWIDTH, "ImageWidth"))
		return (0);
	if (!cmptags(tif1, tif2))
		return (1);
	(void) TIFFGetField(tif1, TIFFTAG_BITSPERSAMPLE, &bitspersample);
	(void) TIFFGetField(tif1, TIFFTAG_SAMPLESPERPIXEL, &samplesperpixel);
	(void) TIFFGetField(tif1, TIFFTAG_IMAGEWIDTH, &imagewidth);
	(void) TIFFGetField(tif1, TIFFTAG_IMAGELENGTH, &imagelength);YDIM=imagelength;
	(void) TIFFGetField(tif1, TIFFTAG_PLANARCONFIG, &config1);
	(void) TIFFGetField(tif2, TIFFTAG_PLANARCONFIG, &config2);
	buf1 = (unsigned char *)calloc(size1 = TIFFScanlineSize(tif1),1);
	buf2 = (unsigned char *)calloc(size2 = TIFFScanlineSize(tif2),1);
	if (buf1 == NULL || buf2 == NULL) {
		psnr_abort("No space for scanline buffers\n");
		exit(-1);
	}
	/** \todo handle seperate cases. */
	if (size1!=size2)
		psnr_abort("ENHANCMENT REQUIRED FOR NONCONTIGIOUS IMAGES.\n");
	XDIM=size1;

	if (config1 != config2 && bitspersample != 8 && samplesperpixel > 1) {
		psnr_abort("Can't handle different planar configuration w/ different bits/sample\n");
		goto bad;
	}
#define	pack(a,b)	((a)<<8)|(b)
	switch (pack(config1, config2)) {
	case pack(PLANARCONFIG_SEPARATE, PLANARCONFIG_CONTIG):
		for (row = 0; row < imagelength; row++) {
			if (TIFFReadScanline(tif2, buf2, row, 0) < 0)
				checkEOF(tif2, row, -1)
			for (s = 0; s < samplesperpixel; s++) {
				if (TIFFReadScanline(tif1, buf1, row, s) < 0)
					checkEOF(tif1, row, s)
				SeparateCompare(1, s, row, buf2, buf1);
			}
		}
		break;
	case pack(PLANARCONFIG_CONTIG, PLANARCONFIG_SEPARATE):
		for (row = 0; row < imagelength; row++) {
			if (TIFFReadScanline(tif1, buf1, row, 0) < 0)
				checkEOF(tif1, row, -1)
			for (s = 0; s < samplesperpixel; s++) {
				if (TIFFReadScanline(tif2, buf2, row, s) < 0)
					checkEOF(tif2, row, s)
				SeparateCompare(0, s, row, buf1, buf2);
			}
		}
		break;
	case pack(PLANARCONFIG_SEPARATE, PLANARCONFIG_SEPARATE):
		for (s = 0; s < samplesperpixel; s++)
			for (row = 0; row < imagelength; row++) {
				if (TIFFReadScanline(tif1, buf1, row, s) < 0)
					checkEOF(tif1, row, s)
				if (TIFFReadScanline(tif2, buf2, row, s) < 0)
					checkEOF(tif2, row, s)
				ContigCompare(s, row, buf1, buf2, size1);
			}
		break;
	case pack(PLANARCONFIG_CONTIG, PLANARCONFIG_CONTIG):
		if ((pimg1=*img1=calloc(size1*imagelength,1))==NULL)
			psnr_abort("Out of memory tiff img1.\n");
		if ((pimg2=*img2=calloc(size2*imagelength,1))==NULL)
			psnr_abort("Out of memory tiff img2.\n");
		*expected_size = size1*imagelength;
		/* SG: make sure the image contains only real bits for each sample */
		mask =  ~((-1)<<bitspersample);
		for (row = 0; row < imagelength; row++) {
			if (TIFFReadScanline(tif1, buf1, row, 0) < 0)
				checkEOF(tif1, row, -1);
			for (s=0 ; s<size1 ;s++)
				buf1[s] &= mask;
			memcpy(pimg1,buf1,size1);pimg1+=size1;
			if (TIFFReadScanline(tif2, buf2, row, 0) < 0)
				checkEOF(tif2, row, -1);
			for (s=0 ; s<size1 ;s++)
				buf2[s] &= mask;
			memcpy(pimg2,buf2,size2);pimg2+=size2;
			/*ContigCompare(-1, row, buf1, buf2, size1);*/
		}
		break;
	}
	if (buf1) free(buf1);
	if (buf2) free(buf2);
	return (1);
bad:
	if (stoponfirstdiff)
		exit(1);
	if (buf1) free(buf1);
	if (buf2) free(buf2);
	return (0);
}

#define	CmpShortField(tag, name) \
	if (!CheckShortTag(tif1, tif2, tag, name) && stoponfirsttag) return (0)
#define	CmpShortField2(tag, name) \
	if (!CheckShort2Tag(tif1, tif2, tag, name) && stoponfirsttag) return (0)
#define	CmpLongField(tag, name) \
	if (!CheckLongTag(tif1, tif2, tag, name) && stoponfirsttag) return (0)
#define	CmpFloatField(tag, name) \
	if (!CheckFloatTag(tif1, tif2, tag, name) && stoponfirsttag) return (0)
#define	CmpStringField(tag, name) \
	if (!CheckStringTag(tif1, tif2, tag, name) && stoponfirsttag) return (0)
#define	CmpShortArrayField(tag, name) \
	if (!CheckShortArrayTag(tif1, tif2, tag, name) && stoponfirsttag) return (0)

static int
cmptags(TIFF* tif1, TIFF* tif2)
{
	CmpLongField(TIFFTAG_SUBFILETYPE,	"SubFileType");
	CmpLongField(TIFFTAG_IMAGEWIDTH,	"ImageWidth");
	CmpLongField(TIFFTAG_IMAGELENGTH,	"ImageLength");
	CmpShortField(TIFFTAG_BITSPERSAMPLE,	"BitsPerSample");
	CmpShortField(TIFFTAG_COMPRESSION,	"Compression");
	CmpShortField(TIFFTAG_PREDICTOR,	"Predictor");
	CmpShortField(TIFFTAG_PHOTOMETRIC,	"PhotometricInterpretation");
	CmpShortField(TIFFTAG_THRESHHOLDING,	"Thresholding");
	CmpShortField(TIFFTAG_FILLORDER,	"FillOrder");
	CmpShortField(TIFFTAG_ORIENTATION,	"Orientation");
	CmpShortField(TIFFTAG_SAMPLESPERPIXEL,	"SamplesPerPixel");
	CmpShortField(TIFFTAG_MINSAMPLEVALUE,	"MinSampleValue");
	CmpShortField(TIFFTAG_MAXSAMPLEVALUE,	"MaxSampleValue");
	CmpFloatField(TIFFTAG_XRESOLUTION,	"XResolution");
	CmpFloatField(TIFFTAG_YRESOLUTION,	"YResolution");
	CmpLongField(TIFFTAG_GROUP3OPTIONS,	"Group3Options");
	CmpLongField(TIFFTAG_GROUP4OPTIONS,	"Group4Options");
	CmpShortField(TIFFTAG_RESOLUTIONUNIT,	"ResolutionUnit");
	CmpShortField(TIFFTAG_PLANARCONFIG,	"PlanarConfiguration");
	CmpLongField(TIFFTAG_ROWSPERSTRIP,	"RowsPerStrip");
	CmpFloatField(TIFFTAG_XPOSITION,	"XPosition");
	CmpFloatField(TIFFTAG_YPOSITION,	"YPosition");
	CmpShortField(TIFFTAG_GRAYRESPONSEUNIT, "GrayResponseUnit");
	CmpShortField(TIFFTAG_COLORRESPONSEUNIT, "ColorResponseUnit");
#ifdef notdef
	{ uint16 *graycurve;
	  CmpField(TIFFTAG_GRAYRESPONSECURVE, graycurve);
	}
	{ uint16 *red, *green, *blue;
	  CmpField3(TIFFTAG_COLORRESPONSECURVE, red, green, blue);
	}
	{ uint16 *red, *green, *blue;
	  CmpField3(TIFFTAG_COLORMAP, red, green, blue);
	}
#endif
	CmpShortField2(TIFFTAG_PAGENUMBER,	"PageNumber");
	CmpStringField(TIFFTAG_ARTIST,		"Artist");
	CmpStringField(TIFFTAG_IMAGEDESCRIPTION,"ImageDescription");
	CmpStringField(TIFFTAG_MAKE,		"Make");
	CmpStringField(TIFFTAG_MODEL,		"Model");
	CmpStringField(TIFFTAG_SOFTWARE,	"Software");
	/** \note EEMBC igmores the Date/Time difference.
	CmpStringField(TIFFTAG_DATETIME,	"DateTime");
	*/
	CmpStringField(TIFFTAG_HOSTCOMPUTER,	"HostComputer");
	CmpStringField(TIFFTAG_PAGENAME,	"PageName");
	CmpStringField(TIFFTAG_DOCUMENTNAME,	"DocumentName");
	CmpShortField(TIFFTAG_MATTEING,		"Matteing");
	CmpShortArrayField(TIFFTAG_EXTRASAMPLES,"ExtraSamples");
	return (1);
}

static void
ContigCompare(int sample, uint32 row, unsigned char* p1, unsigned char* p2, int size)
{
	register uint32 pix;
	register int ppb = 8/bitspersample;

	if (memcmp(p1, p2, size) == 0)
		return;
	switch (bitspersample) {
	case 1: case 2: case 4: case 8: {
		register unsigned char *pix1 = p1, *pix2 = p2;

		for (pix = 0; pix < imagewidth; pix1++, pix2++, pix += ppb)
			if (*pix1 != *pix2)
				PrintDiff(row, sample, pix,
				    *pix1, *pix2);
		break;
	}
	case 16: {
		register uint16 *pix1 = (uint16 *)p1, *pix2 = (uint16 *)p2;

		for (pix = 0; pix < imagewidth; pix1++, pix2++, pix++)
			if (*pix1 != *pix2)
				PrintDiff(row, sample, pix,
				    *pix1, *pix2);
		break;
	}
	}
}

static void
PrintDiff(uint32 row, int sample, uint32 pix, int w1, int w2)
{
	register int mask1, mask2, s, bps;

	if (sample < 0)
		sample = 0;
	bps = bitspersample;
	switch (bps) {
	case 1:
	case 2:
	case 4:
		mask1 =  ~((-1)<<bps);
		s = (8-bps);
		mask2 = mask1<<s;
		for (; mask2; mask2 >>= bps, s -= bps, pix++) {
			if ((w1 & mask2) ^ (w2 & mask2)) {
				printf(
			"Scanline %lu, pixel %lu, sample %d: %01x %01x\n",
	    				row, pix, sample, (w1 >> s) & mask1,
					(w2 >> s) & mask1 );
				if (stoponfirstdiff)
					exit(1);
			}
		}
		break;
	case 8: 
		printf("Scanline %lu, pixel %lu, sample %d: %02x %02x\n",
		    row, pix, sample, w1, w2);
		if (stoponfirstdiff)
			exit(1);
		break;
	case 16:
		printf("Scanline %lu, pixel %lu, sample %d: %04x %04x\n",
		    row, pix, sample, w1, w2);
		if (stoponfirstdiff)
			exit(1);
		break;
	}
}

static void
SeparateCompare(int reversed, int sample, uint32 row, unsigned char* cp1, unsigned char* p2)
{
	uint32 npixels = imagewidth;
	register int pixel;

	cp1 += sample;
	for (pixel = 0; npixels-- > 0; pixel++, cp1 += samplesperpixel, p2++)
		if (*cp1 != *p2) {
			printf("Scanline %lu, pixel %lu, sample %d: ",
			    row, pixel, sample);
			if (reversed)
				printf("%02x %02x\n", *p2, *cp1);
			else
				printf("%02x %02x\n", *cp1, *p2);
			if (stoponfirstdiff)
				exit(1);
		}
}

static int
checkTag(TIFF* tif1, TIFF* tif2, int tag, char* name, void* p1, void* p2)
{

	if (TIFFGetField(tif1, tag, p1)) {
		if (!TIFFGetField(tif2, tag, p2)) {
			printf("%s tag appears only in %s\n",
			    name, TIFFFileName(tif1));
			return (0);
		}
		return (1);
	} else if (TIFFGetField(tif2, tag, p2)) {
		printf("%s tag appears only in %s\n", name, TIFFFileName(tif2));
		return (0);
	}
	return (-1);
}

#define	CHECK(cmp, fmt) {				\
	switch (checkTag(tif1,tif2,tag,name,&v1,&v2)) {	\
	case 1:	if (cmp)				\
	case -1:	return (1);			\
		printf(fmt, name, v1, v2);		\
	}						\
	return (0);					\
}

static int
CheckShortTag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	uint16 v1, v2;
	CHECK(v1 == v2, "%s: %u %u\n");
}

static int
CheckShort2Tag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	uint16 v11, v12, v21, v22;

	if (TIFFGetField(tif1, tag, &v11, &v12)) {
		if (!TIFFGetField(tif2, tag, &v21, &v22)) {
			printf("%s tag appears only in %s\n",
			    name, TIFFFileName(tif1));
			return (0);
		}
		if (v11 == v21 && v12 == v22)
			return (1);
		printf("%s: <%u,%u> <%u,%u>\n", name, v11, v12, v21, v22);
	} else if (TIFFGetField(tif2, tag, &v21, &v22))
		printf("%s tag appears only in %s\n", name, TIFFFileName(tif2));
	else
		return (1);
	return (0);
}

static int
CheckShortArrayTag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	uint16 n1, *a1;
	uint16 n2, *a2;

	if (TIFFGetField(tif1, tag, &n1, &a1)) {
		if (!TIFFGetField(tif2, tag, &n2, &a2)) {
			printf("%s tag appears only in %s\n",
			    name, TIFFFileName(tif1));
			return (0);
		}
		if (n1 == n2) {
			char* sep;
			int i;

			if (memcmp(a1, a2, n1) == 0)
				return (1);
			printf("%s: value mismatch, <%u:", name, n1);
			sep = "";
			for (i = 0; i < n1; i++)
				printf("%s%u", sep, a1[i]), sep = ",";
			printf("> and <%u: ", n2);
			sep = "";
			for (i = 0; i < n2; i++)
				printf("%s%u", sep, a2[i]), sep = ",";
			printf(">\n");
		} else
			printf("%s: %u items in %s, %u items in %s", name,
			    n1, TIFFFileName(tif1),
			    n2, TIFFFileName(tif2)
			);
	} else if (TIFFGetField(tif2, tag, &n2, &a2))
		printf("%s tag appears only in %s\n", name, TIFFFileName(tif2));
	else
		return (1);
	return (0);
}

static int
CheckLongTag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	uint32 v1, v2;
	CHECK(v1 == v2, "%s: %lu %lu\n");
}

static int
CheckFloatTag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	float v1, v2;
	CHECK(v1 == v2, "%s: %g %g\n");
}

static int
CheckStringTag(TIFF* tif1, TIFF* tif2, int tag, char* name)
{
	char *v1, *v2;
	CHECK(strcmp(v1, v2) == 0, "%s: \"%s\" \"%s\"\n");
}

static void
eof(const char* name, uint32 row, int s)
{

	printf("%s: EOF at scanline %lu", name, row);
	if (s >= 0)
		printf(", sample %d", s);
	printf("\n");
}

/* TIFF Section End */

/* AIFF Definitions */

/* global data for get_audio.c. */
int     count_samples_carefully;
int     pcmbitwidth;
int     pcmswapbytes = 0;
/** force byte swapping   default=0, -x command line*/
int		swapbytes=0;

unsigned int num_samples_read;
FILE   *musicin;
typedef enum sound_file_format_e 
{
  sf_unknown, 
  sf_raw, 
  sf_wave, 
  sf_aiff, 
  sf_mp1,  /* MPEG Layer 1, aka mpg */
  sf_mp2,  /* MPEG Layer 2 */
  sf_mp3,  /* MPEG Layer 3 */
  sf_ogg 
} sound_file_format;

sound_file_format input_format;

IFF_AIFF	*current_iff_aiff;

int set_current_aiff(IFF_AIFF iff)
{
	if (!current_iff_aiff)
		return 1;
	memcpy(current_iff_aiff,&iff,sizeof(IFF_AIFF));
	return 0;
}
int print_iff_aiff(IFF_AIFF iff)
{
	printf("numChannels: %d\n",iff.numChannels);
    printf("numSampleFrames: %ld\n",iff.numSampleFrames);
    printf("sampleSize: %d\n",iff.sampleSize);
    printf("sampleRate: %lf\n",iff.sampleRate);
    printf("sampleType: %lu\n",iff.sampleType);
	return 0;
}
int compare_iff_aiff(IFF_AIFF iff0, IFF_AIFF iff1)
{
	if (iff0.numChannels != iff1.numChannels) return 0;
	if (iff0.numSampleFrames != iff1.numSampleFrames) 
		printf("Warning numSampleFrames differ: %d, %d\n",
			iff0.numSampleFrames,iff1.numSampleFrames);
	if (iff0.sampleSize != iff1.sampleSize) return 0;
	if (iff0.sampleRate != iff1.sampleRate) return 0;
	if (iff0.sampleType != iff1.sampleType) return 0;
	return 1;
}

/* Routines to get and set lame global flags. */

int lame_set_samplesize(lame_global_flags*  gfp,int sampleSize )
{
    /* PCM Data Width */
    gfp->sampleSize = sampleSize;

    return 0;
}
int lame_get_samplesize( const lame_global_flags*  gfp )
{
    return gfp->sampleSize;
}

/** input samplerate */
int lame_set_in_samplerate( lame_global_flags*  gfp,int in_samplerate )
{
    /* input sample rate in Hz,  default = 44100 Hz */
    gfp->in_samplerate = in_samplerate;

    return 0;
}

int lame_get_in_samplerate( const lame_global_flags*  gfp )
{
    return gfp->in_samplerate;
}
/** set number of samples 
 it's unlikely for this function to return an error */
int lame_set_num_samples( lame_global_flags*  gfp,unsigned long num_samples)
{
    /* default = 2^32-1 */

    gfp->num_samples = num_samples;

    return 0;
}

unsigned long lame_get_num_samples( const lame_global_flags* gfp )
{
    return gfp->num_samples;
}
int lame_set_num_channels( lame_global_flags*  gfp,int num_channels )
{
    /* default = 2 */

    if ( 2 < num_channels || 0 == num_channels )
        return -1;    /* we don't support more than 2 channels */

    gfp->num_channels = num_channels;

    return 0;
}

int lame_get_num_channels( const lame_global_flags*  gfp )
{
    return gfp->num_channels;
}
/** Size of MPEG frame. */
int lame_get_framesize( const lame_global_flags*  gfp )
{
    return gfp->framesize;
}
/** Number of frames encoded so far. */
int lame_get_frameNum( const lame_global_flags*  gfp )
{
    return gfp->frameNum;
}
int fskip(FILE * fp, long offset, int whence)
{
#ifndef PIPE_BUF
    char    buffer[4096];
#else
    char    buffer[PIPE_BUF];
#endif
    size_t     read;

    if (0 == fseek(fp, offset, whence))
        return 0;

    if (whence != SEEK_CUR || offset < 0) {
        fprintf(stderr,
                "fskip problem: Mostly the return status of functions is not evaluate so it is more secure to polute <stderr>.\n");
        return -1;
    }

    while (offset > 0) {
        read = offset > (sizeof(buffer) ? (long)sizeof(buffer) : offset);
        if ((read = fread(buffer, 1, read, fp)) <= 0)
            return -1;
        offset -= read;
    }

    return 0;
}



#define IFF_ID_FORM 0x464f524d /* "FORM" */
#define IFF_ID_AIFF 0x41494646 /* "AIFF" */
#define IFF_ID_AIFC 0x41494643 /* "AIFC" */
#define IFF_ID_COMM 0x434f4d4d /* "COMM" */
#define IFF_ID_SSND 0x53534e44 /* "SSND" */
#define IFF_ID_MPEG 0x4d504547 /* "MPEG" */

#define IFF_ID_NONE 0x4e4f4e45 /* "NONE" */ /* AIFF-C data format */
#define IFF_ID_2CBE 0x74776f73 /* "twos" */ /* AIFF-C data format */
#define IFF_ID_2CLE 0x736f7774 /* "sowt" */ /* AIFF-C data format */

#define WAV_ID_RIFF 0x52494646 /* "RIFF" */
#define WAV_ID_WAVE 0x57415645 /* "WAVE" */
#define WAV_ID_FMT  0x666d7420 /* "fmt " */
#define WAV_ID_DATA 0x64617461 /* "data" */

void ReadBytes (FILE *fp, char *p, int n) 
{
    memset ( p, 0, n );
    fread  ( p, 1, n, fp );
}

signed int ReadByte ( FILE* fp )
{
    int  result = getc (fp);
    return result == EOF  ?  0  :  (signed char) (result & 0xFF);
}

unsigned int ReadByteUnsigned ( FILE* fp )
{
    int  result = getc (fp);
    return result == EOF  ?  0  :  (unsigned char) (result & 0xFF);
}

int  Read16BitsLowHigh ( FILE* fp )
{
    int  low  = ReadByteUnsigned (fp);
    int  high = ReadByte         (fp);
    
    return (high << 8) | low;
}
int  Read16BitsHighLow ( FILE* fp )
{
    int  high = ReadByte         (fp);
    int  low  = ReadByteUnsigned (fp);
    
    return (high << 8) | low;
}
int  Read24BitsHighLow ( FILE* fp )
{
    int  high = ReadByte         (fp);
    int  med  = ReadByteUnsigned (fp);
    int  low  = ReadByteUnsigned (fp);
    
    return (high << 16) | (med << 8) | low;
}
#define	Read32BitsLowHigh(f)	Read32Bits(f)
int  Read32Bits ( FILE* fp )
{
    int  low  = ReadByteUnsigned (fp);
    int  medl = ReadByteUnsigned (fp);
    int  medh = ReadByteUnsigned (fp);
    int  high = ReadByte         (fp);

    return (high << 24) | (medh << 16) | (medl << 8) | low;
}
int  Read32BitsHighLow ( FILE* fp )
{
    int  high = ReadByte         (fp);
    int  medh = ReadByteUnsigned (fp);
    int  medl = ReadByteUnsigned (fp);
    int  low  = ReadByteUnsigned (fp);
    
    return (high << 24) | (medh << 16) | (medl << 8) | low;
}
/****************************************************************
 * Extended precision IEEE floating-point conversion routines
 ****************************************************************/
# define FloatToUnsigned(f)	((unsigned long)(f))
# define UnsignedToFloat(u)	((double)(u))

double ConvertFromIeeeExtended(char* bytes)
{
	double	f;
	long	expon;
	unsigned long hiMant, loMant;

#ifdef	TEST
printf("ConvertFromIEEEExtended(%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx\r",
	(long)bytes[0], (long)bytes[1], (long)bytes[2], (long)bytes[3],
	(long)bytes[4], (long)bytes[5], (long)bytes[6],
	(long)bytes[7], (long)bytes[8], (long)bytes[9]);
#endif

	expon = ((bytes[0] & 0x7F) << 8) | (bytes[1] & 0xFF);
	hiMant	=	((unsigned long)(bytes[2] & 0xFF) << 24)
			|	((unsigned long)(bytes[3] & 0xFF) << 16)
			|	((unsigned long)(bytes[4] & 0xFF) << 8)
			|	((unsigned long)(bytes[5] & 0xFF));
	loMant	=	((unsigned long)(bytes[6] & 0xFF) << 24)
			|	((unsigned long)(bytes[7] & 0xFF) << 16)
			|	((unsigned long)(bytes[8] & 0xFF) << 8)
			|	((unsigned long)(bytes[9] & 0xFF));

        /* This case should also be called if the number is below the smallest
	 * positive double variable */
	if (expon == 0 && hiMant == 0 && loMant == 0) {
		f = 0;
	}
	else {
	        /* This case should also be called if the number is too large to fit into 
		 * a double variable */
	    
		if (expon == 0x7FFF) {	/* Infinity or NaN */
			f = HUGE_VAL;
		}
		else {
			expon -= 16383;
			f  = ldexp(UnsignedToFloat(hiMant), (int) (expon -= 31));
			f += ldexp(UnsignedToFloat(loMant), (int) (expon -= 32));
		}
	}

	if (bytes[0] & 0x80)
		return -f;
	else
		return f;
}
double ReadIeeeExtendedHighLow(FILE *fp)
{
	char	bytes [10];

	ReadBytes ( fp, bytes, 10 );
	return ConvertFromIeeeExtended ( bytes );
}

void Write8Bits(FILE *fp, int i)
{
	putc(i&0xff,fp);
}


void Write16BitsLowHigh(FILE *fp, int i)
{
	putc(i&0xff,fp);
	putc((i>>8)&0xff,fp);
}

void Write16BitsHighLow(FILE *fp, int i)
{
	putc((i>>8)&0xff,fp);
	putc(i&0xff,fp);
}

void Write32Bits(FILE *fp, int i)
{
	Write16BitsLowHigh(fp,(int)(i&0xffffL));
	Write16BitsLowHigh(fp,(int)((i>>16)&0xffffL));
}

void Write32BitsLowHigh(FILE *fp, int i)
{
	Write16BitsLowHigh(fp,(int)(i&0xffffL));
	Write16BitsLowHigh(fp,(int)((i>>16)&0xffffL));
}

void Write32BitsHighLow(FILE *fp, int i)
{
	Write16BitsHighLow(fp,(int)((i>>16)&0xffffL));
	Write16BitsHighLow(fp,(int)(i&0xffffL));
}

/************************************************************************
* aiff_check2
*
* PURPOSE:	Checks AIFF header information to make sure it is valid.
*	        returns 0 on success, 1 on errors
************************************************************************/

int aiff_check2(const char *file_name, IFF_AIFF * const pcm_aiff_data)
{
    if (pcm_aiff_data->sampleType != IFF_ID_SSND) {
        fprintf(stderr, "Sound data is not PCM in '%s'\n", file_name);
        return 1;
    }
    if (pcm_aiff_data->sampleSize != sizeof(short) * CHAR_BIT) {
        fprintf(stderr, "Sound data is not %i bits in '%s'\n",
                sizeof(short) * CHAR_BIT, file_name);
        return 1;
    }
    if (pcm_aiff_data->numChannels != 1 && pcm_aiff_data->numChannels != 2) {
        fprintf(stderr, "Sound data is not mono or stereo in '%s'\n",
                file_name);
        return 1;
    }
    if (pcm_aiff_data->blkAlgn.blockSize != 0) {
        fprintf(stderr, "Block size is not 0 bytes in '%s'\n", file_name);
        return 1;
    }
    /* A bug, since we correctly skip the offset earlier in the code.
    if (pcm_aiff_data->blkAlgn.offset != 0) {
        fprintf(stderr, "Block offset is not 0 bytes in '%s'\n", file_name);
        return 1;
    } */

    return 0;
}

/*****************************************************************************
 *
 *	Read Audio Interchange File Format (AIFF) headers.
 *
 *	By the time we get here the first 32 bits of the file have already been
 *	read, and we're pretty sure that we're looking at an AIFF file.
 *
 *****************************************************************************/
int parse_aiff_header(lame_global_flags * gfp, FILE * sf)
{
    int     is_aiff = 0;
    long    chunkSize = 0, subSize = 0, typeID = 0, dataType = 0;
    IFF_AIFF aiff_info;

    memset(&aiff_info, 0, sizeof(aiff_info));
    chunkSize = Read32BitsHighLow(sf);

    typeID = Read32BitsHighLow(sf);
    if ((typeID != IFF_ID_AIFF)&&(typeID != IFF_ID_AIFC))
        return 0;

    while (chunkSize > 0) {
        int     type = Read32BitsHighLow(sf);
        chunkSize -= 4;

        /* DEBUGF(
           "found chunk type %08x '%4.4s'\n", type, (char*)&type); */

        /* don't use a switch here to make it easier to use 'break' for SSND */
        if (type == IFF_ID_COMM) {
            subSize = Read32BitsHighLow(sf);
            chunkSize -= subSize;

            aiff_info.numChannels = Read16BitsHighLow(sf);
            subSize -= 2;
            aiff_info.numSampleFrames = Read32BitsHighLow(sf);
            subSize -= 4;
            aiff_info.sampleSize = Read16BitsHighLow(sf);
            subSize -= 2;
            aiff_info.sampleRate = ReadIeeeExtendedHighLow(sf);
            subSize -= 10;

            if (typeID == IFF_ID_AIFC) {
                dataType = Read32BitsHighLow(sf);
                subSize -= 4;

                if ((dataType != IFF_ID_2CLE) && 
                    (dataType != IFF_ID_2CBE) &&
                    (dataType != IFF_ID_NONE))
                    return 0;

                if (aiff_info.sampleSize == 16)
                  pcmswapbytes = (!swapbytes == (dataType == IFF_ID_2CLE));
            }
            
            if (fskip(sf, (long) subSize, SEEK_CUR) != 0)
                return 0;
        }
        else if (type == IFF_ID_SSND) {
            subSize = Read32BitsHighLow(sf);
            chunkSize -= subSize;

            aiff_info.blkAlgn.offset = Read32BitsHighLow(sf);
            subSize -= 4;
            aiff_info.blkAlgn.blockSize = Read32BitsHighLow(sf);
            subSize -= 4;

            if (fskip(sf, (long) aiff_info.blkAlgn.offset, SEEK_CUR) != 0)
                return 0;

            aiff_info.sampleType = IFF_ID_SSND;
            is_aiff = 1;

            /* We've found the audio data. Read no further! */
            break;

        }
        else {
            subSize = Read32BitsHighLow(sf);
            chunkSize -= subSize;

            if (fskip(sf, (long) subSize, SEEK_CUR) != 0)
                return 0;
        }
    }

    /* DEBUGF("Parsed AIFF %d\n", is_aiff); */
    if (is_aiff) {
        /* make sure the header is sane */
        if (0 != aiff_check2("name" /*???????????? */ , &aiff_info))
            return 0;
        if( -1 == lame_set_num_channels( gfp, aiff_info.numChannels ) ) {
			printf("*** Failure: Unsupported number of channels: %ud\n",
                     aiff_info.numChannels );
            fprintf( stderr,
                     "*** Failure: Unsupported number of channels: %ud\n",
                     aiff_info.numChannels );
            exit( 1 );
        }
        (void) lame_set_in_samplerate( gfp, (int)aiff_info.sampleRate );
        pcmbitwidth = aiff_info.sampleSize;
		(void) lame_set_samplesize( gfp, aiff_info.sampleSize);
        (void) lame_set_num_samples( gfp, aiff_info.numSampleFrames );
    }
	set_current_aiff(aiff_info);
    return is_aiff;
}


/** Parse file header
*
* parse_file_header
*
* PURPOSE: Read the header from a bytestream.  Try to determine whether
*		   it's a WAV file or AIFF without rewinding, since rewind
*		   doesn't work on pipes and there's a good chance we're reading
*		   from stdin (otherwise we'd probably be using libsndfile).
*
* When this function returns, the file offset will be positioned at the
* beginning of the sound data.
*
************************************************************************/

void parse_file_header(lame_global_flags * gfp, FILE * sf)
{

    int     type = Read32BitsHighLow(sf);
    /*
       DEBUGF(
       "First word of input stream: %08x '%4.4s'\n", type, (char*) &type); 
     */
    count_samples_carefully = 0;
    input_format = sf_raw;

    if (type == WAV_ID_RIFF) {
        /* It's probably a WAV file */
#if 0
        if (parse_wave_header(gfp, sf)) {
            input_format = sf_wave;
            count_samples_carefully = 1;
        } else {
	    fprintf( stderr, "Warning: corrupt or unsupported WAVE format\n"); 
        }
#endif
    }
    else if (type == IFF_ID_FORM) {
        /* It's probably an AIFF file */
        if (parse_aiff_header(gfp, sf)) {
            input_format = sf_aiff;
            count_samples_carefully = 1;
        }
    }
    if (input_format == sf_raw) {
        /*
           ** Assume it's raw PCM.  Since the audio data is assumed to begin
           ** at byte zero, this will unfortunately require seeking.
         */
        if (fseek(sf, 0L, SEEK_SET) != 0) {
            /* ignore errors */
        }
        input_format = sf_raw;
    }
}

lame_global_flags *lame_init(void);
lame_global_flags *lame_init(void)
{
    lame_global_flags *gfp;

    gfp = calloc(1, sizeof(lame_global_flags));
    if (gfp == NULL)
        return NULL;
	/* Kind of a default value for mp3 and aiff */
	gfp->framesize=1152;
    gfp->lame_allocated_gfp = 1;
	num_samples_read = 0;
    return gfp;
}

/************************************************************************
unpack_read_samples - read and unpack signed low-to-high byte or unsigned
                      single byte input. (used for read_samples function)
                      Output integers are stored in the native byte order
                      (little or big endian).  -jd
  in: samples_to_read
      bytes_per_sample
      swap_order    - set for high-to-low byte order input stream
 i/o: pcm_in
 out: sample_buffer  (must be allocated up to samples_to_read upon call)
returns: number of samples read
*/
int unpack_read_samples( const int samples_to_read, const int bytes_per_sample,
		     const int swap_order, int *sample_buffer, FILE *pcm_in )
{
    int samples_read;
    int i;
    int *op;			/* output pointer */
    unsigned char *ip = (unsigned char *) sample_buffer; /* input pointer */
    const int b = sizeof(int) * 8;

#define GA_URS_IFLOOP( ga_urs_bps ) \
    if( bytes_per_sample == ga_urs_bps ) \
	for( i = samples_read * bytes_per_sample; (i -= bytes_per_sample) >=0;)
    

    samples_read = fread( sample_buffer, bytes_per_sample, 
			  samples_to_read, pcm_in);
    op = sample_buffer + samples_read;

    GA_URS_IFLOOP( 1 )
	*--op = (ip[i] ^ 0x80)<<(b-8) | 0x7f<<(b-16);/* convert from unsigned*/
    if( swap_order == 0 ) {
	GA_URS_IFLOOP( 2 )
	    *--op = ip[i]<<(b-16) | ip[i+1]<<(b-8); 
	GA_URS_IFLOOP( 3 )
	    *--op = ip[i]<<(b-24) | ip[i+1]<<(b-16) | ip[i+2]<<(b-8);
	GA_URS_IFLOOP( 4 )
	    *--op = ip[i]<<(b-32) | ip[i+1]<<(b-24) | ip[i+2]<<(b-16) | ip[i+3] << (b-8);
    } else {
	GA_URS_IFLOOP( 2 )
	    *--op = ip[i]<<(b-8) | ip[i+1]<<(b-16); 
	GA_URS_IFLOOP( 3 )
	    *--op = ip[i]<<(b-8) | ip[i+1]<<(b-16) | ip[i+2]<<(b-24);
	GA_URS_IFLOOP( 4 )
	    *--op = ip[i]<<(b-8) | ip[i+1]<<(b-16) | ip[i+2]<<(b-24) | ip[i+3]<<(b-32);
    }
#undef GA_URS_IFLOOP
    return( samples_read );
}



/************************************************************************
*
* read_samples()
*
* PURPOSE:  reads the PCM samples from a file to the buffer
*
*  SEMANTICS:
* Reads #samples_read# number of shorts from #musicin# filepointer
* into #sample_buffer[]#.  Returns the number of samples read.
*
************************************************************************/

int read_samples_pcm(FILE * musicfile, int sample_buffer[2304], int frame_size,
                 int samples_to_read)
{
    int     samples_read;
    int     iswav = (input_format == sf_wave);
    int     hi_lo_order;	/* byte order of input stream */

    if( (32 == pcmbitwidth) || (24 == pcmbitwidth) || (16 == pcmbitwidth) ) {
				/* assume only recognized wav files are */
				/*  in little endian byte order */
	hi_lo_order = (!iswav == !pcmswapbytes);
        samples_read = unpack_read_samples(samples_to_read, pcmbitwidth/8, 
                                           hi_lo_order,sample_buffer, musicfile );
       
    } else if( 8 == pcmbitwidth ) {
	samples_read = unpack_read_samples( samples_to_read, 1, 0,
					    sample_buffer, musicfile );
    } else {
		printf("*** Failure: Only 8, 16, 24 and 32 bit input files supported \n");
        fprintf(stderr, "*** Failure: Only 8, 16, 24 and 32 bit input files supported \n");
        exit(1);
    }
    if (ferror(musicfile)) {
		printf("*** Failure: Error reading input file\n");
        fprintf(stderr, "*** Failure: Error reading input file\n");
        exit(1);
    }

    return samples_read;
}

#define Min(x,y) (x<y?x:y)

/************************************************************************
  get_audio_common - central functionality of get_audio*
    in: gfp
        buffer    output to the int buffer or 16-bit buffer
   out: buffer    int output    (if buffer != NULL)
        buffer16  16-bit output (if buffer == NULL) 
returns: samples read
note: either buffer or buffer16 must be allocated upon call
ecl: modified to read aiff only.
*/
int get_audio_common( lame_global_flags * const gfp,
		  int buffer[2][1152], short buffer16[2][1152] )
{
    int     num_channels = lame_get_num_channels( gfp );
    int     insamp[2 * 1152];
/*    short   buf_tmp16[2][1152];*/
    int     samples_read=0;
    int     framesize;
    int     samples_to_read;
    unsigned int remaining, tmp_num_samples;
    int     i;
    int     *p;

    /* 
     * NOTE: LAME can now handle arbritray size input data packets,
     * so there is no reason to read the input data in chuncks of
     * size "framesize".  EXCEPT:  the LAME graphical frame analyzer 
     * will get out of sync if we read more than framesize worth of data.
     */

    samples_to_read = framesize = lame_get_framesize(gfp);
    /*assert(framesize <= 1152);*/
	if (framesize > 1152)
	{
		printf("*** Failure: Framesize %d > 1152\n",framesize);
		fprintf(stderr,
			"*** Failure: Framesize %d > 1152\n",framesize);
		exit(1);
	}

    /* get num_samples */
    tmp_num_samples = lame_get_num_samples( gfp );

    /* if this flag has been set, then we are carefull to read
     * exactly num_samples and no more.  This is useful for .wav and .aiff
     * files which have id3 or other tags at the end.  Note that if you
     * are using LIBSNDFILE, this is not necessary 
     */
    if (count_samples_carefully) {
        remaining = tmp_num_samples - Min(tmp_num_samples, num_samples_read);
        if (remaining < (unsigned int)framesize && 0 != tmp_num_samples)
            /* in case the input is a FIFO (at least it's reproducible with
               a FIFO) tmp_num_samples may be 0 and therefore remaining
               would be 0, but we need to read some samples, so don't
               change samples_to_read to the wrong value in this case */
            samples_to_read = remaining;
    }

    switch (input_format) {
    case sf_mp1:
    case sf_mp2:
    case sf_mp3:
        break;
    default:
        samples_read =
            read_samples_pcm(musicin, insamp, num_channels * framesize,
                             num_channels * samples_to_read);
	p = insamp + samples_read;
        samples_read /= num_channels;
	if( buffer != NULL ) {	/* output to int buffer */
	    if( num_channels == 2 ) {
		for( i = samples_read; --i >= 0; ) {
		    buffer[1][i] = *--p;
 		    buffer[0][i] = *--p;
		}
	    } else if( num_channels == 1 ) {
		memset( buffer[1], 0, samples_read * sizeof(int) );
		for( i = samples_read; --i >= 0; ) {
 		    buffer[0][i] = *--p;
		}
	    } else
		/*assert(0);*/
		{
			printf("*** Failure: assert 0 reading PCM samples.\n");
			fprintf(stderr,
				"*** Failure: assert 0 reading PCM samples.\n");
			exit(1);
		}
		
	} else {		/* convert from int; output to 16-bit buffer */
	    if( num_channels == 2 ) {
		for( i = samples_read; --i >= 0; ) {
		    buffer16[1][i] = *--p >> (8 * sizeof(int) - 16);
 		    buffer16[0][i] = *--p >> (8 * sizeof(int) - 16);
		}
	    } else if( num_channels == 1 ) {
		memset( buffer16[1], 0, samples_read * sizeof(short) );
		for( i = samples_read; --i >= 0; ) {
 		    buffer16[0][i] = *--p >> (8 * sizeof(int) - 16);
		}
	    } else
		/*assert(0);*/
		{
			printf("*** Failure: assert 0 reading pcm samples\n");
			fprintf(stderr,
				"*** Failure: assert 0 reading pcm samples\n");
			exit(1);
		}
	}
    }
	/* ecl update stats */
	num_samples_read += samples_read;
	gfp->frameNum++;
    return samples_read;
}
/************************************************************************
*
* get_audio()
*
* PURPOSE:  reads a frame of audio data from a file to the buffer,
*   aligns the data for future processing, and separates the
*   left and right channels
*
************************************************************************/
int get_audio( lame_global_flags * const gfp, int buffer[2][1152] )
{
    return( get_audio_common( gfp, buffer, NULL ) );
}

/** Determine AIFF frames, and load into memory. */
unsigned char *getAIFF(const char *fname,FILE *fd,int *fsize)
{
	lame_global_flags *gfp;
    int     Buffer[2][1152];
	int		bufsize=0;
    int     iread,frames, numframes;
	unsigned char *buf;
	char tmpname[FILENAME_MAX];
	FILE	*fdout=NULL;

	if (fd)
		musicin=fd;
	else
		return NULL;
	bufsize=sizeof(Buffer);

	if (output_enable)
	{
		char *obuf;
		int   len;
		if ((obuf=getFiletype(fname))!=NULL)
		{
			len=obuf-fname;
			strncpy(tmpname,fname,len);
			tmpname[len]=0;
			strcat(tmpname,"pcm");
			fdout=fopen(tmpname,"wb");
		}
	}

	/* create a dummy global structure. */
	gfp=lame_init();
	/* Detect, and grab the info out of aiff header. */
	parse_file_header(gfp, fd);
	if (input_format != sf_aiff)
	{
		printf("*** Failure: File %s is not AIFF format\n",fname);
		fprintf(stderr,
			"*** Failure: File %s is not AIFF format\n",fname);
		exit(1);
	}
	numframes=lame_get_num_samples(gfp)/1152+1;
#if 0
	printf("Filename: %s\n",fname);
	printf("Number of samples: %ld\n",lame_get_num_samples(gfp));
	printf("Number of frames: %ld\n",numframes);
	printf("Sample size (PCM Bitwidth): %d\n",pcmbitwidth);
#endif
	if ((buf=malloc(bufsize*numframes))==0)
	{
		printf("*** Failure: Out of memory at %s : %d\n",__FILE__,__LINE__);
		fprintf(stderr,
			"*** Failure: Out of memory at %s : %d\n",__FILE__,__LINE__);
		exit(1);
	}
	frames=0;
	do
	{
		/* read in 'iread' samples */
		iread = get_audio(gfp, Buffer);
		memcpy(&buf[bufsize*frames],Buffer,bufsize);
		frames++;
		if (frames > numframes)
		{
			char *tmpbuf;
			printf("Warning: Frames read, %d, greater than Estimated %d\n",frames,numframes);
			numframes++;
			if ((tmpbuf=realloc(buf,bufsize*frames))==0)
			{
				printf("*** Failure: Out of memory at %s : %d\n",__FILE__,__LINE__);
				fprintf(stderr,
					"*** Failure: Out of memory at %s : %d\n",__FILE__,__LINE__);
				exit(1);
			}
		}
		if (output_enable)
		{
			int i,j;
			/* Output 16 bit PCM */
			for (i=0;i<2;i++)
				for (j=0;j<1152;j++)
				{
					/* 16 bit PCM on LE machine, force byteswap */
					fputc((Buffer[i][j] & 0xff000000) >> 24,fdout);
					fputc((Buffer[i][j] & 0x00ff0000) >> 16,fdout);
				}
		}
	} while(iread);
	/*printf("Frames: %ld, iread %d\n",frames,iread);*/


	if (output_enable)
		fclose(fdout);

	free(gfp);
	return buf;
}

/** Determine file format/color map, load image into buffer */
unsigned char *loadImage(const char *fname,FILE *fd,int *fsize)
{
	unsigned char *buf=NULL;
	char *ftype = getFiletype(fname);

	if ((strcmp(ftype,"Y"))==0)
	{
		int   fsizeU,fsizeV;
		unsigned char  *buf1,*bufU,*bufV;
		char fnameU[FILENAME_MAX],fnameV[FILENAME_MAX];

		buf = loadOpenfile(fname,fsize,fd);

		memset(fnameU,0,FILENAME_MAX);
		strncpy(fnameU,fname,(ftype-fname));
		strcpy(fnameV,fnameU);
		strcat(fnameU,"U");
		strcat(fnameV,"V");
		bufU=loadOpenfile(fnameU,&fsizeU,NULL);
		bufV=loadOpenfile(fnameV,&fsizeV,NULL);
		buf=realloc(buf,(*fsize+fsizeU+fsizeV));
		buf1=buf+*fsize;
		memcpy(buf1,bufU,fsizeU);
		buf1+=fsizeU;
		memcpy(buf1,bufV,fsizeV);
		*fsize += fsizeU+fsizeV;
		free(bufU);
		free(bufV);
	}
	/** @remark YUV encapsulated into a pgm file. 
	The comparison file can be yuv or Y,U,V */
	else if ((strcmp(ftype,"pgm"))==0)
	{
		*fsize=getFilesize(fname);
		read_pgmheader(fd);
		buf = read_pgmdata(fd,fsize);
	}
	/** An uncompressed AIFF file, containing PCM data.
	The comparison file must be aiff. */
	else if ((strcmp(ftype,"aiff"))==0)
	{
		*fsize=getFilesize(fname);
		buf = getAIFF(fname,fd,fsize);
	}
	else if (((strcmp(ftype,"yuv"))==0) ||
		((strcmp(ftype,"bmp"))==0) ||
		((strcmp(ftype,"deskjet"))==0) ||
		((strcmp(ftype,"laserjet"))==0) ||
		((strcmp(ftype,"pdfwrite"))==0) ||
		((strstr(ftype,"cmyk"))!=NULL) ||
		((strcmp(ftype,"tiff"))==0))
	{
		buf = loadOpenfile(fname,fsize,fd);
	}
	else
	{
		printf("*** Failure: Unsupported file type: %s\n",ftype);
		fprintf(stderr,
			"*** Failure: Unsupported file type: %s\n",ftype);
		exit(1);
	}
	return buf;	
}
/** Read PGM header information, and load global XDIM,YDIM. */
int read_pgmheader(FILE* handle)
{
    int bytes,xsize,ysize,depth;
    char dummy[2];
	
    bytes = fread(dummy,1,2,handle);

    if ( (bytes < 2) || (dummy[0] != 'P') || (dummy[1] != '5' ))
        return 1;
    fscanf(handle,"%d %d %d",&xsize,&ysize,&depth);
    if ( (XDIM==0) || (YDIM==0) )
    {
		if (xsize==ysize)
			ysize=xsize*3/2;
		XDIM=xsize;
		YDIM=ysize;
    }
    return 0;
}
#define IMAGE_SIZE(x,y) ((x)*(y)*3/2)
/** Read YUV encoded as PGM data file. */
unsigned char *read_pgmdata(FILE* handle,int *fsize)
{
    int asize,esize;
    char dummy;
	unsigned char *image;

	image=malloc(IMAGE_SIZE(XDIM,YDIM));
	asize=fread(image,1,IMAGE_SIZE(XDIM,YDIM),handle);
	esize=getExpectedsize(XDIM,YDIM);
	if (asize != esize)
	{
		printf("Size mismatch: expected %d, actual %d\n",esize,asize);
	}
	*fsize=asize;

	/* clears some problems */
    fread(&dummy,1,1,handle);
	fclose(handle);
	return image;
}
/** Read YUV12 image file given a correct X and Y
@param handle An open image file.
@param image A storage area of at least XDIM*YDIM*3/2.
@retval 0 Success, 1 Fail.
*/
int read_yuvdata(FILE* handle, unsigned char *image)
{
	/** Start of U
    unsigned char* buff1_ptr2 = image + XDIM*YDIM;
	*/
	/** Start of V
    unsigned char* buff1_ptr3 = image + XDIM*YDIM + XDIM/2*YDIM/2;
	*/

    if (fread(image,XDIM,YDIM*3/2,handle) != (size_t)YDIM*3/2)
        return 1;
    else
        return 0;
}
/** Write YUV12 as viewable portable gray map comparison file. */
int writePGMcomp(char *filename, unsigned char *image1, unsigned char *image2, int output_image, char *filetype)
{
    FILE	*filehandle;
	int		rv=0,i,len=XDIM*YDIM*3/2;
	unsigned char *imageZ=malloc(len);
	char	*myfilename=malloc(strlen(filename)+strlen(filetype)+3);

	strcpy(myfilename,filename);
	strcat(myfilename,"-");
	strcat(myfilename,filetype);

    if ((filehandle=fopen(myfilename,"wb"))!=NULL)
	{
        fprintf(filehandle,"P5\n\n");
		if (strcmp(filetype,"yuv")==0)
			/* size for two vertically stacked YUV images */
			fprintf(filehandle,"%d %d 255\n",XDIM,(YDIM*3/2)*3);
		else
		{
			fprintf(filehandle,"%d %d 255\n",XDIM,YDIM*3);
			len=XDIM*YDIM;
		}
        fwrite(image1,len,1,filehandle);
        fwrite(image2,len,1,filehandle);
		/**
		 * The high intensity error method is suitable for showing
		 * files that do not have many errors. It can be varied to be
		 * triggered on larger difference errors as needed.
		 * This is the most useful form for our data sets.
		 *	if (image1[i] == image2[i])
		 *		imageZ[i] = 0;
		 *	else
		 *		imageZ[i] = 0xFF;
		 *
		 * The subtracted image can be used, but it's not too visible. It is
		 * good for quickly finding artifacts, or bugs, when looking through
		 * a large number of frames.
		 * imageZ[i]=abs(image1[i]-image2[i]);
		 *
		 * The Error Image is a slightly more viewable form of the
		 * subtracted image. e(i,j)=2(f(i,j)-F(i,j))+128
		 *	imageZ[i] = 2*(image1[i]-image2[i])+128;
		 * 
		 */
		for (i=0;i<len;i++)
			switch (output_image)
			{
			case 1:
				if (image1[i] == image2[i])
		 			imageZ[i] = 0;
		 		else
		 			imageZ[i] = 0xFF;
			break;
			case 2:
				imageZ[i]=abs(image1[i]-image2[i]);
				break;
			case 3:
				imageZ[i] = 2*(image1[i]-image2[i])+128;
				break;
			default:
				printf("ERROR: Invalid Error Image format (-o)\n");
				Usage();
			}
        fwrite(imageZ,len,1,filehandle);
        fclose(filehandle);
        rv = 0;
    }
    else
        rv = 1;

	free(imageZ);
	fprintf(stderr,"Comparison type %d in: %s\n",
				output_enable,myfilename);
	free(myfilename);
	return rv;
}
/** Get the expected image size based on x,y, and filetype.

File Formats:
- YUV12 consists of a Y region, width*height, and two quarter sampled
regions, width/2 * height/2 for U and V. This format does not include
width and height information, and so this must be supplied by the user.
- PGM consists of a YUV12 file with a PGM header.
- AIFF consists of an AIFF or AIFFC header with PCM data.
*/
int getExpectedsize(int x, int y)
{
	int rv;
	/* Add fname argument for multitype support */
	rv = x*y + x*y/2;
	return rv;
}
/** Calculate estimated sample variance. */
double sampleVariance(double data[],int elements)
{
	int	i;
	double di;
	double sum=0;
	double sum_sqr=0;
	double variance;
	
	if (!elements) return 0;

	for (i=0;i<elements;i++)
	{
		sum += data[i];
		sum_sqr += ( data[i] * data[i] );
	}
	di=i*1.0;
	variance = ((di * sum_sqr) - (sum * sum))/(di*(di-1.0));
	return variance;
}
/** Calculate Arithmetic Mean (Average), and Variance.

Swiss army knife, calculate all summaries here in one loop.

I don't trust my math so:
http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance
is wrong, and others have the same page:)
http://mindprod.com/jgloss/sd.html
Knuth is right, and more efficient.
@note this is a sample variance, not a population variance. Standard
Deviation is the square root of this, but for our purposes variance
is better to differentiate samples.
 */
double arithMean(double data[],int elements,double *variance,double *minimum)
{
	int	i;
	double  newavg=0.0,avg=0.0,var=0.0,di=0;
	double	min=data[0];

	/** Add single frame case. */
	if (!elements) 
	{
			*variance = 0.0;
			*minimum=min;
			return min;
	}

	for (i=0;i<elements;i++)
	{
		if (data[i] < min) min=data[i];
		di=i*1.0;
		newavg = avg + ( data[ i ] - avg) / (di + 1.0); 
		var += ( data[ i ] - avg) * (data [ i ] - newavg);
		avg=newavg;
	}
	/* start at 0, di is elements-1 */
	*variance = var/di;
	*minimum=min;
	return avg;
}

/** Calculate Geometric Mean. 
Overflows to infinity at 2**64, if we need to use this convert
to running geometric mean algorithm. */
double geoMean(double array[],int elements)
{
	int		i;
	double	total=1,delements;
	
	if (!elements) return 0;
	/* compiler doesn't convert d elements even if you cast them */
	delements=1.0/(double)elements;

	for (i=0;i<elements;i++)
	{
		/* eliminate invalid arrays */
		if (array[i]==0) return 0;
		total *= array[i];
	}
	total=pow(total,delements);
	return total;
}

/** Given file012.yuv, return file%.3d.yuv */
char *getSprintf(const char *fname)
{
	char buf[FILENAME_MAX]={'\0',};
	char *ftype;
	
	if (!fname || !*fname) return NULL;

	ftype=getFiletype(fname);

	/* SG: ghostscript files start with gs8 */
	/* each page is to be tested.			*/
	if (strstr(fname,"gs-output")!=NULL)
		return (char *)fname;
	/* back up to the '.' */
	ftype--;
	strncpy(buf,fname,(ftype-fname-3));
	strcat(buf,"%.3d");
	strcat(buf,ftype);
	return (char *)strdup(buf);
}

/** Get Image or die. */
unsigned char *getImage(char *fname,char **actual_fname,int *actual_size)
{
	FILE *fd;

	if ((fd = psnrfind_file(fname,"rb",actual_fname))==NULL)
	{
		printf("Failure: File %s not found\n",fname);
		Usage();
	}
	return loadImage(*actual_fname,fd,actual_size);
}
/** Standard PSNR output printing. */
void psnr_print(double *array,
				int    index,
				int    numframes,
				int    allzero,
				int    exactmatch,
				char   *media_type)
{
	double score,samplevariance,minimum;

	if (index != -1 && (index || numframes==1))
		score=arithMean(array,index,&samplevariance,&minimum);
	else
	{
		score=0;
		samplevariance=0;
		minimum=0;
	}
	printf("%s[s],%d\n",media_type,numframes);
	if (numframes = (exactmatch+allzero)) {
		printf("Arithmetic Mean,999.99\n");
		printf("Variance,0.0\n");
		printf("Minimum,999.99\n");
	} else {
		printf("Arithmetic Mean,%f\n",score);
		printf("Variance,%f\n",samplevariance);
		printf("Minimum,%f\n",minimum);
	}
	printf("All Zero %s[s],%d\n",media_type,allzero);
	printf("Exact Match %s[s],%d\n",media_type,exactmatch);
}
/** Output PGM file comparison of images.
The filename will be based off of the filename, 
with the pgm file type.
*/
void psnr_output_enable(char *actual_fname1,
						unsigned char *img1,
						unsigned char *img2)
{
	if (output_enable)
	{
		char *buf;
		int   len;
		char tmpname[FILENAME_MAX];
		if ((buf=getFiletype(actual_fname1))!=NULL)
		{
			len=buf-actual_fname1;
			strncpy(tmpname,actual_fname1,len);
			tmpname[len]=0;
			strcat(tmpname,"pgm");
			if (writePGMcomp(tmpname,img1,img2,output_enable,buf))
				fprintf(stderr,"Error in comparison output.\n");
		}
	}
}

/** Process psnr for aiff file. */
int psnr_aiff(void)
{
	int actual_size1,actual_size2;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1,*img2;
	double *array;
	int		i,index,exactmatch,allzero;

	int Buffer1[2][1152];
	int Buffer2[2][1152];
	int ZeroBuffer[2][1152];
	int bufsize=sizeof(Buffer1);
	unsigned char *tmpimg1,*tmpimg2;
	IFF_AIFF aiff1,aiff2;

	memset(&ZeroBuffer,0,bufsize);

	current_iff_aiff=&aiff1;
	img1=getImage(fname1,&actual_fname1,&actual_size1);
	current_iff_aiff=&aiff2;
	img2=getImage(fname2,&actual_fname2,&actual_size2);
	print_iff_aiff(aiff2);
		/*printf("powpow: %lf\n",pow(pow(2,aiff1.sampleSize)-1,2));*/
	if (!compare_iff_aiff(aiff1,aiff2))
	{
		printf("Error: AIFF headers are incompatible: %s, %s\n",fname1,fname2);
		printf("***%s\n",fname1);
		print_iff_aiff(aiff1);
		printf("***%s\n",fname2);
		print_iff_aiff(aiff2);
		return 1;
	}
	nframes=aiff1.numSampleFrames/1152+1;
	array = malloc((nframes+1)*sizeof(*array));

		/* csv title */
		printf("Frame,PSNR\n");

		/* i tracks the number of frames, index is the number of non-zero frames. */
		for (	i=0,index=0,exactmatch=0,allzero=0,tmpimg1=img1,tmpimg2=img2;
				i<nframes;
				i++,index++)
		{
			memcpy(&Buffer1,tmpimg1,bufsize);
			memcpy(&Buffer2,tmpimg2,bufsize);
			/* Handle All Zero and Exact Match cases. */
			if (((memcmp(&Buffer1,&ZeroBuffer,bufsize))==0) &&
				((memcmp(&Buffer1,&ZeroBuffer,bufsize))==0))
			{
				allzero++;
				index--;
			}
			else if ((memcmp(&Buffer1,&Buffer2,bufsize))==0)
			{
				exactmatch++;
				index--;
			}
			else
			{
				array[index]=PSNR_frame(Buffer1,Buffer2,(double)aiff1.sampleSize);
				printf("Frame %d, %f\n",index,array[index]);
			}
			tmpimg1+=bufsize;
			tmpimg2+=bufsize;
		}
#if 0
		/* Overflow on AIFF, but not needed by Consumer Group.
		score=geoMean(array,index);
		printf("Geometric Mean,%f\n",score);
		*/
		if (index)
			score=geoMean(array,index);
		else
			score=0;
		printf("Geometric Mean,%f\n",score);
#endif
	psnr_print(array,index,
		nframes,allzero,exactmatch,"Frame");
	psnr_output_enable(actual_fname1,img1,img2);
	free(actual_fname1);
	free(actual_fname2);
	free(img1);
	free(img2);

	return 0;
}
/** Process psnr for 256 color bmp. */
int psnr_bmp256(void)
{
	int actual_size1,actual_size2,expected_size;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1,*img2,*zeroimg;
	double *array=NULL;
	int		index=0,exactmatch=0,allzero=0;

	img1=getImage(fname1,&actual_fname1,&actual_size1);
	img2=getImage(fname2,&actual_fname2,&actual_size2);

	/* Do bmp expected size. */
	expected_size = actual_size1;
	/* Handle All Zero and Exact Match cases. */
	/* Do bmp expected size. */
	if (actual_size1 != actual_size2)
	{
		printf("*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		fprintf(stderr,
			"*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		exit(1);
	}

	/* csv title */
	printf("Page,PSNR\n");
	nframes=1;

	/* Set up array to hold psnr values */
	if ((array = malloc((nframes+1)*sizeof(*array)))==NULL)
	{
		printf("*** Failure: Out of memory\n");
		fprintf(stderr,"*** Failure: Out of memory\n");
		exit(1);
	}
	zeroimg = calloc(expected_size,1);

	/** @note Index is intended to be -1 for single frame matching files.
	    This triggers psnr_print to initialize variables to 0.
	 */
	/* Handle All Zero and Exact Match cases. */
	if (((memcmp(img1,zeroimg,expected_size))==0) &&
		((memcmp(img2,zeroimg,expected_size))==0))
	{
		allzero++;
		index--;
	}
	else if ((memcmp(img1,img2,expected_size))==0)
	{
		exactmatch++;
		index--;
	}
	else
	{
		array[index]=SNR(actual_size1,nframes,img1,actual_size2,img2,actual_size1 );
		printf("SNR %d, %f\n",index,array[index]);
		array[index]=PSNR(actual_size1,nframes,img1,actual_size2,img2,actual_size1 );
		printf("Page %d, %f\n",index,array[index]);
	}
	psnr_print(array,index,
		nframes,allzero,exactmatch,"Page");
	/* probably a subroutine later on, define locals here. */
	psnr_output_enable(actual_fname1,img1,img2);
	free(array);
	free(zeroimg);
	free(actual_fname1);
	free(actual_fname2);
	free(img1);
	free(img2);
	return 0;
}
/** Process psnr for packed bits. */
int psnr_packbits(int numbits)
{
	int actual_size1,actual_size2,expected_size;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1,*img2,*zeroimg;
	double *array=NULL;
	int		index=0,exactmatch=0,allzero=0;

	img1=getImage(fname1,&actual_fname1,&actual_size1);
	img2=getImage(fname2,&actual_fname2,&actual_size2);

	/* Do bmp expected size. */
	expected_size = actual_size1;
	/* Handle All Zero and Exact Match cases. */
	/* Do bmp expected size. */
	if (actual_size1 != actual_size2)
	{
		printf("*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		fprintf(stderr,
			"*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		exit(1);
	}

	/* csv title */
	printf("Page,PSNR\n");
	nframes=1;

	/* Set up array to hold psnr values */
	if ((array = malloc((nframes+1)*sizeof(*array)))==NULL)
	{
		printf("*** Failure: Out of memory\n");
		fprintf(stderr,"*** Failure: Out of memory\n");
		exit(1);
	}
	zeroimg = calloc(expected_size,1);

	/** @note Index is intended to be -1 for single frame matching files.
	    This triggers psnr_print to initialize variables to 0.
	 */
	/* Handle All Zero and Exact Match cases. */
	if (((memcmp(img1,zeroimg,expected_size))==0) &&
		((memcmp(img2,zeroimg,expected_size))==0))
	{
		allzero++;
		index--;
	}
	else if ((memcmp(img1,img2,expected_size))==0)
	{
		exactmatch++;
		index--;
	}
	else
	{
		array[index]=SNRpackedbits(actual_size1,nframes,img1,actual_size2,img2,actual_size1,numbits );
		printf("SNR %d, %f\n",index,array[index]);
		array[index]=PSNRpackedbits(actual_size1,nframes,img1,actual_size2,img2,actual_size1,numbits );
		printf("Page %d, %f\n",index,array[index]);
	}
	psnr_print(array,index,
		nframes,allzero,exactmatch,"Page");
	/* probably a subroutine later on, define locals here. */
	psnr_output_enable(actual_fname1,img1,img2);
	free(array);
	free(zeroimg);
	free(actual_fname1);
	free(actual_fname2);
	free(img1);
	free(img2);
	return 0;
}
/** packed CMYK format. A raw raster image that should match in size, and have high psnr.. */
int psnr_cmyk(char *type)
{
	int numbits;
	while (*type) {
		if (*type >'0' && *type<'9') {
			numbits=*type-'0';
			break;
		}
		type++;
	}
	return psnr_packbits(numbits);
}


/** CMYK format. A raw raster image that should match in size, and have high psnr.. */
int psnr_spotcmyk(void)
{
	return psnr_bmp256();
}
/** PCL 3 Format. A binary format that should size out the same. */
int psnr_deskjet(void)
{
	return psnr_bmp256();
}
/** PCL Variant Format, some version level differences between printers.
 A binary format that should size out the same. */
int psnr_laserjet(void)
{
	return psnr_bmp256();
}

/** Tiff G4 Fax, A binary format that does not match on embedded targets.
The slight differences are in both header / data locations within the file,
and small pixel differences within the file. These differences are not visible,
except with an error image.

This format will be converted to a raster for a full PSNR image test. The
PSNR usage as a binary comparison does not work in this case. */
int psnr_tiffg4(void)
{
	FILE *fd;
	TIFF *tif1, *tif2;
	int actual_size1,actual_size2,expected_size;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1=NULL,*img2=NULL,*zeroimg;
	double *array=NULL;
	int		index=0,exactmatch=0,allzero=0;

	/** tiffcmp -l (list all errors). */
	stoponfirstdiff = 0;
	/** We hijacked the Date/Time tag in libtiff,
	so we will stop on the others that we care about.
	*/
	stoponfirsttag = 1;

	/**
	 * In this case, we are processing a single file. 
	 * fname1 and fname2 are good.
	 * We do need to do a pathfind file that was done
	 * internal to getImage.
	 */

	if ((fd = psnrfind_file(fname1,"rb",&actual_fname1))==NULL)
		psnr_abort("File %s not found.\n",fname1);
	fclose(fd);
	if ((fd = psnrfind_file(fname2,"rb",&actual_fname2))==NULL)
		psnr_abort("File %s not found.\n",fname2);
	fclose(fd);
	
	/**
	 * We need to use the libtiff I/O routines, so reopen.
	 * We also do not support directories and wildcards from
	 * libtiff, so the first open blocks this from coming here.
	 * There is an fdopen, but not the reverse.
	 */
	if ((tif1 = TIFFOpen(actual_fname1, "r")) == NULL)
		psnr_abort("TIFF File %s not found.\n",actual_fname1);
	if ((tif2 = TIFFOpen(actual_fname2, "r")) == NULL)
		psnr_abort("TIFF File %s not found.\n",actual_fname2);

	if (((tiffcmp(tif1, tif2, &img1, &img2, &expected_size))==0) ||
		(img1==NULL) || (img2==NULL))
		psnr_abort("TIFF compare error.\n");


	/* csv title */
	printf("Page,PSNR\n");
	nframes=1;

	/* Set up array to hold psnr values */
	if ((array = malloc((nframes+1)*sizeof(*array)))==NULL)
	{
		printf("*** Failure: Out of memory\n");
		fprintf(stderr,"*** Failure: Out of memory\n");
		exit(1);
	}
	zeroimg = calloc(expected_size,1);

	/* Handle All Zero and Exact Match cases. */
	if (((memcmp(img1,zeroimg,expected_size))==0) &&
		((memcmp(img2,zeroimg,expected_size))==0))
	{
		allzero++;
		index--;
	}
	else if ((memcmp(img1,img2,expected_size))==0)
	{
		exactmatch++;
		index--;
	}
	else
	{
		/** \todo For TIFF Seperated, psnr should already handle it. Verify with debug. */
		actual_size1=actual_size2=expected_size;
		array[index]=PSNR(actual_size1,nframes,img1,actual_size2,img2,actual_size1 );
		printf("Page %d, %f\n",index,array[index]);
	}
	psnr_print(array,index,
		nframes,allzero,exactmatch,"Page");
	/* probably a subroutine later on, define locals here. */
	psnr_output_enable(actual_fname1,img1,img2);
	free(array);
	free(zeroimg);
	free(actual_fname1);
	free(actual_fname2);
	free(img1);
	free(img2);
	return 0;
}

/** Strip Date/Time from PDF.*/
int pdfStrip(unsigned char *img1,int actual_size1)
{
	int		i,iStrip,strip_size1=actual_size1,Sflag;
	unsigned char* img1Strip;
	const char *key1="/CreationDate(";
	int lenkey1=strlen(key1);

	if ((img1Strip=malloc(actual_size1))==0)
	{
		printf("ERROR: out of memory - img1Strip.\n");
		fprintf(stderr,"ERROR: out of memory - img1Strip.\n");
	}
	/*
	\\CreationDate(D:xxxx)
	\\ModDate(D:xxxx)
	/ID [xxxx]
	*/
	for (i=0,iStrip=0,Sflag=0;i<actual_size1;i++,iStrip++)
	{
		if (!strncmp((const char *) &img1[i],key1,lenkey1))
		{
			if (Sflag)
			{
				printf("Failure: PDF CreationDate.\n");
				fprintf(stderr,"Failure: PDF CreationDate.\n");
				exit(1);
			}
			else
				Sflag=1;
		}
		else if (!strncmp("/ModDate(",(const char *)&img1[i],strlen("/ModDate(")))
		{
			if (Sflag)
			{
				printf("Failure: PDF ModDate.\n");
				fprintf(stderr,"Failure: PDF ModDate.\n");
				exit(1);
			}
			else
				Sflag=1;
		}
		else if (!strncmp("/ID",(const char *)&img1[i],strlen("/ID")))
		{
			if (Sflag)
			{
				printf("Failure: PDF ID.\n");
				fprintf(stderr,"Failure: PDF ID.\n");
				exit(1);
			}
			else
				Sflag=2;
		}

		/* Strip inside delimiters. */
		if (Sflag)
		{
			iStrip--;
			strip_size1--;
		}
		/* if iStrip==0, start of file...not needed. */
		img1Strip[iStrip] = img1[i];

		/* Check for terminators ) Sflag=1, ] Sflag=2 */
		if (Sflag)
		{
			if (Sflag == 1 && img1[i] == ')')
				Sflag=0;
			else if (Sflag == 2 && img1[i] == 0x0A /*']'*/)
				Sflag=0;
		}
	}
	/* Caller shouldn't mind if we do this...*/
	memcpy(img1,img1Strip,strip_size1);
	free(img1Strip);
	return (int) strip_size1;
}


/** Strip everything except binary stream/endstream sections.*/
int pdfStripBinary(unsigned char *img1,int actual_size1)
{
	int		i,iStrip,strip_size1=actual_size1,Sflag;
	unsigned char* img1Strip;
	const char *key1="stream";
	int lenkey1=strlen(key1);
	const char *endkey1="endstream";
	int lenendkey1=strlen(endkey1);

	if ((img1Strip=malloc(actual_size1))==0)
	{
		printf("ERROR: out of memory - img1Strip.\n");
		fprintf(stderr,"ERROR: out of memory - img1Strip.\n");
	}
	/*
	\\CreationDate(D:xxxx)
	\\ModDate(D:xxxx)
	/ID [xxxx]
	*/
	/* stream/endstream start stripping. */
	for (i=0,iStrip=0,Sflag=1;i<actual_size1;i++,iStrip++)
	{
		if (Sflag && !strncmp((const char *)&img1[i],key1,lenkey1))
		{
				Sflag=0;
		}
		/* Strip inside delimiters. */
		if (Sflag)
		{
			iStrip--;
			strip_size1--;
		}
		/* if iStrip==0, start of file...not needed. */
		img1Strip[iStrip] = img1[i];

		/* Check for terminators ) Sflag=1, ] Sflag=2 */
		if (!strncmp((const char *)&img1[i],endkey1,lenendkey1))
		{
			if (Sflag)
			{
				printf("Failure: PDF endstream.\n");
				fprintf(stderr,"Failure: PDF endstream.\n");
				exit(1);
			}
			else
				Sflag=1;
		}
	}
	/* Caller shouldn't mind if we do this...*/
	memcpy(img1,img1Strip,strip_size1);
	/** \note avoid some memory problems, not too much waste. free(img1Strip); */
	return (int) strip_size1;
}

/** pdf, with small tag areas for fonts. should align from gs or error. */
int psnr_pdfwrite(void)
{
	int actual_size1,actual_size2,expected_size;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1,*img2,*zeroimg;
	double *array=NULL;
	int		index=0,exactmatch=0,allzero=0;

	img1=getImage(fname1,&actual_fname1,&actual_size1);
	img2=getImage(fname2,&actual_fname2,&actual_size2);

	/* Handle All Zero and Exact Match cases. */
	/* Do expected size until we can prove header mismatches are ok.
	if (abs(actual_size1 - actual_size2) > 4)
	{
		printf("*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		fprintf(stderr,
			"*** Failure: File size mismatch:\n\t%s\t%d\n\t%s\t%d\n",
			actual_fname1, actual_size1, actual_fname2, actual_size2);
		exit(1);
	}
	*/

	/** \remark Strip date/time stamp which will be changed
	when timer routines are available. */
	actual_size1 = pdfStrip(img1,actual_size1);
	actual_size2 = pdfStrip(img2,actual_size2);
	expected_size = actual_size1<actual_size2?actual_size1:actual_size2;


	/* csv title */
	printf("Page,PSNR\n"); 
	nframes=1;

	/* Set up array to hold psnr values */
	if ((array = malloc((nframes+1)*sizeof(*array)))==NULL)
	{
		printf("*** Failure: Out of memory\n");
		fprintf(stderr,"*** Failure: Out of memory\n");
		exit(1);
	}
	zeroimg = calloc(expected_size,1);

	/* Handle All Zero and Exact Match cases. */
	if (((memcmp(img1,zeroimg,expected_size))==0) &&
		((memcmp(img2,zeroimg,expected_size))==0))
	{
		allzero++;
		index--;
	}
	else if ((memcmp(img1,img2,expected_size))==0)
	{
		exactmatch++;
		index--;
	}
	else
	{
		array[index]=PSNR(expected_size,nframes,img1,expected_size,img2,expected_size );
		printf("Page %d, %f\n",index,array[index]);
	}
	psnr_print(array,index,
		nframes,allzero,exactmatch,"Page");
	psnr_output_enable(actual_fname1,img1,img2);
	free(array);
	free(zeroimg);
	free(actual_fname1);
	free(actual_fname2);
	free(img1);
	free(img2);
	return 0;
}

/** Main PSNR driver.

Image Stride: When graphics hardware or GDI allocates a memory buffer
for bitmaps, it often pads the rows with extra bytes in order to align
them on some boundary.  The width of the image, in bytes, plus the
width of the extra padding, is called the stride.  Another way to think
of it is that stride gives the number of bytes it takes to advance from
the beginning of one row in an image to the beginning of the next row.

Never assume that stride is equal to the image width, even with 32-bit
pixel formats, because many graphics cards require an alignment that is
64 bits or greater.

*/
int main(int argc, char *argv[])
{
	int	expected_size=0;
	int actual_size1,actual_size2;
	char *actual_fname1=NULL;
	char *actual_fname2=NULL;
	unsigned char *img1,*img2,*zeroimg;
	/*int  stride1,stride2;*/
	double *array,score;
	int		i,index,exactmatch,allzero;
	char *f1_sprintf,fn1[FILENAME_MAX];
	char *f2_sprintf,fn2[FILENAME_MAX];
	long	testendian=0;

    testendian = LONG_PACK('F','O','O','S');
	if(*((char *)(&testendian)) == 'F')
		bigendian = 1;
	else
		bigendian = 0;



	Process_Options(argc,argv);
	path=mpeg2dec_path;
	f1_sprintf=getSprintf(fname1);
	f2_sprintf=getSprintf(fname2);

	/* Process single file cases */
	if ((f1_sprintf==fname1) && (f2_sprintf == fname2))
	{
		char *ftype1=getFiletype(fname1);
		char *ftype2=getFiletype(fname2);
		int   rc=0;
		if (strcmp(ftype1,ftype2))
		{
			printf("*** Failure: Filetype mismatch: %s, %s\n",
				fname1, fname2);
			rc=1;
		}
		else if (!strcmp(ftype1,"aiff"))
			rc=psnr_aiff();
		else if (!strcmp(ftype1,"bmp"))
			rc=psnr_bmp256();
		else if (!strcmp(ftype1,"deskjet"))
			rc=psnr_deskjet();
		else if (!strcmp(ftype1,"laserjet"))
			rc=psnr_laserjet();
		else if (!strcmp(ftype1,"tiff"))
			rc=psnr_tiffg4();
		else if (!strcmp(ftype1,"pdfwrite"))
			rc=psnr_pdfwrite();
		else if (strstr(ftype1,"cmyk")!=NULL) {
			rc=psnr_cmyk(ftype1);
		}
		else
		{
			printf("*** Failure: Unsupported filetype %s\n",ftype1);
			fprintf(stderr,
				"*** Failure: Unsupported filetype %s\n",ftype1);
			rc=1;
		}
		return rc;
	}

	/* csv title */
	printf("Frame,PSNR\n");

	/* Set up array to hold psnr values */
	if ((array = malloc((nframes+1)*sizeof(*array)))==NULL)
	{
		printf("*** Failure: Out of memory\n");
		fprintf(stderr,"*** Failure: Out of memory\n");
		exit(1);
	}

	for (	i=0,index=0,exactmatch=0,allzero=0;
			i<nframes;
			i++,index++)
	{
		/* Build the fnames, assume fname2 is 0 based */
		sprintf(fn1,f1_sprintf,i+frame0);
		sprintf(fn2,f2_sprintf,i);
		img1=getImage(fn1,&actual_fname1,&actual_size1);
		img2=getImage(fn2,&actual_fname2,&actual_size2);

		/* Last sanity check */
		if ((actual_size1 != actual_size2) ||
			((expected_size=getExpectedsize(XDIM,YDIM)) != actual_size1))
		{
			printf("*** Failure: YUV12 Size mismatch (%d,%d):\nExpected size: %d, Size %s : %d, Size %s : %d\n",
				XDIM,YDIM,expected_size,actual_fname1,actual_size1,actual_fname2,actual_size2);
			fprintf(stderr,
				"*** Failure: YUV12 Size mismatch (%d,%d):\nExpected size: %d, Size %s : %d, Size %s : %d\n",
				XDIM,YDIM,expected_size,actual_fname1,actual_size1,actual_fname2,actual_size2);
			exit(1);
		}

		zeroimg = calloc(expected_size,1);

		/* Handle All Zero and Exact Match cases. */
		if (((memcmp(img1,zeroimg,expected_size))==0) &&
			((memcmp(img2,zeroimg,expected_size))==0))
		{
			allzero++;
			index--;
		}
		else if ((memcmp(img1,img2,expected_size))==0)
		{
			exactmatch++;
			index--;
		}
		else
		{
			array[index]=PSNR(XDIM,YDIM,img1,XDIM,img2,XDIM );
			printf("Frame %d, %f\n",index,array[index]);
		}

		free(zeroimg);

		/* probably a subroutine later on, define locals here. */
		psnr_output_enable(actual_fname1,img1,img2);
		free(actual_fname1);
		free(actual_fname2);
		free(img1);
		free(img2);
	}

	
	if (index)
		score=geoMean(array,index);
	else
		score=0;
	printf("Geometric Mean,%f\n",score);

	psnr_print(array,index,
		nframes,allzero,exactmatch,"Frame");

	free(array);
	free(f1_sprintf);
	free(f2_sprintf);

	return 0;
}
/** @} */
/** @} */
