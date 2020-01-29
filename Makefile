# Makefile
line_trace: main.o binarization.o debug.o calc.o
	gcc -o line_trace main.o binarization.o debug.o calc.o

# main
main.o:source/main.c
	gcc -I ./include -c source/main.c

# binarization
binarization.o:source/binarization.c
	gcc -I ./include -c source/binarization.c

# debug
debug.o:source/debug.c
	gcc -I ./include -c source/debug.c

# calc
calc.o:source/calc.c
	gcc -I ./include -c source/calc.c

# clean
clean:
	rm -f main.o binarization.o debug.o calc.o
