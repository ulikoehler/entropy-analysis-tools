#!/usr/bin/env python
#This script performs a precision change on a number file.
#Usage: chprec.py [target precision] [input file] [output file] (All arguments are required)
#The precision of each number in the input file is rounded to [target precision] decimal places.
#The main Entropy tool can perform this operation itself but this may slow down the analysis
#Don't forget to tell Entropy not to do the precision conversion. (See help message for options and syntax)
#This script is not neccessarily faster than the Entropy built-in mechanism
#(but Python's method is guaranteed to be exact and rounds instead of just cutting off).
from __future__ import with_statement
from decimal import *
import sys

if len(sys.argv) != 4:
	print "You have to supply exactly 3 arguments"
	sys.exit(2)

precision = int(sys.argv[1])
infileName = sys.argv[2]
outfileName = sys.argv[3]

prec = Decimal(10) ** -precision #10^-precision

#Main loop
with open(infileName) as infile:
	with open(outfileName,"w") as outfile:
		for line in infile:
			print >> outfile, Decimal(line).quantize(prec, ROUND_HALF_UP)