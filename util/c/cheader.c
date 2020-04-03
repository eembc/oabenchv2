/*
 * $Id: cheader.c,v 1.3 2006/03/09 17:34:19 rick Exp $
 * DESC:	: Build header file and filecreates for EEMBC ram file
 *
 * AUTHOR	: Rick Foos, ECL, LLC
 *
 */
/*
 * @test Program arguments for VC testing MODULO=5
 * -d ../../../consumer/libppm/test1_frame%.3d -n 100 -s 0 -t .ppm -m rb -f 5
 * -d ../../../consumer/libppm/test1_frame%.3d -n 100 -s 0 -t .ppm -m rb -f $MODULO
 * -d ../../../consumer/libmp3/jupiter.mp3  -m rb -w
 * -d ../../../consumer/libmpeg/test1.mpeg  -m rb
 * -d libyuv/zoom%.3d -n 30 -s 1 -t .yuv -m rb -f 5
 * -d libjpeg/parrot.jpg -m rb
 * -d libjpeg/parrot.jpg -m rb -x libjpeg -a /usr/local/share/ghostscript
 * -d libps/image-qa.ps -m rb -x libps -a /usr/local/share/ghostscript
 */

/** External copyright message for generated files */
const char *COPYRIGHT = {
"/**\n"
" *\n"
" * Copyright (C) EEMBC(R) All Rights Reserved\n"
" *\n"
" * This software is licensed with an Acceptable Use Agreement under Apache 2.0.\n"
" * Please refer to the license file (LICENSE.md) included with this code.\n"
" *\n"
" */\n"
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* toupper */

/** Porting: Suffix for C Initialization file */
const char *INITC="_init.c";

/** Porting: C output frame set headers */
const char *frameset_headers_eembc = "#include \"eembc_dt.h\"\n\n";
/** Porting: No EEMBC C output frame set headers */
const char *frameset_headers_noeembc = "\n";
/** Porting: Default frame set headers */
const char *frameset_headers;

/** Porting: C output file create headers */
const char *filecreate_headers_eembc = "#include \"thlib.h\"\n";
/** Porting: No EEMBC C output file create headers */
const char *filecreate_headers_noeembc = 

"#include \"thconfig.h\"\n"
"#include \"thstdio.h\"\n"
"#define THE_FAILURE 1\n"
"FILE *th_fcreate(const char *filename, const char *mode, char *data, size_t size);\n"
"void	th_exit( int exit_code, const char *fmt, ... );\n\n";
/** Porting: C output file create headers */
const char *filecreate_headers;

/** Porting: Data type of C file data array */
const char *cfile_array_type_eembc = "e_u8";
/** Porting: No EEMBC Data type of C file data array */
const char *cfile_array_type_noeembc = "unsigned char";
/** Porting: Data type of C file data array */
const char *cfile_array_type;

/** Number of bytes in data array. */
const char *bytesin_format = "#define BYTES_IN_%s\t%luUL\n";
/** Porting: ROM file create "If" statement */
const char *filecreate_format = 
"\tif ((th_fcreate(\"%s\",\"rb\",(char *)t_%s,BYTES_IN_%s)) == NULL)\n";
/** Porting: ROM file create Error statement */
const char *errfilecreate_format = 
"\t\tth_exit(THE_FAILURE,\"Could not create input file: %s\\n\");\n";

/** Set EEMBC header file dependencies, or no dependencies after getopt (-e option) */
void Set_Dependencies(int eembc_flag)
{
	if (eembc_flag)
	{
		frameset_headers	= frameset_headers_eembc;
		filecreate_headers	= filecreate_headers_eembc;
		cfile_array_type	= cfile_array_type_eembc;
	}
	else
	{
		frameset_headers	= frameset_headers_noeembc;
		filecreate_headers	= filecreate_headers_noeembc;
		cfile_array_type	= cfile_array_type_noeembc;
	}
}

/** Convert string to upper case */
char *strupr(char *string)
{
	char *s;

	if (string)
		for (s = string; *s; ++s)
			*s = toupper(*s);
	return string;
} 

/** Convert string to lower case */
char *strlwr(char *string)
{
	char *s;

	if (string)
		for (s = string; *s; ++s)
			*s = tolower(*s);

	return string;
}

/** Display program options */
static void Usage(void)
{
printf("Usage:  cheader {options}\n\
Options: -d  DIRECTORY: printf directory/filename where files reside, and frame number format\n\
         -x  EXCLUDE: strip prefix for internal file directory paths\n\
         -a  ADD prefix for internal file directory paths\n\
         -o  OUTPUT directory for generated files (default -d directory)\n\
         -n  NUMBER of frames (0 for single file)\n\
         -s  STARTING frame number\n\
         -f  FRAME split modulo to reduce compiler load (i.e. 10->0-9,10-19)\n\
         -t  TYPE: the input file type (i.e. .ppm)\n\
         -m  MODE: file stream mode (i.e. wb, rb, r, w)\n\
         -w  WRITEABLE: Make the array writeable (remove const)\n\
         -e  EEMBC Remove eembc header file dependencies.\n\
         -v  VERBOSE printing\n\
\n\
File patterns:  for sequential filenames, \"printf\" style, e.g. rec%%d\n\
                or rec%%d%%c for fieldwise storage\n\
Example:  cheader -d mpeg/datasets/frame%%.3d -n 100 -s 0 -t .ppm -m rb\n\
\n");
exit(0);
}
/* Globals emitted by options */
/** No EEMBC dependencies (-e) */
int 	EEMBC_Dependencies=1;
/** Quiet/Verbose output */
int		Quiet_Flag=1;
/** Declare data areas writeable (no const qualifier) */
int		NoConst_Flag = 0;
/** printf string of files ../d/frame%.3d */
char	*tplorg=NULL;
/** Output directory for generated files */
char    *outputdir=NULL;
/** Strip prefix from input directory for internal file paths */
char	*stripprefix=NULL;
/** Add prefix from input directory for internal file paths */
char	*addprefix=NULL;
/** total number of frames */
int		nframes=0;
/** number of first frame, default 0 */
int 	frame0=0;
/** file type of input (i.e. .ppm) */
char	*inputtype=NULL;
/** stream mode to open with (rb, rt, r) */
char	*inputmode=NULL;
/** modulo to split C midfile */
int		splitcmid=0;
/** Interim modulo calculations */
div_t   modcmid;

/** Process command line options */
static void Process_Options(int argc,char *argv[])
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

      /* parse ahead to see if another flag immediately follows current
      argument (this is used to tell if a filename is missing) */
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
         case 'D':
            if(NextArg || LastArg)
            {
               printf("ERROR: -d must be followed a Directory name\n");
            }
            else
               tplorg = argv[++i];
            break;

         case 'O':
            if(NextArg || LastArg)
            {
               printf("ERROR: -o must be followed a Directory name\n");
            }
            else
               outputdir = argv[++i];
            break;

         case 'X':
            if(NextArg || LastArg)
            {
               printf("ERROR: -x must be followed a Directory prefix to strip\n");
            }
            else
               stripprefix = argv[++i];
            break;

         case 'A':
            if(NextArg || LastArg)
            {
               printf("ERROR: -a must be followed a Directory prefix to add\n");
            }
            else
               addprefix = argv[++i];
            break;

         case 'N':
            if(NextArg || LastArg)
            {
               printf("ERROR: -n must be followed by the number of frames\n");
            }
            else
               nframes = atoi(argv[++i]);
            break;

         case 'S':
            if(NextArg || LastArg)
            {
               printf("ERROR: -s must be followed by the start frame number\n");
            }
            else
               frame0 = atoi(argv[++i]);
            break;

         case 'F':
            if(NextArg || LastArg)
            {
               printf("ERROR: -f must be followed by the split at frame number\n");
            }
            else
               splitcmid = atoi(argv[++i]);
            break;

         case 'T':
            if(NextArg || LastArg)
            {
               printf("ERROR: -t must be followed by the file type (i.e. .ppm)\n");
            }
            else
               inputtype = argv[++i];
            break;

         case 'M':
            if(NextArg || LastArg)
            {
               printf("ERROR: -m must be followed by the fopen file mode (rb)\n");
            }
            else
               inputmode = argv[++i];
            break;

         case 'V':
            Quiet_Flag = 1;
            break;

         case 'W':
            NoConst_Flag = 1;
            break;

         case 'E':
            EEMBC_Dependencies = 0;
            break;

         default:
            printf("undefined option -%c ignored.",argv[i][1]);
            exit(-1);

      } /* switch() */
    } /* if argv[i][0] == '-' */

    i++;

    /* check for bitstream filename argument (there must always be one, at the very end
    of the command line arguments */

   } /* while() */


   /* options sense checking */
   if ( /* Single files */
	   (tplorg==NULL) ||	/* printf string of files ../d/frame%.3d, or single file */
	   /* (nframes==0) ||	total number of frames to do, 0 for single file */
	   /*(frame0==0) ||		 number of first frame, can be 0 */
	   /* (inputtype==NULL) 	file type of input .ppm */
	   (inputmode==NULL)	/* mode to open with (rb, rt, r) */
	   ) Usage();
   else  /* Single File */
	   if ((nframes != 0 || frame0 != 0) &&
		   inputtype == NULL)
		   Usage();

	/* outputdir is optional */
	if (!outputdir) outputdir=tplorg;

	if (stripprefix && ((strstr(tplorg,stripprefix))==NULL))
	{
		printf("*** ERROR: Strip prefix (-x): %s, not in path: %s\n",stripprefix,tplorg);
		Usage();
	}

	 /* if file is writeable, array can't be const */
	if ((strrchr(inputmode,(int)'w')) != NULL) /* if file is writeable, array can't be const */
		NoConst_Flag = 1;
	   
}
/** Do File conversion to hex digits.
 * This function converts a binary file to the hexadecimal
 * representation and stores it in a text file.
 * This function never gets all the bytes into a file, so we revert to bytes rlf.
 */
unsigned long DoConversion(FILE *in_fp, FILE *out_fp)
{
   unsigned int crlf=0;
   unsigned char *tmp,val;
   unsigned long file_size = 0;

   while (!feof(in_fp))
   {
      if (fread((void *)(&val), 1, 1, in_fp)) 
	  {
		  tmp = (unsigned char *)&val;
		  fprintf(out_fp, "0x%02x, ",*(tmp));
 		  file_size++;
		  if (crlf == 7)
		  {
			  crlf = 0;
			  fprintf(out_fp,"\n");
		  } else crlf++;
         }
   }
	fprintf(out_fp,"\n\n");
	return file_size;
}
/** Process one frame/file into C header file. */
int process_frame(FILE *infile,char *filenotype)
{
	FILE	*outfile;
	char	filename[FILENAME_MAX];
	unsigned long size = 0;

	strcpy(filename,filenotype);
	strcat(filename,".h");
	if ((outfile = fopen(filename,"w")) == NULL)
	{
		printf("Couldn't open output header file %s\n",filename);
		return 0;
	}
	fprintf(outfile,"/*\n * Generated by cheader from file:\n * %s\n */\n\n",filenotype);
	if (COPYRIGHT)
		fprintf(outfile,COPYRIGHT);

	fflush(outfile);

	size = DoConversion(infile,outfile);

	fflush(outfile);
	fclose(outfile);
	return size;
}

/** Get Filename, no directory.
 reverse scan for \ or / */
void	get_filenodir(char *filenodir,char *filenotype)
{
	char	*split;

	/* get filename without directory or filetype */
	if ((split = strrchr(filenotype,(int)'/')) != NULL) 
		strcpy(filenodir,++split); /* move in front of the / */
	else
	if ((split = strrchr(filenotype,(int) '\\')) != NULL)
		strcpy(filenodir,++split);
	else
		strcpy(filenodir,filenotype);
}

/** Get file, no format string.
 forward scan for % */
void	get_filenofmt(char *filenofmt,char *filenotype)
{
	char	*split;

	/* get filename without formatting */
	/* strtok crushes input parm */
	strcpy(filenofmt,filenotype);
	if ((split = strtok(filenofmt,"%")) == NULL) 
		strcpy(filenofmt,filenotype);
}

/** Get file, no filetype.
convert . to _ */
void	get_filenodot(char *filenofmt,char *filenotype)
{
	char *split;
	/* if .'s in path name, leave them alone */
	strcpy(filenofmt,filenotype);
	split = filenofmt + strlen(filenofmt);
	while ((--split != filenofmt) && ((*split != '/') && (*split != '\\')) )
	{
		if (*split == '.') *split = '_';
	}

}
/** Get filename, convert - to _.
Use this to convert filenames that use C reserved characters.
*/
char	*get_filenodash(char *filename)
{
	char *split,*rvsplit;

	if (!filename || !*filename) return filename;

	rvsplit=split=strdup(filename);
	while (*split)
	{
		if (*split == '-') *split = '_';
		split++;
	}
	return rvsplit;
}

/** Append frame to C file */
int addto_midfile(FILE *coutfile,FILE *houtfile,FILE *ioutfile,
				  char *filenodir, char *framefile, unsigned long size)
{
	char	uprfilenodir[FILENAME_MAX];

	/* must do this to a seperate variable to protect original filenodir */
	strcpy(uprfilenodir,filenodir);
	strupr(uprfilenodir);

	/* Put in the correct array definition, and define an extern in the H file */
	if (NoConst_Flag == 0)
	{
		fprintf(houtfile, "extern const %s t_%s[];\n\n",
			cfile_array_type,get_filenodash(filenodir));
		fprintf(coutfile, "const %s t_%s[] = {\n",
			cfile_array_type,get_filenodash(filenodir));
	} else {
		fprintf(houtfile, "extern %s t_%s[];\n\n",
			cfile_array_type,get_filenodash(filenodir));
		fprintf(coutfile, "%s t_%s[] = {\n",
			cfile_array_type,get_filenodash(filenodir));
	}
	fprintf(houtfile, bytesin_format,get_filenodash(uprfilenodir), size);

	/* Insert the file create call into the Init C file */
	fprintf(ioutfile,filecreate_format,
		framefile,
		get_filenodash(filenodir),
		get_filenodash(uprfilenodir));
	fprintf(ioutfile,errfilecreate_format,
		framefile);

	/* Insert the include to the C file array*/
	fprintf(coutfile,"#include \"%s.h\"\n",filenodir);

	/* terminate the C file array, store the file size as a define */
	fprintf(coutfile, "};\n");
	fprintf(coutfile, bytesin_format,
		get_filenodash(strupr(filenodir)), size);
	fprintf(coutfile,"\n");

	fflush(coutfile); /* for debug to see partial results */
	fflush(houtfile); /* for debug to see partial results */
	fflush(ioutfile); /* for debug to see partial results */

return 0;
}

FILE *get_cmidfilename(FILE *oldcmidfile, char *cmidfilename,char *smidfilename,
					   int modframe0,int modnframes)
{
	FILE * cmidfile;

	if (splitcmid == 0) 
		sprintf(cmidfilename,"%s_%.3d_%.3d.c",smidfilename,0,nframes-1);
	else
		sprintf(cmidfilename,"%s_%.3d_%.3d.c",smidfilename,modframe0,modnframes);

	if (oldcmidfile != NULL) fclose(oldcmidfile);
	if ((cmidfile = fopen(cmidfilename,"w")) == NULL)
	{
		printf("Couldn't open output c file %s\n",cmidfilename);
		exit(1);
	}
	fprintf(cmidfile,"/*\n * Generated by cheader for frames %d to %d from file:\n * %s\n */\n\n",
		frame0,nframes,tplorg);
	if (COPYRIGHT)
		fprintf(cmidfile,COPYRIGHT);
	if (frameset_headers)
		fprintf(cmidfile,frameset_headers);

	return cmidfile;
}


void single_midfile(FILE *infile,char *tplorg,char *outputdir,char *stripprefix)
{
	char	hmidfilename[FILENAME_MAX]={'\0',};
	char	imidfilename[FILENAME_MAX]={'\0',};
	char	filenotype[FILENAME_MAX]={'\0',};
	char	filenodir[FILENAME_MAX];
	FILE	*imidfile;	/* RAM initialization file */
	char	uprfilenodir[FILENAME_MAX];
	unsigned long size;
	/* get a fresh copy so we can stripprefix */
	char	*buf=strdup(tplorg);
	char	*bufadd;
	/* keep the original pointer for free */
	char	*freebuf=buf;

	/* 
	 * Build the internal path, absolute or stripprefix'ed 
	 * In either case, it always has a remnant of the original path.
	 */
	if (stripprefix)
	{
		buf=strstr(buf,stripprefix);
		buf+=strlen(stripprefix);
	}
	if (addprefix)
	{
		bufadd=malloc(strlen(buf) + strlen(addprefix) + 2);
		strcpy(bufadd,addprefix);
		strcat(bufadd,buf);
		free(freebuf);
		buf=freebuf=bufadd;
	}
	/* Build the output filename, based on the input filename */
	get_filenodot(filenotype,tplorg);
	get_filenodir(filenodir,filenotype);
	/* Build the output directory (might be tplorg, so we strip out filename anyway) */
	get_filenodot(filenotype,outputdir);
	/* stitch in the output directory */
	if ((strcmp(tplorg,outputdir))!=0)
	{
		strcat(filenotype,"/");
		strcat(filenotype,filenodir);
	}
	strcpy(uprfilenodir,filenodir);strupr(uprfilenodir);
	strcpy(hmidfilename,filenotype);strcat(hmidfilename,".h");
	strcpy(imidfilename,filenotype);strcat(imidfilename,INITC);
	/* Open Header file for input file output */
	if ((size = process_frame(infile,filenotype)) == 0)
	{
		printf("Error in process_frame on %s\n",tplorg);
		fclose(infile);
		exit(1);
	}
	
	/* Open C file to load in generated header file */
	if ((imidfile = fopen(imidfilename,"w")) == NULL)
	{
		printf("Couldn't open output file %s\n",imidfilename);
		exit(1);
	}
	if (!frame0 && !nframes)
		fprintf(imidfile,"/*\n * Generated by loadfile from file:\n * %s\n */\n\n",imidfilename);
	else
		fprintf(imidfile,"/*\n * Generated by loadfile for frames %d to %d from file:\n * %s\n */\n\n",frame0,nframes,imidfilename);
	if (COPYRIGHT)
		fprintf(imidfile,COPYRIGHT);
	if (filecreate_headers)
		fprintf(imidfile,filecreate_headers);

	/* build array in C file */
	if (NoConst_Flag == 0)
	fprintf(imidfile, "const %s t_%s[] = {\n",
		cfile_array_type,get_filenodash(filenodir));
	else
	fprintf(imidfile, "%s t_%s[] = {\n",
		cfile_array_type,get_filenodash(filenodir));

	fprintf(imidfile,"#include \"%s.h\"\n};\n",filenodir);
	fprintf(imidfile,bytesin_format,
		get_filenodash(uprfilenodir), size);
	fprintf(imidfile,"\n");

	fprintf(imidfile,"void init_%s(void)\n{\n",get_filenodash(filenodir));

	/* 
	 * Insert the file create call into the Init C file
	 * Here is where we insert the fake file name in buf!
	 */
	fprintf(imidfile,filecreate_format,
		buf,
		get_filenodash(filenodir),
		get_filenodash(uprfilenodir));
	fprintf(imidfile,errfilecreate_format,buf);
	fprintf(imidfile,"}\n\n");
	fclose(imidfile);
	free(freebuf);
}

int main(int argc, char *argv[])
{
	char	filename[FILENAME_MAX]={'\0',};
	char	cmidfilename[FILENAME_MAX]={'\0',};
	char	hmidfilename[FILENAME_MAX]={'\0',};
	char	imidfilename[FILENAME_MAX]={'\0',};
	char	smidfilename[FILENAME_MAX]={'\0',};
	char	filenotype[FILENAME_MAX]={'\0',};
	char	filenodir[FILENAME_MAX];
	FILE	*infile;	/* input frame file */
	FILE	*cmidfile=NULL;	/* C collector file */
	FILE	*hmidfile;	/* H collector file */
	FILE	*imidfile;	/* RAM initialization file */
	int		i;
	unsigned long size;
	int		modframe0,modnframes;

	Process_Options(argc,argv);
	Set_Dependencies(EEMBC_Dependencies);
	if (nframes == 0)		/* single file */
	{
		printf("C Header Single File: %s\n",tplorg);
		if ((infile = fopen(tplorg,inputmode)) == NULL)
		{
			printf("Couldn't open input file %s\n",tplorg);
			exit(1);
		}
		single_midfile(infile,tplorg,outputdir,stripprefix);
		fclose(infile);
	} else {				/* multiple header files, with C collector and init files */
		printf("C Header Frame Files: %s %d - %d\n",tplorg,frame0,nframes);

		/* Open Middle files */
		get_filenofmt(cmidfilename,tplorg);
		strcat(cmidfilename,inputtype);
		get_filenodot(cmidfilename,cmidfilename);
		strcpy(hmidfilename,cmidfilename);
		strcpy(imidfilename,cmidfilename);
		strcpy(smidfilename,cmidfilename);
		get_filenodir(filenodir,cmidfilename);
		/* append initial file types */
		strcat(hmidfilename,".h");
		strcat(imidfilename,INITC);
		if ((hmidfile = fopen(hmidfilename,"w")) == NULL)
		{
			printf("Couldn't open output c file %s\n",hmidfilename);
			exit(1);
		}
		fprintf(hmidfile,"/*\n * Generated by cheader for frames %d to %d from file:\n * %s\n */\n\n",
			frame0,nframes,tplorg);
		if (COPYRIGHT)
			fprintf(hmidfile,COPYRIGHT);
		if (frameset_headers)
			fprintf(hmidfile,frameset_headers);
		if ((imidfile = fopen(imidfilename,"w")) == NULL)
		{
			printf("Couldn't open output c file %s\n",imidfilename);
			exit(1);
		}
		fprintf(imidfile,"/*\n * Generated by cheader for frames %d to %d from file:\n * %s\n */\n\n",
			frame0,nframes,tplorg);
		if (COPYRIGHT)
			fprintf(imidfile,COPYRIGHT);
		fprintf(imidfile,filecreate_headers);
		fprintf(imidfile,"#include \"%s.h\"\n\n",filenodir);
		fprintf(imidfile,"void init_%s(void)\n{\n",get_filenodash(filenodir));


		for (i=frame0;i<nframes+frame0;i++)
		{
			sprintf(filenotype,tplorg,i);	/* add the frame number */
			strcpy(filename,filenotype);	/* preserve filenotype */
			strcat(filename,inputtype);		/* add the filetype */
			strcat(filenotype,inputtype);
			get_filenodot(filenotype,filenotype); /* extend filename with type */
			get_filenodir(filenodir,filenotype);
			if ((infile = fopen(filename,inputmode)) == NULL)
			{
				printf("Couldn't open frame %s\n",filename);
				exit(1);
			} else {
				printf("Processing frame: %d\r",i);
				if ((size = process_frame(infile,filenotype)) == 0)
				{
					printf("Error in Do Process on %s\n",filename);
					fclose(infile);
					exit(1);
				}
				fclose(infile);
			}
			if (splitcmid != 0)
			{
				modcmid = div(i,splitcmid);
				modnframes = ++modcmid.quot*splitcmid;
				modnframes--;
				if (modnframes > nframes+frame0) modnframes=nframes+frame0-1;
				modframe0 = i;
				/* If fstart0 is not 0, we start inside the modulo range */
				if (modcmid.rem == 0 || cmidfile == NULL) 
				{
					cmidfile = get_cmidfilename(cmidfile,cmidfilename,smidfilename,modframe0,modnframes);
					printf("modframe0: %d, modframes: %d\n",modframe0,modnframes);
				}
			} else cmidfile = get_cmidfilename(cmidfile,cmidfilename,smidfilename,frame0,nframes-1);
			addto_midfile(cmidfile,hmidfile,imidfile,filenodir,filename,size);
		}
		fprintf(imidfile,"}\n\n");
		fclose(cmidfile);
		fclose(hmidfile);
		fclose(imidfile);
	}
	return 0;
}
