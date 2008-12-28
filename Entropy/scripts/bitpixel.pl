#!/usr/bin/perl -w
use Cairo;

my $infilename = shift;
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

my $png = "out.png";

my $imgWidth = 32;
my $imgHeight = $count;

my $surf = Cairo::ImageSurface->create ('rgb24', $imgWidth, $imgHeight);
my $cr = Cairo::Context->create ($surf);

#Fill
$cr->rectangle (0, 0, $imgWidth, $imgHeight);
$cr->set_source_rgb (1, 1, 1);
$cr->fill;

$cr->set_source_rgb (0, 0, 0);

for($i = 0;$i < $count;$i++)
{	
	$d = $data[$i];
	for($j = 0; $j < 32;$j++)
	{
		$cr->new_path();
		$cr->rectangle($j,$i,1,1) if $d & (2**$j);
		$cr->stroke();
	}
}

$cr->show_page;
$surf->write_to_png ($png);