# Microsoft Developer Studio Project File - Name="libth" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libth - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libth.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libth.mak" CFG="libth - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libth - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libth - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libth - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libth___Win32_Release"
# PROP BASE Intermediate_Dir "libth___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseLib"
# PROP Intermediate_Dir "ReleaseLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libth - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libth___Win32_Debug"
# PROP BASE Intermediate_Dir "libth___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugLib"
# PROP Intermediate_Dir "DebugLib"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libth - Win32 Release"
# Name "libth - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
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

SOURCE=..\..\..\th\src\thtypes.h
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

!IF  "$(CFG)" == "libth - Win32 Release"

!ELSEIF  "$(CFG)" == "libth - Win32 Debug"

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
