//modifiable constants by user
#define SIZE_OF_CNF 3
#define NUMBER_OF_STATEMENTS
#define NUMBER_OF_CLAUSES
#define NUMBER_OF_VARIABLES
#define NAME "CNF"

//libraries included
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>	//random numbers
#include <cstdlim>	//random numbers

//debuging
#include <iostream>
#include <cstdlib>


//Declarations:
//complete
std::vector <char> getVars(unsigned int size);
//returns a vector of the usable characters for differen variables 

//complete
void generateCaluse(unsigned int size, std::vector <char> &vars, std::ofstream file);
//generates a clause of CNF and outputs it into the file


std::vector <unsigned int> getProbabilities();
//returns a vector of unsigned ints to represent relitive liklyhood of each variable in the input vector
//may be based off an external file

//complete
unsigned long long sum(const std::vector <unsigned int> &input);
//gets the sum of all the values in the vector

//complete
unsigned long long random(unsigned long long max);
//gets random interger in the range [0, max]

//complete
float logBase(float base, float x);
//returns log of any base


//Definitions:
int main()
{

	vector <signed char> vars = getVars(NUMBER_OF_VARIABLES);

	std::ofstream output;
	//get paramaters
	otuptu.open(NAME + ".pram")

	output.open(NAME + ".cnf", std::fstream::app);

	for(unsigned int n = 0; n < NUMBER_OF_STATEMENTS; n++)
	{
		for(unsigned int i = 0; i < NUMBER_OF_CLAUSES; n++)
		{
			generateCaluse(SIZE_OF_CNF, vars, output);
			output << ' ';
		}
		output << std::endl;
	}
	output.close();
	return 0;
}

std::vector <signed char> getVars(unsigned int size)
{
	std::vector <signed char> output(size);

	//start with 33 (!) and go to 126 (~)
	if(size > 94 /*number of characters between ~ and ! (inclusive)*/)
	{
		std::cout << "try again with smaller size\n";
		exit(0);
	}
	else
	{
		//generate vector with characters that will be used
		for(unsigned int i = 0; i < size; i++)
		{
			output[i] = '!' + i;
		}
	}
	return output;
}

void generateCaluse(unsigned int size, std::vector <signed char> &vars, std::ofstream &file)
{
	for(unsigned int i = 0; i < size; i++)
	{
		std::vector <unsigned int> probabilities = getProbabilities();
		unsigned int index = 0;
		for(unsigned long long value = random(sum(probabilities) - 1); true; index++)
		{
			if(value > probabilities[index])
				break;
			value -= probabilities[index];
		}
		file << (index % 2) ? vars[index] -1 * vars[index];
	}
}

unsigned long long sum(const std::vector <unsigned int> &input)
{
	unsigned long long output = 0;
	for(unsigned int i = 0; i < input.size(); i++)
		output += input[i];
	return output;
}

unsigned long long random(unsigned long long max)
{
	//find large enough power
	//the least natural number such that RAND_MAX ^ it >= max
	const unsigned int power = ceil(logBase(RAND_MAX, max));

	//get divisor
	//the greatest natural number such that max * it <= RAND_MAX ^ power
	const unsigned int divisor = floor(pow(RAND_MAX, power) / (float)max)

	//generate random number
	//the output
	unsigned long long randomNumber = 0;
	do{
		for(unsigned int i = power; i > 0; i--)
			randomNumber += pow(rand(), i);
	}while(randomNumber > divisor * max);
	randomNumber %= max;

	return randomNumber;
}

float logBase(float base, float x)
{
	return log(x)/log(base);
}
