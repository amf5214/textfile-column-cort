// Written by Austin Fraley
// 02/08/2024
// Series of functions to help sort a file by the nth word

#include "readfile.h"
#include "colsort.h"

// Function to interpret cli arguments into filepath and nth word args
// Params: argc:int is the number of command line arguements present
// argv:char** is an array of strings provided by the cli
// destNthWord:int* pointer to an int where the nth word int will be stored
// filePath:char* is a pointer to a string that will hold the file path
void getSortArgs(int argc, char** argv, int* destNthWord, char* filePath) {
	// Control flow to assign values to filePath and nthWord
	if(argc < 2) {
		errorNotEnoughArguements();
	} 
	else if(argc > 2 && argc < 4) {
		int output = -1;
		if (argv[1][0] == '-') {
			strcpy(filePath, argv[2]);
			output = sscanf(argv[1] + 1, "%d", destNthWord);
		} else {
			strcpy(filePath, argv[1]);
			output = sscanf(argv[2] + 1, "%d", destNthWord);
		}
		if(output < 1) {
			errorInvalidNthWord();
		}

	}
	else {
		strcpy(filePath, argv[1]);
	}

}

// Function to perform the sort by nth word
// Uses qsort to sort the file therefore requires the compareLines function defined within readfile.h
// Params: file:File* representing a pointer to the File object, nthWord:int representing the nthWord index
// Returns: File representing the sorted file
File sortFileByNthWord(File* file, int nthWord) {
	assignNthWords(file, nthWord);
	qsort(file->lines, file->length, sizeof(Line), compareLines);
	return *file;
}

// Function to read in a file and perform the sort by nth word
// Uses the stdio FILE object to read in and then switches to File object from readfile.h 
// Params: filePath:char* representing a string with the file path, nthWord:int representing the nthWord index
// Returns: File representing the sorted file
File getFileSortedByNthWord(char* filePath, int nthWord) {
	FILE* file = (FILE*) malloc(sizeof(FILE*));
	file = fopen(filePath, "r");

	File file1 = readInFile(file);
	
	sortFileByNthWord(&file1, nthWord);

	fclose(file);

	return file1;
}


int main(int argc, char** argv) {
	// Variable to store the nth word to sort by
	int nthWord = 1;

	// Variable to store the file path
	char* filePath = (char*) malloc(sizeof(char*) * 50);

	// Assign file path and nth word
	getSortArgs(argc, argv, &nthWord, filePath);

	File file = getFileSortedByNthWord(filePath, nthWord);

	printFile(&file);

	freeFile(file);
	free(filePath);

	return 0;
}
