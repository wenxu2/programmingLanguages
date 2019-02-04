/*
File name: proj.h
Author: Wenwen Xu
Project: Project 1
Description: headfile to hold all function to be used in this project
*/

#include <stdbool.h>
#ifndef PROJ_H
#define PROJ_H

typedef struct TABLE *table;

table createTable(char *value, int key,table next);

void readFile();

int lexanAnalyzer();

int hash(char *value);

bool isCharNull(char c);

void freeTable(table currentTable);

int lookup(char *value);


//recursive descent parser
void match(int t);

void factor();

void term();

void expression();

void assignStmt();


#endif