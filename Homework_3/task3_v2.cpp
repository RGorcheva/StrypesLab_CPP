#include "./lib/helper.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>

char* find_first_appearance(const char* search, const char* find) //ok
{
	char* pSearch = const_cast<char*>(search);
	char* pFind = const_cast<char*>(find);
	for (; *pSearch != '\0'; ++pSearch)
	{
		const char* pIn = pSearch;
		for (; *pFind != '\0'; ++pFind, ++pIn)
		{
			if (*pFind != *pIn)
			{
				break;
			}
		}
		if (*pFind == '\0')
		{
			return pSearch;
		}
	}
	return nullptr;
}

int count_delimiters(const char* string, const char* del) //ok
{
	if (!string || !del)
	{
		return 0;
	}
	int count = 0;
	char* pString = const_cast<char*>(string);
	while (1)
	{
		pString = find_first_appearance(pString, del);
		if (!pString)
		{
			return count;
		}
		pString += strlen(del);
		count++;
	}
	return count;
}

int count_full_strings(const char* string, const char* del)
{
	if (!string || !del)
	{
		return 0;
	}
	int count = 0;
	char* pString = const_cast<char*>(string);
	char* pDel = find_first_appearance(string, del);
	if (pDel == pString)
	{
		pString += strlen(del);
		if (*pString == '\0')
		{
			return count;
		}
	}
	while (1)
	{
		count++;
		pString = find_first_appearance(pString, del);
		if (!pString)
		{
			return count;
		}
		pString += strlen(del);
		if (*pString == '\0')
		{
			return count--;
		}
	}
	return count++;
}
int count_all_strings(const char* string, const char* del)
{
	if (!string || !del)
	{
		return 0;
	}
	int count = 0;
	char* pString = const_cast<char*>(string);
	char* pDel = find_first_appearance(string, del);
	if (pDel == pString)
	{
		pString += strlen(del);
		if (*pString == '\0')
		{
			return count;
		}
	}
	while (1)
	{
		count++;
		pString = find_first_appearance(pString, del);
		if (!pString)
		{
			return count;
		}
		pString += strlen(del);
		if (*pString == '\0')
		{
			return count--;
		}
	}
	return count++;
}

char* copy_substring(const char* start, const char* end) //ok
{
	if (!start || !end)
	{
		return nullptr;
	}
	const char* func_name = "copy_substring";
	size_t size = end - start + 1;
	char* substring = (char*)malloc(sizeof(char) * size);
	if (!substring)
	{
		std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
		return nullptr;
	}
	char* it = const_cast<char*>(start);
	int i = 0;
	for (; i < size - 1; i++)
	{
		substring[i] = start[i];
	}
	substring[i] = '\0';
	return substring;
}

char** string_split(const char* string, const char* delimiter, bool keep_empty_elements)
{
	if (!string || !delimiter)
	{
		return nullptr;
	}
	const char* func_name = "string_split";
	int count_word = 0;
	if (keep_empty_elements)
	{
		count_word = count_all_strings(string, delimiter);
	}
	else
	{
		count_word = count_full_strings(string, delimiter);
	}
	char** separate_arr = (char**)malloc(sizeof(char*) * (count_word + 1));
	if (!separate_arr)
	{
		std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
		return nullptr;
	}
	separate_arr[count_word] = nullptr;

	int i = 0;
	char* pStr = const_cast<char*>(string);
	char* pDel = find_first_appearance(pStr, delimiter);
	if (!pDel) //there is no delimiter in the string
	{
		separate_arr[i] = (char*)malloc(sizeof(char) * (strlen(string) + 1));
		if (!separate_arr[i])
		{
			std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
			return nullptr;
		}
		return separate_arr;
	}

	if (pDel == pStr) //if starts with delimiter, ignore it
	{
		if(keep_empty_elements)
		{

		}
		pStr += strlen(delimiter);
		pDel = find_first_appearance(pStr, delimiter);
		if (!pDel)
		{
			pDel = &pStr[strlen(pStr)];
		}
	}
	for (int i = 0; i < count_word; i++)
	{
		size_t str_size = pDel - pStr + 1;
		separate_arr[i] = (char*)malloc(sizeof(char) * str_size);
		if (!separate_arr[i])
		{
			std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
			return nullptr;
		}
		int j = 0;
		for (; j < str_size - 1; j++)
		{
			separate_arr[i][j] = *pStr;
			pStr++;
		}
		separate_arr[i][j] = '\0';
		if (*pStr == '\0')
		{
			return separate_arr;
		}
		pStr += strlen(delimiter);
		if (*pStr == '\0')
		{
			return separate_arr;
		}
		pDel = find_first_appearance(pStr, delimiter);
		if (!pDel)
		{
			pDel = &pStr[strlen(pStr)];
		}
	}
	return separate_arr;
}

int main(void)
{
	const char* input = enter_string();
	const char* delimiter = enter_string();
	//int words = count_full_strings(input, delimiter);
	char** str_arr = string_split(input, delimiter, true);

	for (int i = 0; str_arr[i] != nullptr; i++)
	{
		std::cout << i << ": " << str_arr[i] << std::endl;
	}

	//free allocated memory
	for (int i = 0; i < words; i++)
	{
		if (str_arr[i])
		{
			free((void*)str_arr[i]);
		}
	}
	if (str_arr)
	{
		free((void*)str_arr);
	}
	if (input)
	{
		free((void*)input);
	}
	if (delimiter)
	{
		free((void*)delimiter);
	}

	exit(EXIT_SUCCESS);
}
