[toc]

# 第5讲 相机与图像

## 1. 目标

1. 理解针孔相机的模型、内参与径向畸变参数；
2. 理解一个空间点是如何投影导相机成像平面的；
3. 掌握OpenCV的图像存储与表达方式；
4. 学会基本的摄像头标定方法；

## 2. 知识点

1. 相机模型

   * 针孔相机模型
   * 畸变模型：径向和切向畸变

2. 单目相机成像过程

   > 世界坐标系    ->    相机坐标系     ->     归一化平面(根据畸变参数计算畸变后的坐标)     ->    像素坐标系

3. 双目相机成像模型

4. RGB-D相机原理：红外结构光和飞行时间。

5. 扩展：

   * 相机标定原理、分类及程序；
   * 单目深度估计；
   * 双目视差图算法；

## 3. 实践

1. 安装OpenCV；
2. ImageBasis
   1. 读取图片
   2. 基本操作
   3. 遍历图像像素
3. undistortImage
   1. 求归一化平面上，畸变后正确的坐标；
   2. ==畸变模型公式==：
   3. 比较手动去畸变和opencv自带去畸变undistort函数，opencv自带函数略快；
4. stereoVision
   1. ==如何求视差==，SGBM算法；
   2. **深度彩色图**；
5. jointMap
   1. 已知深度图及图像间的外参，建立点云地图；
   2. 根据内参，计算每一对RGB-D图像对应的点云；
   3. 根据各张图的相机位姿（外参），把点云加进来，组成点云地图；（==会不会有重复加进去的点呢？==）
   4. 显示三维点云；

## 4. 课后习题

1. 寻找一部相机（你的手机或笔记本的摄像头即可），标定它的内参。

   你可能会用到标定板，或者自己打印一张标定用的棋盘格；

   > 1. 标定方法：
   >    1. Matlab -> Camera Calibration工具箱
   >    2. ROS      -> [官方参考](http://wiki.ros.org/camera_calibration)
   > 2. [相机标定原理与步骤](https://blog.csdn.net/baidu_38172402/article/details/81949447?ops_request_misc=&request_id=&biz_id=102&utm_term=%E7%9B%B8%E6%9C%BA%E6%A0%87%E5%AE%9A%E5%8E%9F%E7%90%86&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-81949447.pc_search_mgc_flag&spm=1018.2226.3001.4187)
   > 3. 张正友标定法；
   > 4. [相机标定-标定图片拍摄规范](https://jensen-lee.blog.csdn.net/article/details/83861288)

2. 叙述相机内参的物理意义。

   如果一个相机的分辨率变为原来的两倍，而其他地方不变，那么它的内参将如何变化？

   > 1. 物理意义：一点从相机坐标系到像素坐标系上的坐标变换；
   >
   > 2. 相机内参如何变化：
   >
   >    <img src="https://img-blog.csdnimg.cn/20191122144802340.png" alt="在这里插入图片描述" style="zoom:50%;" />
   >
   >    > u的单位是像素，其物理意义为世界坐标系下的点在像素平面的投影；
   >    >
   >    > 当分辨率变为原来的两倍，公式左右都乘以2；
   >    >
   >    > 然而三维世界坐标并未变化，所以焦距的值和主点的坐标值都会增加一倍；

3. 搜索特殊相机（鱼眼或全景相机）的标定方法。它们与普通的针孔模型有何不同？

   > 1. [转：鱼眼相机标定以及OpenCV实现](https://blog.csdn.net/u010784534/article/details/50474371)

4. 调研全局快门（global shutter）相机和卷帘快门（rolling shutter）相机的异同。

   它们在SLAM中有何优缺点？

   > [转：区别](https://blog.csdn.net/abcwoabcwo/article/details/93099982)

5. RGB-D相机是如何标定的？以Kinect为例，需要标定哪些参数？

   （参照https://github.com/code-iai/iai_kinect2）

6. 除了示例程序演示的遍历图像的方式，你还能举出哪些遍历图像的方法？

   > 主要有这几种：
   >  1.一个一个点读取的方法：image.at<uchar>(i,j);
   >
   > 2.指针遍历：Mat图像在内存中连续排布可以用 image.Ptr<uchar>()指针遍历；(用的最多)
   >
   > 3.迭代器遍历：利用cv里的iterator进行遍历。

7. 阅读OpenCV官方教程，学习它的基本用法。

