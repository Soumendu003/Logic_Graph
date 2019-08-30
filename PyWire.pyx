from libc.stdlib cimport calloc
from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "Wire.h":
    
    cdef cppclass Wire:
        Wire() except +
        Wire(int index_size, int capacity) except +
        void update_wire(int index, char* key)
        void update_wire_connection(int index, char* key, char* vertex, char* port)
        bool contains(int index, char* key)
        bool get_wire_connections(int index, char* key, vector[string] &vertices, vector[string] &ports)
        void get_size()

cdef class PyWire(object):
    cdef Wire wire
    cdef int mask
    cdef vector[string] val_container
    cdef vector[string] port_container

    def __cinit__(self, index_size = 65536, bucket_capacity = 65536):
        self.wire = Wire(index_size, bucket_capacity)
        self.mask = index_size - 1
        
    def update_wire(self, str key):

        #print("Update Wire called")
        self.wire.update_wire(hash(key) & self.mask, key.encode('UTF-8'))

    def update_wire_connection(self, str key, str vertex, str port):

        #print("update wire connection called")
        self.wire.update_wire_connection(hash(key) & self.mask, key.encode('UTF-8'), vertex.encode('UTF-8'), port.encode('UTF-8'))
        #print("Returned after updating")
    

    def get_connections(self, str key):      

        #print("get connection called")
        if(self.wire.get_wire_connections(hash(key) & self.mask, key.encode('UTF-8'), self.val_container, self.port_container)):
            lst = []
            for i in range(0, self.val_container.size()):

                lst.append((self.val_container[i].decode('UTF-8'), self.port_container[i].decode('UTF-8')))
            
            self.val_container.clear()
            self.port_container.clear()
            return lst
        
        else:
            return None

    def contains_wire(self, str key):

        #print("contains wire called")
        #print(" key = "+key)
        return self.wire.contains(hash(key) & self.mask, key.encode('UTF-8'))

    def get_size(self):
        self.wire.get_size()
            