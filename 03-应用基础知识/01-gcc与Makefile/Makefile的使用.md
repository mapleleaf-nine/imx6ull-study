# 在Linux中使用make命令来编译程序，特别是大程序；而make命令所执行的动作依赖于Makefile文件。
1. 简单Makefile格式
    - 目标(target)…: 依赖(prerequiries)…
      < tab >命令(command)
    - 目标(target)通常是要生成的文件的名称，可以是可执行文件或OBJ文件，也可以是一个执行的动作名称，诸如`clean’。
    依赖是用来产生目标的材料(比如源文件)，一个目标经常有几个依赖。
    命令是生成目标时执行的动作，一个规则可以含有几个命令，每个命令占一行。
    注意：每个命令行前面必须是一个Tab字符，即命令行第一个字符是Tab。这是容易出错的地方。
    通常，如果一个依赖发生了变化，就需要规则调用命令以更新或创建目标。但是并非所有的目标都有依赖，例如，目标“clean”的作用是清除文件，它没有依赖。
    规则一般是用于解释怎样和何时重建目标。make首先调用命令处理依赖，进而才能创建或更新目标。当然，一个规则也可以是用于解释怎样和何时执行一个动作，即打印提示信息。
    一个Makefile文件可以包含规则以外的其他文本，但一个简单的Makefile文件仅仅需要包含规则。虽然真正的规则比这里展示的例子复杂，但格式是完全一样的。
    对于上面的Makefile，执行“make”命令时，仅当hello.c文件比hello文件新，才会执行命令“arm-linux-gcc –o hello hello.c”生成可执行文件hello；如果还没有hello文件，这个命令也会执行。
    运行“make clean”时，由于目标clean没有依赖，它的命令“rm -f hello”将被强制执行。
2. Makefile简单函数
    - $(foreach var,list,text)　：简单地说，就是 for each var in list, change it to text。对list中的每一个元素，取出来赋给var，然后把var改为text所描述的形式。
        ```
        objs := a.o b.o
        dep_files := $(foreach f, $(objs), .$(f).d) // 最终 dep_files := .a.o.d .b.o.d
        ```
    - $(wildcard pattern) : pattern所列出的文件是否存在，把存在的文件都列出来。
        ```
        src_files := $( wildcard *.c) // 最终 src_files中列出了当前目录下的所有.c文件
        ```
3. 通用Makefile解析
    - make命令的使用 ：执行make命令时，它会去当前目录下查找名为“Makefile”的文件，并根据它的指示去执行操作，生成第一个目标。
        + 我们可以使用“-f”选项指定文件，不再使用名为“Makefile”的文件，比如：
            ```
             make -f Makefile.build
            ```
        + 我们可以使用“-C”选项指定目录，切换到其他目录里去，比如：
            ```
             make -C a/ -f Makefile.build
            ```
        + 我们可以指定目标，不再默认生成第一个目标：
            ```
             make -C a/ -f Makefile.build other_target
            ```
    - 即时变量、延时变量 ：变量的定义语法形式如下 :
        ```
        A = xxx  // 延时变量,它的值在使用时才展开、才确定
                 // 如果使用“A := $@”，这是立即变量，这时$@为空，所以A的值就是空。
        B ?= xxx // 延时变量，只有第一次定义时赋值才成功；如果曾定义过，此赋值无效
        C := xxx // 立即变量
        D += yyy // 如果D在前面是延时变量，那么现在它还是延时变量；
                 // 如果D在前面是立即变量，那么现在它还是立即变量
        ```
    - 变量的导出(export) ：在编译程序时，我们会不断地使用“make -C dir”切换到其他目录，执行其他目录里的Makefile。如果想让某个变量的值在所有目录中都可见，要把它export出来。
    - Makefile中可以使用shell命令 ：
        ```
        TOPDIR := $(shell pwd)  // 这是个立即变量，TOPDIR等于shell命令pwd的结果。
        ```
    - 
4. 常见的自动化变量
- $@ ——目标文件的名称；
- $^ ——所有的依赖文件，以空格分开，不包含重复的依赖文件；
- $< ——第一个依赖文件的名称。
    ```
    %.o : %.c   //所有的.o文件，依赖于对应的.c文件
        gcc -c -o $@ $<    //$@表示目标(%.o)，$^表示依赖列表(%.s)。
    ```
