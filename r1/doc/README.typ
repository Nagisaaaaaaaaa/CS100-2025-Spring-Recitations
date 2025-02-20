#set text(font: ("LXGW WenKai"))
// #set text(font: ("linux libertine", "楷体"))
#set par(justify: true)
#set heading(numbering: "1.1.1.")
#set math.equation(numbering: "(1)")

//
//
//
= 让我们用 `printf` 创作些好看的东西吧

+ 如果在 windows 上，请先运行 `bash`
+ `gcc main.c -o main.exe`
+ `LANG=C.UTF-8 ./main.exe > image.ppm`
+ `python show.py image.ppm`

= 不想每次都打这么多字

+ `python go.py main.c`
