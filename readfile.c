// Written by Austin Fraley
// 02/07/2024
// Series of types and functions to assist in handling files

# define MAX_LINE_SIZE 128

#include "readfile.h"

// Function to create a Word object
// This function copies the string provided so that it is independent
// of the provided pointer and also calculates and stores lenth for you
// Params: initText:char* represents an array of chars/string of text
// Returns: Word type struct
Word createWord(char* initText) {
	unsigned long length = strlen(initText);
	Word newWord;
	newWord.text = (char*) malloc(sizeof(char*) * length);
	strcpy(newWord.text, initText);
	newWord.length = (int)length;
	return newWord;
}

// Function to create a Line object
// Params: initWords:Word* an array of Word objects,
// initLength:int length of the array
// Returns: Line type object
Line createLine(Word* initWords, int initLength) {
	char* emptyStr = "";
	Line newLine;
	newLine.nthWord = (char*) malloc(sizeof(char*) * initLength);
	strcpy(newLine.nthWord, emptyStr);
	newLine.length = initLength;
	newLine.words = initWords;
	return newLine;
}


// Function to create a File object
// Params: initLines:Line* an array of Line ojects,
// initLength: int length of the array
// Returns File object
File createFile(Line* initLines, int initLength) {
	File newFile = {initLines, initLength};
	return newFile;
}

// Function to print out a Line object
// Iterates through the words array and prints on one line
// Params: line:Line* Line pointer used to access the line properties
void printLine(Line* line) {
	for(int i = 0; i < line->length; i++) {
		printf("%s ", line->words[i].text);
	}
	printf("\n");
}

// Function to print out a File object
// Iterates through the lines array and prints out one at a time using printLine function
// Params: file:File* Line pointer used to access the line properties
void printFile(File* file) {
	int length = file->length;

	printf("\n");
	for(int i = 0; i < length; i++) {
		printLine(&file->lines[i]);
	}
	printf("\n");
}

// Function to count the number of words in a line
// Copies the input char array so that the origin is not modified
// Params: lineText:char* line of text
// Returns: int representing the number of words present
int countWords(char* lineText) {
	const char*  delim = " ";

	// These two lines  duplicate the input string so that it is not modified
	char* text = (char*) malloc(sizeof(char*) * strlen(lineText));
	strcpy(text, lineText);

	int count = 0;
	char* word;

	word = strtok(text, delim);

	while(word != NULL) {
		count += 1;
		word = strtok(NULL, delim);
   	}

   	free(text);

	return count;
}
// Function to pop last character from a string/char*
// Params: string:char* represents the string to pop from, length:int is the length of the string
// Returns: char* is the pointer to the new string
char* popCharFromString(char* string, int length) {
	char* newString = (char*) calloc((length - 1), sizeof(char*));
	for(int i = 0; i < (length - 1); i++) {
		newString[i] = string[i];
	}

	char* rtnString = (char*) calloc((length - 1), sizeof(char*));
	strcpy(rtnString, newString);

	free(newString);

	return rtnString;
}

// Function to remove the next line character from the end of a word
// Params: word:Word word to check and remove from
// Returns: Word is the new word object where the \n has been removed 
Word removeNextLine(Word* word) {
	if(word->text[word->length-1] == '\n') {

		Word rtnWord = createWord(popCharFromString(word->text, word->length));

		return rtnWord;
	}
	else {
		return *word;
	}
}

// Function to read in a line and store it into a Line object
// This function copies the input string so that the original is not modified
// Params: lineText:char* string representing the text on the provided line
// Returns: Line object representing the line but is much more interactive
Line readInLine(char* lineText) {
	const char* delim = " ";

	int length = countWords(lineText);

	// These two lines  duplicate the input string so that it is not modified
	char* text = (char*) malloc(sizeof(char*) * strlen(lineText));
	strcpy(text, lineText);

	Word* words = (Word*) malloc(sizeof(Word) * length);

	int count = 0;
	char* word;

	word = strtok(text, delim);

	while(word != NULL) {
		Word newWord = createWord(word);

		words[count] = newWord;
		word = strtok(NULL, delim);

		count += 1;
	}

	words[length - 1] = removeNextLine(&words[length - 1]);

	Line newLine = createLine(words, length);

	free(text);

	return newLine;
}

// Function to count the number of lines in a file
// Params: file:FILE* FILE object pointer from std io library storing a stream of data
// Returns: int representing the number of lines in the file
int countFileLines(FILE* file) {
	int count = 0;

	char* emptyStr = "";

	while(!feof(file)) {
		char* line = (char*) malloc(sizeof(char*) * MAX_LINE_SIZE);
		strcpy(line, emptyStr);

                fgets(line, MAX_LINE_SIZE, file);

		if(strlen(line) > 0 && line[0] != '\n') {
			count += 1;
		}

		free(line);
        }

	rewind(file);

	return count;
}

// Function to read in a file from a std io library FILE object 
// Params: file:FILE* FILE object pointer from std io library storing a stream of data
// Returns: File struct containing an array of Line objects and a length value
File readInFile(FILE* file) {
	char* emptyStr = "";

	int numLines = countFileLines(file);
	Line* lines = (Line*) malloc(sizeof(Line) * numLines);

	int count = 0;

        while(!feof(file)) {
                char* line = (char*) malloc(sizeof(char*) * MAX_LINE_SIZE);
                strcpy(line, emptyStr);

                fgets(line, MAX_LINE_SIZE, file);

                if(strlen(line) > 0 && line[0] != '\n') {
                	Line newLine = readInLine(line);
			lines[count] = newLine;
			count += 1;
                }

        }

	File returnFile = createFile(lines, numLines);

	rewind(file);

	return returnFile;
}

// Function to assign the nthword attribute of a Line object
// Params: line:Line* line to be updated, nthWord:int index of the nthWord
void assignNthWord(Line* line, int nthWord) {
	if(line->length >= nthWord) {
		Word wordObj = line->words[nthWord - 1];
		line->nthWord = (char*) malloc(sizeof(char*) * wordObj.length);
		strcpy(line->nthWord, wordObj.text);
	} else if (line->length < nthWord && line->length > 0) {
		Word wordObj = line->words[line->length - 1];
		line->nthWord = (char*) malloc(sizeof(char*) * wordObj.length);
		strcpy(line->nthWord, wordObj.text);
	}
}

// Function to assign the nthword attribute of all Line objects in a File object
// Params: file:File* file to be updated, nthWord:int index of the nthWord
void assignNthWords(File* file, int nthWord) {
	for(int i = 0; i < file->length; i++) {
		assignNthWord(&file->lines[i], nthWord);
	}
}

// Function to compare lines of a file
// Created with the prototype required by qsort function
// Params: a:const void* is a void pointer to line 1, b:const void* is a void pointer to line 2
// Returns: int representing whether the nth word is equal to, comes before or after
int compareLines(const void * a, const void * b) {

	Line line1 = *(Line*) a;
	Line line2 = *(Line*) b;


	return strcmp(line1.nthWord, line2.nthWord);
}

// Function to free a file object and all of it's components
// Params: file:File is the file object to be freed
void freeFile(File file) {
	for(int i = 0; i < file.length; i++) {
		for(int j = 0; j < file.lines[i].words[j].length; j++) {
			free(file.lines[i].words[j].text);
		}
		free(file.lines[i].words);
		free(file.lines[i].nthWord);
	}
	free(file.lines);
}
