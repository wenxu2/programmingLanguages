/*
File name: main.c
Author: Wenwen Xu
Project: Project 2
Description: main file to run the project 
*/

#include <stdio.h>
#include <stdlib.h>
#include "proj.h"
#include <ctype.h>
#include "symbol.h"

int main(int argc, char* argv[])
{
    ///get user input for file name
    char *filename = argv[1];

    printf("\n\n%s\n", filename);
    
    runProgram(filename);//run the program with file 1

    return 0;
}