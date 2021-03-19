#1 
头文件：
```c
#include <sys/mman.h>
```
函数原型：
```c
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
```
函数说明：
① addr表示指定映射的內存起始地址，通常设为 NULL表示让系统自动选定地址，并在成功映射后返回该地址；
② length表示将文件中多大的内容映射到内存中；
③ prot 表示映射区域的保护方式，可以为以下4种方式的组合
a. PROT_EXEC 映射区域可被执行
b. PROT_READ 映射区域可被读出
c. PROT_WRITE 映射区域可被写入
d. PROT_NONE 映射区域不能存取
④ Flags 表示影响映射区域的不同特性，常用的有以下两种
a. MAP_SHARED 表示对映射区域写入的数据会复制回文件内，原来的文件会改变。
b. MAP_PRIVATE 表示对映射区域的操作会产生一个映射文件的复制，对此区域的任何修改都不会写回原来的文件内容中。
⑤ 返回值：若成功映射，将返回指向映射的区域的指针，失败将返回-1。