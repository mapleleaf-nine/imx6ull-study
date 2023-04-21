1. 在Linux系统中，一切都是“文件”：普通文件、驱动程序、网络通信等等。所有的操作，都是通过“文件IO”来操作的。
2. 文件从哪里来？
- 磁盘，flash，sd卡，U盘：真实文件以某种格式（FAT32/EXT4）保存在某个设备上（/dev/...)，访问这些设备要先挂载mount。
- Linux内核提供的虚拟文件系统，也需要先挂载mount
- 特殊文件：/dev/...，设备节点（字符设备，块设备）
3. 通用的IO模型：open/read/write/lseek/close
- 不是通用的函数：ioctl/mmap
4. Linux下有3种查询函数用法的工具：help、man、info。
- help只能用于查看某个命令的用法，而man手册既可以查看命令的用法，还可以查看函数的详细介绍等。
    ```
    1 Executable programs or shell commands // 命令
    2 System calls (functions provided by the kernel) // 系统调用，比如 man 2 open
    3 Library calls (functions within program libraries) // 函数库调用
    4 Special files (usually found in /dev) // 特殊文件, 比如 man 4 tty
    5 File formats and conventions eg /etc/passwd // 文件格式和约定, 比如man 5 passwd
    6 Games // 游戏
    7 Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7) //杂项
    8 System administration commands (usually only for root) // 系统管理命令
    9 Kernel routines [Non standard] // 内核例程
    ```
    - 比如想查看open函数的用法时，可以直接执行“man open”，发现这不是想要内容时再执行“man 2 open”。
5. 系统调用函数进入内核的过程
- 常用glibc库
![Alt](https://img-blog.csdnimg.cn/20210318215921175.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hcGxlTGVhZl85,size_16,color_FFFFFF,t_70)
- 内核的sys_open、sys_read会做什么
![Alt](https://img-blog.csdnimg.cn/20210318220030440.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L01hcGxlTGVhZl85,size_16,color_FFFFFF,t_70)

6. 查看挂载

   ```c
   cat /proc/mounts       //查看挂载设备等信息
   ```

7. 主设备号：表示哪一种类型的驱动，从设备号：表示该类驱动的第几个设备（硬件）标识
