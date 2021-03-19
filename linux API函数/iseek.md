# 1
头文件：
```c
#include<sys/types.h>
#include<unistd.h>
```
函数原型:
```c
off_t lseek(int fd, off_t offset, int whence);
```
一、参数
1.fd:要操作的文件对应的文件描述符
2.offset:相对于whence的偏移量
3.whence:可以为SEEK_SET(0),SEEK_CUR(1),SEEK_END(2);
SEEK_SET:将读写位置移动到文件头后再增加offset个字节
SEEK_CUR:将读写位置移动到当前指定位置后再增加offset个字节
SEEK_END:将读写位置移动到文件结尾后再增加offset个字节

二、返回值:成功则返回当前读写位置，即目前的文件指针距文件开头有多少个字节；失败则返回-1

三、功能:
1.设置文件指针的位置
2.拓展文件大小
