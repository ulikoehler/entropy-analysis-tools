#!/usr/bin/env python
#See README file in RandGen folder for description
#or start with "-h" parameter for simple usage
from __future__ import with_statement
from random import *
from decimal import *
import sys
from optparse import OptionParser

#Parse the command line options
parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-c",
				"--count",
				type="int",
				action="store",
				dest="count")
parser.add_option("-o",
				"--out",
				dest="outputFilename",
				help="Statistics output file")
parser.add_option("-g",
				"--generator",
				dest="generatorName",
				type="choice",
				choices=["mt","sys","wh"],
				action="store")
parser.add_option("-d",
				"--distribution",
				type="choice",
				choices=["01","uniform","beta","exponential","gamma","gauss","lognormal","normal","vonmises","pareto","weibull"],
				dest="distribution",
				action="store")
parser.add_option("-p",
				"--param1",
				type="string",
				dest="param1",
				action="store")
parser.add_option("-q",
				"--param2",
				type="string",
				dest="param2",
				action="store")
#Set defaults
parser.set_defaults(generatorName="mt",
				 outputFilename="rand.txt",
				 distribution="01",
				 param1="1",
				 param2="5",
				 count=10000
				 )

#Parse			
(options,args) = parser.parse_args()

#Declare global aliases to the option variables
distribution = options.distribution
generatorName = options.generatorName
outputFilename = options.outputFilename
count = options.count

#Convert the parameter options to a numeric literal of the appropriate type
if distribution == "01":
	param1 = int(options.param1)
	param2 = int(options.param2)
else:
	param1 = float(options.param2)
	param2 = float(options.param2)
	
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
		generator = Random()
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
	 fgen = generator.expovariate #expovariate takes only one parameter
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
elif distribution == "weibull":
	fgen = generator.weibullvariate
	
#Main loop
with open(outputFilename, "w") as outfile:
	for i in xrange(count):
		print >> outfile, fgen(param1,param2)