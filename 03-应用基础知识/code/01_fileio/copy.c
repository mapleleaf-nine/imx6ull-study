
/*open函数涉及头文件*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
/*read,write函数涉及头文件*/
#include<unistd.h>
#include<stdio.h>

int main(int argc, char **argv)
{
    int fd_old, fd_new;
    char buf[1024];
    int len;

    /*判断参数*/
    if(argc != 3)
    {
        printf("Usage: %s <old_file> <new_file>\n", argv[0]);
        return -1;
    }

    /*打开老文件*/
    /*int open( const char * pathname,int flags, mode_t mode);*/
    fd_old = open(argv[1], O_RDONLY);
    if(fd_old == -1)
    {
        printf("can't open %s\n", argv[1]);
        return -1;
    }

    /*创建新文件*/
    /*第二个参数表示文件不存在就创建文件，若文件存在并且以可写的方式打开时，此旗标会令文件长度清为0，内容清零*/
    /*第三个参数给给权限*/
    fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |S_IWOTH);
    if(fd_new == -1)
    {
        printf("can't open %s\n", argv[2]);
        return -1;
    }

    /*循环 读老文件，写新文件*/
    /*ssize_t read(int fd,void * buf ,size_t count);*/
    /*ssize_t write (int fd,const void * buf,size_t count);*/
    while((len = read(fd_old, buf, 1024)) > 0)
    {
        if(write(fd_new, buf, len) != len)
        {
            printf("can't write %s\n", argv[2]);
            return -1;
        }
    }

    /*关闭文件*/
    close(fd_old);
    close(fd_new);
    
    return 0;
}