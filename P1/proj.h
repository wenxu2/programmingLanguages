/*
File name: proj.h
Author: Wenwen Xu
Project: Project 1
Description: headfile to hold all function to be used in this project
*/

#include <stdbool.h>
#ifndef PROJ_H
#define PROJ_H

//create a row
typedef struct ROW *Row;
Row createRow(int pos, char *value, int type, Row next);

void setNextRow(Row currentRow, Row next);

Row getNextRow(Row currentRow);

//create a table
typedef struct TABLE *Table;
Table createTable(Row head, Row tail, int size);

//inseart value
void insertRow(Table currentTable, int pos, char *value, int type);

void displayTable(Table currentTable);

bool isRowExist(Table currentTable, Row newRow);

//lexanAnalyzer 
void readFile();

int lexanAnalyzer();

int hash(char *value);

bool isCharNull(char c);

int lookup(char *value);

//recursive descent parser
void match(int t);

void factor();

void term();

void expression();

void assignStmt();

char* getWord(char c, FILE *fp, char* word);

void getComment(char c, FILE *fp, char *line);

#endif