import sys

class Graph_Processor():

    def __init__(self, Graph):

        # Holds the Original Graph
        self.__Graph = Graph
        # Holds the Intermetiate assignment
        self.__Connections = {}
        self.__Wires = {}
        self.__count = 0

        self.f = open("log.txt","w")

    # Review Insertion
    def __add_node(self, node, Type = "Unkwn" ,tot_port = 1):

        self.__Graph.add_node(node, Type = Type, tot_port = tot_port)

    def __add_wire(self, wire):

        if(wire in self.__Wires):

            self.f.write("Multiple Definition of wire = "+wire+"  found. \n")
        
        else:

            self.__Wires.update({wire : [[],[]]})


    '''def __find_root(self,node):

        if(node not in self.__Connections):
            return node
        elif(self.__Connections[node] not in self.__Connections):
            return self.__Connections[node]
        else:
            return self.__find_root(self.__Connections[node])'''


    # Review Creation    
    # Handle node_u = None  
    # if check_collection = True then check whether exists in collection, else insert in the collection
    # There must be a source port as well as a destination port attribute of each edge
    def __add_edge(self,node_u, node_v, s_port = '0', d_port = '0'):

        if(node_v in self.__Wires):

            if(node_u in self.__Graph.nodes):

                self.__Wires[node_v][0].append((node_u, s_port))
                return
            
            if(node_u in self.__Wires):

                self.__Wires[node_v].append((node_u, s_port))
                self.f.write("Input of the wire = "+node_v+"   coming from another wire = "+node_u+"\n")
                return

            if(node_u in self.__Connections):

                source = self.__Connections[node_u]

                if(source[0] in self.__Wires):

                    self.__Wires[source[0]][1].append((node_v, d_port))
                    self.f.write("Input of the wire = "+node_v+"   coming from another wire = "+source[0]+"\n")
                    return
                
                if(source[0] in self.__Graph.nodes):

                    self.__Wires[node_v][0].append((source[0],source[1]))
                    return

            else:

                self.f.write("No concrete definition found for intermediate source = "+node_u+" \n")
            
            if(len(self.__Wires[node_v][0]) > 1):

                self.f.write("Multiple source of the wire = "+node_v+"\n")

            return
        
        if(node_v in self.__Connections):

            if(self.__Connections[node_v][0] not in self.__Graph.nodes):
                
                self.f.write("Multiple source of the signal = "+node_v+"     without being previously assigned to a node\n")
            
            else:

                self.__add_edge(node_u, self.__Connections[node_v][0], s_port = s_port, d_port = self.__Connections[node_v][1])

            return
        
        if(node_v in self.__Graph.nodes):

            if(node_u in self.__Wires):

                self.__Wires[node_u][1].append((node_v, d_port))
                return
            
            if(node_u in self.__Connections):

                source = self.__Connections[node_u]

                if(source[0] in self.__Wires):

                    self.__Wires[source[0]][1].append((node_u,s_port))
                    return
                
                if(source[0] in self.__Graph.nodes):

                    self.__Graph.add_edge(source[0], node_v, s_port = source[1], d_port = d_port)
                    return

                else:

                    self.f.write("node_u = "+node_u+" doesn't get a concrete parent, given parent is = "+source[0]+"\n")
                    return
            
            if(node_u in self.__Graph.nodes):

                self.__Graph.add_edge(node_u, node_v, s_port = s_port, d_port = d_port)
                return
            
            else:

                pass
                #self.f.write("Graph node = "+node_v+"  gets input from previously unknown signal = "+node_u+"\n")

        else:

            if(node_u in self.__Connections):

                try:
                    self.__Connections.update({node_v : self.__Connections[node_u]})
                except:
                    print("Node_u = "+node_u+"\t parent = "+str(self.__Connections[node_u]))
                return
            
            if(node_u in self.__Wires or node_u in self.__Graph.nodes):

                self.__Connections.update({node_v : (node_u, s_port)})
                return

            else:

                pass
                #self.f.write("node_u = "+node_u+"  is previously undeclared \n")

                


    def __handle_alias(self,tok_v, tok_u):

        tok_u = tok_u.split("[")
        #print("tok_u = "+tok_u[0])

        if(len(tok_u) == 1):                  #tok_v not a vector input

            self.__add_edge(tok_u[0], tok_v)
        
        elif(len(tok_u) == 2):

            self.__add_edge(tok_u[0], tok_v, s_port = tok_u[1][:-1])

    # Takes a list of tokens and process those
    def process_tokens(self, tokens):

        self.__count += 1

        if(self.__count < len(self.__Connections)):

            print(self.__Connections)
            sys.exit()

        if(tokens[0] == "input"):

            if(len(tokens) == 2):

                self.__add_node(tokens[1], "Input")
                return
            
            if(len(tokens) == 3):

                self.__add_node(tokens[2], "Input", int(tokens[1][1 : len(tokens[1])-3]) + 1)
            
            return
        
        if(tokens[0] == "output"):

            if(len(tokens) == 2):

                self.__add_node(tokens[1], "Output")
                return
            
            if(len(tokens) == 3):

                self.__add_node(tokens[2], "Output", int(tokens[1][1 : len(tokens[1])-3]) + 1)

            return

        if(tokens[0] == "alias"):

            self.__handle_alias(tokens[1],tokens[3])
            return

        if(tokens[0] == "wire"):

            self.__add_wire(tokens[1])
            return
        
        if(tokens[0] == "assign"):
            
            self.__add_edge(tokens[3], tokens[1])
            return

        if("MED_LUT" in tokens[0]):

            self.__add_node(tokens[1], Type = "LUT", tot_port = (len(tokens) -2 )/2)

            # Process the .O port
            self.__add_edge(tokens[1], tokens[3], s_port = tokens[2])

            i = 4

            # takes 2 tokens at a time and processes
            while(i < len(tokens)):

                self.__add_edge(tokens[i+1], tokens[1], d_port = tokens[i])
                i += 2

            return

        if("MED_LDN" == tokens[0][0:7] or "MED_FD" == tokens[0][0:6]):

            print(self.__count)
            print(" Number of Nodes = "+str(len(self.__Graph.node)))
            print("Collection size = "+str(len(self.__Connections)))

            self.__add_node(tokens[1], Type = "LUT", tot_port = (len(tokens) -2 )/2)

            # Process the .Q port
            self.__add_edge(tokens[1], tokens[3], s_port = tokens[2])

            i = 4

            # takes 2 tokens at a time and processes
            while(i < len(tokens)):

                self.__add_edge(tokens[i+1], tokens[1], d_port = tokens[i])
                i += 2

            return

    def resolve_edges(self):

        for key in self.__Wires:

            if(len(self.__Wires[key][0]) == 0):

                self.f.write("No input found for the Wire = "+key+"\n")
            
            if(self.__Wires[key][0][0] not in self.__Graph.nodes):

                self.f.write("Input to the wire = "+key+"  not found in Graph Nodes. input node = "+self.__Wires[key][0][0]+"\n")

            else:

                for ele in self.__Wires[key][1]:

                    if(ele[0] in self.__Wires):

                        self.f.write(" wire = "+ele[0]+"  getting input from another wire = "+key+"\n")
                    
                    if(ele[0] in self.__Graph.nodes):

                        self.__Graph.add_edge(self.__Wires[key][0][0], ele[0], s_port = self.__Wires[key][0][1], d_port = ele[1])
                    
                    else:

                        self.f.write("Output of the wire = "+key+"  going to non concrete signal = "+ele[0]+"\n")

                    



    def print_Graph(self):

        print(self.__Graph.nodes(data = True))

    def get_Graph(self):

        return self.__Graph












