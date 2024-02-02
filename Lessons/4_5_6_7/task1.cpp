//4:Numeric systems
//5: Data types
#include <iomanip>
#include <iostream>

int f5()
{
    int x; //bad practice, to be initialized!!!
    x = 5;
    std::cout << "x=";
    std::cin >> x;
    double d = 0.14; // initialized true copy and assigninig;
    float f{0.5f}; //new way of initialization
    std::cout << "x = " << x << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "d = " << std::setprecision(20) << d << std::endl;
    std::cout << "0.1 + 0.2 = " << (0.1 + 0.2) << std::endl;

    int z{5};
    //int z{5.5}; - error
    int n{}; //zero initialization;
    bool b{};

    //Naming Conventions:
    int num_apples; //snake_case
    int numApples; //camelCase

    return 0;
}

//7: Conditional statements, Loops

int f7()
{
    int x = 0;
    if (true && false)
    {
        x = 10;
    } else if (5)
    {
        x = 5;
    }
    std::cout << "x = " << x << std::endl;

    while (x > 0)
    {
        --x;
        std::cout << "x = " << x << std::endl;
    }
    for (int i = 0; i < 5; i++)
    {
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

    



//8: Pointers

int f8()
{
    for (int i = 1; i <= 10; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    int i = 1;
    while (i <=10)
    {
        std::cout << i << " ";
        i++;
    }
    std::cout << std::endl;
    i = 1;
    do
    {
        std::cout << i << " ";
        i++;
    } while (i <= 10);
    std::cout << std::endl;

    double input;
    std::cin >> input;
    std::cout



    return 0;
}

int main()
{
    f5();
    f7();
    f8();
    return 0;
}