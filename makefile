all: main

main: readfile.c
	clang -gdwarf-4 -O0 colsort.c readfile.c -o colsort
