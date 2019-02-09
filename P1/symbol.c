#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "symbol.h"

struct ROW{

    int pos;
    char *value;
    int type;
    Row next;
};

Row createRow(int pos, char *value, int type, Row next){

    Row newRow = malloc(sizeof *newRow);
    newRow->pos = pos;
    newRow->value = value;
    newRow->type = type;
    newRow->next = next;

    return newRow;
}

struct TABLE{
    
    Row head;
    Row tail;
    int size;
};

Row getNextRow(Row currentRow){
    return currentRow->next;
}

void setNextRow(Row currentRow, Row next)
{
    currentRow->next = next;
}

Table createTable(Row head, Row tail, int size){

    Table newTable = malloc(sizeof *newTable);
    newTable->head = head;
    newTable->tail = tail;
    newTable->size = size;

    return newTable;

}

void insertRow(Table currentTable, Row newRow)
{
    if(currentTable->tail == NULL)
    {
        currentTable->tail = newRow;
    }

    setNextRow(newRow, currentTable->head);
    currentTable->head = newRow;
    currentTable->size += 1;

}

void displayTable(Table currentTable){

    Row currentRow = currentTable->head;
    
    while(currentRow != NULL)
    {
        printf("%d %s % d \n", currentRow->pos, currentRow->value, currentRow->type);
        currentRow = getNextRow(currentRow);
        
    }

}

bool isValueExist(Table currentTable, Row newRow, bool a)
{
   Row currentRow = currentTable->head;
   a = false;

   while(currentRow != NULL)
   {
       if(strcmp(currentRow->value, newRow->value) == 0)
       {
           a = true;
           return a; //value already exist in the table
       }
       
       currentRow = getNextRow(currentRow);
       
   }

   return a; //value does not exist 
}

//free the row 
void freeRow(Row currentROw)
{
    free(currentROw);
}
