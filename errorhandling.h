// Written by Austin Fraley
// 02/08/2024
// Series of functions to handle errors programatically

#ifndef ERRORHANDLING_H
#define ERRORHANDLING_H

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Error conditions
// 1 - Not enough command line arguements given
// Function to print error for not enough arguements provided to cli
void errorNotEnoughArguements();

// 2 - File path is not valid
// Function to print error for invalid file path provided to cli
// Params: providedPath:char* representing the provided value for the file path
void errorFilePathInvalid(char* providedPath);

// 3 - File path is longer than 50 characters
// Function to print error for file path to long
// Params: pathLength:int representing the length of the file path 
void errorFilePathTooLong(int pathLength);

// 4 - Invalid nth character arguement nthWord = null
// Function to print error for invalid nth word arguement provided
void errorInvalidNthWord();

// 5 - Line is longer than 128 characters
// Function to print error for file line exceeding line max length of 128 characters
// Params: lineLength:int representing the length of the invalid line
void errorLineIsTooLong(int lineLength);

#endif
