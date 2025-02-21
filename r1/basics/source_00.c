#include <stdio.h>

/*

This piece of source code corresponds to:
Recitaion Slide 01 - Historical Artifacts of C - Empty Parameter List.

*/

// Accepts anything. Always returns 42.
int always_42(){
    return 42;
}

// Accepts nothing. Always returns 666.
int always_114514(void){
    return 114514;
}


int main(void){
    // "always_42" accepts "anything", which includes an void input.
    int x = always_42();
    // Or you can give him some parameters when calling. Won't make any difference.
    int y = always_42(1, 2, 3, "dummy params");
    // "always_666" explicity uses "void". So no parameters will be allowed when calling.
    int z = always_114514();
    // You can try give it parameters and see what happens.
    // int _ = always_666("try any param");
    printf("x = %d\ny = %d\nz = %d\n", x, y, z);
}