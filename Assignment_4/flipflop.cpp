#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "flipflop.h"

using namespace std;

int Flipflop::eval()
{
    int temp;

    if (this->call_control == 0)/*if the function has never been called before*/
    {
        temp = inp1->eval();
        this->call_control = 1; 

        if (temp == 1)
        {
            int temp_memory = this->memory;
            this->memory = !(this->memory);
            this->output_value = !temp_memory;
            return !temp_memory;
        }
        else 
        {
            this->output_value = memory;
            return this->memory;
        }
    }
    else
    {
        return this->output_value;
    }
}
/*set gets functions to access private data*/
void Flipflop::set_output_name(string output)
{
    this->out = output;
}
void Flipflop::set_input(string input_name)
{
    this->name = input_name;
}
string Flipflop::get_output()
{
    return this->out;
}
string Flipflop::get_input1()
{
    return name;
}
void Flipflop::set_point1(Gate *p1)
{
    inp1 = p1;
}

void Flipflop::initial_func_call_controll()
{
    this->call_control = 0;
}
void Flipflop::set_memory()
{
    this->memory = 0;
}
