#ifndef PROTO_H
#define PROTO_H

/**
 * @file 
 * @brief All prototypes grouped by file.
 *
 * A reference file for all globally defined functions and procedures.
 *
 * @remark This file is automatically generated with "make proto". DO NOT EDIT
 */

/** @addtogroup eembc_utilities Version 2 Benchmark Utilities
 * @{ */
/** @addtogroup PROTO_H PROTO Application Program Interface
 * @{ */

/* The following definitions come from  psnr.c  */

void Usage(void);
void psnr_abort( const char *fmt, ... );
void Process_Options(int argc,char *argv[]);
int checkswap(int swap);
double absdistq_frame(
				int buf1[2][1152],
				int buf2[2][1152]);
double absdistq(int x,int y, 
				unsigned char* buf1, int stride1, 
				unsigned char* buf2, int stride2);
double absdistqn(int x,int y, 
				unsigned char* buf1, int stride1, 
				unsigned char* buf2, int stride2, int numbits);
double noise_power(int x,int y, 
				unsigned char* ref, 
				unsigned char* actual, int numbits);
double signal_power(int x,int y, 
				unsigned char* signal, int numbits);
double PSNR_frame(int buf1[2][1152],int buf2[2][1152],double datawidth);
double PSNR(int x,int y, 
			unsigned char* buf1, int stride1, 
			unsigned char* buf2, int stride2);
double PSNRpackedbits(int x,int y, 
			unsigned char* buf1, int stride1, 
			unsigned char* buf2, int stride2,int numbits);
double SNRpackedbits(int x,int y, 
			unsigned char* actual, int stride1, 
			unsigned char* ref, int stride2,int numbits);
double SNR(int x,int y, 
			unsigned char* actual, int stride1, 
			unsigned char* ref, int stride2) ;
FILE *psnrfind_file(const char *filename, const char *filemode,char **actualname);
int getFilesize(const char *fname);
char *getFiletype(const char *fname);
unsigned char *loadOpenfile(const char *fname,int *fsize,FILE *fd);
int set_current_aiff(IFF_AIFF iff);
int print_iff_aiff(IFF_AIFF iff);
int compare_iff_aiff(IFF_AIFF iff0, IFF_AIFF iff1);
int lame_set_samplesize(lame_global_flags*  gfp,int sampleSize );
int lame_get_samplesize( const lame_global_flags*  gfp );
int lame_set_in_samplerate( lame_global_flags*  gfp,int in_samplerate );
int lame_get_in_samplerate( const lame_global_flags*  gfp );
int lame_set_num_samples( lame_global_flags*  gfp,unsigned long num_samples);
unsigned long lame_get_num_samples( const lame_global_flags* gfp );
int lame_set_num_channels( lame_global_flags*  gfp,int num_channels );
int lame_get_num_channels( const lame_global_flags*  gfp );
int lame_get_framesize( const lame_global_flags*  gfp );
int lame_get_frameNum( const lame_global_flags*  gfp );
int fskip(FILE * fp, long offset, int whence);
void ReadBytes (FILE *fp, char *p, int n) ;
signed int ReadByte ( FILE* fp );
unsigned int ReadByteUnsigned ( FILE* fp );
int  Read16BitsLowHigh ( FILE* fp );
int  Read16BitsHighLow ( FILE* fp );
int  Read24BitsHighLow ( FILE* fp );
int  Read32Bits ( FILE* fp );
int  Read32BitsHighLow ( FILE* fp );
double ConvertFromIeeeExtended(char* bytes);
double ReadIeeeExtendedHighLow(FILE *fp);
void Write8Bits(FILE *fp, int i);
void Write16BitsLowHigh(FILE *fp, int i);
void Write16BitsHighLow(FILE *fp, int i);
void Write32Bits(FILE *fp, int i);
void Write32BitsLowHigh(FILE *fp, int i);
void Write32BitsHighLow(FILE *fp, int i);
int aiff_check2(const char *file_name, IFF_AIFF * const pcm_aiff_data);
int parse_aiff_header(lame_global_flags * gfp, FILE * sf);
void parse_file_header(lame_global_flags * gfp, FILE * sf);
int unpack_read_samples( const int samples_to_read, const int bytes_per_sample,
		     const int swap_order, int *sample_buffer, FILE *pcm_in );
int read_samples_pcm(FILE * musicfile, int sample_buffer[2304], int frame_size,
                 int samples_to_read);
int get_audio_common( lame_global_flags * const gfp,
		  int buffer[2][1152], short buffer16[2][1152] );
int get_audio( lame_global_flags * const gfp, int buffer[2][1152] );
unsigned char *getAIFF(const char *fname,FILE *fd,int *fsize);
unsigned char *loadImage(const char *fname,FILE *fd,int *fsize);
int read_pgmheader(FILE* handle);
unsigned char *read_pgmdata(FILE* handle,int *fsize);
int read_yuvdata(FILE* handle, unsigned char *image);
int writePGMcomp(char *filename, unsigned char *image1, unsigned char *image2, int output_image, char *filetype);
int getExpectedsize(int x, int y);
double sampleVariance(double data[],int elements);
double arithMean(double data[],int elements,double *variance,double *minimum);
double geoMean(double array[],int elements);
char *getSprintf(const char *fname);
unsigned char *getImage(char *fname,char **actual_fname,int *actual_size);
void psnr_print(double *array,
				int    index,
				int    numframes,
				int    allzero,
				int    exactmatch,
				char   *media_type);
void psnr_output_enable(char *actual_fname1,
						unsigned char *img1,
						unsigned char *img2);
int psnr_aiff(void);
int psnr_bmp256(void);
int psnr_packbits(int numbits);
int psnr_cmyk(char *type);
int psnr_spotcmyk(void);
int psnr_deskjet(void);
int psnr_laserjet(void);
int psnr_tiffg4(void);
int pdfStrip(unsigned char *img1,int actual_size1);
int pdfStripBinary(unsigned char *img1,int actual_size1);
int psnr_pdfwrite(void);
int main(int argc, char *argv[]);

/** @} */
/** @} */
#endif /*  PROTO_H  */

