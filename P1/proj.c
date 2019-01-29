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


struct SYMBOLTABLE{
    int position;
    char *value;
    int type;
};

int hashCode(int key, int size)
{
    return key%size;
}

int search(int key)
{
    int index = hashCode();
}

SymbolTable createTable(int position, char *value, int type)
{
    SymbolTable symbolTable = malloc(sizeof(*symbolTable));
    symbolTable->position = position;
    symbolTable->value = value;
    symbolTable->type = type;

    return symbolTable;
}

void lexanAnalyzer(){
    
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

        }else if(isalpha(c)) //if c is a letter 
        {
            printf("c is a letetr %c \n", c);
        }

    }
    //close file    
    fclose(fp);
}

bool isCharNull(char c){

    if(c == ' ' || c == '\t') //check if c is a space or tab
    {
        return true;
    }

    return false;
}



