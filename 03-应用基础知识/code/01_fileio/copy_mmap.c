
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/mman.h>
#include<stdio.h>

int main(int argc, char **argv)
{
    int fd_old, fd_new;
    struct stat stat;
    char *buf;

    /*判断参数*/
    if(argc != 3)
    {
        printf("Usage: %s <old_file> <new_file>\n", argv[0]);
        return -1;
    }

    /*打开老文件*/
    fd_old = open(argv[1], O_RDONLY);
    if(fd_old == -1)
    {
        printf("can't open %s\n", argv[1]);
        return -1;
    }

    /*确定老文件的大小*/
    if(fstat(fd_old, &stat) == -1)
    {
        printf("can't get stat of %s\n", argv[1]);
        return -1;
    }

    /*映射老文件*/
    /*	void *mmap(void *start,size_t length,int prot,int flags,int fd,off_t offsize);*/
    /*首地址为NULL；st_size 文件大小，以字节计算；PROT_READ 映射区域可被读取*/
    /*MAP_SHARED对映射区域的写入数据会复制回文件内，而且允许其他映射该文件的进程共享。*/
    /*参数fd为open()返回的文件描述词，代表欲映射到内存的文件。
    参数offset为文件映射的偏移量，通常设置为0，代表从文件最前方开始对应，offset必须是分页大小的整数倍。*/
    /*若映射成功则返回映射区的内存起始地址，否则返回MAP_FAILED(－1)，错误原因存于errno 中。*/
    buf = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, fd_old, 0);
    if(buf == MAP_FAILED)
    {
        printf("can't mmap %s\n", argv[1]);
        return -1;
    }

    /*创建新文件*/
    fd_new = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH |S_IWOTH);
    if(fd_new == -1)
    {
        printf("can't open %s\n", argv[2]);
        return -1;
    }

    /*写入新文件*/
    if(write(fd_new, buf, stat.st_size) != stat.st_size)
    {
        printf("can't write %s\n", argv[2]);
        return -1;
    }

    /*关闭文件*/
    close(fd_old);
    close(fd_new);

    return 0;
}

