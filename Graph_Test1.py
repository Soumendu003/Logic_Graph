import networkx as nx
import numpy as np
import sys

class DGraph(nx.DiGraph):

    def __init__(self, data=None, **attr):

        super(DGraph, self).__init__(data, **attr)
        self.level = None
        self.count = 0
        self.Name_to_Id = {}

    def __initialize_level(self):

        self.level = np.ndarray((self.number_of_nodes(),),dtype = np.uint16)
        self.level.fill(-1)
    
    def level_create(self):

        print("Creating Level")
        self.__initialize_level()

    def add_node(self, n, **attr):
        
        super(DGraph, self).add_node(self.count, **attr)
        self.Name_to_Id.update({n:self.count})
        self.count += 1
        

G = nx.DiGraph()

G.add_node(3,weight=0.4,UTM=('13S',382871,3972649))
G.add_node(4,weight=0.4,UTM=('13S',382871,3972649))

print(G.nodes(data = True))

H = DGraph(G, key ="value")

H.add_node(hash("Hazard"),weight=0.4,UTM=('13S',382871,3972649))
H.add_node(hash("Hazard"),weight=0.4,UTM=('13S',382871,3972649))
H.add_node(hash("Hazard"),weight=0.4,UTM=('13S',382871,3972649))

if( 3 not in G.nodes):
    print("3node not present")
else:
    print("Present")


print(H.node)
print(H.graph)
print(H.node_dict_factory)
print(H.nodes(data = True))

print(" Size = "+str(sys.getsizeof(H)))


H.level_create()

print(H.level)
