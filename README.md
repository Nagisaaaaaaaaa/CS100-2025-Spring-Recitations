# CS100 2025 Spring Recitations

## Introduction

以下是每次复习课的补充材料。虽然它们是非官方的实验性内容，并且与作业、quiz、考试没有任何关系，甚至我们每次只会在复习课的最后简单提一嘴，但它们绝对是实用且规范的好例子。我们设计它们的初衷是希望各位能一边享受 C/C++ 编程，一边丰富自己的工程经验。不妨关闭 Copilot 之类的 AI 工具，一行一行地对着代码抄一遍，会有所收获的。

为了保证代码简洁、可读，我们只完全兼容了 Windows，存在一些实现无法在 Linux 等操作系统上直接运行。但请不要慌，这些小问题都是相当好解决的，比如只需要删除 `.exe` 这些后缀即可。如果您碰到难以解决的问题，我们随时欢迎反馈。

## Supp 1: Hello Painter

我们将学习如何使用 `printf` 来作画。

<img src="r1/supp/image.png" style="zoom: 100%;" />

## Supp 2: Hello Primitive

我们将学习如何在图上画圆、椭圆、长方形。

<img src="r2/supp/image.png" style="zoom: 100%;" />

## Supp 3: Hello Fractal

我们将学习如何绘制[分形](https://en.wikipedia.org/wiki/Fractal)。

<img src="r3/supp/image.png" style="zoom: 25%;" />

## Supp 4: Hello Animation

我们将学习如何制作[动画](r4/supp/video_high_quality.mp4)。

<img src="r4/supp/image.png" style="zoom: 100%;" />

## Supp 5: Hello Macro

我们将学习如何实现强大、实用的宏，例如让同一个宏能够接收不同数量的参数、做不同的事情。
```c
// 接收一个参数。
MY_ASSERT(a == 1);
// 接收两个参数，第二个参数是失败时会打印的信息。
MY_ASSERT(a == 1, "杂鱼♥～杂鱼♥～，才不会告诉你 `a` 应该等于 1 呢♥");
```
