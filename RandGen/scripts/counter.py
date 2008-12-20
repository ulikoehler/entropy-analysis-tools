#!/usr/bin/env python
from __future__ import with_statement
from optparse import OptionParser

parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-i","--in",dest="input",help="Data input file")
parser.add_option("-o", "--out", dest="output",help="Statistics output file")
parser.add_option("-s","--separator",dest="separator",help="CSV separator")
#Set the defaults
parser.set_defaults(output="counts.txt",separator=",")
#Do the actual parsing
(options,args) = parser.parse_args()

#occurrences dictionary
occ = {}

#read the data
with open(options.input) as fin:
	for line in fin:
		line = line[:-1] #Remove the newline character
		if not line in  occ:
			occ[line] = 1L
			continue
		occ[line] += 1L
	
#write the data
with open(options.output, "w") as fout:
	for k in occ:
		fout.write(k + options.separator + str(occ[k]) + "\n")