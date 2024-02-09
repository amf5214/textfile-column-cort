#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Word{
	char* text;
	int length;
} Word;

typedef struct Line{
	Word* words;
	int length;
	char* nthWord;
} Line;

typedef struct File{
	Line* lines;
	int length;
} File;

// Function to create a Word object
// This function copies the string provided so that it is independent
// of the provided pointer and also calculates and stores lenth for you
// Params: initText:char* represents an array of chars/string of text
// Returns: Word type struct
Word createWord(char* initText);

// Function to create a Line object
// Params: initWords:Word* an array of Word objects,
// initLength:int length of the array
// Returns: Line type object
Line createLine(Word* initWords, int initLength);

// Function to create a File object
// Params: initLines:Line* an array of Line ojects,
// initLength: int length of the array
// Returns File object
File createFile(Line* initLines, int initLength);

// Function to print out a Line object
// Iterates through the words array and prints on one line
// Params: line:Line* Line pointer used to access the line properties
void printLine(Line* line);

// Function to print out a File object
// Iterates through the lines array and prints out one at a time using printLine function
// Params: file:File* Line pointer used to access the line properties
void printFile(File* file);

// Function to count the number of words in a line
// Copies the input char array so that the origin is not modified
// Params: lineText:char* line of text
// Returns: int representing the number of words present
int countWords(char* lineText);

// Function to pop last character from a string/char*
// Params: string:char* represents the string to pop from, length:int is the length of the string
// Returns: char* is the pointer to the new string
char* popCharFromString(char* string, int length);

// Function to remove the next line character from the end of a word
// Params: word:Word word to check and remove from
// Returns: Word is the new word object where the \n has been removed 
Word removeNextLine(Word* word);

// Function to count the number of lines in a file
// Params: file:FILE* FILE object pointer from std io library storing a stream of data
// Returns: int representing the number of lines in the file
int countFileLines(FILE* file);

// Function to read in a line and store it into a Line object
// This function copies the input string so that the original is not modified
// Params: lineText:char* string representing the text on the provided line
// Returns: Line object representing the line but is much more interactive
Line readInLine(char* lineText);

// Function to read in a file from a std io library FILE object 
// Params: file:FILE* FILE object pointer from std io library storing a stream of data
// Returns: File struct containing an array of Line objects and a length value
File readInFile(FILE* file);

// Function to assign the nthword attribute of a Line object
// Params: line:Line* line to be updated, nthWord:int index of the nthWord
void assignNthWord(Line* line, int nthWord);

// Function to assign the nthword attribute of all Line objects in a File object
// Params: file:File* file to be updated, nthWord:int index of the nthWord
void assignNthWords(File* file, int nthWord);

// Function to compare lines of a file
// Created with the prototype required by qsort function
// Params: a:const void* is a void pointer to line 1, b:const void* is a void pointer to line 2
// Returns: int representing whether the nth word is equal to, comes before or after
int compareLines(const void * a, const void * b);

// Function to free a file object and all of it's components
// Params: file:File is the file object to be freed
void freeFile(File file);
