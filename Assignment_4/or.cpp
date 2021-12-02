#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "or.h"

using namespace std;

int Or::eval()
{
    int temp1, temp2;
    if (this->call_control == 0) /*if the function has never been called before*/
    {
        this->call_control = 1;
        temp1 = in1->eval();
        temp2 = in2->eval();
        this->output_value = temp1 || temp2;
        return this->output_value;
    }
    else
    {
        return this->output_value;
    }
}
/*Get set functions to access data*/
void Or::set_output_name(string output)
{
    this->out = output;
}
void Or::set_inputs(string input1, string input2)
{
    this->input1_name = input1;
    this->input2_name = input2;
}
string Or::get_output()
{
    return this->out;
}
string Or::get_input1()
{
    return input1_name;
}
string Or::get_input2()
{
    return input2_name;
}
void Or::set_point1(Gate *p1)
{
    in1 = p1;
}
void Or::set_point2(Gate *p2)
{
    in2 = p2;
}

void Or::initial_func_call_controll()
{
    this->call_control = 0;
}
