#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "gate.h"
using namespace std;
/*base class functions*/
 int Gate:: eval(){return 1;}
 void Gate::set_input(string input_name) {}                                    //OUTPUT NOT FLIPFLOP
 void Gate::set_inputs(string input1, string input2) {}                        //AND OR
 void Gate::set_output_name(string output) {}                                  //INPUT AND OR NOT FLIPFLOP
 void Gate::set_outputs(string out1, string out2, string out3, string out4) {} // FLIPFLOP
 void Gate::set_point1(Gate *p1) {}
 void Gate::set_point2(Gate *p2) {}
 void Gate::set_out(int value) {}

 string Gate::get_input1() { return ""; }
 string Gate::get_input2() { return ""; }
 string Gate::get_output() { return ""; } //OUTPUT AND OR
 void Gate::print() {}
 void Gate::initial_func_call_controll() {}
 void Gate::set_memory() {}
 int Gate::get_output_value() { return 1; }