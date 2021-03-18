#1 简单粗暴，效率低
#testMakefile : main.c sub.c sub.h
#	gcc -o testMakefile main.c sub.c

#2 效率高，相似规则太多太啰嗦，不支持检测头文件
#testMakefile : main.o sub.o
#	gcc -o testMakefile main.o sub.o
#main.o : main.c
#	gcc -c -o main.o main.c
#sub.o : sub.c
#	gcc -c -o sub.o sub.c
#clean : 
#	rm testMakefile *.o -f

#3 效率高，精炼，不支持检测头文件
#testMakefile : main.o sub.o
#	gcc -o testMakefile main.o sub.o
#%.o :　%.c
#	gcc -c -o $@ $<
#clean : 
#	rm testMakefile *.o -f

#4 效率高，精炼，支持检测头文件(但是需要手工添加头文件规则)
#testMakefile : main.o sub.o
#	gcc -o testMakefile main.o sub.o
#%.o : %.c
#	gcc -c -o $@ $<
#sub.o : sub.h
#clean :
#	rm *.o testMakefile -f

#5 效率高，精炼，支持自动检测头文件，不支持子目录里的依赖文件
objs := main.o sub.o
testMakefile : $(objs)
	gcc -o testMakefile $^
# 需要判断是否存在依赖文件
# .main.o.d .sub.o.d 最前面的'.'表示这是隐藏文件
dep_files := $(foreach f, $(objs), .$(f).d)
dep_files := $(wildcard $(dep_files))
# 把依赖文件包含进来
# 如果变量不等于空，就把依赖文件包含进来
ifneq ($(dep_files),)
    include $(dep_files)
endif
%.o : %.c
	gcc -Wp,-MD,.$@.d -c -o $@ $<
clean :
	rm *.o testMakefile -f
distclean :
	rm $(dep_files) *.o testMakefile -f





