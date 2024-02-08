#define MAX_CHAR_IN_LINE 128

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to count the numbe of lines in the provided file
int countFileLines(FILE* file) {
	int count = 0;

	char* line = (char*) malloc(sizeof(char*) * MAX_CHAR_IN_LINE);

	while(!feof(file)) {
  	  	fgets(line, MAX_CHAR_IN_LINE, file);
		unsigned long length = strlen(line);
		printf("line %d length = %lu\n", count, length);
    		if(length > 1) {
			count += 1;
		}
    	}

	// free(line);

	return count;
}

// Function to read in the provided file and store it in the provided array
int readFile(FILE* file, char** fileLines, int lineCount) {
	int count = 0;

        while(!feof(file)) {
		char* line = (char*) malloc(sizeof(char*) * MAX_CHAR_IN_LINE);

		if(count >= lineCount) {
			return -1;
		}
                fgets(line, MAX_CHAR_IN_LINE, file);

		if(strlen(line) > 1) {
			fileLines[count] = line;
        	        count += 1;
	        }

	}

	return 0;
}


// Function to compare lines
int compareLines(const void * a, const void * b) {

	int nthWord = 0;

	const char* delim = " ";

	char* line1 = *(char**) a;
	char* line2 = *(char**) b;

	printf("line 1 = %s\n", line1);
	printf("line 2 = %s\n", line2);

	char* word1 = strtok(line1, delim);
	int iter1 = 0;
	while( word1 != NULL ) {
      		printf( " %s\n", word1 );
		if(iter1 == nthWord) {
			break;
		}
      		word1 = strtok(NULL, delim);
		iter1++;
   	}

	char* word2 = strtok(line2, delim);
	int iter2 = 0;
	while( word2 != NULL ) {
		printf(" %s\n", word2);
		if(iter2 == nthWord) {
			break;
		}
		word2 = strtok(NULL, delim);
		iter2++;
	}

	return strcmp(word1, word2);
}

// Function to print out array of strings
void printArrayOfStrings(char** fileLines, int lineCount) {
	for(int i = 0; i < lineCount; i++) {
		printf("line %d = %s\n", i,  fileLines[i]);
	}
}

int main(int argc, char** argv) {
	// Variable to store the nth word to sort by
	int nthWord = 1;

	// Variable to store the file path
	char* filePath = NULL;

	// Control flow to assign values to filePath and nthWord
	if(argc < 2) {
		printf("Not enough arguements provided\n");
	} 
	else if(argc > 2 && argc < 4) {
		printf("Includes nth char\n");
		if (argv[1][0] == '-') {
				printf("First arg is nt\n");
				filePath = argv[1];
			} else {
				printf("Second arg is nth\n");
				filePath = argv[2];
			}
	}
	else {
		printf("Doesn't include the nth char\n");
		filePath = argv[1];
	}

	printf("File path = %s\n", filePath);

	// File object pointer
	FILE* file = (FILE*) malloc(sizeof(FILE*));

	// Open the file and store it as a stream
	file = fopen(filePath, "r");

	// Run function to count the number of lines
	int lineCount = countFileLines(file);

   	printf("Line count = %d\n", lineCount);

	// Reset the file for the next file use
	rewind(file);

	// Declare the array of strings
	char** fileLines = (char**) malloc(sizeof(char*) * lineCount * MAX_CHAR_IN_LINE);

	// Read in the lines of the file
	int result = readFile(file, fileLines, lineCount);

	// Print array of strings before sort
	printArrayOfStrings(fileLines, lineCount);

	// Sort the array
	qsort(fileLines, lineCount, sizeof(char*) * 128 * lineCount, compareLines);

	// Print array of strings after sort
        printArrayOfStrings(fileLines, lineCount);

   	// Close file object
	fclose(file);

	return 0;
}
