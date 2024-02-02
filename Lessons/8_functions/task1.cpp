#include <iostream>
#include <cmath>

void validateAndSqrt(double a)
{
    if (value >= 0)
    {
        std::cout << sqrt(a) << std::endl;
    }
    else
    {
        std::cout << "Input is negative!" <<std::endl;
    }
}

int main()
{
    while (true)
    {
        char input;
        double value;
        std::cout << "Enter q for exit, other to continue: ";
        std::cin >> input;
        if (input == 'q')
        {
            std::cout << "Closing program!" << std::endl;
            break;
        }
    }
}