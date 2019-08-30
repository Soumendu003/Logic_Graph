#ifndef GRAPH_PARSER
#define GRAPH_PARSER

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include <cctype>
#include <boost/algorithm/string.hpp>
using namespace std;

#define BUFFER_SIZE  32*1024

class Parser{
    private:
        ifstream ifs;
        char* file;
        vector<string> parts;
        const vector<string> ret_container;
        char str[BUFFER_SIZE];
        string delimiters;

    public:
        Parser(){};
        Parser(char* file);
        ~Parser();
        const vector<string>& next_tokens();
    
};

#endif
