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
int id;
char c;
char* word;
char *number;

void runProgram()
{
    symboltable = createTable(NULL, NULL, 0);
    fp = fopen("test.txt", "r");

    insertRow(symboltable, pos,"begin", BEGIN);
    pos++;

    //displayTable(symboltable);

    while(fp != NULL)
    {
        assignStmt();
    }

    fclose(fp);

}


int lexanAnalyzer(){

    while(true)
    {
        c = fgetc(fp);
    
        if(c == '~')
        {
            char *line = malloc(10000);
            getComment(c,line);
            lineNumber++;
            free(line);
        }
        else if(c == '\n'){
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
            word = malloc(50);
            getWord(c,word);
           
            if(strcmp(word,"begin") == 0)
            {
                id = BEGIN;

            }else if(strcmp(word,"end") == 0)
            {
                id = END;
                
            }else{
            
                id = ID;
            }

            //create the row 
            newRow = createRow(pos,word,id,NULL);

            //check if the row exist 
            if(!isRowExist(symboltable, newRow))
            {
                printf("Row does not exist\n");
                insertRow(symboltable, pos, word, id);
                pos++;
                freeRow(newRow);//free the row after insert 

            }else if(strcmp(word,"begin"))
            {
                //lookahead = ID;
                return BEGIN;

            }else if(strcmp(word,"end"))
            {
                return END;
                exit(0);
            }

            //lookahead = ID;
            free(word);
            return ID;

        }else if(c == EOF)//end of the file
        {
            displayTable(symboltable);
            exit(0);//exit the program 

        }else{
            //lookahead = c;
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
    }

    if(c != '=' && c != '(' && c != ')' && c != '-' && c!= '*' && c!= '/' & c!= '+' && (!isalpha(c)) && (!isalnum(c)) && c != '\n' && c != ' ' && c != '\t')
    {
        printf("Syntax Error: Invalided Identifer '%s' in line %d!\n", word,lineNumber);
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
    //printf("%s\n",line);
}

/*
*recursive descent parser
*/
void match(int t)
{
    if(lookahead == t)
    {
        lookahead = lexanAnalyzer();
        displayTable(symboltable);

    }else{
        printf("match - Syntax Error: check line %d.\n",lineNumber);//need add line number 
        exit(0);
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
        expression();
        match(')');

    }else{
        printf("factor - Syntax Error: check line %d.\n",lineNumber);
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

    if(lookahead == '=' )
    {
        match(lookahead);
        expression();
        match(';');
    }else if (lookahead != '='){
        printf("Syntax Error: missing '=' in line %d.\n", lineNumber);
        exit(0);
    }
    
}





