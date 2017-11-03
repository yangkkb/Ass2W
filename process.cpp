
//==================Include Headfiles
//for ANSC C stander headfiles
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autoptr.h"

//for C++ headfiles
#include <iostream>
//Graph
#include "Graph.h"
//Parser
#include "Parser.h"

//================== some defines
#define PDEBUG  false


//================== Constant define
namespace project {
    const int ReadBuffer_MaxLen = 0xFFFF; //64KB for read buffer
}

//namespace decleartion
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using namespace project;


namespace project {

    /*  this function check if the first command is s
     *  args:
     *      ptrEle: the pointer of parser element of command V
     *  return:
     *      bool: if true means format correct.
     *  note:
     *      if there is anythign wrong function return false. and print error
     *          message on stderr
     */
    bool isCommands(parser::_Element* ptrEle) {
        typedef parser::_Element::_ElementList::iterator EleIter;

        parser::_Element* ptrEle_Current;
        parser::_Element* ptrEle_Root;
        EleIter _first, _end;

        if (ptrEle == 0) {
            std::cerr << "Error:" << "NULL pointer of element or point!" << std::endl;
            return false;
        }
        ptrEle_Root = ptrEle_Current = ptrEle;
        //check root type
        if (ptrEle_Root->type != parser::_Element::type_node) {
            //std::cerr << "Error:" << "Wrong parser element type!" << std::endl;
            return false;
        }
        _first = ptrEle_Root->children.begin();
        _end = ptrEle_Root->children.end();

        // first must be label s
        if (_first == _end) {
            return false;
        }
        ptrEle_Current = *_first;
        if ((ptrEle_Current->type != parser::_Element::type_label) ||
                (ptrEle_Current->data_label != "s")) {
            return false;
        }
        return true;
    }

    /*  this function parsed command s from PtrEle
     *  args:
     *      ptrEle: the pointer of parser element of command V
     *      ptrStart: the pointer for storage pointID start
     *      ptrEnd:the pointer for storage pointID end
     *  return:
     *      bool: if true means format correct.
     *  note:
     *      if there is anythign wrong function return false. and print error
     *          message on stderr
     */
    bool convert2s(parser::_Element* ptrEle, long* ptrStart, long* ptrEnd) {
        typedef parser::_Element::_ElementList::iterator EleIter;

        parser::_Element* ptrEle_Current;
        parser::_Element* ptrEle_Root;
        EleIter _first, _end;

        if (ptrEle == 0 || ptrStart == 0 || ptrEnd == 0) {
            std::cerr << "Error:" << "NULL pointer of element or point!" << std::endl;
            return false;
        }
        ptrEle_Root = ptrEle_Current = ptrEle;
        //check root type
        if (ptrEle_Root->type != parser::_Element::type_node) {
            std::cerr << "Error:" << "Wrong parser element type!" << std::endl;
            return false;
        }
        _first = ptrEle_Root->children.begin();
        _end = ptrEle_Root->children.end();

        // first must be label s
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if ((ptrEle_Current->type != parser::_Element::type_label) ||
                (ptrEle_Current->data_label != "s")) {
            std::cerr << "Error:" << "Wrong command ,expected s!" << std::endl;
            return false;
        }
        //second check if it is a uinteger
        _first++;
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if (ptrEle_Current->type != parser::_Element::type_uinteger) {
            std::cerr << "Error:" << "Wrong fromat expected an unsigned!" << std::endl;
            return false;
        }
        *ptrStart = ptrEle_Current->data_uinteger;
        //third check if it is a uinteger
        _first++;
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if (ptrEle_Current->type != parser::_Element::type_uinteger) {
            std::cerr << "Error:" << "Wrong format expected an unsigned!" << std::endl;
            return false;
        }
        *ptrEnd = ptrEle_Current->data_uinteger;
        //4th check if it is end
        _first++;
        if (_first != _end) {
            std::cerr << "Error:" << "Wrong format too more!" << std::endl;
            return false;
        }
        return true;
    }

    /*  this function parsed command V from PtrEle
     *  args:
     *      ptrEle: the pointer of parser element of command V
     *      ptrV: the pointer for storage ptrV
     *  return:
     *      bool: if true means format correct.
     *  note:
     *      if there is anythign wrong function return false. and print error
     *          message on stderr
     */
    bool convert2V(parser::_Element* ptrEle, long* ptrV) {
        typedef parser::_Element::_ElementList::iterator EleIter;

        parser::_Element* ptrEle_Current;
        parser::_Element* ptrEle_Root;
        EleIter _first, _end;

        if (ptrEle == 0 || ptrV == 0) {
            std::cerr << "Error:" << "NULL pointer of element or V!" << std::endl;
            return false;
        }
        ptrEle_Root = ptrEle_Current = ptrEle;
        //check root type
        if (ptrEle_Root->type != parser::_Element::type_node) {
            std::cerr << "Error:" << "Wrong parser element type!" << std::endl;
            return false;
        }
        _first = ptrEle_Root->children.begin();
        _end = ptrEle_Root->children.end();

        // first must be label V
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if ((ptrEle_Current->type != parser::_Element::type_label) ||
                (ptrEle_Current->data_label != "V")) {
            std::cerr << "Error:" << "Wrong command ,expected V!" << std::endl;
            return false;
        }
        //second check if it is a uinteger
        _first++;
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if (ptrEle_Current->type != parser::_Element::type_uinteger) {
            std::cerr << "Error:" << "Wrong fromat expected an unsigned!" << std::endl;
            return false;
        }
        *ptrV = ptrEle_Current->data_uinteger;
        //third check if it is end
        _first++;
        if (_first != _end) {
            std::cerr << "Error:" << "Wrong fromat too more!" << std::endl;
            return false;
        }
        return true;
    }

    /*  this function convert parsed element to Graph. auto generated
     *  template args:
     *      _T_Graph: the template for graph
     *  args:
     *      ptrEle: pointer of element of parser result
     *      _graph: reference of graph
     *  return:
     *      bool: if it is sucess
     *  exceptions:
     *      graph::Exception: when operate with graph, this function direct
     *          throw exceptions from graph
     *  note:
     *      if there is wrong format in ptrEle , we will print error on stderr
     *          and return false. that means you need wait another input
     */
    template <typename _Tp_Graph>
    bool convert2Graph(parser::_Element* ptrEle, _Tp_Graph& _graph)
    throw (graph::Exception) {
        typedef _Tp_Graph _Graph;
        //typedef graph::_T_Graph<long, long> _Graph;
        typedef parser::_Element::_ElementList::iterator EleIter;
        _Graph& graph = _graph;
        parser::_Element* ptrEle_Root = ptrEle;
        parser::_Element* ptrEle_Current;
        EleIter _first, _end;
        EleIter _first_Edge, _end_Edge;
        long point_start, point_end;
        if (ptrEle == 0) {
            std::cerr << "Error:" << "NULL pointer of element!" << std::endl;
            return false;
        }
        // free graph
        graph.release();
        //check root type
        if (ptrEle_Root->type != parser::_Element::type_node) {
            std::cerr << "Error:" << "Wrong parser element type!" << std::endl;
            return false;
        }
        _first = ptrEle_Root->children.begin();
        _end = ptrEle_Root->children.end();
        // check command E
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if ((ptrEle_Current->type != parser::_Element::type_label) ||
                (ptrEle_Current->data_label != "E")) {
            std::cerr << "Error:" << "Wrong Command!" << std::endl;
            return false;
        }
        _first++;
        //check second for operator {
        if (_first == _end) {
            std::cerr << "Error:" << "Wrong command format expected {!" << std::endl;
            return false;
        }
        ptrEle_Current = *_first;
        if ((ptrEle_Current->type != parser::_Element::type_operator) ||
                (ptrEle_Current->data_operator != "{")) {
            std::cerr << "Error:" << "Wrong command format expected {!" << std::endl;
            return false;
        }
        _first++;
        //third must be node
        ptrEle_Current = *_first;
        //4th must be }
        _first++;
        //5th must be end
        _first++;
        if (_first != _end) {
            std::cerr << "Error:" << "Wrong command format too more!" << std::endl;
            return false;
        }
        //in {} must paired <>
        _first = ptrEle_Current->children.begin();
        _end = ptrEle_Current->children.end();
        //loop
        while (_first != _end) {
            ptrEle_Current = *_first;
            // first check if it is <
            if ((ptrEle_Current->type != parser::_Element::type_operator) ||
                    (ptrEle_Current->data_operator != "<")) {
                std::cerr << "Error:" << "Wrong command format expected <!" << std::endl;
                return false;
            }
            // following must be node and add edge
            _first++;
            ptrEle_Current = *_first;
            _first_Edge = ptrEle_Current->children.begin();
            _end_Edge = ptrEle_Current->children.end();
            // first must be an uinteger
            if ((_first_Edge == _end_Edge) ||
                    ((*_first_Edge)->type != parser::_Element::type_uinteger)) {
                std::cerr << "Error:" << "Wrong command format expected unsigned integer!" << std::endl;
                return false;
            }
            ptrEle_Current = *_first_Edge;
            point_start = ptrEle_Current->data_uinteger;
            _first_Edge++;
            //second must be ,
            if ((_first_Edge == _end_Edge) ||
                    ((*_first_Edge)->type != parser::_Element::type_operator) ||
                    ((*_first_Edge)->data_operator != ",")) {
                std::cerr << "Error:" << "Wrong command format expected ," << std::endl;
                return false;
            }
            _first_Edge++;
            // third must be an uinteger
            if ((_first_Edge == _end_Edge) ||
                    ((*_first_Edge)->type != parser::_Element::type_uinteger)) {
                std::cerr << "Error:" << "Wrong command format expected unsigned integer!" << std::endl;
                return false;
            }
            ptrEle_Current = *_first_Edge;
            point_end = ptrEle_Current->data_uinteger;
            _first_Edge++;
            //final must be end
            if (_first_Edge != _end_Edge) {
                std::cerr << "Error:" << "Wrong command format too more in <>!" << std::endl;
                return false;
            }
            // Add Edge
            graph(point_start, point_end) = 1;
            graph(point_end, point_start) = 1;
            graph(point_start) = 0;
            graph(point_end) = 0;
            // following must be > skip
            _first++;
            // if it is end or check if it is ,
            _first++;
            if (_first == _end) {
                break;
            } else {
                ptrEle_Current = *_first;
                if ((ptrEle_Current->type != parser::_Element::type_operator) ||
                        (ptrEle_Current->data_operator != ",")) {
                    std::cerr << "Error:" << "Wrong command format expected ," << std::endl;
                    return false;
                }
            }
            //Next
            _first++;
        }

        return true;
    }

}// end namespace


void Process(graph::_T_Graph<long, long>& Graph) {
    //variables define
    char* inputBufferV = new char[ReadBuffer_MaxLen];
    char* inputBufferE = new char[ReadBuffer_MaxLen];
    char* inputBufferS = new char[ReadBuffer_MaxLen];
    bool bInputRith;
    bool bDirectExit;
    bool bhasVaildGraph;
    long v, s_start, s_end;
    //Parser
    parser::auto_ptr<parser::Parser> ptrParserImp;
    parser::auto_ptr<parser::_Element> ptrParserEle;
    parser::_Factory parserFactory;

    bDirectExit = false;
    bhasVaildGraph = false;
    //get Factory Instance
    try {
        parserFactory = parser::factory();
        ptrParserImp.reset(parserFactory.forInstance("Ass2"));
    } catch (parser::Exception & e) {
        cerr << "Error:";
        e.printMSG(cerr);
        cerr << endl;
    }
    while (1) {
        // read first line V
        bInputRith = false;
        while (bInputRith == false) { //loop for V
            if (cin.eof()) {
                bDirectExit = true;
                break;
            }
#if PDEBUG==true
            cout << "Write V: " << endl;
#endif
            cin.getline(inputBufferV, project::ReadBuffer_MaxLen);
#if PDEBUG==true
            cout << "Read A Line V: " << inputBufferV << endl;
#endif
            if (strlen(inputBufferV) == 0) {
                bDirectExit = true;
                break;
            }
#if PDEBUG==true
            cout << "Length of V is: " << strlen(inputBufferV) << endl;
#endif
            try {
                ptrParserEle.reset(ptrParserImp->parser(inputBufferV));
            } catch (parser::Exception & e) {
                cerr << "Error:";
                e.printMSG(cerr);
                cerr << endl;
                continue;
            } catch (std::exception & e) {
                cerr << "Error:";
                cerr << "something else happen in v process";
                cerr << endl;
                bDirectExit = true;
                break;
            }
            if ((bhasVaildGraph == true) && (isCommands(ptrParserEle.get()))) { //if graph is vaild and s is command
                // preform s
                if (convert2s(ptrParserEle.get(), &s_start, &s_end) == false) {
                    continue;
                }
                //start search
                try {
                    graph::searchPath(Graph, s_start, s_end, 0x7FFFFFFF);
                    Graph[s_end].printPath(cout, '-');
                    cout << endl;
                } catch (graph::Exception & e) {
                    cerr << "Error:";
                    e.printMSG(cerr);
                    cerr << endl;
                    continue;
                }
                continue; // wait for V or s
            } else {
                if (convert2V(ptrParserEle.get(), &v) == false) {
                    continue;
                }
            }
#if PDEBUG==true
            cout << "We got a V: " << v << endl;
#endif
            std::cout << inputBufferV << endl;
            if (v == 0) {
                cerr << "Error:" << "V can not be 0" << endl;
                continue;
            }
            Graph.Min_ID = 0;
            Graph.Max_ID = v - 1;
            bInputRith = true;
            /*  A new vaild V command will make graph refresh
             */
            bhasVaildGraph = false;
        } //end loop for V
        if (bDirectExit == true) {
            break;
        }

        // read second line E
        bInputRith = false;
        while (bInputRith == false) { //loop for e
            if (cin.eof()) {
                bDirectExit = true;
                break;
            }
#if PDEBUG==true
            cout << "Write E: " << endl;
#endif
            cin.getline(inputBufferE, project::ReadBuffer_MaxLen);
#if PDEBUG==true
            cout << "Read A Line E: " << inputBufferE << endl;
#endif
            if (strlen(inputBufferE) == 0) {
                bDirectExit = true;
                break;
            }
            try {
                ptrParserEle.reset(ptrParserImp->parser(inputBufferE));
            } catch (parser::Exception & e) {
                cerr << "Error:";
                e.printMSG(cerr);
                cerr << endl;
                continue;
            }
            std::cout<<inputBufferE<<endl;
            //Here convert ele 2 graph
            try {
                if (convert2Graph(ptrParserEle.get(), Graph) == false) {
                    continue;
                }
            } catch (graph::Exception & e) {
                cerr << "Error:";
                e.printMSG(cerr);
                cerr << endl;
                continue;
            }
#if PDEBUG==true
            cout << "We got a Graph: " << endl;
            Graph.printGraph(cout);
#endif
            bInputRith = true;
            bhasVaildGraph = true;
        } //end loop for E
        if (bDirectExit == true) {
            break;
        }

        // read third line s
        bInputRith = false;
        while (bInputRith == false) { //loop for s
            if (cin.eof()) {
                bDirectExit = true;
                break;
            }
#if PDEBUG==true
            cout << "Write S: " << endl;
#endif
            cin.getline(inputBufferS, project::ReadBuffer_MaxLen);
#if PDEBUG==true
            cout << "Read A Line S: " << inputBufferS << endl;
#endif
            if (strlen(inputBufferS) == 0) {
                bDirectExit = true;
                break;
            }
            try {
                ptrParserEle.reset(ptrParserImp->parser(inputBufferS));
            } catch (parser::Exception & e) {
                cerr << "Error:";
                e.printMSG(cerr);
                cerr << endl;
                continue;
            }
            //Here convert ele 2 s
            if (convert2s(ptrParserEle.get(), &s_start, &s_end) == false) {
                continue;
            }
#if PDEBUG==true
            cout << "We got a search: " << s_start << " to " << s_end << endl;
#endif
            //start search
            try {
                graph::searchPath(Graph, s_start, s_end, 0x7FFFFFFF);
#if PDEBUG==true
                cout << "We got a search result! " << endl;
#endif
                Graph[s_end].printPath(cout, '-');
                cout << endl;
            } catch (graph::Exception & e) {
                cerr << "Error:";
                e.printMSG(cerr);
                cerr << endl;
                // if there is something wrong in search, then s should pass
                // and watiing another V or S
                //continue;
            }
            bInputRith = true;
        } //end loop for S
        if (bDirectExit == true) {
            break;
        }
    }

    delete[] inputBufferV;
    delete[] inputBufferE;
    delete[] inputBufferS;
}
