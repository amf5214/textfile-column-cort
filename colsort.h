// Written by Austin Fraley
// 02/08/2024
// Series of functions to help sort a file by the nth word

// Function to interpret cli arguments into filepath and nth word args
// Params: argc:int is the number of command line arguements present
// argv:char** is an array of strings provided by the cli
// destNthWord:int* pointer to an int where the nth word int will be stored
// filePath:char* is a pointer to a string that will hold the file path
void getSortArgs(int argc, char** argv, int* destNthWord, char* filePath);

// Function to perform the sort by nth word
// Uses qsort to sort the file therefore requires the compareLines function defined within readfile.h
// Params: file:File* representing a pointer to the File object, nthWord:int representing the nthWord index
// Returns: File representing the sorted file
File sortFileByNthWord(File* file, int nthWord);

// Function to read in a file and perform the sort by nth word
// Uses the stdio FILE object to read in and then switches to File object from readfile.h 
// Params: filePath:char* representing a string with the file path, nthWord:int representing the nthWord index
// Returns: File representing the sorted file
File getFileSortedByNthWord(char* filePath, int nthWord);