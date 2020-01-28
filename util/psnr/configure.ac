#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

dnl AC_PREREQ(2.59)
AC_INIT([PSNR],[1.3], [support@ebenchmarks.com],[eembc-psnr])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([psnr.c])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CC
AC_PROG_MAKE_SET
# Need for libtiff
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h limits.h malloc.h stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_OFF_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([floor memset munmap pow strchr strdup strrchr])

dnl --------------------------------------------------
dnl Doxygen Install
dnl --------------------------------------------------
dnl AC_MSG_CHECKING([Doxygen Install])

dnl Find a Doxygen install, dot (graphviz) is called by doxygen.
dnl NOTE: The default is no package per autoconf. In makefile.in disable 
dnl documentation feature for source releases, or if dot and doxygen 
dnl are not found.
dnl For windows, requires building DOT with
dnl Cygwin so that it works with Cygwin doxygen. 
dnl This is too compilicated for default end user installs.


AC_PATH_PROG([DOXYGEN],[doxygen],[NONE],[$PATH])
AC_PATH_PROG([GRAPHVIZ],[dot],[NONE],[$PATH])
AC_PATH_PROG([DOXYSEARCH],[doxysearch],[NONE],[$PATH])

AC_ARG_WITH([doxygen],
AC_HELP_STRING([--with-doxygen],[Generate detail design documentation]),
	[
	# Run if with/without specified
	if test x$withval = xno; then
	AC_MSG_RESULT(disabled)
	elif test x$DOXYGEN = xNONE -o x$GRAPHVIZ = xNONE ; then
	AC_MSG_RESULT([Doxygen AND Graphviz must be installed])
	fi
	],
)

dnl YES, NO or NONE for makefile.in
dnl Default is YES if all preconditions met.

if test x$with_doxygen = xno; then 
	DOXINSTALL=NO
elif test x$DOXYGEN != xNONE -a x$GRAPHVIZ != xNONE; then
	DOXINSTALL=YES
	GRAPHVIZ=`dirname $GRAPHVIZ`
else
	DOXINSTALL=NONE
fi
AC_SUBST(DOXINSTALL)

dnl Doxyfile OUTPUT_DIRECTORY for html and latex directories
dnl also used in Makefile to make pdf in latex directory.
DOXYROOT=.
AC_ARG_VAR(DOXYROOT,
	[Web server document root to store doxyfile output])

dnl --------------------------------------------------
dnl Find html help (Microsoft Only)
dnl --------------------------------------------------
if test x$DOXINSTALL != xNONE; then
AC_PATH_PROG([HTMLHELP],[hhc.exe],[no],[/cygdrive/c/PROGRA~1/HTMLHE~1:/cygdrive/d/PROGRA~1/HTMLHE~1:$PATH])
AC_ARG_VAR([HTMLHELP],[Microsoft Help Compiler])
if test x$HTMLHELP = xno; then
HTMLHELP=
fi
fi

dnl --------------------------------------------------
dnl Find a Web Server (as Package)
dnl --------------------------------------------------

dnl --------------------------------------------------
dnl Packages and Features
dnl --------------------------------------------------

dnl --------------------------------------------------
dnl Precious Variables
dnl --------------------------------------------------
dnl Newer versions of autoconf call AC_HELP_STRING


dnl For Cygwin based systems drive letters need to be converted 
dnl to a Unix path for Doxygen
UNIXPREFIX=$prefix
AC_SUBST([UNIXPREFIX])

dnl Having trouble with cygwin1.dll pathing under apache, 
dnl tried -mno-cygwin switch and had multiple autoconf failures in mingw

case "$target_os" in
	*cygwin*) 
		UNIXPREFIX=`cygpath --unix $UNIXPREFIX`
		;;
	*linux*)   
		;;
	*solaris*) 
		;;
	*)
		echo "New or Unknown target OS: $target_os..."
		;;
esac

AC_CONFIG_FILES([Makefile dox/Doxyfile dox/Makefile libtiff/Makefile])
AC_OUTPUT

