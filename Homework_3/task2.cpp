#include "./lib/helper.hpp"
#include <iostream>
#include <string.h>
#include <stdlib.h>


char* decompress_string(const char* source)
{
	const char* func_name = "decompress_string";
	if (source == nullptr)
	{
		return nullptr;
	}
	char number[10] = { '\0' };
	int n = 0;
	char* new_str = nullptr;
	size_t capacity = strlen(source) + 1;
	char* destination = (char*)malloc(sizeof(char) * capacity);
	if (!destination)
	{
		std::cerr << "In function " << func_name << ": Cannot allocate memory!" << std::endl;
		return nullptr;
	}
	int d = 0;
	for (int s = 0; source[s] != '\0'; s++)
	{
		if (')' == source[s])
		{
			if (d == capacity)
			{
				capacity *= 2;
				if ((new_str = realloc_str(destination, capacity)) == nullptr)
				{
					free(destination);
					return nullptr;
				}
				destination = new_str;
			}
			destination[d] = '\0';
			return destination;
		}
		if ('A' <= source[s] && source[s] <= 'Z')
		{
			if (d == capacity)
			{
				capacity *= 2;
				if ((new_str = realloc_str(destination, capacity)) == nullptr)
				{
					free(destination);
					return nullptr;
				}
				destination = new_str;
			}
			destination[d] = source[s];
			d++;
		}
		if (('0' <= source[s] && source[s] <= '9'))
		{
			number[n] = source[s];
			n++;
		}
		if ('(' == source[s])
		{
			s++;
			number[n] = '\0';
			int num = atoi(number);
			n = 0;
			char* partial_str = decompress_string(&source[s]);
			while (source[s] != ')')
			{
				s++;
			};
			for (int i = 0; i < num; i++)
			{
				for (int p = 0; partial_str[p] != '\0'; p++)
				{
					if (d == capacity)
					{
						capacity *= 2;
						if ((new_str = realloc_str(destination, capacity)) == nullptr)
						{
							free(destination);
							return nullptr;
						}
						destination = new_str;
					}
					destination[d] = partial_str[p];
					d++;
				}
			}
			free((void*)partial_str);
		}
	}
	if (d == capacity)
	{
		capacity *= 2;
		if ((new_str = realloc_str(destination, capacity)) == nullptr)
		{
			free(destination);
			return nullptr;
		}
		destination = new_str;
	}
	destination[d] = '\0';
	return destination;
}

int main(void)
{
	const char* input = enter_string();
	const char* output = decompress_string(input);
	std::cout << output << std::endl;

	if (input)
	{
		free((void*)input);
	}
	if (output)
	{
		free((void*)output);
	}
	exit(EXIT_SUCCESS);
}