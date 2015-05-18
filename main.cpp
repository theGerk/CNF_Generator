//libraries included
#include <fstream>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdlib>


//Defined constants -- Will be updated continiously
	//operators in input
	#define REFERENCE '#'
		//Unary
			#define NEGITIVEi '-'
			#define FACTORIALi '!'
			#define CEILINGi 'C'
			#define FLOORi 'F'
			#define ROUNDi 'R'

		//Binary
			#define ADDi '+'
			#define SUBTRACTi '-'
			#define MULTIPLYi '*'
			#define DIVIDEi '/'
			#define POWERi '^'
			#define LOGi '~'
			#define ROOTi '`'

	//Other functions without operators


	//operators in memory
		//Unary
			#define NEGITIVEo '-'
			#define FACTORIALo '!'
			#define CEILINGo 'C'
			#define FLOORo 'F'
			#define ROUNDo 'R'

		//Binary
			#define ADDo '+'
			#define SUBTRACTo '-'
			#define MULTiPLYo '*'
			#define DiViDEo '/'
			#define POWERo '^'
			#define LOGo '~'
			#define ROOTo '`'

		//Other functions without operators (sine, cosine, tangent, sumation)




//Declarations:
class parameter;
class function;
class operand;
class variable;

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

//complete
float factorial(float x);
//returns factorial of the rounded value of x

//classes
class parameter{
	private:
		//vars
		unsigned int existances;			//number of previous existances
		unsigned int distance;				//distance to last existance

		unsigned int update;				//how often to update
		operand probability;				//function to use to generate probability
		signed char name;					//character to represent variable
		unsigned int output;				//the current output from the function
		std::vector <unsigned int*> var;	//the variables used by it
		std::string setLine;				//the entire line from the .pram file used for this

		//functions

		void mutateLine();
		//changes setLine to being used for function

		//complete
		unsigned int* getVariableToUse(char character);
		//returns the variable that is going to be used based on variable

		//complete
		int findVarLocation(unsigned int* var);
		//returns the location in the var vector where that exists
		//if it does not exist it returns the maximum value sotrable in an unsigned int
		//this value is obatained by simply taking the bitwise negation of 0

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
		signed char output(std::vector <parameter> &arg);
		//returns the character as well doing other nessicary things

		//complete
		unsigned int value() const	{return output;}
		//returns output member variable

		//in progress
		void setup(const std::vector <parameter> &parameters);
		//uses setLine to set up var, then changes it so that function can use it and then removes data from setLine as to save sapce
		//if update is 0 then will just delete setLine's contents
		//also initializes output regardless

		//complete
		void reset();
		//used between statments to reset everything neisccary
		//does not reset length
};

class function{
	private:
		std::vector <operand> input;	//the values that are going to be operated on
		char operation;					//char representing 

	public:
		//functions
		//complete - Will be upadated
		float evaluate() const;
		//gets output of function


		void setup(const std::string &input, const std::vector <variable> &vars);
		//sets up function

		//complete
		function(const std::string &input, const std::vector <variable> &vars)	{setup(input, vars);}
		//calls setup
};

class operand{
	private:
		unsigned short varInUse;	//says which member variable is bing used
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

		//complete
		float getValue() const;
		//evaluates if it is true or false and returns value
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
		for(unsigned int i = numberOfClauses; i; i--)
		{
			generateCaluse(sizeOfCNF, parameters, output);
			output << ' ';
		}
		output << std::endl;
	}
	output.close();
	return 0;
	//done
}

void generateCaluse(unsigned int size, std::vector <parameter> &vars, std::ofstream &file)
{
	for(unsigned int i = size; i; i--)
	{
		for(unsigned int n = vars.size(); n; vars.at(--n).update());
		unsigned int index = 0;
		for(unsigned long long value = random(sum(vars) - 1); value > vars.at(index).value(); index++)
		{
			value -= vars.at(index).value();
		}
		file >> vars.at(index).output(vars);
	}
}

unsigned long long sum(const std::vector <unsigned int> &input)
{
	unsigned long long output = 0;
	for(unsigned int i = input.size(); i; output += input.at(--i));
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
		for(unsigned int i = power; i; randomNumber += pow(rand(), i--));
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
	for(unsigned int i = input.size(); i; output += input.at(--i).value());
	return output;
}

signed char parameter::output(std::vector <parameter> &arg)
{
	for(unsigned int n = arg.size(); n; arg.at(--n).distance++);
	existances++;
	distance = 0;
	length++;
	return output;
}

void parameter::update()
{
	if(update && !(length % update))
	{
		// for(unsigned int i = var.size(); i; var.at(--i).value = *(var.at(i).parent));
		output = probability.getValue();
	}
}

parameter::parameter(std::ifstream &input, signed char symbol)
{
	existances = 0;
	distance = 0;
	getline(input, setLine);
	name = symbol;
}

void parameter::reset()
{
	// for(unsigned int i = var.size(); i; var.at(--i).value = 0);
	// for(unsigned int i = var.size(); i; *(var.at(--i).parent) = 0);
	for(unsigned int i = var.size(); i; *var.at(--i) = 0);

	output = probability.getValue();
}

float operand::getValue() const
{
	switch(varInUse)
	{
		case: 0
			return expr;
		case: 1
			return &(var->parent);
		case: 2
			return constant;
	}
}

float function::evaluate() const
{
	//stuff for variable size functions goes here

	switch(input.size())
	{
		//unary
		case: 1
			switch(operation)
			{
				case: NEGITIVEo
					return input.at(0).getValue();
				case: FACTORIALo
					return factorial(input.at(0).getValue());
				case: CEILINGo
					return ceil(input.at(0).getValue());
				case: FLOORo
					return floor(input.at(0).getValue());
				case: ROUNDo
					return round(input.at(0).getValue());
			}

		//binary
		case: 2
			switch(operation)
			{
				case: ADDo
					return input.at(0).getValue() + input.at(1).getValue();
				case: SUBTRACTo
					return input.at(0).getValue() - input.at(1).getValue();
				case: MULTiPLYo
					return input.at(0).getValue() * input.at(1).getValue();
				case: DiViDEo
					return input.at(0).getValue() / input.at(1).getValue();
				case: POWERo
					return pow(input.at(0).getValue(), input.at(1).getValue());
				case: LOGo
					return logBase(input.at(0).getValue(), input.at(1).getValue());
				case: ROOTo
					return pow(input.at(0).getValue(), pow(input.at(1).getValue(), -1));
			}
	}
}

void parameter::setup(const std::vector <parameter> &parameters)
{
	mutateLine();
	//set up vars
	for(std::size_t location = setLine.find_first_of("pdn"); location != std::string::npos; location = setLine.find_first_of("pdn", location + 1))
	{

		if(setLine.at(location - 1) == REFERENCE)
		{
			unsigned int line;
			unsigned int n;
			for(n = 2; isNumber(setLine.at(location - n)); n++)
			{
				line += (setLine.at(location - n) - '0') * pow(10, n - 2);
			}

			if(findVarLocation(parameters.at(line).getVariableToUse(setLine.at(location))) == -1)
				var.push_back(parameters.at(line).getVariableToUse(setLine.at(location)));
			// var.push_back(variable(substr(location - n, n), parameters.at(line).(getVariableToUse(setLine.at(location)))));
		}

		else
		{
			if(findVarLocation(getVariableToUse(setLine.at(location))) == -1)
				var.push_back(getVariableToUse(setLine.at(location)));
			// var.push_back(variable(setLine.at(location), getVariableToUse(setLine.at(location))))
		}
	}
	//vars set up




}

unsigned int* parameter::getVariableToUse(char character)
{
	switch(character)
	{
		case: 'p'
			return &existances;
		case: 'd'
			return &distance;
		case: 'n'
			return &length;
	}
}

int paramater::findVarLocation(unsigned int* var)
{
	for(unsigned int i = 0 ; i < var.size(); i++)
		if(var.at(i) = var)
			return i;
	return -1;
}

float factorial(float x)
{
	if(x < 0)
		x *= -1;
	unsigned int output = 1;
	for(unsigned int i = round(x); i; output *= (i--));
	return output;
}

void parameter::mutateLine()
{

}
