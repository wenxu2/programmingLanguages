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
char c;
char* word;
char *number;
bool a = false;

void runProgram()
{
    symboltable = createTable(NULL, NULL, 0);
    fp = fopen("test.txt", "r");

    c = fgetc(fp);

    while(fp != NULL)
    {
        checkEnding(c);
        while(lexanAnalyzer() != '=')
        {
            lexanAnalyzer();
        }
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
        c = fgetc(fp);
    
        if(c == '~')
        {
            char *line = malloc(10000);
            getComment(c,line);
            lineNumber++;
            line = NULL;
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

            int id = ID;
           
            if(strcmp(word,"begin") == 0)
            {
                id = BEGIN;

            }else if(strcmp(word,"end") == 0)
            {
                id = END;
                
            }
            
            //printf("\nWord: %s, Id: %d ", word, id);
            newRow = createRow(pos, word, id, NULL);
            isValueExist(symboltable, newRow, a);

            //check if the row exist 
            if(a == false)
            {
                insertRow(symboltable, newRow);

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

        }else if(c == EOF)//end of the file, should end with "end"
        {
            //displayTable(symboltable);
            a = false;
            newRow = createRow(pos, "end", END, NULL);
            isValueExist(symboltable, newRow,a);
            if(a == false)
            {
                printf("Missing identifer 'end' in the file\n");
                exit(0);
            }else{
                displayTable(symboltable);
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
    char *line = malloc(10000);
    //getComment(c,line);
    //checkEnding(c,line);
    //line = NULL;

    int i = 0;
    while(isalpha(c) || c == '_' || isalnum(c))
    {
        word[i++] = c;
        c = fgetc(fp);

        if(c == '(')
        {
            if(isalpha(word[i-1]))
            {
                printf("Syntax Error: missing '=' in line %d.\n", lineNumber);
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

    if(lookahead == '=' || lookahead == ID)
    {
        match(lookahead);
        expression();
        match(';');

    }else if (lookahead != '='){

        printf("Syntax Error: missing '=' in line %d.\n", lineNumber);
        exit(0);
    }
    
}

void checkEnding(char c){
    
    char *checkline = malloc(10000);
    int i = 0;
    while(c != '\n')
    {
        checkline[i++] = c;
        c = fgetc(fp);
    }

    checkline[i] = '\0';
    ungetc(c,fp);

    if(checkline[i-1] != ';' && checkline[i-1] != 'n' && checkline[i-1] != 'd' && checkline[0] != '~')
    {
        
        printf("Syntax Error: missing ';' in line %d.\n", lineNumber);
        exit(0);
        
    }
    
    checkline = NULL;
   
}




