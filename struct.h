/*
Parikh Shivam
ICSI 402
Assignment 3
UNIX ID: sp191221
*/


struct dataBase{
  char relationName[RELATTRINOEXT]; // holds relation name
  char attributeName[RELATTRINOEXT]; // holds attribute name
  char type[STRUCTTYPESIZE]; // holds type I or S
  int numAttributes; //holds number of attributes
  int attriSize; // holds attribute Size in bytes
  };
        
struct duplicateString{ 
  char *duplicate; // holds only character
  };
        
        
        