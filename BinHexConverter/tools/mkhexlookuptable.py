#!/usr/bin/env python
#Creates a lookup table for hex values
#TODO: Make more flexible for arbitrary table numbers
import sys
sys.stdout.write("string toHex[] = {")
for x in xrange(0,255):
	sys.stdout.write("\""+hex(x)[2:]+"\"")
	if x < 255-1:
		sys.stdout.write(",")
print "};"
	