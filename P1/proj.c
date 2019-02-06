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
#include "symbol.h"

//define variables 
#define ID 300
#define NUM 301
#define BEGIN 400
#define END 401 

int lookahead;


int lexanAnalyzer(){
    
    char c;
    
    //create table
    Table symboltable = createTable(NULL, NULL, 0);

    //count line number 
    int count = 0;
    int pos = 0;

    while(true)
    {
        c = getchar();
        
        if(c == '~')
        {
            char *line = malloc(10000);
            //getComment(c,fp,line);
            count++;
        }
        else if(c == '\n'){
            count++;
        }
        else if(isCharNull(c)) //if c is a space or tab
        {
            //do nothing
            
        }else if (c == '\n') // if c is a new line, increase line number 
        {
            count ++;

        }else if(isdigit(c)) //if c is a digit
        {
            /*
            * get the number into numLexeme
            */
            return NUM;

        }else if(isalpha(c)) //if c is a letter 
        {
            //get identiferier into value
            char* word = malloc(50);
            //getWord(c,fp,word);

            Row newRow = createRow(pos, word, ID, NULL);

            if(!isRowExist(symboltable, newRow))
            {
                insertRow(symboltable, pos, word, ID);
                pos++;
            }else if(strcmp(word,"begin"))
            {
                printf("begin\n");
                return BEGIN;

            }else if(strcmp(word,"end"))
            {
                printf("end\n");
                return END;
            }
        }
     }

    return 0;
}

/*
* build string array
*/
char* getWord(char c, FILE *fp, char *word)
{

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

void getComment(char c, FILE *fp, char *line)
{

    int i = 0;
    while(c != '\n')
    {
        line[i++] = c;
        c = fgetc(fp);
    }

    line[i] = '\0';
    printf("%s\n",line);
    ungetc(c,fp);    
}

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
        printf("Error Message\n");
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

void expression(){
    term();
    while(lookahead == '+' || lookahead == '-')
    {
        match(lookahead);
        term();
    }
}

void assignStmt()
{
    match(ID);

    if(lookahead != '=')
    {
        printf("ERROR");
    }else{
        match(lookahead);
        expression();
        match(';');
    }
}




