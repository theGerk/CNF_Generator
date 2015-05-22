//libraries included
#include <fstream>
#include <cstring>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>


//Defined constants -- Will be updated continiously
	//variables
		#define LENGTH 'n'
		#define EXISTANCES 'p'
		#define DISTANCE 'd'
		
		//string of all of variables
			#define VARIABLES "npd"

	//operators in input
		#define REFERENCEi '#'	//not an operator as it is now
		#define SEPERATORi ','	//not an operator
		
		//Unary
			#define NEGITIVEi '-'	//2
			#define FACTORIALi '!'	//3
			#define CEILINGi 'C'	//6
			#define FLOORi 'F'		//6
			#define ROUNDi 'R'		//6

		//Binary
			#define ADDi '+'		//7
			#define SUBTRACTi '-'	//7
			#define MULTIPLYi '*'	//5
			#define DIVIDEi '/'		//5
			#define POWERi '^'		//4
			#define LOGi '~'		//4
			#define ROOTi '`'		//4
			#define DECIMALi '.'	//1

	//Other functions without operators


	//operators in memory
		#define REFERENCEo '#'	//not an operator as it is now
		#define SEPERATORo ','	//not an operator
		
		//Unary
			#define NEGITIVEo '-'	//2
			#define FACTORIALo '!'	//3
			#define CEILINGo 'C'	//6
			#define FLOORo 'F'		//6
			#define ROUNDo 'R'		//6

		//Binary
			#define ADDo '+'		//7
			#define SUBTRACTo '-'	//7
			#define MULTIPLYo '*'	//5
			#define DIVIDEo '/'		//5
			#define POWERo '^'		//4
			#define LOGo '~'		//4
			#define ROOTo '`'		//4
			#define DECIMALo '.'	//1

		//Other functions without operators (sine, cosine, tangent, sumation)


//Benji is doing some thinking here
//some example equations being broken up
// a + Cb 		----		insert parenthse, you can tell where it goes because it surrounds everything to the end in this case
// a + (Cb)
//+(a, Cb)
//+(a, C(b))

// a * Cb.7		----		insert parenthse, you can tell where it goes because the one other operator after it has lower value?						<-------				WRONG, see next example
// a * (Cb.7)	----		alterntive reason is that you can tell where the parntheses end based on what has greater value then the previous operator 	<-------				Seems correct!
//*(a, Cb.7)	----		What if the parenthse 
//*(a, C(b.7))
//*(a, C(.(b,7)))

// a.Cb * 7
// a.(Cb) * 7
// *(a.(Cb), 7)
// *(.(a, Cb), 7)
// *(.(a, C(b)), 7)

//so if there is an operator before the unary operator put parentheses around it?
// R!b * -4.Ca/Fi
// R(!b) * (-4.(Ca)/(Fi))
//R(!b * (-4.(Ca)/(Fi)))
//R(*(!b, -4.(Ca)/(Fi))))
//R(*(!(b), -(4.(Ca)/(Fi))))
//R(*(!(b), -(.(4, Ca/(Fi)))))
//R(*(!(b), -(.(4, /(Ca, Fi)))))
//R(*(!(b), -(.(4, /(C(a), F(i))))))

//It seems to work wonders like this



//Declarations:
class parameter;
class function;
class operand;

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

//complete
bool isNumber(const char &input);
//checks if input is a number 0 - 9

//complete
void clean(std::string &input);
//takes off paranetheses at ends of string if the parentheses needlessly surround it

//complete
unsigned int operatorSize(unsigned int i, const std::string &input);
//returns the number of inputs an operation needs

//complete
unsigned int inverseOrderOfOperation(const char& Operator, unsigned int size);			//complete
unsigned int inverseOrderOfOperation(unsigned int location, const std::string &sting);	//complete
//returns the value of the inverted order of operations

//complete
bool isOpeartor_o(char character);
bool isOpeartor_i(char character);
//checks if it is a character

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

		//complete
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
		std::vector <operand> inputs;	//the values that are going to be operated on
		char operation;					//char representing 

	public:
		//functions
		//complete - Will be upadated
		float evaluate() const;
		//gets output of function

		//in progress
		void setup(const std::string &input, const std::vector <unsigned int*> &vars);
		//sets up function

		//complete
		function(const std::string &input, const std::vector <unsigned int*> &vars)	{setup(input, vars);}
		//calls setup
};

class operand{
	private:
		unsigned short varInUse;	//says which member variable is bing used
		// 0 --> expr
		// 1 --> var
		// 2 --> constant

		//ONLY 1 MAY BE USED
		function expr;
		unsigned int *var;
		float constant;

	public:
		//public member functions
		//complete
		void setup(std::string input, const std::vector <unsigned int*> &vars);
		//sets up operand

		//complete
		float getValue() const;
		//evaluates if it is true or false and returns value

		//complete
		operand(const std::string &input, const std::vector <unsigned int*> &vars)	{setup(input, vars);}
		//calls setup
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
	for(unsigned int i = parameters.size(); i; parameters.at(--i).setup(parameters));	//beatifully consice but hard to read line of code is beautifuly consice and hard to read :P	Suck on my poor style Max!
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
	// getline(input, setLine);
	while(input.peak() != '\n' || input.peak() != std::endl)
	{
		if(input.peak() = ' ')
			input.get();
		else
			setLine += input.get(); 
	}
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
			return &var;
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
				case: MULTIPLYo
					return input.at(0).getValue() * input.at(1).getValue();
				case: DIVIDEo
					return input.at(0).getValue() / input.at(1).getValue();
				case: POWERo
					return pow(input.at(0).getValue(), input.at(1).getValue());
				case: LOGo
					return logBase(input.at(0).getValue(), input.at(1).getValue());
				case: ROOTo
					return pow(input.at(0).getValue(), pow(input.at(1).getValue(), -1));
				case: DECIMALo
					return input.at(0).getValue() + input.at(1).getValue() * pow(10, -1 * ceil(logBase(10, input.at(1).getValue())));
			}
	}
}

void parameter::setup(const std::vector <parameter> &parameters)
{
	//switching from input symbols to stored symbols would be a good thing to do here
	//will be done in future version of prograam

	unsigned int colon = setLine.find_last_of(":");

	//set up update
	std::vector <unsigned int*> fixThisLater;
	operand findUpdate(setLine.substr(colon + 1), fixThisLater);
	findUpdate.getValue();
	//update set up

	setLine.resize(colon);
	std::string newString;
	unsigned int loc = 0;

	//set up vars
	for(std::size_t location = setLine.find_first_of(VARIABLES); location != std::string::npos; location = setLine.find_first_of(VARIABLES, location + 1))
	{
		if(setLine.at(location - 1) == REFERENCEi)
		{
			unsigned int n;
			unsigned int line = 0;
			for(n = 2; isNumber(setLine.at(location - n)); n++)
			{
				line += (setLine.at(location - n) - '0') * pow(10, n - 2);
			}			

			int temp = findVarLocation(parameters.at(line).getVariableToUse(setLine.at(location)));
			if(temp == -1)
				var.push_back(parameters.at(line).getVariableToUse(setLine.at(location)));
			// var.push_back(variable(substr(location - n, n), parameters.at(line).(getVariableToUse(setLine.at(location)))));

			//add to newString
			newString += setLine.substr(loc, location - loc - n + 1);
			loc = location + 1;
			newString += REFERENCEo;
			newString += std::to_string(temp);
			//added to newString
		}

		else
		{
			int temp = findVarLocation(getVariableToUse(setLine.at(location)));
			if(temp == -1)
				var.push_back(getVariableToUse(setLine.at(location)));
			// var.push_back(variable(setLine.at(location), getVariableToUse(setLine.at(location))))

			//add to newString
			newString += setLine.substr(loc, location - loc);
			loc = location + 1;
			newString += REFERENCEo;
			newString += std::to_string(temp);
			//added to newString
		}

	}
	//vars set up

	probability.setup(newString, var);
	output = probability.getValue();

	setLine.resize(0);
}

unsigned int* parameter::getVariableToUse(char character)
{
	switch(character)
	{
		case: EXISTANCES
			return &existances;
		case: DISTANCE
			return &distance;
		case: LENGTH
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

void operand::setup(std::string &input, const std::vector <unsigned int*> &vars)
{
	clean(input);

	if(input.at(0) == REFERENCEo)
	{
		unsigned int i;
		for(i = 1; isNumber(input.at(i)); i++);
		if(i == input.size())
		{
			//this is a variable
			varInUse = 1;
			unsigned int temp = 0;
			unsigned int counter = 0;
			for(unsigned int i = input.size(); --i; temp += pow(10, counter++) * input.at(i));
			var = vars.at(temp);
		}
		else
		{
			//this is an equation
			varInUse = 0;
			expr.setup(input, vars);
		}
	}
	else if(isNumber(input.at(0)))
	{
		unsigned int i;
		for(i = 1; isNumber(input.at(i)); i++);
		if(i == input.size())
		{
			//this is a constant
			varInUse = 2;
			constant = 0;
			unsigned int counter = 0;
			for(unsigned int i = input.size(); i--; constant += pow(10, counter++) * input.at(i));
		}
		else
		{
			//this is an equation
			varInUse = 0;
			expr.setup(input, vars);
		}
	}
	else
	{
		//this is an equation
		varInUse = 0;
		expr.setup(input, vars);
	}
}

bool isNumber(const char &input)
{
	return (input >= '0' && input <= '9');
}

void clean(std::string &input)
{
	while(input[0] == START_PARA())
	{
		bool del = true;
		int open = 1;
		for(unsigned int i = 1; i < input.size(); i++)
		{
			if(input[i] == START_PARA())
				open++;
			else if(input[i] == END_PARA())
				open--;

			if(open == 0)
			{
				del = false;
				break;
			}
		}

		if(del)
			input = input.substr(1, input.size() - 2);
		else
			break;
	}
}

void function::setup(const std::string &input, const std::vector <unsigned int*> var)
{
	//find operator and size of operation
	unsigned int last = 0;
	unsigned int loc;
	unsigned int size;
	unsigned int i;

	//i'm not sure how to get in the parentheses but this seems like a good place
	do{
		i = input.size()
		while(i--)
		{
			unsigned int tempSize = operatorSize(i, input);
			if(inverseOrderOfOperation(input.at(i), tempSize) > last)
			{
				loc = i;
				size = tempSize;
			}
		}
	}while(false);

	//operator found and size of operation

	inputs.resize(size);
	std::vector <string> strings(size);

	while(i < input.size())
	{
		if(!loc)
		{

		}
	}
}

unsigned int operatorSize(unsigned int i, const std::string &input)
{
	if(i)
	{
		//this means it is a binary operator
		return 2;
	}
	else
	{
		//check to see if a unary operator witout parentheses after
		if(input.at(1) != '(')
			return 1;

		//look for commas inisde only 1 set of parntheses and add 1
		unsigned int output = 1;
		i = 2;
		for(unsigned int open = 1; i < input.size(); i++)
		{
			if(input.at(itr) == '(')
				open++;
			else if(input.at(itr) != ')')
				open--;
			else if(input.at(itr) == SEPERATORo && open == 1)
				output++;
		}
		return output;
	}
}

unsigned int inverseOrderOfOperation(const char& Operator, unsigned int size)
{
	switch(size)
	{
		case:1
			switch(Operator)
			{
				case: NEGITIVEo
					return 2;
				case: FACTORIALo
					return 3;
				case: CEILINGo
					return 6;
				case: FLOORo
					return 6;
				case: ROUNDo
					return 6;
			}

		case:2
			switch(Operator)
			{
				case: ADDo
					return 7;
				case: SUBTRACTo
					return 7;
				case: MULTIPLYo
					return 5;
				case: DIVIDEo
					return 5;
				case: POWERo
					return 4;
				case: LOGo
					return 4;
				case: ROOTo
					return 4;
				case: DECIMALo
					return 1;
			}
	}
}

unsigned int inverseOrderOfOperation(unsigned int location, const std::string &sting)
{
	return inverseOrderOfOperation(sting.at(location), operatorSize(location, sting));
}

bool isOpeartor_o(char character)
{
	switch(character)
	{
	//unary
		case: NEGITIVEo
		case: FACTORIALo
		case: CEILINGo
		case: FLOORo
		case: ROUNDo

	//Binary
		case: ADDo
		case: SUBTRACTo
		case: MULTIPLYo
		case: DIVIDEo
		case: POWERo
		case: LOGo
		case: ROOTo
		case: DECIMALo
			return true;

		default:
			return false;
	}
}

bool isOpeartor_i(char character)
{
	switch(character)
	{
	//unary
		case: NEGITIVEi
		case: FACTORIALi
		case: CEILINGi
		case: FLOORi
		case: ROUNDi

	//Binary
		case: ADDi
		case: SUBTRACTi
		case: MULTIPLYi
		case: DIVIDEi
		case: POWERi
		case: LOGi
		case: ROOTi
		case: DECIMALi
			return true;

		default:
			return false;
	}
}
