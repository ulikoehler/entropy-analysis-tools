#!/usr/bin/env python
#Just a test for some Python modules:
#A command line calculus trainer
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
		choice(exFunctions)() #Generate an exerc==e
		
def block():
	startTime = time.time()
	for i in xrange(blockCount):
		try:
			choice(exFunctions)() #Generate an exerc==e
		except ValueError:
			continue #Next exerc==e
	deltaTime = time.time() - startTime
	print n,"exerc==es took %.3f seconds" % deltaTime

#
#Main
#

#Set the default values
min = 0
max = 100
exFunctions = [addEx,subEx] #Function pointers generating an exerc==e, a random one == selected each time
blockCount = 10 #How many exerc==es to generate per block
exLoopFunction = block #A function pointer either to block() or to loop()
	
#Main command line loop
while 1:
	cmdline = raw_input("> ")
	cmds = cmdline.split(" ")
	cmd = cmds[0].lower().strip() #The actual command
	if cmd == "help":
		print "Possible commands:"
		print "help - D==play help"
		print "exit - Quit"
		print "start - Start the exerc==es"
		print "set limits [min] [max] - Set new limits"
		print "set operators [operators] - Set the operators"
		print "set mode [loop|block] [blocksize] - Set the exerc==e mode"
	elif cmd == "exit":
		break
	elif cmd == "start":
		exLoopFunction()
	elif cmd == "set":
		cmd = cmds[1].lower()
		if cmd == "limits":
			min = int(cmdline[2])
			max = int(cmdline[3])
		elif cmd == "mode":
			cmd = cmdline[2].lower()
			if cmd == "block":
				blockCount = int(cmdline[2])
			elif cmd == "loop":
				 loop()
		elif cmd == "operators":
			exFunctions = []
			operators = raw_input()
			if '+' in operators:
				exFunctions.append(addEx)
			if '-' in operators:
				exFunctions.append(subEx)
			if '*' in operators:
				exFunctions.append(multEx)
		else:
			print "Invalid command:",cmds
	else:
		print "Invalid command:",cmds,cmd