/* this file is for Parser Ass2 register when program loaded
 *
 */

//==================Include headfiles

//Ansic C
#include <string.h>

#include "autoptr.h"
//relative
#include "Parser_Ass2.h"

#define PDEBUG  false
#if PDEBUG == true
#include "iostream"
#endif

//================== static variables
static
project::Parser_Ass2::Parser_Ass2_StaticIni
_parser_Ass2_Static_;

namespace project {
    namespace Parser_Ass2 {

        /*  this function parser the string or chars of str and return in
         *  _Element format. This parser is used for graph parse , for
         *  assignment 2.
         *  args:
         *      Str: a string need to be parsed
         *  return:
         *      a pointer of _element,formated
         *  exceptions:
         *  warning: the return value _Element* is a pointer , you should
         *      carefully handle with and relaese its memory using delete
         *      function by yourselef. it is higly recommended that use
         *      std::auto_ptr to receive it.
         */
        parser::_Element* ParserImp_Ass2::parser(char* str)
        throw (parser::ParseException, parser::Exception) {
            //tyedef
            typedef std::stack<std::string> OpeStack;
            typedef std::stack<parser::_Element*> EleStack;
            /*  ptrRetEle is a smart pointer , used to store _Element pointer
             *  when an exception is thrown , it will atomictally delete it
             */
            parser::auto_ptr<parser::_Element> ptrRetEle(new parser::_Element);
            /*  this stack is to storage operator if it is not empty when
             *  exit function . it will have an exception. if the right
             *  operator like ] will causes a pop action . and the pop
             *  operator must match [ . or else there will exception
             */
            OpeStack stackOperator;
            /*  this stack storages the last operatoed Element Node pointer
             */
            EleStack stackElement;
            /*  pointer of currently operated element
             */
            parser::_Element* ptrCurrentEle;
            /*  opinter of last create4 Element
             */
            parser::_Element* ptrNewEle;
            /*  poistion of current operated in Str
             */
            int strPos;
            int strLength;
            /*  following are result got from converter
             */
            Converter::RetLabel parsedLabel;
            Converter::RetOperator parsedOperator;
            Converter::RetReal parsedReal;
            Converter::RetSinteger parsedSinteger;
            Converter::RetUinteger parsedUinteger;
#if PDEBUG == true
            std::cout << "Begin Parsing..." << std::endl;
#endif

            //Ini variables
            ptrCurrentEle = ptrRetEle.get();
            ptrCurrentEle->beNode();
#if PDEBUG == true
            std::cout << "Parsing Ini finished" << std::endl;
#endif
            strPos = 0;
            strLength = strlen(str);
#if PDEBUG == true
            std::cout << "str length is:" << strLength << std::endl;
#endif
            while (strPos < strLength) {
                if (Recognizer::isBlank(str, strPos)) {
                    strPos += Filter::blank(str, strPos);
                }
#if PDEBUG == true
                std::cout << "str Pos is:" << strPos << std::endl;
#endif
                if (strPos >= strLength) {
                    break;
                }
                // begin to recognize
                // first identify Label
                if (Recognizer::isLabel(str, strPos)) {
#if PDEBUG == true
                    std::cout << "it is a label" << std::endl;
#endif
                    parsedLabel = Converter::getLabel(str, strPos);
#if PDEBUG == true
                    std::cout << "the convert result:" << parsedLabel.charParsed << " : " << parsedLabel.data << std::endl;
#endif
                    // if label is vaild
                    if (parsedLabel.charParsed != 0) {
                        strPos += parsedLabel.charParsed;
                        ptrNewEle = new parser::_Element();
                        ptrNewEle ->beLabel(parsedLabel.data);
                        ptrCurrentEle->addChild(ptrNewEle);
#if PDEBUG == true
                        std::cout << "We Got A Label: " <<
                                ptrNewEle->data_label << std::endl;
#endif
                        continue;
                    }
                }
                // second check sinteger
                if (Recognizer::isSinteger(str, strPos)) {
                    parsedSinteger = Converter::getSinteger(str, strPos);
                    if (parsedSinteger.charParsed != 0) {
                        strPos += parsedSinteger.charParsed;
                        ptrNewEle = new parser::_Element();
                        ptrNewEle->beSinteger(parsedSinteger.data);
                        ptrCurrentEle->addChild(ptrNewEle);
#if PDEBUG == true
                        std::cout << "We Got A Sinteger: " <<
                                ptrNewEle->data_sinteger << std::endl;
#endif
                        continue;
                    }
                }
                // third check uinteger
                if (Recognizer::isUinteger(str, strPos)) {
                    parsedUinteger = Converter::getUinteger(str, strPos);
                    if (parsedUinteger.charParsed != 0) {
                        strPos += parsedUinteger.charParsed;
                        ptrNewEle = new parser::_Element();
                        ptrNewEle->beUinteger(parsedUinteger.data);
                        ptrCurrentEle->addChild(ptrNewEle);
#if PDEBUG == true
                        std::cout << "We Got A Uinteger: " <<
                                ptrNewEle->data_uinteger << std::endl;
#endif
                        continue;
                    }
                }
                // 4th check double
                if (Recognizer::isReal(str, strPos)) {
                    parsedReal = Converter::getReal(str, strPos);
                    // if Real is vaild
                    if (parsedReal.charParsed != 0) {
                        strPos += parsedReal.charParsed;
                        ptrNewEle = new parser::_Element();
                        ptrNewEle->beReal(parsedReal.data);
                        ptrCurrentEle->addChild(ptrNewEle);
#if PDEBUG == true
                        std::cout << "We Got A Real: " <<
                                ptrNewEle->data_real << std::endl;
#endif
                        continue;
                    }
                }
                //last check operator
                if (Recognizer::isOperator(str, strPos)) {
                    parsedOperator = Converter::getOperator(str, strPos);
                    if (parsedOperator.charParsed != 0) {
                        strPos += parsedOperator.charParsed;
                        ptrNewEle = new parser::_Element();
                        ptrNewEle->beOperator(parsedOperator.data);
#if PDEBUG == true
                        std::cout << "We Got A Operator: " <<
                                ptrNewEle->data_operator << std::endl;
#endif
                        //check if it is a push operator
                        if (parsedOperator.data == "(" ||
                                parsedOperator.data == "{" ||
                                parsedOperator.data == "[" ||
                                parsedOperator.data == "<") {
                            stackOperator.push(parsedOperator.data);
                            ptrCurrentEle->addChild(ptrNewEle);
                            ptrNewEle = new parser::_Element();
                            ptrNewEle->beNode();
                            ptrCurrentEle->addChild(ptrNewEle);
                            stackElement.push(ptrCurrentEle);
                            ptrCurrentEle = ptrNewEle;
                        } else {
                            //check pop operator
                            if (parsedOperator.data == ")" ||
                                    parsedOperator.data == "}" ||
                                    parsedOperator.data == "]" ||
                                    parsedOperator.data == ">") {
                                // check paired
                                if (stackOperator.empty() == true) {
                                    throw parser::ParseException(strPos,
                                            "No match for this operator");
                                }
                                if (stackOperator.top() == "(" &&
                                        parsedOperator.data != ")") {
                                    throw parser::ParseException(strPos,
                                            "expected a )");
                                }
                                if (stackOperator.top() == "{" &&
                                        parsedOperator.data != "}") {
                                    throw parser::ParseException(strPos,
                                            "expected a }");
                                }
                                if (stackOperator.top() == "[" &&
                                        parsedOperator.data != "]") {
                                    throw parser::ParseException(strPos,
                                            "expected a ]");
                                }
                                if (stackOperator.top() == "<" &&
                                        parsedOperator.data != ">") {
                                    throw parser::ParseException(strPos,
                                            "expected a >");
                                }
                                // all pass then do pop
                                stackOperator.pop();
                                ptrCurrentEle = stackElement.top();
                                stackElement.pop();
                                ptrCurrentEle->addChild(ptrNewEle);
                            } else {
                                // other operator
                                ptrCurrentEle->addChild(ptrNewEle);
                            }
                        }
                        continue;
                    }
                }
                //else throw exception
                throw parser::ParseException(strPos, "Unknown sign");
            }
            if (stackOperator.empty() == false) {
                throw parser::ParseException(strPos, "No match operator");
            }
            return ptrRetEle.release();
        }
    } //end of namespace Parser_Ass2
}//end of namspace project



