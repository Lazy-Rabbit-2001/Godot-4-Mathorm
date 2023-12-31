[English](README.md) | **中文版（当前页面）**
# Godot 4 Mathorm
基于GDExtension而开发的数学库，同时也是部分GDExtension的开发前置

# 安装
1. 将本工程克隆到任意文件夹下，复制其中的`gdextension`文件夹
2. 打开你的游戏工程文件所在目录（即project.godot文件所在目录）
3. 将已复制好的`gdextension`文件夹粘贴在该目录下

# 简介
`Mathorm`一词为本人自造词，由"Math"和"storm"二词拼缀而来。`Mathorm`继承自`RefCounted`类，为GDScript中部分高频超量计算提供优化版本的数学库计算

## 微积分
`Calculus`类在开发时遇到涉及变化率、数据分析等领域时十分有用。该类中每个方法都自带一个`samples`参数，用于控制微积分结果的精度，该值越高，结果越精确。 本类中的`get_integral_definite()`和`get_derivative_at()`也需要传入一个`Callable`类型的参数`function`。**注意**：这里传入的`function`**只能传入一个**参数，且该参数及返回值**必须为`float`类型**，否则将会导致不可预测的后果。  

## 2D变换矩阵算法
`Transform2DAlgo`类为引擎内置的`Vector2`类型和`Transform2D`类型提供更多**相关**方法，如`get_projection_limit()`，该方法会返回一个向量在另一个向量上的投影，且该投影的长度有一定限制。现已用于[`EntityBody2D`的`move_and_slide()`方法中](https://github.com/Lazy-Rabbit-2001/Godot-4-EntityBody2D).

## 椭圆线
`Ellipse`几何类型能够让你无中生‘椭’，同时提供了一系列方法能够让你获取到该椭圆的半长/短轴、离心率、面积以及周长等信息，也支持旋转椭圆的操作，还可以让你获取在椭圆上的一个点

更多方法将会在未来版本中实装

# 安装需求
## 支持的Godot版本
4.2及以上

## 支持的开发系统及平台
Windows 10, 11 x86-64
