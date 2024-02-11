// Written by Austin Fraley
// 02/09/2024
// Series of functions to handle errors programatically

#include "errorhandling.h"

// Function to print error for not enough arguements provided to cli
void errorNotEnoughArguements() {
	fprintf(stderr, "Error: Not enough arguements provided. Requires at least 1 argument, \
file path with optional arguement -<number> representing the word index to sort by.\n");
}

// Function to print error for invalid file path provided to cli
// Params: providedPath:char* representing the provided value for the file path
void errorFilePathInvalid(char* providedPath) {
	fprintf(stderr, "Error: The provided file path {%s} is invalid\n", providedPath);
}

// Function to print error for file path to long
// Params: pathLength:int representing the length of the file path 
void errorFilePathTooLong(int pathLength) {
	fprintf(stderr, "Error: The provided filepath is longer than the maximum length of 50. \
Provided path is %d characters\n", pathLength);
}

// Function to print error for invalid nth word arguement provided
void errorInvalidNthWord() {
	fprintf(stderr, "Error: The provided optional arguement nthWord is invalid. Should be \
in the form of -<number> where number is greater than or equal to 1\n");
}

// Function to print error for file line exceeding line max length of 128 characters
// Params: lineLength:int representing the length of the invalid line
void errorLineIsTooLong(int lineLength) {
	fprintf(stderr, "Error: Line is longer than the max length of 128 characters at %d \
characters long\n", lineLength);
}