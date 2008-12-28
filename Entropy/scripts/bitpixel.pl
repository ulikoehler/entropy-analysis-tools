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

my $surf = Cairo::ImageSurface->create ('argb32', 32, $count);
my $cr = Cairo::Context->create ($surf);

#Fill
$cr->rectangle (0, 0, 32, length(@data));
$cr->set_source_rgba (1, 1, 1, 0.5);
$cr->fill;

for($i = 0;$i < length(@data);$i++)
{
	$cr->restore();
	$cr->translate(0,$i);
	
	$cr->set_source_rgba (0, 0, 0, 0);
	
	$d = $data[$i];
	for($j = 0; $j < 32;$j++)
	{
		$cr->translate(1,0);
		$cr->rel_line_to(1,0) if ($d & 2**$i);
	}
}

$cr->show_page;
$surf->write_to_png ($png);


