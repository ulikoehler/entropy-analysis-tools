#!/usr/bin/env python
#Just a test for some Python modules:
#A command line oriented maths trainer
from sys import *
from random import *
import time

#Something like global counters
correct = 0
false = 0

def loopStatistics():
	print "Correct:",correct
	print "False:",false
	
def addEx():
	op1 = randint(min,max)
	op2 = randint(min,max)
	correctSolution = op1 + op2
	userSolution = raw_input(str(op1) + " + " + str(op2) + " = ")
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	if userSolution == correctSolution:
		print " Correct!"
	else:
		print " False:",correctSolution
		
		
def subEx():
	op1 = randint(min,max)
	op2 = randint(min,max)
	correctSolution = op1 - op2
	userSolution = raw_input(str(op1) + " - " + str(op2) + " = ")
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	if userSolution == correctSolution:
		print " Correct!"
	else:
		print " False:",correctSolution

def multEx():
	op1 = randint(min,max)
	op2 = randint(min,max)
	correctSolution = op1 * op2
	userSolution = raw_input(str(op1) + " * " + str(op2) + " = ")
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	if userSolution == correctSolution:
		print "Correct!"
	else:
		print "False:",correctSolution

def loop():
	while 1:
		choice(exFunctions)() #Generate an exercise
		
def block(n):
	startTime = time.time()
	for i in xrange(n):
		choice(exFunctions)() #Generate an exercise
	deltaTime = time.time() - startTime
	print n,"exercises took",deltaTime,"seconds"

#
#Main
#
#Ask for the least number to use
min = int(raw_input("Min: "))
max = int(raw_input("Max: "))

#Tuple containing function pointers
#to all exercise-producing functions
exFunctions = (addEx,subEx,multEx)

mode = raw_input("Mode: ")

if mode == "loop":
	loop()
elif mode == "block":
	while 1:
		blockCount = int(raw_input("Exercises: "))
		block(blockCount)