/**
@file
@brief Stub file for autoconf build to pass control to gs.c.
Only build this using autoconf!
*/

/** required for th_lite */
char the_tcdef[512]={'\0',};

/** Stub for autoconf build, allows test harness link. */
int    test_main( char **tcdef, int argc, const char* argv[] )
{
	return 0;
}

int gs_main(int argc, char *argv[]);
/*SG: relying on internal GS filesystem
int init_filesystem(void); */

/** th regular only, allow th calls */
extern char *thdef;
extern char the_thdef[];
/** Stub for autoconf build. Use --allow-multiple-definition */
int main(int argc, char *argv[])
{
	int rv=0;
	/* th regular only */
	/*thdef = the_thdef;*/
	/* Initialize Harness File System. */
	/* SG: using compile_inits option for GS, so no need for TH file system
	init_filesystem(); */
	rv = gs_main(argc,argv);
	printf("\nGhostscript Return to Stub: %d\n",rv);
	th_printf("\nGhostscript TH Return to Stub: %d\n",rv);
	return rv;
}

