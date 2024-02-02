#include <iostream>
//typedef int(*MyFunction)(int,int);
using MyFunction = int(*)(int);

int f(int x){
    return 5*x;
}

MyFunction ptr = f;

using VoidFn = void(*)(int);
void forEach(const int* arr, const int count, VoidFn fptr){
    for (int i = 0; i < count; i++){
        fptr(arr[i]);
    }
}

int sumWithCallback(const int*arr, const int count, VoidFn fptr, int limit){
    int sum = 0;
    for (int i = 0; i < count; i++){
        if (fptr != nullptr && arr[i] > limit){
            fptr(arr[i]);
        }
        sum += arr[i];
    }
    return sum;
}

int square(int x){
    return x*x;
}

void map(int* arr, const int count, int(*fptr)(int)){
    for (int i = 0; i < count; i++){
        arr[i] = fptr(arr[i]);
    }
    
}

void print(int x){
    std::cout << x << ' '; 
}
void printEven(int x){
    if (x % 2 == 0){
        std::cout << x << ' '; 
    }
}

int main(void){

    std::cout << f(10) << std::endl;
    int arr[] = {1,2,3,4,5};
    forEach(arr, 5, print);
    forEach(arr, 5, printEven);
    std::cout << "Sum = " << sumWithCallback(arr, 5, print, 3) << std::endl;
    map(arr, 5, square);
    std::cout << "Sum = " << sumWithCallback(arr, 5, nullptr, 3) << std::endl;
    return 0;
}