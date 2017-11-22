# zMatrix

zMatrix 是一个使用C++编写的图像处理库，它的基础是_Matrix矩阵模板类。
<br><br>

## 特色
* C++11<br>
* 尽可能的提高可读性<br>
* zMatrix使用**类模板**来支持各种类型<br>
* 函数接口尽量和`matlab`和`opencv`类似，zMatrix类可以和openCV中的Mat类转换<br>
* 使用**引用计数**来达到**自动内存管理**的目的，不需要为内存问题担心

<br><br>

## 依赖
```
必须: jpeg fftw gtk+2.x(Linux 必须) WIN32(Windows 必须) FFmpeg
可选: Kinect opencv
```
### OpenCV
Windows && Linux
* 默认关闭
* 如果使用确认`CMake`可以找到`OpenCV`。

### FFTW
Windows
* 默认使用
* `dll`库在`./zMatrix/3rdparty/fftw`下，将`dll`添加到环境变量中

Linux
* 默认使用
* 安装libfftw3-dev

### FFmpeg
* 读取摄像头依赖

### GUI
Windows
* WIN32 API

Linux
* GTK+ 2.x


### Kinect
* 默认关闭
* `Kinect`模块使用的`OpenCV`，使用前保证`Kinect`和`OpenCV`的环境均配置好了

## 生成工程
Windows && Linux
```
    mkdir build
    cd build
    cmake .. -DCMAKE_INSTALL_PREFIX=<path>
```

<br><br>

## Visual Studio插件推荐
`Image Watch`:可以在新窗口以图片的形式显示`cv::Mat`类型数据，非常方便调试。<br>
如果要支持`z::Matrix`类型的显示，使用`resources/ImageWatch/ImageWatchOpenCV.natvis`替换插件的配置文件。<br>
如果要显示自定义数据结构，Visual studio官网查看natvis文件的配置格式。

`ForceUTF8(no BOM)`:文件保存为utf8格式

<br><br>

## 已经实现功能

### 矩阵的基本功能
* 没有实现求秩和求逆

### 图像的读写
* 暂时只支持**jpeg**的读取和写入

### 读取摄像头
* 使用FFmpeg支持在Linux上读取摄像头(v4l2)

### 图像处理相关
#### 基础
* 颜色空间转换`cvtColor()`，BRG->RGB, BGR->GRAY, BGR->HSI, BGR->HSV

#### 线性滤波
* 方框滤波函数`boxFilter()`
* 均值滤波函数`blur()`
* 高斯滤波函数`GassionBlur()`

#### 非线性滤波
* 中值滤波函数`medianBlur()`
* 双边滤波函数`bilateralFilter()`

#### 形态学滤波
* 腐蚀和膨胀函数`erode()/dilate()`
* 开运算、闭运算、顶帽、黑帽、形态学梯度运算，函数`morpEX()`

#### 图像变换
* `sobel()`算子
* 简单的`canny`边缘检测，彩色和灰度均可，效果不好

#### 离散傅里叶变换
* 默认使用`FFTW`来实现
* 自己实现的基2快速傅里叶变换

#### 图像轮廓
* 寻找轮廓：`findContours()` 和 `findOutermostContours()`

#### 阈值
* 单通道固定值阈值：`threshold()`

#### 图像金字塔
* 对图像上采样函数：`pyrUp()`
* 对图形下采样函数：`pyrDown()`

### Kinect 4 Windows v2 （Events）
* Kinect获取深度、彩色和红外图像，返回`cv::Mat`类型的数据

<br><br>
<br>