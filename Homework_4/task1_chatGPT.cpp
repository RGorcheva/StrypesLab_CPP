#include <iostream>

struct DList {
    DList* next = nullptr;
    DList* prev = nullptr;
};

struct Number {
    DList list;
    const int value;
};

typedef void (*FreeElement)(DList*);
typedef bool (*FilterElement)(DList*);

void append(DList*& list, DList* element) {
    if (!list) {
        list = element;
        return;
    }

    DList* last = list;
    while (last->next) {
        last = last->next;
    }

    last->next = element;
    element->prev = last;
}

void prepend(DList*& list, DList* element) {
    if (!list) {
        list = element;
        return;
    }

    element->next = list;
    list->prev = element;
    list = element;
}

void rotateList(DList*& list, int count) {
    if (!list || count == 0) {
        return;
    }

    DList* current = list;
    int absCount = count > 0 ? count : -count;

    for (int i = 0; i < absCount; ++i) {
        if (count > 0) {
            if (!current->next) {
                break;
            }
            current = current->next;
        }
        else {
            if (!current->prev) {
                break;
            }
            current = current->prev;
        }
    }

    if (count > 0) {
        list->prev = current;
        current->next = list;
        list = current->next;
        list->prev = nullptr;
    }
    else {
        list->prev = current->prev;
        current->prev->next = list;
        current->prev = nullptr;
        current->next = nullptr;
        list = current;
    }
}

DList* detachElement(DList*& list) {
    if (!list) {
        return nullptr;
    }

    DList* element = list;
    list = list->next;
    if (list) {
        list->prev = nullptr;
    }

    element->next = nullptr;
    element->prev = nullptr;
    return element;
}

void freeList(DList*& list, FreeElement freeElement) {
    while (list) {
        DList* element = detachElement(list);
        freeElement(element);
    }
}

void filterList(DList*& list, FilterElement filterElement, FreeElement freeElement) {
    DList* remaining = nullptr;

    while (list) {
        DList* current = detachElement(list);

        if (filterElement(current)) {
            freeElement(current);
        }
        else {
            prepend(remaining, current);
        }
    }

    list = remaining;
}

#define FOR_EACH(Type, iterName, list) for (Type* iterName = reinterpret_cast<Type*>(list); iterName != nullptr; iterName = reinterpret_cast<Type*>(iterName->next))

#define FOR_EACH_R(Type, iterName, list) for (Type* iterName = reinterpret_cast<Type*>(list); iterName != nullptr; iterName = reinterpret_cast<Type*>(iterName->prev))

void freeNumber(DList* n) {
    delete static_cast<Number*>(n);
}

bool isOdd(DList* element) {
    return (static_cast<Number*>(element)->value & 1) == 1;
}

bool isDiv3(DList* element) {
    return (static_cast<Number*>(element)->value % 3) == 0;
}

int main() {
    DList* list = nullptr;
    for (int c = 0; c < 20; c++) {
        Number* n = new Number{ {}, c };
        if (true) {
            prepend(list, &n->list);
        }
        else {
            append(list, &n->list);
        }
    }
    std::cout << "List: ";
    printList(list);

    std::cout << "Left rotate 1: ";
    rotateList(list, 1);
    printList(list);

    std::cout << "Right rotate 6: ";
    rotateList(list, -6);
    printList(list);

    DList* odd = splitList(list, isOdd);

    std::cout << "Split even elements: ";
    printList(list);
    std::cout << "Split odd elements: ";
    printList(odd);

    filterList(list, isDiv3, freeNumber);
    std::cout << "Split even elements, filter div 3: ";
    printList(list);
    filterList(odd, isDiv3, freeNumber);
    std::cout << "Split odd elements, filter div 3: ";
    printList(odd);

    std::cout << "odd reversed: ";
    FOR_EACH_R(Number, n, odd) {
        std::cout << n->value << ' ';
    }
    std::cout << std::endl;

    std::cout << "even reversed: ";
    FOR_EACH_R(Number, n, list) {
        std::cout << n->value << ' ';
    }
    std::cout << std::endl;

    freeList(odd, freeNumber);
    freeList(list, freeNumber);
    return 0;
}