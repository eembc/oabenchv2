#!/bin/sh

# you could use csh so echo -n works on Solaris, 
# but other things do not work unless sh
# Here is the workaround...
case `echo "testing\c"; echo 1,2,3`,`echo -n testing; echo 1,2,3` in
  *c*,-n*) ECHO_N= ECHO_C='
' ECHO_T='	' ;;
  *c*,*  ) ECHO_N=-n ECHO_C= ECHO_T= ;;
  *)       ECHO_N= ECHO_C='\c' ECHO_T= ;;
esac

# Find an autoconf, in path

ACLOCAL=`which aclocal`
AUTOCONF=`which autoconf`
AUTORECONF=`which autoreconf`
AUTOMAKE=`which automake`
LIBTOOLIZE=`which libtoolize`
AUTOHEADER=`which autoheader`

[ -z $ACLOCAL ] && exit 1
[ -z $AUTOCONF ] && exit 1
[ -z $AUTORECONF ] && exit 1
[ -z $AUTOMAKE ] && exit 1
[ -z $LIBTOOLIZE ] && exit 1
[ -z $AUTOHEADER ] && exit 1

# The first time this is run,
# config.status will fail if stamp-h.in doesn't exist
[ ! -f ./stamp-h.in ] && touch ./stamp-h.in

# Autoconf the configure script

echo $ECHO_N "Removing files that are not needed... $ECHO_C"
find . -type d -name autom4te\*.cache -exec rm -rf {} \; 2>/dev/null
find . -name ltmain.sh -exec rm -f {} \; 2>/dev/null
echo "done"

echo $ECHO_N "Setup with aclocal... $ECHO_C"
$ACLOCAL 1>/dev/null 2>/dev/null
echo "done"

echo $ECHO_N "Copying files provided by libtool... $ECHO_C"
$LIBTOOLIZE --force --copy 1>/dev/null 2>/dev/null
echo "done"

echo $ECHO_N "Running autoheader... $ECHO_C"
$AUTOHEADER 1>/dev/null 2>/dev/null
echo "done"

echo $ECHO_N "Copying files provided by automake... $ECHO_C"
$AUTOMAKE --add-missing --include-deps --foreign --copy 1>/dev/null || echo "*** automake error" || exit 1
echo "done"

echo $ECHO_N "Creating ./configure... $ECHO_C"
rm -f ./configure
$AUTOCONF
echo "done"

echo $ECHO_N "Removing files that are not needed... $ECHO_C"
find . -type d -name autom4te\*.cache -exec rm -rf {} \; 2>/dev/null
find . -name ltmain.sh -exec rm -f {} \; 2>/dev/null
echo "done"

# See autoconf developer discussion on "config.cache considered harmful"
echo "Running Configure (creating new config.cache)..."
rm -f config.cache
./configure


