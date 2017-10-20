/* 
 * File:   Parser_Basic.h
 *
 * Created on 2017��10��11��, ����8:41
 */

#ifndef _PARSER_BASIC_H
#define	_PARSER_BASIC_H

//==================Include realted headfiles
#include <deque>
#include <stack>
#include <list>
#include <map>
#include "ostream"

//define a namespace
namespace parser {
    //=================Predeclaration
    class _Element;

    //=================Error Exceptions

    class Exception {
    public:

        Exception() {
        }

        virtual ~Exception() {
        };
        //virtual ~Exception();

        /* print a message on ostr
         * args:
         * ostr: an out stream where ERROR message put out.
         */
        virtual void printMSG(std::ostream& ostr) {
            ostr << "Undescribed Exception";
        };
    };

    class UnImpException : public Exception {
    public:

        UnImpException() {
        };

        ~UnImpException() {
        };

        /*  print a message on ostr
         *  args:
         *      ostr: an out stream where ERROR message put out.
         */
        virtual void printMSG(std::ostream& ostr) {
            ostr << "Unimplemented Parser Class";
        };
    };

    /*  this exception it thrown when parser parsing a string encounterd a
     *  syntax error. for example mismatching operator like () {} [] <>.
     *  Wrong format of integer or real like 9.9.9 or else
     */
    class ParseException : public Exception {
    public:
        /*  errorPos indicated position where error take place. The errorPos is
         *  the offset from char string which is as an arguments when invoked 
         *  parse funciton
         */
        int errorPos;

        /*  errorDescription is a Description of error message
         */
        std::string errorDescription;

        /*  construction function
         *  args:
         *      errPos: the offset of parsing string where error toke place
         *      errDes: error description
         */
        ParseException(int errPos, std::string errDes) {
            errorPos = errPos;
            errorDescription = errDes;
        };

        ~ParseException() {
        };

        /*  print a message on ostr
         *  args:
         *      ostr: an out stream where ERROR message put out.
         */
        virtual void printMSG(std::ostream& ostr) {
            ostr << "Parsing string at: " << errorPos <<
                    " encountered an ERROR: " << errorDescription;
        };
    };
    //=================end of exceptions

    /*  this is a virtual interface class Parser
     *  this class is used to parser a string into _Element format and return
     *  any kind of parser should be a subclass of this .
     */
    class Parser {
    public:

        /* consturction function that do nothing*/
        Parser() {
        }

        /*virtual deconstruction function*/
        virtual ~Parser() {
        }

        /*  this function parser the string or chars of str and return in
         *  _Element format.
         *  args:
         *      Str: a string need to be parsed
         *  return:
         *      a pointer of _element,formated
         *  exceptions:
         *      UnImpException: if use this unoverlayed virtual function( use
         *          this calss not an implemented class), this exception will
         *          throwen.
         *  warning: the return value _Element* is a pointer , you should
         *      carefully handle with and relaese its memory using delete
         *      function by yourselef. it is higly recommended that use
         *      std::auto_ptr to receive it.
         */
        virtual _Element* parser(char* str)
        throw (ParseException, UnImpException, Exception) {
            throw UnImpException();
            return 0;
        }

        /*  similar to java . newInstatnce is used to generated a new class
         *      interface. that is if a child class that is an implemetion
         *      of Parser. you invoke this function , then it(child class) will
         *      generate a new class of itselef(child class). and return a
         *      interface class(Parser) of that newest generated class(new
         *      child).
         *  args:
         *      None.
         *  return:
         *      pointer of Parser. you should use delete method to
         *          deconstructed class by yourselef. auto_ptr is recommended.
         *  excpetions:
         *      UnImpException: if use this unoverlayed virtual function( use
         *          this calss not an implemented class), this exception will
         *          throwen.
         */
        virtual Parser* newInstance()
        throw (UnImpException, Exception) {
            throw UnImpException();
            return 0;
        }
    }; //end of class Parser

    /*  this is a basic element to storage data . all data stored in
     *  hierarchically tree struct
     */
    class _Element {
    public:
        //typedef
        typedef std::list<_Element*> _ElementList;
        // define the _Element type

        typedef enum {
            type_node, // does not contain any information just a node contain children tree
            type_operator, // it is any possble operator ( ) + - * / \ ! ~ or else
            type_string, // it contains a string
            type_label, // it contains a label
            type_sinteger, //it contains a singed integer lik char short int long
            type_uinteger, //it contains an unsigned integer lik uchar ushort uint ulong
            type_real //it contains a real may be float or double
        } _Type;
        _Type type;

        //define the data
        std::string data_operator;
        std::string data_string;
        std::string data_label;
        signed long data_sinteger;
        unsigned long data_uinteger;
        double data_real;

        //define the sub tree
        _ElementList children;

        //=========== define class methods

        /*  this function add a element as a child
         *  args:
         *      elem:   the pointer of _Element need to added
         *  return:
         *      void
         */
        void addChild(_Element* elem) {
            if (elem) {
                children.push_back(elem);
            }
        }

        /*  this function make this element becom an operator element
         *  args:
         *      strOperator: the string of added operator.
         */
        void beOperator(const std::string& strOperator) {
            data_operator = strOperator;
            type = type_operator;
        }

        /*  this function make this element becom a node element
         *  args: None
         */
        void beNode() {
            type = type_node;
        }

        /*  this function make this element becom a string element
         *  args:
         *      str: the string of this element.
         */
        void beString(const std::string& str) {
            data_string = str;
            type = type_string;
        }

        /*  this function make this element becom a label element
         *  args:
         *      str: the label string of this element.
         */
        void beLabel(const std::string& str) {
            data_label = str;
            type = type_label;
        }

        /*  this function make this element becom a real element
         *  args:
         *      real: the value of real.
         */
        void beReal(const double real) {
            data_real = real;
            type = type_real;
        }

        /*  this function make this element becom a signed integer element
         *  args:
         *      sint: the value of integer.
         */
        void beSinteger(signed long sint) {
            data_sinteger = sint;
            type = type_sinteger;
        }

        /*  this function make this element becom an unsigned integer element
         *  args:
         *      uint: the value of integer.
         */
        void beUinteger(unsigned long uint) {
            data_uinteger = uint;
            type = type_uinteger;
        }

        /*construction empty
         */
        _Element() : type(type_node) {
            children.clear();
        }

        /* copy construction
         */
        _Element(const _Element& elem) {
            clone(elem);
        }

        /* operator overload = , function as a copy
         */
        _Element & operator =(const _Element& elem) {
            clone(elem);
            return *this;
        }

        /*deepcopy function
         */
        _Element& clone(const _Element& elem) {
            _ElementList::const_iterator _first, _end;
            type = elem.type;
            data_label = elem.data_label;
            data_operator = elem.data_operator;
            data_real = elem.data_real;
            data_sinteger = elem.data_sinteger;
            data_string = elem.data_string;
            data_uinteger = elem.data_uinteger;
            // begin children deep copy
            _first = elem.children.begin();
            _end = elem.children.end();
            while (_first != _end) {
                children.push_back(new _Element(*(*_first)));
                _first++;
            }
            return *this;
        }

        /*  this function delete the children and release the resource
         */
        void release() {
            _ElementList::iterator _first, _end;
            _first = children.begin();
            _end = children.end();
            while (_first != _end) {
                delete (*_first);
                _first++;
            }
            children.clear();
        }

        /* deconstruction function
         */
        ~_Element() {
            release();
        }

        /*  print element tree
         *  args:
         *      ostr : an ostream that to be print
         */
        void print(std::ostream& ostr) {
            _ElementList::iterator _first, _end;
            switch (type) {
                case type_node:
                    ostr << "    node    :" << this<< std::endl;
                    _first = children.begin();
                    _end = children.end();
                    while (_first != _end) {
                        (*_first)->print(ostr);
                        _first++;
                    }
                    ostr << " end node   :" << this<< std::endl;
                    break;
                case type_operator:
                    ostr << "operator    : " << data_operator << std::endl;
                    break;
                case type_real:
                    ostr << "real        : " << data_real << std::endl;
                    break;
                case type_sinteger:
                    ostr << "sinteger    : " << data_sinteger << std::endl;
                    break;
                case type_string:
                    ostr << "string      : " << data_string << std::endl;
                    break;
                case type_uinteger:
                    ostr << "uinteger    : " << data_uinteger << std::endl;
                    break;
                case type_label:
                    ostr << "label       :" << data_label <<std::endl;
                    break;
                default:
                    ostr << "Error" << std::endl;
                    break;
            }
        }

    }; //end of class _Element


} //end of namespace

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* _PARSER_BASIC_H */

