#include "Map.h"

Map::Map (int index_size, int bucket_capacity)
{
    f = fopen("Map_log1.txt", "w");
    index_table = std::vector<uint32_t>(index_size, 0);
    std::cout<<"Allocation Done"<<std::endl;
    //this->bucket.reserve(bucket_capacity);
    // Sets the first place Invalid
    char val[VAL_SIZE];
    char port[PORT_SIZE];
    strcpy(val, "INVALID");
    strcpy(port, "N/A"); 
    update_bucket(val, val, port);
}

void Map::update (int index, char* key, char* value, char* port){

    fprintf(f,"key = %s\tvalue = %s\t port = %s\n",key,value,port);    
    if (index_table[index] >= bucket.size())
    {
        std::cout<<"index = "<<index<<std::endl;
        std::cout<<"bucket size = "<<bucket.size()<<std::endl;
    }

    if (index_table[index] == 0)
    {
        index_table[index] = update_bucket(key, value, port);
    }
    else {
        insert_bucket(index_table[index], key, value, port);
    }
    fprintf(f,"Returned from update\n");
    
}

bool Map::get (int index, char* key, char* val_container, char* port_container){
    int ele_index = get_ele_index(index_table[index], key);
    if(ele_index < 0)
    {
        return false;
    }
    else{
        strcpy(val_container, bucket[ele_index].value);
        strcpy(port_container, bucket[ele_index].port);
        return true;
    }
}

void Map::get_size()
{
    std::cout<<"Bucket size = "<<bucket.size()<<std::endl;
}

bool Map::contains_key(int index, char* key)
{
    int ele_index = get_ele_index(index_table[index], key);
    if(ele_index < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}

uint32_t Map::update_bucket (char* key, char* value, char* port)
{
    key_val tem;
    strncpy(tem.key, key, KEY_SIZE);
    strncpy(tem.value, value, VAL_SIZE);
    strncpy(tem.port, port, PORT_SIZE);
    tem.next = 0;
    bucket.push_back(tem);
    //std::cout<<"Item pushed"<<std::endl;
    return bucket.size() - 1;
}



void Map::insert_bucket (uint32_t index, char* key, char* value, char* port)
{
    if(index >= bucket.size())
    {
        std::cout<<"index = "<<index<<std::endl;
        std::cout<<"bucket size = "<<bucket.size()<<std::endl;
    }
    if(strcmp(bucket[index].key, key) == 0)
    {
        strncpy(bucket[index].value, value, VAL_SIZE);
        strncpy(bucket[index].port, port, PORT_SIZE);
    }
    else if(bucket[index].next == 0)
    {
        bucket[index].next = update_bucket(key, value, port);
    }
    else
    {
        insert_bucket(bucket[index].next, key, value, port);
    }

    return;
    
}

int Map::get_ele_index (uint32_t index, char* key)
{
    if(strcmp(bucket[index].key, key) == 0)
    {
        return index;
    }
    else if (bucket[index].next == 0)
    {
        //std::cout<<" Invalid element tried to acces = "<<key<<std::endl;
        return -1;
    }
    else
    {
        return get_ele_index(bucket[index].next, key);
    }
    
}

