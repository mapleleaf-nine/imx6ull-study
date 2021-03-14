#include <stdio.h>

/*
gcc -o hello hello.c
1. 执行 ./hello (argc = 1, argv[1] = ./hello)
2. 执行 ./hello bingo (argc = 2, argv[1] = ./hello argv[2] = bingo)
3. 执行 ./hello double bingo (argc = 3, argv[1] = ./hello argv[2] = double argv[3] = bingo)
*/
int main(int argc, char **argv)
{
    int n = 0;
    if(argc == 2)
        {
            printf("hello %s!\n", argv[1]);
        }
    else if(argc == 1 )
        {
            printf("hello world!\n");
        }
    else if(argc > 2)
        {
            for(n = 0; n < argc; n++)
                {
                    printf("argc_%d is %s\n",n,argv[n]);
                }
        }
    return 0;
}