#include <iostream>
#include "../lib/set.h"

int main()
{
    Set set;
    int code, val;

    do
    {
        std::cout << "[0]Exit/[1]Add/[2]Contains/[3]Remove/[4]Size/[5]Display: ";
        std::cin >> code;
    
        if (code < 0 || code > 5)
            std::cout << "Invalid call code\n";
        else if (code == 5)
        {
            std::cout << "Values: ";
            print(set);
            std::cout << "\n";
        }
        else if (code == 4)
            std::cout << "Size: " << set.len() << "\n";
        else if (code == 3)
        {
            std::cout << "Value: ";
            std::cin >> val;
            if (!set.remove(val)) std::cout << "Value is not present\n";
        }
        else if (code == 2)
        {
            std::cout << "Value: ";
            std::cin >> val;
            if (!set.contains(val)) std::cout << "Value is not present\n";
            else std::cout << "Value is present\n";
        }
        else if (code == 1)
        {
            std::cout << "Value: ";
            std::cin >> val;
            if (!set.add(val)) std::cout << "Value is present\n";
        }
    }
    while (code != 0);

    return 0;
}
