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

void runProgram(char *filename)
{
    /*
    * create table and open file
    * */
    symboltable = createTable(NULL, NULL,0);
    fp = fopen(filename, "r");
    
    while(fp != NULL)
    {
        lexanAnalyzer();
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

            //int id = ID;
            //printf("%d word: %s\n", pos,word);

            if(pos == 0){
                if(strcmp(word,"begin") != 0)
                {
                    printf("ERROR! Missing 'begin' in you code!\n");
                    exit(0);
                } 
               
            }

            if(strcmp(word,"begin") == 0)
            {
                //id = BEGIN;
                newRow = createRow(pos,"begin",BEGIN,NULL);
                insertRow(symboltable,newRow);
                pos++;

            }else if(strcmp(word,"end") == 0)
            {
                //id = END;
                newRow = createRow(pos,"end",END,NULL);
                insertRow(symboltable,newRow);
                pos++;

            }

            if(strcmp(word,"int")==0){

                insertValue(c);

            }else if(!isValueExist(symboltable, word))
            {
                printf("ERROR! Value '%s' haven not been decleared yet!\n",word);
                exit(0);   
            }else if(strcmp(word,"begin"))
            {
                return BEGIN;

            }else if(strcmp(word,"end"))
            {
                return END;
            }

            word = NULL;

            free(word);
            return ID;

        }else if(c == EOF) //end of the file, should end with "end"
        {
            if(!isValueExist(symboltable, "end"))
            {
                printf("Missing identifer 'end' in the file\n");
                exit(0);
            }
            
        }else if(c == '='){
            c = fgetc(fp);
            output(c);

        }else{
           assignsign(c);
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

        if(c == '_')
        {
            if(word[i-1] == '_')
            {
                printf("Invalid Identifer in line %d.\n", lineNumber);
                exit(0);
            }
        }
    }

    //check the end of the word
    if(!isalnum(word[i-1]) && !isalpha(word[i]))
    {
        printf("Invalid Identifer '%s' in line %d.\n", word, lineNumber);
        exit(0);
    }

    if(strcmp(word, "end") == 0)
    {
        newRow = createRow(pos, "end", END, NULL);
        insertRow(symboltable, newRow);

        if(numberofleft != numberofright)
        {
            printf("Syntax Error\n");
            exit(0);
            
        }else{
             //displayTable(symboltable);
             exit(0);
        }
    }

    word[i] = '\0';
    ungetc(c,fp);
    
    return word;
}
/*
* get value and insert to table
*/
void insertValue(char c){

    char *w = malloc(10000);
    int i = 0;
    c = fgetc(fp);
    while(c != ';' )
    { 
        if(c != ' '){
            w[i++] = c;
        }

        c = fgetc(fp);
    }
    
    word[i] = '\0';
    ungetc(c,fp);

    char spliter = ',';
    char *token = strtok(w,&spliter);

    // createRow(int pos, char *value, int type,char *decleartype, Row next)
    while(token != NULL){
        
        newRow = createRow(pos,token, ID, NULL);

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
int match(int t)
{
    if(lookahead == t)
    {
        lookahead = lexanAnalyzer();
        printf("%d\n", lexanAnalyzer());
        return lookahead;
        
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

    //lookahead = ID;

    printf("%d\n", lookahead);

    if(lookahead == '=' || lookahead == ID)
    {
        match(lookahead);
        expression();
        match(';');

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

void output(char c){

    char *sentence  = malloc(10000);
    int i = 0;

    while( c != '\n'){
        c = fgetc(fp);
        if((c != ' ')&& (c != ';'))
            sentence[i++] = c;
    }

    sentence[i] = '\0';
    ungetc(c,fp);  

    //printf("%s\n",sentence);
    compiling(sentence);

}

void compiling(char *sentence){

    char previouschar = '\0';
    char currentchar = '\0';
    char lastchar = '\0';
    char* sign = malloc(40);
    int j = 0;
    int k = 0;
    int o = 0;

    char *rzero= malloc(10);
    char *rtwo = malloc(10);

    char *rthree = malloc(10);

    char *charzero= malloc(10);
    char *charone = malloc(10);
 
    for(int i = 1; sentence[i] !='\n'; i++){
        currentchar = sentence[i];
        previouschar = sentence[i-1];

        if(currentchar == '('){
            lastchar = previouschar;
        }else{
            if(sentence[i] != '(' && sentence[i] != ')' && sentence[i] != '_'){
                if(!isdigit(sentence[i])){
                    if(!isalpha(sentence[i])){
                        sign[j++] = sentence[i];
                    }
                }     
            }
        }

        //assign R0
        if((isdigit(sentence[i])) || (isalpha(sentence[i])) || (sentence[i] == '_')){
            rzero[k++] = sentence[i];
        }else{
            rzero[k++] = '~';
        }

    }

    //printf("%s\n", sign);
    //printf("%s\n", rzero);

    char spliter = '~';
    char *token = strtok(rzero,&spliter);

    int t = 0;
    while(token != NULL){
        
        if(t == 0){
            printf("R0 = %s\n",token);
            strcpy(charzero,token);

        }else if(t == 1)
        {
           printf("R1 = %s\n",token);
           strcpy(charone,token);
        }

        if(t == 2){
            
            printf("R0 = R0 %c R1\n",sign[0]);
            printf("R2 = %s\n",token);
            strcpy(rtwo,token);
        }

        if(t == 3){
            printf("R0 = %s\n", token);
            strcpy(rthree, token);

        }
        
        t++;
        //printf("token: %s\n",token);
        
        token = strtok(NULL,&spliter);
    }

    if(t == 2){
        printf("R0 = R0 %s R1\n",sign);
        printf("******[%s,%s,%c]******\n",charzero,charone,sign[0]);
    }

    //printf("total t: %d \n", t);

    if(t == 3){
        printf("R2 = %s\n", rtwo);
        printf("R1 = R1 %c R2\n",sign[1]);
        printf("******[%s,%s,%c, %s, %c]******\n",charzero,charone,sign[0], rtwo, sign[1]);
    }

    if(t == 4){

        printf("R1 = R0 %c R1\n", sign[1]);
        printf("R2 = R1 %c R2\n", sign[2]);
        printf("******[%s,%s,%c,%s,%c, %s,%c]******\n",charzero,charone,sign[0], rtwo, sign[1], rthree, sign[2]);
    }
    
    
}





