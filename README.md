# 大纲
只包含 Rendering 相关的部分，几何造型不感兴趣所以没做（~~不是懒~~

大部分注释都是用英文写的——因为感觉写英文注释更顺手一点，因为这个课程本身就是 UC Santa Barbara 的 CS180/CS280* 直接平移过来的。
> *Fun Fact: UC Berkeley 教的也其实差不多，一些课件的内容甚至是 literally 地完全一致233（如果你感兴趣，伯克利的那个课程的编号是 CS 184/284A，也很值得一看。

> [!NOTE]
> GAMES101 的课程作业在对应标题内容的下一节课放出，并且在下一节课通常会有重要知识补充。

> 例如 hw3 需要的法线计算实际上是在 Lecture 10 Geometry 1 (Introduction) 的前半部分介绍的，而不是在 Lecture 09 Shading 3 (Texture Mapping Cont.) 的部分。

- hw1：**旋转矩阵**和**透视投影矩阵**。
  
  - Lecture 01 Overview of Computer Graphics
  - Lecture 02 Review of Linear Algebra
  - Lecture 03 Transformation
  - Lecture 04 Transformation Cont.
 
<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw1/images/output1.png" width="234" height="238">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw1/images/output2.png" width="234" height="238">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw1/images/output3.png" width="234" height="238">
</p>
    
- hw2：**光栅化**和 **Z-Buffer** 算法。

  - Lecture 05 Rasterization 1 (Triangles)
  - Lecture 06 Rasterization 2 (Antialiasing and Z-Buffering)

<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw2/output.png" width="351" height="357">
</p>

- hw3：**图形流水线**、**着色器**、**纹理映射**、**局部光照模型（Blinn-Phong）等**

  - Lecture 07 Shading 1 (Illumination, Shading and Graphics Pipeline)
  - Lecture 08 Shading 2 (Shading, Pipeline and Texture Mapping)
  - Lecture 09 Shading 3 (Texture Mapping Cont.)

<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw3/images/output_normal.png" width="230" height="230">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw3/images/output_phong.png" width="230" height="230">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw3/images/output_texmappedwithphong.png" width="230" height="230">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw3/images/output_bump.png" width="230" height="230">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw3/images/output_displacement.png" width="230" height="230">
</p>

- hw5：**递归式光线追踪** - **光线方程** $r(t) = \vec{o} + t \vec{d}$、**成像平面上各像素的光线**、**光线-三角形求交（Ray-Tri intersection）** （Moller-Trumbore 算法）

  - Lecture 13 Ray Tracing 1

<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101/blob/main/hw5/image/binary.png" width="640" height="480">
</p>

- hw6：**光线追踪加速结构** - **光线-包围盒求交（Ray-Box intersection）**、**层次包围盒（BVH）遍历**

  - Lecture 14 Ray Tracing 2

<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101-projects/blob/main/hw6/image/bvh.png" width="640" height="480">
</p>

- hw7：**路径追踪（Path Tracing）**

  - Lecture 15 Ray Tracing 3
  - Lecture 16 Ray Tracing 4
  - Lecture 17 Materials and Appearances
  - Lecture 18 Advanced Topics in Rendering
 
...
*The Rendering Equation is:*
$$
L_o(\mathbf{x}, \omega_o) = L_e(\mathbf{x}, \omega_o) + \int_{\Omega} f_r(\mathbf{x}, \omega_i, \omega_o)\, L_i(\mathbf{x}, \omega_i)\, (\omega_i \cdot \mathbf{n}) \, d\omega_i
$$
...

>摘自 James T. Kajiya 发表于 SIGGRAPH 1986 的论文《The Rendering Equation》，符号形式有调整。

**“名字越短，事情越大。”——Lingqi Yan**


# 构建
## Windows 11 (x86-64)
**你需要安装**：
- Windows Subsystem for Linux 2 (WSL 2)
  - 🐧安装一个 Linux 发行版（<img src="https://cdn.simpleicons.org/archlinux/1793D1" height="25"/>Arch Linux, <img src="https://cdn.simpleicons.org/ubuntu/E95420" height="25"/>Ubuntu, etc.）
- <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/clion/clion-original.svg" height="25"/> JetBrains CLion

接着，在 Linux 下安装必要的 C++ 开发工具（CMake, 编译器等）：
```shell
sudo apt install build-essential
unzip cmake
```

安装 GAMES101 所需的 **OpenCV** 计算机视觉库和 **Eigen** 向量数学库：
```shell
sudo apt install libeigen3-dev libopencv-dev
```

在 CLion 里进行如下配置：
<p align="center">
  <img src="https://github.com/BlueMicro233/GAMES101-projects/blob/main/assets/toolchain.png" width="737" height="550">
</p>

## macOS (aarch64)
和 Linux 那边的步骤差不多（OpenCV, Eigen），并且在 CLion 里不需要额外配置工具链，只是 CMakeList.txt 需要改（可以交给 LLM 完成）。

# 碎碎念
GAMES101 是最好的中文图形学课程，不接受反驳。学习这门课程可以对图形学（尤其是闫老师的课很注重 Rendering 这块）在做什么有个自上而下的基础认知，不像国内很多图形学课从盘古开天辟地给你讲理论，结果到最后什么都不懂。

闫老师的授课给人一种亲切和有趣感，这种拉近听众与学科之间距离是很多**课程**难以做到的（当然也有图形学本身就散发魅力的原因）。由于图形学的确有难度，有趣和好玩的体验其实蛮重要的。

做这些作业是真的挺有必要的（因为学的是**计算机**图形学，怎么能少得了代码实现？）。不过有人会说：“**助教框架都写好了，学生基本上就是在实现一些接口，学到了什么？**” 此言差矣！
你要知道现在的历史情境下，图形学造轮子比以前还更没用了（工业界在近几十年积累了大量优秀的成品，现在更是 LLM 飞速发展）。**只有高效地掌握核心思想的人才能达成最好的学习**。

同时笔者还认为，这种规模的作业正适合以前从未接触过正经 C++ 项目的大一大二学生拿来作为基本的工具链入门。

虽然笔者在两年多以前就接触到了这个神课，并且刷了不止一遍。但是作业还真没认真做过，由于之前上高中并没有时间配环境和写代码，现在得赶紧补上了（（（
