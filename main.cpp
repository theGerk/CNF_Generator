//libraries included
#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>


//debuging
#include <cstdlib>

class parameter;
class function;
class operand;
class variable;

//Declarations:
//complete
void generateCaluse(unsigned int size, std::vector <parameter> &vars, std::ofstream file);
//generates a clause of CNF and outputs it into the file

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

		unsigned int update;			//how often to update
		operand probability;			//function to use to generate probability
		signed char name;				//character to represent variable
		unsigned int output;			//the current output from the function
		std::vector <variable> var;		//the variables used by it
		std::string setLine;			//the entire line from the .pram file used for this

		//functions

		void mutateLine();
		//changes setLine to being used for function

	public:
		//vars
		static unsigned int length;		//number of total variables used

		//fucntions
		//complete
		parameter(std::ifstream &input, signed char symbol);
		//constructor: sets everything from .pram file

		//complete
		void update();
		//updates output when it's time

		//complete
		signed char output();
		//returns the character as well doing other nessicary things

		//complete
		unsigned int value() const	{return output;}
		//returns output member variable


		void setup(const std::vector <parameter> &parameters);
		//uses setLine to set up var, then changes it so that function can use it and then removes data from setLine as to save sapce
		//if update is 0 then will just delete setLine's contents
		//also initializes output regardless


		void reset();
		//used between statments to reset everything neisccary
};

class function{
	private:
		std::vector <operand> input;	//the values that are going to be operated on
		char operation;					//char representing 

	public:
		//functions

		float evaluate();
		//gets output of function


		void setup(const std::string &input, const std::vector <variable> &vars);
		//sets up function
};

class operand{
	private:
		unsigned char varInUse;	//says which member variable is bing used
		// 0 --> expr
		// 1 --> var
		// 2 --> constant

		//ONLY 1 MAY BE USED
		expression expr;
		variable *var;
		float constant;

	public:
		//public member functions
		
		void setup(std::string input, const std::vector <variable>& vars);
		//sets up operand


		float getValue() const;
		//evaluates if it is true or false and returns value

};

struct variable{
		std::string name;		//the symbolic name of the variable
		unsigned int* parent;	//the value that sets it
		float value;			//the value of the variable
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

	//set up second part of parameters
	for(unsigned int i = parameters.size(); i; parameters.at(--i).setup(parameters));	//beatifully consice but hard to read line of code is beatifully consice and hard to read :P 	Suck on my poor style Max!
	//parameters have been completely set up

	//clsoe filestream
	input.close();
	//closed filestream

	//output
	std::ofstream output;
	output.open(name + ".cnf")
	while(numberOfStatements-- > 0)
	{
		parameters.at(0).length == 0;
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
		for(unsigned int i = power; !i; i--)
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

void parameter::update()
{
	if(update && !(length % update))
	{
		//code stuff
		output = probability.getValue();
	}
}

parameter::parameter(std::ifstream &input, signed char symbol)
{
	reset();
	getline(input, setLine);
	name = symbol;
}

