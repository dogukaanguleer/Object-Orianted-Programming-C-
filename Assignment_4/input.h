#ifndef __INPUT_H__
#define __INPUT_H__

#include <string>
#include "gate.h"

using namespace std;
class Input : public Gate
{
public:
    int eval();
    void set_output_name(string output);
    string get_output();
    void set_out(int value);

private:
    string output_name;
    int out;
    Gate *inp1;
};

#endif