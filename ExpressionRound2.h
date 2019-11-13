/**
* ExpressionRound2.h
* This is the header file for the expression data structure.
* All method definitions are in this file
* Class by: Lia Chrysanthopoulos
* Project 1
* Date: 10/27/2019
* Professor Liew
* CS 203
*/

#ifndef ExpressionRound2_h
#define ExpressionRound2_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Struct for expressions
typedef struct Exp{
    char* symbol; 
    struct Exp* first; 
    struct Exp* rest; 
}Exp; 

//methods for data strcuture
extern void create(Exp* ,char* arr);
extern void createRecursion(char*, struct Exp*);
extern void createRecursion2(char *, struct Exp*); 
extern void printExp(Exp* ptr);
extern void printRest(Exp* ptr);
extern void evaluate(Exp* e); 
extern void append(Exp* e, char* arr); 
extern void printSubset(Exp* e, char* c);

//method taken from Professor Liew in order to copy data from one char* into another char*
extern void copyData( char* src, char* dest, int s1, int s2, int num );

#endif /* Expression_h */
