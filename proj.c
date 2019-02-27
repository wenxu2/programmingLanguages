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
int lineNumber = 1;
Table symboltable;
char *signtable;
Row newRow;
char* word;
char *number;
bool a = false;
int numberofleft = 0;
int numberofright = 0;
int numberofequal = 0;
int numberofclose = 0;
bool is_END_exist = false;
bool is_BEGIN_exist = false;

void runProgram()
{
    /*
    * create table and open file
    * */
    symboltable = createTable(NULL, NULL,0);
    fp = fopen("test.txt", "r");
    
    while(fp != NULL)
    {
        lexanAnalyzer();
        
        if(lexanAnalyzer() == '=')
        {
            assignStmt();
        }

    }

    //close files
    fclose(fp);

    /*
    * free memory
    */
    free(newRow);
    free(symboltable);
    free(signtable);
    free(word);
    free(number);

}

int lexanAnalyzer(){

    while(true)
    {
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
            
            if(strcmp(word,"int") == 0 ){
                c = fgetc(fp);
                insertValue(c);

            }else if(strcmp(word,"begin"))
            {
                is_BEGIN_exist = true;
                return BEGIN;

            }else if(strcmp(word,"end"))
            {
                is_END_exist = true;
                return END;
            }else if(!isValueExist(symboltable, word)){

                printf("Word have not been decleared!\n");
            }

            printf("\n");
            free(word);
            return ID;
            return ID;

        }else if(c == EOF) //end of the file, should end with "end"
        {
            if(!is_END_exist){
                printf("ERROR! Missing identifer 'END' in you code\n");
                exit(0);
            }else{
                displayTable(symboltable);
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
    }

    word[i] = '\0';
    ungetc(c,fp);

    return word;
}

/*
* get value and insert to table
*/
void insertValue(char c){

    char *w = malloc(200);
    int i = 0;
    while( c != ';')
    { 
        w[i++] = c;
        c = fgetc(fp);
    }
    
    //printf("%s\n",w);

    char spliter = ',';
    char *token = strtok(w,&spliter);

    // createRow(int pos, char *value, int type,char *decleartype, Row next)
    while(token != NULL){
        
        newRow = createRow(pos,token, ID,"int",NULL);

        if(!isValueExist(symboltable,token)){
            insertRow(symboltable, newRow);
            pos++;

        }else{
            printf("ERROR! Value '%s' already declear!\n", token);
            exit(0);
        }

        token = strtok(NULL,&spliter);
    }

}

/*
* build number array
*/
void getNumber(char c, char *number)
{
    int i = 0;
    while(isdigit(c) || c == '.')
    {
        
        number[i++] = c;
        c = fgetc(fp);  
    }

    number[i] = '\0';
    ungetc(c,fp);

    if(number[i-1] == '.')
    {
        printf("Invalid number '%s' in line %d.\n",number,lineNumber);
        exit(0);
    }
    
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
        printf("test Syntax Error: check line %d.\n",lineNumber);//need add line number 
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
        printf("factor : Syntax Error: check line %d.\n",lineNumber-1);
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
        
        printf("assign Syntax Error: check line %d.\n",lineNumber-1);
        exit(0);
    }
    
}

/*
* assign signs in the txt files
*/
void assignsign(char ch)
{
    int i =0;
    signtable = malloc(1000);
    if(!isalpha(ch) && !isdigit(ch))
    {
        signtable[i++] = ch;
    }

    int j = 0;
    for(j = 0; j< i; j++)
    {
        if(signtable[j] == '(')
        {
            numberofleft += 1;
        }

        if(signtable[j] == ')')
        {
            numberofright += 1;
        }

        if(signtable[j] == '=')
        {
            numberofequal +=1;
        }

        if(signtable[j] == ';')
        {
            numberofclose += 1;
        }
    }

}





