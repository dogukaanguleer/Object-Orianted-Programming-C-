
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "decoder.h"

using namespace std;

int Decoder::eval()
{
    int temp1 = inp1->eval();
    int temp2 = inp2->eval();
    //cout << temp1 << temp2 << " ";

    if (temp1 == 0 && temp2 == 0)
    {
        this->out[0] = 1;
        this->out[1] = 0;
        this->out[2] = 0;
        this->out[3] = 0;
    }
    else if (temp1 == 0 && temp2 == 1)
    {
        this->out[0] = 0;
        this->out[1] = 1;
        this->out[2] = 0;
        this->out[3] = 0;
    }
    else if (temp1 == 1 && temp2 == 0)
    {
        this->out[0] = 0;
        this->out[1] = 0;
        this->out[2] = 1;
        this->out[3] = 0;
    }
    else if (temp1 == 1 && temp2 == 1)
    {
        this->out[0] = 0;
        this->out[1] = 0;
        this->out[2] = 0;
        this->out[3] = 1;
    }
    return 1;
}
/*Get set functions to access private data*/
void Decoder::print()
{
    cout << out[0] << " " << out[1] << " " << out[2] << " " << out[3] << endl;
}
void Decoder::set_outputs(string out1, string out2, string out3, string out4)
{
    this->outputs[0] = out1;
    this->outputs[1] = out2;
    this->outputs[2] = out3;
    this->outputs[3] = out4;
}
void Decoder::set_inputs(string input1, string input2)
{
    this->input1_name = input1;
    this->input2_name = input2;
}
string Decoder::get_input1()
{
    return input1_name;
}
string Decoder::get_input2()
{
    return input2_name;
}
void Decoder::set_point1(Gate *p1)
{
    inp1 = p1;
}
void Decoder::set_point2(Gate *p2)
{
    inp2 = p2;
}
