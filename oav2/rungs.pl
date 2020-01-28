#!/usr/bin/perl
use Getopt::Long; 
use File::Copy;

#$gsname = "gcc/bin_lite/gs8_lite.exe";
$gsname = "gcc/bin_lite/gs8_lite.exe";
$gsparam = "-do_uuencode -dNOPAUSE -dBATCH -q ";
$outpath = "gcc/gs-output";
$logpath = "gcc/results_lite";
$logext= "run.log";
$dryrun=0;
$fontcat=0;
$train=0;
$split_pages=0;
$not_using_thio=0;

GetOptions (
	'gsparam=s' => \$gsparam,
	'gsname=s' => \$gsname,
	'outpath=s' => \$outpath,
	'logext=s' => \$logext,
	'logpath=s' => \$logpath,
	'train' => \$train,
	'split' => \$split_pages,
	'fontcat' => \$fontcat,
	'dryrun' => \$dryrun
);

$split_cmd = $split_pages ? "page%03d." : "";
#all devices
@gs_devices = qw(deskjet laserjet tiff bmp cmyk1b cmyk2b cmyk4b cmyk8b);
#all data files
@gs_testdata = qw(fonts fern spreadsheet ppt pptpdf mandel text banner photo);
if ($train) {
	@gs_testdata = qw(colormap);
	$fontcat=1;
}
#all installed fonts
@gs_fonts = qw(CenturySchL-Bold CenturySchL-BoldItal CenturySchL-Ital CenturySchL-Roma Dingbats NimbusMonL-Bold NimbusMonL-BoldObli NimbusMonL-Regu NimbusMonL-ReguObli NimbusRomNo9L-Medi NimbusRomNo9L-MediItal NimbusRomNo9L-Regu NimbusRomNo9L-ReguItal NimbusSanL-Bold NimbusSanL-BoldCond NimbusSanL-BoldCondItal NimbusSanL-BoldItal NimbusSanL-Regu NimbusSanL-ReguCond NimbusSanL-ReguCondItal NimbusSanL-ReguItal StandardSymL URWBookmanL-DemiBold URWBookmanL-DemiBoldItal URWBookmanL-Ligh URWBookmanL-LighItal URWChanceryL-MediItal URWGothicL-Book URWGothicL-BookObli URWGothicL-Demi URWGothicL-DemiObli URWPalladioL-Bold URWPalladioL-BoldItal URWPalladioL-Ital URWPalladioL-Roma);
#parameters for each device/datafile
#devices to use with each datafile
$params{colormap} = "-d.Nx=2 -d.Ny=2 gsnup.ps 3dcolor.ps:4";
$device{colormap} = "deskjet laserjet tiff bmp cmyk1b cmyk2b cmyk4b cmyk8b";

$params{fonts} = "Rotate-fontlist2.ps";
$device{fonts} = "tiff";

$params{fern} = "fractal-fern.ps";
$device{fern} = "tiff";

$params{spreadsheet} = "-d.Nx=2 -d.Ny=2 gsnup.ps spreadsheet.ps:4";
$device{spreadsheet} = "bmp cmyk1b cmyk2b cmyk4b cmyk8b";

$params{ppt} = "presentation.ps";
$device{ppt} = "tiff cmyk1b cmyk2b cmyk4b cmyk8b";

$params{pptpdf} = "presentation4.pdf";
$device{pptpdf} = "bmp cmyk1b cmyk2b cmyk4b cmyk8b";

$params{shade} = "shadings.pdf";
$device{shade} = "bmp cmyk1b cmyk2b cmyk4b";

$params{mandel} = "-r300 mandel.ps";
$device{mandel} = "bmp";

$params{text} = "-d.Nx=4 -d.Ny=4 gsnup.ps ebreadme.ps:8";
$device{text} = "tiff cmyk1b cmyk2b cmyk4b cmyk8b";

$params{banner} = "-d.Nx=4 -d.Ny=4 gsnup.ps banner.ps:16";
$device{banner} = "bmp cmyk1b cmyk2b";

$params{photo} = "photo.ps:4";
$device{photo} = "cmyk1b cmyk2b cmyk4b bmp";

$params{prfont} = "prfont.ps";
$device{prfont} = "cmyk1b";

#device parameters
$params{deskjet}="-sDEVICE=deskjet";
$params{laserjet}="-sDEVICE=laserjet";
$params{tiff}="-sDEVICE=tiffg4";
$params{bmp}="-sDEVICE=bmp256";
$params{cmyk1b}="-sDEVICE=bitcmyk -dGrayValues=2";
$params{cmyk2b}="-sDEVICE=bitcmyk -dGrayValues=4";
$params{cmyk4b}="-sDEVICE=bitcmyk -dGrayValues=16";
$params{cmyk8b}="-sDEVICE=bitcmyk -dGrayValues=256";


#construct a command line for each datafile + device combo
$uid=196;
$fails=0;
foreach $test (@gs_testdata) {
	$tp=$params{$test};
	print "$test\n\t$tp\n";
	@devs=split / /,$device{$test};
	foreach $dev (@devs) {
		$dp=$params{$dev};
		$flog="gs8.$test.$dev$logext";
		$fname="gs8.$test.$split_cmd$dev";
		$outname="-sOutputFile=$outpath/$fname";
		$cmd="$gsname -uid=$uid $gsparam $dp $outname $tp > $logpath/$flog";
		$uid++;
		print "\t$cmd\n";
		if (!$dryrun) {
			system($cmd) ;
			$testname=$fname;
			$testname=~ s/page\%d/page1/;
			if ($not_using_thio && ! -f "$outpath/$testname") {
				print "ERROR: $fname not generated\n";
				$fails++;
			}
			$gprof="$logpath/gs8.gprof";
			$testname=~ s/page1\.//;
			if (-f $gprof) {
				print "\tbackup gprof data\n";
				copy($gprof,"$logpath/$testname.gprof");
			}
		}
	}
}
#also optionally do font catalogue of all fonts
if ($fontcat) {
	print "\nDoing font catalogue\n";
	#first prepare command line that includes all fonts
	foreach $font (@gs_fonts) {
		$fontcmd .= " -c \"/$font DoFont\"";
	}
	#now set all the rest of the parameters
	$test="fontcat";
	$tp=$params{prfont}.$fontcmd;
	$dev=$device{prfont};
	$dp=$params{$dev};
	$flog="gs8.$test.$dev$logext";
	$fname="gs8.$test.$split_cmd$dev";
	$outname="-sOutputFile=$outpath/$fname";
	$cmd="$gsname -uid=$uid $gsparam $dp $outname $tp > $logpath/$flog";
	$uid++;
	print "\t$cmd\n";
	if (!$dryrun) {
		system($cmd) ;
		$testname=$fname;
		$testname=~ s/page\%d/page1/;
		if ($not_using_thio && ! -f "$outpath/$testname") {
			print "ERROR: $fname not generated\n";
			$fails++;
		}
		$gprof="$logpath/gs8.gprof";
		$testname=~ s/page1\.//;
		if (-f $gprof) {
			print "\tbackup gprof data\n";
			copy($gprof,"$logpath/$testname.gprof");
		}
	}
}

print "Done with $fails fails\n";

exit 0;

