#include "helper.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>

char* realloc_str(char* str, size_t new_size)
{
	const char* func_name = "realloc_char";
	if (!str || !new_size)
	{
		std::cerr << "In function " << func_name << ": arr is nullptr or size is 0!" << std::endl;
		return nullptr;
	}
	char* new_str = (char*)realloc(str, sizeof(char) * new_size);
	if (new_str == nullptr)
	{
		std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
		return nullptr;
	}
	str = new_str;
	return str;
}

const char* enter_string(void)
{
	const char* func_name = "enter_string";
	int capacity = 25;
	char* str = (char*)malloc(sizeof(char) * capacity);
	char* new_str = nullptr;
	if (str == nullptr)
	{
		std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
		return nullptr;
	}
	char c = '\0';
	int it = 0;
	while ((c = getchar()) != '\n')
	{
		if (it == capacity)
		{
			capacity *= 2;
			if ((new_str = realloc_str(str, capacity)) == nullptr)
			{
				free(str);
				return nullptr;
			}
			str = new_str;
		}
		str[it] = c;
		it++;
	}
	if (it == capacity)
	{
		capacity *= 2;
		if ((new_str = realloc_str(str, capacity)) == nullptr)
		{
			free(str);
			return nullptr;
		}
		str = new_str;
	}
	str[it] = '\0';
	capacity = strlen(str) + 1;
	if ((new_str = realloc_str(str, capacity)) == nullptr)
	{
		free(str);
		return nullptr;
	}
	str = new_str;
	return str;
}