#!/usr/bin/env python
from __future__ import with_statement
import sys
import os
import os.path
import getopt

#Parse command line options
dbFilename = sys.argv[1]
action = sys.argv[2]
if action == "train":
	inputFilename = sys.argv[3]

dbExists = os.path.exists(dbFilename)

#Read the database
data = {}
if dbExists:
	#Open the database for reading
	dbRead = open(dbFilename,"r")
	#Read all datasets
	for line in dbRead:
		splits = line.partition(" ")
		data[splits[0]] = int(splits[2])
	
#Perform the user-selected action
if action is "train":
	infile = open(inputFilename)
	#Set the last character variable to a default value
	lastc = ' '
	with open(inputFilename) as infile:
		print "t" #TODO DEBUG
		c = f.read(1).upper().swapcase()
		if c.isalpha():
			if lastc.isalpha():
				pattern = lastc + c
				data[pattern] += 1
				lastc = c
			else:
				lastc = c
	infile.close()
	
#Close the database
if dbExists:
	dbRead.close()

#Open the database for writing
dbWrite = open(dbFilename,"w")
#Write the database data
dbWrite.truncate()
for key in data:
	print >> dbWrite, key, data[key]
	
dbWrite.close()