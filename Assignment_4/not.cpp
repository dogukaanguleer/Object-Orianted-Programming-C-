#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "not.h"

using namespace std;

int Not::eval()
{
    int temp;
    if (this->call_control == 0) /*if the function has never been called before*/
    {
        this->call_control = 1;

        temp = !inp1->eval();
        this->output_value = temp;
        return temp;
    }
    else
    {
        return this->output_value;
    }
}
/*Get set functions to access data*/
void Not::set_output_name(string output)
{
    this->out = output;
}
void Not::set_input(string input_name)
{
    this->name = input_name;
}
string Not::get_output()
{
    return this->out;
}
string Not::get_input1()
{
    return name;
}
void Not::set_point1(Gate *p1)
{
    inp1 = p1;
}

void Not::initial_func_call_controll()
{
    this->call_control = 0;
}
