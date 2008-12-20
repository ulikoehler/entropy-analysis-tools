#!/usr/bin/env python
from __future__ import with_statement
from sys import *
from optparse import OptionParser
from math import *
from decimal import Decimal

parser = OptionParser()
parser.enable_interspersed_args()
#Add options
parser.add_option("-i","--in",dest="input",help="Data input file")
parser.add_option("-o", "--out", dest="output",help="Output file")
parser.add_option("-l", "--lower", dest="lower",type="float",help="Statistics output file")
parser.add_option("-u", "--upper", dest="upper",type="float",help="Upper limit")
#Set defaults
parser.set_defaults(output="randlim.txt", lower=0.0,upper=1.0)
#Parse
(options,args) = parser.parse_args()

with open(options.input) as infile:
	with open(options.output, "w") as outfile:
		for line in infile:
			num = Decimal(line)
			print >> outfile, str(fmod(num,(options.upper-options.lower)) + options.lower)