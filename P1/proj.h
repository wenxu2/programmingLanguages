/*
File name: proj.h
Author: Wenwen Xu
Project: Project 1
Description: headfile to hold all function to be used in this project
*/

#include <stdbool.h>
#ifndef PROJ_H
#define PROJ_H

typedef struct SYMBOLTABLE *SymbolTable; 

int hashCode(int key, int size);

SymbolTable createTable(int position, char *value, int type);

void readFile();

void lexanAnalyzer();

bool isCharNull(char c);

#endif