#ifndef __DECODER_H__
#define __DECODER_H__

#include <string>
#include "gate.h"



class Decoder : public Gate
{
public:
    int eval();
    void print();
    void set_outputs(string out1, string out2, string out3, string out4);
    void set_inputs(string input1, string input2);
    string get_input1();
    string get_input2();
    void set_point1(Gate *p1);
    void set_point2(Gate *p2);

private:
    string input1_name;
    string input2_name;
    int out[4];
    string outputs[4];
    Gate *inp1;
    Gate *inp2;
};


#endif