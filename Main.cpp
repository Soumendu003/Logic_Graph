#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <cctype>
#include <boost/algorithm/string.hpp>
#include "Graph_Application.h"
using namespace std;

int main()
{
    ifstream ifs;
    ifs.open ("/home/sghorui/Trace_Path/sample_design_file");
    string delimiters("{},\t ()\n\r");
    //string delimiters(" ");
    vector<std::string> parts;
    Graph_Application app(2500000, 2500000);

    char str[32*1024];
    vector<string> container;
    while (ifs.getline(str, 32*1024, ';'))
    {
        container.clear();
        parts.clear();
        boost::split(parts, str, boost::is_any_of(delimiters));
        for(int i = 0; i < parts.size(); i++)
        {
            if(parts[i].size() > 0 && parts[i].at(0) != ' '){
                container.push_back(parts[i]);
            }
        }
        app.process_graph(container);
    }
    ifs.close();
    
}