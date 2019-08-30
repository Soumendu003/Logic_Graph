#ifndef MAP_H
#define MAP_H

#include<vector>
#include<cstdlib>
#include<string.h>
#include<iostream>
#include <fstream>

#define KEY_SIZE 32
#define VAL_SIZE 32
#define PORT_SIZE 8
#define INDEX_TABLE_SIZE 65536

struct key_val {
    char key[KEY_SIZE];
    char value[VAL_SIZE];
    char port[PORT_SIZE];
    uint32_t next;
};


class Map{
    private:
        std::vector<uint32_t> index_table;
        std::vector<key_val> bucket;
        FILE* f;

    public:
        explicit Map() {
            std::cout<<"Void Map Constructor caleed"<<std::endl;
        };
        Map(int index_size, int bucket_capacity);
        ~Map() {};
        void update(int index, char* key, char* value, char* port);
        bool get(int index, char* key, char* val_container, char* port_container);
        bool contains_key(int index, char* key);
        void get_size();

    private:
        uint32_t update_bucket(char* key, char* value, char* port);
        void insert_bucket(uint32_t index, char* key, char* value, char* port);
        int get_ele_index(uint32_t index, char* key);

};
#endif