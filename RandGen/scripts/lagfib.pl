#!/usr/bin/perl -w
#This script implements the lagged fibonacci generator
#y_i = (y{i-A}+y{i-B}) mod m
#Syntax is: lagfib.pl outfile n m A B [seed list]
#Where:
#out = The output filename
#n = The number of numbers to generate
#m = The modulus (as above)
#A,B as above
#[seed list] = A comma-separated list of seed values, at least A and at least B elements

#Parse the command line
my $ofname = shift;
my $n = shift;
my $m = shift;
my $a = shift;
my $b = shift;
my $sraw = shift;
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