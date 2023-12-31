**English(current)** | [中文版](zh_cn.md)
# Godot 4 Mathorm
A GDExtension-based math library, and some of gdextensions needs this as dependency before their development of those gdextensions.

# How to Install?
1. Clone the repo to any folders and copy the `gdextension` folder
2. Go into the directory of your project where a `project.godot` exists
3. Paste the folder you just copied to the directory

# How it Works
`Mathorm` is a self-made word blended from "Math" and "storm", which is a mathlib and contains set of `RefCounted` classes that you can use for enormous and frequent calculations in GDScript.

### Calculus
`Calculus` is a useful class when you want to analyse data and function deltas. Each function in this class contains a parameter `samples`, which makes you manually adjust the accuracy the reuslt will be. The higher the value of `samples` is, the more accurate the result will be given.  
In methods `get_integral_definite()` and `get_derivative_at()`, there are `function` parameters, a Callable that you need to input. **BE CAREFUL:** The method you input should and can contain **ONLY ONE PARAMETER** and the type of both the parameter and the returned value **SHOULD BE `float`**, otherwise it will cause unexpected results.

### Transform2DAlgo
`Transform2DAlgo` is a class that provide extra methods related to `Vector2` and `Transform2D`, like `get_projection_limit()`, which returns a `Vector2` projecting onto another 2d vector and limit its length. This is used in [EntityBody2D's `move_and_slide()`](https://github.com/Lazy-Rabbit-2001/Godot-4-EntityBody2D).

### Ellipse
`Ellipse` is a geomentry class that allows you to perform an ellipse from zero. In this class, you can get its half long/short axis, eccentricity, area and cirumference by calling relative methods. Also, you can even rotate the ellipse and get a point on it.

More classes methods will be implemented in the future

# Requirements
## Supported Godot Versions
4.2 or above

## Supported developing platforms
Windows 10, 11 x86-64
