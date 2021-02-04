#!usr/bin/env python3

#Will take the output from a .pbs script and return only the lines containing 
#the word Max, this line will show the time to complete the operation

import sys

fptr = open(sys.argv[-1], 'r')

for line in fptr:
    if "Max" in line:
        print(line)
        
