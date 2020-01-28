# Microsoft Developer Studio Project File - Name="libfonts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libfonts - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libfonts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libfonts.mak" CFG="libfonts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libfonts - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libfonts - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libfonts - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libfonts_Release"
# PROP Intermediate_Dir "libfonts_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /Ze /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libfonts - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libfonts___Win32_Debug"
# PROP BASE Intermediate_Dir "libfonts___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libfonts_Debug"
# PROP Intermediate_Dir "libfonts_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Ze /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "libfonts - Win32 Release"
# Name "libfonts - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\libfonts\a010013l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010013l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010013l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\fonts_dir_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\fonts_scale_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_pfm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_pfb_init.c
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_pfm_init.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\libfonts\a010013l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010013l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010013l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010015l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010033l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\a010035l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018012l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018015l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018032l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\b018035l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059013l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059016l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059033l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\c059036l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\d050000l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\fonts_dir.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\fonts_scale.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019003l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019004l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019023l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019024l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019043l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019044l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019063l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n019064l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021003l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021004l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021023l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n021024l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022003l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022004l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022023l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\n022024l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052003l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052004l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052023l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\p052024l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\s050000l_pfm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_afm.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_pfb.h
# End Source File
# Begin Source File

SOURCE=..\libfonts\z003034l_pfm.h
# End Source File
# End Group
# End Target
# End Project
