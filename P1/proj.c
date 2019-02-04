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

struct TABLE{
    char *value;
    int key;
    table next; 
};

table createTable(char *value, int key, table next){

    table newTable = malloc(sizeof *newTable);
    newTable->value = value;
    newTable->key = key;
    newTable->next = next;

    return newTable;
}


/*
* free the table at the end 
*/
void freeTable(table currentTable){
    free(currentTable);
}



int lexanAnalyzer(){
    
    FILE *fp;
    char c;
    fp = fopen("test.txt", "r");

    if(fp == NULL){

        printf("ERROR!\n");

    }

    //count line number 
    int count = 1;

    while( (c = getc(fp)) != EOF)
    {
        //printf("%c", c);
         if(c == '\n'){
            count++;
            printf("Line %d: \n ", count);
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
            printf("c is a digit: %c \n", c);

            /*
            * get the number into numLexeme
            */

            //return NUM;

        }else if(isalpha(c)) //if c is a letter 
        {
            printf("c is a letetr %c \n", c);

            //int pos = lookup(c);
            

            //return ID;
        }

    }
    //close file    
    fclose(fp);

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
        error("Syntax error");
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
}


