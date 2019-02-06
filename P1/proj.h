/*
File name: proj.h
Author: Wenwen Xu
Project: Project 1
Description: headfile to hold all function to be used in this project
*/

#include <stdbool.h>
#ifndef PROJ_H
#define PROJ_H

//lexanAnalyzer 
bool isCharNull(char c);

int lexanAnalyzer();

//recursive descent parser
void match(int t);

void factor();

void term();

void expression();

void assignStmt();

//build string and comment array
char* getWord(char c, char* word);

void getComment(char c, char *line);

#endif