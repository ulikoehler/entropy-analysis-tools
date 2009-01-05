#!/usr/bin/env python
#This script performs a precision change on a number file.
#Usage: chprec.py [target precision] [input file] [output file] (All arguments are required)
#The precision of each number in the input file is rounded to [target precision] decimal places.
#The main Entropy tool can perform this operation itself but this may slow down the analysis
#Don't forget to tell Entropy not to do the precision conversion. (See help message for options and syntax)
#This script is not neccessarily faster than the Entropy built-in mechanism (using Boost::format)
#(but Python's method is guaranteed to be exact when Decimal mode is selected and rounds instead of just cutting off).
from __future__ import with_statement
from decimal import *
from optparse import OptionParser
from math import *
import sys

parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-i","--in",dest="input",help="Data input file")
parser.add_option("-o", "--out", dest="output",help="Statistics output file")
parser.add_option("-p","--precision",type="int",dest="precision",help="CSV separator")

parser.add_option("--int",action="store_true",dest="int",help="Use int as key type (instead of string)")
parser.add_option("-l","--long",action="store_true",dest="long",help="Use long as key type (instead of string)")
parser.add_option("-f","--float",action="store_true",dest="float",help="Use string as key type (instead of string)")
parser.add_option("-d","--decimal",action="store_true",dest="decimal",help="Use Decimal as key type (instead of string)")
#Set the defaults
parser.set_defaults(output="counts.txt",separator=",")
#Do the actual parsing
(options,args) = parser.parse_args()

prec = float(10 ** - options.precision) #10^-precision

#Set the right converter lambda function
if options.int:
	fconv = lambda x: int(x)
elif options.long:
	fconv = lambda x: long(x)
elif options.decimal:
	fconv = lambda x: Decimal(x)
else: #Float or anything else (treated as float)
	fconv = lambda x: float(x)

#Set the right quantizer lambda function
if options.decimal: #Decimal
	fquantize = lambda x: Decimal(x).quantize(prec, ROUND_HALF_UP)
else: #All other
	fquantize = lambda x: x-fmod(x,prec)

#Main loop
with open(options.input) as infile:
	with open(options.output,"w") as outfile:
		for line in infile:
			print >> outfile, fquantize(fconv(line))