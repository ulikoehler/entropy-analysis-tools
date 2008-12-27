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
#
#TODO:
#The command line syntax as above is not yet implemented so you are asked for
#the values via stdin

#Ask for the values
print "Output file:";
	my $ofname = <>;
	chomp $ofname;
print "Numbers to generate:";
	my $n = <>;
	chomp $n;
print "Modulus:";
	my $m = <>;
	chomp $m;
print "A:";
	my $a = <>;
	chomp $a;
print "B:";
	my $b = <>;
	chomp $b;
print "Seeds (comma separated):";
	$sraw = <>;
	chomp $sraw;
	my @s = split(/,/,$sraw);

open(OUTFILE, ">" . $ofname) or die "Can't open output file!";
while($n > 0)
{
	$y = ($s[$a-1] + $s[$b-1]) % $m; #-1: First array index is 0
	print OUTFILE $y . "\n";
	#Add the current value to the beginning of the array and
	#remove the last value to save memory.
	unshift(@s,$y);
	pop(@s);
	
	$n--; #Decrement the loop counter
}
close OUTFILE;