#!/usr/bin/env python
#pstricks-prep.py
#A script to prepare 1D/2D-CSV data files for use with LaTeX pstricks plotting
#Usage: chprec.py [target precision] [input file] [output file] (All arguments are required)
#For 2D-CSV files:
#	The script converts the syntax from x,y to [x y]
#For
from __future__ import with_statement
from decimal import *
from optparse import OptionParser
from math import *
import sys

parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-i","--in",dest="input",help="Data input file")
parser.add_option("-o", "--out", dest="output",help="Output file")
parser.add_option("-s","--separator",type="int",dest="separator",help="Separator in the input file")

parser.add_option("--xdelta",dest="xdelta",type="float",help="For 1D-input: x increment for each line")
parser.add_option("--xstart",dest="x",type="float",help="For 1D-input: x start value")
parser.add_option("-l","--long",action="store_true",dest="long",help="Use long as key type (instead of string)")
parser.add_option("-f","--float",action="store_true",dest="float",help="Use string as key type (instead of string)")
parser.add_option("-d","--decimal",action="store_true",dest="decimal",help="Use Decimal as key type (instead of string)")
#Set the defaults
parser.set_defaults(output="psdata.txt",separator=",",xdelta=1.0,xstart=0.0)
#Do the actual parsing
(options,args) = parser.parse_args()

#Main loop
with open(options.input) as infile:
	with open(options.output,"w") as outfile:
		for line in infile:
			print >> outfile, fquantize(fconv(line))