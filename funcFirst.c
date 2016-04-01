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
#include "externs.h"



//setup method takes config file name as an extension, and creates a database
void setUpDataList(char *configFileName){
  int loopRun; //limit for outerloop
  int innerLoopRun; //limit for innerloop
  int i; // for outerloop
  int p; // for innerloop
    
    int indexStatic = 0; // index location for implementing an array
    FILE *tempRelationFile; // temporary file pointer
    
  char tempRelation[RELATTRINOEXT]; // temp relation to copy from schema file
  char tempRelationFileName[RELATTRIEXT]; // this will hold the file name with extension
    
    
    char attributeInnerLoop[RELATTRINOEXT]; // temp attribute
    char typeInnerLoop[STRUCTTYPESIZE]; // temp type
    int sizeInnerLoop; //temp size
    
  FILE *configFile = fopen (configFileName, "r" ); // open input file for read
    if (configFile==NULL) { // if the open was unsuccessful
        printf("File Error: Config File can't be opened from funcFirst \n"); exit (1); // print an error and exit
    }
  
  fscanf(configFile, "%d", &loopRun);  // find loop limit
  
  for(i=0; i<loopRun; i++){ // runs for number of relations times
    fscanf(configFile, "%s", tempRelation); // read the name of relation name
      
      strcpy(tempRelationFileName, tempRelation); // copy relation name into bigger space
      strcat(tempRelationFileName, ".sch"); // put file extension at the end
      
      tempRelationFile = fopen (tempRelationFileName, "r" ); // open input file for read
      if (tempRelationFile==NULL) { // if the open was unsuccessful
          printf("\n\n\n");
          printf("File Error: Schema can't be opened from setup function \n\n\n"); exit (1); // print an error and exit
      }

      fscanf(tempRelationFile, "%d", &innerLoopRun); // read the first int from schema file which is number of attributes
      
      for(p = 0; p < innerLoopRun; p++){
          strcpy(storedArray[indexStatic].relationName, tempRelation); // relation name
          
          storedArray[indexStatic].numAttributes = innerLoopRun; // number of attributes for first function
          
          fscanf(tempRelationFile, "%s %s %d", attributeInnerLoop, typeInnerLoop, &sizeInnerLoop); // stores attribute name, type, attribute size in bytes
          
          strcpy(storedArray[indexStatic].attributeName, attributeInnerLoop); //copy onto struct database
          strcpy(storedArray[indexStatic].type, typeInnerLoop); // copy onto struct database
          storedArray[indexStatic].attriSize = sizeInnerLoop; // copy onto struct database
          
          indexStatic++; // increment the array location
      } // inner for loop ends
      
  } // outer for loop ends
    

    /*
    for(i = 0; i < 100; i++){
        printf("Array Data Base: %s %s %d \n",storedArray[i].attributeName,storedArray[i].type, storedArray[i].attriSize);
        printf("relation and number of attri: %s %d \n", storedArray[i].relationName, storedArray[i].numAttributes);
    }
    */
    
}  

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// nattr method takes relation as a parameter
void nattr(char *relation){
    int index = 0; // index location for an array of database
    int numAttri = 0; // this is the output, holds number of attributes

    //while index is less than arraysize 100, keep running
    // and if the relation name matches, copy the number attribute
    while(index < ARRAYSIZE){
        if(strcmp(storedArray[index].relationName, relation) == 0){
            numAttri = storedArray[index].numAttributes;
        }
        
        index++; // index incrementer
    }
    
    // check whether there the relation exists
    // there could between 1 to 10 relation ship size
    if(numAttri == 0){ // if it's zero then it doesn't exist
        printf("\n\n\n");
        printf("ERROR: Invalid relation ---- %s\n\n\n", relation); // error message saying relation doesn't exist
    }
    else{ // print the number of attributes
        printf("\n\n\n");
        printf("The size is: %d\n\n\n", numAttri); // print the number of attributes
    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this function will take relation name as a parameter
int tuplen(char *relation){
    int keepSearch = 0; // indicates to keep searching
    int loopStart; // loop starting index
    int length = 0; // holds the length
    int i = 0; // loop incrementer
    int p = 0; // loop incrementer
    
    //go through the array and find out if it matches with relation name
    //if it does then get the number of attributes and loop that many times to throug the array
    //if the length is still 0 then error will print
    //according to that
    while(i < ARRAYSIZE){ // starts from 0 run until 100
        if(strcmp(storedArray[i].relationName, relation)==0 && keepSearch==0){
            // if it has maching relaion and attribute
            keepSearch = 1; // we dont't need to keep searching
            
            // make that location your inner loop starting index
            loopStart = storedArray[i].numAttributes;
            
            // run until the number of attributes times and sum all the attribute size
            for(p=i; p < i+loopStart; p++){ // loop will run until ur index location+number of attributes
                length += storedArray[p].attriSize; // sum attribute size
            }
        }
        i++; // increment
    }
    return length; // return the length
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this method takes relation name and attribute name
void infattr(char *relation, char *attribute){
    int matchFound = 0; // match found checker
    char type[STRUCTTYPESIZE]; // type is I or S
    int sizeInBytes = 0; // holds size in bytes
    
    int relationCheck = 0; // relation checker
    int attributeCheck = 0; // relation checker
    
    int i; // for loop counter
    
    for(i = 0; i < ARRAYSIZE; i++){ // run through the array and find if relation and attributes matches for same node
        if(strcmp(storedArray[i].relationName, relation) == 0
           && strcmp(storedArray[i].attributeName, attribute) == 0){ // if there is a match
            matchFound = 1; // set match match found to 1
            strcpy(type, storedArray[i].type); // copy type from array onto type I or S
            sizeInBytes = storedArray[i].attriSize; // copies the size of the attribute
        }
        else{ // if the relation name and attribute didn't match find what matches
            if(strcmp(storedArray[i].relationName, relation) == 0){ // if relation matches
                relationCheck = 1; // relation check to 1
            }
            if(strcmp(storedArray[i].attributeName, attribute) == 0){ // if attribute matches
                attributeCheck = 1; // attribute check to 1
            }
        }
    }
    
    if(matchFound == 0){ // if match failed then print appropriate error
        if(relationCheck == 0){ // if relation didn't match
            printf("\n\n\n"); // new lines
            printf("INFATTR ERROR: Invalid Relation ---- %s\n\n\n", relation); // print error saying invalid relation
        }
        if(attributeCheck == 0){ // if attribute didn't match
            printf("\n\n\n"); // new lines
            printf("INFATTR ERROR: Invalid Attribute ---- %s\n\n\n", attribute); // print error saying invalid attribute
        }
    }
    else{ // if there was full match
        printf("\n\n\n"); // new lines
        printf("Attribute Type: %s\n", type); // print attribute type
        printf("Attribute Length: %d\n\n\n", sizeInBytes); // print length in bytes
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this method takes relation name and returns count
int count(char *relation){
    FILE *relationDat;
    long size; // size will be stored
    int i; // loop counter
    int relationCheck = 0; // relation check will be 1 if there is relation match
    
    char tempRelationWithExt[RELATTRIEXT]; // temp relation name with bigger space to hold extension
    
    strcpy(tempRelationWithExt, relation); // string copy relation onto bigger space
    
    //printf("temp print from count: %s\n", tempRelationWithExt);
    
    strcat(tempRelationWithExt, ".dat"); // concatinate .dat
    
    //printf("temp print from count: %s\n", tempRelationWithExt);
    
    for(i = 0; i < ARRAYSIZE; i++){ // run loop through the array
        
        if(strcmp(storedArray[i].relationName, relation) == 0){ // if there is such relation then
            relationCheck = 1; // set relation check to 1
        }
        
    }
    
    if(relationCheck == 1){ // if the relation exists
    
    relationDat = fopen (tempRelationWithExt,"r"); // open file
    
    if (relationDat==NULL){ // file is null
        printf("Error COUNT: opening file \n"); // print an error
        exit(1); //exit the program
    }
    else
    {
        fseek (relationDat, 0, SEEK_END); // fseek till end
        size=ftell (relationDat); // finds the size for whole file
        fclose (relationDat); // close data file
        //printf ("Counts: %ld\n\n\n",size/(tuplen(relation))); // devide size by tuplen and print it
        return size/(tuplen(relation)); // return count
    }
    }
    else{// the relation wasn't found
        //printf("ERROR COUNT: Invalid Relation ---- %s\n\n\n", relation); // print error
        return 0; // return zero
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this method takes relation name and attribute name
void project(char *relation, char *attribute){
    
    
    int matchFound = 0; // match found checker

    int sizeInBytes = 0; // holds size in bytes
    
    int relationCheck = 0; // relation checker
    int attributeCheck = 0; // relation checker
    
    int i; // for loop counter
    
    
    int p; // loop counter
    int q; // loop counter
    int w = 0; // loop counter
    
    int d;  // loop counter
    
    int doNotPut = 0; // do not put checker
    
    int duplicate = 0; // duplicate array counter
    
    int tempColumnNum = 0; // holds temporary column number
    int columnNum = 0; // counts number of columns for the given attribute
    int tempRange; // gives the size for inner loop
    int loopStop = 0; // indicates to stop loop
    
    int tempNumBytesBefore = 0; //this holds the bytes to skip before reading attribute temporarily
    
    int numBytesBefore = 0; // number of bytes to skip bytes before you read appropriate attribute
    
    int numBytesAfter = 0; // number of bytes to skip bytes after you read appropriate attribute
    
    int readBytes; //number of bytes to be read in for specific attribute
    
    char relationFileName[RELATTRIEXT]; // file name with .dat extension size 20
    
    char buffer[tuplen(relation)+1]; //buffer size for reading string
    
    int intBuffer = 0; // holds integer value when reading
    
    char type[STRUCTTYPESIZE]; // type holds I or S
    
    FILE *relationFile; // file pointer
    /////////////////////////////////////
    // this will check is there a match
    
    for(i = 0; i < ARRAYSIZE; i++){ // run through the array and find if relation and attributes matches for same node
        if(strcmp(storedArray[i].relationName, relation) == 0
           && strcmp(storedArray[i].attributeName, attribute) == 0){ // if there is a match
            matchFound = 1; // set match match found to 1
        }
        else{ // if the relation name and attribute didn't match find what matches
            if(strcmp(storedArray[i].relationName, relation) == 0){ // if relation matches
                relationCheck = 1; // relation check to 1
            }
            if(strcmp(storedArray[i].attributeName, attribute) == 0){ // if attribute matches
                attributeCheck = 1; // attribute check to 1
            }
        } // else ends
    } // for loop ends
    
    //////////////////////////////////////
    // match found is done.
    
    if(matchFound == 0){ // if match failed then print appropriate error
        if(relationCheck == 0){ // if relation didn't match
            printf("\n\n\n"); // new lines
            printf("PROJECT ERROR: Invalid Relation ---- %s\n\n\n", relation); // print error saying invalid relation
        }
        if(attributeCheck == 0){ // if attribute didn't match
            printf("\n\n\n"); // new lines
            printf("PROJECT ERROR: Invalid Attribute ---- %s\n\n\n", attribute); // print error saying invalid attribute
        }
    }
    else{ // if there was full match
        
        for(p = 0; p < ARRAYSIZE; p++){ // run through the array
            
            // if the relation name matches that means we need to find attributes from that point
            if(strcmp(storedArray[p].relationName, relation) == 0 && loopStop==0){
                
                //tempNumBytesBefore += storedArray[p].attriSize;
                
                //printf("tempNumBytesBefore: %d\n", tempNumBytesBefore);
                //if(loopStop == 0){
                    //numBytesBefore = tempNumBytesBefore;
                    //printf("numBytesBefore %d\n", numBytesBefore);
                tempRange = storedArray[p].numAttributes; // copy number of attributes as your inner for loop limit
                loopStop = 1; // there can be only one relation so we don't need to check again for relation match
                
                    for(q = p; q < p+tempRange; q++){ // run the inner loop number of attributes + starting index times
                    tempNumBytesBefore += storedArray[q].attriSize; //keep adding bytes for to skip before
                                                
                    //printf("p: %d\n", p);
                    //printf("q: %d\n", q);
                    //printf("tempRange %d\n", tempRange);
                    //printf("p+tempRange: %d\n", p+tempRange);
                    //printf("tempColumnNum %d\n", tempColumnNum);
                    //printf("columnNum %d\n", columnNum);
                    tempColumnNum ++; // increment the number of column
                    
                    // when we find attribute match copy temp column counter onto column count
                    // because temp will continue to change, but we need the very first one
                    
                    if(strcmp(storedArray[q].attributeName, attribute) == 0){
                        readBytes = storedArray[q].attriSize; //size of the attribute
                        strcpy(type,storedArray[q].type); //copy type from array
                        numBytesAfter = tuplen(relation) - tempNumBytesBefore; //computes the bytes to skip before
                        numBytesBefore = tempNumBytesBefore - storedArray[q].attriSize; //compute bytes to skip after
                        //printf("numBytesBefore %d\n", numBytesBefore);
                        //printf("numBytesAfter %d\n", numBytesAfter);
                        columnNum = tempColumnNum; // copy onto column number
                    }
                
                }
            }
        }
        
        //printf("Project Found match: %s %s %d \n\n\n", relation, attribute, columnNum);
        
        
        ////////////////////////////////////////
        //    start to deal with .dat file    //
        ////////////////////////////////////////
        
        strcpy(relationFileName, relation); // copy string to bigger place
        
        strcat(relationFileName, ".dat"); // concatinate with .dat extension
        
        relationFile = fopen(relationFileName, "r"); // open .dat file
        
   
        if(relationFile == NULL){ // if file couldn't open
            printf("ERROR: RELATION file can't be opened from PROJECT Method \n"); // print an error
            exit(1); // exit the program 
        }
        
        
        // run loop for number of tuples
        
        for(w = 0; w < count(relation); w++){
            
            fseek(relationFile, (long)numBytesBefore, SEEK_CUR); // skip the bytes before
            
            if(strcmp(type, "I") == 0){ // if the attribute is I type
                
                fread (&intBuffer, sizeof(int), 1, relationFile); //read the integer into buffer
                
                fflush(stdout); //  fflush
                printf("printing number: %d\n",intBuffer); //print an integer
                fflush(stdout); // fflush
            }
            else{ // this is S type
                fread (buffer, readBytes, 1, relationFile); //read the string
                
                printf("printing character: %s\n", buffer); //print the string
            }
            fseek(relationFile, (long)numBytesAfter, SEEK_CUR); //skeep bytes after you read
        }
        
        /*
        for(d = 0; d < count(relation); d++){
            printf("%s\n", duplicateArray[d].duplicate);
        }
        */
        //
        
        
        
    } //else ends
    
    
    
    
    
}


// this method takes relarion, attribute, relop, and value as a parameter
void select(char *relation, char *attribute, char *relop, char *value){
    
    char type[STRUCTTYPESIZE]; // type holds I or S
    int i; // loop incrementer
    int matchFound = 0; //change to 1 if match found
    int relationCheck = 0; //change to 1 if relation found
    int attributeCheck = 0; //change to 1 if attribute found for the relation
    int isString = 0; // this will set to 1 if it's string
    
    int foundPrint = 0; // this will set to 1 when we find tupel to print
    
    char *tokValue; //after token value

    char relationFileName[RELATTRIEXT]; //bigger space for filename
    
    char *compareString; // compares this string with input value
    
    int compareInt; // compares this int with input value
    
    int tupleLength; // holds tuple length
    
    FILE *relationFile; // .dat file pointer
    
    char buffer[tuplen(relation)]; //buffer to hold fread
    
    
    if(isdigit(value[0]) == 0){
        isString = 1;
    }
    
    tokValue = strtok(value, "\""); // tokenises it
    
    
    for(i = 0; i < ARRAYSIZE; i++){ // run through the array and find if relation and attributes matches for same node
        if(strcmp(storedArray[i].relationName, relation) == 0
           && strcmp(storedArray[i].attributeName, attribute) == 0){ // if there is a match
            strcpy(type, storedArray[i].type); // copy type
            matchFound = 1; // set match match found to 1
        }
        else{ // if the relation name and attribute didn't match find what matches
            if(strcmp(storedArray[i].relationName, relation) == 0){ // if relation matches
                relationCheck = 1; // relation check to 1
            }
            if(strcmp(storedArray[i].attributeName, attribute) == 0){ // if attribute matches
                attributeCheck = 1; // attribute check to 1
            }
        } // else ends
    } // for loop ends
     
    //////////////////////////////////////
    // match found is done.
    
    if(matchFound == 0){ // if match failed then print appropriate error
        if(relationCheck == 0){ // if relation didn't match
            printf("\n\n\n"); // new lines
            printf("SELECT ERROR: Invalid Relation ---- %s\n\n\n", 
relation); // print error saying invalid relation
        }
        if(attributeCheck == 0){ // if attribute didn't match
            printf("\n\n\n"); // new lines
            printf("SELECT ERROR: Invalid Attribute ---- %s\n\n\n", 
attribute); // print error saying invalid attribute
        }
    }
    else{ // We know there was full match, check if relop matches with the value
        
        if(strcmp(type, "S")==0){ // if type is string
        if(isString == 1 && strcmp(type, "S")==0){ // it must be string and type must be S
            if(strcmp(relop, "==") || strcmp(relop, "!=")){ // if can have either one of the relop
           // printf("it is string and data type is string \n\n\n");
                //// PASSED ALL CHECK FIND AND PRINT THE TUPEL
                
                //////////////////////////////////////////////////
                //////////////////////////////////////////////////
                
                strcpy(relationFileName, relation); // copy file name into bigger space
                strcat(relationFileName, ".dat"); // attach extension
                
                //relationFile = fopen(relationFileName, "r"); // open .dat file
                
                relationFile = fopen("Students.dat", "r"); // open .dat file
                if(relationFile == NULL){ // if file couldn't open
                    printf("ERROR: RELATION file can't be opened from PROJECT Method \n"); // print an error
                    exit(1); // exit the program
                }
                
                
                
                //////////////////////////////////////////////////
            }
            else{
                printf("Wrong type of relop \n");
            }
        }
        else{
            printf("Wrong type of value for attribute --- %s\n", attribute);
        }
        }
        else{
            //printf("TYPE is INT \n");
            if(isString == 0 && strcmp(type, "I")==0){ // must not be string and must be int
                if(strcmp(relop, "<=")==0
                   || strcmp(relop, ">=")==0
                   || strcmp(relop, "<")==0
                   ||strcmp(relop, ">")==0
                   || strcmp(relop, "==")==0
                   ||strcmp(relop, "!=")==0){ //this can have any relop
                    //printf("it is int and data type is int \n\n\n");
                    //// PASSED ALL CHECK FIND AND PRINT THE TUPEL
                    
                    
                    
                }
                else{
                    printf("Wrong type of relop \n"); // relop is wrong if this can't run in the if statement
                }
            }
            else{ // something is wrong with attribute
                printf("Wrong type of value for attribute --- %s\n", attribute);
            }
        }
    }// big else ends
}













        
