# Microsoft Developer Studio Project File - Name="libpgm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libpgm - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libpgm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libpgm.mak" CFG="libpgm - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libpgm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libpgm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libpgm - Win32 Release"

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

!ELSEIF  "$(CFG)" == "libpgm - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /Zm800 /c
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

# Name "libpgm - Win32 Release"
# Name "libpgm - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\DavidAndDogs_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\dragon_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\DragonFly_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\EEMBCGroupShotMiami_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\Galileo_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\Goose_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\graydient_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\libpgm_init.c
# End Source File
# Begin Source File

SOURCE=..\libpgm_single.c
# End Source File
# Begin Source File

SOURCE=..\Mandrake_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\MarsFormerLakes_pgm_init.c
# End Source File
# Begin Source File

SOURCE=..\Rose256_pgm_init.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\DavidAndDogs_pgm.h
# End Source File
# Begin Source File

SOURCE=..\dragon_pgm.h
# End Source File
# Begin Source File

SOURCE=..\DragonFly_pgm.h
# End Source File
# Begin Source File

SOURCE=..\EEMBCGroupShotMiami_pgm.h
# End Source File
# Begin Source File

SOURCE=..\Galileo_pgm.h
# End Source File
# Begin Source File

SOURCE=..\Goose_pgm.h
# End Source File
# Begin Source File

SOURCE=..\graydient_pgm.h
# End Source File
# Begin Source File

SOURCE=..\Mandrake_pgm.h
# End Source File
# Begin Source File

SOURCE=..\MarsFormerLakes_pgm.h
# End Source File
# Begin Source File

SOURCE=..\Rose256_pgm.h
# End Source File
# End Group
# End Target
# End Project
