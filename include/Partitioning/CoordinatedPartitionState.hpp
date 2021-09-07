/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor			     			     ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0							     ***/
/***********************************************************/

#ifndef __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__
#define __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__

#pragma once

#include "Record.hpp"
#include "Edge/Edge.hpp"
#include "Partitioning/Utility/Globals.hpp"
#include <vector>
#include <set>

namespace CXXGRAPH
{
    namespace PARTITIONING
    {
        template <typename T>
        class CoordinatedPartitionState : public PartitionState<T>
        {
        private:
            std::map<int, CoordinatedRecord<T>> record_map;
            std::vector<std::atomic<int>> machines_load_edges;
            std::vector<std::atomic<int>> machines_load_vertices;
            Globals GLOBALS;
            int MAX_LOAD;
            //DatWriter out; //to print the final partition of each edge
        public:
            CoordinatedPartitionState(Globals &G);
            ~CoordinatedPartitionState();

            Record<T> &getRecord(int x);
            int getMachineLoad(int m);
            void incrementMachineLoad(int m, Edge<T> &e);
            int getMinLoad();
            int getMaxLoad();
            std::vector<int> getMachines_load();
            int getTotalReplicas();
            int getNumVertices();
            std::set<int> getVertexIds();

            void incrementMachineLoadVertices(int m);
            std::vector<int> getMachines_loadVertices();
        };
        template <typename T>
        CoordinatedPartitionState<T>::CoordinatedPartitionState(Globals &G) : record_map()
        {
            this->GLOBALS = G;
            for (int i = 0; i < GLOBALS.numberOfPartition; i++)
            {
                machines_load_edges.push_back(std::atomic<int>(0));
                machines_load_vertices.push_back(std::atomic<int>(0));
            }
            MAX_LOAD = 0;
        }
        template <typename T>
        CoordinatedPartitionState<T>::~CoordinatedPartitionState()
        {
        }
        template <typename T>
        Record<T> &CoordinatedPartitionState<T>::getRecord(int x)
        {
            if (record_map.find(x) == record_map.end())
            {
                record_map[x] = CoordinatedRecord<T>();
            }
            return record_map.at(x);
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getMachineLoad(int m)
        {
            return machines_load_edges.at(m);
        }
        template <typename T>
        void CoordinatedPartitionState<T>::incrementMachineLoad(int m, Edge<T> &e)
        {
            machines_load_edges[m] = machines_load_edges[m] + 1;
            int new_value = machines_load_edges.at(m);
            if (new_value > MAX_LOAD)
            {
                MAX_LOAD = new_value;
            }
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getMinLoad()
        {
            int MIN_LOAD = std::numeric_limits<int>::max();
            auto machines_load_edges_it = machines_load_edges.begin();
            for (machines_load_edges_it; machines_load_edges_it != machines_load_edges.end(); ++machines_load_edges_it)
            {
                int loadi = *machines_load_edges_it;
                if (loadi < MIN_LOAD)
                {
                    MIN_LOAD = loadi;
                }
            }
            return MIN_LOAD;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getMaxLoad()
        {
            return MAX_LOAD;
        }
        template <typename T>
        std::vector<int> CoordinatedPartitionState<T>::getMachines_load()
        {
            std::vector<int> result;
            for (int i = 0; i < machines_load_edges.size(); i++)
            {
                result.push_back(machines_load_edges[i]);
            }
            return result;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getTotalReplicas()
        {
            //TODO
            int result = 0;
            auto record_map_it = record_map.begin();
            for (record_map_it; record_map_it != record_map.end(); ++record_map_it)
            {
                int r = record_map_it->second.getReplicas();
                if (r > 0)
                {
                    result += r;
                }
                else
                {
                    result++;
                }
            }
            return result;
        }
        template <typename T>
        int CoordinatedPartitionState<T>::getNumVertices()
        {
            return record_map.size();
        }
        template <typename T>
        std::set<int> CoordinatedPartitionState<T>::getVertexIds()
        {
            //if (GLOBALS.OUTPUT_FILE_NAME!=null){ out.close(); }
            std::set<int> result;
            auto record_map_it = record_map.begin();
            for (record_map_it; record_map_it != record_map.end(); ++record_map_it)
            {
                result.insert(record_map_it->first);
            }
            return result;
        }
        template <typename T>
        void CoordinatedPartitionState<T>::incrementMachineLoadVertices(int m)
        {
            machines_load_vertices[m] = machines_load_vertices[m] + 1;
        }
        template <typename T>
        std::vector<int> CoordinatedPartitionState<T>::getMachines_loadVertices()
        {
            std::vector<int> result;
            for (int i = 0; i < machines_load_vertices.size(); i++)
            {
                result.push_back(machines_load_vertices.at(i));
            }
            return result;
        }
    }
}

#endif // __CXXGRAPH_PARTITIONING_COORDINATEDPARTITIONSTATE_H__