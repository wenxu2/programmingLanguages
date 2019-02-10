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

/*
* declear values
*/
int lookahead = ID;
FILE *fp;
int pos = 0;
int lineNumber = 0;
Table symboltable;
Row newRow;
char* word;
char *number;
bool a = false;

void runProgram()
{
    symboltable = createTable(NULL, NULL, 0);
    fp = fopen("test.txt", "r");
    
    while(fp != NULL)
    {
        lexanAnalyzer();
        
        if(lexanAnalyzer() == '=')
        {
            assignStmt();
        }

    }
    
    fclose(fp);
    free(newRow);
    free(symboltable);

}

int lexanAnalyzer(){

    while(true)
    {
        printf("lookhead: %d\n", lookahead);
        char c = fgetc(fp);
    
        if(c == '~')
        {
            char *line = malloc(10000);
            getComment(c,line);
            lineNumber++;
            line = NULL;
        }else if(c == '\n'){
            lineNumber++;
        }
        else if(c == ' ' || c == '\t') //if c is a space or tab
        {
            /*
            * do nothing
            */
        }else if (c == '\n') //if c is a new line, increase line number 
        {
            lineNumber++;
            

        }else if(isdigit(c)) //if c is a digit
        {
            /*
            * get the number into numLexeme
            */
            number = malloc(50);
            getNumber(c,number);
            free(number);
            return NUM;

        }else if(isalpha(c)) //if c is a letter 
        {
            
            //get identiferier into value
            word = malloc(100);
            getWord(c,word);
            
            //printf("Word: %s\n",word);
            
            int id = ID;
           
            if(strcmp(word,"begin") == 0)
            {
                id = BEGIN;

            }else if(strcmp(word,"end") == 0)
            {
                id = END;
                
            }
            
            newRow = createRow(pos, word, id, NULL);
            
            //check if the row does not exist
            if(!isValueExist(symboltable, newRow))
            {
                insertRow(symboltable, newRow); //insert into the table
                
                if(pos == 0 && (strcmp(word, "begin") != 0))
                {
                    printf("Missing identifer 'begin' in the file\n");
                    exit(0);
                
                }

                pos++;
                word = NULL;
                
            }else if(strcmp(word,"begin"))
            {
                return BEGIN;

            }else if(strcmp(word,"end"))
            {
                return END;
            }

            free(word);
            return ID;

        }else if(c == EOF) //end of the file, should end with "end"
        {
            newRow = createRow(pos, "end", END, NULL);
            if(!isValueExist(symboltable, newRow))
            {
                printf("Missing identifer 'end' in the file\n");
                exit(0);
            }
            
        }else{
            return c;
        }
     }

}

/*
* build string array
*/
char *getWord(char c, char *word)
{

    int i = 0;
    while(isalpha(c) || c == '_' || isalnum(c))
    {
        word[i++] = c;
        c = fgetc(fp);

        if(c == '(')
        {
            if(isalpha(word[i-1]))
            {
                printf("Syntax Error in line %d.\n", lineNumber);
                exit(0);
            }
        }
    }

    if(strcmp(word, "end") == 0)
    {
        newRow = createRow(pos, "end", END, NULL);
        insertRow(symboltable, newRow);
        displayTable(symboltable);
        exit(0);
    }

    word[i] = '\0';
    ungetc(c,fp);
    
    return word;
}

/*
* build number array
*/
void getNumber(char c, char *number)
{
    int i = 0;
    while(isnumber(c) || c == '.')
    {
        
        number[i++] = c;
        c = fgetc(fp);  
    }

    number[i] = '\0';
    ungetc(c,fp);
    
}

/*
* build comment array
*/
void getComment(char c, char *line)
{

    int i = 0;
    while(c != '\n')
    {
        line[i++] = c;
        c = fgetc(fp);
    }

    line[i] = '\0';
    ungetc(c,fp);    
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
        printf("Syntax Error: check line %d.\n",lineNumber);//need add line number 
        exit(0);
    }
}

void factor(){

    lexanAnalyzer();
    if(lookahead == ID)
    {
        match(ID);

    }else if(lookahead == NUM)
    {
        match(NUM);

    }else if (lookahead == '(')
    {
        match('(');
        expression();
        match(')');

    }else{
        printf("Syntax Error: check line %d.\n",lineNumber-1);
        exit(0);
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

    if(lookahead == '=' || lookahead == ID)
    {
        match(lookahead);
        expression();
        match(';');

    }else{
        
        printf("Syntax Error: check line %d.\n",lineNumber-1);
        exit(0);
    }
    
}





