#!/usr/bin/env python
#See README file in RandGen folder for description
#or start with "-h" parameter for simple usage
from __future__ import with_statement
from random import *
from decimal import *
import sys
import getopt

if len(sys.argv) < 2: #Output file and count needed
	print "You have to supply at least 2 arguments"
	usage()
	sys.exit(1)

outfileName = sys.argv[1]
count = int(sys.argv[2])

#Parse the command line options
try:
	opts,args = getopt.gnu_getopt(sys.argv[1:], "hg:d:p:q:", ["help","generator=","distribution=","param1=","param2="])
except getop.GetoptError, err:
	print str(err)
	usage()
	sys.exit(2)
	
#Ensure object existence
generatorName = "mt" #Default MT19937
distribution = "01" #Default [0;1]
param1 = "1"
param2 = "1"

for o, a in opts:
	if o in ("-h", "--help"):
		usage()
		sys.exit(2)
	elif o in ("-g", "--generator"):
		generatorName = a
	elif o in ("-d", "--distribution"):
		distribution = a
	elif o in ("-p", "--param1"):
		param1 = a[1:] #Cut off '='
	elif o in("-q", "--param2"):
		param2 = a[1:] #Cut off '='

#Convert the parameter options to a numeric literal of the right type
if distribution == "01":
	param1 = int(param1)
	param2 = int(param2)
else:
	param1 = float(param1)
	param2 = float(param2)
	
#
#Set the right random generator object and function pointer
#
if generatorName == "mt": #Default
	generator = Random()
elif generatorName == "sys":
	try:
		generator = SystemRandom()
	except NotImplementedError, err:
		print "System random number generator is not available on your operating system:"
		print str(err)
		print "Using default random number generator."
elif generatorName == "wh":
	generator = WichmannHill()

#Generator function pointer
#if distribution == "01": #Default
fgen = lambda x,y: random() #fgen must be a 2-parameter function
if distribution == "uniform":
	fgen = generator.uniform
elif distribution == "beta":
	fgen = generator.betavariate
elif distribution == "exponential":
	fgen = generator.expovariate
elif distribution == "gamma":
	fgen = generator.gammavariate
elif distribution == "gauss":
	fgen = generator.gauss
elif distribution == "lognormal":
	fgen = generator.lognormvariate
elif distribution == "normal":
	fgen = generator.normalvariate
elif distribution == "vonmises":
	fgen = generator.vonmisesvariate
elif distribution == "pareto":
	fgen = lambda x,y: generator.paretovariate(x) #Only 1 parameter needed
elif distribution == "weibullvariate":
	fgen = generator.weibullvariate
	
#Main loop
with open(outfileName, "w") as outfile:
	for i in xrange(count):
		print >> outfile, fgen(param1,param2)