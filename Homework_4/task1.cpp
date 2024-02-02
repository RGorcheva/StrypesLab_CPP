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

///**
// * @brief Print all elements in the list followed by new line
// *
// * @param list - the list to print
// */
//void printList(DList* list);
//
///**
// * @brief Split given list into two new ones based on predicate
// *
// * @param list - the input list, set to the first element of the remaining elements that do not match the predicate
// * @param filterElement - the predicate used to filter elements,
// * @return DList* - list of all elements that predicate returned true
// */
//DList* splitList(DList*& list, FilterElement filterElement);
//
//
//// Implementation start here:
//
///**
// * @brief Append new list element after the given one, if list is empty, set list to new element
// *
// * @param list - the existing element to insert after or nullptr
// * @param element - the new element to insert
// */
//void append(DList*& list, DList* element);
//
///**
// * @brief Prepend new list element before the given one, if list is empty set list to new element
// *
// * @param list - the existing element to insert or nullptr
// * @param element - the new element to insert
// */
//void prepend(DList*& list, DList* element);
//
///**
// * @brief Rotate the list by number of items
// *
// * @param list - the list input/output, points to new start of list after
// * @param count - positive value rotates left, negative value rotate right
// */
//void rotateList(DList*& list, int count);
//
///**
// * @brief Remove one element from the list and return it
// *
// * @param list - input the element to remove, output the next element in the list or nullptr
// * @return DList* - the removed element
// */
//DList* detachElement(DList*& list);
//
///**
// * @brief Delete all elements in the list calling freeElement to deallocate the memory
// *
// * @param list - the list to free, set to nullptr
// * @param freeElement - function to use to delete elements
// */
//void freeList(DList*& list, FreeElement freeElement);
//
///**
// * @brief Delete all elements in the list that match a given predicate
// *
// * @param list - the list to filter, points to the remaining elements after call or nullptr if empty
// * @param filterElement - function to check if element must be filtered
// * @param freeElement - function to deallocate filtered elements
// */
//void filterList(DList*& list, FilterElement filterElement, FreeElement freeElement);

/**
 * @brief Macro for easier iteration of lists
 * @note See printList and splitList for usage example
 *
 * @param Type - the type of the element
 * @param iterName - the name of the element in the for loop
 * @param list - the list
 */
#define FOR_EACH(Type, iterName, list) for (Type* iterName = (Type*)list; iterName != nullptr; iterName = (Type*)(iterName->list.next))

 /**
  * @brief Macro for easier iteration of lists in reverse order
  * @note See main for usage
  *
  * @param Type - the type of the element
  * @param iterName - the name of the element in the for loop
  * @param list - the list
  */
#define FOR_EACH_R(Type, iterName, list) for (Type* iterName = (Type*)list; iterName != nullptr; iterName = (Type*)(iterName->list.prev))




  // End of implementation

void printList(DList* list) {
    FOR_EACH(Number, s, list) {
        std::cout << s->value << ' ';
    }
    std::cout << std::endl;
}

DList* splitList(DList*& list, FilterElement filterElement) {
    DList* filtered = nullptr;
    DList* remaining = nullptr;

    FOR_EACH(DList, iter, list) {
        if (filterElement(iter)) {
            DList* removed = detachElement(iter);
            prepend(filtered, removed);
        }
        else if (!remaining) {
            remaining = iter;
        }
    }

    list = remaining;
    return filtered;
}

void freeNumber(DList* n) {
    delete (Number*)n;
}

bool isOdd(DList* element) {
    return (((Number*)element)->value & 1) == 1;
}

bool isDiv3(DList* element) {
    return (((Number*)element)->value % 3) == 0;
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
