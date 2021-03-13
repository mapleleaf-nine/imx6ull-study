# linux基本指令

## 目录/文件操作指令

1. pwd : 打印当前所在路径
2. cd ：改变路径、切换路径
   - cd -  ：进入上次目录
   - cd ~ ：进入家目录
   - cd .. ： 返回上一级目录
3.  mkdir ： 创建目录
   - mkdir -p dir1/dir2 ： 创建目录与子目录
4.  rmdir ： 删除目录（只能删除一个空目录）
5.  ls ： 列出目录内容
   - ls -l  ： 显示文件更完整信息
   - ls -a ： 显示当前目录下的文件及隐藏文件
   - ls -lh ： 显示文件熟悉、链接数、文件所有者、文件所属用户组、文件大小、最后修改时间和文件名信息
6.  cp ： 复制文件或目录
   - -r ： 递归地，即复制所以文件
   - -f ： 强制覆盖
   - -d ： 如果源文件为链接文件，也只是把它作为链接文件复制
7.  rm ： 删除文件或目录
   - -r ： recursive
   - -f ： force
8.  cat ： 串联文件的内容并打印出来
   - -n ：显示行号
9. touch ： 修改文件的时间，如果文件不存在则创建空文件

## 改变文件的权限和属性

1. chgrp ：改变文件所属用户组

   - chgrp 【-R】 用户组  dirname/filename
2. chown ：改变文件的所有者
3. chmod ： 改变文件的权限
   - r ： 4 可读
   - w ：2 可写
   - x ： 1 可执行
   - u代表user、g代表group、o代表others

## 查找/搜索命令

1. find ：格式　find	目录名	选项	查找条件
   - 例如 ：find  /home/book  -name  "*.txt"   *是通配符
2.  grep ： 查找文件中符合条件的字符串
   - 格式 ： grep	选项	查找模式	文件名
   - 例如 ： grep -n "abc" text1.txt
   - grep可以配合管道命令符"|"使用
## 压缩/解压命令
- 单个文件压缩使用gzip和bzip2，多个文件和目录使用tar
1. gzip的常用项
   - -l ：列出压缩文件的内容
   - -k ：在压缩或解压时，保留输入文件
   - -d ：将压缩文件进行解压缩
   - gzip　：只能压缩单个文件，不能压缩目录
2. bzip : -k ：压缩文件  -kd　：解压文件
3. tar
   - -c(create)：表示创建用来生成文件包 。
   - -x：表示提取，从文件包中提取文件。
   - -t：可以查看压缩的文件。
   - -z：使用gzip方式进行处理，它与”c“结合就表示压缩，与”x“结合就表示解压缩。
   - -j：使用bzip2方式进行处理，它与”c“结合就表示压缩，与”x“结合就表示解压缩。
   - -v(verbose)：详细报告tar处理的信息。
   - -f(file)：表示文件，后面接着一个文件名。 -C <指定目录> 解压到指定目录。
   - tar -czvf dira.tar.gz dira 压缩    
   - tar xzvf dira.tar.gz -C /home/book 解压  
## 网络命令
1. ifconfig ：查看网络、设置ip
   - -a ：显示所有网卡接口
   - up：激活网卡接口
   - down：关闭网卡接口
   - address：xxx.xxx.xxx.xxx，IP地址
2. route和DNS : 路由和DNS
3. file : 查看文件名
4. which和whereis : 查找命令或应用程序所在位置
##  软件包管理系统(ubuntu)
1. apt下载工具使用

 
   
   
   
   



























   


