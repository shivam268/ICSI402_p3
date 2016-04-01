/*
Parikh Shivam
ICSI 402
Assignment 3
UNIX ID: sp191221
*/


void nattr(char *relation); // nattr method
void infattr(char *relation, char *attribute); //infattr method
void setUpDataList(char *configFileName); //sets up the database
int tuplen(char *relation);    //tupel length counter
int count(char *relation); // return number of tuples
void project(char *relation, char *attribute); //projects the column
void select(char *relation, char *attribute, char *relop, char *value); //prints tupels
        
        
        
        
        
        
        
        