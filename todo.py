#!/usr/bin/python
import os.path
import sys

todoFile = "/home/jignesh/Dropbox/todo.txt"
todoLines = []

def addTodo():
    for line in sys.stdin:
    	line = line.strip()
    	if line != "":
	        todoLines.append(line)

def exitTodo():
    f = open(todoFile,'w')
    for s in todoLines:
	    f.write(s+"\n")
    f.close()

def displayTodo():
    print ""
    cnt=1
    for line in todoLines:
        sys.stdout.write(str(cnt)+": "+line+"\n")
        cnt=cnt+1
    print ""

def delTodo():
	positions = []
	for s in sys.argv:
		if s.isdigit():
			positions.append(int(s)-1)
	
	positions.sort(reverse=True)
	
	for i in positions:
		if i < len(todoLines):
			del todoLines[i]

def cleanTodo():
	positions = []
	for i in range(0,len(todoLines)):
		todoLines[i] = todoLines[i].strip()
		if todoLines[i] == "":
			positions.append(i)
			
	positions.sort(reverse=True)	
	
	for i in positions:
		del todoLines[i]
						
if __name__ ==  "__main__":

    if(os.path.isfile(todoFile)):
        with open(todoFile) as f:
            todoLines = f.read().splitlines()              
		
	cleanTodo()
	
    if len(sys.argv) == 1:
        displayTodo()
    else:
        if sys.argv[1] == "add":
            addTodo()
        elif sys.argv[1] == "del":
            delTodo()
        exitTodo()   
