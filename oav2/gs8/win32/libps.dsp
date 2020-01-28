# Microsoft Developer Studio Project File - Name="libps" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libps - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libps.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libps.mak" CFG="libps - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libps - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libps - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libps - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libps - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "libps___Win32_Debug"
# PROP BASE Intermediate_Dir "libps___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "libps___Win32_Debug"
# PROP Intermediate_Dir "libps___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\.." /I "..\..\..\th\x86\al" /I "..\..\..\th\src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
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

# Name "libps - Win32 Release"
# Name "libps - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\libps\acctest_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\addxchar_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\afmdiff_awk_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\align_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8_rpd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8gc12f_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8hg12f_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8oh06n_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8pa06n_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8pp12f_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bj8ts06n_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a0_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a1_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a2_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a3_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a4_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a5_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a6_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a7_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a8_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b1_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b2_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b3_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b4_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b6_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b7_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b8_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\caption_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cbjc600_ppd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cbjc800_ppd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cdj550_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cdj690_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cdj690ec_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cid2code_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\cidfmap_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\decrypt_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dnj750c_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dnj750m_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\docie_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\dvipdf_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\errpage_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIcidfmap_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIconfig_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIfontmap_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\fixmswrd_pl_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\font2pcl_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_ATB_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_ATM_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_GS_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_OS2_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_OSF_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_SGI_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_Sol_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_Ult_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_VMS_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_agl_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_btokn_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ccfnt_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ce_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cff_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidcm_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciddc_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidfm_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidfn_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidtt_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciecs2_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciecs3_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cmap_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cmdl_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cspace_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_css_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dbt_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devcs_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devn_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devpxl_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_diskf_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_diskn_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dpnxt_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps1_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps2_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dscp_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_epsf_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fapi_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fform_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fntem_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fonts_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_frsd_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_icc_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_il1_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_il2_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_img_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_indxd_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_init_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_kanji_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ksb_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l2img_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_m_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_xpm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lev2_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lgo_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lgx_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ll3_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_m_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_xpm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mex_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mgl_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mro_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_patrn_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pdf_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pdfwr_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pfile_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_rdlin_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_res_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_resmp_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_resst_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_m_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_xpm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_sepr_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_setpd_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_statd_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_std_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_stres_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_sym_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_m_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_xbm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_xpm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_trap_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ttf_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_typ32_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_typ42_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_type1_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wan_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl1_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl2_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl5_e_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsbj_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsbj_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj500_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj500_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gslj_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gslj_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gslp_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gslp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gslp_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsnd_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsnd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsndt_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gsnup_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gssetgs_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gst_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\gstt_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ht_ccsto_ps_init.c
# End Source File
# Begin Source File

SOURCE="..\libps\image-qa_ps_init.c"
# End Source File
# Begin Source File

SOURCE=..\libps\impath_ps_init.c
# End Source File
# Begin Source File

SOURCE="..\libps\Info-macos_plist_init.c"
# End Source File
# Begin Source File

SOURCE=..\libps\jispaper_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\landscap_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\level1_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lines_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lp386_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lp386r2_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lpgs_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lpr2_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\lprsetup_sh_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\markhint_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\markpath_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\necp2x6_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\necp2x_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\packfile_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pcharstr_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_base_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_draw_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_font_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_main_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_ops_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_rbld_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_sec_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pdfwrite_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pftogsf_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ppath_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pphs_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pphs_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\prfont_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\printafm_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\printafm_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ai_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdfwr_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdfxx_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps_cmd_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\pv_sh_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\quit_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras1_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras24_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras32_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras3_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras4_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\ras8m_upp_init.c
# End Source File
# Begin Source File

SOURCE="..\libps\rinkj-2200-setup_init.c"
# End Source File
# Begin Source File

SOURCE=..\libps\rollconv_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\showchar_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\showpage_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640ih_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640ihg_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640p_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640pg_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640pl_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\st640plg_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc1520h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc200_h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc2_h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc2_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc2s_h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc300_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc300bl_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc300bm_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc500p_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc500ph_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc600ih_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc600p_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc600pl_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc640p_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc800ih_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc800p_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc800pl_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc_h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc_l_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stc_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stcany_h_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stcany_upp_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stcinfo_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stcolor_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\stocht_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\traceimg_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\traceop_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\type1enc_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\type1ops_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\uninfo_ps_init.c
# End Source File
# Begin Source File

SOURCE="..\libps\unix-lpr_sh_init.c"
# End Source File
# Begin Source File

SOURCE=..\libps\unprot_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewcmyk_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewgif_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewjpeg_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewmiff_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewpbm_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewpcx_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\viewps2a_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\wftopfa_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\wftopfa_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\winmaps_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\wmakebat_bat_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\wrfont_ps_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\xlatmap_init.c
# End Source File
# Begin Source File

SOURCE=..\libps\zeroline_ps_init.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\libps\acctest_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\addxchar_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\afmdiff_awk.h
# End Source File
# Begin Source File

SOURCE=..\libps\align_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops.h
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\bdftops_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8_rpd.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8gc12f_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8hg12f_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8oh06n_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8pa06n_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8pp12f_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bj8ts06n_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a0_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a1_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a2_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a3_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a4_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a5_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a6_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a7_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610a8_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b1_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b2_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b3_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b4_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b6_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b7_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\bjc610b8_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\caption_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\cbjc600_ppd.h
# End Source File
# Begin Source File

SOURCE=..\libps\cbjc800_ppd.h
# End Source File
# Begin Source File

SOURCE=..\libps\cdj550_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\cdj690_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\cdj690ec_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\cid2code_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\cidfmap.h
# End Source File
# Begin Source File

SOURCE=..\libps\decrypt_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\dnj750c_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\dnj750m_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\docie_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint.h
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\dumphint_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\dvipdf.h
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps.h
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\eps2eps_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\errpage_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIcidfmap.h
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIconfig.h
# End Source File
# Begin Source File

SOURCE=..\libps\FAPIfontmap.h
# End Source File
# Begin Source File

SOURCE=..\libps\fixmswrd_pl.h
# End Source File
# Begin Source File

SOURCE=..\libps\font2c.h
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\font2c_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\font2pcl_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_ATB.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_ATM.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_GS.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_OS2.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_OSF.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_SGI.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_Sol.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_Ult.h
# End Source File
# Begin Source File

SOURCE=..\libps\Fontmap_VMS.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_agl_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_btokn_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ccfnt_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ce_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cff_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidcm_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciddc_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidfm_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidfn_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cidtt_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciecs2_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ciecs3_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cmap_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cmdl_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_cspace_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_css_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dbt_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devcs_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devn_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_devpxl_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_diskf_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_diskn_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dpnxt_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps1_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps2_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dps_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_dscp_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_epsf_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fapi_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fform_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fntem_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_fonts_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_frsd_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_icc_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_il1_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_il2_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_img_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_indxd_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_init_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_kanji_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ksb_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l2img_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_m_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_l_xpm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lev2_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lgo_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_lgx_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ll3_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_m_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_m_xpm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mex_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mgl_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_mro_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_patrn_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pdf_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pdfwr_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_pfile_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_rdlin_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_res_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_resmp_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_resst_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_m_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_s_xpm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_sepr_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_setpd_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_statd_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_std_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_stres_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_sym_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_m_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_xbm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_t_xpm.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_trap_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_ttf_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_typ32_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_typ42_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_type1_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wan_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl1_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl2_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gs_wl5_e_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsbj.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsbj_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj500.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj500_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsdj_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gslj.h
# End Source File
# Begin Source File

SOURCE=..\libps\gslj_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gslp.h
# End Source File
# Begin Source File

SOURCE=..\libps\gslp_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gslp_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsnd.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsnd_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsndt_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gsnup_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\gssetgs_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gst_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\gstt_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ht_ccsto_ps.h
# End Source File
# Begin Source File

SOURCE="..\libps\image-qa_ps.h"
# End Source File
# Begin Source File

SOURCE=..\libps\impath_ps.h
# End Source File
# Begin Source File

SOURCE="..\libps\Info-macos_plist.h"
# End Source File
# Begin Source File

SOURCE=..\libps\jispaper_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\landscap_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\level1_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\lines_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\lp386_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\lp386r2_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\lpgs_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\lpr2_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\lprsetup_sh.h
# End Source File
# Begin Source File

SOURCE=..\libps\markhint_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\markpath_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\necp2x6_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\necp2x_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\packfile_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pcharstr_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2dsc_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf2ps_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_base_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_draw_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_font_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_main_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_ops_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_rbld_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdf_sec_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdfopt_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pdfwrite_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm.h
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\pf2afm_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa.h
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\pfbtopfa_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pftogsf_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ppath_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\pphs.h
# End Source File
# Begin Source File

SOURCE=..\libps\pphs_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\prfont_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\printafm.h
# End Source File
# Begin Source File

SOURCE=..\libps\printafm_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ai_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ascii_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2epsi_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf12_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf13_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf14_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdf_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdfwr.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2pdfxx_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\ps2ps_cmd.h
# End Source File
# Begin Source File

SOURCE=..\libps\pv_sh.h
# End Source File
# Begin Source File

SOURCE=..\libps\quit_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras1_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras24_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras32_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras3_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras4_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\ras8m_upp.h
# End Source File
# Begin Source File

SOURCE="..\libps\rinkj-2200-setup.h"
# End Source File
# Begin Source File

SOURCE=..\libps\rollconv_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\showchar_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\showpage_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640ih_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640ihg_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640p_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640pg_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640pl_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\st640plg_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc1520h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc200_h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc2_h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc2_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc2s_h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc300_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc300bl_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc300bm_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc500p_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc500ph_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc600ih_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc600p_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc600pl_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc640p_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc800ih_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc800p_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc800pl_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc_h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc_l_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stc_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stcany_h_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stcany_upp.h
# End Source File
# Begin Source File

SOURCE=..\libps\stcinfo_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\stcolor_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\stocht_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\sysvlp_sh.h
# End Source File
# Begin Source File

SOURCE=..\libps\traceimg_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\traceop_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\type1enc_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\type1ops_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\uninfo_ps.h
# End Source File
# Begin Source File

SOURCE="..\libps\unix-lpr_sh.h"
# End Source File
# Begin Source File

SOURCE=..\libps\unprot_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewcmyk_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewgif_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewjpeg_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewmiff_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewpbm_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewpcx_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\viewps2a_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\wftopfa.h
# End Source File
# Begin Source File

SOURCE=..\libps\wftopfa_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\winmaps_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\wmakebat_bat.h
# End Source File
# Begin Source File

SOURCE=..\libps\wrfont_ps.h
# End Source File
# Begin Source File

SOURCE=..\libps\xlatmap.h
# End Source File
# Begin Source File

SOURCE=..\libps\zeroline_ps.h
# End Source File
# End Group
# End Target
# End Project
