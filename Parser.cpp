#include "Parser.h"

Parser::Parser(char* file){
    this->file = file;
    this->ifs.open(file);
    this->delimiters = "{},\t ()\n\r";
}

Parser::~Parser(){
    if(ifs.is_open()){
        ifs.close();
    }
}

vector<string>& Parser::next_tokens(){
    ret_container.clear();
    parts.clear();
    if(ifs.getline(str, BUFFER_SIZE, ';'))
    {
        boost::split(parts, str, boost::is_any_of(delimiters));
        for(int i = 0; i < parts.size(); i++)
        {
            if(parts[i].size() > 0 && parts[i].at(0) != ' '){
                ret_container.push_back(parts[i]);
            }
        }

    }
    return ret_container;
}




/*int main()
{
    ifstream ifs;
    if(ifs.is_open()){
        cout<<"Open\n";
    }
    ifs.open ("Parser_Test.txt", ifstream::in);
    string delimiters("{},\t ()\n\r");
    //string delimiters(" ");
    vector<std::string> parts;

    char str[32*1024];

    while (ifs.getline(str, 32*1024, ';'))
    {
        //cout<<"Obtained line = "<<endl;
        //cout<<str<<endl;
        boost::split(parts, str, boost::is_any_of(delimiters));
        for(int i = 0; i < parts.size(); i++)
        {
            if(parts[i].size() > 0 && parts[i].at(0) != ' '){
                cout<<"tok = "<<parts[i]<<endl;
            }
        }
        parts.clear();
    }
    ifs.close();
    
}*/