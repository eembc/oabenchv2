# Microsoft Developer Studio Project File - Name="ditherv2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ditherv2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ditherv2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ditherv2.mak" CFG="ditherv2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ditherv2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ditherv2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ditherv2 - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ditherv2 - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "DATA_2" /FR /YX /FD /GZ /c
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

# Name "ditherv2 - Win32 Release"
# Name "ditherv2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\bmark.c
# End Source File
# Begin Source File

SOURCE=..\dither.c
# End Source File
# Begin Source File

SOURCE=..\imageio.c
# End Source File
# Begin Source File

SOURCE=..\..\libpgm\libpgm_single.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\algo.h
# End Source File
# Begin Source File

SOURCE=..\dither.h
# End Source File
# Begin Source File

SOURCE=..\imageio.h
# End Source File
# Begin Source File

SOURCE=..\kernel.h
# End Source File
# Begin Source File

SOURCE=..\masks.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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
