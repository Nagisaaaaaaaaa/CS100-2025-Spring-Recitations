#include <stdio.h>

/*

This piece of source code corresponds to:
Recitaion Slide 01 - Historical Artifacts of C - Undeclared functions.
You should check different behaviors between C and C++ compilers yourself!

In the "main" function, an undeclared (thus of course undefined) function
is called. If you are using IDE or something like clangd, you should have 
noticed some warning signs, such as red underline, telling you that something
is wrong.

Then let's try two different way of compiling this "wrong" code.
Open your terminal("Ctrl + `" if you are using VSCode) and enter current folder.

1. Try "gcc source_01.c".

2. Try "g++ source_01.c".

*/

int main(void){
    int x = function_undeclared();
    printf("%d\n", x);
    return 0;
}

/*

Neither of them will be compiled and generate executable, which is fully expected. 
Now pay attention to the difference between these two return messages.

When you use "gcc.exe" to compile, you should see a WARNING made by compiler 
and then a ERROR made by linker ("ld.exe" -the GNU linker).
While using "g++.exe", everything terminates in the compilation phase, with
an ERROR telling you 'function_undeclared' was not declared in this scope.

Why is that?

In C, when you call a function that is not declared, the compiler doesn’t 
know about it during the compilation phase. The C compiler will let the code 
pass through but then fails during the linking phase because it can’t find 
the definition of that function (the linker tries to link the function call to 
its definition, but it doesn't exist).

In C++, the compiler checks everything more thoroughly during compilation. 
It wants to make sure that when a function is called, it has already been 
declared or defined. So, if there’s an undeclared function, the C++ compiler 
will report an error at compile-time, before moving on to the linking phase.

** Main Difference ** 
C++ compilers are more strict at compile time to catch errors early, 
while C compilers are more lenient and let some issues be caught later during linking.

*/