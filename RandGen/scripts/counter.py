#!/usr/bin/env python
from __future__ import with_statement
from optparse import OptionParser
from decimal import Decimal

parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-i","--in",dest="input",help="Data input file")
parser.add_option("-o", "--out", dest="output",help="Statistics output file")
parser.add_option("-s","--separator",dest="separator",help="CSV separator")

parser.add_option("--int",action="store_true",dest="int",help="Use int as key type (instead of string)")
parser.add_option("--long",action="store_true",dest="long",help="Use long as key type (instead of string)")
parser.add_option("--float",action="store_true",dest="float",help="Use string as key type (instead of string)")
parser.add_option("--Decimal",action="store_true",dest="decimal",help="Use  as key type (instead of string)")
#Set the defaults
parser.set_defaults(output="counts.txt",separator=",")
#Do the actual parsing
(options,args) = parser.parse_args()

#Set the right converter lambda function
if options.int:
	fconv = lambda x: int(x)
elif options.long:
	fconv = lambda x: long(x)
elif options.float:
	fconv = lambda x: float(x)
elif options.decimal:
	fconv = lambda x: Decimal(x)
else: #string
	fconv = lambda x: x

#occurrences dictionary
occ = {}

#read the data
with open(options.input) as fin:
	for line in fin:
		line = fconv(line[:-1]) #Remove the newline character
		if not line in  occ:
			occ[line] = 1L
			continue
		occ[line] += 1L
	
#Sort the data
occ.keys().sort()
#Write the data into the output file
with open(options.output, "w") as fout:
	for k in occ:
		fout.write(str(k) + options.separator + str(occ[k]) + "\n")