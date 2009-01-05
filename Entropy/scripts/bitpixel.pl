#!/usr/bin/perl -w
#bitpixel.pl
#This script is intended to display binary patterns in files having one integer per line.
#If a bit is set, the appropriate pixel is set black, otherwise white.
#The syntax is:
#bitpixel.pl [infilename] [outfilename] [width]
#Where:
#infilename = The file to read the numbers from, one integer per line-
#outfilename = The PNG file to write the resulting image to. Defaults to out.png.
#width = The width in bits to analyze. Defaults to 32.
#libcairo-perl with PNG backend support is needed
use Cairo;

#Check library requirements
die "Cairo PNG backend is not supported!\n" unless (Cairo::HAS_PNG_FUNCTIONS);

my $infilename = shift;
my $outfilename = shift || "out.png";
my $imgWidth = shift || 32;

#Read the data from the input file
open(INFILE, "<" . $infilename);
my $count = 0;
while($line = <INFILE>)
{
	chomp $line;
	push(@data,$line);
	$count++;
}
close INFILE;

#imgWidth already declared
my $imgHeight = $count;

my $surf = Cairo::ImageSurface->create ('rgb24', $imgWidth, $imgHeight);
my $cr = Cairo::Context->create ($surf);

#Fill
$cr->rectangle (0, 0, $imgWidth, $imgHeight);
$cr->set_source_rgb (1, 1, 1);
$cr->fill;

$cr->set_source_rgb (0, 0, 0);

#Main loop: processes one number per iteration
for($i = 0;$i < $count;$i++)
{
	$d = $data[$i];
	#Each iteration processes one bit in => draws one line
	for($j = 0; $j < $imgWidth;$j++)
	{
		$cr->new_path();
		$cr->rectangle($j,$i,1,1) if $d & (2**$j);
		$cr->stroke();
	}
}

$cr->show_page;
$surf->write_to_png ($outfilename);