# Microsoft Developer Studio Project File - Name="libth_lite" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libth_lite - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libth_lite.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libth_lite.mak" CFG="libth_lite - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libth_lite - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libth_lite - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libth_lite - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libth_lite___Win32_Release"
# PROP BASE Intermediate_Dir "libth_lite___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseLib_Lite"
# PROP Intermediate_Dir "ReleaseLib_Lite"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\..\th_lite\x86\al" /I "..\..\..\th_lite\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libth_lite - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libth_lite___Win32_Debug"
# PROP BASE Intermediate_Dir "libth_lite___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugLib_Lite"
# PROP Intermediate_Dir "DebugLib_Lite"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W4 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th_lite\x86\al" /I "..\..\..\th_lite\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "libth_lite - Win32 Release"
# Name "libth_lite - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "TH"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\th_lite\src\crc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\doscan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\filedata.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\fileio.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\fileio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\heap.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_Lite\src\heap.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\printfe.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\printfe.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\rand.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\ssubs.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\ssubs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_Lite\src\thal.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thassert.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thdirent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th\src\therrno.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\therrno.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\therror.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thfcntl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thfl.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thfl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thlib.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_Lite\src\thlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thmalloc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\threent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thstat.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thstdio.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thstdlib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thstring.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thtime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thtypes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thunistd.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\thvinfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\uuencode.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\src\uuencode.h
# End Source File
# End Group
# Begin Group "AL"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\changelog.txt

!IF  "$(CFG)" == "libth_lite - Win32 Release"

!ELSEIF  "$(CFG)" == "libth_lite - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\dirent_msvc.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\dirent_msvc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\eembc_dt.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\heapport.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\thal.c
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\thcfg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\thconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\thstdint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\th_lite\x86\al\thtypes.h
# End Source File
# End Group
# End Target
# End Project
