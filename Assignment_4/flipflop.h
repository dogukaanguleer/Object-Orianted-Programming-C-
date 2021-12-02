#ifndef __FLIPFLOP_H__
#define __FLIPFLOP_H__

#include <string>
#include "gate.h"

class Flipflop : public Gate
{
public:
    int eval();
    void set_output_name(string output);
    void set_input(string input_name);
    string get_output();
    string get_input1();
    void set_point1(Gate *p1);
    void initial_func_call_controll();
    void set_memory();

private:
    string name;
    string out;
    int output_value;
    int memory;
    Gate *inp1;
    bool call_control;
};


#endif