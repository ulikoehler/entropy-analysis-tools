#!/usr/bin/env python
#Enumerates 1D values to produce 2D values
from __future__ import with_statement
import sys

with open(sys.argv[1]) as infile:
	with open(sys.argv[2], "w") as outfile:
		i = 1 #Counter
		for line in infile:
			print >> outfile, str(i) + "," + line,
			i += 1
		
	
