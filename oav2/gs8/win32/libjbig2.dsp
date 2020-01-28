# Microsoft Developer Studio Project File - Name="libjbig2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libjbig2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libjbig2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libjbig2.mak" CFG="libjbig2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libjbig2 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libjbig2 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libjbig2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libjbig2_Release"
# PROP Intermediate_Dir "libjbig2_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Ze /W3 /GX /O2 /I "..\jbig2dec" /I "..\libpng" /I "..\zlib" /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D HAVE_STRING_H=1 /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libjbig2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libjbig2___Win32_Debug"
# PROP BASE Intermediate_Dir "libjbig2___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libjbig2_Debug"
# PROP Intermediate_Dir "libjbig2_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Ze /W3 /Gm /GX /ZI /Od /I "..\jbig2dec" /I "..\libpng" /I "..\zlib" /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D HAVE_STRING_H=1 /FR /YX /FD /GZ /c
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

# Name "libjbig2 - Win32 Release"
# Name "libjbig2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\jbig2dec\getopt.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\getopt1.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith_iaid.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith_int.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_generic.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_huffman.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_image.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_image_pbm.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_image_png.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_metadata.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_mmr.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_page.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_segment.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_symbol_dict.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_text.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\memcmp.c
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\sha1.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\jbig2dec\config_types.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\config_win32.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\getopt.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith_iaid.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_arith_int.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_generic.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_huffman.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_hufftab.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_image.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_metadata.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_mmr.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_priv.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\jbig2_symbol_dict.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\os_types.h
# End Source File
# Begin Source File

SOURCE=..\jbig2dec\sha1.h
# End Source File
# End Group
# End Target
# End Project
