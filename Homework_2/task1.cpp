#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>

const double EPS{0.0001};
const int g_number_of_symb{12};

//Function check if two doubles are near enough 
bool are_doubles_equals(const double a, const double b)
{
    if (EPS > fabs(a - b))
    {
        return true;
    }
    return false;
}

void configure_progress_bar(
    char* arr,
    int arr_size,
    const double current_progress,
    const int number_of_symb = g_number_of_symb,
    const bool show_progress = true,
    const char left_symb = '[',
    const char right_symb = ']',
    const char full_symb = '=',
    const char empty_symb = ' ')
{
    int number_of_full_symbols = int(ceil(current_progress * double(number_of_symb)));
    int number_ot_progress_num_symb{4};
    arr[0] = left_symb;
    if (show_progress)
    {
        sprintf(&arr[number_of_symb / 2 + 1], "%3d%%", int(ceil(current_progress * 100.00))); // 4 symbols
        int i = 1;
        for (; i <= number_of_full_symbols; i++)
        {
            if (i == number_of_symb / 2 + 1)
            {
                number_of_full_symbols += number_ot_progress_num_symb;
                i += number_ot_progress_num_symb;
            }
            arr[i] = full_symb;
        }
        for (; i <= arr_size - 3; i++)
        {
            if (i == number_of_symb / 2 + 1)
            {
                i += number_ot_progress_num_symb;
            }
            arr[i] = empty_symb;
        }
        arr[i] = right_symb;
        arr[arr_size-1] = '\0';
    }
    else
    {
        int i = 1;
        for (; i <= number_of_full_symbols; i++)
        {
            arr[i] = full_symb;
        }
        for (; i <= number_of_symb; i++)
        {
            arr[i] = empty_symb;
        }
        arr[arr_size - 7] = right_symb;
        sprintf(&arr[arr_size - 6], "%3d%%", int(current_progress * 100.00)); //copy array with 5 symbols
    }
}

void implement_progress(int seconds)
{
    double current_progress{0.0};
    int arr_size = g_number_of_symb + 7; // left_sym, right_symb, 3 symbols for progress number, symbols '%' and terminating symbol.
    char* arr = new char[arr_size];

    while ((current_progress < 1.0) or are_doubles_equals(current_progress, 1.0))
    {
        system("clear");
        configure_progress_bar(arr, arr_size, current_progress);
        std::cout << arr << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000000*seconds/g_number_of_symb));
        current_progress += 1.0/double(g_number_of_symb);

    }

    delete[] arr;
}

int main(void)
{
    int seconds{0};

    std::cout << "Enter number of seconds for filling the progress bar: ";
    std::cin >> seconds;
    
    implement_progress(seconds);

    return 0;
}