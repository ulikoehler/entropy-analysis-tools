from sys import *

if argc is not 5:
	print "Too less arguments"
	exit(2)

infile = open(argv[1], "r")
outfile = open(argv[2], "w")

lower = (int) argv[3]
upper = (int) argv[4]

for line in infile:
	num = (int) line
	print >> outfile, (num % (upper-lower) + lower)

infile.close()
outfile.close()