# ICSI402_p3
Creates Relational DB and API functions to access DB

This is the third project for CSI 402. The test cases are provided thanks to proffesor Ravi. This program will create a relational database from the provided schema file. It can be run by using providing it the name of a config file then the name of the query file. The config file must contains how many databases to be created as well as the names of the databses. These names are then used to open the relevent files with the actual schema and data information. The schema file must have an ending of .sch and the data file must contain a .dat ending. The query file must contain the command to run followed by the required attributes. The provided example files show how the files are named as well as how to format it. Once the database is created from the provided files the queries are run against it and the output is shown to the screen, the provided example output file shows for the sample files. The following commands are usable with this program:
nattr database_name   - Prints how many attributes there are in the given database
tuplen database_name  - Prints how many entries there are in the given database
infattr database_name attribute_name  - prints the type of attribute as well as the maximum length of any values for the attribute
count database_name -  prints how many entries there is under the given attribute.
Project database_name attribute_name  - prints all non duplicate entries for the given attribute, not that my implementation does not filter duplicates.
select - this function was meant to do the same functionality as project but with additional filtering, however it was not implemented within my program. 
 
