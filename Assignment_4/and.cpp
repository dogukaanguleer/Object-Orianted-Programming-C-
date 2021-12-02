#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "and.h"

using namespace std;

int And::eval()
{
    int temp1, temp2;
    if (this->call_control == 0) /*if the function has never been called before*/
    {

        this->call_control = 1; /* to not call function again */
        temp1 = in1->eval(); 
        temp2 = in2->eval();
        this->output_value = temp1 && temp2;
        return this->output_value;
    }
    else /*if function calls before*/
    {
        return this->output_value; 
    }
}
/*set get functions to access private data.*/
void And::set_output_name(string output) 
{
    this->out = output;
}
void And::set_inputs(string input1, string input2)
{
    this->input1_name = input1;
    this->input2_name = input2;
}
string And::get_output()
{
    return this->out;
}
string And::get_input1()
{
    return input1_name;
}
string And::get_input2()
{
    return input2_name;
}
void And::set_point1(Gate *p1)
{
    in1 = p1;
}
void And::set_point2(Gate *p2)
{
    in2 = p2;
}

void And::initial_func_call_controll()
{
    this->call_control = 0;
}
