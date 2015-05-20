Will generate just random characters to act as variables, space is used to represent a break between clauses and new line is used to represent break between statements.

It will only uses characters between 33 and 126 as well as possibly using 127 - 255

Defined values:
p = number of previous existences
q = number of inverted existences
n = number of previous variables used
i = number of inverted variables used
d = distance to last instance
b = distance to last inverted instance
may reference another line by using var#line_number
p#4	this references the 4th line's p value

Syntax for a variable:
T: U
F: U
U must be defined if the previous statement is not constant
T, F, and U must be natural numbers
T is the chance for true 
F is the chance for false

Example line:
10/(p + q - d - b) : 3
5/(p + q - d - b) : 1
The first part gives the equation for likely-hood to exist.
The second part gives how often it will be updated
The third part gives the equation for likely-hood to exist with an inversion.
The fourth part gives how often to update the false
Peace-wise functions will be added in future, as for now they are way to hard