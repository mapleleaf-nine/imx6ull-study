- gcc -E -o main.i main.c
- gcc -S -o main.s main.i
- gcc -c -o main.o main.s

- gcc -E -o sub.i sub.c
- gcc -S -o sub.s sub.i
- gcc -c -o sub.o sub.s

- gcc -o test main.o sub.o
- ./test