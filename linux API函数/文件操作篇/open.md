# 1
头文件：
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
```
函数原型：
```c
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
```
函数说明：
① pathname 表示打开文件的路径；
② Flags表示打开文件的方式，常用的有以下6种，
a. O_RDWR表示可读可写方式打开;
b. O_RDONLY表示只读方式打开;
c. O_WRONLY表示只写方式打开;
d. O_APPEND 表示如果这个文件中本来是有内容的，则新写入的内容会接续到原来内容的后面;
e. O_TRUNC表示如果这个文件中本来是有内容的，则原来的内容会被丢弃，截断；
f. O_CREAT表示当前打开文件不存在，我们创建它并打开它，通常与O_EXCL结合使用，当没有文件时创建文件，有这个文件时会报错提醒我们；
③ Mode表示创建文件的权限，只有在flags中使用了O_CREAT时才有效，否则忽略。
④ 返回值：打开成功返回文件描述符，失败将返回-1。
# 2
基于文件描述符的文件打开方式
###函数原型
```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char* pathname,int flags);
int open(const char* pathname,int flags,mode_t mode);
int creat(const char* pathname,mode_t mode);
```
>stat是status的缩写

>fcntl是file control的缩写

##参数
###flags
flags字段使用POSIX的几个宏，此时必须包含头文件`<fcntl.h>`才行。
可以是下面几个宏的逻辑或组合。这些宏共有三种类型：

|访问方式|描述
|---|---
|*O_RDONLY*|只读
|*O_WRONLY*|只写
|*O_RDWR*|可读写

|打开时标志|描述
|---|---
|*O_CREAT*|创建文件，需要指定第餐个参数mode
|*O_EXCL*|与`O_CREAT`联用，如果文件已存在则返回错误
|*O_TRUNC*|将清空文件的内容，仅对普通文件有用
|*O_NOCTTY*|若打开的文件是终端设备，不让它作为该进程的控制终端
|*O_NOBLOCK*|以非阻塞模式打开

|IO操作方式|描述
|---|---
|*O_APPEND*|把数据写到文件末尾
|*O_NONBLOCK*|对文件的read()/write()，当无立即可用输入(或输出不能立即写出)时能以EAGAIN错误状态标志立即返回 
|*O_ASYNC*|(异步)此标志被设置，文件描述符有输入数据时会生成SIGIO信号
|*O_SYNC*|
|*O_DSYNC*|
|*O_RSYNC*|

>`O_EXCL`的EXCL是Exclusive（排他的，专有的）的缩写
>>如果在打开已有文件的时候，没有使用`O_TRUNC`参数，而只是将fd的偏移置为文件头，
这样会有问题，即之前的内容没有没删除，而是逐个覆盖。如果第二次输入的内容少于文件本身的内容，
则会出现问题。

-----------

    一个进程当前有哪些打开的文件描述符可以通过/proc/进程ID/fd目录查看
