#include "Wire.h"

Wire::Wire (int index_size, int capacity)
{
    index_table = std::vector<uint32_t>(index_size, 0);
    //this->wire_bucket.reserve(capacity);
    //this->port_bucket.reserve(capacity);
    char val[VAL_SIZE];
    char port[PORT_SIZE];
    strncpy(val, "INVALID",VAL_SIZE);
    strncpy(port, "N/A",PORT_SIZE);
    update_wire_bucket(val);
    update_connection_bucket(val, port);
    //std::cout<<"Constructor Wire Bucket Capacity = "<<wire_bucket.capacity()<<std::endl;
    //std::cout<<"Constructor Port Bucket Capacity = "<<port_bucket.capacity()<<std::endl;
}

void Wire::get_size(){
    std::cout<<"Wire_bucket size = "<<wire_bucket.size()<<std::endl;
    std::cout<<"Connection bucket size = "<<port_bucket.size()<<std::endl;
}

void Wire::update_wire(int index, char* key){
    //std::cout<<" Wire Bucket Capacity = "<<wire_bucket.capacity()<<std::endl;
    //std::cout<<"Inside update bucket with index_table[index] = "<<index_table[index]<<std::endl;
    //std::cout<<" Wire bucket size = "<<wire_bucket.size()<<std::endl;
    //std::cout<<" key val = "<<key<<std::endl;
    if(index_table[index] == 0)
    {
        index_table[index] = update_wire_bucket(key);
    }
    else{
        insert_wire_bucket(index_table[index], key);
    }
}

uint32_t Wire::update_wire_bucket(char* key){
    key_connect tem;
    strncpy(tem.key, key, WIRE_SIZE);
    tem.connect = 0;
    tem.next = 0;
    wire_bucket.push_back(tem);
    //std::cout<<"Pushed value"<<std::endl;
    return wire_bucket.size() - 1;
}

void Wire::insert_wire_bucket(uint32_t index, char* key){

    //std::cout<<" Inside insert_wire_bucket with index = "<<index<<"\t key = "<<key<<std::endl;
    if(strcmp(wire_bucket[index].key, key) == 0)
    {
        // Same wire value inserted
        return;
    }
    else if(wire_bucket[index].next == 0)
    {
        int tem = update_wire_bucket(key);
        //std::cout<<" Last element index returned by update_wire_bucket = "<<tem<<std::endl;
        wire_bucket[index].next = tem;
        //std::cout<<" Last element index = "<<wire_bucket[index].next<<std::endl;
    }
    else
    {
        insert_wire_bucket(wire_bucket[index].next, key);
    }

    //std::cout<<"Returning from insert_wire_bucket"<<std::endl;
    
    return;
}

void Wire::update_wire_connection(int index, char* key, char* vertex, char* port){

    int wire_index = get_wire_index(index_table[index], key);

    if(wire_index < 0){
        update_wire(index, key);
        update_wire_connection(index, key, vertex, port);
    }
    else{
        wire_bucket[wire_index].connect = update_connection(wire_bucket[wire_index].connect, vertex, port);
    }


}

uint32_t Wire::update_connection_bucket(char* vertex, char* port){
    val_port tem;
    strncpy(tem.val, vertex, VAL_SIZE);
    strncpy(tem.port, port, PORT_SIZE);
    tem.next = 0;
    port_bucket.push_back(tem);
    return port_bucket.size() - 1;

}

uint32_t Wire::update_connection(uint32_t index, char* vertex, char* port){

    if(index == 0)
    {
        return update_connection_bucket(vertex, port);
    }
    else{
        insert_connection_bucket(port_bucket[index].next, vertex, port);
        return index;
    }

}

void Wire::insert_connection_bucket(uint32_t index, char* vertex, char* port){
    if(strcmp(port_bucket[index].port, port) == 0 &&  strcmp(port_bucket[index].val, vertex) == 0)
    {
        return;
    }
    else if(port_bucket[index].next == 0)
    {
        port_bucket[index].next = update_connection_bucket(vertex, port);
    }
    else
    {
        insert_connection_bucket(port_bucket[index].next, vertex, port);
    }
    
}


int Wire::get_wire_index(uint32_t index, char* key){
    if(strcmp(wire_bucket[index].key, key) == 0)
    {
        return index;
    }
    else if (wire_bucket[index].next == 0)
    {
        return -1;
    }
    else
    {
        return get_wire_index(wire_bucket[index].next, key);
    }

}

bool Wire::contains(int index, char* key){
    int wire_index = get_wire_index(index_table[index], key);
    if(wire_index < 0)
    {
        return false;
    }
    else{
        return true;
    }
}


bool Wire::get_wire_connections(int index, char* key, std::vector<std::string> &vertices, std::vector<std::string> &ports){
    int wire_index = get_wire_index(index_table[index], key);
    if(wire_index < 0)
    {
        return false;
    }
    else if(wire_bucket[wire_index].connect == 0)
    {
        return false;
    }
    else{
        index = wire_bucket[wire_index].connect;
        while(index != 0)
        {   
            vertices.push_back(std::string(port_bucket[index].val));
            ports.push_back(std::string(port_bucket[index].port));
            index = port_bucket[index].next;
        }
        return true;
    }

}

int main()
{
    Wire m = Wire(1000,1000);
    char val[VAL_SIZE];
    char key[VAL_SIZE];
    char port[PORT_SIZE];
    strncpy(val, "Hazard", VAL_SIZE);
    strncpy(key, "Guddu", WIRE_SIZE);
    strncpy(port, "17", PORT_SIZE);
    m.update_wire(1,key);
    m.update_wire_connection(1,key,val,port);
    return 0;
}