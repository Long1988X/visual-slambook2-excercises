[toc]

# 第4讲 李群与李代数

## 1. 目标

1. 理解李群与李代数的概念，掌握$SO(3)、SE(3)$与对应李代数的表示方式；
2. 理解$BCH$近似的意义；
3. 学会在李代数上的扰动模型；
4. 使用$Sophus$对李代数进行运算；

## 2. 知识点

1. 理解群、李群、李代数的概念与定义；
2. 理解群与李代数满足的性质；
3. 理解$SO(3)和SE(3)$的定义；
4. 理解$so(3)和se(3)$的定义；
5. 推导$SO(3)与so(3)$指数与对数映射；
6. 推导$SE(3)与se(3)$指数与对数映射；
7. 掌握$BCH$近似公式的表达及其意义；
8. 推导$SO(3)$上的李代数求导与左扰动模型；
9. 推导$SE(3)$上的李代数求导与左扰动模型；
10. 试着推导右扰动模型；

## 3. 实践

1. SLAM中李群、李代数==存在的意义==；

   > 1. 三维空间刚体运动的描述方式：旋转矩阵、旋转向量、欧拉角、四元数等；即SLAM中位姿的表示。
   > 2. 为了解决例如“什么样的相机位姿，最符合当前观测数据”的优化问题，求解最优位姿，R、t；
   > 3. 但，旋转矩阵自身带有约束（正交且行列式为1）；
   > 4. 通过李群 - 李代数间的转换关系，==把位姿估计变成无约束的优化问题，简化求解方式==；
   > 5. 由于李群对加法不封闭，导致==无法使用导数的定义进行求导操作==，进而不方便优化问题；
   > 6. 李代数对加法封闭，可以使用导数定义进行求导，也可以使用扰动模型。
   > 7. 在SLAM中，经常构建与位姿有关的函数，然后讨论该函数关于位姿的导数，以调整当前的估计值。
   > 8. 由于李代数由向量组成，具有良好的加法运算，因此使用李代数解决求导问题思路分成两种：1）李代数的求导模型；2）扰动模型。
   
2. 基础：$SO(3)、SE(3)、so(3)、se(3)$的定义及$BCH$近似公式：

   > 1. 三维旋转矩阵构成**特殊正交群$SO(3)$**（Sepcial Orthogonal Group）
   >
   >    $SO\left( 3 \right) =\left\{ \boldsymbol{R}\in R^{3×3}|\boldsymbol{RR}^T=\boldsymbol{I}\text{，}\det \left( \boldsymbol{R} \right) =1 \right\} $
   >
   > 2. 三维变换矩阵构成**特殊欧氏群$SE(3)$**（Special Euclidean Group）
   >
   >    $SE\left( 3 \right) =\left\{ \boldsymbol{T}=\left[ \begin{matrix}
   >    	\boldsymbol{R}&		\boldsymbol{t}\\
   >    	0^T&		1\\
   >    \end{matrix} \right] \in R^{4×4}|\boldsymbol{R}\in SO\left( 3 \right) ,\boldsymbol{t}\in R^3 \right\}$
   >
   > 3. $SO(3)$对应的**李代数$so(3)$**，位于$R^3$空间，其元素是三维向量或三维反对称矩阵：
   >
   >    $so\left( 3 \right) =\left\{ \phi \in R^3,\boldsymbol{\Phi }=\phi ^{\land}\in R^{3×3} \right\} $
   >
   > 4. $SE(3)$对应的**李代数$se(3)$**，位于$R^6$空间，由一个平移加上一个$so(3)$元素构成的向量：
   >
   >    $se\left( 3 \right) =\left\{ \xi =\left[ \begin{array}{c}
   >    	\rho\\
   >    	\phi\\
   >    \end{array} \right] \in R^6,\rho \in R^3,\phi \in so\left( 3 \right) ,\xi ^{\land}=\left[ \begin{matrix}
   >    	\phi ^{\land}&		\rho\\
   >    	0^T&		0\\
   >    \end{matrix} \right] \in R^{4×4} \right\}$
   >
   > 5. **$BCH$近似公式**：
   >
   >    $\ln \left( \exp \left( \phi _{1}^{\land} \right) \exp \left( \phi _{2}^{\land} \right) \right) ^{\lor}\approx \left\{ \begin{array}{l}
   >    	\boldsymbol{J}_l\left( \phi _2 \right) ^{-1}\phi _1+\phi _2\ \text{当}\phi _1\text{为小量}\\
   >    	\boldsymbol{J}_r\left( \phi _1 \right) ^{-1}\phi _2+\phi _1\ \text{当}\phi _2\text{为小量}\\
   >    \end{array} \right.$
   >
   > 6. $BCH$近似的意义：
   >
   >    > 1. 假定对某个旋转矩阵$R$，对应的李代数为$\phi$，**给它左乘一个微小旋转，记作$\bigtriangleup \boldsymbol{R}$**，对应的李代数为$\bigtriangleup \phi$。
   >    >
   >    >    那么，在李群上，得到的结果就是$\boldsymbol{J}_l\left( \phi \right) ^{-1}\bigtriangleup \phi +\phi $。合并起来，可以简单地写成：
   >    >
   >    >    $\bigtriangleup \boldsymbol{R}\cdot \boldsymbol{R}=\exp \left( \bigtriangleup \phi ^{\land} \right) \exp \left( \phi ^{\land} \right) =\exp \left( \left( \boldsymbol{J}_l\left( \phi \right) ^{-1}\bigtriangleup \phi +\phi \right) ^{\land} \right) $
   >    >
   >    > 2. 反之，如果**在李代数上进行加法**，让一个$\phi$加上$\bigtriangleup \phi$，那么可以近似为李群上带左右雅可比地乘法：
   >    >
   >    >    $\exp \left( \left( \phi +\bigtriangleup \phi \right) ^{\land} \right) =\exp \left( \left( \boldsymbol{J}_l\bigtriangleup \phi \right) ^{\land} \right) \exp \left( \phi ^{\land} \right) =\exp \left( \phi ^{\land} \right) \exp \left( \left( \boldsymbol{J}_r\bigtriangleup \phi \right) ^{\land} \right) $
   >
   > 7. 矩阵求导顺序：
   >
   >    > 假设$a、b、x、y$都是列向量，那么有如下规则：
   >    >
   >    > $\lim_{x\rightarrow 0\text{，}y\rightarrow 0}\frac{\left[ \begin{matrix}
   >    > 	\boldsymbol{a}&		\boldsymbol{b}\\
   >    > \end{matrix} \right] ^T}{\left[ \begin{matrix}
   >    > 	\boldsymbol{x}&		\boldsymbol{y}\\
   >    > \end{matrix} \right] ^T}=\frac{d\left[ \begin{array}{c}
   >    > 	\boldsymbol{a}\\
   >    > 	\boldsymbol{b}\\
   >    > \end{array} \right]}{d\left[ \begin{array}{c}
   >    > 	\boldsymbol{x}\\
   >    > 	\boldsymbol{y}\\
   >    > \end{array} \right]}=\left[ \frac{d\left[ \begin{matrix}
   >    > 	\boldsymbol{a}&		\boldsymbol{b}\\
   >    > \end{matrix} \right] ^T}{d\left[ \begin{array}{c}
   >    > 	\boldsymbol{x}\\
   >    > 	\boldsymbol{y}\\
   >    > \end{array} \right]} \right] ^T=\left[ \begin{matrix}
   >    > 	\frac{d\boldsymbol{a}}{d\boldsymbol{x}}&		\frac{d\boldsymbol{b}}{d\boldsymbol{x}}\\
   >    > 	\frac{d\boldsymbol{a}}{d\boldsymbol{y}}&		\frac{d\boldsymbol{b}}{d\boldsymbol{x}}\\
   >    > \end{matrix} \right] ^T=\left[ \begin{matrix}
   >    > 	\frac{d\boldsymbol{a}}{d\boldsymbol{x}}&		\frac{d\boldsymbol{a}}{d\boldsymbol{y}}\\
   >    > 	\frac{d\boldsymbol{b}}{d\boldsymbol{x}}&		\frac{d\boldsymbol{b}}{d\boldsymbol{x}}\\
   >    > \end{matrix} \right]$
   >
   > 7. ==以上是后续进行指数、对数映射，李代数求导，扰动模型推导的基础==；

3. 推导实践

   > 1. $SO(3)、so(3)、SE(3)、se(3)$指数与对数映射的对应关系:
   >
   >    <img src="C:\Users\Pikachu\AppData\Roaming\Typora\typora-user-images\image-20211206091042219.png" alt="image-20211206091042219" style="zoom:50%;" />
   >
   > 2. $SO(3)$上的李代数求导与左扰动模型:
   >
   >    > 1. ==李代数求导==：**用李代数表示位姿，然后根据李代数加法对李代数求导**
   >    >
   >    >    假设对一个空间点$p$进行了旋转，得到了$Rp$。
   >    >
   >    >    ==现在，要计算旋转之后点地坐标相对于旋转的导数==，记作：$\frac{\partial \left( \boldsymbol{R}p \right)}{\partial \boldsymbol{R}}$
   >    >
   >    >    由于，$SO(3)$没有加法，所以该导数没法按照导数的定义进行计算。
   >    >
   >    >    设$R$对应的李代数为$\phi$，==转而计算李代数导数==：
   >    >    $$
   >    >    \frac{\partial \left( \boldsymbol{R}p \right)}{\partial \boldsymbol{R}}=\frac{\partial \left( \exp \left( \phi ^{\land} \right) p \right)}{\partial \phi}=\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \left( \phi +\delta \phi \right) ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \  \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \left( \boldsymbol{J}_l\delta \phi \right) ^{\land} \right) \exp \left( \phi ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{\left( \boldsymbol{I}+\left( \boldsymbol{J}_l\delta \phi \right) ^{\land} \right) \exp \left( \phi ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{\left( \boldsymbol{J}_l\delta \phi \right) ^{\land}\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\boldsymbol{J}_l\delta \phi}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ =-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\boldsymbol{J}_l=-\left( \boldsymbol{R}p \right) ^{\land}p
   >    >    $$
   >    >
   >    >    > 说明：
   >    >    >
   >    >    > 第一行：李代数形式求导公式；
   >    >    >
   >    >    > 第二行：$BCH$左乘近似公式；
   >    >    >
   >    >    > 第三行：$\exp \left( \left( \boldsymbol{J}_l\delta \phi \right) ^{\land} \right)$的**一阶泰勒展开**；
   >    >    >
   >    >    > 第四行：消去同类项；
   >    >    >
   >    >    > 第五行：运用$a\times b=-b\times a$，令$a = \boldsymbol{J}_l\delta \phi,\ b = \exp \left( \phi ^{\land} \right) p$；目的是消去$\delta \phi$。
   >    >
   >    > 2. ==左扰动模型==：**对李群左乘微小扰动，然后对该扰动求导**
   >    >
   >    >    另一种求导方式：==对$R$进行一次扰动$\bigtriangleup \boldsymbol{R}$，看结果相对于扰动的变化率==；
   >    >
   >    >    以左扰动为例，设左扰动$\bigtriangleup \boldsymbol{R}$对应的李代数为$\bigtriangleup \phi$，然后，对$\bigtriangleup \phi$求导，即：
   >    >    $$
   >    >    \frac{\partial \left( \boldsymbol{R}p \right)}{\partial \left( \delta \phi \right)}=\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \left( \delta \phi \right) ^{\land} \right) \exp \left( \phi ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{\left( \boldsymbol{I}+\left( \delta \phi \right) ^{\land} \right) \exp \left( \phi ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{\left( \delta \phi \right) ^{\land}\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ =\lim_{\delta \phi \rightarrow 0}\frac{-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\delta \phi}{\delta \phi}
   >    >    $$
   >    >    $$
   >    >    \ \ \ \ \ \ \ =-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\ =-\left( \boldsymbol{R}p \right) ^{\land}
   >    >    $$
   >    >
   >    >    > 说明：
   >    >    >
   >    >    > 第一行：对李群左乘小扰动；
   >    >    >
   >    >    > 第二行：$\exp \left( \left( \delta \phi \right) ^{\land} \right)$的一阶泰勒展开；
   >    >    >
   >    >    > 第三行：消去同类项$\exp \left( \phi ^{\land} \right) p$；
   >    >    >
   >    >    > 第四行：运用$a\times b=-b\times a$，令$a = \delta \phi,\ b = \exp \left( \phi ^{\land} \right) p$；
   >
   > 3. $SE(3)$上的李代数求导与左扰动模型;
   >
   >    > 1. 李代数求导：略
   >    >
   >    > 2. 左扰动模型：
   >    >
   >    >    假设某空间点$p$经过一次变换$T$（对应李代数$\xi$），得到$Tp$。
   >    >
   >    >    现在，给$T$左乘一个扰动$\bigtriangleup \boldsymbol{T} = exp(\left( \delta \xi \right) ^{\land})$，设扰动项的李代数$\delta \xi =\left[ \begin{matrix}
   >    >    	\delta \rho&		\delta \phi\\
   >    >    \end{matrix} \right] ^T$，那么：
   >    >
   >    >     
   >    > $$
   >    >    \frac{\partial \left( \boldsymbol{T}p \right)}{\partial \left( \delta \xi \right)}=\lim_{\delta \xi \rightarrow 0}\frac{\exp \left( \left( \delta \xi \right) ^{\land} \right) \exp \left( \xi ^{\land} \right) p-\exp \left( \xi ^{\land} \right) p}{\delta \xi}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 1 \right) 
   >    > $$
   >    > $$
   >    >    =\lim_{\delta \xi \rightarrow 0}\frac{\left( \boldsymbol{I}+\left( \delta \xi \right) ^{\land} \right) \exp \left( \xi ^{\land} \right) p-\exp \left( \xi ^{\land} \right) p}{\delta \xi}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 2 \right) 
   >    > $$
   >    > $$
   >    >    =\lim_{\delta \xi \rightarrow 0}\frac{\left( \delta \xi \right) ^{\land}\exp \left( \xi ^{\land} \right) p}{\delta \xi}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 3 \right) 
   >    > $$
   >    > $$
   >    >    =\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{matrix}
   >    >    	\left( \delta \phi \right) ^{\land}&		\delta \rho\\
   >    >    	0^T&		0\\
   >    >    \end{matrix} \right] \left[ \begin{array}{c}
   >    >    	\boldsymbol{R}p+\boldsymbol{t}\\
   >    >    	1\\
   >    >    \end{array} \right]}{\delta \xi}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 4 \right) 
   >    > $$
   >    > $$
   >    >    =\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{array}{c}
   >    >    	\left( \delta \phi \right) ^{\land}\left( \boldsymbol{R}p+\boldsymbol{t} \right) +\delta \rho\\
   >    >    	0^T\\
   >    >    \end{array} \right]}{\left[ \begin{matrix}
   >    >    	\delta \rho&		\delta \phi\\
   >    >    \end{matrix} \right] ^T}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 5 \right) 
   >    > $$
   >    > $$
   >    >    =\left[ \begin{matrix}
   >    >    	\frac{\partial \left( \left( \delta \phi \right) ^{\land}\left( \boldsymbol{R}p+\boldsymbol{t} \right) +\delta \rho \right)}{\delta \rho}&		\frac{\partial \left( \left( \delta \phi \right) ^{\land}\left( \boldsymbol{R}p+\boldsymbol{t} \right) +\delta \rho \right)}{\delta \phi}\\
   >    >    	0^T&		0\\
   >    >    \end{matrix} \right] \ \ \ \ \left( 6 \right) 
   >    > $$
   >    > $$
   >    >    =\left[ \begin{matrix}
   >    >    	\boldsymbol{I}&		-\left( \boldsymbol{R}p+\boldsymbol{t} \right)\\
   >    >    	0^T&		0\\
   >    >    \end{matrix} \right] \overset{def}{=}\left( \boldsymbol{T}p \right) ^{\odot}\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \left( 7 \right)
   >    > $$
   >    >
   >    >    > 说明：
   >    >    >
   >    >    > （5）、（6）涉及矩阵求导顺序；

4. 编程实践

   1. useSophus

      > 1. 安装Sophus
      > 2. 构造$SO(3)、SE(3)$对象，并进行指数、对数映射；
      > 3. 当知道更新量后，如何对李群元素进行更新；

   2. trajectoryError

      > 1. 读取文件
      > 2. SO(3)和Rotation_matrix是一样的，Sophus::SE3d和Isometry是一样的表达；
      > 3. 计算RMSE；

5. 扩展知识

   > 1. 矩阵行列式的定义及几何意义？
   > 2. 导数的定义？
   > 3. 反对称矩阵定义、由来及理解？
   > 4. 泰勒展开？及常见函数的泰勒展开形式？
   > 5. 向量、矩阵的常见操作？
   > 6. SE(3)上的指数映射推导？

## 4. 课后习题

1. 验证$SO(3)、SE(3)和Sim(3)$关于乘法成群。

   > 1. 理解$SO(3)、SE(3)和Sim(3)$的定义；
   > 2. 乘法成群的意思是，满足群的四个性质：封闭性、结合率、幺元、逆；

2. 验证$(R^3，R，*)$构成李代数。*表示叉乘

   > 1. $R^3$表示一个三维向量$(a_1,a_2,a_3)$；
   > 2. 构成李代数的意思是，满足李代数的四个性质：封闭性、双线性、自反性、雅可比等价性；

3. 验证$so(3)和se(3)$满足李代数要求的性质。

   > 1. 理解$so(3)、se(3)$的定义；
   > 2. 李代数的四个性质；

4. 验证性质(4.20)和(4.21)。

   > 由于$\phi$是三维向量。其模长和方向，分别记作$\theta$和$a$，于是有$\phi = \theta a$；
   >
   > 1. (4.20)公式推导：
   >
   >    $a^{\land}a^{\land}=\left[ \begin{matrix}
   >    	0&		-a_3&		a_2\\
   >    	a_3&		0&		-a_1\\
   >    	-a_2&		a_1&		0\\
   >    \end{matrix} \right] \left[ \begin{matrix}
   >    	0&		-a_3&		a_2\\
   >    	a_3&		0&		-a_1\\
   >    	-a_2&		a_1&		0\\
   >    \end{matrix} \right] $
   >
   > 2. (4.21)公式推导：
   >
   >    $a^{\land}a^{\land}a^{\land}=\left[ \begin{matrix}
   >    	0&		-a_3&		a_2\\
   >    	a_3&		0&		-a_1\\
   >    	-a_2&		a_1&		0\\
   >    \end{matrix} \right] \left[ \begin{matrix}
   >    	0&		-a_3&		a_2\\
   >    	a_3&		0&		-a_1\\
   >    	-a_2&		a_1&		0\\
   >    \end{matrix} \right] \left[ \begin{matrix}
   >    	0&		-a_3&		a_2\\
   >    	a_3&		0&		-a_1\\
   >    	-a_2&		a_1&		0\\
   >    \end{matrix} \right] = -a^{\land}$
   >
   > 3. 这两个式子，提供了处理$a^{\land}$高阶项的方法。

5. 证明：

   $\boldsymbol{Rp}^{\land}\boldsymbol{R}^T=\left( \boldsymbol{Rp} \right) ^{\land}$

   > [第四讲课后习题-参考](https://blog.csdn.net/m0_38095099/article/details/105447379)

6. 证明：

   $\boldsymbol{R}\exp \left( \boldsymbol{p}^{\land} \right) \boldsymbol{R}^T=\exp \left( \left( \boldsymbol{Rp} \right) ^{\land} \right) $

   该式称为$SO(3)$上的伴随性质。同样地，在$SE(3)$上也有伴随性质：

   $\boldsymbol{T}\exp \left( \boldsymbol{\xi }^{\land} \right) \boldsymbol{T}^{-1}=\exp \left( \left( Ad\left( T \right) \xi \right) ^{\land} \right) $

   $Ad\left( T \right) =\left[ \begin{matrix}
   	\boldsymbol{R}&		\boldsymbol{t}^{\land}\boldsymbol{R}\\
   	0&		\boldsymbol{R}\\
   \end{matrix} \right] $

   >==这个伴随性质有啥意义或用处？==

7. 仿照左扰动的推导，推导$SO(3)和SE(3)$在右扰动下的导数。

   > 1. $SO(3)$右扰动模型：
   >    $$
   >    \frac{\partial \left( \boldsymbol{Rp} \right)}{\partial \left( \boldsymbol{\delta \phi } \right)}=\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \phi ^{\land} \right) \exp \left( \left( \delta \phi \right) ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    $$
   >    $$
   >    =\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \phi ^{\land} \right) \left( \boldsymbol{I}+\left( \delta \phi \right) ^{\land} \right) p-\exp \left( \phi ^{\land} \right) p}{\delta \phi}
   >    $$
   >    $$
   >    =\lim_{\delta \phi \rightarrow 0}\frac{\exp \left( \phi ^{\land} \right) \left( \delta \phi \right) ^{\land}p}{\delta \phi}
   >    $$
   >    $$
   >    =\lim_{\delta \phi \rightarrow 0}\frac{\left( \exp \left( \phi ^{\land} \right) \left( \delta \phi \right) \right) ^{\land}\left( \exp \left( \phi ^{\land} \right) p \right)}{\delta \phi}
   >    $$
   >    $$
   >    =\lim_{\delta \phi \rightarrow 0}\frac{-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\left( \exp \left( \phi ^{\land} \right) \left( \delta \phi \right) \right)}{\delta \phi}
   >    $$
   >    $$
   >    =-\left( \exp \left( \phi ^{\land} \right) p \right) ^{\land}\exp \left( \phi ^{\land} \right) \ =\ -\left( \boldsymbol{Rp} \right) ^{\land}\boldsymbol{R}
   >    $$
   >
   > 2. $SE(3)$右扰动模型：
   >    $$
   >    \frac{\partial \left( \boldsymbol{Tp} \right)}{\partial \left( \boldsymbol{\delta \xi } \right)}=\lim_{\delta \xi \rightarrow 0}\frac{\exp \left( \xi ^{\land} \right) \exp \left( \left( \delta \xi \right) ^{\land} \right) \boldsymbol{p}-\exp \left( \xi ^{\land} \right) \boldsymbol{p}}{\delta \xi}
   >    $$
   >    $$
   >    =\lim_{\delta \xi \rightarrow 0}\frac{\exp \left( \xi ^{\land} \right) \left( \boldsymbol{I}+\left( \delta \xi \right) ^{\land} \right) \boldsymbol{p}-\exp \left( \xi ^{\land} \right) \boldsymbol{p}}{\delta \xi}
   >    $$
   >    $$
   >    =\lim_{\delta \xi \rightarrow 0}\frac{\exp \left( \xi ^{\land} \right) \left( \delta \xi \right) ^{\land}\boldsymbol{p}}{\delta \xi}
   >    $$
   >    $$
   >    =\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{matrix}
   >    	\boldsymbol{R}&		\boldsymbol{t}\\
   >    	0^T&		1\\
   >    \end{matrix} \right] \left[ \begin{matrix}
   >    	\left( \boldsymbol{\delta \phi } \right) ^{\land}&		\boldsymbol{\delta \rho }\\
   >    	0^T&		0\\
   >    \end{matrix} \right] \boldsymbol{p}}{\delta \xi}\ =\ \lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{matrix}
   >    	\boldsymbol{R}&		\boldsymbol{t}\\
   >    	0^T&		1\\
   >    \end{matrix} \right] \left[ \begin{matrix}
   >    	\left( \boldsymbol{\delta \phi } \right) ^{\land}&		\boldsymbol{\delta \rho }\\
   >    	0^T&		0\\
   >    \end{matrix} \right] \left[ \begin{array}{c}
   >    	\boldsymbol{p}\\
   >    	1\\
   >    \end{array} \right]}{\delta \xi}
   >    $$
   >    $$
   >    =\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{matrix}
   >    	\boldsymbol{R}&		\boldsymbol{t}\\
   >    	0^T&		1\\
   >    \end{matrix} \right] \left[ \begin{array}{c}
   >    	\left( \boldsymbol{\delta \phi } \right) ^{\land}\boldsymbol{p}+\boldsymbol{\delta \rho }\\
   >    	0\\
   >    \end{array} \right]}{\delta \xi}=\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{array}{c}
   >    	\boldsymbol{R}\left( \boldsymbol{\delta \phi } \right) ^{\land}\boldsymbol{p}+\boldsymbol{R\delta \rho }\\
   >    	0\\
   >    \end{array} \right]}{\delta \xi}
   >    $$
   >    $$
   >    =\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{array}{c}
   >    	\boldsymbol{R}\left( \boldsymbol{\delta \phi } \right) ^{\land}\boldsymbol{p}+\boldsymbol{R\delta \rho }\\
   >    	0\\
   >    \end{array} \right]}{\left[ \begin{matrix}
   >    	\boldsymbol{\delta \rho }&		\left( \boldsymbol{\delta \phi } \right) ^{\land}\\
   >    \end{matrix} \right] ^T}=\lim_{\delta \xi \rightarrow 0}\frac{\left[ \begin{array}{c}
   >    	-\left( \boldsymbol{Rp} \right) ^{\land}\boldsymbol{R\delta \phi }+\boldsymbol{R\delta \rho }\\
   >    	0\\
   >    \end{array} \right]}{\left[ \begin{matrix}
   >    	\boldsymbol{\delta \rho }&		\left( \boldsymbol{\delta \phi } \right) ^{\land}\\
   >    \end{matrix} \right] ^T}
   >    $$
   >    $$
   >    =\left[ \begin{matrix}
   >    	\boldsymbol{R}&		-\left( \boldsymbol{Rp} \right) ^{\land}\boldsymbol{R}\\
   >    	0&		0\\
   >    \end{matrix} \right]
   >    $$

8. 搜索cmake的find_package指令是如何运作的。它有哪些可选的参数？为了让cmake找到某个库，需要哪些先决条件？

   > [参考](https://blog.csdn.net/sen873591769/article/details/90183015)

