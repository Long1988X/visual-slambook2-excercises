[toc]

# 第1讲 预备知识

1. 有线性方程$Ax=b$，若已知$A，b$，需要求解$x$，该如何求解？

   这对$A和b$有哪些要求？

   提示：从$A$的维度和秩角度来分析。

   > 1. 求解方法：
   >    1. QR分解
   >    2. LDLT
   >    3. 高斯列主元法
   >    4. 具体求解过程交给相关库吧，比如Eigen；
   >    
   > 2. 对$A、b$有哪些要求？
   >
   >    ==直观理解：当$b$是矩阵$A$各列向量的线性组合时，有解；==
   >
   >    参考MIT线性代数教程Lecture 6 向量空间与列向量；
   >
   >    1. 有解无解总结：
   >       * 通过高斯消元法，化简，化成阶梯行方程组；
   >       * 出现${0=d}$形式的不相容方程，则**无解**；
   >       * 有解情况下，有效方程个数小于未知数个数，则有**无穷多解**；如果正好相等，则有**唯一解**；
   >    2. 齐次方程组：$b=0$
   >       * 不存在无解的情况；（0必然是其解）
   >       * 判断$det(A)$
   >       * 若$det(A)==0$，则有非零解（无穷多个解）
   >       * 若$det(A)！=0$，则只有零解（唯一解）
   >    3. 非齐次方程组：$b!=0$
   >       * 考察系数矩阵$r(A)$，增广矩阵$r(A,b)$，以及方程组未知数个数$n$
   >       * 若$r(A)<r(A,b)$，则方程组无解；
   >       * 若$r(A)=r(A,b)<n$，则方程组有多个解；
   >       * 若$r(A)=r(A,b)=n$，则方程组有唯一解；

2. 高斯分布是什么？它的一维形式是什么样子？它的高维形式是什么样子？

   > 1. ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200301225748575.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0hhbmdoYW5nXw==,size_16,color_FFFFFF,t_70)
   > 2. 高斯分布：高斯分布（正态分布）是一个常见的连续概率分布。
   > 3. 一维形式
   >    1. 若随机变量$X$服从一个位置参数为$μ$、方差为$σ^2$的正态分布，可以记为$X ~ N(μ,σ2)$，则其概率密度函数为：
   > 4. 高维形式

3. 你知道C++中的类吗？你知道STL吗？你使用过它们吗？

   > 1. C++类
   >    * 可以看作是对相似事物的抽象；
   >    * 用类描述对象；对象是指现实世界中的一切事物；
   >    * C++中使用关键字class来定义类；
   > 2. STL
   >    * Standard Template Library，标准模板库；
   >    * 广义上分为三类：algorithm（算法）、container（容器）、iterator（迭代器）
   >    * 几乎所有代码都采用了模板类和模板函数的方式，提供了更好的代码重用机会；

4. 你以前怎样书写C++程序？（你完全可以说只在Visual C++ 6.0下写过C++工程，只要你有写C++和C语言的经验就行。）

   > 使用vscode编辑代码，然后编写CMakeLists.txt，生成makefile编译软件；

5. 你知道C++11标准吗？你听说过或用过其中那些新特性？有没有其他标准？

   > 1. 新特性
   >    * auto
   >    * for (auto &kp in keypoints)
   >    * lambda表达式
   > 2. 其他标准
   >    * C99 C++98
   >    * C++21 2021

6. 你知道Linux吗？你有没有至少使用过一种（不算安卓）操作系统，比如Ubuntu？

7. Linux的目录结构是什么样的？你知道哪些基本命令，比如ls、cat等？

   > 1. 目录结构
   >
   >    ![img](https://img-blog.csdn.net/20151001105801791?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center)
   >
   > 2. 基本命令

8. 如何在Ubuntu系统中安装软件（不打开软件中心的情况下）？这些软件被安装在什么地方？如果只知道模糊的软件名称（比如想要安装一个名称中含有Eigen的库），应该如何安装它？

   > 1. 安装软件
   >    1. sudo apt install
   >    2. dpkg -i *.deb
   >    3. 源码安装
   > 2. 安装位置
   >    * /usr/local
   > 3. 模糊安装软件
   >    * sudo apt-cache search libeigen*

9. 花一个小时学习vim，因为你迟早会用它。

   能够在学习本书的过程中使用它输入代码即可；

   不要在它的插件上浪费时间，不要想着把vim用成IDE，只用它做文本编辑的工作。
   
   > 1. 四种模式：命令模式、编辑模式、末行模式、可视化模式；
   > 2. ![Vim编辑器模式关系图](https://img-blog.csdnimg.cn/20210217160304749.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0hzRm9yUHlw,size_16,color_FFFFFF,t_70#pic_center)

