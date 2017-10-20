/* 
 * File:   Graph_Alg_Search.h
 * Author: yangkkb
 *
 * Created on 2017��10��11��, ����12:04
 */

#ifndef _GRAPH_ALG_SEARCH_H
#define	_GRAPH_ALG_SEARCH_H

//================== Head file include
#include "Graph_T.h"

//================== define template algorithems
namespace graph {

    //================== define exceptions

    /* this exception is used for algorithems , when the path is not reachable
     */
    template<typename _Point_ID>
    class _T_PathException : public graph::Exception {
    public:
        _Point_ID startID, endID;
        std::string errorMSG;

        /*  construction funcion
         *  args:
         *      start: the start id of path
         *      end: the end id of path
         *      ErrorMSG: an error message
         */
        _T_PathException(_Point_ID start, _Point_ID end, std::string ErrorMSG) {
            startID = start;
            endID = end;
            errorMSG = ErrorMSG;
        }

        virtual void printMSG(std::ostream& ostr) {
            ostr << "Path:(" << startID << "," << endID << ")"
                    << " encounters an ERROR: " << errorMSG;
        }
    };

    //================== define algs

    /*  this template function is used to find a shortest path between startId
     *  andend ID. this function use a method similar to Dijkstra. this function
     *  can get the point to point shortest point in directed graph.
     *
     *  template args:
     *      _Point_ID:see _T_Graph for information and warnings
     *      _Point_Value:see _T_Graph for information and warnings
     *      _Tp_Graph:the Graph class see _T_Graph for information and warnings
     *  args:
     *      _graph: a reference of _T_Graph that contains the graph being processed
     *      startID: ID of the start point in search path
     *      endID:ID of the end(target) point in search path
     *      maxValue: the max value of point. it means point not searched or
     *               presently not find path should have a ideal infinity value.
     *               any meanful value (path or accumulated edges value should
     *               less than maxValue). for long maxValue=0x7FFFFFFF. this
     *               max value will apply on valueSum
     *  return:
     *      _Point_Value: the minmum value ot path from start point to end point.
     *                   more path infromation can be found in _graph relevant
     *                   end point 's member path . or using method printPath.
     *  expceptions:
     *      _T_ID_Exception:this exception is something wrong with point ID
     *                      and thrown in following cases:
     *          1:startID or end ID is out of bound;
     *
     *      _T_PathException:this exception is something wrong with path.when
     *                       this exception thrown it may means path or point
     *                       of path not exist. exception thrown in following
     *                       cases:
     *          1:  no edge contact with start point or end point.(start point 
     *              or end point not found in Pointmap)
     *          2: path no exist. no path can reach between start point to end
     *              point
     */
    template<typename _Point_ID, typename _Tp_Graph, typename _Point_Value>
    _Point_Value searchPath(_Tp_Graph& _graph, _Point_ID startID, _Point_ID endID,
            _Point_Value maxValue)
    throw (_T_PathException<_Point_ID>, _T_ID_Exception<_Point_ID>) {
        //typedef types
        //typedef __Tp_Graph;
        typedef _Tp_Graph __Tp_Graph;
        //for test
        //typedef _T_Graph<long, long> __Tp_Graph;

        // edge point and other types
        typedef typename __Tp_Graph::Edge Edge;
        typedef typename __Tp_Graph::EdgeList EdgeList;
        typedef typename __Tp_Graph::Point Point;
        typedef typename __Tp_Graph::PointList PointList;
        typedef typename __Tp_Graph::PointMap PointMap;
        typedef _T_ID_Exception<_Point_ID> ID_Exception;
        typedef _T_PathException<_Point_ID> PathException;

        //define variables
        __Tp_Graph& graph = _graph;
        typename PointMap::iterator _ite_start, _ite_end, _ite_map_end;
        typename PointList::iterator _ite_pfirst, _ite_pend;
        typename PointList::iterator _ite_searlist_first, _ite_searlist_end;
        typename EdgeList::iterator _ite_edge_first, _ite_edge_end;
        /* warning _ite_searlist_end must update it may invalid */
        Point* ptrPointCurrent, * ptrPointNext;
        PointList searchList;
        Edge* ptrEdge;
        _Point_Value tmpSumValue;
        //first check ID boundry
        if (startID > graph.Max_ID || startID < graph.Min_ID) {
            throw ID_Exception(startID, "ID outof boundary.");
        }
        if (endID > graph.Max_ID || endID < graph.Min_ID) {
            throw ID_Exception(endID, "ID outof boundary.");
        }
        //find point in pointMap
        _ite_start = graph.points_map.find(startID);
        _ite_end = graph.points_map.find(endID);
        _ite_map_end = graph.points_map.end();
        if (_ite_start == _ite_map_end || _ite_end == _ite_map_end) {
            throw PathException(startID, endID, "Path Not exist, ID Not in map.");
        }
        //give every point a max value
        _ite_pfirst = graph.points_list.begin();
        _ite_pend = graph.points_list.end();
        while (_ite_pfirst != _ite_pend) {
            (*_ite_pfirst)->valueSum = maxValue;
            _ite_pfirst++;
        }
        // give start point value
        ptrPointCurrent = _ite_start->second;
        ptrPointCurrent->valueSum = ptrPointCurrent->value;
        ptrPointCurrent->path.clear();
        ptrPointCurrent->path.push_back(ptrPointCurrent->id);
        searchList.clear();
        searchList.push_back(ptrPointCurrent);
        // begin search
        _ite_searlist_first = searchList.begin();
        while (_ite_searlist_first != searchList.end()) {
            ptrPointCurrent = *_ite_searlist_first;
            _ite_edge_first = ptrPointCurrent->edges_begin.begin();
            _ite_edge_end = ptrPointCurrent->edges_begin.end();
            while (_ite_edge_first != _ite_edge_end) {
                ptrEdge = (*_ite_edge_first);
                ptrPointNext = ptrEdge->point_end;
                tmpSumValue = ptrPointCurrent->valueSum + ptrEdge->value +
                        ptrPointNext->value;
                if (tmpSumValue < ptrPointNext->valueSum) {
                    //check if value is less then update
                    ptrPointNext->valueSum = tmpSumValue;
                    searchList.push_back(ptrPointNext);
                    ptrPointNext->path = ptrPointCurrent->path;
                    ptrPointNext->path.push_back(ptrPointNext->id);
                }
                _ite_edge_first++;
            }
            searchList.erase(_ite_searlist_first);
            _ite_searlist_first = searchList.begin();
        }
        if (_ite_end->second->valueSum == maxValue) {
            throw PathException(startID, endID, "Path Not exist, Unreachable.");
        }
        return _ite_end->second->valueSum;
    }//end of function searchPath



}// end of namespace

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* _GRAPH_ALG_SEARCH_H */

