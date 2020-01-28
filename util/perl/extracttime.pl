#!/usr/bin/perl
$debug=0;
#ignore flags provided to awk version of script, use info from log instead.
$fails=0;
while (<>) {
	chomp;
	$line=$_;
	@field=split /[:=]/,$_;
	print "$line\n" if ($debug);
	if ($field[0] =~ /^\>\>/) {
		$field[1]=~ s/^\s*//; #strip leading space
		if ($field[0] =~ /BM/) {
			$desc=$field[1];
			print "\tBM:$desc\n" if ($debug);
		}
		if ($field[0] =~ / ID/) {
			print $field[1] if ($debug);
			($sub,$bmid, $rest)=split /\s/,$field[1];
			print "\tID:$bmid, SUB:$sub\n" if ($debug);
		}
		if ($field[0] =~ /UID/) {
			$ee_uid=$field[1];
			print "\tUID: $ee_uid\n" if ($debug);
		}
		if ($field[0] =~ /Iterations/) {
			$rec_iter=$field[1];
			print "\trit: $rec_iter\n" if ($debug);
		}
		if ($field[0] =~ /data/i) {
			$dataset=$field[1];
			$dataset =~ s/.*\///; #strip any direcory info
			$dataset =~ s/.*\\//; #strip any direcory info
			$dataset =~ s/\s//g; #strip spaces
			print "\tDATA: $dataset\n" if ($debug);
		}
		if ($field[0] =~ /device/i) {
			$dataset.=":$field[1]";
			$dataset.=":$field[2]" if (defined($field[2])); 
			$dataset =~ s/\s//g; #strip spaces
			print "\tDATA: $dataset\n" if ($debug);
		}
	}
	if ($field[0] =~ /^--/) {
		$field[1]=~ s/^\s*//; #strip leading space
		if ($field[0] =~ /Target Timer Rate/) {
			$timer_rate=$field[1];
			print "\trate: $timer_rate\n" if ($debug);
		}
		if ($field[0] =~ /Target Duration/) {
			$duration=$field[1];
			print "\tdura: $duration\n" if ($debug);
		}
		if ($field[0] =~ /Iterations[^\/]/) {
			$actual_iter=$field[1];
			print "\titer: $actual_iter\n" if ($debug);
		}
		if ($field[0] =~ /CRC/) {
			$actual_CRC=$field[1];
			print "\tcrc: $actual_CRC\n" if ($debug);
		}
		if ($field[0] =~ /Iterations\/Sec/) {
			$itps=$field[1];
			print "\titps: $itps\n" if ($debug);
		}
		if ($field[0] =~ /Total Run Time/) {
			$total_time=$field[1];
			print "\ttot: $total_time\n" if ($debug);
		}
		if ($field[0] =~ /Time \/ Iter/) {
			$secs_per_it=$field[1];
			print "\tsit: $secs_per_it\n" if ($debug);
		}
		if ($field[0] =~ /Energy\/Iteration\[F1\]\s+([\d\.]+)/) {
			$sample1=$1;
			$energy1=$field[1];
		}
		if ($field[0] =~ /Energy\/Iteration\[F2\]\s+([\d\.]+)/) {
			$sample2=$1;
			$energy2=$field[1];
		}
		if ($field[0] =~ /PowerAvg\[F1\]/) {
			$power1=$field[1];
		}
		if ($field[0] =~ /PowerAvg\[F2\]/) {
			$power2=$field[1];
		}
		if ($field[0] =~ /EnergyStdDev\[F1\]/) {
			$EnergyStdDev1=$field[1];
		}
		if ($field[0] =~ /EnergyStdDev\[F2\]/) {
			$EnergyStdDev2=$field[1];
		}
		if ($field[0] =~ /PowerRMS\[F1\]/) {
			$PowerRMS1=$field[1];
		}
		if ($field[0] =~ /PowerRMS\[F2\]/) {
			$PowerRMS2=$field[1];
		}
		if ($field[0] =~ /PowerStdDev\[F1\]/) {
			$PowerStdDev1=$field[1];
		}
		if ($field[0] =~ /PowerStdDev\[F2\]/) {
			$PowerStdDev2=$field[1];
		}
	}
	if ($line =~ /(failure|error)/) {
		$fails++;
	}
	if ($line =~ /Actual CRC ([x\d]*), Expected CRC ([x\d]*)/) {
		$req_CRC=$2;
		$actual_CRC=$1;
	}
}

if (!defined($req_CRC)) {
	$req_CRC=$actual_CRC;
}
if (!defined($itps)) {
	$itps = $actual_iter / ($duration / $timer_rate );
}
if (!defined($total_time)) {
	$total_time = ($duration / $timer_rate );
}
if (!defined($secs_per_it)) {
	$secs_per_it = (1.0 / $itps );
}

printf ("%d\t%s\t%-12s\t%-11s\t%s\t%-30s\t%-6s\t%-6s\t%d\t%d\t%d\t%18.9f\t%18.9f\t%18.9f", 
	$ee_uid,$sub, $bmid, $dataset, $fails>0 ? "ERROR" : "", $desc, $req_CRC, $actual_CRC, 
	$actual_iter, $duration, $timer_rate, $itps, $total_time, $secs_per_it);

if (defined($sample1)) {
	printf ("\t%f\t%.3e\t%f\t%f\t%f\t%f", 
	$sample1,$energy1,$EnergyStdDev1,$power1,$PowerStdDev1,$PowerRMS1);
}
if (defined($sample2)) {
	printf ("\t%f\t%.3e\t%f\t%f\t%f\t%f", 
	$sample2,$energy2,$EnergyStdDev2,$power2,$PowerStdDev2,$PowerRMS2);
}
