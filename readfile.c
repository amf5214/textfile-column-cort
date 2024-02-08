// Written by Austin Fraley
// 02/07/2024
// Series of types and functions to assist in handling files


#include "readfile.h"

// Function to create a Word object
// This function copies the string provided so that it is independent
// of the provided pointer and also calculates and stores lenth for you
// Params: initText:char* represents an array of chars/string of text
// Returns: Word type struct
Word createWord(char* initText) {
	unsigned long length = strlen(initText);
	char* innerText = (char*) malloc(sizeof(char*) * length);
	strcpy(innerText, initText);
	Word newWord = {innerText, (int)length};
	return newWord;
}

// Function to create a Line object
// Params: initWords:Word* an array of Word objects,
// initLength:int length of the array
// Returns: Line type object
Line createLine(Word* initWords, int initLength) {
	Line newLine = {initWords, initLength};
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

void printFile(File* file) {
	int length = file->length;
	for(int i = 0; i < length; i++) {
		printLine(&file->lines[i]);
	}
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

	return count;

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

	Line newLine = createLine(words, length);

	return newLine;
}

int countFileLines(FILE* file) {
	int count = 0;

	char* emptyStr = "";

	while(!feof(file)) {
		char* line = (char*) malloc(sizeof(char*) * 128);
		strcpy(line, emptyStr);

                fgets(line, 128, file);

		if(strlen(line) > 0 && line[strlen(line)-1]  == '\n') {
			count += 1;
		}

		free(line);
        }

	rewind(file);

	return count;
}

File readInFile(FILE* file) {
	char* emptyStr = "";

	int numLines = countFileLines(file);
	Line* lines = (Line*) malloc(sizeof(Line) * numLines);

	int count = 0;

        while(!feof(file)) {
                char* line = (char*) malloc(sizeof(char*) * 128);
                strcpy(line, emptyStr);

                fgets(line, 128, file);

                if(strlen(line) > 0 && line[strlen(line)-1]  == '\n') {
                	Line newLine = readInLine(line);
			lines[count] = newLine;
			count += 1;
                }

        }

	File returnFile = createFile(lines, numLines);

	rewind(file);

	return returnFile;
}


int main() {
	// Word word1 = createWord("Hello");
	// printf("word1 = %s\n", word1.text);

	// char* line1 = "this is a test line";
	// char* testLine = (char*) malloc(sizeof(char*) * 128);
	// strcpy(testLine, line1);

	// Line output = readInLine(testLine);

	// printf("Length of testLine is %d\n", output.length);

	// printLine(&output);

	FILE* file = fopen("testfile.txt", "r");

	File file1 = readInFile(file);

	printFile(&file1);

	fclose(file);

	return 0;
}
