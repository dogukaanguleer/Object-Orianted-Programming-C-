
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "input.h"
using namespace std;
int Input::eval()
{
    return out;
}
/*Get set functions to access private data*/
void Input::set_output_name(string output)
{
    this->output_name = output;
}

string Input::get_output()
{
    return this->output_name;
}

void Input::set_out(int value)
{
    this->out = value;
}
