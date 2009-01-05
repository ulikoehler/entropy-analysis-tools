#!/usr/bin/env python
#This is a runtime-configurable implementation of the
#linear congruentialpseudo-random number generator,
#using the following formula:
#y = (a*z+b) mod m
#where:
#z = the last generate result (or the seed at startup)
#a,b,m = parameters (defaults generated randomly)
#
#Numbers created by the LC algorithm are NOT indended
#to be used for cryptographical purposes.
#Note that the LC is a lot slower than almost all other
#algorithms, especially the MersenneTwister.
from __future__ import with_statement
from random import *
from decimal import *
from math import *
import sys
from optparse import OptionParser

#Generate random defaults for the option parser
randm = randint()
randa = randint(randm)
randb = randint(randm)
randseed

#Initlialize the option parser
parser = OptionParser()
parser.enable_interspersed_args()
parser.add_option("-c",
				"--count",
				type="int",
				action="store",
				dest="count",
				help="How many random numbers to generate")
parser.add_option("-o",
				"--out",
				dest="outfileName",
				help="Output file")
parser.add_option("-a",
				"--parama",
				type="long",
				dest="a",
				help="Parameter a (multiplier)")
parser.add_option("-b",
				"--paramb",
				type="long",
				dest="b",
				help="Parameter b (increment)")
parser.add_option("-m",
				"--paramm",
				type="long",
				dest="m",
				help="Parameter m (modulus)")
parser.add_option("-s",
				"--seed",
				type="long",
				dest="seed",
				help="Seed (= last generator result)")

#Set defaults
parser.set_defaults(outfileName="rand.txt",
				 count=10000,
				 a=randa,
				 b=randb,
				 m=randm,
				 seed=randseed
				 )

#Parse			
(options,args) = parser.parse_args()

#Global paramter aliases
a = options.a
b = options.b
m = options.m
lastres = options.seed	

with open(options.outfileName,"w") as outfile:
	for i in xrange(options.count):
		lastres = (a * lastres + b) % m
		print >> outfile,lastres