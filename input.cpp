#include <stdio.h>

int foo()
{
    printf("Foo");
    return 0;
}

__attribute__((section("Secure"))) int world()
{
    printf("World");
    return 0;
}

int hello()
{
    printf("Hello");
    world();
    hello();
    hello();
    return 0;
}

int main()
{
    int a = foo();
    int (*fptr)();
    fptr = foo;
    hello();
    world();
    fptr();
    return 0;
}