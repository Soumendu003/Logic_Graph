
class Light_Graph:

    def __init__(self):

        self.nodes = {}

    def add_node(self, node, tot_port = 1):

        self.nodes.update({node : tot_port})

    def add_edge(self,node_u, node_v, **attr):

        pass