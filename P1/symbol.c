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

void insertRow(Table currentTable, int pos, char *value, int type)
{
    Row newRow = createRow(pos, value, type, NULL);
    currentTable->size += 1;

    if(currentTable->tail == NULL)
    {
        currentTable->head = newRow;
        currentTable->tail = newRow;

        return;
    }
    
    setNextRow(currentTable->tail, newRow);
    currentTable->tail = newRow;
}

void displayTable(Table currentTable){

    Row currentRow = currentTable->head;
    
    while(currentRow != NULL)
    {
        printf("%d %s % d \n", currentRow->pos, currentRow->value, currentRow->type);
        currentRow = getNextRow(currentRow);
        
    }

}

bool isRowExist(Table currentTable, Row newRow)
{
   Row currentRow = currentTable->head;

   while(currentRow != NULL)
   {
       if(currentRow->value == newRow->value)
       {
           return true; //value already exist in the table
       }

       currentRow = getNextRow(currentRow);
       
   }

    return false; //value does not exist 
}

//free the row 
void freeRow(Row currentROw)
{
    free(currentROw);
}
