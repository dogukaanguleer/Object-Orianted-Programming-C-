#ifndef __AND_H__
#define __AND_H__

#include <string>
#include "gate.h"

class And : public Gate
{
public:
    int eval();
    void set_output_name(string output);
    void set_inputs(string input1, string input2);
    string get_output();
    string get_input1();
    string get_input2();
    void set_point1(Gate *p1);
    void set_point2(Gate *p2);
    void initial_func_call_controll();
private:
    string input1_name;
    string input2_name;
    string out;
    int output_value;
    Gate *in1;
    Gate *in2;
    bool call_control;
};
#endif
