#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "output.h"


using namespace std;

int Output::eval()
{
    this->output_value = input->eval();

    return this->output_value;
}
void Output::set_input(string input_name)
{
    this->name = input_name;
}
string Output::get_input1()
{
    return this->name;
}
void Output::set_point1(Gate *p1)
{
    input = p1;
}
int Output::get_output_value()
{
    return this->output_value;
}
