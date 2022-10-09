@REM echo off
@REM 可能需要开大栈空间防止解析器递归爆栈(?存疑
@REM -Wl,--stack=1073741824

g++ -w -O2 .\src\* -I .\include\ -o casm.exe -DVMEM_SIZE=1024*1024*1024

exit

@REM -DVMEM_INIT_CLEAR=0                    初始化内存值,最好为0
@REM -DVMEM_SIZE=1024*1024                  设置vmem大小,单位:字节
@REM -DVMEM_MAX_FREESPACE_BLOCK=1024*1024   设置堆内存回收栈容量,单位:块
@REM -DNO_EXIT_AFTER_PANIC                  禁用panic后退出
@REM -DECHO_BLOCK_NAME                      输出代码块名
@REM -DDUMP_VMEM_AFTER_PANIC                panic后转储

@REM .\casm.exe
