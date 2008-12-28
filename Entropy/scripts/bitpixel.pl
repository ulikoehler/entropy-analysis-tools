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

my $surf = Cairo::ImageSurface->create ('rgb24', 32, $count*2);
my $cr = Cairo::Context->create ($surf);

#Fill
$cr->rectangle (0, 0, 32, $count);
$cr->set_source_rgb (1, 1, 1);
$cr->fill;

$cr->set_source_rgb (0, 0, 0);

for($i = 0;$i < length(@data);$i++)
{	
	$d = $data[$i];
	for($j = 0; $j < 32;$j++)
	{
		$cr->new_path();
		$cr->rectangle($j*2,$i*2,1,1) if ($d & (2**$i));
		$cr->stroke();
	}
}

$cr->show_page;
$surf->write_to_png ($png);


