/*
Parikh Shivam
ICSI 402
Assignment 3
UNIX ID: sp191221
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>  
#include "constants.h"
  #include "struct.h"
#include "globals.h"
//#include "struct.h"
#include "prototypes.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////
///											    ///
///		              MAIN METHOD STARTS		         ///
///								     			    ///
///////////////////////////////////////////////////////////////


int main(int args, char *argv[])
{
  
    
    /*
     #define RELATTRINOEXT 16
     #define RELATTRIEXT 20
     */
    int loop = 0; // to terminate the loop
    
    FILE *configFile; // file pointer for configaration file
    FILE *queryFile;  // file pointer for query file
    
    char command[QUERYCOMMANDLENGTH]; // to hold command
    char relName[RELATTRINOEXT]; // to hold relation name
    char attName[RELATTRINOEXT]; // to hold attribute name
    char relop[RELOPSIZE]; // to hold relop sign
    char value[VALUESIZE]; // to hold value for select command
    
    char *tokValue;
    
    // ERROR CHECKING FOR COMMAND ENTRY, CONFIG FILE, QUERY FILE //
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(args != COMMANDENTRY){ // if parameter entry is not 3
        printf("Wrong number of parameters \n"); // print error message
        exit(1); // exit the program
    }
    
  
     
      
  //char *configFileName = (char *) malloc(sizeof(argv[ARGONE]));
  //strcpy(configFileName, argv[ARGONE]);
  
  
    configFile = fopen ( argv[ARGONE] , "r" ); // open input file for read
    if (configFile==NULL) { // if the open was unsuccessful
        printf("File Error: Config File can't be opened \n"); exit (1); // print an error and exit

    }
  
    queryFile = fopen ( argv[ARGTWO] , "r" ); // open input file for read
    if (queryFile==NULL) { // if the open was unsuccessful
        printf("File Error: Query File can't be opened \n"); exit (1); // print an error and exit
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  
  //printf("Config File: %s\n", configFileName);
  //printf("argument one: %s\n", argv[ARGONE]);
   setUpDataList(argv[ARGONE]); // calls method with appropriate parameters
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
 
    ////////////////////////////////////////////////////////////
    //    WHILE LOOP TO IDENTIFY COMMAND, AND CALL METHODS    //
    ////////////////////////////////////////////////////////////
    
    // while loop will run through the query file and identify the command
    // it will call appropriate methods
    
    while(loop == 0){ // while we don't reach to quit command
        fscanf(queryFile, "%s", command); // read first word
        
        if(strcmp(command, "nattr") == 0){ // if its nattr
            fscanf(queryFile, "%s", relName); // read relation name
            //printf("nattr is the command \n");
            //printf("relName is: %s\n", relName);
            nattr(relName); // calls method with appropriate parameters
        }
        else if(strcmp(command, "tuplen") == 0){ // if its tuplen
            fscanf(queryFile, "%s", relName); // read relation name
            //printf("tuplen is the command \n");
            //printf("relName is: %s\n", relName);
            //tuplen(relName);
            
            // calls method with appropriate parameters
            if(tuplen(relName) == 0){ // return is 0 then the relation doesn't exist
                printf("\n\n\n"); // new lines
                printf("tuplen ERROR: Invalid relation ---- %s\n\n\n", relName); // print an error message
            }
            else{ // relation exists then print length
            printf("Tuple Length: %d\n", tuplen(relName)); // prints length
            }
        }
        else if(strcmp(command, "infattr") == 0){ // if its infattr
            fscanf(queryFile, "%s", relName); // read relation name
            fscanf(queryFile, "%s", attName); // read attribute name
            //printf("infattr is the command \n");
            //printf("relName is: %s\n", relName);
            //printf("attName is: %s\n", attName);
            infattr(relName, attName); // calls method with appropriate parameters
        }
        else if(strcmp(command, "count") == 0){ // if its count
            fscanf(queryFile, "%s", relName); // read relation name
            //printf("count is the command \n");
            //printf("relName is: %s\n", relName);
            //count(relName);
          //printf ("Counts: %ld\n\n\n",count(relName));
                  // calls method with appropriate parameters
            if(count(relName) == 0){ // return is 0 then the relation doesn't exist
                printf("\n\n\n"); // new lines
                printf("count ERROR: Invalid relation ---- %s\n\n\n", relName); // print an error message
            }
            else{ // relation exists then print length
            printf("count: %d\n\n", count(relName)); // prints length
            }
        }
        else if(strcmp(command, "project") == 0){ // if its project
            fscanf(queryFile, "%s", relName); // read relation name
            fscanf(queryFile, "%s", attName); // read attribute name
            //printf("project is the command \n");
            //printf("relName is: %s\n", relName);
            //printf("attName is: %s\n", attName);
            project(relName, attName); // calls method with appropriate parameters
        }
        else if(strcmp(command, "select") == 0){ // if its select
            fscanf(queryFile, "%s", relName); // read relation name
            fscanf(queryFile, "%s", attName); // read attribute name
            fscanf(queryFile, "%s", relop); // read relop sign
            fscanf(queryFile, "%s", value); // read value
            //printf("select is the command \n");
            //printf("relName is: %s\n", relName);
            //printf("attName is: %s\n", attName);
            //printf("relop is: %s\n", relop);
            //printf("value is: %s\n", value);
            tokValue = strtok(value, "\""); // tokenises it
            //printf("value is: %s\n", tokValue);
            
            
            select(relName, attName, relop, value); // calls method with appropriate parameters
            
            
        }
        else if(strcmp(command, "quit") == 0){ // if its quit command
            printf("quit is the command \n");
            loop = 1; // change loop to 1, to stop the while loop
        }
        else{// command can't be identified
            printf("Command can't be identified \n\n\n"); // print message saying the command can't be identified
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    return 1; // ends the main method
}
///////////////////////////////////////////////////////////////
///									     		   ///
///			     MAIN METHOD ENDS	                  ///
///								     			  ///
/////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        