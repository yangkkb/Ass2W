/*
 * File:   Parser.h
 * Author: yangkkb
 *
 * Created on 2017��10��11��, ����7:46
 */

#ifndef _PARSER_H
#define	_PARSER_H

//==================Include realted headfiles
#include "Parser_Basic.h"
#include "Parser_T.h"
//stl std
#include "map"
#include "list"

//declare a namespace
namespace parser {

    //============= exceptions

    /*  this class is thrown when the class name is not exist when require a class
     *  from factory.
     */
    class InexistException : public Exception {
    public:
        std::string errorName;

        /*  construction function
         *  args:
         *      name: the class name
         */
        InexistException(std::string name) {
            errorName = name;
        }

        /* deconstruction function , do nothing*/
        ~InexistException() {

        }

        /*  print a message on ostr
         *  args:
         *      ostr: an out stream where ERROR message put out.
         */
        virtual void printMSG(std::ostream& ostr) {
            ostr << "Inexistent Parser Class : " << errorName;
        };
    };

    /*  this exception is thrown when the searched parser is not in facotry
     */
    class ExistedException : public Exception {
    public:
        std::string errorName;

        /*  construction function
         *  args:
         *      name: the class name
         */
        ExistedException(std::string name) {
            errorName = name;
        }

        /* deconstruction function , do nothing*/
        ~ExistedException() {

        }

        /*  print a message on ostr
         *  args:
         *      ostr: an out stream where ERROR message put out.
         */
        virtual void printMSG(std::ostream& ostr) {
            ostr << "Parser Class : " << errorName << " already existed";
        };
    };
    //============= end of exceptions

    /*  this is a factory class used to generate and management all interface
     *  of parser
     */
    class _Factory {
    private:
        // type define
        typedef std::map<std::string, parser::Parser*> PMap;
        typedef std::list<parser::Parser*> PList;
    private:
        /*pointer to int keep the refrenced number*/
        int* ptrrefCount;
        /*this map is story key value for parser*/
        PMap* ptrparserMap;
        /*this list is used to stor calss need to delete when deconstruction*/
        PList* ptrparserList;
    private:

        void newVars() {
            ptrrefCount = new int;
            (*ptrrefCount) = 1;
            ptrparserMap = new PMap;
            ptrparserList = new PList;
        }
    public:

        /*  add a class interface to factory, with a key name. name should be
         *  unique.
         *  args:
         *      name: string of key name. unique
         *      ptrparImp: a pointer of class, an implement of interface Parser
         *  return:
         *      none
         *  exceptions:
         *      ExistedException: when the name is already added before, this
         *          exception will thrown.
         */
        void addClass(std::string name, const Parser* ptrparImp)
        throw (ExistedException) {
            PMap::iterator _find;
            Parser* _parImp;
            _parImp = const_cast<Parser*> (ptrparImp);

            _find = ptrparserMap->find(name);
            if (_find != ptrparserMap->end()) {
                throw ExistedException(name);
            }
            ptrparserList->push_back(_parImp);
            ptrparserMap->insert(PMap::value_type(name, _parImp));
        }

        /*  overload
         *  args:
         *      name:same as above
         *      parImp:a const quote
         */
        void addClass(std::string name, const Parser& parImp)
        throw (ExistedException) {
            addClass(name, &parImp);
        }

        /*  this function get an instance from parser class implemet. it provke
         *      the method newInstance of implemet. Either an new instance ,or
         *      the instance itselef will returned , that is decided by the
         *      implemnt itselef.
         *  args:
         *      name: a key name of the instance you are looking for
         *  return:
         *      Parser pointer of the new instance.
         *  exceptions:
         *      InexistException: the exception will thrown when factory cannot
         *          find class correspond with name.
         *      UnImpException: see parser::Parser
         *      Exception: see parser::Parser
         *  warning:
         *      the return pointer will not release or delete it selef, you
         *          should carefulay deal with it yourself. You can use auto_ptr
         */
        Parser* forInstance(std::string name)
        throw (InexistException, UnImpException, Exception) {
            PMap::iterator _find;
            if (ptrrefCount == 0) {
                throw InexistException(name);
            }
            _find = ptrparserMap->find(name);
            if (_find == ptrparserMap->end()) {
                throw InexistException(name);
            }
            return _find->second->newInstance();
        }

        /* a refrenced copy function
         */
        void clone(parser::_Factory& fac) {
            release();
            ptrrefCount = fac.ptrrefCount;
            ptrparserList = fac.ptrparserList;
            ptrparserMap = fac.ptrparserMap;
            if (ptrrefCount != 0) {
                (*ptrrefCount)++;
            }
        }

        /*  construction function
         */
        _Factory() {
            newVars();
        }

        /* a copy construction
         */
        _Factory(parser::_Factory & fac) : ptrrefCount(0), ptrparserList(0),
        ptrparserMap(0) {
            clone(fac);
        }

        /*  operator = overload
         */
        _Factory & operator=(parser::_Factory & fac) {
            clone(fac);
            return *this;
        }

        /*  release all resource in class
         */
        void release() {
            PList::iterator _first, _end;
            if (ptrrefCount == 0) {
                return;
            }
            /*refrenced count minus 1*/
            (*ptrrefCount)--;
            if ((*ptrrefCount) != 0) {
                // if there still refrence not release
                ptrrefCount = 0;
                ptrparserList = 0;
                ptrparserMap = 0;
                return;
            }
            for (_first = ptrparserList->begin(), _end = ptrparserList->end();
                    _first != _end; _first++) {
                try {
                    delete *_first;
                } catch (...) {

                }
            }
            ptrparserList->clear();
            ptrparserMap->clear();
            delete ptrrefCount;
            delete ptrparserList;
            delete ptrparserMap;
            ptrrefCount = 0;
            ptrparserList = 0;
            ptrparserMap = 0;
        }

        /*  deconstruction function
         *      delete all class stored
         */
        ~_Factory() {
            release();
        }

    }; // end of _Factory


    /*  define a global factory. for c++ static initialise we use a function
     *  and return facotry.
     *  return:
     *      a static factory
     */
    parser::_Factory& factory();
}//end of namespace


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* _PARSER_H */

