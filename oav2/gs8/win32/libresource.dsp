# Microsoft Developer Studio Project File - Name="libresource" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libresource - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libresource.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libresource.mak" CFG="libresource - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libresource - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libresource - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libresource - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "libresource___Win32_Release"
# PROP BASE Intermediate_Dir "libresource___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "libresource_Release"
# PROP Intermediate_Dir "libresource_Release"
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

!ELSEIF  "$(CFG)" == "libresource - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libresource___Win32_Debug"
# PROP BASE Intermediate_Dir "libresource___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libresource_Debug"
# PROP Intermediate_Dir "libresource_Debug"
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

# Name "libresource - Win32 Release"
# Name "libresource - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE="..\libresource\78-EUC-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-EUC-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78ms-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\78ms-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\83pv-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\90ms-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\90ms-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\90pv-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\90pv-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-0_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-1_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-2_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultCMYK_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultGray_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultRGB_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-UCS2_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETenms-B5-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETenms-B5-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETHK-B5-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETHK-B5-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\EUC-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\EUC-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\GBK-EUC-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\GBK-EUC-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\H_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource\Hankaku_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource\Hiragana_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\Identity-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\Identity-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\Katakana_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\KSC-Johab-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSC-Johab-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSCms-UHC-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSCms-UHC-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\Latin1_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\NWP-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\NWP-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\RKSJ-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\RKSJ-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\Roman_init.c
# End Source File
# Begin Source File

SOURCE=..\libresource\StandardEncoding_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\UniCNS-UCS2-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniCNS-UCS2-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\Unicode_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\UniGB-UCS2-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniGB-UCS2-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniHojo-UCS2-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniJIS-UCS2-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniJIS-UCS2-V_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniKS-UCS2-H_init.c"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniKS-UCS2-V_init.c"
# End Source File
# Begin Source File

SOURCE=..\libresource\V_init.c
# End Source File
# Begin Source File

SOURCE="..\libresource\WP-Symbol_init.c"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\libresource\78-EUC-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-EUC-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78ms-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\78ms-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\83pv-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\90ms-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\90ms-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\90pv-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\90pv-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Add-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-0.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-1.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Adobe-Japan1-2.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultCMYK.h
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultGray.h
# End Source File
# Begin Source File

SOURCE=..\libresource\DefaultRGB.h
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-UCS2.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETen-B5-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETenms-B5-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETenms-B5-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETHK-B5-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\ETHK-B5-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\EUC-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\EUC-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Ext-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\GBK-EUC-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\GBK-EUC-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\H.h
# End Source File
# Begin Source File

SOURCE=..\libresource\Hankaku.h
# End Source File
# Begin Source File

SOURCE=..\libresource\Hiragana.h
# End Source File
# Begin Source File

SOURCE="..\libresource\Identity-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\Identity-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\Katakana.h
# End Source File
# Begin Source File

SOURCE="..\libresource\KSC-Johab-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSC-Johab-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSCms-UHC-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\KSCms-UHC-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\Latin1.h
# End Source File
# Begin Source File

SOURCE="..\libresource\NWP-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\NWP-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\RKSJ-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\RKSJ-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\Roman.h
# End Source File
# Begin Source File

SOURCE=..\libresource\StandardEncoding.h
# End Source File
# Begin Source File

SOURCE="..\libresource\UniCNS-UCS2-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniCNS-UCS2-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\Unicode.h
# End Source File
# Begin Source File

SOURCE="..\libresource\UniGB-UCS2-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniGB-UCS2-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniHojo-UCS2-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniJIS-UCS2-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniJIS-UCS2-V.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniKS-UCS2-H.h"
# End Source File
# Begin Source File

SOURCE="..\libresource\UniKS-UCS2-V.h"
# End Source File
# Begin Source File

SOURCE=..\libresource\V.h
# End Source File
# Begin Source File

SOURCE="..\libresource\WP-Symbol.h"
# End Source File
# End Group
# End Target
# End Project
