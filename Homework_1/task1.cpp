/*
Задача 1. Напишете програма която прочита 3 реални числа N, x и y. N е размерът на фигурата, 
а x и y са координатите на точка. За тази точка трябва да изведете какво е положението ѝ спрямо 
фигурата: вътре, извън, върху контура.
*/

#include <iostream>
#include <cmath>

#define EPS 0.0001

//Function check if two doubles are near enough 
bool are_doubles_equals(double a, double b)
{
    if (EPS > fabs(a - b))
    {
        return true;
    }
    return false;
}

/*Function check if a point is in, out or on the figure.
  Function returns :
  1 - the point is in figure
  0 - the point is on the figure 
 -1 - the pointis outside the figure*/
int point_position_in_figure(double N, double x, double y)
{
    N = fabs(N);
    if (are_doubles_equals(x * y, 0.0) || x * y > 0.0) //x*y >= 0
    {
        double ax = fabs(x);
        double ay = fabs(y);
        if (ax < N && ay < N)
        {
            return 1;
        }                //(|x| == |N| && |y| <= |N|) || (|y| == |N| && |x| <= |N|)
        else if ((are_doubles_equals(ax,N) && (are_doubles_equals(ay,N) || ay < N)) || (are_doubles_equals(ay,N) && (are_doubles_equals(ax,N) || ax < N)))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
    else 
    {              //N = sqrt(x*x + y*y)
        if (are_doubles_equals(N,sqrt(pow(x,2.0) + pow(y,2.0))))
        {
            return 0;
        }          //N > sqrt(x*x + y*y)
        else if (N > sqrt(pow(x,2.0) + pow(y,2.0)))
        {
            return 1;          
        }
        else
        {
            return -1;
        }
    }
}

int main()
{
    double N{0.0};
    double x{0.0};
    double y{0.0};
    std::cout << "N = ";
    std::cin >> N;
    std::cout << "Enter coordinates: (x,y) = ";
    std::cin >> x >> y;
    //Prowerki!!!!
    switch (point_position_in_figure(N,x,y))
    {
        case 1: std::cout << "The point (" << x << "," << y << ") is inside the figure!" << std::endl; break;
        case -1: std::cout << "The point (" << x << "," << y << ") is outside the figure!" << std::endl; break;
        case 0: std::cout << "The point (" << x << "," << y << ") is on the contour of the figure!" << std::endl; break;
        default: break;
    }
    return 0;
}