
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include "input.h"
#include "output.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "flipflop.h"
#include "decoder.h"
#include "gate.h"


using namespace std;

/*Counts the number of gate, splits the line*/
int number_of_gate(string str)
{
    int gate_number = 0;
    stringstream s(str); // Used for breaking words
    string word;
    s >> word;
    if (word == "INPUT")
    {
        while (s >> word)
            gate_number++;
        return gate_number;
    }
    if (word == "OUTPUT")
    {
        while (s >> word)
            gate_number++;
        return gate_number;
    }
    return 1;
}

int main()
{
    int inputflag = 0, numberOfGates = 0, temp, inputGatesNumber, count = 0, outputGateNumber;
    ifstream circuit_file("circuit.txt"), input_file("input.txt");
    string str;

    while (getline(circuit_file, str)) 
    {
        temp = number_of_gate(str);
        if (count == 0)
            inputGatesNumber = temp; /* assings the number of input */
        if (count == 1)
            outputGateNumber = temp; /*assings the number of output */

        count++;
        if (temp != -1)
            numberOfGates = numberOfGates + temp;
    }

    /*creates new gate array and */
    Gate **circuit_array = new Gate *[numberOfGates];
    circuit_file.clear();
    circuit_file.seekg(0, circuit_file.beg);

    //===========================================FILL CIRCUIT ARRAY=======================================
    //   According first word of line, it assings values using get set functions.Creates new object 
    int index = 0;
    bool decoder_flag = 0; /*if the circuit has decoder*/
    while (getline(circuit_file, str))
    {
        stringstream s(str);
        string word;
        s >> word;

        if (word == "INPUT")
        {
            for (; s >> word; index++)
            {
                circuit_array[index] = new Input;
                circuit_array[index]->set_output_name(word);
            }
            index--;
        }
        else if (word == "OUTPUT")
        {
            index++;
            for (; s >> word; index++)
            {
                circuit_array[index] = new Output;
                circuit_array[index]->set_input(word);
            }
            index--;
        }
        else if (word == "AND" || word == "OR")
        {
            index++;
            if (word == "AND")
                circuit_array[index] = new And;
            else
                circuit_array[index] = new Or;

            s >> word;
            circuit_array[index]->set_output_name(word);
            s >> word;
            string temp = word;
            s >> word;
            circuit_array[index]->set_inputs(temp, word);
        }
        else if (word == "NOT" || word == "FLIPFLOP")
        {
            index++;
            if (word == "NOT")
                circuit_array[index] = new Not;
            else
                circuit_array[index] = new Flipflop;

            s >> word;
            circuit_array[index]->set_output_name(word);
            s >> word;
            circuit_array[index]->set_input(word);
        }
        else if (word == "DECODER")
        {
            decoder_flag = 1;
            index++;
            circuit_array[index] = new Decoder;
            string array[4];
            for (int i = 0; i < 4; i++)
            {
                s >> array[i];
            }
            circuit_array[index]->set_outputs(array[0], array[1], array[2], array[3]);
            s >> word;
            string temp = word;
            s >> word;
            circuit_array[index]->set_inputs(temp, word);
        }
    }

    //======================================CONNECTS CIRCUITS========================================
    //If the input values of gates equals to another gates output, then points.
    for (int i = inputGatesNumber; i < numberOfGates; i++)
    {
        for (int a = 0; a < numberOfGates; a++)
        {
            if (circuit_array[i]->get_input1() == circuit_array[a]->get_output() && circuit_array[a]->get_output() != "")
            {
                circuit_array[i]->set_point1(circuit_array[a]);
            }
        }

        for (int a = 0; a < numberOfGates; a++)
        {
            if ((circuit_array[i]->get_input2() == circuit_array[a]->get_output()) && circuit_array[a]->get_output() != "" && circuit_array[i]->get_input2() != "")
            {
                circuit_array[i]->set_point2(circuit_array[a]);
            }
        }
    }

    /*Sets a value of 0 for functions that have not yet been used. And sets memory 0 for flipflop*/
    for (int i = 0; i < numberOfGates; i++)
    {
        circuit_array[i]->initial_func_call_controll();
        circuit_array[i]->set_memory();
    }

    int a;
    /*If there is a decoder, it calls eval function of decoder gates.*/
    /*If there is no decoder, calls eval function of output gates*/
    while (getline(input_file, str))
    {
        stringstream s(str);
        string word;
        /*sets the input values from file*/
        for (a = 0; a < inputGatesNumber; a++)
        {
            s >> word;
            if (word == "0")
            {
                circuit_array[a]->set_out(0);
            }
            else if (word == "1")
            {
                circuit_array[a]->set_out(1);
            }
        }

        if (a == inputGatesNumber) /*if the inputs are setted*/
        {
            if (decoder_flag == 1) /*checks circuit has decoder*/
            {
                circuit_array[numberOfGates - 1]->eval();  /*calls eval function of decoder*/
                circuit_array[numberOfGates-1]->print();  /*prints 4 outputs*/
                for (int i = 0; i < numberOfGates; i++)
                {
                    circuit_array[i]->initial_func_call_controll();  /*to call functions again, it resets function situtation*/
                }
            }
            else  /*the circuit doesn't have decoder*/
            {
                for (int i = inputGatesNumber; i < inputGatesNumber + outputGateNumber; i++)
                {
                    circuit_array[i]->eval(); /*calls eval function of each output*/
                    cout << circuit_array[i]->get_output_value()<<" "; /*gets output values */
                }
                cout<<endl;
                for (int i = 0; i < numberOfGates; i++)
                {
                    circuit_array[i]->initial_func_call_controll();  /*to call functions again, it resets function situtation*/
                }
            }
        }
    }
}