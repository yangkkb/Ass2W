/* 
 * File:   Graph_T.h
 * template file for Graph Storage and its storage
 *
 */

#ifndef _GRAPH_T_H
#define	_GRAPH_T_H

//==================Include related head files
#include "list"
#include "map"
#include "iostream"

//==================Define the template structure
// define namespace
namespace graph {

    //==================pre declaration
    template<typename _Point_ID, typename _Edge_Value, typename _PTag = char,
            typename _Point_Value = _Edge_Value> struct _T_Edge;

    //==================begin template for _T_Edge

    /* this template is for a graph point contents ID Value Tag and else
     * args:
     * same as _T_Graph
     * warnings:
     * same as _T_Graph
     */
    template<typename _Point_ID, typename _Edge_Value, typename _PTag = char,
            typename _Point_Value = _Edge_Value>
            class _T_Point {
        //Member defines
    public:
        //type define
        typedef _T_Edge<_Point_ID, _Edge_Value, _PTag, _Point_Value> Edge;
        /* id is used for identify point must buunique*/
        _Point_ID id;
        /* value is value on this point*/
        _Point_Value value;
        /* value accumulated , use as a temporary data*/
        _Edge_Value valueSum;
        /*tag store something else */
        _PTag tag;
        /*used for storage path  point id by point id*/
        std::list<_Point_ID> path;
        /*used for storage edge pointers*/
        std::list<Edge*> edges_begin; /*this point is the begin point in edges*/
        std::list<Edge*> edges_end; /*this point is the end point in edges*/
    public:

        /* add a edge to point storages
         * if edge.point_begin == this point
         *      edge is add in edges_being
         * if edge.point_end == this point
         *      edge is add in edges_end
         * else
         *     return false
         */
        bool addEdge(Edge& edge)
        throw () {
            return addEdge(&edge);
        }

        /* same as Previous one
         * edgeptr is a pointer
         */
        bool addEdge(Edge* edgeptr)
        throw () {
            bool rSucess;
            typename std::list<Edge*>::iterator _first, _end;

            rSucess = false;
            if (edgeptr->point_begin == this) {
                // check if edge is already in
                for (_first = edges_begin.begin(), _end = edges_begin.end();
                        _first != _end; _first++) {
                    if ((*_first) == edgeptr) {
                        break;
                    }
                }
                if (_first == _end) {
                    edges_begin.push_back(edgeptr);
                    rSucess = true;
                }
            }
            if (edgeptr->point_end == this) {
                // check if edge is already in
                for (_first = edges_end.begin(), _end = edges_end.end();
                        _first != _end; _first++) {
                    if ((*_first) == edgeptr) {
                        break;
                    }
                }
                if (_first == _end) {
                    edges_end.push_back(edgeptr);
                    rSucess = true;
                }
            }
            return rSucess;
        }

        /*  search and Edge in list. Edge is (thisID,endID)
         *  if exist then return it's pointer else return 0
         *  args:
         *      endID: the end point id.
         *  return:
         *      the Edge pointer. if edge not exist it is 0;
         *  exceptions:
         *      none.
         */
        Edge* searchEdge(_Point_ID endID)
        throw () {
            typename std::list<Edge*>::iterator _first, _end;
            _first = edges_begin.begin();
            _end = edges_begin.end();
            while (_first != _end) {
                if ((*_first)->point_end->id == endID) {
                    break;
                }
                _first++;
            }
            if (_first != _end) {
                return *_first;
            } else {
                return 0;
            }
        }

        /* performe a deep copy include data and path
         */
        _T_Point& clone(const _T_Point& Point) {
            id = Point.id;
            value = Point.value;
            tag = Point.tag;
            path = Point.path; //auto use deep copy
            edges_begin = Point.edges_begin;
            edges_end = Point.edges_end;
            return *this;
        }

        /*construction function
         */
        _T_Point() {
            path.clear();
            edges_begin.clear();
            edges_end.clear();
        }

        /*construction function
         * args:
         * ID: unique id for this point
         */
        _T_Point(_Point_ID ID) {
            id = ID;
            path.clear();
            edges_begin.clear();
            edges_end.clear();
        }

        /*construction function
         * args:
         * ID: unique id for this point
         * Value: value on this point
         * Tag:somethin else you want to store
         */
        _T_Point(_Point_ID ID, _Point_Value Value, _PTag Tag) {
            id = ID;
            value = Value;
            tag = Tag;
            path.clear();
            edges_begin.clear();
            edges_end.clear();
        }

        /* copy construction
         */
        _T_Point(_T_Point& Point) {
            clone(Point);
        }

        /* deconstruction function
         */
        ~_T_Point() {
            path.clear();
            edges_begin.clear();
            edges_end.clear();
        }

        /* = opeartion copy from a Point
         * args:
         * Point right operator where copied data.
         */
        _T_Point & operator =(const _T_Point& Point) {
            clone(Point);
            return *this;
        }

        /*  functions that print data path to an ostream
         *  template args:
         *      _Tp: the seperator string type between every point.
         *          it can be string, char , char* or any thing else that
         *          support ostream<< _Tp operator
         *  args:
         *      ostr : an output stream , can use such as cout or file or any out stream
         *      spe: the Seperator string between every points;
         */
        template<typename _Tp>
        void printPath(std::ostream& ostr, _Tp spe) {
            typename std::list<_Point_ID>::iterator _first, _end;
            _first = path.begin();
            _end = path.end();
            while (_first != _end) {
                ostr << *_first;
                *_first++;
                if (_first != _end) {
                    ostr << spe;
                }
            }
        }
    };
    //==================End of _T_Point



    //==================template for _T_Edge

    /* template for edge struct , it is a directed edge
     * args:
     * same as _T_Graph
     * warnings:
     * same as _T_Graph
     */
    template<typename _Point_ID, typename _Edge_Value, typename _PTag,
    typename _Point_Value>
    struct _T_Edge {
        //members
    public:
        typedef _T_Point<_Point_ID, _Point_Value, _PTag, _Point_Value> Point;
        Point* point_begin; /*It is a pointer store the begin of edge*/
        Point* point_end; /*It is a pointer store the end of edge*/
        _Edge_Value value; /* store the value of this edge */

        /* construction function
         * args:
         * begin: it is a pointer referenced to point which is the begin of edge
         * end: it is a pointer referenced to point which is the end of edge
         * edgval: the value on this edge
         */
        _T_Edge(Point* begin, Point* end, _Edge_Value edgval) {
            point_begin = begin;
            point_end = end;
            value = edgval;
        }

        /* construction function
         */
        _T_Edge() : point_begin(0), point_end(0) {
        }

        /* a copy construction function
         *
         */
        _T_Edge(const _T_Edge & edge) {
            clone(edge);
        }

        /* a copy function , copy data from edge
         * args:
         * edge: the source edge need to be copyed;
         * return:
         * this struct
         */
        _T_Edge & clone(const _T_Edge & edge) {
            point_begin = edge.point_begin;
            point_end = edge.point_end;
            value = edge.value;
            return * this;
        }
    };
    //==============end of _T_Edge



    //============== Error Exception

    /* this is a basic exception class
     */
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

    /* this template is for virtual class to deal the exception when something
     * wrong with point id
     * args:
     * same as _T_Graph
     * warnings:
     * same as _T_Graph
     */
    template<typename _Point_ID>
    class _T_ID_Exception : public graph::Exception {
    public:
        _Point_ID pointID;
        std::string errorMSG;

        /* construction funcion
         * args:
         * ErrID: Error ID
         * ErrorMSG: an error message
         */
        _T_ID_Exception(_Point_ID ErrID, std::string ErrorMSG) {
            pointID = ErrID;
            errorMSG = ErrorMSG;
        }

        virtual ~_T_ID_Exception() {
        }

        virtual void printMSG(std::ostream& ostr) {
            ostr << "PointID: ";
            ostr << pointID;
            ostr << " encounters an ERROR: " << errorMSG;
        }
    };

    /*  this template is for virtual class to deal the exception when something
     *  wrong with points
     *  args:
     *      same as _T_Graph
     *  warnings:
     *      same as _T_Graph
     */
    template<typename _Point_ID, typename _Edge_Value, typename _PTag,
    typename _Point_Value>
    class _T_Point_Exception : public graph::Exception {
    public:
        typedef _T_Point<_Point_ID, _Edge_Value, _PTag, _Point_Value> Point;
        Point* point;
        std::string errorMSG;

        /* construction funcion
         * args:
         * ErrPoint: pointer referenced to Point cased Error
         * ErrorMSG: an error message
         */
        _T_Point_Exception(Point* ErrPoint, std::string ErrorMSG) {
            point = ErrPoint;
            errorMSG = ErrorMSG;
        }

        virtual void printMSG(std::ostream& ostr) {
            ostr << "Point: ";
            if (point != 0) {
                ostr << point->id;
            } else {
                ostr << "Unknown";
            }
            ostr << " encounters an ERROR: " << errorMSG;
        }
    };

    //============== End of Error Exception

    /*
     *  this template is for a graph storage
     *  args:
     *      _Point_ID: the data type that identify a unique point.like ,integer
     *                ,string
     *      _Edge_Value： the data type that contents the value of edge ,
     *                  and must have + (add) operation. like integer or string
     *                  or float or else.
     *      _PTag: the addtional data storage in point class. Not use in common
     *      _Point_Value: the data type that contents the value of point, and
     *                  must have + (add) operation. like integer or string or
     *                  float or else.  by default _Edge_Value = _Edge_Value
     *      Map: the container for points , the default is std::map<_Point_ID,Point*>
     *           default is a btree. you can use any other container you want .
     *           may be you need to use a hash map or else. but any container
     *           must have find and clear and insert methods.
     *
     *  warning: operate + between _Point_Value and _Edge_Value must be support.
     *  warning: _Point_Value must have operator << for std::ostream
     *  warning: _Point_ID must have operator < , > ,<=,>= , becase we use btree to
     *          sotr it, and we validate _Point_ID .
     */
    template <typename _Point_ID, typename _Edge_Value, typename _PTag = char,
            typename _Point_Value = _Edge_Value,
            typename Map = std::map<
            _Point_ID,
            graph::_T_Point<_Point_ID, _Edge_Value, _PTag, _Point_Value >*
            > >
            class _T_Graph {
    public:
        //declaration types
        typedef _T_Point<_Point_ID, _Edge_Value, _PTag, _Point_Value> Point;
        typedef _T_Edge<_Point_ID, _Edge_Value, _PTag, _Point_Value> Edge;
        //typedef std::map<_Point_ID, Point*> PointMap;
        typedef Map PointMap;
        typedef std::list<Edge*> EdgeList;
        typedef std::list<Point*> PointList;
        //Exceptions
        typedef _T_Point_Exception<_Point_ID, _Edge_Value, _PTag, _Point_Value>
        Point_Exception;
        typedef _T_ID_Exception<_Point_ID> ID_Exception;

        _Point_ID Max_ID; /*Max ID , any one should not bigger than this*/
        _Point_ID Min_ID; /*min ID, any on should not less than this*/

        //containers
        //used to contain datas and delete them when Graph released
        EdgeList edges_list;
        PointList points_list;

        //BtreeMap or HashMap to lookup point
        PointMap points_map;

    public:

        /*  this function add a directed edge with edge value in graph.
         *  args:
         *      beginID: the begin point id of this edge
         *      endID:the end point id of this edge
         *      value: the value on this edge
         *  return:
         *      void
         *  exceptions:
         *      ID_Exception: somethin wrong with id. in following cases:
         *          1:somethin wrong with beginID or endID. out of boundary;
         *          2:bacause of inner error beginID or endID cannot be correctly
         *              find matched points in PointsMap or related point cannot
         *              be correctly created.
         */
        void addEdge(_Point_ID beginID, _Point_ID endID, _Edge_Value value)
        throw (ID_Exception) {
            typename PointMap::iterator _ite_beginID, _ite_endID;
            Edge* newEdge;
            Point* tempPoint;
            if (beginID > Max_ID || beginID < Min_ID) {
                throw ID_Exception(beginID, "ID outof boundary.");
            }
            if (endID > Max_ID || endID < Min_ID) {
                throw ID_Exception(endID, "ID outof boundary");
            }
            // Create new Edge first
            newEdge = new Edge();
            newEdge->value = value;
            edges_list.push_back(newEdge);
            // check if begin id and end if whether exsit
            _ite_beginID = points_map.find(beginID);
            /*  can not do this if beginID=end ID then and not in map then
             *  point will create tiwce
             */
            // _ite_endID = points_map.find(endID);
            if (_ite_beginID != points_map.end()) { //point class exist
                tempPoint = _ite_beginID->second;
            } else { //point class not exist then creat it
                tempPoint = new Point(beginID);
                points_list.push_back(tempPoint);
                points_map.insert(typename PointMap::value_type(beginID, tempPoint));
            }
            newEdge->point_begin = tempPoint;
            if (tempPoint->addEdge(newEdge) == false) {
                throw ID_Exception(beginID, "ID can not compatible with data in map");
            }
            // for end id
            _ite_endID = points_map.find(endID);
            if (_ite_endID != points_map.end()) { //point class exist
                tempPoint = _ite_endID->second;
            } else { //point class not exist then creat it
                tempPoint = new Point(endID);
                points_list.push_back(tempPoint);
                points_map.insert(typename PointMap::value_type(endID, tempPoint));
            }
            newEdge->point_end = tempPoint;
            if (tempPoint->addEdge(newEdge) == false) {
                throw ID_Exception(endID, "ID can not compatible with data in map");
            }
        }

        /*  overload of operator ()
         *  this function use to ge reference value of an edge selected by
         *  (beginID,endID). if the edge do not exist then create it. if edge
         *  exist return the reference value.
         *  args:
         *      beginID: the begin point id of this edge
         *      endID:the end point id of this edge
         *  return:
         *      reference value
         *  exceptions:
         *      ID_Exception: somethin wrong with id. in following cases:
         *          1:somethin wrong with beginID or endID. out of boundary;
         *          2:bacause of inner error beginID or endID cannot be correctly
         *              find matched points in PointsMap or related point cannot
         *              be correctly created.
         */
        _Edge_Value & operator() (_Point_ID beginID, _Point_ID endID)
        throw (ID_Exception) {
            typename PointMap::iterator _ite_beginID, _ite_endID;
            Edge* ptrEdge;
            Point* ptr_beginPoint, * ptr_endPoint;
            // ID boundary check
            if (beginID > Max_ID || beginID < Min_ID) {
                throw ID_Exception(beginID, "ID outof boundary.");
            }
            if (endID > Max_ID || endID < Min_ID) {
                throw ID_Exception(endID, "ID outof boundary");
            }
            // check if begin id and end if whether exsit
            _ite_beginID = points_map.find(beginID);
            //_ite_endID = points_map.find(endID);
            //begin ID
            if (_ite_beginID != points_map.end()) { //point class exist
                ptr_beginPoint = _ite_beginID->second;
            } else { //point class not exist then creat it
                ptr_beginPoint = new Point(beginID);
                points_list.push_back(ptr_beginPoint);
                points_map.insert(typename PointMap::value_type(beginID, ptr_beginPoint));
            }
            // for end id
            _ite_endID = points_map.find(endID);
            if (_ite_endID != points_map.end()) { //point class exist
                ptr_endPoint = _ite_endID->second;
            } else { //point class not exist then creat it
                ptr_endPoint = new Point(endID);
                points_list.push_back(ptr_endPoint);
                points_map.insert(typename PointMap::value_type(endID, ptr_endPoint));
            }
            //search Edge
            ptrEdge = ptr_beginPoint->searchEdge(endID);
            if (ptrEdge == 0) { //Edge do not exist then create it
                ptrEdge = new Edge;
                ptrEdge->point_begin = ptr_beginPoint;
                ptrEdge->point_end = ptr_endPoint;
                edges_list.push_back(ptrEdge);
                ptr_beginPoint->addEdge(ptrEdge);
                ptr_endPoint->addEdge(ptrEdge);
            }
            return ptrEdge->value;
        }

        /*  this function used to set value on point pID
         *  args:
         *      pID: the id of point need to set value
         *      value: the value on this point
         *  return:
         *      void
         *  exceptions:
         *      ID_Exception: somethin wrong with id. in following cases:
         *          1:somethin wrong with pID. out of boundary;
         */
        void setPointValue(_Point_ID pID, _Point_Value value)
        throw (ID_Exception) {
            typename PointMap::iterator _ite_pID;
            Point* tempPoint;
            if (pID > Max_ID || pID < Min_ID) {
                throw ID_Exception(pID, "ID outof boundary.");
            }
            //first find wether pID is in pointMap
            _ite_pID = points_map.find(pID);
            if (_ite_pID == points_map.end()) {
                //if we did not find it then create it
                tempPoint = new Point(pID);
                points_list.push_back(tempPoint);
                points_map.insert(typename PointMap::value_type(pID, tempPoint));
            } else {
                tempPoint = _ite_pID->second;
            }
            //set values
            tempPoint->value = value;
        }

        /*  overload of operator ()
         *  used to get a reference value of pID point
         *  args:
         *      pID: the id of point need to set value
         *  return:
         *      reference value of pID
         *  exceptions:
         *      ID_Exception: somethin wrong with id. in following cases:
         *          1:somethin wrong with pID. out of boundary;
         */
        _Point_Value & operator () (_Point_ID pID)
        throw (ID_Exception) {
            typename PointMap::iterator _ite_pID;
            Point* tempPoint;
            if (pID > Max_ID || pID < Min_ID) {
                throw ID_Exception(pID, "ID outof boundary.");
            }
            //first find wether pID is in pointMap
            _ite_pID = points_map.find(pID);
            if (_ite_pID == points_map.end()) {
                //if we did not find it then create it
                tempPoint = new Point(pID);
                points_list.push_back(tempPoint);
                points_map.insert(typename PointMap::value_type(pID, tempPoint));
            } else {
                tempPoint = _ite_pID->second;
            }
            //return reference
            return tempPoint->value;
        }

        /*  overload of operator []
         *  used to get a reference value of pID point
         *  args:
         *      pID: the id of point need to set value
         *  return:
         *      reference of the Point
         *  exceptions:
         *      ID_Exception: somethin wrong with id. in following cases:
         *          1:somethin wrong with pID. out of boundary;
         */
        Point & operator [] (_Point_ID pID)
        throw (ID_Exception) {
            typename PointMap::iterator _ite_pID;
            Point* tempPoint;
            if (pID > Max_ID || pID < Min_ID) {
                throw ID_Exception(pID, "ID outof boundary.");
            }
            //first find wether pID is in pointMap
            _ite_pID = points_map.find(pID);
            if (_ite_pID == points_map.end()) {
                //if we did not find it then create it
                tempPoint = new Point(pID);
                points_list.push_back(tempPoint);
                points_map.insert(typename PointMap::value_type(pID, tempPoint));
            } else {
                tempPoint = _ite_pID->second;
            }
            //return reference
            return *tempPoint;
        }

        /* print all Graph to outstream
         * args:
         * ostr : an ostream that to be print
         */
        void printGraph(std::ostream& ostr) {
            typename PointList::iterator _p_first, _p_end;
            typename EdgeList::iterator _e_first, _e_end;
            Point* point;
            Edge* edge;
            _p_first = points_list.begin();
            _p_end = points_list.end();
            while (_p_first != _p_end) {
                point = *_p_first;
                ostr << "Point " << point->id << " Value: " << point->value <<
                        " Sum: " << point->valueSum <<
                        " with edges:" << std::endl;
                _e_first = point->edges_begin.begin();
                _e_end = point->edges_begin.end();
                while (_e_first != _e_end) {
                    edge = *_e_first;
                    ostr << "\t(" << edge->point_begin->id << " , " <<
                            edge->point_end->id << " ) value: " <<
                            edge->value << std::endl;
                    _e_first++;
                }
                _p_first++;
            }
        }

        /* deep copy datas and graph from graph
         * args:
         * graph: graph which to be copyied
         * return: this
         */
        _T_Graph& clone(const _T_Graph& graph) {
            release();
            Max_ID = graph.Max_ID;
            Min_ID = graph.Min_ID;
            return *this;
        }

        //construction function

        _T_Graph() {
            edges_list.clear();
            points_list.clear();
            points_map.clear();
        }

        /* construction function
         * args:
         *  min : the minimum id for point
         *  max: the maximum id for point
         */
        _T_Graph(_Point_ID min, _Point_ID max) {
            Max_ID = max;
            Min_ID = min;
            edges_list.clear();
            points_list.clear();
            points_map.clear();
        }

        /* construction copy
         */
        _T_Graph(const _T_Graph& graph) {
            clone(graph);
        }

        /* operator = , copy
         */
        _T_Graph & operator =(const _T_Graph& graph) {
            clone(graph);
            return *this;
        }

        /* release all data
         */
        void release(void) {
            typename PointList::iterator _p_first, _p_end;
            typename EdgeList::iterator _e_first, _e_end;

            points_map.clear();
            //release Points;
            _p_first = points_list.begin();
            _p_end = points_list.end();
            while (_p_first != _p_end) {
                delete (*_p_first);
                _p_first++;
            }
            points_list.clear();

            //release Edges
            _e_first = edges_list.begin();
            _e_end = edges_list.end();
            while (_e_first != _e_end) {
                delete(*_e_first);
                _e_first++;
            }
            edges_list.clear();
        }

        /* deconstruction
         */
        ~_T_Graph() {
            release();
        }
    };

}
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* _GRAPH_T_H */

