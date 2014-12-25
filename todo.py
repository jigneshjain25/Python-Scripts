#!/usr/bin/python
import os.path
import sys

todoFile = "/home/jignesh/.todo"
todoLines = []

def addTodo():
    for line in sys.stdin:
        todoLines.append(line)

def exitTodo():
    f = open(todoFile,'w')
    f.writelines(todoLines)
    f.close()

def displayTodo():
    print ""
    cnt=1
    for line in todoLines:
        sys.stdout.write(str(cnt)+": "+line)
        cnt=cnt+1
    print ""

def delTodo():
    positions = []
    line = raw_input().split(" ")
    for i in line:
        positions.append(int(i)-1)
    positions.sort(reverse=True)

    for i in positions:
        if i < len(todoLines):
            del todoLines[i]

if __name__ ==  "__main__":

    if(os.path.isfile(todoFile)):
        with open(todoFile) as f:
            todoLines = f.readlines()

    if len(sys.argv) == 1:
        displayTodo()
    else:
        if sys.argv[1] == "add":
            addTodo()
        elif sys.argv[1] == "del":
            delTodo()
        exitTodo()
