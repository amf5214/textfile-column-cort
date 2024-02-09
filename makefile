all: main

main: readfile.c
	clang -gdwarf-4 -O0 *.c -o colsort
