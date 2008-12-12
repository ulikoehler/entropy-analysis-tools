#!/usr/bin/env python
from __future__ import with_statement
import sys
import os
import os.path
import getopt

#Functions for checking if a character matches the specified criterias
def checkCharAll(c):
	return 1
	
def checkCharAlpha(c):
	return c.isalpha()
	
#Parse the boolean options
try:
	opts,args = getopt.gnu_getopt(sys.argv[1:], "bs:", ["binary","separator="])
except getop.GetoptError, err:
	print str(err)
	usage()
	sys.exit(2)
	
#
#Evaluate the options
#
#Set the appropriate char checker function
if "b" in opts:
	checkChar = checkCharAll
else:
	checkChar = checkCharAlpha
#Set the appropriate separator
separator = ","
if separator in opts:
	separator = opts["separator"]
	
#Check if the user supplied enough arguments
if len(sys.argv) < 2:
	print "You supplied only ",sys.argc," of at least 2 arguments"
	sys.exit(1)

#
#Parse the remainding command line options
#
dbFilename = sys.argv[1]
action = sys.argv[2]
if action == "train" or action == "score":
	inputFilename = sys.argv[3]

dbExists = os.path.exists(dbFilename)

#
#Read the database
#
data = {}
if dbExists:
	#Open the database for reading
	dbRead = open(dbFilename,"r")
	#Read all datasets
	for line in dbRead:
		splits = line.rpartition(separator)
		data[splits[0]] = int(splits[2])

#	
#Perform the user-selected action
#

#Train the database
if action == "train":
	#Set the last character variable to a default value
	lastc = ' '
	with open(inputFilename) as infile:
		while 1:
			c = infile.read(1).upper().swapcase()
			if len(c) is 0:
				break
			if checkChar(c):
				if lastc.isalpha():
					pattern = lastc + c
					if not pattern in data:
						data[pattern] = 0
					data[pattern] = data[pattern] + 1
			lastc = c
	infile.close()
#Score a file
elif action == "score":
	with open(inputFilename) as infile:
		score = 0
		lastc = ' '
		while 1:
			c = infile.read(1).upper().swapcase()
			if len(c) is 0:
				break
			if checkChar(c):
				if lastc.isalpha():
					pattern = lastc + c
					score += data[pattern]
			lastc = c
	#Print out the result score
	print "File has a score of",score


#		
#Close the database
#
if dbExists:
	dbRead.close()
#
#Write the database data (if neccessary)
#
#Open the database for writing
if action == "train":
	dbWrite = open(dbFilename,"w")
	dbWrite.truncate() #Remove all previous data
	for key in data:
		dbWrite.write("%s%s%s\n"%(key,separator,data[key]))
		
	dbWrite.close()