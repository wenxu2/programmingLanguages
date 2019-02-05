/*
File name: proj.c
Author: Wenwen Xu
Project: Project 1
Description: this file contains logic for this project 
*/

#include <stdio.h>
#include "proj.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//define variables 
#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401 


int lookahead;

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

char* getWord(char c, FILE *fp, char *word)
{

    //char *word;
    //word = malloc(5);
    int i = 0;
     while(isalpha(c))
            {
                word[i++] = c;
                c = fgetc(fp);
            }

            word[i] = '\0';
            //printf("%s\n",word);
            ungetc(c,fp);

    return word;
}


bool isRowExist(Table currentTable, Row newRow)
{
   Row currentRow = currentTable->head;

   while(currentRow != NULL)
   {
       if(currentRow->value == newRow->value)
       {
           //printf("exist!\n");
           return true;
       }

        currentRow = getNextRow(currentRow);
       
   }

    //printf("does not exist!\n");
    return false;
}

int lexanAnalyzer(){
    
    FILE *fp;
    char c;
    fp = fopen("test.txt", "r");

    //create table
    Table symboltable = createTable(NULL, NULL, 0);


    if(fp == NULL){

        printf("ERROR!\n");

    }

    //count line number 
    int count = 1;
    int pos = 0;


    while( (c = getc(fp)) != EOF)
    {
        //printf("%c", c);
         if(c == '\n'){
            count++;
            //printf("Line %d: \n ", count);
         }

        if(isCharNull(c)) //if c is a space or tab
        {
            //printf("%c - this is a space\n", c);
            //do nothing
        }else if (c == '\n') // if c is a new line, increase line number 
        {
            count ++;

        }else if(isdigit(c)) //if c is a digit
        {
           // printf("c is a digit: %c \n", c);

            /*
            * get the number into numLexeme
            */

            //return NUM;

        }else if(isalpha(c)) //if c is a letter 
        {
            //printf("c is a letetr %c \n", c);
            //get identiferier into value
            char* word = malloc(50);
            getWord(c,fp,word);

            //printf("%s\n", word);

            Row newRow = createRow(pos, word, ID, NULL);

            if(!isRowExist(symboltable, newRow))
            {
                insertRow(symboltable, pos, word, ID);
                pos++;
            }

           
            
        }else{
        
        //return c;
     }

    }
    //close file    
    fclose(fp);
    
    displayTable(symboltable);

    return 0;
}


//int lookup(char *value);


bool isCharNull(char c){

    if(c == ' ' || c == '\t') //check if c is a space or tab
    {
        return true;
    }

    return false;
}


/*
*recursive descent parser
*/

void match(int t)
{
    if(lookahead == t)
    {
        lookahead = lexanAnalyzer();
    }else{
        printf("syntax error\n");//need add line number 
    }
}

void factor(){

    if(lookahead == ID)
    {
        match(ID);
    }else if(lookahead == NUM)
    {
        match(NUM);
    }else if (lookahead == '(')
    {
        match('(');
        //expression
        match(')');
    }
    else{
        printf("Error Message");
    }
}

void term(){
    factor();
    while(lookahead == '*' || lookahead == '/')
    {
        match(lookahead);
        factor();
    }
}


