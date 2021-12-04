[toc]

# 第3讲 三维空间刚体运动

## 1. 目标

1. 理解三维空间的刚体运动描述方式：旋转矩阵、变换矩阵、（旋转向量）、四元数和欧拉角。
2. 掌握Eigen库的矩阵、几何模块的使用方法。

## 2. 知识点

1. 一个刚体在三维空间中的运动是如何描述的；

   > 旋转 + 平移；
   >
   > 平移没有太大问题，如何处理旋转；

2. 旋转矩阵、变换矩阵、旋转向量、四元数、欧拉角的意义，以及如何运算和转换；

3. $SO(3)$特殊正交群、$SE(3)$特殊欧式群

4. 罗德里格斯公式：旋转向量与旋转矩阵之间的变换；

5. 欧拉角：万向锁问题；

6. 四元数：

   1. 四元数可视化；[四元数可视化 - 视频](https://www.bilibili.com/video/av33385105)
   2. 四元数定义、运算；
   3. **四元数与旋转矩阵、旋转向量的转换**；

## 3. 实践部分

1. 安装Eigen；

2. 安装Pangolin；

3. useEigen：矩阵

   > 1. 练习Eigen库Matrix的使用；
   > 2. 矩阵的声明、初始化、基本运算、点乘、叉乘、特征值、特征向量；

4. useGeometry：几何模块

   > 1. 练习Eigen库Geometry的使用；
   > 2. 练习各种旋转的表达方式，以及他们之间的变换方式；（旋转矩阵、欧拉角、旋转向量、四元数）

5. plotTrajectory：使用Pangolin绘制相机轨迹

   > 1. 轨迹，**其实是机器人（相机）坐标系的原点在世界坐标系中的坐标**；
   > 2. 理解$T_{WR}$更直观的原因？其可以将机器人坐标系的原点，欧式变换为在世界坐标系下的坐标，也就是机器人此时此刻的轨迹点；
   > 3. 学习、练习Panglonn绘图流程、基本操作；
   > 4. 想想：==**轨迹文件从何而来？**==前端视觉里程计？

6. visualizeGeometry：显示相机位姿（3D窗口）

   > 1. 演示相机位姿的各种表达方式；
   > 2. 能够正确编译、执行程序；
   > 3. 试着阅读源码，是否能理解代码流程；

## 4. 课后习题

1. **验证旋转矩阵是正交矩阵**。

   > 1. 正交矩阵
   >
   >    ==**正交矩阵（orthogonal matrix）**==是一个非常好的矩阵，原因如下：
   >
   >    1. 正交矩阵每一列都是单位矩阵，并且两两正交。**最简单的正交矩阵就是单位阵**。
   >    2. 正交矩阵的逆（inverse）等于正交矩阵的转置（transpose）$A^{-1}=A^T$。同时可以推论出**正交矩阵的行列式的值肯定为正负1的**。
   >    3. 正交矩阵满足很多矩阵性质，比如可以相似于对角矩阵等等。
   >
   > 2. 旋转矩阵是正交矩阵验证
   >
   >    * 旋转矩阵**R**满足第一个条件，因为单位向量无论怎么旋转长度肯定不会变而且向量之间的正交性质也不会变；
   >
   >      先说一下什么是旋转矩阵？
   >
   >      如图1所示，我们假设最开始空间的坐标系$X_A,Y_A,Z_A$就是笛卡尔坐标系，这样我们得到空间A的矩阵$V_A=[X_A,Y_A,Z_A]^T$，其实也可以看做是单位阵$I$。经过旋转后，空间A的三个坐标系变成了图1中红色的三个坐标系$X_B,Y_B,Z_B$，得到空间B的矩阵，$V_B=[X_B,Y_B,Z_B]^T$。我们将两个空间联系起来可以得到$V_B=RV_A$，这里**R**就是我们所说的旋转矩阵。
   >
   >      ![img](https://images0.cnblogs.com/blog2015/791740/201508/060205044088686.png)
   >
   >      由于$X_A=[1,0,0]^T$，，$_YA=[0,1,0]^T$，$Z_A=[0,0,1]^T$，结合图2可以看出，旋转矩阵**R**就是由三个向$X_B,Y_B,Z_B$量组成的。
   >
   >      讲到这里，大家应该会发现旋转矩阵**R**满足第一个条件，因为单位向量无论怎么旋转长度肯定不会变而且向量之间的正交性质也不会变。那么**旋转矩阵就是正交阵**！
   >
   >      进一步利用数学公式进行证明：
   >
   >      ![img](https://images0.cnblogs.com/blog2015/791740/201508/060154505647587.png)
   >
   >    * **A**到**B**的旋转矩阵等于**B**到**A**的旋转矩阵的转置，$R^{-1}=R^T$；
   >
   >      两点数学知识。（1）点乘（dot product）的几何意义：如图3，我们从点乘的公式可以得到**α•β**相当与**β**的模乘上**α**在**β**上投影的模，所以当|**β**|=1时，**α•β**就是指**α**在**β**上投影的模。这一点在下面的内容中非常重要。（2）旋转矩阵逆的几何意思：这个比较抽象，不过也好理解。旋转矩阵相当于把一个向量（空间）旋转成新的向量（空间），那么逆可以理解为由新的向量（空间）转回原来的向量（空间）。
   >
   >      ![img](https://images0.cnblogs.com/blog2015/791740/201508/060214481586681.png)
   >
   >      看看$X_B,Y_B,Z_B$究竟是什么？由于图中所有的向量均是单位向量，所以$X_B$与$X_A$点乘的结果可以看成$X_B$在$X_A$上的投影的模，也就是$X_B$在空间A中**x轴的分量**！！图中中间的位置列出了$X_B$向量中的三个分量分别为$X_B$在$X_A$上的投影的模、$X_B$在$Y_A$上的投影的模和$X_B$在$Z_A$上的投影的模。这从几何角度很好理解。以此类推，可以得出的旋转矩阵**R**的表达形式。我们根据图4可以惊喜的发现，矩阵R的第一行就是$X_A$在$X_B,Y_B,Z_B$上的投影的模，也就是${X_A}^T$。
   >
   >      ![img](https://images0.cnblogs.com/blog2015/791740/201508/060231194231745.png)
   >
   >      根据上面公式可以推出**A**到**B**的旋转矩阵等于**B**到**A**的旋转矩阵的转置。根据我们上一段所说的**A**到**B**的旋转矩阵的逆就是等于**B**到**A**的旋转矩阵，因此很容易推出**R-1**等于**RT**！这满足正交矩阵的第二个条件，又一次证明了**旋转矩阵就是正交阵**。 
   >
   >      ![img](https://images0.cnblogs.com/blog2015/791740/201508/060239008303315.png)
   >
   >      
   >
   > 3. 举例说明
   >
   >    现在以三个欧拉角中的**RotX**为例（其余两个欧拉角以此类推），验证一下以上说的结论。
   >
   >    首先结合图5的公式，计算出**RotX**的旋转矩阵**Rrotx**。
   >
   >    ![img](https://images0.cnblogs.com/blog2015/791740/201508/061036414865256.png)
   >
   >    这样就完成旋转矩阵**Rrotx**，我们接下来验证一下。
   >
   >    1. 我们计算每一行每一列的模，都为1；并且任意两个列向量或者任意两个行向量都是正交的。所以满足上文列出的第一个性质。
   >    2. 我们计算**Rrotx**的行列式，很简单可以算出为1。这时我们计算一下该矩阵的逆和转置，这里我不写出来了是相等的。所以满足上文列出的第三个性质。
   >    3. 第三个性质要牵扯到更多的数学知识，在这里就不验证了。
   >
   >    **总结一下**：旋转矩阵是一个完美的矩阵——正交矩阵。它的行列式为1，且每个列向量都是单位向量且相互正交，它的逆等于它的转置。
   >
   > 4. ==参考==：
   >
   >    1. [旋转矩阵的性质分析](https://www.cnblogs.com/caster99/p/4703033.html)

2. **寻找罗德里格斯公式的推导过程并加以理解**。

   罗德里格斯公式描述了从旋转向量到旋转矩阵的转换关系。

   设旋转向量长度为$θ$，方向为$n$，那么旋转矩阵$R$为：

   ​						$$\boldsymbol{R}=\cos \theta \boldsymbol{I}+\left( 1-\cos \theta \right) \boldsymbol{nn}^T+\sin \theta \boldsymbol{n}^{\land}$$

   请证明此式！

   > **Rodrigues' Rotation Formula**
   >
   > 1. **定义**
   >
   >    * 在给定轴和旋转角度后，罗德里格斯公式是一个在空间有效的旋转向量的算法；
   >    * 可以从旋转向量变换为旋转矩阵；
   >    * 也就是说，该公式计算了从李代数$so(3)$到李群$SO(3)$的指数映射，而不用通过计算矩阵指数求得；
   >    * 罗德里格斯公式是计算三维空间中，一个待旋转向量绕旋转轴旋转一定角度后，得到一个新的向量的计算公式，而且可以改写成矩阵形式；
   >
   > 2. **推导思路**
   >
   >    已知：
   >
   >    旋转向量$\theta \vec{n}$，$\vec{n}$为单位向量；θ为旋转角度；
   >
   >    待旋转向量$\vec {v}$，旋转后的向量$\vec {v}_{rot}$；
   >
   >    则存在，$\vec {v}_{rot} = R\vec {v}$
   >
   >    通过向量平行四边形法则、正交分解、点积、叉积原理，求出$\vec {v}_{rot}$，与上式对比，消去$\vec {v}$，可以得出罗德里格斯公式；
   >
   > 3. **公式推导**
   >
   >    <img src="/home/pikachu/vslam14_exercises/ch3/Rodrigues%E2%80%98%20image.png" alt="Rodrigues‘ image" style="zoom:50%;" />
   >
   >    1. $\vec {v}_{rot} = R\vec {v}$
   >
   >    2. 求$\vec {v}_{rot}$
   >
   >       1. $\vec{v}_{rot}=\vec{v}_{rot\parallel}+\vec{v}_{rot\bot}$
   >
   >       2. $\vec{v}_{rot\parallel} = \vec{v}_{\parallel}$
   >
   >       3. $\vec{v}_{rot\bot}=\vec{a}+\vec{b}$
   >
   >          1. $\left| \vec{a} \right|=\left| \vec{v}_{rot\bot} \right|\times \cos \left( \theta -90° \right) =\left| \vec{v}_{rot\bot} \right|\sin \theta $，即$\vec{a}=\vec{w}\sin \theta $
   >
   >          2. $\left| \vec{b} \right|=\left| \vec{v}_{rot\bot} \right|\cos \left( 180°-\theta \right) =-\left| \vec{v}_{rot\bot} \right|\cos \theta $，即$\vec{b}=\vec{v}_{\bot}\cos \theta $
   >
   >          3. 求$\vec{w}$：
   >
   >             * $\because \ \vec{n},\vec{v}_{\bot}\text{与}\vec{w}\text{两两垂直，且}\left| \vec{w} \right|=\left| \vec{v}_{\bot} \right|\left| \vec{n} \right|sin<\vec{v}_{\bot},\vec{n}>=\left| \vec{v}_{\bot} \right|;$
   >             * $\because \ \vec{v}=\vec{v}_{\parallel}+\vec{v}_{\bot},\ \vec{v}_{\parallel}=\left( \vec{v}\cdot \vec{n} \right) \vec{n}$
   >             * $\therefore \ \text{由向量外积公式}，且\vec{n}\text{与}\vec{v}_{\parallel}\text{平行共线}，得$
   >             * $\vec{w}=\vec{n}\times \vec{v}_{\bot}=\vec{n}\times \left( \vec{v}-\vec{v}_{\parallel} \right) =\vec{n}\times \vec{v}-\vec{n}\times \vec{v}_{\parallel}=\vec{n}\times \vec{v}$
   >             * 即：$\vec{w}=\vec{n}\times \vec{v}$
   >
   >          4. 求$\vec{v}_{\bot}$：
   >
   >             * $\because \ \vec{v}=\vec{v}_{\parallel}+\vec{v}_{\bot}$
   >             * 由向量的矢量投影公式，得$\ \vec{v}_{\parallel}=\left( \vec{v}\cdot \vec{n} \right) \vec{n}$
   >             * $\therefore \ \vec{v}_{\bot}=\vec{v}-\vec{v}_{\parallel}=\vec{v}-\left( \vec{v}\cdot \vec{n} \right) \vec{n}$
   >
   >          5. $\therefore \ \vec{v}_{rot\bot}=\vec{a}+\vec{b}=\vec{w}\sin \theta +\vec{v}_{\bot}\cos \theta $
   >
   >             ​                               $=\sin \theta \left( \vec{n}\times \vec{v} \right) +\cos \theta \left( \vec{v}-\left( \vec{v}\cdot \vec{n} \right) \vec{n} \right) $
   >
   >    3. 最后公式，带入相关参数，并合并同类项：
   >
   >       * $\vec{v}_{rot}=\vec{v}_{rot\parallel}+\vec{v}_{rot\bot}=\vec{v}_{\parallel}+\vec{v}_{rot\bot}=\left( \vec{v}\cdot \vec{n} \right) \vec{n}+\sin \theta \left( \vec{n}\times \vec{v} \right) +\cos \theta \left( \vec{v}-\left( \vec{v}\cdot \vec{n} \right) \vec{n} \right) $
   >
   >         ​	    $=\cos \theta \vec{v}+\left( 1-\cos \theta \right) \left( \vec{v}\cdot \vec{n} \right) \vec{n}+\sin \theta \left( \vec{n}\times \vec{v} \right) $
   >
   >    4. 将得到得结果，变为矩阵得形式：
   >
   >       * 把$\vec{n}，\vec{v}$分别写为列向量：
   >
   >         $\vec v = \left(  \begin{array}{c} v_x\\
   >         	v_y\\
   >         	v_z\\ \end{array} \right) $  $\vec n = \left(  \begin{array}{c} v_n\\
   >         	n_y\\
   >         	n_z\\ \end{array} \right)$
   >
   >       * 令$\vec {v}_{rot} = R\vec {v}$，下面对$R$进行计算：
   >
   >         * $\left( \vec{v}\cdot \vec{n} \right) \vec{n}=\vec{n}\left( \vec{v}\cdot \vec{n} \right) =\vec{n}\left( \vec{n}^T \vec{v} \right) $
   >         * $\vec{n}\times \vec{v}=\left| \begin{matrix}
   >           	\vec{i}&		\vec{j}&		\vec{k}\\
   >           	n_x&		n_y&		n_z\\
   >           	v_x&		v_y&		v_z\\
   >           \end{matrix} \right|=\left( \begin{array}{c}
   >           	n_yv_z-n_zv_y\\
   >           	n_xv_z-n_zv_x\\
   >           	n_xv_y-n_yv_x\\
   >           \end{array} \right) =\left( \begin{matrix}
   >           	0&		-n_z&		n_y\\
   >           	n_z&		0&		-n_x\\
   >           	-n_y&		n_x&		0\\
   >           \end{matrix} \right) \left( \begin{array}{c}
   >           	v_x\\
   >           	v_y\\
   >           	v_z\\
   >           \end{array} \right)$
   >
   >         $\therefore \ \vec{v}_{rot}=\boldsymbol{R}\vec{v}=\cos \theta \boldsymbol{I}\vec{v}+\left( 1-\cos \theta \right) \vec{n}\vec{n}^T\vec{v}+\sin \theta \vec{n}^{\land}\vec{v}$
   >
   >         $\text{左右除去}\vec{v}\text{，得出罗德里格斯公式\ :}$
   >
   >         $\boldsymbol{R}=\cos \theta \boldsymbol{I}+\left( 1-\cos \theta \right) \vec{n}\vec{n}^T+\sin \theta \vec{n}^{\land}$
   >
   > 参考：
   >
   > 1. [Rodrigues' rotation formula - wiki]([https://en.jinzhao.wiki/wiki/Rodrigues%27_rotation_formula](https://en.jinzhao.wiki/wiki/Rodrigues'_rotation_formula))
   > 2. [罗德里格斯公式推导 - 知乎](https://zhuanlan.zhihu.com/p/113299607)
   > 3. 数学几何绘图软件：GeoGebra

3. **验证四元数旋转某个点后，结果是一个虚四元数（实部为零），所以仍然对应到一个三维空间点，见式 3.33。**

   通过运算，验证旋转后的四元数仍是一个虚四元数，即实部分量为0，虚部三分量仍表示一个空间点。

   知识点：

   1. 四元数运算：乘法、模长、逆；
   2. 单位四元数；
   3. 旋转向量转为四元数；

4. **画表总结旋转矩阵、轴角、欧拉角、四元数的转换关系。**

   ![在这里插入图片描述](https://img-blog.csdnimg.cn/20191121192832367.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MzYxOTM0Ng==,size_16,color_FFFFFF,t_70)

5. **假设有一个大的Eigen矩阵，想把它的左上角3x3的块取出来，然后赋值$I_{3x3}$。请编程实现。**

   见use_Eigen.cpp

6. **一般线性方程$Ax=b$有哪几种做法？你能在$Eigen$中实现吗？**

   > [转：六种方法解线性方程组！](https://www.cnblogs.com/newneul/p/8306442.html)
   >
   > 线性方程组Ax = b的解法 :
   > 	1、直接法：(1,2,3,4,5）
   > 	2、迭代法:如Jacobi迭代法(6)
   > 	其中只有2 3方法不要求方程组个数与变量个数相等
   >
   > 下面简略说明下**Jacobi迭代算法**:
   > 由迭代法求解线性方程组的**基本思想**是将联立方程组的求解归结为重复计算一组彼此独立的线性表达式，这就使问题得到了简化，类似简单迭代法转换方程组中每个方程式可得到雅可比迭代式；
   > 迭代法求解方程组有一定的局限性，比如下面Jacobi函数程序实现的过程中，会判断迭代矩阵的谱半径是不是小于1，如果小于1表示Jacobi迭代法收敛，如果求不出来迭代矩阵即D矩阵不可逆的话，无法通过收敛的充要条件来判断是不是收敛，此时可以试着迭代多次，看看输出结果是否收敛，此时Jacobi迭代算法并不一定收敛，只能试着做下，下面的程序实现过程仅仅处理了充要条件，迭代法同时有十分明显的优点——算法简单，因而编制程序比较容易，所以在实际求解问题中仍有非常大利用价值。
   >
   > ```C++
   > #include <iostream>
   > #include <ctime>
   > #include <cmath>
   > #include <complex>
   > /*线性方程组Ax = b的解法(直接法（1,2,3,4,5）+迭代法(6))其中只有2 3方法不要求方程组个数与变量个数相等*/
   > 
   > //包含Eigen头文件
   > //#include <Eigen/Dense>
   > #include <Eigen/Core>
   > #include <Eigen/Geometry>
   > #include <Eigen/Eigenvalues>
   > 
   > //下面这两个宏的数值一样的时候 方法1 4 5 6才能正常工作
   > #define MATRIX_SIZE 3   //方程组个数
   > #define MATRIX_SIZE_ 3  //变量个数
   > //using namespace std;
   > typedef  Eigen::Matrix<double,MATRIX_SIZE, MATRIX_SIZE_>  Mat_A;
   > typedef  Eigen::Matrix<double ,MATRIX_SIZE,1 >            Mat_B;
   > 
   > //Jacobi迭代法的一步求和计算
   > double Jacobi_sum(Mat_A &A,Mat_B &x_k,int i);
   > 
   > //迭代不收敛的话 解向量是0
   > Mat_B Jacobi(Mat_A &A, Mat_B &b,int &iteration_num, double &accuracy );
   > 
   > int main(int argc,char **argv)
   > {
   >     //设置输出小数点后3位
   >     std::cout.precision(3);
   >     //设置变量
   >     Eigen::Matrix<double,MATRIX_SIZE, MATRIX_SIZE_> matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE,MATRIX_SIZE_);
   >     Eigen::Matrix<double ,MATRIX_SIZE,1 > v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE,1);
   > 
   >     //测试用例
   >     matrix_NN << 10,3,1,2,-10,3,1,3,10;
   >     v_Nd <<14,-5,14;
   > 
   >     //设置解变量
   >     Eigen::Matrix<double,MATRIX_SIZE_,1> x;
   > 
   >     //时间变量
   >     clock_t tim_stt = clock();
   > 
   > /*1、求逆法	很可能没有解 仅仅针对方阵才能计算*/
   > #if (MATRIX_SIZE == MATRIX_SIZE_)
   >     x = matrix_NN.inverse() * v_Nd;
   >     std::cout<<"直接法所用时间和解为："<< 1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         <<"MS"<< std::endl << x.transpose() << std::endl;
   > #else
   >     std::cout<<"直接法不能解!(提示:直接法中方程组的个数必须与变量个数相同，需要设置MATRIX_SIZE == MATRIX_SIZE_)"<<std::endl;
   > #endif
   > 
   > /*2、QR分解解方程组	适合非方阵和方阵 当方程组有解时的出的是真解，若方程组无解得出的是近似解*/
   >     tim_stt = clock();
   >     x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
   >     std::cout<<"QR分解所用时间和解为："<<1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         << "MS" << std::endl << x.transpose() << std::endl;
   > 
   > /*3、最小二乘法	适合非方阵和方阵，方程组有解时得出真解，否则是最小二乘解(在求解过程中可以用QR分解 分解最小二成的系数矩阵) */
   >     tim_stt = clock();
   >     x = (matrix_NN.transpose() * matrix_NN ).inverse() * (matrix_NN.transpose() * v_Nd);
   >     std::cout<<"最小二乘法所用时间和解为:"<< 1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         << "MS" << std::endl  << x.transpose() << std::endl;
   > 
   > /*4、LU分解方法	只能为方阵（满足分解的条件才行）    */
   > #if (MATRIX_SIZE == MATRIX_SIZE_)
   >     tim_stt = clock();
   >     x = matrix_NN.lu().solve(v_Nd);
   >     std::cout<< "LU分解方法所用时间和解为:" << 1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         << "MS" << std::endl << x.transpose() << std::endl;
   > #else
   >     std::cout<<"LU分解法不能解!(提示:直接法中方程组的个数必须与变量个数相同，需要设置MATRIX_SIZE == MATRIX_SIZE_)"<<std::endl;
   > #endif
   > 
   > /*5、Cholesky	分解方法  只能为方阵 (结果与其他的方法差好多)*/
   > #if (MATRIX_SIZE == MATRIX_SIZE_)
   >     tim_stt = clock();
   >     x = matrix_NN.llt().solve(v_Nd);
   >     std::cout<< "Cholesky 分解方法所用时间和解为:" << 1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         << "MS"<< std::endl<< x.transpose()<<std::endl;
   > #else
   >     std::cout<< "Cholesky法不能解!(提示:直接法中方程组的个数必须与变量个数相同，需要设置MATRIX_SIZE == MATRIX_SIZE_)"<<std::endl;
   > #endif
   > 
   > /*6、Jacobi迭代法  */
   > #if (MATRIX_SIZE == MATRIX_SIZE_)
   >     int Iteration_num = 10 ;
   >     double Accuracy =0.01;
   >     tim_stt = clock();
   >     x= Jacobi(matrix_NN,v_Nd,Iteration_num,Accuracy);
   >     std::cout<< "Jacobi 迭代法所用时间和解为:" << 1000*(clock() - tim_stt)/(double)CLOCKS_PER_SEC
   >         << "MS"<< std::endl<< x.transpose()<<std::endl;
   > #else
   >     std::cout<<"LU分解法不能解!(提示:直接法中方程组的个数必须与变量个数相同，需要设置MATRIX_SIZE == MATRIX_SIZE_)"<<std::endl;
   > #endif
   > 
   >     return 0;
   > }
   > 
   > //迭代不收敛的话 解向量是0
   > Mat_B Jacobi(Mat_A  &A,Mat_B  &b, int &iteration_num, double &accuracy ) {
   >     Mat_B x_k = Eigen::MatrixXd::Zero(MATRIX_SIZE_,1);//迭代的初始值
   >     Mat_B x_k1;         //迭代一次的解向量
   >     int k,i;            //i,k是迭代算法的循环次数的临时变量
   >     double temp;        //每迭代一次解向量的每一维变化的模值
   >     double R=0;         //迭代一次后，解向量每一维变化的模的最大值
   >     int isFlag = 0;     //迭代要求的次数后，是否满足精度要求
   > 
   >     //判断Jacobi是否收敛
   >     Mat_A D;            //D矩阵
   >     Mat_A L_U;          //L+U
   >     Mat_A temp2 = A;    //临时矩阵获得A矩阵除去对角线后的矩阵
   >     Mat_A B;            //Jacobi算法的迭代矩阵
   >     Eigen::MatrixXcd EV;//获取矩阵特征值
   >     double maxev=0.0;   //最大模的特征值
   >     int flag = 0;       //判断迭代算法是否收敛的标志 1表示Jacobi算法不一定能收敛到真值
   > 
   >     std::cout<<std::endl<<"欢迎进入Jacobi迭代算法！"<<std::endl;
   >     //對A矩陣進行分解 求取迭代矩陣 再次求取譜半徑 判斷Jacobi迭代算法是否收斂
   >     for(int l=0 ;l < MATRIX_SIZE;l++){
   >         D(l,l) = A(l,l);
   >         temp2(l,l) = 0;
   >         if(D(l,l) == 0){
   >             std::cout<<"迭代矩阵不可求"<<std::endl;
   >             flag =1;
   >             break;
   >         }
   >     }
   >     L_U = -temp2;
   >     B = D.inverse()*L_U;
   > 
   >     //求取特征值
   >     Eigen::EigenSolver<Mat_A>es(B);
   >     EV = es.eigenvalues();
   > //    cout<<"迭代矩阵特征值为:"<<EV << endl;
   > 
   >     //求取矩陣的特征值 然後獲取模最大的特徵值 即爲譜半徑
   >     for(int index = 0;index< MATRIX_SIZE;index++){
   >         maxev = ( maxev > __complex_abs(EV(index)) )?maxev:(__complex_abs(EV(index)));
   >     }
   >     std::cout<< "Jacobi迭代矩阵的谱半径为："<< maxev<<std::endl;
   > 
   >     //谱半径大于1 迭代法则发散
   >     if(maxev >= 1){
   >         std::cout<<"Jacobi迭代算法不收敛！"<<std::endl;
   >         flag =1;
   >     }
   > 
   >     //迭代法收敛则进行迭代的计算
   >     if (flag == 0 ){
   >         std::cout<<"Jacobi迭代算法谱半径小于1,该算法收敛"<<std::endl;
   >         std::cout<<"Jacobi迭代法迭代次数和精度： "<< std::endl << iteration_num<<" "<<accuracy<<std::endl;
   > 
   >         //迭代计算
   >         for( k = 0 ;k < iteration_num ; k++ ){
   >             for(i = 0;i< MATRIX_SIZE_ ; i++){
   >                 x_k1(i) = x_k(i) + ( b(i) - Jacobi_sum(A,x_k,i) )/A(i,i);
   >                 temp = fabs( x_k1(i) - x_k(i) );
   >                 if( fabs( x_k1(i) - x_k(i) ) > R )
   >                     R = temp;
   >             }
   > 
   >             //判断进度是否达到精度要求 达到进度要求后 自动退出
   >             if( R < accuracy ){
   >                 std::cout <<"Jacobi迭代算法迭代"<< k << "次达到精度要求."<< std::endl;
   >                 isFlag = 1;
   >                 break;
   >             }
   > 
   >             //清零R，交换迭代解
   >             R = 0;
   >             x_k = x_k1;
   >         }
   >         if( !isFlag )
   >             std::cout << std::endl <<"迭代"<<iteration_num<<"次后仍然未达到精度要求，若不满意该解，请再次运行加大循环次数！"<< std::endl;
   >         return x_k1;
   >     }
   >     //否则返回0
   >     return  x_k;
   > }
   > 
   > //Jacobi迭代法的一步求和计算
   > double Jacobi_sum(Mat_A  &A,Mat_B &x_k,int i) {
   >     double sum;
   >     for(int j = 0; j< MATRIX_SIZE_;j++){
   >         sum += A(i,j)*x_k(j);
   >     }
   >     return sum;
   > }
   > ```