#include "Graph_Application.h"

Graph_Application::Graph_Application(int index_size, int capacity){
    this->connections = Map(index_size, capacity);
    this->wire = Wire(index_size, capacity);
    this->graph = Map(index_size, capacity);
    this->wire.get_size();
    this->connections.get_size();
}

void Graph_Application::process_graph(std::vector<std::string> container){
    if(container.size() > 0)
    {
        /*if(container[0] == "input")
        {
            std::cout<<"Input "<<"\t";
            for(int i = 1; i < container.size(); i++)
            {
                std::cout<<container[i]<<"\t";
            }
            std::cout<<"\n";
        }
        if(container[0] == "output")
        {
            std::cout<<"Output "<<"\t";
            for(int i = 1; i < container.size(); i++)
            {
                std::cout<<container[i]<<"\t";
            }
            std::cout<<"\n";
        }
        if(container[0] == "alias")
        {
            std::cout<<"Alias "<<"\t";
            for(int i = 1; i < container.size(); i++)
            {
                std::cout<<container[i]<<"\t";
            }
            std::cout<<"\n";
        }
        if(container[0] == "wire")
        {
            std::cout<<"Wire "<<"\t";
            for(int i = 1; i < container.size(); i++)
            {
                std::cout<<container[i]<<"\t";
            }
            std::cout<<"\n";

        }*/
        if(container[0] == "assign")
        {
            std::cout<<"Assign "<<"\t";
            for(int i = 1; i < container.size(); i++)
            {
                std::cout<<container[i]<<"\t";
            }
            std::cout<<"\n";
        }
    }
    
}