#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>
#include "gate.h"

using namespace std;

class Output : public Gate
{
public:
    int eval();
    void set_input(string input_name);
    string get_input1();
    void set_point1(Gate *p1);
    int get_output_value();

private:
    string name;
    Gate *input;
    int output_value;
};
#endif