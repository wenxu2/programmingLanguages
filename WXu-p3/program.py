#!/usr/bin/python
import tkinter as tk
import sys

import sys


file = open('fsa.txt','r') 
a = '' # hold the line
part = '' # holds strings after the line being split

for x in file:
    a = x
file.close() 

#read legal.txt
file = open(sys.argv[1],'r') 
inputString = '' # hold the line
for x in file:
    inputString = x
file.close() 

#GUI
root = tk.Tk()
canvas = tk.Canvas(root, width=500, height=1000, borderwidth=0, highlightthickness=0) 
canvas.pack()

#split the stirng 
part = a.split(';')
legalArrlist = []
transition = part[2].split(',')

x = 0
while x < len(transition):
    individual = transition[x][1:-1].split(':')
    if(individual[0] == individual[1]):
        y1 = 100
        y2 = 140
        x1 = 150
        x2 = 220
        if(individual[0] != '0'):
            y1 = y1 + 80 * (int(individual[0]))
            y2 = y2 + 80 * (int(individual[0]))
        canvas.create_oval(x1, y1, x2, y2)
        canvas.create_text(230,y1+20,fill="black",font="Times 20 italic bold",text=individual[2])
        if len(legalArrlist) != 0: 
            if individual[2] != legalArrlist[len(legalArrlist) - 1] :
                legalArrlist.append(individual[2])
        if len(legalArrlist) == 0:
            legalArrlist.append(individual[2])

    if(individual[0] != individual[1]):
        i = int(individual[1]) - 1
        y1 = 140
        y2 = 180
        x1 = 140
        x2 = 140
        if(int(individual[0]) == i):
            if(individual[0] != '0'):
                y1 = y1 + 80 * (int(individual[0]))
                y2 = y2 + 80 * (int(individual[0]))
            canvas.create_line(x1, y1, x2,y2, width = 2, arrow=tk.LAST)
            canvas.create_text(x2+10,y1+20,fill="black",font="Times 20 italic bold",text=individual[2])
            if len(legalArrlist) != 0: 
                if individual[2] != legalArrlist[len(legalArrlist) - 1] :
                    legalArrlist.append(individual[2])
            if len(legalArrlist) == 0:
                legalArrlist.append(individual[2])

        #draw to the gui
        if(int(individual[0]) > int(individual[1])):
            y1 = y1 + 80 * (int(individual[0])) - 20
            y2 = y2 + 80 * (int(individual[1])) - 60
            canvas.create_line(120, y1, 40,y1, width = 2, arrow=tk.LAST)
            canvas.create_line(40, y2, 100,y2, width = 2, arrow=tk.LAST)
            canvas.create_line(40, y1, 40,y2, width = 2, arrow=tk.LAST)
            canvas.create_text(60,y1/2+20,fill="black",font="Times 20 italic bold",text=individual[2])
            if len(legalArrlist) != 0: 
                if individual[2] != legalArrlist[len(legalArrlist) - 1] :
                    legalArrlist.append(individual[2])
            if len(legalArrlist) == 0:
                legalArrlist.append(individual[2])

    #assign individual to null
    individual = ''
    x = x + 1

#set x and y
x = 0
y1 = 100
y2 = 140
#create stage 0 arrow line
canvas.create_line(60, 70, 100, 120, width = 2, arrow=tk.LAST)
while x < int(part[0]):
    cir = canvas.create_oval(100, y1, 170, y2, fill='green')
    canvas.create_text(140,y1+20,fill="black",font="Times 20 italic bold",text=x)
    acceptance = part[4].split(',')
    if str(x) in acceptance:
        #print("Exist in " + str(x))
        cir = canvas.create_oval(110, y1+5, 160, y2-5)

    y1 = y1 + 80
    y2 = y2 + 80
    x += 1

#bool variable
illegalProgram = None

#check if the string is legal
for x in inputString:
    if x not in legalArrlist:
        illegalProgram = True

reducedArray = []
inputArray = []
for x in inputString:
    inputArray.append(x)

for x in inputArray:
    if len(reducedArray) != 0: 
        if x != reducedArray[len(reducedArray) - 1] :
            reducedArray.append(x)
    if len(reducedArray) == 0:
        reducedArray.append(x)

if legalArrlist != reducedArray:
    illegalProgram = True
else:
    illegalProgram = False

#print if the prgram is legal or not 
if illegalProgram:
    print("Illegal Program")
else :
    print("Legal Program")

#draw the GUI
root.wm_title("Project 3")
root.mainloop()