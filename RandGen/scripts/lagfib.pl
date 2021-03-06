#!/usr/bin/perl -w
#This script implements the lagged fibonacci generator
#y_i = (y{i-A}+y{i-B}) mod m
#Syntax is: lagfib.pl [outfile] [n] [m] [A] [B] [seed list]
#Where:
#[outfile] = The output filename. Defaults to "rand.txt"
#[n] = The number of numbers to generate. Defaults to 100000
#[m] = The modulus (as above). Defaults to 1e9
#[A],[B] as above. Default to A=1;B=2
#[seed list] = A comma-separated list of seed values, at least A and at least B elements. Defaults to "1,2"

#Parse the command line
my $ofname = shift || "rand.txt";
my $n = shift || 100000;
my $m = shift || 1000000000;
my $a = shift || 1;
my $b = shift || 2;
my $sraw = shift || "1,2";
my @s = split(/,/,$sraw);

#Open the output file
open(OUTFILE, ">" . $ofname) or die "Can't open output file!";
#Main loop
while($n > 0)
{
	#Generate a new value
	$y = ($s[$a-1] + $s[$b-1]) % $m; #-1: First array index is 0
	print OUTFILE $y . "\n";
	#Add the current value to the beginning of the array and
	#remove the last value to save memory.
	unshift(@s,$y);
	pop(@s);
	#Decrement the loop counter
	$n--;
}
#Close the output file
close OUTFILE;