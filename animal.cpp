#include <iostream>
#include <string>
#include "animal.h"
using namespace std;
//construstors and definition of functions
int Animal::0; // initializes the static variable
Animal::Animal()
{
	count++; //adds to the statis count by 1 everytime
}
string Animal::speak()
{
	return "test";
}
int Canine::count = 0;  //initializes static variable
Canine::Canine()
{
	count++; //adds canine to static variable
}
string Dog::speak()
{
	return "Woof";
}
int Feline::count = 0;  //initializes static variable
Feline::Feline()
{
	count++; //adds feline to static variable
}
string Feline::speak()
{
	return "Purr";
}
Dog::Dog()
{
	name = "dog";
}
Dog::Dog(string dname):name(dname)
{
	name = dname;
}
string Dog::getName(string name) {
	return name;
}
Cat::Cat()
{
	name = "Cat";
}
Cat::Cat(string cname)
{
	name = cname;
}
string Cat::getName()
{
	return name;
}
Wolf::Wolf() {
}
string	Wolf::howl()
{
	return "Howl";
}

