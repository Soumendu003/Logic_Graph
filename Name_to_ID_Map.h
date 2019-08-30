#ifndef CONNECTION_H
#define CONNECTION_H

#include<vector>
#include<cstdlib>
#include<string>
#include<string.h>
#include<iostream>
#include<functional>

#define KEY_SIZE 128
#define BUCKET_SIZE 65536

struct index_t{
    uint16_t bucket_index;
    uint16_t array_index;
};

struct bucket_t{
    char key[KEY_SIZE];
    uint32_t ID;
    uint16_t next_bucket_index;
    uint16_t next_array_index;
};



class Name_to_ID_Map{
    private:
        std::vector<index_t> index_table;
        std::vector<bucket_t*> array;
        std::hash<std::string> index_hash_maker;
        const uint32_t index_musk;
        uint16_t next_bucket_void;

    public:
        Name_to_ID_Map():index_musk(0){};
        Name_to_ID_Map(int index_table_size);
        ~Name_to_ID_Map();
        void update(std::string name, uint32_t ID);
        uint32_t get_ID(std::string name);
    
    private:
        void update_bucket(uint32_t index, char* key, uint32_t ID);
        index_t append_bucket(char* key, uint32_t ID);
        void insert_bucket(index_t index, char* key, uint32_t ID);
        uint32_t ID(uint32_t index, char* key);
        uint32_t get_ID_from_bucket(index_t index, char* key);
};


#endif