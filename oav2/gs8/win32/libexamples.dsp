# Microsoft Developer Studio Project File - Name="libexamples" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libexamples - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libexamples.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libexamples.mak" CFG="libexamples - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libexamples - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libexamples - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libexamples - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libexamples___Win32_Release"
# PROP BASE Intermediate_Dir "libexamples___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libexamples_Release"
# PROP Intermediate_Dir "libexamples_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /Zm800 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libexamples - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libexamples___Win32_Debug"
# PROP BASE Intermediate_Dir "libexamples___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libexamples_Debug"
# PROP Intermediate_Dir "libexamples_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /Zm800 /GZ /c
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

# Name "libexamples - Win32 Release"
# Name "libexamples - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\libexamples\alphabet_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\annots_pdf_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\chess_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\colorcir_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\doretree_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\escher_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\golfer_eps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\grayalph_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\journal_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\ppst56_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\ridt91_eps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\snowflak_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\tiger_eps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\vasarely_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libexamples\waterfal_ps_init.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\libexamples\alphabet_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\annots_pdf.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\chess_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\colorcir_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\doretree_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\escher_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\golfer_eps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\grayalph_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\journal_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\ppst56_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\ridt91_eps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\snowflak_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\tiger_eps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\vasarely_ps.h
# End Source File
# Begin Source File

SOURCE=..\libexamples\waterfal_ps.h
# End Source File
# End Group
# End Target
# End Project
