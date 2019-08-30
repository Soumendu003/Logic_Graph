#include "Name_to_ID_Map.h"


Name_to_ID_Map::Name_to_ID_Map(int index_table_size):index_musk(index_table_size -1){
    index_t tem_index;
    tem_index.array_index = 0;
    tem_index.bucket_index = 0;
    index_table = std::vector<index_t>(index_table_size, tem_index);
    std::cout<<"Index Table Allocation Done"<<std::endl;

    next_bucket_void = 0;

    bucket_t tem_bucket;
    tem_bucket.next_array_index = 0;
    tem_bucket.next_bucket_index = 0;
    char key[KEY_SIZE] = "INVALID";
    append_bucket(key, 0);
    std::cout<<"Invalid entry done\n";
}

Name_to_ID_Map::~Name_to_ID_Map(){
    for(int i = 0; i<array.size(); i++)
    {
        free(array[i]);
    }
}

void Name_to_ID_Map::update(std::string name, uint32_t ID){
    int hash = index_hash_maker(name);
    uint32_t index = hash&index_musk;
    char key[KEY_SIZE];
    strncpy(key, name.c_str(), KEY_SIZE);
    update_bucket(index, key, ID);
}

void Name_to_ID_Map::update_bucket(uint32_t index, char* key, uint32_t ID){
    if(index_table[index].array_index == 0 && index_table[index].bucket_index == 0)
    {
        index_t ret = append_bucket(key, ID);
        index_table[index].array_index = ret.array_index;
        index_table[index].bucket_index = ret.bucket_index;
    }
    else{
        //std::cout<<"Possible collision happened"<<std::endl;
        insert_bucket(index_table[index], key, ID);
    }
}

index_t Name_to_ID_Map::append_bucket(char* key, uint32_t ID){
    if(next_bucket_void == 0){
        bucket_t* tem = (bucket_t*)calloc(BUCKET_SIZE, sizeof(bucket_t));
        if(tem == 0){
            std::cout<<"Bucket allocation failed"<<std::endl;
        }
        array.push_back(tem);
        //std::cout<<"Pushed Bucket in array"<<std::endl;
    }
    /*if(array[array.size() - 1] == 0)
    {
        std::cout<<"Bucket allocation failed"<<std::endl;
    }*/
    bucket_t tem;
    tem.next_array_index = 0;
    tem.next_bucket_index = 0;
    strncpy(tem.key, key, KEY_SIZE);
    tem.ID = ID;
    std::cout<<"Size of bucket array = "<<array.size()<<std::endl;
    array[array.size() - 1][next_bucket_void] = tem;
    index_t ret;
    ret.array_index = array.size() - 1;
    ret.bucket_index = next_bucket_void;
    next_bucket_void += 1;
    return ret;
    
}

void Name_to_ID_Map::insert_bucket(index_t index, char* key, uint32_t ID){
    if(strcmp(array[index.array_index][index.bucket_index].key, key) == 0){
        return;
    }
    if(array[index.array_index][index.bucket_index].next_array_index == 0 && array[index.array_index][index.bucket_index].next_bucket_index == 0)
    {
        index_t ret = append_bucket(key, ID);
        array[index.array_index][index.bucket_index].next_array_index = ret.array_index;
        array[index.array_index][index.bucket_index].next_bucket_index = ret.bucket_index;
        return;
    }
    else
    {
        index_t tem;
        tem.array_index = array[index.array_index][index.bucket_index].next_array_index;
        tem.bucket_index = array[index.array_index][index.bucket_index].next_bucket_index;
        insert_bucket(tem, key, ID);
    }
    
}

uint32_t Name_to_ID_Map::get_ID(std::string name){
    int hash = index_hash_maker(name);
    uint32_t index = hash&index_musk;
    char key[KEY_SIZE];
    strncpy(key, name.c_str(), KEY_SIZE);
    return ID(index, key);
}

uint32_t Name_to_ID_Map::ID(uint32_t index, char* key){
    if(index_table[index].array_index == 0 && index_table[index].bucket_index == 0)
    {
        return 0;       // 0 is invalid ID
    }
    else{
        return get_ID_from_bucket(index_table[index], key);
    }

}

uint32_t Name_to_ID_Map::get_ID_from_bucket(index_t index, char* key){
    if(strcmp(array[index.array_index][index.bucket_index].key, key) == 0){
        return array[index.array_index][index.bucket_index].ID;
    }
    if(array[index.array_index][index.bucket_index].next_array_index == 0 && array[index.array_index][index.bucket_index].next_bucket_index == 0)
    {
        return 0;
    }
    else
    {
        index_t tem;
        tem.array_index = array[index.array_index][index.bucket_index].next_array_index;
        tem.bucket_index = array[index.array_index][index.bucket_index].next_bucket_index;
        return get_ID_from_bucket(tem, key);
    }
}