all: main

main: readfile.c
	clang -gdwarf-4 -O0 readfile.c -o colsort
