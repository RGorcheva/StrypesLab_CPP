#include "./lib/helper.hpp"
#include <iostream>
#include <iomanip>
#include <string>

const int ROWS = 6;

enum Columns
{
	PERSON,
	MOTHER,
	FATHER,
	COLS
};

typedef const char* (*fp)[COLS];

void print_table(const char* arr[][COLS], int rows)
{
	if (!arr || !rows)
	{
		return;
	}
	std::cout << std::setw(20) << "[Person]";
	std::cout << std::setw(20) << "[Mother]";
	std::cout << std::setw(20) << "[Father]" << std::endl;

	for (int i = 0; i < rows; i++)
	{
		std::cout << std::setw(20) << arr[i][PERSON];
		std::cout << std::setw(20) << arr[i][MOTHER];
		std::cout << std::setw(20) << arr[i][FATHER] << std::endl;
	}
	std::cout << std::endl;
}

int compare_lexicaly(const void* a, const void* b)
{
	const char* strA = (*(fp)a)[PERSON];
	const char* strB = (*(fp)b)[PERSON];
	return strcmp(strA, strB);
}

bool find_relation(const char* arr[][COLS], int rows, const char* child, const char* parent, int* count)
{
	if (!arr || !rows || !child || !parent)
	{
		return false;
	}
	bool has_person = false;
	int find_person = 0;
	for (int i = 0; i < rows; i++)
	{
		if (!strcmp(arr[i][PERSON], child))
		{
			has_person = true;
			find_person = i;
			break;
		}
	}
	if (has_person == false)
	{
		return false;
	}
	if (!strcmp(parent, arr[find_person][MOTHER]))
	{
		(*count)++;
		return true;
	}
	if (!strcmp(parent, arr[find_person][FATHER]))
	{
		(*count)++;
		return true;
	}
	if (find_relation(arr, rows, arr[find_person][MOTHER], parent, count))
	{
		(*count)++;
	}
	if (find_relation(arr, rows, arr[find_person][FATHER], parent, count))
	{
		(*count)++;
	}
	return *count ? true : false;
}

int main(void)
{
	const char* table[ROWS][COLS]{ nullptr };

	std::cout << "Enter table:" << std::endl;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			table[i][j] = enter_string();
		}
	}

	std::cout << "Unsorted: " << std::endl;
	print_table(table, ROWS);
	qsort(&table, ROWS, sizeof(char* [COLS]), compare_lexicaly);
	std::cout << "Sorted: " << std::endl;
	print_table(table, ROWS);

	const char* child = nullptr;
	const char* parent = nullptr;

	while (1)
	{
		std::cout << "Enter two names:" << std::endl;
		child = enter_string();
		if (!strcmp(child, "exit"))
		{
			break;
		}
		parent = enter_string();

		int count_relation = 0;
		bool is_found_relation = find_relation(table, ROWS, child, parent, &count_relation);
		std::cout << count_relation << std::endl;
	};

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			free((void*)table[i][j]);
		}
	}

	if (child)
	{
		free((void*)child);
	}
	if (parent)
	{
		free((void*)parent);
	}

	exit(EXIT_SUCCESS);
}