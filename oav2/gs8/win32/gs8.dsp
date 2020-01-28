# Microsoft Developer Studio Project File - Name="gs8" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=gs8 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "gs8.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gs8.mak" CFG="gs8 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gs8 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "gs8 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "gs8 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Za /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /I "..\x86\al" /I "..\include" /I "..\icclib" /I "..\ijs" /I "..\jpeg" /I "..\jbig2dec" /I "..\lib" /I "..\libpng" /I "..\src" /I "..\zlib" /I "..\jasper-1.701.0\src\libjasper\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D SHARE_LIBPNG=1 /D SHARE_JPEG=1 /D SHARE_ZLIB=1 /D SHARE_JBIG2=1 /U "HAVE_MKSTEMP" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "gs8 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /Za /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /I "..\x86\al" /I "..\include" /I "..\icclib" /I "..\ijs" /I "..\jpeg" /I "..\jbig2dec" /I "..\lib" /I "..\libpng" /I "..\src" /I "..\zlib" /I "..\jasper-1.701.0\src\libjasper\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D SHARE_LIBPNG=1 /D SHARE_JPEG=1 /D SHARE_ZLIB=1 /D SHARE_JBIG2=1 /U "HAVE_MKSTEMP" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "gs8 - Win32 Release"
# Name "gs8 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\algo.c
# End Source File
# Begin Source File

SOURCE=..\bmark.c
# End Source File
# Begin Source File

SOURCE=..\filesystem_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts_init.c
# End Source File
# Begin Source File

SOURCE=..\libps_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource_init.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\algo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\src\gs16spl.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gsdll2.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gsdll32.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gsos2.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gspmdrv.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gswin.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gswin32.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\src\gswin386.rc
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter "c h"
# Begin Source File

SOURCE=..\include\arch.h
# End Source File
# Begin Source File

SOURCE=..\include\gconfig.c
# End Source File
# Begin Source File

SOURCE=..\include\gconfig.h
# End Source File
# Begin Source File

SOURCE=..\include\gconfig_.h
# End Source File
# Begin Source File

SOURCE=..\include\gconfigv.h
# End Source File
# Begin Source File

SOURCE=..\include\gscdefs.c
# End Source File
# Begin Source File

SOURCE=..\include\iconfig.c
# End Source File
# End Group
# Begin Group "gs8 Source Files"

# PROP Default_Filter "c;h"
# Begin Source File

SOURCE=..\src\dscparse.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevabuf.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevbbox.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevbit.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevbj10.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevbmp.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevbmpc.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevcdj.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevclj.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevcljc.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdbit.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdcrd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevddrw.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdevn.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdflt.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdgbr.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdjet.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdljm.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevdsha.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevfax.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevhit.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevjpeg.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevlj56.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm1.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm16.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm2.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm24.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm32.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm4.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm40.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm48.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm56.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm64.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevm8.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevmem.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevmpla.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevmrun.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevnfwd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevp14.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpbm.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpccm.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpcl.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpcx.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdf.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfb.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfc.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfg.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfi.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfj.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfk.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfm.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfo.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfp.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfr.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfu.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfv.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdt.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtb.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtc.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdte.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtf.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdti.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdts.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtt.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtv.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtw.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpipe.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevplnx.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpng.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevppla.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevprn.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevps.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsdi.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsdp.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsds.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsdu.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsf1.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsf2.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsfm.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsft.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsfu.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsfx.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsim.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsu.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpx.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevpxut.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevtfax.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevtfnx.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevtifs.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevupd.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevvec.c
# End Source File
# Begin Source File

SOURCE=..\src\gdevxcf.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_getnv.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_nsync.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_stdia.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_strdl.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_unifn.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_unifs.c
# End Source File
# Begin Source File

SOURCE=..\src\gp_unix.c
# End Source File
# Begin Source File

SOURCE=..\src\gpmisc.c
# End Source File
# Begin Source File

SOURCE=..\src\gs.c
# End Source File
# Begin Source File

SOURCE=..\src\gsalloc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsalpha.c
# End Source File
# Begin Source File

SOURCE=..\src\gsalphac.c
# End Source File
# Begin Source File

SOURCE=..\src\gsargs.c
# End Source File
# Begin Source File

SOURCE=..\src\gsbitcom.c
# End Source File
# Begin Source File

SOURCE=..\src\gsbitops.c
# End Source File
# Begin Source File

SOURCE=..\src\gsbittab.c
# End Source File
# Begin Source File

SOURCE=..\src\gscdevn.c
# End Source File
# Begin Source File

SOURCE=..\src\gscedata.c
# End Source File
# Begin Source File

SOURCE=..\src\gscencs.c
# End Source File
# Begin Source File

SOURCE=..\src\gschar.c
# End Source File
# Begin Source File

SOURCE=..\src\gschar0.c
# End Source File
# Begin Source File

SOURCE=..\src\gscie.c
# End Source File
# Begin Source File

SOURCE=..\src\gsciemap.c
# End Source File
# Begin Source File

SOURCE=..\src\gsclipsr.c
# End Source File
# Begin Source File

SOURCE=..\src\gscolor.c
# End Source File
# Begin Source File

SOURCE=..\src\gscolor1.c
# End Source File
# Begin Source File

SOURCE=..\src\gscolor2.c
# End Source File
# Begin Source File

SOURCE=..\src\gscolor3.c
# End Source File
# Begin Source File

SOURCE=..\src\gscoord.c
# End Source File
# Begin Source File

SOURCE=..\src\gscparam.c
# End Source File
# Begin Source File

SOURCE=..\src\gscpixel.c
# End Source File
# Begin Source File

SOURCE=..\src\gscrd.c
# End Source File
# Begin Source File

SOURCE=..\src\gscrdp.c
# End Source File
# Begin Source File

SOURCE=..\src\gscrypt1.c
# End Source File
# Begin Source File

SOURCE=..\src\gscscie.c
# End Source File
# Begin Source File

SOURCE=..\src\gscsepr.c
# End Source File
# Begin Source File

SOURCE=..\src\gscspace.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdevice.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdevmem.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdfilt.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdparam.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdps.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdps1.c
# End Source File
# Begin Source File

SOURCE=..\src\gsdsrc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsequivc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfcid.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfcid2.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfcmap.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfcmap1.c
# End Source File
# Begin Source File

SOURCE=..\src\gsflip.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfname.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfont.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfont0.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfont0c.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc0.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc3.c
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc4.c
# End Source File
# Begin Source File

SOURCE=..\src\gsgcache.c
# End Source File
# Begin Source File

SOURCE=..\src\gsgdata.c
# End Source File
# Begin Source File

SOURCE=..\src\gsht.c
# End Source File
# Begin Source File

SOURCE=..\src\gsht1.c
# End Source File
# Begin Source File

SOURCE=..\src\gshtscr.c
# End Source File
# Begin Source File

SOURCE=..\src\gshtx.c
# End Source File
# Begin Source File

SOURCE=..\src\gsicc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsimage.c
# End Source File
# Begin Source File

SOURCE=..\src\gsimpath.c
# End Source File
# Begin Source File

SOURCE=..\src\gsinit.c
# End Source File
# Begin Source File

SOURCE=..\src\gsiodev.c
# End Source File
# Begin Source File

SOURCE=..\src\gsistate.c
# End Source File
# Begin Source File

SOURCE=..\src\gsline.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmalloc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmatrix.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmemlok.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmemory.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmemret.c
# End Source File
# Begin Source File

SOURCE=..\src\gsmisc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsnogc.c
# End Source File
# Begin Source File

SOURCE=..\src\gsnorop.c
# End Source File
# Begin Source File

SOURCE=..\src\gsnotify.c
# End Source File
# Begin Source File

SOURCE=..\src\gsovrc.c
# End Source File
# Begin Source File

SOURCE=..\src\gspaint.c
# End Source File
# Begin Source File

SOURCE=..\src\gsparam.c
# End Source File
# Begin Source File

SOURCE=..\src\gsparams.c
# End Source File
# Begin Source File

SOURCE=..\src\gsparamx.c
# End Source File
# Begin Source File

SOURCE=..\src\gspath.c
# End Source File
# Begin Source File

SOURCE=..\src\gspath1.c
# End Source File
# Begin Source File

SOURCE=..\src\gspcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\gsptype1.c
# End Source File
# Begin Source File

SOURCE=..\src\gsptype2.c
# End Source File
# Begin Source File

SOURCE=..\src\gsroptab.c
# End Source File
# Begin Source File

SOURCE=..\src\gsserial.c
# End Source File
# Begin Source File

SOURCE=..\src\gsshade.c
# End Source File
# Begin Source File

SOURCE=..\src\gsstate.c
# End Source File
# Begin Source File

SOURCE=..\src\gstext.c
# End Source File
# Begin Source File

SOURCE=..\src\gstrans.c
# End Source File
# Begin Source File

SOURCE=..\src\gstype1.c
# End Source File
# Begin Source File

SOURCE=..\src\gstype2.c
# End Source File
# Begin Source File

SOURCE=..\src\gstype42.c
# End Source File
# Begin Source File

SOURCE=..\src\gsutil.c
# End Source File
# Begin Source File

SOURCE=..\src\gswts.c
# End Source File
# Begin Source File

SOURCE=..\src\gxacpath.c
# End Source File
# Begin Source File

SOURCE=..\src\gxbcache.c
# End Source File
# Begin Source File

SOURCE=..\src\gxblend.c
# End Source File
# Begin Source File

SOURCE=..\src\gxccache.c
# End Source File
# Begin Source File

SOURCE=..\src\gxccman.c
# End Source File
# Begin Source File

SOURCE=..\src\gxchar.c
# End Source File
# Begin Source File

SOURCE=..\src\gxchrout.c
# End Source File
# Begin Source File

SOURCE=..\src\gxcht.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclbits.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclimag.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclip.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclip2.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclipm.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclist.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclmem.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclpage.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclpath.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclrast.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclread.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclrect.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclutil.c
# End Source File
# Begin Source File

SOURCE=..\src\gxclzlib.c
# End Source File
# Begin Source File

SOURCE=..\src\gxcmap.c
# End Source File
# Begin Source File

SOURCE=..\src\gxcpath.c
# End Source File
# Begin Source File

SOURCE=..\src\gxctable.c
# End Source File
# Begin Source File

SOURCE=..\src\gxdcconv.c
# End Source File
# Begin Source File

SOURCE=..\src\gxdcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\gxdevndi.c
# End Source File
# Begin Source File

SOURCE=..\src\gxdhtserial.c
# End Source File
# Begin Source File

SOURCE=..\src\gxfcopy.c
# End Source File
# Begin Source File

SOURCE=..\src\gxfdrop.c
# End Source File
# Begin Source File

SOURCE=..\src\gxfill.c
# End Source File
# Begin Source File

SOURCE=..\src\gxhintn.c
# End Source File
# Begin Source File

SOURCE=..\src\gxhldevc.c
# End Source File
# Begin Source File

SOURCE=..\src\gxht.c
# End Source File
# Begin Source File

SOURCE=..\src\gxhtbit.c
# End Source File
# Begin Source File

SOURCE=..\src\gxi12bit.c
# End Source File
# Begin Source File

SOURCE=..\src\gxi16bit.c
# End Source File
# Begin Source File

SOURCE=..\src\gxicolor.c
# End Source File
# Begin Source File

SOURCE=..\src\gxidata.c
# End Source File
# Begin Source File

SOURCE=..\src\gxifast.c
# End Source File
# Begin Source File

SOURCE=..\src\gximag3x.c
# End Source File
# Begin Source File

SOURCE=..\src\gximage.c
# End Source File
# Begin Source File

SOURCE=..\src\gximage1.c
# End Source File
# Begin Source File

SOURCE=..\src\gximage2.c
# End Source File
# Begin Source File

SOURCE=..\src\gximage3.c
# End Source File
# Begin Source File

SOURCE=..\src\gximage4.c
# End Source File
# Begin Source File

SOURCE=..\src\gximono.c
# End Source File
# Begin Source File

SOURCE=..\src\gxipixel.c
# End Source File
# Begin Source File

SOURCE=..\src\gxiscale.c
# End Source File
# Begin Source File

SOURCE=..\src\gxmclip.c
# End Source File
# Begin Source File

SOURCE=..\src\gxoprect.c
# End Source File
# Begin Source File

SOURCE=..\src\gxp1fill.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpaint.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpath.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpath2.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpcmap.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpcopy.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpdash.c
# End Source File
# Begin Source File

SOURCE=..\src\gxpflat.c
# End Source File
# Begin Source File

SOURCE=..\src\gxsample.c
# End Source File
# Begin Source File

SOURCE=..\src\gxshade.c
# End Source File
# Begin Source File

SOURCE=..\src\gxshade1.c
# End Source File
# Begin Source File

SOURCE=..\src\gxshade4.c
# End Source File
# Begin Source File

SOURCE=..\src\gxshade6.c
# End Source File
# Begin Source File

SOURCE=..\src\gxstroke.c
# End Source File
# Begin Source File

SOURCE=..\src\gxsync.c
# End Source File
# Begin Source File

SOURCE=..\src\gxttfb.c
# End Source File
# Begin Source File

SOURCE=..\src\gxtype1.c
# End Source File
# Begin Source File

SOURCE=..\src\gxwts.c
# End Source File
# Begin Source File

SOURCE=..\src\gzspotan.c
# End Source File
# Begin Source File

SOURCE=..\src\ialloc.c
# End Source File
# Begin Source File

SOURCE=..\src\iapi.c
# End Source File
# Begin Source File

SOURCE=..\src\ibnum.c
# End Source File
# Begin Source File

SOURCE=..\src\iccinit0.c
# End Source File
# Begin Source File

SOURCE=..\src\icontext.c
# End Source File
# Begin Source File

SOURCE=..\src\idebug.c
# End Source File
# Begin Source File

SOURCE=..\src\idict.c
# End Source File
# Begin Source File

SOURCE=..\src\idisp.c
# End Source File
# Begin Source File

SOURCE=..\src\idparam.c
# End Source File
# Begin Source File

SOURCE=..\src\idstack.c
# End Source File
# Begin Source File

SOURCE=..\src\igc.c
# End Source File
# Begin Source File

SOURCE=..\src\igcref.c
# End Source File
# Begin Source File

SOURCE=..\src\igcstr.c
# End Source File
# Begin Source File

SOURCE=..\src\iinit.c
# End Source File
# Begin Source File

SOURCE=..\src\ilocate.c
# End Source File
# Begin Source File

SOURCE=..\src\imain.c
# End Source File
# Begin Source File

SOURCE=..\src\imainarg.c
# End Source File
# Begin Source File

SOURCE=..\src\iname.c
# End Source File
# Begin Source File

SOURCE=..\src\interp.c
# End Source File
# Begin Source File

SOURCE=..\src\iparam.c
# End Source File
# Begin Source File

SOURCE=..\src\iplugin.c
# End Source File
# Begin Source File

SOURCE=..\src\ireclaim.c
# End Source File
# Begin Source File

SOURCE=..\src\isave.c
# End Source File
# Begin Source File

SOURCE=..\src\iscan.c
# End Source File
# Begin Source File

SOURCE=..\src\iscanbin.c
# End Source File
# Begin Source File

SOURCE=..\src\iscannum.c
# End Source File
# Begin Source File

SOURCE=..\src\istack.c
# End Source File
# Begin Source File

SOURCE=..\src\iutil.c
# End Source File
# Begin Source File

SOURCE=..\src\iutil2.c
# End Source File
# Begin Source File

SOURCE=..\src\md5.c
# End Source File
# Begin Source File

SOURCE=..\src\sa85d.c
# End Source File
# Begin Source File

SOURCE=..\src\sarc4.c
# End Source File
# Begin Source File

SOURCE=..\src\sbcp.c
# End Source File
# Begin Source File

SOURCE=..\src\scantab.c
# End Source File
# Begin Source File

SOURCE=..\src\scfd.c
# End Source File
# Begin Source File

SOURCE=..\src\scfdtab.c
# End Source File
# Begin Source File

SOURCE=..\src\scfe.c
# End Source File
# Begin Source File

SOURCE=..\src\scfetab.c
# End Source File
# Begin Source File

SOURCE=..\src\scfparam.c
# End Source File
# Begin Source File

SOURCE=..\src\sdcparam.c
# End Source File
# Begin Source File

SOURCE=..\src\sdctc.c
# End Source File
# Begin Source File

SOURCE=..\src\sdctd.c
# End Source File
# Begin Source File

SOURCE=..\src\sdcte.c
# End Source File
# Begin Source File

SOURCE=..\src\sddparam.c
# End Source File
# Begin Source File

SOURCE=..\src\sdeparam.c
# End Source File
# Begin Source File

SOURCE=..\src\seexec.c
# End Source File
# Begin Source File

SOURCE=..\src\sfilter1.c
# End Source File
# Begin Source File

SOURCE=..\src\sfilter2.c
# End Source File
# Begin Source File

SOURCE=..\src\sfxstdio.c
# End Source File
# Begin Source File

SOURCE=..\src\shc.c
# End Source File
# Begin Source File

SOURCE=..\src\siinterp.c
# End Source File
# Begin Source File

SOURCE=..\src\siscale.c
# End Source File
# Begin Source File

SOURCE=..\src\sjbig2.c
# End Source File
# Begin Source File

SOURCE=..\src\sjpegc.c
# End Source File
# Begin Source File

SOURCE=..\src\sjpegd.c
# End Source File
# Begin Source File

SOURCE=..\src\sjpege.c
# End Source File
# Begin Source File

SOURCE=..\src\sjpx.c
# End Source File
# Begin Source File

SOURCE=..\src\slzwc.c
# End Source File
# Begin Source File

SOURCE=..\src\slzwce.c
# End Source File
# Begin Source File

SOURCE=..\src\slzwd.c
# End Source File
# Begin Source File

SOURCE=..\src\smd5.c
# End Source File
# Begin Source File

SOURCE=..\src\spdiff.c
# End Source File
# Begin Source File

SOURCE=..\src\spngp.c
# End Source File
# Begin Source File

SOURCE=..\src\spprint.c
# End Source File
# Begin Source File

SOURCE=..\src\spsdf.c
# End Source File
# Begin Source File

SOURCE=..\src\srld.c
# End Source File
# Begin Source File

SOURCE=..\src\srle.c
# End Source File
# Begin Source File

SOURCE=..\src\sstring.c
# End Source File
# Begin Source File

SOURCE=..\src\stream.c
# End Source File
# Begin Source File

SOURCE=..\src\szlibc.c
# End Source File
# Begin Source File

SOURCE=..\src\szlibd.c
# End Source File
# Begin Source File

SOURCE=..\src\szlibe.c
# End Source File
# Begin Source File

SOURCE=..\src\ttcalc.c
# End Source File
# Begin Source File

SOURCE=..\src\ttfinp.c
# End Source File
# Begin Source File

SOURCE=..\src\ttfmain.c
# End Source File
# Begin Source File

SOURCE=..\src\ttfmemd.c
# End Source File
# Begin Source File

SOURCE=..\src\ttinterp.c
# End Source File
# Begin Source File

SOURCE=..\src\ttload.c
# End Source File
# Begin Source File

SOURCE=..\src\ttobjs.c
# End Source File
# Begin Source File

SOURCE=..\src\vdtrace.c
# End Source File
# Begin Source File

SOURCE=..\src\zarith.c
# End Source File
# Begin Source File

SOURCE=..\src\zarray.c
# End Source File
# Begin Source File

SOURCE=..\src\zbfont.c
# End Source File
# Begin Source File

SOURCE=..\src\zbseq.c
# End Source File
# Begin Source File

SOURCE=..\src\zcfont.c
# End Source File
# Begin Source File

SOURCE=..\src\zchar.c
# End Source File
# Begin Source File

SOURCE=..\src\zchar1.c
# End Source File
# Begin Source File

SOURCE=..\src\zchar2.c
# End Source File
# Begin Source File

SOURCE=..\src\zchar32.c
# End Source File
# Begin Source File

SOURCE=..\src\zchar42.c
# End Source File
# Begin Source File

SOURCE=..\src\zcharout.c
# End Source File
# Begin Source File

SOURCE=..\src\zcharx.c
# End Source File
# Begin Source File

SOURCE=..\src\zcid.c
# End Source File
# Begin Source File

SOURCE=..\src\zcie.c
# End Source File
# Begin Source File

SOURCE=..\src\zcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\zcolor1.c
# End Source File
# Begin Source File

SOURCE=..\src\zcolor2.c
# End Source File
# Begin Source File

SOURCE=..\src\zcolor3.c
# End Source File
# Begin Source File

SOURCE=..\src\zcontext.c
# End Source File
# Begin Source File

SOURCE=..\src\zcontrol.c
# End Source File
# Begin Source File

SOURCE=..\src\zcrd.c
# End Source File
# Begin Source File

SOURCE=..\src\zcsdevn.c
# End Source File
# Begin Source File

SOURCE=..\src\zcsindex.c
# End Source File
# Begin Source File

SOURCE=..\src\zcspixel.c
# End Source File
# Begin Source File

SOURCE=..\src\zcssepr.c
# End Source File
# Begin Source File

SOURCE=..\src\zdevcal.c
# End Source File
# Begin Source File

SOURCE=..\src\zdevice.c
# End Source File
# Begin Source File

SOURCE=..\src\zdevice2.c
# End Source File
# Begin Source File

SOURCE=..\src\zdfilter.c
# End Source File
# Begin Source File

SOURCE=..\src\zdict.c
# End Source File
# Begin Source File

SOURCE=..\src\zdpnext.c
# End Source File
# Begin Source File

SOURCE=..\src\zdps.c
# End Source File
# Begin Source File

SOURCE=..\src\zdps1.c
# End Source File
# Begin Source File

SOURCE=..\src\zdscpars.c
# End Source File
# Begin Source File

SOURCE=..\src\zfarc4.c
# End Source File
# Begin Source File

SOURCE=..\src\zfbcp.c
# End Source File
# Begin Source File

SOURCE=..\src\zfcid.c
# End Source File
# Begin Source File

SOURCE=..\src\zfcid0.c
# End Source File
# Begin Source File

SOURCE=..\src\zfcid1.c
# End Source File
# Begin Source File

SOURCE=..\src\zfcmap.c
# End Source File
# Begin Source File

SOURCE=..\src\zfdctd.c
# End Source File
# Begin Source File

SOURCE=..\src\zfdcte.c
# End Source File
# Begin Source File

SOURCE=..\src\zfdecode.c
# End Source File
# Begin Source File

SOURCE=..\src\zfile.c
# End Source File
# Begin Source File

SOURCE=..\src\zfile1.c
# End Source File
# Begin Source File

SOURCE=..\src\zfileio.c
# End Source File
# Begin Source File

SOURCE=..\src\zfilter.c
# End Source File
# Begin Source File

SOURCE=..\src\zfilter2.c
# End Source File
# Begin Source File

SOURCE=..\src\zfjbig2.c
# End Source File
# Begin Source File

SOURCE=..\src\zfjpx.c
# End Source File
# Begin Source File

SOURCE=..\src\zfmd5.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont0.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont1.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont2.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont32.c
# End Source File
# Begin Source File

SOURCE=..\src\zfont42.c
# End Source File
# Begin Source File

SOURCE=..\src\zfontenum.c
# End Source File
# Begin Source File

SOURCE=..\src\zfproc.c
# End Source File
# Begin Source File

SOURCE=..\src\zfrsd.c
# End Source File
# Begin Source File

SOURCE=..\src\zfsample.c
# End Source File
# Begin Source File

SOURCE=..\src\zfunc.c
# End Source File
# Begin Source File

SOURCE=..\src\zfunc0.c
# End Source File
# Begin Source File

SOURCE=..\src\zfunc3.c
# End Source File
# Begin Source File

SOURCE=..\src\zfunc4.c
# End Source File
# Begin Source File

SOURCE=..\src\zfzlib.c
# End Source File
# Begin Source File

SOURCE=..\src\zgeneric.c
# End Source File
# Begin Source File

SOURCE=..\src\zgstate.c
# End Source File
# Begin Source File

SOURCE=..\src\zht.c
# End Source File
# Begin Source File

SOURCE=..\src\zht1.c
# End Source File
# Begin Source File

SOURCE=..\src\zht2.c
# End Source File
# Begin Source File

SOURCE=..\src\zicc.c
# End Source File
# Begin Source File

SOURCE=..\src\zimage.c
# End Source File
# Begin Source File

SOURCE=..\src\zimage2.c
# End Source File
# Begin Source File

SOURCE=..\src\zimage3.c
# End Source File
# Begin Source File

SOURCE=..\src\ziodev.c
# End Source File
# Begin Source File

SOURCE=..\src\ziodev2.c
# End Source File
# Begin Source File

SOURCE=..\src\ziodevsc.c
# End Source File
# Begin Source File

SOURCE=..\src\ziodevst.c
# End Source File
# Begin Source File

SOURCE=..\src\zmath.c
# End Source File
# Begin Source File

SOURCE=..\src\zmatrix.c
# End Source File
# Begin Source File

SOURCE=..\src\zmedia2.c
# End Source File
# Begin Source File

SOURCE=..\src\zmisc.c
# End Source File
# Begin Source File

SOURCE=..\src\zmisc1.c
# End Source File
# Begin Source File

SOURCE=..\src\zmisc2.c
# End Source File
# Begin Source File

SOURCE=..\src\zmisc3.c
# End Source File
# Begin Source File

SOURCE=..\src\zpacked.c
# End Source File
# Begin Source File

SOURCE=..\src\zpaint.c
# End Source File
# Begin Source File

SOURCE=..\src\zpath.c
# End Source File
# Begin Source File

SOURCE=..\src\zpath1.c
# End Source File
# Begin Source File

SOURCE=..\src\zpcolor.c
# End Source File
# Begin Source File

SOURCE=..\src\zrelbit.c
# End Source File
# Begin Source File

SOURCE=..\src\zshade.c
# End Source File
# Begin Source File

SOURCE=..\src\zstack.c
# End Source File
# Begin Source File

SOURCE=..\src\zstring.c
# End Source File
# Begin Source File

SOURCE=..\src\zsysvm.c
# End Source File
# Begin Source File

SOURCE=..\src\ztoken.c
# End Source File
# Begin Source File

SOURCE=..\src\ztrans.c
# End Source File
# Begin Source File

SOURCE=..\src\ztype.c
# End Source File
# Begin Source File

SOURCE=..\src\zupath.c
# End Source File
# Begin Source File

SOURCE=..\src\zusparam.c
# End Source File
# Begin Source File

SOURCE=..\src\zvmem.c
# End Source File
# Begin Source File

SOURCE=..\src\zvmem2.c
# End Source File
# End Group
# Begin Group "gs8 Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\src\bfont.h
# End Source File
# Begin Source File

SOURCE=..\src\btoken.h
# End Source File
# Begin Source File

SOURCE=..\src\ccfont.h
# End Source File
# Begin Source File

SOURCE=..\src\ctype_.h
# End Source File
# Begin Source File

SOURCE=..\src\dirent_.h
# End Source File
# Begin Source File

SOURCE=..\src\dos_.h
# End Source File
# Begin Source File

SOURCE=..\src\dscparse.h
# End Source File
# Begin Source File

SOURCE=..\src\dstack.h
# End Source File
# Begin Source File

SOURCE=..\src\dwdll.h
# End Source File
# Begin Source File

SOURCE=..\src\dwimg.h
# End Source File
# Begin Source File

SOURCE=..\src\dwinst.h
# End Source File
# Begin Source File

SOURCE=..\src\dwmain.h
# End Source File
# Begin Source File

SOURCE=..\src\dwreg.h
# End Source File
# Begin Source File

SOURCE=..\src\dwsetup.h
# End Source File
# Begin Source File

SOURCE=..\src\dwtext.h
# End Source File
# Begin Source File

SOURCE=..\src\dwtrace.h
# End Source File
# Begin Source File

SOURCE=..\src\dwuninst.h
# End Source File
# Begin Source File

SOURCE=..\src\errno_.h
# End Source File
# Begin Source File

SOURCE=..\src\errors.h
# End Source File
# Begin Source File

SOURCE=..\src\estack.h
# End Source File
# Begin Source File

SOURCE=..\src\fcntl_.h
# End Source File
# Begin Source File

SOURCE=..\src\files.h
# End Source File
# Begin Source File

SOURCE=..\src\gconf.h
# End Source File
# Begin Source File

SOURCE=..\include\gconfigd.h
# End Source File
# Begin Source File

SOURCE=..\src\gdebug.h
# End Source File
# Begin Source File

SOURCE=..\src\gdev8bcm.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevbbox.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevbjc.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevbjcl.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevbmp.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevcgml.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevcgmx.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevcmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevdcrd.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevddrw.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevdevn.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevdljm.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevdsp.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevdsp2.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevfax.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmac.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmacpictop.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmacttf.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmeds.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmem.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmgr.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmpla.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmrop.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmrun.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevmswn.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevp14.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpccm.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpcfb.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpcl.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfc.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfg.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfo.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdfx.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdt.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtb.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtd.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtf.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdti.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdts.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtt.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtv.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtw.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpdtx.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevplnx.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpm.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevppla.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevprn.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevprna.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsdf.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsds.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsf.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpsu.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpxat.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpxen.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpxop.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevpxut.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevsgi.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevstc.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevsvga.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevtfax.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevtifs.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevvec.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevx.h
# End Source File
# Begin Source File

SOURCE=..\src\gdevxcmp.h
# End Source File
# Begin Source File

SOURCE=..\src\ghost.h
# End Source File
# Begin Source File

SOURCE=..\src\gp.h
# End Source File
# Begin Source File

SOURCE=..\src\gp_mac.h
# End Source File
# Begin Source File

SOURCE=..\src\gp_mswin.h
# End Source File
# Begin Source File

SOURCE=..\src\gpcheck.h
# End Source File
# Begin Source File

SOURCE=..\src\gpgetenv.h
# End Source File
# Begin Source File

SOURCE=..\src\gpmisc.h
# End Source File
# Begin Source File

SOURCE=..\src\gpsync.h
# End Source File
# Begin Source File

SOURCE=..\src\gsalloc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsalpha.h
# End Source File
# Begin Source File

SOURCE=..\src\gsalphac.h
# End Source File
# Begin Source File

SOURCE=..\src\gsargs.h
# End Source File
# Begin Source File

SOURCE=..\src\gsbitmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gsbitops.h
# End Source File
# Begin Source File

SOURCE=..\src\gsbittab.h
# End Source File
# Begin Source File

SOURCE=..\src\gsccode.h
# End Source File
# Begin Source File

SOURCE=..\src\gsccolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gscdefs.h
# End Source File
# Begin Source File

SOURCE=..\src\gscdevn.h
# End Source File
# Begin Source File

SOURCE=..\src\gscedata.h
# End Source File
# Begin Source File

SOURCE=..\src\gscencs.h
# End Source File
# Begin Source File

SOURCE=..\src\gschar.h
# End Source File
# Begin Source File

SOURCE=..\src\gscie.h
# End Source File
# Begin Source File

SOURCE=..\src\gscindex.h
# End Source File
# Begin Source File

SOURCE=..\src\gsclipsr.h
# End Source File
# Begin Source File

SOURCE=..\src\gscolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gscolor1.h
# End Source File
# Begin Source File

SOURCE=..\src\gscolor2.h
# End Source File
# Begin Source File

SOURCE=..\src\gscolor3.h
# End Source File
# Begin Source File

SOURCE=..\src\gscompt.h
# End Source File
# Begin Source File

SOURCE=..\src\gscoord.h
# End Source File
# Begin Source File

SOURCE=..\src\gscpixel.h
# End Source File
# Begin Source File

SOURCE=..\src\gscpm.h
# End Source File
# Begin Source File

SOURCE=..\src\gscrd.h
# End Source File
# Begin Source File

SOURCE=..\src\gscrdp.h
# End Source File
# Begin Source File

SOURCE=..\src\gscrypt1.h
# End Source File
# Begin Source File

SOURCE=..\src\gscsel.h
# End Source File
# Begin Source File

SOURCE=..\src\gscsepr.h
# End Source File
# Begin Source File

SOURCE=..\src\gscspace.h
# End Source File
# Begin Source File

SOURCE=..\src\gscssub.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdcolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdevice.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdfilt.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdll.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdllos2.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdllwin.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdpnext.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdps.h
# End Source File
# Begin Source File

SOURCE=..\src\gsdsrc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsequivc.h
# End Source File
# Begin Source File

SOURCE=..\src\gserror.h
# End Source File
# Begin Source File

SOURCE=..\src\gserrors.h
# End Source File
# Begin Source File

SOURCE=..\src\gsexit.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfcmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gsflip.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfname.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfont.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc0.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc3.h
# End Source File
# Begin Source File

SOURCE=..\src\gsfunc4.h
# End Source File
# Begin Source File

SOURCE=..\src\gsgc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsgcache.h
# End Source File
# Begin Source File

SOURCE=..\src\gsgdata.h
# End Source File
# Begin Source File

SOURCE=..\src\gshsb.h
# End Source File
# Begin Source File

SOURCE=..\src\gsht.h
# End Source File
# Begin Source File

SOURCE=..\src\gsht1.h
# End Source File
# Begin Source File

SOURCE=..\src\gshtx.h
# End Source File
# Begin Source File

SOURCE=..\src\gsicc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsimage.h
# End Source File
# Begin Source File

SOURCE=..\src\gsio.h
# End Source File
# Begin Source File

SOURCE=..\src\gsipar3x.h
# End Source File
# Begin Source File

SOURCE=..\src\gsiparam.h
# End Source File
# Begin Source File

SOURCE=..\src\gsiparm2.h
# End Source File
# Begin Source File

SOURCE=..\src\gsiparm3.h
# End Source File
# Begin Source File

SOURCE=..\src\gsiparm4.h
# End Source File
# Begin Source File

SOURCE=..\src\gsjconf.h
# End Source File
# Begin Source File

SOURCE=..\src\gsjmorec.h
# End Source File
# Begin Source File

SOURCE=..\src\gslib.h
# End Source File
# Begin Source File

SOURCE=..\src\gsline.h
# End Source File
# Begin Source File

SOURCE=..\src\gslparam.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmalloc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmdebug.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmemlok.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmemory.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmemraw.h
# End Source File
# Begin Source File

SOURCE=..\src\gsmemret.h
# End Source File
# Begin Source File

SOURCE=..\src\gsnogc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsnotify.h
# End Source File
# Begin Source File

SOURCE=..\src\gsovrc.h
# End Source File
# Begin Source File

SOURCE=..\src\gspaint.h
# End Source File
# Begin Source File

SOURCE=..\src\gsparam.h
# End Source File
# Begin Source File

SOURCE=..\src\gsparams.h
# End Source File
# Begin Source File

SOURCE=..\src\gsparamx.h
# End Source File
# Begin Source File

SOURCE=..\src\gspath.h
# End Source File
# Begin Source File

SOURCE=..\src\gspath2.h
# End Source File
# Begin Source File

SOURCE=..\src\gspcolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gspenum.h
# End Source File
# Begin Source File

SOURCE=..\src\gspmdrv.h
# End Source File
# Begin Source File

SOURCE=..\src\gsptype1.h
# End Source File
# Begin Source File

SOURCE=..\src\gsptype2.h
# End Source File
# Begin Source File

SOURCE=..\src\gsrect.h
# End Source File
# Begin Source File

SOURCE=..\src\gsrefct.h
# End Source File
# Begin Source File

SOURCE=..\src\gsrop.h
# End Source File
# Begin Source File

SOURCE=..\src\gsropc.h
# End Source File
# Begin Source File

SOURCE=..\src\gsropt.h
# End Source File
# Begin Source File

SOURCE=..\src\gsserial.h
# End Source File
# Begin Source File

SOURCE=..\src\gsshade.h
# End Source File
# Begin Source File

SOURCE=..\src\gsstate.h
# End Source File
# Begin Source File

SOURCE=..\src\gsstruct.h
# End Source File
# Begin Source File

SOURCE=..\src\gsstype.h
# End Source File
# Begin Source File

SOURCE=..\src\gstext.h
# End Source File
# Begin Source File

SOURCE=..\src\gstparam.h
# End Source File
# Begin Source File

SOURCE=..\src\gstrans.h
# End Source File
# Begin Source File

SOURCE=..\src\gstrap.h
# End Source File
# Begin Source File

SOURCE=..\src\gstype1.h
# End Source File
# Begin Source File

SOURCE=..\src\gstypes.h
# End Source File
# Begin Source File

SOURCE=..\src\gsuid.h
# End Source File
# Begin Source File

SOURCE=..\src\gsutil.h
# End Source File
# Begin Source File

SOURCE=..\src\gswts.h
# End Source File
# Begin Source File

SOURCE=..\src\gsxfont.h
# End Source File
# Begin Source File

SOURCE=..\src\gx.h
# End Source File
# Begin Source File

SOURCE=..\src\gxalloc.h
# End Source File
# Begin Source File

SOURCE=..\src\gxalpha.h
# End Source File
# Begin Source File

SOURCE=..\src\gxarith.h
# End Source File
# Begin Source File

SOURCE=..\src\gxband.h
# End Source File
# Begin Source File

SOURCE=..\src\gxbcache.h
# End Source File
# Begin Source File

SOURCE=..\src\gxbitfmt.h
# End Source File
# Begin Source File

SOURCE=..\src\gxbitmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gxbitops.h
# End Source File
# Begin Source File

SOURCE=..\src\gxblend.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcdevn.h
# End Source File
# Begin Source File

SOURCE=..\src\gxchar.h
# End Source File
# Begin Source File

SOURCE=..\src\gxchrout.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcid.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcie.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcindex.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcldev.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclio.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclip.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclip2.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclipm.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclipsr.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclist.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclmem.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclpage.h
# End Source File
# Begin Source File

SOURCE=..\src\gxclpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcolor2.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcomp.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcoord.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcspace.h
# End Source File
# Begin Source File

SOURCE=..\src\gxctable.h
# End Source File
# Begin Source File

SOURCE=..\src\gxcvalue.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdcconv.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdcolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdda.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevbuf.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevcli.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevice.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevmem.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevndi.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdevrop.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdht.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdhtres.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdhtserial.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdither.h
# End Source File
# Begin Source File

SOURCE=..\src\gxdtfill.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfapi.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfarith.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfcache.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfcid.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfcmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfcmap1.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfcopy.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfdrop.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfill.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfillsl.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfilltr.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfillts.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfixed.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfont.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfont0.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfont0c.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfont1.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfont42.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfrac.h
# End Source File
# Begin Source File

SOURCE=..\src\gxftype.h
# End Source File
# Begin Source File

SOURCE=..\src\gxfunc.h
# End Source File
# Begin Source File

SOURCE=..\src\gxgetbit.h
# End Source File
# Begin Source File

SOURCE=..\src\gxhintn.h
# End Source File
# Begin Source File

SOURCE=..\src\gxhldevc.h
# End Source File
# Begin Source File

SOURCE=..\src\gxht.h
# End Source File
# Begin Source File

SOURCE=..\src\gxhttile.h
# End Source File
# Begin Source File

SOURCE=..\src\gxhttype.h
# End Source File
# Begin Source File

SOURCE=..\src\gxiclass.h
# End Source File
# Begin Source File

SOURCE=..\src\gximag3x.h
# End Source File
# Begin Source File

SOURCE=..\src\gximage.h
# End Source File
# Begin Source File

SOURCE=..\src\gximage3.h
# End Source File
# Begin Source File

SOURCE=..\src\gxiodev.h
# End Source File
# Begin Source File

SOURCE=..\src\gxiparam.h
# End Source File
# Begin Source File

SOURCE=..\src\gxistate.h
# End Source File
# Begin Source File

SOURCE=..\src\gxline.h
# End Source File
# Begin Source File

SOURCE=..\src\gxlum.h
# End Source File
# Begin Source File

SOURCE=..\src\gxmatrix.h
# End Source File
# Begin Source File

SOURCE=..\src\gxmclip.h
# End Source File
# Begin Source File

SOURCE=..\src\gxobj.h
# End Source File
# Begin Source File

SOURCE=..\src\gxop1.h
# End Source File
# Begin Source File

SOURCE=..\src\gxoprect.h
# End Source File
# Begin Source File

SOURCE=..\src\gxp1impl.h
# End Source File
# Begin Source File

SOURCE=..\src\gxpageq.h
# End Source File
# Begin Source File

SOURCE=..\src\gxpaint.h
# End Source File
# Begin Source File

SOURCE=..\src\gxpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gxpcache.h
# End Source File
# Begin Source File

SOURCE=..\src\gxpcolor.h
# End Source File
# Begin Source File

SOURCE=..\src\gxropc.h
# End Source File
# Begin Source File

SOURCE=..\src\gxrplane.h
# End Source File
# Begin Source File

SOURCE=..\src\gxsample.h
# End Source File
# Begin Source File

SOURCE=..\src\gxshade.h
# End Source File
# Begin Source File

SOURCE=..\src\gxshade4.h
# End Source File
# Begin Source File

SOURCE=..\src\gxstate.h
# End Source File
# Begin Source File

SOURCE=..\src\gxstdio.h
# End Source File
# Begin Source File

SOURCE=..\src\gxsync.h
# End Source File
# Begin Source File

SOURCE=..\src\gxtext.h
# End Source File
# Begin Source File

SOURCE=..\src\gxtmap.h
# End Source File
# Begin Source File

SOURCE=..\src\gxttf.h
# End Source File
# Begin Source File

SOURCE=..\src\gxttfb.h
# End Source File
# Begin Source File

SOURCE=..\src\gxtype1.h
# End Source File
# Begin Source File

SOURCE=..\src\gxwts.h
# End Source File
# Begin Source File

SOURCE=..\src\gxxfont.h
# End Source File
# Begin Source File

SOURCE=..\src\gzacpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gzcpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gzht.h
# End Source File
# Begin Source File

SOURCE=..\src\gzline.h
# End Source File
# Begin Source File

SOURCE=..\src\gzpath.h
# End Source File
# Begin Source File

SOURCE=..\src\gzspotan.h
# End Source File
# Begin Source File

SOURCE=..\src\gzstate.h
# End Source File
# Begin Source File

SOURCE=..\src\ialloc.h
# End Source File
# Begin Source File

SOURCE=..\src\iapi.h
# End Source File
# Begin Source File

SOURCE=..\src\iastate.h
# End Source File
# Begin Source File

SOURCE=..\src\iastruct.h
# End Source File
# Begin Source File

SOURCE=..\src\ibnum.h
# End Source File
# Begin Source File

SOURCE=..\src\ichar.h
# End Source File
# Begin Source File

SOURCE=..\src\ichar1.h
# End Source File
# Begin Source File

SOURCE=..\src\icharout.h
# End Source File
# Begin Source File

SOURCE=..\src\icid.h
# End Source File
# Begin Source File

SOURCE=..\src\icie.h
# End Source File
# Begin Source File

SOURCE=..\src\icolor.h
# End Source File
# Begin Source File

SOURCE=..\src\iconf.h
# End Source File
# Begin Source File

SOURCE=..\src\icontext.h
# End Source File
# Begin Source File

SOURCE=..\src\icremap.h
# End Source File
# Begin Source File

SOURCE=..\src\icsmap.h
# End Source File
# Begin Source File

SOURCE=..\src\icstate.h
# End Source File
# Begin Source File

SOURCE=..\src\iddict.h
# End Source File
# Begin Source File

SOURCE=..\src\iddstack.h
# End Source File
# Begin Source File

SOURCE=..\src\idebug.h
# End Source File
# Begin Source File

SOURCE=..\src\idict.h
# End Source File
# Begin Source File

SOURCE=..\src\idictdef.h
# End Source File
# Begin Source File

SOURCE=..\src\idisp.h
# End Source File
# Begin Source File

SOURCE=..\src\idosave.h
# End Source File
# Begin Source File

SOURCE=..\src\idparam.h
# End Source File
# Begin Source File

SOURCE=..\src\idsdata.h
# End Source File
# Begin Source File

SOURCE=..\src\idstack.h
# End Source File
# Begin Source File

SOURCE=..\src\ierrors.h
# End Source File
# Begin Source File

SOURCE=..\src\iesdata.h
# End Source File
# Begin Source File

SOURCE=..\src\iestack.h
# End Source File
# Begin Source File

SOURCE=..\src\ifapi.h
# End Source File
# Begin Source File

SOURCE=..\src\ifcid.h
# End Source File
# Begin Source File

SOURCE=..\src\ifilter.h
# End Source File
# Begin Source File

SOURCE=..\src\ifilter2.h
# End Source File
# Begin Source File

SOURCE=..\src\ifont.h
# End Source File
# Begin Source File

SOURCE=..\src\ifont1.h
# End Source File
# Begin Source File

SOURCE=..\src\ifont2.h
# End Source File
# Begin Source File

SOURCE=..\src\ifont42.h
# End Source File
# Begin Source File

SOURCE=..\src\ifrpred.h
# End Source File
# Begin Source File

SOURCE=..\src\ifunc.h
# End Source File
# Begin Source File

SOURCE=..\src\ifwpred.h
# End Source File
# Begin Source File

SOURCE=..\src\igc.h
# End Source File
# Begin Source File

SOURCE=..\src\igcstr.h
# End Source File
# Begin Source File

SOURCE=..\src\igstate.h
# End Source File
# Begin Source File

SOURCE=..\src\iht.h
# End Source File
# Begin Source File

SOURCE=..\src\iimage.h
# End Source File
# Begin Source File

SOURCE=..\src\iimage2.h
# End Source File
# Begin Source File

SOURCE=..\src\iinit.h
# End Source File
# Begin Source File

SOURCE=..\src\ilevel.h
# End Source File
# Begin Source File

SOURCE=..\src\imain.h
# End Source File
# Begin Source File

SOURCE=..\src\imainarg.h
# End Source File
# Begin Source File

SOURCE=..\src\imemory.h
# End Source File
# Begin Source File

SOURCE=..\src\iminst.h
# End Source File
# Begin Source File

SOURCE=..\src\iname.h
# End Source File
# Begin Source File

SOURCE=..\src\inamedef.h
# End Source File
# Begin Source File

SOURCE=..\src\inameidx.h
# End Source File
# Begin Source File

SOURCE=..\src\inames.h
# End Source File
# Begin Source File

SOURCE=..\src\inamestr.h
# End Source File
# Begin Source File

SOURCE=..\src\interp.h
# End Source File
# Begin Source File

SOURCE=..\src\iosdata.h
# End Source File
# Begin Source File

SOURCE=..\src\iostack.h
# End Source File
# Begin Source File

SOURCE=..\src\ipacked.h
# End Source File
# Begin Source File

SOURCE=..\src\iparam.h
# End Source File
# Begin Source File

SOURCE=..\src\iparray.h
# End Source File
# Begin Source File

SOURCE=..\src\ipcolor.h
# End Source File
# Begin Source File

SOURCE=..\src\iplugin.h
# End Source File
# Begin Source File

SOURCE=..\src\iref.h
# End Source File
# Begin Source File

SOURCE=..\src\isave.h
# End Source File
# Begin Source File

SOURCE=..\src\iscan.h
# End Source File
# Begin Source File

SOURCE=..\src\iscanbin.h
# End Source File
# Begin Source File

SOURCE=..\src\iscannum.h
# End Source File
# Begin Source File

SOURCE=..\src\isdata.h
# End Source File
# Begin Source File

SOURCE=..\src\isstate.h
# End Source File
# Begin Source File

SOURCE=..\src\istack.h
# End Source File
# Begin Source File

SOURCE=..\src\istkparm.h
# End Source File
# Begin Source File

SOURCE=..\src\istream.h
# End Source File
# Begin Source File

SOURCE=..\src\istruct.h
# End Source File
# Begin Source File

SOURCE=..\src\itoken.h
# End Source File
# Begin Source File

SOURCE=..\src\iutil.h
# End Source File
# Begin Source File

SOURCE=..\src\iutil2.h
# End Source File
# Begin Source File

SOURCE=..\src\ivmem2.h
# End Source File
# Begin Source File

SOURCE=..\src\ivmspace.h
# End Source File
# Begin Source File

SOURCE=..\src\jerror_.h
# End Source File
# Begin Source File

SOURCE=..\src\macos_carbon_d_pre.h
# End Source File
# Begin Source File

SOURCE=..\src\macos_carbon_pre.h
# End Source File
# Begin Source File

SOURCE=..\src\macos_classic_d_pre.h
# End Source File
# Begin Source File

SOURCE=..\src\macsystypes.h
# End Source File
# Begin Source File

SOURCE=..\src\main.h
# End Source File
# Begin Source File

SOURCE=..\src\malloc_.h
# End Source File
# Begin Source File

SOURCE=..\src\math_.h
# End Source File
# Begin Source File

SOURCE=..\src\md5.h
# End Source File
# Begin Source File

SOURCE=..\src\memory_.h
# End Source File
# Begin Source File

SOURCE=..\src\oparc.h
# End Source File
# Begin Source File

SOURCE=..\src\opcheck.h
# End Source File
# Begin Source File

SOURCE=..\src\opdef.h
# End Source File
# Begin Source File

SOURCE=..\src\oper.h
# End Source File
# Begin Source File

SOURCE=..\src\opextern.h
# End Source File
# Begin Source File

SOURCE=..\src\ostack.h
# End Source File
# Begin Source File

SOURCE=..\src\pipe_.h
# End Source File
# Begin Source File

SOURCE=..\src\png_.h
# End Source File
# Begin Source File

SOURCE=..\src\sa85d.h
# End Source File
# Begin Source File

SOURCE=..\src\sa85x.h
# End Source File
# Begin Source File

SOURCE=..\src\sarc4.h
# End Source File
# Begin Source File

SOURCE=..\src\sbcp.h
# End Source File
# Begin Source File

SOURCE=..\src\sbhc.h
# End Source File
# Begin Source File

SOURCE=..\src\sbtx.h
# End Source File
# Begin Source File

SOURCE=..\src\sbwbs.h
# End Source File
# Begin Source File

SOURCE=..\src\scanchar.h
# End Source File
# Begin Source File

SOURCE=..\src\scf.h
# End Source File
# Begin Source File

SOURCE=..\src\scfx.h
# End Source File
# Begin Source File

SOURCE=..\src\scommon.h
# End Source File
# Begin Source File

SOURCE=..\src\sdcparam.h
# End Source File
# Begin Source File

SOURCE=..\src\sdct.h
# End Source File
# Begin Source File

SOURCE=..\src\sfilter.h
# End Source File
# Begin Source File

SOURCE=..\src\shc.h
# End Source File
# Begin Source File

SOURCE=..\src\shcgen.h
# End Source File
# Begin Source File

SOURCE=..\src\siinterp.h
# End Source File
# Begin Source File

SOURCE=..\src\siscale.h
# End Source File
# Begin Source File

SOURCE=..\src\sisparam.h
# End Source File
# Begin Source File

SOURCE=..\src\sjbig2.h
# End Source File
# Begin Source File

SOURCE=..\src\sjpeg.h
# End Source File
# Begin Source File

SOURCE=..\src\slzwx.h
# End Source File
# Begin Source File

SOURCE=..\src\smd5.h
# End Source File
# Begin Source File

SOURCE=..\src\smtf.h
# End Source File
# Begin Source File

SOURCE=..\src\spdiffx.h
# End Source File
# Begin Source File

SOURCE=..\src\spngpx.h
# End Source File
# Begin Source File

SOURCE=..\src\spprint.h
# End Source File
# Begin Source File

SOURCE=..\src\spsdf.h
# End Source File
# Begin Source File

SOURCE=..\src\srdline.h
# End Source File
# Begin Source File

SOURCE=..\src\srlx.h
# End Source File
# Begin Source File

SOURCE=..\src\sstring.h
# End Source File
# Begin Source File

SOURCE=..\src\stat_.h
# End Source File
# Begin Source File

SOURCE=..\src\std.h
# End Source File
# Begin Source File

SOURCE=..\src\stdint_.h
# End Source File
# Begin Source File

SOURCE=..\src\stdio_.h
# End Source File
# Begin Source File

SOURCE=..\src\stdpn.h
# End Source File
# Begin Source File

SOURCE=..\src\stdpre.h
# End Source File
# Begin Source File

SOURCE=..\src\store.h
# End Source File
# Begin Source File

SOURCE=..\src\stream.h
# End Source File
# Begin Source File

SOURCE=..\src\strimpl.h
# End Source File
# Begin Source File

SOURCE=..\src\string_.h
# End Source File
# Begin Source File

SOURCE=..\src\szlibx.h
# End Source File
# Begin Source File

SOURCE=..\src\szlibxx.h
# End Source File
# Begin Source File

SOURCE=..\src\time_.h
# End Source File
# Begin Source File

SOURCE=..\src\ttcalc.h
# End Source File
# Begin Source File

SOURCE=..\src\ttcommon.h
# End Source File
# Begin Source File

SOURCE=..\src\ttconf.h
# End Source File
# Begin Source File

SOURCE=..\src\ttconfig.h
# End Source File
# Begin Source File

SOURCE=..\src\ttfinp.h
# End Source File
# Begin Source File

SOURCE=..\src\ttfmemd.h
# End Source File
# Begin Source File

SOURCE=..\src\ttfoutl.h
# End Source File
# Begin Source File

SOURCE=..\src\ttfsfnt.h
# End Source File
# Begin Source File

SOURCE=..\src\ttinterp.h
# End Source File
# Begin Source File

SOURCE=..\src\ttload.h
# End Source File
# Begin Source File

SOURCE=..\src\ttmisc.h
# End Source File
# Begin Source File

SOURCE=..\src\ttobjs.h
# End Source File
# Begin Source File

SOURCE=..\src\tttables.h
# End Source File
# Begin Source File

SOURCE=..\src\tttype.h
# End Source File
# Begin Source File

SOURCE=..\src\tttypes.h
# End Source File
# Begin Source File

SOURCE=..\src\unistd_.h
# End Source File
# Begin Source File

SOURCE=..\src\vdtrace.h
# End Source File
# Begin Source File

SOURCE=..\src\vms_x_fix.h
# End Source File
# Begin Source File

SOURCE=..\src\vmsmath.h
# End Source File
# Begin Source File

SOURCE=..\src\windows_.h
# End Source File
# Begin Source File

SOURCE=..\src\wrfont.h
# End Source File
# Begin Source File

SOURCE=..\src\write_t1.h
# End Source File
# Begin Source File

SOURCE=..\src\write_t2.h
# End Source File
# Begin Source File

SOURCE=..\src\zchar42.h
# End Source File
# Begin Source File

SOURCE=..\src\zht2.h
# End Source File
# End Group
# Begin Group "gs8 rinkj"

# PROP Default_Filter "c;h"
# Begin Source File

SOURCE="..\src\rinkj\evenbetter-rll.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\evenbetter-rll.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-byte-stream.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-byte-stream.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-config.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-config.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-device.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-device.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-dither.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-dither.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-epson870.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-epson870.h"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-screen-eb.c"
# End Source File
# Begin Source File

SOURCE="..\src\rinkj\rinkj-screen-eb.h"
# End Source File
# End Group
# Begin Group "FL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\th\src\anytoi.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\anytoi.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\crc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\doscan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\fileio.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\fileio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\heap.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\heap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\memmgr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\memmgr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\printfe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\printfe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\rand.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\ssubs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\ssubs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thassert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thdirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\therrno.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\therror.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\therror.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thfcntl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thfl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thfl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thfli.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thmalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\threent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thstat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thstdio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thstdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thstring.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thtime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thunistd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\thvinfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\uuencode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\uuencode.h
# End Source File
# End Group
# Begin Group "AL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\changelog.txt

!IF  "$(CFG)" == "gs8 - Win32 Release"

!ELSEIF  "$(CFG)" == "gs8 - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\dirent_msvc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\dirent_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\eembc_dt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\heapport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\thal.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\thcfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\thconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\thstdint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\thtypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\x86\al\tmain.c
# End Source File
# End Group
# End Target
# End Project
