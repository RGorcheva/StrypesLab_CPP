
#include <iostream>
#include <iomanip>
#include <cmath>

struct square
{
	double height;
	double infiltration_step;
	double available_q;
	double infiltrated_q;
	square* neighbors[4]; // 0 = up. 1 = down, 2 = left, 3 = right
};

const double EPS{ 0.0001 };

double min(double a, double b) //ok
{
	return a < b ? a : b;
}

bool are_doubles_equals(const double a, const double b) //ok
{
	if (EPS > fabs(a - b))
	{
		return true;
	}
	return false;
}

void print_infiltrated_quantities(square* arr, const int rows, const int cols) //ok
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << std::setprecision(2) << std::fixed << arr[i * cols + j].infiltrated_q << "    ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

void setup_network(square* network, const int rows, const int cols)
{
	double start_Q_per_square{ 0.0 };
	std::cout << "Enter heights of the squares: ";
	for (int i = 0; i < rows * cols; i++)
	{
		std::cin >> network[i].height;
	}
	std::cout << "Enter infiltration steps of the squares: ";
	for (int i = 0; i < rows * cols; i++)
	{
		std::cin >> network[i].infiltration_step;
	}
	std::cout << "Enter start water quantity per square: ";
	std::cin >> start_Q_per_square;
	for (int i = 0; i < rows * cols; i++)
	{
		network[i].available_q = start_Q_per_square;
		network[i].infiltrated_q = 0.0;
	}
	for (int i = 0; i < rows; i++) // 0 = up, 1 = down, 2 = left, 3 = right
	{
		for (int j = 0; j < cols; j++)
		{
			if (i == 0) //define up square 
			{
				network[i * cols + j].neighbors[0] = nullptr;
			}
			else
			{
				network[i * cols + j].neighbors[0] = &network[(i - 1) * cols + j];
			}
			if (i == rows - 1) //define down square = 1
			{
				network[i * cols + j].neighbors[1] = nullptr;
			}
			else
			{
				network[i * cols + j].neighbors[1] = &network[(i + 1) * cols + j];
			}
			if (j == 0) //definr left square
			{
				network[i * cols + j].neighbors[2] = nullptr;
			}
			else
			{
				network[i * cols + j].neighbors[2] = &network[i * cols + (j - 1)];
			}
			if (j == cols - 1) //define right square
			{
				network[i * cols + j].neighbors[3] = nullptr;
			}
			else
			{
				network[i * cols + j].neighbors[3] = &network[i * cols + (j + 1)];
			}
		}
	}
}

square* find_higher_square_with_available_water(square* arr, const int size)
{
	square* max = &arr[0];
	int i = 0;
	for (; i < size; i++)
	{
		if (are_doubles_equals(arr[i].available_q, 0.0))
		{
			continue;
		}
		max = &arr[i];
		break;
	}
	for (int j = i + 1; j < size; j++)
	{
		if (arr[j].height > (*max).height)
		{
			max = &arr[j];
		}
	}
	return max;
}

void step(square* network, const int size) //NOK - wrong algorytm
{
	for (int i = 0; i < size; i++)
	{
		if (are_doubles_equals(network[i].available_q, 0.0))
		{
			continue;
		}
		double current_infiltration_step = min(network[i].infiltration_step, network[i].available_q);
		network[i].infiltrated_q += current_infiltration_step;
		network[i].available_q -= current_infiltration_step;
	}
	square* current_hightest = find_higher_square_with_available_water(network, size);
	if (are_doubles_equals(current_hightest->available_q, 0.0))
	{
		return;
	}
	double sum_heights{ 0 };
	for (int n = 0; n < 4; n++)
	{
		if (current_hightest->neighbors[n] != nullptr && current_hightest->neighbors[n]->height < current_hightest->height)
		{
			sum_heights += current_hightest->neighbors[n]->height;
		}
	}
	if (are_doubles_equals(sum_heights, 0.0))
	{
		return;
	}
	for (int n = 0; n < 4; n++)
	{
		if (current_hightest->neighbors[n] != nullptr && current_hightest->neighbors[n]->height < current_hightest->height)
		{
			current_hightest->neighbors[n]->available_q += (current_hightest->neighbors[n]->height / sum_heights) * current_hightest->available_q;
		}
	}
	current_hightest->available_q = 0.0;
}

double total_infiltrated_quantity(square* network, const int size) //ok
{
	double sum{ 0.0 };
	for (int i = 0; i < size; i++)
	{
		sum += network[i].infiltrated_q;
	}
	return sum;
}

void infiltrate_network(square* network, const int size) //ok
{
	double total_fallen_Q{ size * network[0].available_q };
	double total_infiltrated_Q{ 0.0 };
	while (!are_doubles_equals(total_fallen_Q, total_infiltrated_Q))
	{
		step(network, size);
		total_infiltrated_Q = total_infiltrated_quantity(network, size);
	}
}

int main(void)
{
	int W{ 0 };
	int H{ 0 };

	std::cout << "Enter network dimensions: ";
	std::cin >> W >> H;

	square* network = new square[W * H];

	setup_network(network, W, H);
	infiltrate_network(network, W * H);
	print_infiltrated_quantities(network, W, H);

	delete[] network;
	return 0;
}