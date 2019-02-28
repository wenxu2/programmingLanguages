/*
 File name: symbol.h
 Author: Wenwen Xu
 Project: Project 2
 Description: this file contains function for the symbol
 */

#include <stdbool.h>
#ifndef SYMBOL_H
#define SYMBOL_H


//create a row
typedef struct ROW *Row;
Row createRow(int pos, char *value, int type, Row next);

void setNextRow(Row currentRow, Row next);

Row getNextRow(Row currentRow);

//create a table
typedef struct TABLE *Table;
Table createTable(Row head, Row tail, int size);

//inseart value
void insertRow(Table currentTable, Row newRow);

void displayTable(Table currentTable);

bool isValueExist(Table currentTable, char *value);

//free the row
void freeRow(Row currentRow);

#endif
