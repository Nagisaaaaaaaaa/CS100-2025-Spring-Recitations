#set text(font: ("LXGW WenKai"))
// #set text(font: ("linux libertine", "楷体"))
#set par(justify: true)
#set heading(numbering: "1.1.1.")
#set math.equation(numbering: "(1)")

= 运行我们的小程序

+ 如何在 windows 上，先运行 `bash`
+ `gcc main.c -o main.exe`
+ `LANG=C.UTF-8 ./main.exe > image.ppm`
+ `python show.py image.ppm`

= 把它们整合起来

+ `python go.py main.c`
