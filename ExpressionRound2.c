/**
* ExpressionRound2.c
* This class contains the data structure and all of its methods that allow you
* to create and manipulate it.
* Class by: Lia Chrysanthopoulos
* Project 1
* Date: 10/27/2019
* Professor Liew
* CS 203
*
**/

#include "ExpressionRound2.h"
//Global Variables
int openPar; 
int closedPar; 
int totalIndex; 
bool reset; 
bool resetOnce;


/**
* This method initally takes in the string the user puts it in and evaulates 
* whether or not the expression is a single number or a math expresssion 
* @Param - Exp* e - the expression created in main
* @Param - char* arr - The string from the user 
* @return- void 
*/
void create(Exp *e, char* arr){
    resetOnce= 1; 
    //single integer 
    if((strlen(arr) == 2 && arr[0] != ')') ){ //must be 2 because stdin include '/0'

        e->symbol = (char*)malloc(sizeof(char));
        char c = arr[0]; 
        e->symbol[0] = c;  // doesnt have a first no brackets
        
        e->first = NULL; 
        e->rest = NULL; 
    }
    
    else{
        createRecursion(arr, e);
    }
}

/**
* This method is the first of the recursion methods. It takes in an expression with
* parenthesis and breaks in down into levels for the data structure. 
* It removes the begingign parenthesis and symbol for the expression. 
* @ Param - char* currExpresssion - the expression containing parenthesis
* @ Param - struct Exp *e - the current "expression" you are at in the data strcuture
* @ Return- void
*/
void createRecursion(char* currExp, struct Exp *e){
    reset= 1; 
    int length = strlen(currExp);

    if(strlen(currExp) == 1){
        return;
    } 
    else{
       //if first charater is a (
     if(currExp[0] == '('){
        openPar = openPar+1;

        Exp *first = (Exp*)malloc(sizeof(Exp)); //node for fist exp 
        e->first = first; 
        Exp *rest = (Exp*)malloc(sizeof(Exp)); //node for rest 
        e->rest = rest; 

        //allocate space for symbol
        first->symbol = malloc(sizeof(char)*10); 
        char c = currExp[1]; 
        first->symbol[0] = c; 
        
        char *newExp = (char*)malloc(20*sizeof(char));

        //cannot get rid of space beofre number- may be a new (
        copyData(currExp, newExp, 2, 0, strlen(currExp)-2); 

        //if first character is a space get rid of it 
        if(newExp[0] == ' '){
             char *newnew = (char*)malloc(20*sizeof(char));
            copyData(newExp, newnew, 1, 0, strlen(currExp)-1); 
            createRecursion2(newnew, rest);
        }
        else{
            createRecursion2(newExp, rest);
        }
      }
    }
    return; 

}

/**
* This is the second of the third of the create methods that takes in strings that contain the
* entire rest to an operator. It breaks it down into firsts and rests
* @Param- char* currExp -the current string at the current expression
* @ Param - Exp* e- "the rest" of the expression 
* @Return - void 
*/
void createRecursion2(char* currExp, Exp* e){
    
    //numbers with no parenthesis
    if(currExp[0] != 0){

        if(resetOnce == 1){ //take away last parenthesis for first oen only
        closedPar--;
        char *newExp = (char*)malloc(20*sizeof(char));
        copyData(currExp, newExp, 0, 0, strlen(currExp)-2); 
        currExp = newExp;
        resetOnce = 0; 
        reset = 0; 
        } 
        else if(reset==1){  //take away parnthesis 
            closedPar--;
            char *newExp = (char*)malloc(20*sizeof(char));
            copyData(currExp, newExp, 0, 0, strlen(currExp)-1); 
            currExp = newExp;
            reset = 0; 
        }
        if( currExp[0] == ' '){  //if theres a space in the begining 
            char *newExp = (char*)malloc(20*sizeof(char));
            copyData(currExp, newExp, 1, 0, strlen(currExp)-1); 
            currExp = newExp;
        }

        if(currExp[0] != '(' ){

            Exp *first = (Exp*)malloc(sizeof(Exp));
            e->first = first; 
            first->symbol = malloc(sizeof(char)*10); 
        
            //if you have 1 number 
            if(currExp[1] == ' ' || currExp[1] == 0){

            char c = currExp[0]; 
            first->symbol[0] = c;
            char *newExp = (char*)malloc(20*sizeof(char));
            copyData(currExp, newExp, 2, 0, strlen(currExp)-2);
            
            Exp *rest = (Exp*)malloc(sizeof(Exp)); 
            if(strlen(newExp) == 0){
                e->rest = NULL;  
                rest = NULL;
                return;
            }else{
                e->rest = rest; 
            }

            createRecursion2(newExp, rest);
        }
                
            //if you have multiple numbers
            else if(currExp[1] != ' ' && strlen(currExp) != 0 && currExp[0] != '(' ){
               if( currExp[0] == ' '){  //if theres a space in the begining 
                    char *newExp = (char*)malloc(20*sizeof(char));
                    copyData(currExp, newExp, 1, 0, strlen(currExp)-1); 
                    currExp = newExp;

                }
                int len; 
                char* numbs = "1234567890";
                char* temp = malloc(sizeof(char)*10); 
                //copy whole number into a new string called temp
                len = strspn(currExp, numbs);  
                copyData(currExp, temp, 0, 0, len);
            
                copyData(temp, first->symbol, 0, 0, len);
                first->symbol = first->symbol; 

                Exp *rest = (Exp*)malloc(sizeof(Exp));
                e->rest = rest; 
            
                char *newExp = (char*)malloc(20*sizeof(char));
                copyData(currExp, newExp, len+1, 0, strlen(currExp)-(len));

                //rest= NULL;
                if(strlen(newExp) == 0){
                    e->rest = NULL; 
                    rest = NULL;
                    return;
                }
            createRecursion2(newExp, rest);
            
        }
    
    }
    //pareenthesis expressions
    else if(currExp[0]=='('){
        int len; 
        char* between = ")";
        char* temp = malloc(sizeof(char)*10); 
       
        len = strcspn(currExp, between); //get number of spots before ) 
        if(currExp[len+1] == ')'){
            len = len +1; 
        }       
        copyData(currExp, temp, 0, 0, (len+1));  //temp has the new string with ()
        
        char* newExp = malloc(sizeof(char)*10);  //the one that has leftovers 
        copyData(currExp, newExp, len+1, 0, strlen(currExp)- len);

        Exp *first = (Exp*)malloc(sizeof(Exp)); //create a first for parentheiss expression
        e->first = first; 
        createRecursion(temp,  first);      //call first recursion method with new first BEFORE you create the rest

        Exp *rest = (Exp*)malloc(sizeof(Exp)); //create rest
        e->rest = rest; 

        if(strlen(newExp) == 0 || newExp[0] == ')'){    //if the newExpression is empty dont call it recursively 
            e->rest = NULL; 
            rest = NULL; 
            return; 
        }else{
            createRecursion2(newExp, rest);
        }
  
       }
    }else{
          return;
    }
    
  
}

 /*
 * By; Professor Chun Wai Liew - THANK YOU!
 * copies a specified number of elements from source to destination, given the starting indices in both
 * @param src - pointer to the array of ints to be copied FROM
 * @param dest - pointer to the array of ints to be copied TO
 * @param s1 - starting index in src array
 * @param s2 - starting index in dest array
 * @param num - number of elements to be copied
 */   
void copyData( char* src, char* dest, int s1, int s2, int num ) {
  for( int i = 0; i < num; i++ )
    dest[s2++] = src[s1++];
}

/**
* This Method prints the expression which is the datastrcutre. 
* @Param - Exp* e- the expression at the "head" of the data strcuture
* @Return - void 
*/
void printExp(Exp* e){  
    char* total = (char*) malloc(60* sizeof(char)); 
    if(e == NULL){
        printf("Expression is NULL");
    }
    if(e->rest == 0){    //just  a symbol  
        printf(e->symbol); 
    }else{
        printf("("); 
        printRest(e); 
        printf(")");
    }
        printf("%s\n", total);

}

/**
* This method is the helper method for the PrintExp
* @Param - Exp* currExp - expression taken in by PrintExp 
* @Return - void 
*/
void printRest(Exp* currExp){
    if(currExp ==0) return; 

    if(currExp->first ==0 && currExp->rest ==0){
        printf("%s", currExp->symbol);
        return; 
    }
    if(currExp->first->first != 0 && currExp->first != 0){
        printf("(");
        printRest(currExp->first); 
        printf(")");
        if(currExp->rest){
            printf(" ");
            printRest(currExp->rest); 
        }
        return; 
    }
    if(currExp->first != 0 && currExp->first->symbol != 0){
        printRest(currExp->first); 

        if(currExp->rest != 0 ){
            printf(" ");
            printRest(currExp->rest); 
        }
    }
}

/**
* This method appends an expression to the current expression in the datastrcuture
* @Param - Exp* e- The expression "head" of the data strcuture
* @Param - Char* arr - The string of the expression beign appended to the structure
*/
void append(Exp* e, char* arr){
    Exp* newRest = (Exp*)malloc(sizeof(Exp)); 
    createRecursion2(arr, newRest);
    Exp* current = e->rest; 
    
    while(current->rest != NULL){
        current = current->rest; 
    }

    current->rest = newRest; 
    printf("\nNew Expression:");
    printExp(e); 

}

/**
* This method prints a subset of the expression using commands 'r' and 'f'
* 'r' = rest of the expressssion 
* 'f' = first part of the expresssion 
* @Param - Exp* e- THe 'head' of the expression data strcuture in main
* @Param - char* c- the string defined in 'r's or 'f's for the located subset
* @return - void
*/
void printSubset(Exp* e, char* c){
    Exp* current = e; 
    int i = 0; 
    while(c[i] == 'r'){
         current = current->rest; 
         i++;

    }
    if(c[i] == 'f'){
        current = current->first; 
    }
    printf("%s", current->symbol); 
}

/**
* This method evaluates the current expression arithmetically
* This method is not functioning properly 
* @Param  - Exp*e - the 'head' expression of the data strcuture 
* @Return - void 
*/
void evaluate(Exp* e){
char* arr= (char*)malloc(60*sizeof(char*)); 
   Exp* current = e; 
   int i = 0;
   int sum = 0; 
   while(e != NULL){
       arr[i] = e->rest->first->symbol;
       if(arr[0] ==  '+'){
            sum+=arr[i+1];
            evaluate(e->rest);
        }
        if(arr[0] == '-'){
            sum-= arr[i+1];
        }
        if(arr[0] == '*'){
            sum= sum*arr[i]; 
        }
       e = e->rest; 
       i++;
   }
   printf("%d", sum);
    
    
}