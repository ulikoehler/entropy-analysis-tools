#!/usr/bin/env python
from __future__ import with_statement
from random import *
from sys import *

outfileName = argv[1]
count = (long) argv[2]

#Parse the options
try:
	opts,args = getopt.gnu_getopt(sys.argv[1:], "hd:p:q:l:u:", ["help","distribution=","param1=","param2=","lower=","upper="])
except getop.GetoptError, err:
	print str(err)
	usage()
	sys.exit(2)
	
for o, a in opts:
	if o in ("-h", "--help")
		usage()
		sys.exit(2)
	elif o in ("-d", "--distribution")
		distribution = a
	elif o in ("-p", "--param1")
		param1 = (double) a
	elif o in("-q", "--param2")
		param2 = (double) a
	elif o in("-l", "--lower")
		lower = (int) a
	elif o in("-q", "--upper")
		upper = (int) a
		
#
#Set the right random generator function pointer
#
fgen = lambda: random() #Default
elif distribution == "uniform":
	fgen = lambda: uniform(lower,upper)
elif distribution == "beta":
	fgen = lambda: betavariate(param1,param2)
elif distribution == "exponential":
	fgen = lambda: expovariate(param1,param2)
elif distribution == "gamma":
	fgen = lambda: gammavariate(param1, param2)
elif distribution == "gauss":
	fgen = lambda: gauss(param1,param2)
elif distribution == "lognormal":
	fgen = lambda: lognormvariate(param1,param2)
elif distribution == "normal":
	fgen = lambda: normalvariate(param1,param2)
elif distribution == "vonmises":
	fgen = lambda: vonmisesvariate(param1,param2)
elif distribution == "pareto":
	fgen = lambda: paretovariate(param1,param2)
elif distribution == "weibullvariate":
	fgen = lambda: weibullvariate(param1,param2)
	
#Main loop
with open(outfileName, "w") as outfile:
	for i in xrange(count)
		print >> outfile, fgen()