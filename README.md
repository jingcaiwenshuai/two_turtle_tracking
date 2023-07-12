# 两只乌龟跟随仿真
---
## 实现功能：键盘控制第一只乌龟运动，第二只乌龟自动跟随并到达第一只乌龟的位置（但不是轨迹跟踪）
## 实现步骤
1. 调用ros服务新建一只小乌龟GUI
2. 发布两只乌龟对于world的tf坐标系信息
3. 通过两只乌龟与world的坐标关系，计算得出两只乌龟的tf坐标变换，针对该tf发布第二只乌龟的cmd_vel信息
---
## 在读者电脑下的仿真操作
1. #创建工作空间
```
mkdir -p ~/catkin_ws/src
```
2. #catikin初始化工作空间
```
catkin_init_workspace
```
3. #克隆包到当前(src)文件夹下
```
git clone https://github.com/jingcaiwenshuai/two_turtle_tracking.git
```
4. #退回到工作空间目录下
```
cd ..
```
5. #编译
```
catkin_make
```
6. #soure工作空间
```
source devel/setup.bash
```
7. #运行launch文件
 ```
roslaunch step3_control_turtle2 two_turtle_tracking.launch 
```
8. #在当前终端“上下左右”键即可控制第一只乌龟运动，并实现第二只乌龟跟随
