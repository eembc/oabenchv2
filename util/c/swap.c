/*
 * $Id: swap.c,v 1.2 2006/03/09 17:34:19 rick Exp $
 * DESC:	: Perform 32 bit endian byte swap on a file.
 *
 * AUTHOR	: Rick Foos, ECL, LLC
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> /* stat, struct stat */

char	*fname1;
char	*fname2;
int		 width=32;

void Usage(void)
{
	printf("Usage:\nswap -w <width> file1 file2\n");
	exit(0);
}

/** Process command line options */
void ProcessOptions(int argc,char *argv[])
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

			case 'W':
				if(NextArg || LastArg)
				{
					printf("ERROR: -w must be followed by image width\n");
					Usage();
				}
				else
					width = atoi(argv[++i]);
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

int checkswap(int swap)
{
	int doswap=0;
	/* We seem to also need swapping on BE hosts.
	if (bigendian) return swap;
	 */
	if (width==32)
	{
		doswap=(swap&0x000000ff)<<24;
		doswap|=(swap&0x0000ff00)<<8;
		doswap|=(swap&0x00ff0000)>>8;
		doswap|=(swap&0xff000000)>>24;
	}
	else if (width==16)
	{
		doswap=(swap&0x0000ff00)>>8;
		doswap=(swap&0x000000ff)<<8;
	}

	return doswap;
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

/** Load a file into a malloc'ed memory region. */
unsigned char *loadFile(const char *fname,long *fsize)
{
	unsigned char *buf;
	FILE *fd=NULL;

	/* run the gamut, and return */
	if ((fd=fopen(fname,"rb"))==NULL)
	{
		printf("File %s would not open.\n",fname);
		exit(1);
	}
	if (!(*fsize = getFilesize(fname)))
	{
		printf("File %s is empty.\n",fname);
		exit(1);
	}
	if (!(buf=malloc(*fsize)))
	{
		printf("Out of memory for %s, %d bytes\n",fname, *fsize);
		exit(1);
	}
	if ((fread(buf,*fsize,1,fd))!=1)
	{
		free(buf);
		printf("Error reading %d bytes from %s\n",fsize,fname);
		exit(1);
	}
	fclose(fd);
	return buf;
}
/** Create a 32 bit big endian pattern */
#define LONG_PACK(a,b,c,d) ((long) (((long)(a))<<24) | (((long)(b))<<16) | \
                                   (((long)(c))<<8)  |((long)(d)))
/** Swap endian of 32 bits of data. */
#define SWAP(a) ( (((a)&0x000000ff)<<24) | (((a)&0x0000ff00)<<8) | \
                  (((a)&0x00ff0000)>>8)  | (((a)&0xff000000)>>24) )

int main(int argc, char *argv[])
{
	long	fsize=0;
	long	fsizewidth;
	int		nframes=0,i;
	int		bigendian;
	int		*buf;
	FILE	*fd;

	bigendian = LONG_PACK('F','O','O','S');
	if(*((char *)(&bigendian)) == 'F')
		bigendian = 1;
	else
		bigendian = 0;

	ProcessOptions(argc,argv);
	buf=loadFile(fname1,&fsize);

	/* run the gamut, and return */
	if ((fd=fopen(fname2,"wb"))==NULL)
	{
		printf("File %s would not open for write.\n",fname2);
		exit(1);
	}

	/* Put in 16 bit code later if needed. */

	fsizewidth=fsize/(width/8);

	for (i=0;i<fsizewidth;i++)
	{
		buf[i]=checkswap(buf[i]);
	}

	if ((fwrite(buf,fsize,1,fd))!=1)
	{
		printf("Error writing %d bytes to %s\n",fsize,fname2);
	}
	free(buf);
	fclose(fd);
	return 0;
}
