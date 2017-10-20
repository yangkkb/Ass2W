/*
 * File:   Parser_Ass2.h
 *
 *
 * Created on 2017��10��17��, ����2:03
 */

#ifndef _PARSER_ASS2_H
#define	_PARSER_ASS2_H

//================== include related head files
#include "Parser.h"
//std lib
#include "stdlib.h"
//Relative STL headfiles
#include "stack"

#define PDEBUG  false
#if PDEBUG ==true
#include "iostream"
#endif

//define namespace
namespace project {
    // a sub namespace
    namespace Parser_Ass2 {
        //================== pre decleartion;
        class Converter;
        class Filter;
        class Recognizer;
        //================== define a Template for return value

        /*  this calss use to return a data and number of parsed chars for
         *  Converter.
         *  template args:
         *      _Tp:    the type of storaged data. like double string integer
         *          and else.
         */
        template<typename _Tp>
        class _T_RetValue {
        public:
            /*  the data we storage
             */
            _Tp data;
            /*  how many char we parsed.
             */
            int charParsed;

            /*  construction function
             */
            _T_RetValue() : charParsed(0) {

            }

            /*  construction function
             *  args:
             *      refdata: data need to be storage
             *      cchar:  const char parsed
             */
            _T_RetValue(const _Tp& refdata, const int ccharParsed) {
                data = refdata;
                charParsed = ccharParsed;
            }

            /*  copy construction function
             */
            _T_RetValue(const _T_RetValue& sour) {
                clone(sour);
            }

            /*  overload of operator =
             */
            _T_RetValue & operator=(const _T_RetValue& sour) {
                clone(sour);
                return *this;
            }

            /*  perform a deep copy
             *  args:
             *      sour:   const ref. source.
             */
            void clone(const _T_RetValue& sour) {
                data = sour.data;
                charParsed = sour.charParsed;
            }

        };

        //================== define a classes for parser for Assignment2

        class ParserImp_Ass2 : public parser::Parser {
        protected:
            /*  Members     */
        public:

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
            virtual parser::_Element* parser(char* str)
            throw (parser::ParseException, parser::Exception);

            /*  Construction function
             */
            ParserImp_Ass2() {

            }

            /*  Deconstruction function
             */
            virtual ~ParserImp_Ass2() {

            }

            /*  this function return a Parser interface pointer of this parser
             *  args:
             *      None
             *  return:
             *      return a Parser pointer
             *  warning: user should delete returned class.
             *  see more on parser::Parser
             */
            virtual Parser* newInstance()
            throw (parser::UnImpException, parser::Exception) {
                return new ParserImp_Ass2;
            }

        }; //end of class ParserImp_Ass2


        //================= function class

        /*  this class used to convert data from string
         */
        class Converter {
        public:
            //define types
            typedef _T_RetValue<std::string> RetOperator;
            typedef _T_RetValue<double> RetReal;
            typedef _T_RetValue<signed long> RetSinteger;
            typedef _T_RetValue<unsigned long> RetUinteger;
            typedef _T_RetValue<std::string> RetLabel;

            /*  this function used to get unsigned integer from string
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      RetUinteger: is a template of class _T_RetVal
             *          the data is the unsigned long of sinteger
             *          the charParsed is the number of chars this converter
             *              used. if it is 0 means anything wrong happened
             *              in conversion. may be wrong format , wrong type.
             */
            static RetUinteger getUinteger(char* Str, int offset = 0) {
                char cTemp;
                unsigned long tempUint;
                RetUinteger retUint;
                int ccharParsed;

                tempUint = 0;
                ccharParsed = 0;
                retUint.data = 0;
                if (Str == 0) {
                    return retUint;
                }
                Str += offset;
                while ((cTemp = (*Str)) != 0) {
                    if ((cTemp >= '0') && (cTemp <= '9')) {
                        tempUint = tempUint * 10;
                        tempUint += cTemp - '0';
                    } else {
                        break;
                    }
                    Str++;
                    ccharParsed++;
                }
                retUint.data = tempUint;
                retUint.charParsed = ccharParsed;
                return retUint;
            } //end of function

            /*  this function used to get signed integer from string
             *  in most situation it is a negtive number
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      RetSinteger: is a template of class _T_RetVal
             *          the data is the signed long of sinteger
             *          the charParsed is the number of chars this converter
             *              used. if it is 0 means anything wrong happened
             *              in conversion. may be wrong format , wrong type.
             */
            static RetSinteger getSinteger(char* Str, int offset = 0) {
                char cTemp;
                bool bNegtive;
                int ccharParsed;
                RetSinteger retSint;
                RetUinteger getUint;

                ccharParsed = 0;
                bNegtive = false;
                retSint.data = 0;

                if (Str == 0) {
                    return retSint;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return retSint;
                }
                if (cTemp == '-') { // it is a negtive
                    bNegtive = true;
                    Str++;
                    ccharParsed++;
                }
                getUint = getUinteger(Str);
                if (getUint.charParsed == 0) {
                    return retSint;
                }
                retSint.data = getUint.data;
                if (bNegtive == true) {
                    retSint.data = -retSint.data;
                }
                retSint.charParsed = ccharParsed + getUint.charParsed;
                return retSint;
            }

            /*  this function used to get a double from string
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      RetReal: is a template of class _T_RetVal
             *          the data is the double of real
             *          the charParsed is the number of chars this converter
             *              used. if it is 0 means anything wrong happened
             *              in conversion. may be wrong format , wrong type.
             */
            static RetReal getReal(char* Str, int offset = 0) {
                char cTemp;
                bool bNegtive;
                bool dot;
                double RealInt; /*the integer part of real*/
                double RealDot; /*decimal part of real*/
                double RealDotWeight;
                RetReal retReal;
                int cParsed;

                cParsed = 0;
                RealInt = 0;
                RealDot = 0;
                RealDotWeight = 1.0;
                bNegtive = false;
                dot = false;

                if (Str == 0) {
                    return retReal;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return retReal;
                }
                if (cTemp == '-') { // it is a negtive
                    bNegtive = true;
                    Str++;
                    cParsed++;
                }
                while ((cTemp = (*Str)) != 0) {
                    if ((cTemp >= '0') && (cTemp <= '9')) {
                        if (dot == false) {
                            RealInt = RealInt * 10;
                            RealInt = RealInt + (cTemp - '0');
                        } else {
                            RealDotWeight = RealDotWeight / 10;
                            RealDot += (cTemp - '0') * RealDotWeight;
                        }
                    } else {
                        if (cTemp == '.') {
                            if (dot == false) {
                                dot = true;
                            } else {
                                return retReal;
                            }
                        } else {
                            break;
                        }
                    }
                    Str++;
                    cParsed++;
                }

                retReal.data = RealInt + RealDot;
                if (bNegtive) {
                    retReal.data = -retReal.data;
                }
                retReal.charParsed = cParsed;
                return retReal;
            }

            /*  this function used to get a label from string
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      RetLabel: is a template of class _T_RetVal
             *          the data is the string of label
             *          the charParsed is the number of chars this converter
             *              used. if it is 0 means anything wrong happened
             *              in conversion. may be wrong format , wrong type.
             */
            static RetLabel getLabel(char* Str, int offset = 0) {
                char cTemp;
                RetLabel retLabel;
                int ccharParsed;
                std::string tempLabel;

#if PDEBUG == true
                std::cout << "Begin convert label .offset: " << offset << std::endl;
#endif
                ccharParsed = 0;
                tempLabel = "";
                if (Str == 0) {
                    return retLabel;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return retLabel;
                }
                while ((cTemp = (*Str)) != 0) {
#if PDEBUG == true
                    std::cout << "templabel:" << tempLabel << " cTemp:" << cTemp << std::endl;
#endif
                    if ((cTemp == '_') || ((cTemp >= 'a') && (cTemp <= 'z'))
                            || ((cTemp >= 'A') && (cTemp <= 'Z'))) {
                        tempLabel += (cTemp);
                        Str++;
                        ccharParsed++;
                    } else {
                        if ((cTemp >= '0') && (cTemp <= '9')) {
                            // No numbers in Label. Error
                            return retLabel;
                        } else {
                            break;
                        }
                    }
                }
#if PDEBUG == true
                std::cout << "Label before freturn:" << tempLabel << ":" << ccharParsed << std::endl;
#endif
                retLabel.data = tempLabel;
                retLabel.charParsed = ccharParsed;
#if PDEBUG == true
                std::cout << "Returned Label" << std::endl;
#endif
                return retLabel;
            }

            /*  this function used to get an operator from string
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      RetOperator: is a template of class _T_RetVal
             *          the data is the string of operatore
             *          the charParsed is the number of chars this converter
             *              used. if it is 0 means anything wrong happened
             *              in conversion. may be wrong format , wrong type.
             */
            static RetOperator getOperator(char* Str, int offset = 0) {
                char cTemp;
                char cTemp2;
                const char * singleOperator = "(){}[]~%#$\"?@.,";
                RetOperator RetOperator;
                if (Str == 0) {
                    return RetOperator;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return RetOperator;
                }
                cTemp2 = *(Str + 1);
                switch (cTemp) {
                        //test double operator
                    case '-': // for example -> -=
                        switch (cTemp2) {
                            case '>':
                                RetOperator.data = "->";
                                RetOperator.charParsed = 2;
                                break;
                            case '=':
                                RetOperator.data = "-=";
                                RetOperator.charParsed = 2;
                                break;
                            default:
                                RetOperator.data = "-";
                                RetOperator.charParsed = 1;
                                break;
                        }
                        break;
                    case ':': // for example ::
                        if (cTemp2 == ':') {
                            RetOperator.data = "::";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = ":";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '>': // for example >> >=
                        switch (cTemp2) {
                            case '>':
                                RetOperator.data = ">>";
                                RetOperator.charParsed = 2;
                                break;
                            case '=':
                                RetOperator.data = ">=";
                                RetOperator.charParsed = 2;
                                break;
                            default:
                                RetOperator.data = ">";
                                RetOperator.charParsed = 1;
                                break;
                        }
                        break;
                    case '<': //for example << <=
                        switch (cTemp2) {
                            case '<':
                                RetOperator.data = "<<";
                                RetOperator.charParsed = 2;
                                break;
                            case '=':
                                RetOperator.data = "<=";
                                RetOperator.charParsed = 2;
                                break;
                            default:
                                RetOperator.data = "<";
                                RetOperator.charParsed = 1;
                                break;
                        }
                        break;
                    case '=': //for example ==
                        if (cTemp2 == '=') {
                            RetOperator.data = "==";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "=";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '!': //for example !=
                        if (cTemp2 == '=') {
                            RetOperator.data = "!=";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "!";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '+'://+=
                        if (cTemp2 == '=') {
                            RetOperator.data = "+=";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "+";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '*'://*=
                        if (cTemp2 == '=') {
                            RetOperator.data = "*=";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "*";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '/':// /=
                        if (cTemp2 == '=') {
                            RetOperator.data = "/=";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "/";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    case '&': //&& &=
                        switch (cTemp2) {
                            case '&':
                                RetOperator.data = "&&";
                                RetOperator.charParsed = 2;
                                break;
                            case '=':
                                RetOperator.data = "&=";
                                RetOperator.charParsed = 2;
                                break;
                            default:
                                RetOperator.data = "&";
                                RetOperator.charParsed = 1;
                                break;
                        }
                        break;
                    case '|': //|| |=
                        switch (cTemp2) {
                            case '|':
                                RetOperator.data = "||";
                                RetOperator.charParsed = 2;
                                break;
                            case '=':
                                RetOperator.data = "|=";
                                RetOperator.charParsed = 2;
                                break;
                            default:
                                RetOperator.data = "|";
                                RetOperator.charParsed = 1;
                                break;
                        }
                        break;
                    case '^'://^=
                        if (cTemp2 == '=') {
                            RetOperator.data = "^=";
                            RetOperator.charParsed = 2;
                        } else {
                            RetOperator.data = "^";
                            RetOperator.charParsed = 1;
                        }
                        break;
                    default:
                        while ((cTemp2 = (*singleOperator)) != 0) {
                            if (cTemp == cTemp2) {
                                RetOperator.data = cTemp;
                                RetOperator.charParsed = 1;
                            }
                            singleOperator++;
                        }
                        break;
                }
                return RetOperator;
            }


        }; //end of class Converter

        /*  this class consists of static function used to recognize string type.
         */
        class Recognizer {
        public:

            /*  this function used to test if the Str+offset is a Blank char
             *  args:
             *      Str: the string need to recognized
             *      offset: the offset for Recognizer
             *  return:
             *      bool: true means Str + offset is the type
             */
            static bool isBlank(char* Str, int offset = 0) {
                char cTemp;
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                if (cTemp == ' ' || cTemp == '\t' ||
                        cTemp == '\r' || cTemp == '\n') {
                    return true;
                }
                return false;
            }

            /*  this function used to test if the Str+offset is an operator char
             *  args: same as isBlank
             *  return: same as isBlank
             */
            static bool isOperator(char* Str, int offset = 0) {
                char cTemp;
                const char* Opertorchars = "(){}[]<>,.!+-=|#$%^&*'\"?:/";
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                while ((*Opertorchars) != 0) {
                    if (cTemp == (*Opertorchars)) {
                        return true;
                    }
                    Opertorchars++;
                }
                return false;
            }

            /*  this function used to test if the Str+offset is a singed integer
             *  most time means it is a negtive integer
             *  args: same as isBlank
             *  return: same as isBlank
             */
            static bool isSinteger(char* Str, int offset = 0) {
                char cTemp;
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                if (cTemp != '-') {
                    return false;
                }
                Str++;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                if (!((cTemp >= '0') && (cTemp <= '9'))) {
                    return false;
                }
                Str++;
                while ((cTemp = *Str) != 0) {
                    if (cTemp == '.') {
                        return false;
                    }
                    if (((cTemp >= '0') && (cTemp <= '9'))) {

                    } else {
                        if (((cTemp >= 'a') && (cTemp <= 'z')) ||
                                ((cTemp >= 'A') && (cTemp <= 'Z'))) {
                            return false;
                        } else {
                            return true;
                        }
                    }
                    Str++;
                }
                return true;
            }

            /*  this function used to test if the Str+offset is an unsinged integer
             *  most time means it is a positive integer
             *  args: same as isBlank
             *  return: same as isBlank
             */
            static bool isUinteger(char* Str, int offset = 0) {
                char cTemp;
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                if (!((cTemp >= '0') && (cTemp <= '9'))) {
                    return false;
                }
                Str++;
                while ((cTemp = *Str) != 0) {
                    // No dot
                    if (cTemp == '.') {
                        return false;
                    }
                    if (((cTemp >= '0') && (cTemp <= '9'))) {

                    } else {
                        if (((cTemp >= 'a') && (cTemp <= 'z')) ||
                                ((cTemp >= 'A') && (cTemp <= 'Z'))) {
                            return false;
                        } else {
                            return true;
                        }
                    }
                    Str++;
                }
                return true;
            }

            /*  this function used to test if the Str+offset is an double
             *  args: same as isBlank
             *  return: same as isBlank
             */
            static bool isReal(char* Str, int offset = 0) {
                char cTemp;
                bool dot; //boolean wether dot has been here once
                dot = false;
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                // first char can be number or - if it is - skip
                if (cTemp == '-') {
                    Str++;
                    cTemp = *Str;
                    if (cTemp == 0) {
                        return false;
                    }
                }
                // second letter can be .
                if (cTemp == '.') {
                    dot = true;
                    Str++;
                    cTemp = *Str;
                    if (cTemp == 0) {
                        return false;
                    }
                }
                //There must atleast one number
                if (!((cTemp >= '0') && (cTemp <= '9'))) {
                    return false;
                }
                Str++;
                while ((cTemp = *Str) != 0) {
                    if (((cTemp >= '0') && (cTemp <= '9'))) {

                    } else {
                        if (((cTemp >= 'a') && (cTemp <= 'z')) ||
                                ((cTemp >= 'A') && (cTemp <= 'Z'))) {
                            return false;
                        } else {
                            if (cTemp == '.') {
                                if (dot == true) {
                                    return false;
                                } else {
                                    dot = true;
                                }
                            } else {
                                return true;
                            }

                        }
                    }
                    Str++;
                }
                return true;
            }

            /*  this function used to test if the Str+offset is an label
             *  args: same as isBlank
             *  return: same as isBlank
             */
            static bool isLabel(char* Str, int offset = 0) {
                char cTemp;
                if (Str == 0) {
                    return false;
                }
                Str += offset;
                cTemp = *Str;
                if (cTemp == 0) {
                    return false;
                }
                //Label start with _ or a-z A-Z
                if (cTemp == '_') {
                    return true;
                }
                if ((cTemp >= 'a') && (cTemp <= 'z')) {
                    return true;
                }
                if ((cTemp >= 'A') && (cTemp <= 'Z')) {
                    return true;
                }
                return false;
            }

        }; // End of class Recognizer

        /*  this class consists of static functions used to filter blank ,
         *  or else
         */
        class Filter {
        public:

            /*  this function filter and skip all blank chars like space table
             *  return nextline \r\t\n and return sikpped counts
             *  args:
             *      Str: the string applied to this filter
             *      offset: the offset where begin to filter
             *  return:
             *      int : the number of chars skipped. if 0 , no char skiped.
             *          for example: Str+offset+return is the first char that 
             *          not blank begin from str + offset
             */
            static int blank(char* Str, int offset = 0) {
                int skipCount = 0;
                char Temp;
                if (Str == 0) {
                    return 0;
                }
                Str += offset;
                while ((Temp = *Str) != 0) {
                    if ((Temp != ' ') && (Temp != '\t') &&
                            (Temp != '\r') && (Temp != '\n')) {
                        break;
                    }
                    Str++;
                    skipCount++;
                }
                return skipCount;
            }
        };

        //================= register class

        /*  a class use it's construction function to perform a static function
         */
        class Parser_Ass2_StaticIni {
        public:

            /*  construction function used to register Ass2
             */
            Parser_Ass2_StaticIni() {
                parser::_Factory& factory = parser::factory();
                factory.addClass("Ass2", new ParserImp_Ass2());
            }

        }; //end of class Parser_Ass2_StaticIni

    }// end of namespace

}//end of namespace



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* _PARSER_ASS2_H */

