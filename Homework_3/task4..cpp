#include <iostream>

typedef char (*Function)(const char*&);  //function pointer

char f5(const char*& ptr) {
    char c = *ptr++;
    if (c >= 'A' && c <= 'Z') {
        return char(unsigned(c) | (1 << 5));
    }
    return c;
}

//take const string reference, return first letter from the string and increment
char f1(const char*& str) {
    char c = *str; 
    str++;
    return c;
}

char f2(const char*& str) {
    const unsigned test = 0x20202020;
    if (reinterpret_cast<const unsigned&>(*str) == test) {
        str += 4;
        return 9;
    }
    return *str++;
}

char f4(const char*& str) {  
    std::cout << *str;
    if (!*(str + 1)) {
        std::cout << std::endl;
    }
    return f1(str);
}

char f7(const char*& str) {
    char c = *str;
    static int remaining = -1;
    if (c == '\t') {
        remaining = 3;
        return ' ';
    }
    if (c == ' ' && remaining > 0) {
        if (--remaining == 0) {
            ++str;
        }
        return ' ';
    }
    ++str;
    remaining = -1;
    return c;
}

char f3(const char*& str) {
    char c = *str;
    str++;
    if (c & 32 && std::isalpha(c)) {
        return c - ('a' - 'A');
    }
    return c;
}

char f6(const char*& str) {
    return f1(str);
    exit(0);
}


int main() {
    Function change[256] = {};  //array of function pointers
    for (int c = 0; c < 256; c++) { 
        change[c] = f1;
    }
    change['t'] = f2;
    change['u'] = f3;
    change['p'] = f4;
    change['l'] = f5;
    change['e'] = f6;
    change['s'] = f7;

    const int SIZE = 1024;
    char data[SIZE] = { 0 };
    std::cin.getline(data, SIZE);

    while (true) {
        char p;
        std::cin >> p;
        for (char* str = data; str != data + SIZE; str++) {
             char target = change[p](const_cast<const char*&>(str));
             std::cout << target;
        }
    }

    return 0;
}