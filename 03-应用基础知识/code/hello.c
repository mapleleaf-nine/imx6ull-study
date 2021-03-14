#include <stdio.h>

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