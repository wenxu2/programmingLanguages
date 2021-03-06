/*
File name: proj.h
Author: Wenwen Xu
Project: Project 1
Description: headfile to hold all function to be used in this project
*/

#include <stdbool.h>
#ifndef PROJ_H
#define PROJ_H

//run the program
void runProgram(char *filename);

//lexanAnalyzer 
int lexanAnalyzer();

//recursive descent parser
void match(int t);

void factor();

void term();

void expression();

void assignStmt();

//build string and comment array
char *getWord(char c, char *word);

void getComment(char c, char *line);

void getNumber(char c, char *number);

bool valueIdentiferCheck(char *word);

bool numberCheck(char *number);

void assignsign(char ch);

#endif
