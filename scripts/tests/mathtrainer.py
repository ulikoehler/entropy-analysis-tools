#!/usr/bin/env python
#Just a test for some Python modules:
#A command line calculus trainer
from __future__ import with_statement
from sys import *
from random import *
import time

def statistics():
	print "Overall solved:",correct+false
	print "Correct:",correct
	print "False:",false
	
#Generates an exercise with + as the operator.
#Returns 0 if solved correctly, 1 else
def addEx():
	#Allow write-access to the global statistics counters
	global correct,false
	#Generate two random numbers
	op1 = randint(min,max)
	op2 = randint(min,max)
	#Calculate the correct solution
	correctSolution = op1 + op2
	#Read the user's solution (not yet converted to a number)
	userSolution = raw_input(str(op1) + " + " + str(op2) + " = ")
	#Check if the user requested to show statistics
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	#Check if the user's solution is correct or false (or only has the false sign)
	if userSolution == correctSolution:
		print " Correct!"
		correct += 1
		return 0 #Success
	elif ignoresign & userSolution == -correctSolution:
		print " Correct!"
		correct += 1
		return 0 #Success
	else:
		print " False:",correctSolution
		false += 1
		return 1 #Failure

#Generates an exercise with - as the operator.
#Returns 0 if solved correctly, 1 else
def subEx():
	#Allow write-access to the global statistics counters
	global correct,false
	#Generate two random numbers
	op1 = randint(min,max)
	op2 = randint(min,max)
	#Calculate the correct solution
	correctSolution = op1 - op2
	#Read the user's solution (not yet converted to a number)
	userSolution = raw_input(str(op1) + " - " + str(op2) + " = ")
	#Check if the user requested to show statistics
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	#Check if the user's solution is correct or false (or only has the false sign)
	if userSolution == correctSolution:
		print " Correct!"
		correct += 1
		return 0 #Success
	elif ignoresign & userSolution == -correctSolution:
		print " Correct!"
		correct += 1
		return 0 #Success
	else:
		print " False:",correctSolution
		false += 1
		return 1 #Failure

#Generates an exercise with * as the operator.
#Returns 0 if solved correctly, 1 else
def multEx():
	#Allow write-access to the global statistics counters
	global correct,false
	#Generate two random numbers
	op1 = randint(min,max)
	op2 = randint(min,max)
	#Calculate the correct solution
	correctSolution = op1 * op2
	#Read the user's solution (not yet converted to a number)
	userSolution = raw_input(str(op1) + " * " + str(op2) + " = ")
	#Check if the user requested to show statistics
	if userSolution == "stats":
		statistics()
		return
	userSolution = int(userSolution)
	#Check if the user's solution is correct or false (or only has the false sign)
	if userSolution == correctSolution:
		print "Correct!"
		correct += 1
		return 0 #Success
	elif ignoresign & userSolution == -correctSolution:
		print " Correct!"
		correct += 1
		return 0 #Success
	else:
		print "False:",correctSolution
		false += 1
		return 0 #Failure

def loop():
	while 1:
		choice(exFunctions)() #Generate an exercise
		
def block():
	startTime = time.time()
	#i = loop counter
	i = blockCount
	#A for+xrange loop can't be used here because
	#if repeatOnFalse is set the loop counter must be increased by one.
	#This is not possible with the standard generators.
	while i > 0:
		try:
			ret = choice(exFunctions)() #Generate an exercise			
			#If the exercise has not been solved correctly
			#and if repeatOnFalse is set, generate a new one
			#without decreasing the loop counter (adding one instead)
			if ret and repeatOnFalse	:
				i += 1
		except ValueError:
			continue #Next exercise
		except EOFError:
			#The user typed CTRL+D, so print a newline character (before statistics)
			#and return to the command line interface
			print
			break
		#Decrement the loop counter
		i -= 1
	deltaTime = time.time() - startTime
	#If enabled, write the average time per exercise
	#into the statistics file
	if statsFile:
		with open(".mathtrainer","w") as fout:
			print >> fout, "%.3f" % (deltaTime/blockCount)
	#Print the statistics into stdout
	print "%i exercises took %.3f seconds" % (blockCount, deltaTime)

#
#Main
#

#Set the default values
min = 0
max = 100
ignoresign = 0
exFunctions = [addEx,subEx] #Function pointers generating an exercise, a random one == selected each time
blockCount = 10 #How many exercises to generate per block
exLoopFunction = block #A function pointer either to block() or to loop()
repeatOnFalse = 1 #If > 0, don't decrease the block loop counter if the exercise has not been solved correctly
statsFile = 0 #Whether to write the solving times into ~/.mathtrainer
#Statistical counters
correct = 0
false = 0
	
#Main command line loop
while 1:
	cmdline = raw_input("> ")
	cmds = cmdline.split(" ")
	cmd = cmds[0].lower().strip() #The actual command
	if cmd == "help":
		print "Possible commands:"
		print "help - D==play help"
		print "exit - Quit"
		print "start - Start the exercises"
		print "reset - Reset the counters"
		print "statistics - Show the statistics"
		print "set limits [min] [max] - Set new limits (defaults min=0 and max = 100"
		print "set ignore-sign [true|false] - Set whether to ignore the sign (default true)"
		print "set operators [operators] - Set the operators (defaults + and -)"
		print "set mode [loop|block] [blocksize] - Set the exercise mode (default block, blocksize 10)"
		print "set repeat-on-false [true|false] - Set whether to accept only correctly-solved exercises (default true)"
		print "[enable|disable] stats-file - Set whether to save the time in ~/.mathtrainer (default disables)"
	elif cmd == "exit":
		break
	elif cmd == "enable":
		cmd = cmds[1].lower()
		if cmd == "stats-file":
			statsFile = 1
	elif cmd == "disable":
		cmd = cmds[1].lower()
		if cmd == "stats-file":
			statsFile = 0
	elif cmd == "start":
		try:
			exLoopFunction()
		except KeyboardInterrupt:
			break #Exit if the user typed CTRL+C or CTRL+D
	elif cmd == "reset":
		correct = 0
		false = 0
	elif cmd == "statistics":
		statistics()
	elif cmd == "set":
		cmd = cmds[1].lower()
		if cmd == "limits":
			min = int(cmdline[2])
			max = int(cmdline[3])
		elif cmd == "mode":
			cmd = cmdline[2].lower()
			if cmd == "block":
				exLoopFunction = block
				blockCount = int(cmdline[2])
			elif cmd == "loop":
				 exLoopFunction = loop
		elif cmd == "operators":
			exFunctions = []
			operators = raw_input()
			if '+' in operators:
				exFunctions.append(addEx)
			if '-' in operators:
				exFunctions.append(subEx)
			if '*' in operators:
				exFunctions.append(multEx)
		elif cmd == "ignore-sign":
			if cmds[2] == "true":
				ignoresign = 1
			elif cmds[2] == "false":
				ignoresign = 0
			else:
				print "Invalid value:",cmds[2]
		elif cmd == "repeat-on-false":
			if cmds[2] == "true":
				reapeatOnFalse = 1
			elif cmds[2] == "false":
				reapeatOnFalse = 0
			else:
				print "Invalid value:",cmds[2]
		else:
			print "Invalid command:",cmd
	else:
		print "Invalid command:",cmd