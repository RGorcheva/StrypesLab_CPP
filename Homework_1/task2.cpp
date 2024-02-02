/*
Задача 2. Напишете програма, която порчита 2 цели числа от стандартния вход - sum и count. 
Програмата трябва да намери count на брой последователни числа, чиято сума е точно sum. 
Ако няма такива да изведе подходящо съобщение, че няма. 
Не използвайте масиви за решението на задачата!
*/

#include <iostream>

void print_count_numbers_with_sum(int count, int sum)
{
    int sum_min{0};
    for (int i = 1; i <= count; i++)
    {
        sum_min += i;
    }
    int interval = sum - sum_min;
    if (interval % count != 0)
    {
        std::cout << "There are no " << count << " consecutive numbers which sum is " << sum << "!" << std::endl;
        return ;
    } 
    int offset = interval/count;
    std::cout << "There are " << count << " consecutive numbers which sum is " << sum << ":" << std::endl;
    for (int i = 1 + offset; i < 1 + offset + count; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main()
{
    int count{0};
    int sum{0};

    std::cout << "count = ";
    std::cin >> count;
    std::cout << "sum = ";
    std::cin >> sum;

    print_count_numbers_with_sum(count, sum);

    return 0;
}