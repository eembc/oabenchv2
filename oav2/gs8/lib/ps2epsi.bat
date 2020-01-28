@echo off 
@rem $Id: ps2epsi.bat 6300 2005-12-28 19:56:24Z giles $

if %1/==/ goto usage
if %2/==/ goto usage

call gssetgs.bat
set infile=%1
set outfile=%2

rem Ghostscript uses %outfile% to define the output file
%GSC% -q -dNOPAUSE -dSAFER -dDELAYSAFER -sDEVICE=bit -sOutputFile=NUL ps2epsi.ps < %infile%

rem We bracket the actual file with a few commands to help encapsulation
echo %%%%Page: 1 1 >> %outfile%
echo %%%%BeginDocument: %outfile% >> %outfile%
echo /InitDictCount countdictstack def gsave save mark newpath >> %outfile%

rem Append the original onto the preview header
copy %outfile% + %infile%

echo %%%%EndDocument >> %outfile%
echo countdictstack InitDictCount sub { end } repeat >> %outfile%
echo cleartomark restore grestore >> %outfile%

goto end

:usage
echo "Usage: ps2epsi <infile.ps> <outfile.epi>"

:end
