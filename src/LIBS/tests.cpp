#include <iostream>
#include <vector>

int main()
{
    int x = 0;
    x |= (1<<1);
    x |= (1<<3);
    x |= (1<<4);
    x |= (1<<8);
    for (int i = 0; i < 32; i++) {
        if (x&(1<<i)) std::cout << i << " ";
    }
    std::cout << x;
}