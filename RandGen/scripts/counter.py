#!/usr/bin/env python
from __future__ import with_statement
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-o", "--out", dest="output",default="out.txt", help="Statistics output file")
parser.add_option("-i","--in",dest="input",default="test.txt", help="Data input file")
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
with open(options.output) as fin:
	for k,n in occ:
		print >> fout, k , n