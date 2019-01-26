/*
File name: proj.c
Author: Wenwen Xu
Project: Project 1
Description: 
*/
#include <stdio.h>
#include "proj.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void lexanAnalyzer(){
    
    FILE *fp;
    char c;
    fp = fopen("test.txt", "r");

    if(fp == NULL){

        printf("ERROR!\n");

    }

    while( (c = getc(fp) ) != EOF)
    {
        //printf("%c", c);

        if(isCharNull(c))
        {
            //printf("%c - this is a space\n", c);
            //do nothing
        }

        if(isCharDigit(c))
        {
            
        }

        
    }
        
     
    fclose(fp);

}

bool isCharNull(char c){

    if(c == ' ')
    {
        return true;
    }

    return false;
}

bool isCharDigit(char c){

    int num[10] = {0,1,2,3,4,5,6,7,8,9};

    for(int i = 0; i < sizeof(num); i++)
    {
        if(c == num[i])
        {
            return true;
        }
    }

    return false;

}




