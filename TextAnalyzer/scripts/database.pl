#!/usr/bin/perl -w
$action = shift;
$db = shift;
$file = shift;
$n = shift;

open(DB,"<".$db) or $nodb = 1;
if(!$nodb)
{
	while($line = <DB>)
	{
		@dataset = split(/,/,$line);
		$data{$dataset[0]} = $dataset[1]
	}
}
close DB;

if($action == "update")
{
	open(INFILE,"<".$file) or die "Cannot open input file";
	#First read n-1 chars into the buffer array
	for($i = 1;$i<$n;$i++)
	{
		unshift(@buffer,getc(INFILE))
	}
	#Then do the actual work char-by-char
	while(($char = getc(INFILE)) != eof)
	{
		
	}
}