/*
Задача 3. Имате даден код: 
#include <iostream>

int main() {
	double k;
	int n;
	std::cin >> k >> n;

	const float check = 1e-6;
	float a = 1.f;
	float result = k / double(n);
	double b = 0.f;
	int c = 1;
	
	do {
		float temp = 1.f;
		for (int c = 0; c < n; c++) {
			temp *= result;
		}
		b = temp - k;
		const int now = (b > 0.f) - (b < 0);

		if (now != c) {
			a *= 0.75;
			c = now;
		}
		
		if (b > 0.f) {
			result *= 1.f/(1 + a);
		} else {
			result = result * (1.f + a);
		}
	} while(check < fabs(b));

	std::cout << result;

	return 0;
}
В коментар напишете кратък текст какво прави кода, как работи и евентуално каква задача решава. 
Променете кода както намерите за добре така че да го подобрите.
*/

#include <iostream>
#include <cmath>//for fabs()

int main() 
{
	double k{0.0}; //initialization
	int n{0};
	std::cin >> k >> n;

	//const float check = 1e-6;
	const double check{0.000001};  //1e-6; - more readable
	double a{1.0};
	double result = k / (double)n; //double, not float
	double b{0.0};
	int sign{1}; //c
	
	do {
		double temp{1.0}; //double, not float
		for (int i = 0; i < n; i++) //different variable from above c, more readable
		{
			temp *= result; 
		} // at the end of first iteration: temp = (k/n)^n
		b = temp - k; // = (k/n)^n - k
		const int new_sign = (b > 0.0) - (b < 0.0); //if 0.0 is the same type like b, it wouldn't need a type cast. 
		//b > 0 -> new_sighn = 1;
		//b = 0 -> new_sighn = 0;
		//b < 0 -> new_sighn = -1;

		if (new_sign != sign) 
		{
			a *= 0.75; //the amplitude decreases when the sign is changed
			sign = new_sign; //saves the last sign
		}
		
		if (b > 0.0) 
		{
			result *= 1.0/(1.0 + a); // result  = k/n(1+a)
		} 
		else 
		{
			result *=  1.0 + a; // result  = k(1+a)/n
		}
	} while(check < fabs(b));

	std::cout << result;

	return 0;
}

//I'm not sure what exactly the code do, but I suppose it find the root of some equasion.
//The code iterates the result while the last iteration is less than given deviation (check).