# CASM
CASM的全称是Catium Self Made language.  
并且部分指令类似汇编语言, 因此有ASM成分(大雾).  

## 解释器的使用:
参考`build.bat`编译, 编译出来的可执行程序`casm.exe`(windows下).  

CASM目前没有使用任何平台相关代码, 因此她是跨平台的.  

运行可执行文件时, 您可以在标准输入流中输入您的CASM代码, 或者您也可以在命令提示符中用管道符将文件重定向至标准输入流.  
标准输入流结束后, CASM将尝试解释您的代码.  
如果解释过程中发现语法错误, 将会报错.  

[Hello, World! 例程](example/HelloWorld.casm)

CASM代码文件后缀应为`.casm`

# 语法  
一般的操作语法为 `操作符 [操作字节数] 操作数 [操作数 ...]`

# 注释

注释要求单独成行或位于行尾, 主要是不能出现在其他语句的操作数位置, 以`#`开始

# CASM没有函数, 也不需要显式循环
我们并未采用函数, 而是引入了"代码块"的概念.  
作为循环的替代品, 代码块默认是循环执行的.  
如果代码块内没有显式跳出/返回指令(如`ret`,`rez`等), 则会循环执行代码块主体内容.

## 代码块
see at [block.cpp](src/block.cpp)  
代码块由`block`关键字声明, 以`endblock`关键字结束, 不得相交或嵌套.  
举个例子:  
```casm
block loop
    sub     4       cnt     1
    rez     cnt
endblock

block main
    var     4       cnt     0xff
    call    loop
    ret
endblock
```
上述代码会在`main`块中声明一个4字节变量`cnt`, 然后调用`loop`块, 每次循环令`cnt`减一, 直到`cnt`为零时返回`main`块, 最后退出`main`块.  
**整个程序由名为`main`的代码块开始执行, 如果不存在则不会有代码被执行**  
<span id="multi-definition-of-block">
在任何情况下, 如果有某个代码块的名字被声明了多于1次, 则后面的同名代码块会覆盖前面的同名代码块.  
</span>
CASM允许块的内容在运行时改变, 因此她是动态语言.  

# 内存管理
CASM采用堆栈模式管理内存:  
+ 变量的内存由堆维护, 堆自底向上生长[vmem_heap.cpp](src/vmem_heap.cpp)
+ 栈空间由栈维护, 栈自顶向下生长[vmem_stack.cpp](src/vmem_stack.cpp)

总的可用于解释代码的内存在编译解释器时定义(默认为128MB). 参考[build.bat](build.bat)

## 堆: 内存分配与回收

## 栈: push
+ 接受1个操作数  
+ 不需要指定数据长度  
`push a` 将`a`入栈, 即在栈顶按字节复制`a`  
+ `a`必须为变量  
注意, 不需要显式的指定数据长度, 是因为数据长度根据变量名判断.  

## 栈: pop
+ 接受1个操作数  
+ 不需要指定数据长度  
`pop a` 出栈到`a`, 即从栈顶按字节复制数据到`a`  
+ `a`必须为变量  
+ 栈大小小于变量大小时忽略本次操作(`a`中值不变)  
注意, 不需要显式的指定数据长度, 是因为数据长度根据变量名判断.  


# 数据类型

## 立即数
+ 格式为10进制整数或16进制整数  
+ 十进制整数可以为负数  
+ 16进制整数格式类似`0x0123456789abcdef`, 且不允许负数  
+ 超出目标操作数容量的, 高位将被舍去(在小端字节序下).  

## 变量
see at [var.cpp](src/var.cpp)  

CASM不强制区分变量内容的类型, 因此她是一种弱类型语言.  

+ 变量的生存周期是从它被声明到他被销毁.  
+ 在生存周期内, 变量的作用域是全局.  
+ 只能使用`a~z`,`A~Z`,`0~9`,`_`作为标识符(经测试 [unicode字符或许也能用](example/unicode.casm))  
+ 区分大小写  
+ 不允许`0~9`作为标识符首字母  

### 变量的声明: var关键字
+ 接受2个操作数  
+ 需要指定数据长度  

`var a b c` 创建一个`a`字节的变量, 变量名为`b`, 初始值为`c`  
+ `a`的大小不限制, 当**堆空间**不足以创建时, 产生错误.  
+ `b`的要求见变量名格式  
+ `c`只能为立即数,或其他变量.  
+ 当`c`为变量时, 初始化操作将按字节复制`c`的内容到`b`, 多退少补  
+ 当`c`为立即数时, 如果`a`小于等于4则按值复制, 否则按字节填充`c`的最低字节.  
+ 特别地, 0字节变量允许被声明, 但可能无法被正常使用  
+ 长度为负的变量可能会导致未定义行为  

小于等于4字节的变量在其他运算中会被优先视为整数.  
3字节整数变量不区分正负.  
*注意, 在循环块中创建变量而不删除变量是不明智的, 因为循环执行至第二次的时候就会产生重名变量的错误.*  

### 变量的销毁: del关键字
+ 接受1个操作数  
+ 不需要指定数据长度  
`del a` 销毁一个名为`a`的变量.  
销毁后内存会被释放进**堆**中(详见[vmem_heap.cpp](src/vmem_heap.cpp#vmem_free)).  
目前回收机制比较简陋, 对长度是二的幂的内存进行整块回收, 否则拆分后回收.  

## 内存地址

格式为`[addr]`  
其中`addr`可以是变量名,立即数,**但不可以是另一个内存地址**  
表示内存中`addr`位置的内容, 元素字节数另外指定.  
如果`addr`是一个长度大于`4`的变量, 将产生错误.

CASM是不进行内存保护的, 您可以用`[]`操作符访问任意地址的数据(限制在解释器提供的虚拟内存范围里).  

# 指令
指令分为块内指令和块外指令.  
+ 块外指令由[流解释器](src/executor.cpp#parse_stream)解释并分割成块.  
+ 块内指令由[块解释器](src/executor.cpp#execute_block)解释并执行.  

## 块内指令

### call
用于跳转到某个代码块, 在目标代码块显式返回时回到`call`所在代码块继续执行后续代码.  

### ret
用于无条件跳出代码块.  

### rez
+ 接受一个操作数  
+ 操作数必须为变量  
用于有条件跳出代码块, 操作数值为`0`时跳出代码块, 否则继续执行块内其后的语句.  

举个例子:  
```casm
block loop
    sub     4       cnt     1       # 1
    rez     cnt                     # 2
endblock

block main
    var     4       cnt     0xff
    call    loop
    ret                             # 3
endblock
```
上述代码会循环执行loop块的内容(#1 & #2), 直到cnt值为0时跳出, 继续执行#3.  

### exit
用于无条件结束整个程序(强制令解释器退出).  

### mov
`mov a b c` 从`c`复制`a`字节的数据到`b`位置  
+ 接受2个操作数  
+ 需要指定数据长度  
+ `a`必须是一个正立即数.  
+ `b,c`可以是内存地址, 可以是变量名  
+ `c`可以为立即数  
+ `b`不得为立即数  

### 整数运算
*注: 3字节运算视为4字节运算并自然溢出为3字节*

#### add
`add a b c` 进行一次`a`字节加法, 把`c`加在`b`上  
+ 接受2个操作数  
+ 需要指定数据长度(不超过4)  
+ `b`必须为变量  
+ `c`可以是立即数,变量  
  
#### sub
`sub a b c` 进行一次`a`字节减法, 把`b`减去`c`  
+ 接受2个操作数  
+ 需要指定数据长度(不超过4)  
+ `b`必须为变量  
+ `c`可以是立即数,变量  

#### mul
`mul a b c` 进行一次`a`字节乘法, 把`c`乘在`b`上  
+ 接受2个操作数  
+ 需要指定数据长度(不超过4)  
+ `b`必须为变量  
+ `c`可以是立即数,变量  

#### div
`div a b c` 进行一次`a`字节除法, 把`c`除在`b`上.  
+ 接受2个操作数  
+ 需要指定数据长度(不超过4)  
+ `b`必须为变量  
+ `c`可以是立即数,变量 
+ **下取整**.  

## 内存指令

### addr
取地址运算.    
`addr a b` 获取`b`的内存地址并写到`a`  
+ 接受2个操作数  
+ 不需要指定数据长度  
+ 要求`a`,`b`均为变量  
+ `a`最好为4字节变量, 少于字节的将会截取低位, 多于4字节的只填充低4字节.  

### size
取长度运算.  
`size a b` 获取`b`的内存大小并写到`a`  
+ 接受2个操作数  
+ 不需要指定数据长度  
+ 要求`a`,`b`均为变量.  
+ `a`最好为4字节变量, 少于字节的将会截取低位, 多于4字节的只填充低4字节.  

### IO指令

#### pchar
`pchar a` 把`a`当做一个ASCII字符输出到标准输出流(stdout)  
+ 接受1个操作数  
+ 不需要指定数据长度  
+ `a`可以为变量, 内存地址, 立即数  
+ 如果`a`是变量, 则取其最低字节  
+ 如果`a`是内存地址, 则取该位置1字节  
+ 如果`a`是立即数, 则取其最低字节  

#### pint
`pint a` 把`a`当做一个有符号整数输出到标准输出流(stdout)  
+ 接受1个操作数  
+ 不需要指定数据长度  
+ `a`可以为变量, 立即数  
+ 如果`a`是变量, 则最多取其低4字节  
+ 如果`a`是立即数, 则直接输出  
+ 特别地, 如果`a`是3字节变量则被视为一个仅有低3位的4字节有符号整数.  

# 块外指令

## include
用于包含另外一个文件.  
`include a.casm` 把`a.casm`文件的内容加入当前程序, 要求`a.casm`必须是一个可以读取的合法casm文件, 其内容格式依照本文其他要求.  
比如说,`1.casm`中有一个block, 想要在`2.casm`执行时被调用, 就可以在`2.casm`中加入一句`include 1.casm`.  
由`include`连接的若干代码文件共享变量,内存,堆栈.  

一般情况下, 由于CASM对块的处理是顺序无关的, `include`可以位于任何块外部的位置, 文件头部, 尾部, 中间均不影响被包含代码的执行.  
特别地, 如果重定义了同名代码块, 那么include的位置会影响到代码块的内容, 参见[block](#multi-definition-of-block).

`include`会吧目标文件当做一个新的流交给流解释器处理.  

## block
用于标记某个代码块开始.  

## endblock
用于标记某个代码块结束.  
