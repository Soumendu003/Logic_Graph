#ifndef GRAPH_APPLICATION_H
#define GRAPH_APPLICATION_H
#include "Wire.h"
#include "Map.h"

class Graph_Application{
    private:
        Map connections;
        Wire wire;
        Map graph;
    public:
        Graph_Application(){};
        Graph_Application(int index_size, int capacity);
        ~Graph_Application(){};
        void process_graph(std::vector<std::string> container);

};


#endif