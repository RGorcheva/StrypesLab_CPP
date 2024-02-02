/*
Задача 4. Напишете функция andAll която приема 2 цели числа M и N, M <= N. 
Функцията трябва да намери резултата от прилагането на побитово "и" (&) на всички числа в интервала [M, N].
Напишете програма която прочита цяло число N от входа. Програмата трябва да намери първите N прости числа. 
За всеки 2 последователни прости числа P1, P2 изведете andAll(P1, P2).
*/

#include <iostream>

void sort_asscending(int *a, int *b)
{
    if( *a > *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
}

int bit_and(int a, int b)
{
    return a & b;
}

void and_all(int M, int N)
{
    sort_asscending(&M, &N);
    std::cout << "bitwise & between " << M << " and " << N << std::endl;
    for (int i = M; i < N; i++)
    {
        std::cout << "bit_and(" << i << "," << i + 1 << ") = " << bit_and(i, i+1) << std::endl;
    }
}

bool is_a_prime_number(int n)
{
    int count{1};
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i <= n; i++)
    {
        if (n % i == 0)
        {
            count++;
            if (count > 2)
            {
                return false;
            }
        }
    }
    return true;
}

void find_first_N_primers(int n)
{
    if (n <= 1)
    {
        std::cout << "N must be a positive integer number, greater than 1!" << std::endl;
        return;
    }
    int previous{2};
    int current{0};
    int count{1};
    for (int i = 3; count < n; i++)
    {
        if (is_a_prime_number(i))
        {
            current = i;
            and_all(previous, current);
            count++;
            previous = current;
        }
    }
}

int main()
{
    int N{0};
    std::cout << "N = ";
    std::cin >> N;

    find_first_N_primers(N);

    return 0;
}