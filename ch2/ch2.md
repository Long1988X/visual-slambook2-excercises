# 第2讲 初识SLAM

## 1. 目标

1. 理解一个视觉SLAM框架由哪几个模块组成，各模块的任务是什么？
2. 搭建编程环境，为开发和实验做准备。
3. 理解如何在Linux下编译并运行一个程序，如果程序出了问题，又该如何调试它。
4. 掌握cmake的基本使用方法。

## 2. 课后习题

1. 阅读文献[1]和[14]，你能看懂其中的内容吗？

   > [1] A survey of monocular simultaneous localization and mapping 2016
   >
   > [14] Graph-based slam: A survey, ROBOT 2013

2. 阅读SLAM的综述文献，例如[9，15-18]等。这些文献中关于SLAM的看法与本书有何异同；

   > [9] Past, present and future of simultaneous localization and mapping: Towards the robust-perception age 2016
   >
   > [15] Visual simultaneous localizaion and mapping: a survey 2015
   >
   > [16] Topological simultaneous localization and mapping: a survey 2014
   >
   > [17] Kalman filter for robot vision: A survey 2012
   >
   > [18] Recent advances in simultaneous localization and map-building using computer vision 2007

3. g++命令有哪些参数？怎么填写参数可以更改生成的程序文件名？

   > -E：只激活预处理，不生成文件需要把它重定向到一个输出文件里面；
   >
   > g++ -E hello.c > more.txt
   >
   > -S：只激活预处理和编译，把文件编译成.s汇编代码，可以使用文本编辑器查看；
   >
   > -c：只激活预处理、编译和汇编，把程序做成.o的目标文件，二进制机器码一般人也读不了；
   >
   > ==-o==：制定目标名称，缺省的时候，a.out; g++ hello.c -o hello.exe

4. 使用build文件夹来编译你的cmake工程，然后在KDevelop中试试。

   > 外部编译：将源码文件和cmake生成的工程文件分开，将cmake生成的工程文件放在一个单独的build目录下面；

5. 刻意在代码中添加一些语法错误，看看编译会生成什么样的信息。你能看懂g++的错误信息吗？

   > 1. 从第一个错误查，更事半功倍。
   > 2. 看不懂的错误，复制错误内容，网页粘贴。。。

6. 如果忘了把库链接到可执行程序上，编译会报错吗？报什么样的错？

   > 库文件包含了函数的实现，忘记链接会报undefined reference to ...

7. 阅读《CMake实践》，了解CMake的其他语法。

   > 1. 大体看一遍，动手写写里面的例子；
   > 2. 等用到的时候在查看；

8. 完善Hello SLAM小程序，把它做成一个小程序库，安装到本地硬盘中。然后，新建一个工程，使用find_package找到这个库并调用。

   > 1. 将Hello SLAM编译动态库；
   > 2. CMakeLists.txt install动态库及头文件；
   > 3. cmake ..   
   > 4. make
   > 5. make install

9. 阅读其他cmake教学材料，例如：https://github.com/TheErk/CMake-tutorial。

10. 找到KDevelop的官方网站，看看它还有哪些特性。你都用上了吗？

    > 没有用KDevelop；
    >
    > 使用的vscode编辑代码，然后cmake ..

11. 如果在第1讲学习了vim，那么请试试KDevelop的Viim编辑功能。

    > 1. 知道vim的四个模式，知道如何切换；
    > 2. 能够使用vim修改小许代码，即可；