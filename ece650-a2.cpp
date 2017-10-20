
//==================Include Headfiles
//for ANSC C stander headfiles
#include <stdio.h>
#include <stdlib.h>
//for C++ headfiles
#include <iostream>
//Graph
#include "Graph.h"
//Parser
//#include "Parser.h"

//================== Constant define
namespace project {
    const int ReadBuffer_MaxLen = 0xFFFF; //64KB for read buffer
}

//namespace decleartion
using std::cin;
using std::cout;
using std::endl;
using namespace project;

//================== Example demos
void examples(graph::_T_Graph<long, long> & Graph);
//for code source see examples.cpp

//==================void Process function

void Process(graph::_T_Graph<long, long>& Graph);


/* main function
 * 
 */
int main(int argc, char** argv) {
    graph::_T_Graph<long, long> Graph;
    //example for how to use my graph lib
    //examples(Graph); //See More in this function

    // Here truly deal with the problem
    Process(Graph);
    return (EXIT_SUCCESS);
}

