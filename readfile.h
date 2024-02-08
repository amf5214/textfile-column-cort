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
} Line;

typedef struct File{
	Line* lines;
	int length;
} File;

Word createWord(char* initText);

Line createLine(Word* initWords, int initLength);

File createFile(Line* initLines, int initLength);

void printLine(Line* line);

int countWords(char* lineText);

int countFileLines(FILE* file);

Line readInLine(char* lineText);

File readInFile(FILE* file);



