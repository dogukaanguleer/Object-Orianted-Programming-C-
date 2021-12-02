#ifndef __GATE_H__
#define __GATE_H__

#include <string>
using namespace std;

class Gate
{
public:
    virtual int eval();
    
    virtual void set_input(string input_name);                                  //OUTPUT NOT FLIPFLOP
    virtual void set_inputs(string input1, string input2);                        //AND OR
    virtual void set_output_name(string output);                                  //INPUT AND OR NOT FLIPFLOP
    virtual void set_outputs(string out1, string out2, string out3, string out4); // FLIPFLOP
    virtual void set_point1(Gate *p1);
    virtual void set_point2(Gate *p2);
    virtual void set_out(int value);

    virtual string get_input1();
    virtual string get_input2();
    virtual string get_output();//OUTPUT AND OR
    virtual void print();
    virtual void initial_func_call_controll();
    virtual void set_memory();
    virtual int get_output_value();
};
#endif