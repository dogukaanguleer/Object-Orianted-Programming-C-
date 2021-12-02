#ifndef __NOT_H__
#define __NOT_H__

#include <string>
#include "gate.h"
class Not : public Gate
{

public:
    int eval();
    void set_output_name(string output);
    void set_input(string input_name);
    string get_output();
    string get_input1();
    void set_point1(Gate *p1);
    void initial_func_call_controll();

private:
    string name;
    string out;
    int output_value;
    Gate *inp1;
    bool call_control;
};





#endif