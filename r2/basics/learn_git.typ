#set text(font: ("LXGW WenKai"))
// #set text(font: ("linux libertine", "楷体"))
#set par(justify: true)
#set heading(numbering: "1.1.1.")
#set math.equation(numbering: "(1)")

//
//
//
= 初次使用 git

- 随便找个地方，新建文件夹 `LearnGit`

- 在 `LearnGit` 目录下打开 terminal
  ```bash
  git init
  ```

- 在 `LearnGit` 目录下新建 `main.c` 
  ```c
  #include <stdio.h>

  int main(void) {
    printf("Hello World!\n");

    return 0;
  }
  ```

- 将 `main.c` 暂存 (添加到购物车)
  ```bash
  git add main.c
  ```

- 将暂存的内容提交到本地仓库 (付款，清空购物车)
  ```bash
  git commit -m "Add `main.c`."
  ```

- 看看我们的提交历史 (购买记录)
  ```bash
  git log
  ```

//
//
//
= 做一些修改并再次提交

- 对 `main.c` 做一些修改
  ```c
  #include <stdio.h>

  void SayHello(void) {
    printf("Hello World!\n");
  }

  int main(void) {
    SayHello();

    return 0;
  }
  ```

- 再次提交
  ```bash
  git add main.c
  git commit -m "Add `SayHello`."
  ```

- 看看我们的提交历史
  ```bash
  git log
  ```

- 看看老版本的代码
  ```bash
  git checkout master^
  ```

- 回到新版本的代码
  ```bash
  git checkout master
  ```

- 看看当前版本和老版本的区别
  ```bash
  git diff master^
  ```

//
//
//
= 再做一些修改

- 对 `main.c` 再做一些修改
  ```c
  #include <stdio.h>

  void SayHello(void) {
    printf("Hello World!\n");
  }

  void SayQAQ(void) {
    printf("QAQ.........\n");
  }

  int main(void) {
    SayHello();
    SayQAQ();

    return 0;
  }
  ```

- 再次提交
  ```bash
  git add main.c
  git commit -m "Add `SayQAQ`."
  ```

- 看看我们的提交历史
  ```bash
  git log
  ```

- 在这三个版本之间切换
  ```bash
  git checkout master^^
  git checkout master^
  git checkout master
  ```

- 看看这几个版本之间的区别
  ```bash
  git diff master^
  git diff master^^

  git diff master^ master
  git diff master^^ master
  git diff master^^ master^
  ```

//
//
//
= 使用 VSCode 插件

- 安装 GitLens 插件

- 点击 VSCode 左侧的 Source Control 图标

- 点击 GitLens 栏目
