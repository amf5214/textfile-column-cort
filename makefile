all: main

main: readfile.c
	clang -g -O0 readfile.c -o colsort
