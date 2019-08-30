from libc.stdlib cimport calloc
from libcpp cimport bool
cdef extern from "Map.h":

    cdef cppclass Map:
        Map() except +
        Map(int index_size, int bucket_capacity) except +
        void update(int index, char* key, char* value, char* port)
        bool get(int index, char* key, char* val_container, char* port_container)
        bool contains_key(int index, char* key)
        void get_size()

cdef class PyMap(object):
    cdef Map cmap;
    cdef int mask;
    cdef char* val_container;
    cdef char* port_container;


    def __cinit__(self, index_size = 65536, bucket_capacity = 65536):

        self.cmap = Map(index_size, bucket_capacity);
        print("Map obtained")
        self.mask = index_size - 1;
        self.val_container = <char*> calloc(32, sizeof(char))
        self.port_container = <char*> calloc(8, sizeof(char))


    def update(self, str key, str value, str port):

        #print("update connection called")
        self.cmap.update(hash(key) & self.mask, key.encode('UTF-8'), value.encode('UTF-8'), port.encode('UTF-8'))

    def get(self, str key):

        #print("get connection called")
        if(self.cmap.get(hash(key) & self.mask, key.encode('UTF-8'), self.val_container, self.port_container)):
            return (self.val_container.decode('UTF-8'), self.port_container.decode('UTF-8'))
        else:
            return None
    
    def get_size(self):

        #print("Index table size in Bytes = "+str(self.cmap.get_index_table_size()))
        #print("Bucket size = "+str(self.cmap.get_bucket_size()))
        #self.cmap.get_bucket_capacity()
        #print("Bucket capacity = "+str(self.cmap.get_bucket_capacity()))
        #print("Index table size = "+str(self.cmap.get_index_table_length()))
        pass
    
    def contains_key(self, str key):

        #print("Contains key called")
        return self.cmap.contains_key(hash(key) & self.mask, key.encode('UTF-8'))

    def get_size(self):

        self.cmap.get_size()