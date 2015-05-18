//libraries included
#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>


//debuging
#include <cstdlib>

class parameter;
class equation;
class operand;
class operator;

//Declarations:
//complete
void generateCaluse(unsigned int size, std::vector <parameter> &vars, std::ofstream file);
//generates a clause of CNF and outputs it into the file


std::vector <unsigned int> getProbabilities();
//returns a vector of unsigned ints to represent relitive liklyhood of each variable in the input vector
//may be based off an external file

//complete
unsigned long long sum(const std::vector <parameter> &input);		//complete
unsigned long long sum(const std::vector <unsigned int> &input);	//complete
//gets the sum of all the values in the vector

//complete
unsigned long long random(unsigned long long max);
//gets random interger in the range [0, max]

//complete
float logBase(float base, float x);
//returns log of any base


//classes
class parameter{
	private:
		//vars
		unsigned int existances;		//number of previous existances
		unsigned int distance;			//distance to last existance
		static unsigned int length;		//number of total variables used
		unsigned int update;			//how often to update
		equation probability;			//function to use to generate probability
		signed char name;				//character to represent variable
		unsigned int output;			//the current output from the function
	public:
		//fucntions

		parameter(std::ifstream &input, signed char symbol);
		//constructor: sets everything from .pram file


		void update();
		//updates output when it's time

		//complete
		signed char output();
		//returns the character as well doing other nessicary things

		//complete
		unsigned int value()	{return output;}
		//returns output member variable
};

class equation{
	//stuff
};

class operand{
	//stuff
};

class operator{
	//stuff
};







//Definitions:
int main()
{
	//get file to use
	std::ifstream input;
	std::string name
	do
	{
		std::cout << "Please give the file name you would like to use.\nNote: it must already have a .pram file setup.\n";
		std::getline(std::cin, name);
		input.open(name + ".pram");
	}while(input.fail())
	//file is set up

	//get info from file
	unsigned int sizeOfCNF;
	unsigned int numberOfStatements;
	unsigned int numberOfClauses;

	input >> sizeOfCNF >> numberOfStatements >> numberOfClauses;			//This line can be improved, a lot.

	std::vector <parameter> parameters;

	for(signed char character = 33; !input.eof(); character = (character < 0) ? character * -1 : character * -1 + 1)
	{
		parameters.push_back(parameter(input, character));
		if(character == -126)
			break;
	}
	//got all info from file

	//clsoe filestream
	input.close();
	//closed filestream

	//output
	std::ofstream output;
	output.open(name + ".cnf")
	while(numberOfStatements-- > 0)
	{
		for(unsigned int i = 0; i < numberOfClauses; i++)
		{
			generateCaluse(sizeOfCNF, parameters, output);
			output << ' ';
		}
		output << std::endl;
	}
	output.close();
	return 0;
}




void generateCaluse(unsigned int size, std::vector <parameter> &vars, std::ofstream &file)
{
	for(unsigned int i = 0; i < size; i++)
	{
		unsigned int index = 0;
		for(unsigned long long value = random(sum(vars) - 1); value > vars.at(index).value(); index++)
		{
			value -= vars.at(index).value();
		}
		file >> vars.at(index).output();
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

unsigned long long sum(const std::vector <parameter> &input)
{
	unsigned long long output = 0;
	for(unsigned int i = 0; i < input.size(); i++)
		output += input.at(i).value();
	return output;
}

signed char parameter::output()
{
	existances++;
	distance = 0;
	length++;
	return output;
}