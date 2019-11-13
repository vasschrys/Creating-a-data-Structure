/**
* This is the main class. This is were all the fucntion are run from. 
* The user input is put into here and taken care on based on what the user wants the program to do 
* Project by: Lia Chrysanthopoulos
* Project 1
* Date: 10/27/2019
* Professor Liew
* CS 203
*/

#include "main.h"
#include "ExpressionRound2.h"
#include <stdlib.h>
#include <string.h>
#define SIZE 50

int main(){
    char *mystring = (char*)malloc(60*sizeof(char)); 
    char input = '0';
    Exp *e = (Exp*)(malloc(sizeof(Exp))); 

    while( input!= 'q'){
        //fflush(stdin); //not needed ?
        input= getchar(); 
        if(input == 'c'){ //create expression
            printf("Enter Expression:\n");
            fgets(mystring, 100, stdin); 
            fgets(mystring, 100, stdin); 
            create(e, mystring);
        }else if(input== 'p'){ //print expression
            fgets(mystring, 100, stdin); 
            printExp(e); 
        }else if(input == 'a'){ //append to the current structire
            printf("Enter Expression:\n");
            fgets(mystring, 100, stdin); 
            fgets(mystring, 100, stdin); //some reason had to had this twice for it to show up
            append(e, mystring);
        }else if(input == 's'){
            printf("Specify Subset:\n");
            fgets(mystring, 100, stdin); 
            fgets(mystring, 100, stdin); //some reason had to had this twice for it to show up
            printSubset(e, mystring);
            printf("\n");
        }else if(input == 'e'){ //evaluate the expression arithmetically
            printf("Not Available\n");
            //evaluate(e);
        }
        
    }
    free(e);

}
