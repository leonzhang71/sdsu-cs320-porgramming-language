#Name: Chonglin Zhang
#class: CS320
#instructor: Shawn Healey
#Date: 2-14-2021
#Program: Create a "FANBOYS" program and require to "import re" (regular expresion)
#Purpose: "FANBOYS" are for, and, nor, but, or, yet, so. We need to find all the fanboys from sentences.
#Also, we need to take fanboys out and make them to be an independent sentences.
#How to use: 
#step 1: create a text file, and name "text.txt" 
#step 2: put the text file in the same direction as the hw1cs320.py file.
#step 3: open your ide and run this program

import re

#open the file
file = open("text.txt", 'r')

#read the file
readfile = file.readlines()

#print the context from the text.txt(test)
#print(readfile)

#give the string
str = readfile[0]

#split the fanboys
fanboys = re.split(', for |, and |, nor |, but |, or |, yet |, so ', str)

#use the for loop to print all sentences in order 
for i in range(len(fanboys)):
    print(i+1,":", fanboys[i])
    print()
