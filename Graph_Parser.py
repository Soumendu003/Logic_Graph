import Cython.PyWire as Wire
import Cython.PyMap as Connection

class Graph_Parser():

    def __init__(self, Graph):

        self.__Graph = Graph
        self.__connection = Connection.PyMap(index_size = 1000000, bucket_capacity = 1000000)
        self.__wire = Wire.PyWire(index_size = 1000000, bucket_capacity = 1000000)
        self.__count = 0
        self.f = open("log.txt","w")
        self.__state = 0

    def __add_node(self, node, Type = "Unkwn" ,tot_port = 1):

        self.__Graph.add_node(node, Type = Type, tot_port = tot_port)

    def __add_wire(self, wire):

        self.__wire.update_wire(wire)
    
    def __add_edge(self,node_u, node_v, s_port = '0', d_port = '0'):

        if(self.__wire.contains_wire(node_v)):

            if("'b" in node_u):
                self.f.write("Constant val found = "+node_u+"\n")
                self.__wire.update_wire_connection(node_u, node_v, d_port)
                return

            if(node_u in self.__Graph.nodes):

                self.__wire.update_wire_connection(node_v, node_u, s_port)
                return
            
            if(self.__wire.contains_wire(node_u)):

                self.__wire.update_wire_connection(node_v, node_u, s_port)
                self.f.write("Input of the wire = "+node_v+"   coming from another wire = "+node_u+"\n")
                return
            
            source = self.__connection.get(node_u)
            if(source != None):

                if(self.__wire.contains_wire(source[0])):

                    self.__wire.update_wire_connection(source[0], node_v, d_port)
                    #self.__wire.update_wire_connection(node_v, source[0], source[1])
                    self.f.write("Input of the wire = "+node_v+"   coming from another wire = "+source[0]+"\n")
                    return

            else:

                self.f.write("No concrete definition found for intermediate source = "+node_u+" \n")
            
            return

        if(self.__connection.contains_key(node_v)):

            self.f.write("Multiple source of the signal = "+node_v+"\n")
        
        if(node_v in self.__Graph.nodes):

            if("'b" in node_u):
                self.f.write("Constant val found = "+node_u+"\n")
                self.__wire.update_wire_connection(node_u, node_v, d_port)

            if(self.__wire.contains_wire(node_u)):

                self.__wire.update_wire_connection(node_u, node_v, d_port)
                return
            
            if(self.__connection.contains_key(node_u)):

                source = self.__connection.get(node_u)

                if(self.__wire.contains_wire(source[0])):

                    self.__wire.update_wire_connection(source[0], node_v, d_port)
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

            if(self.__connection.contains_key(node_u)):

                source = self.__connection.get(node_u)
                try:
                    self.__connection.update(node_v, source[0], source[1])
                except:
                    print("Node_u = "+node_u+"\t parent = "+str(source)+"\n")
                return
            
            if(self.__wire.contains_wire(node_u) or node_u in self.__Graph.nodes):

                self.f.write("node_v = "+node_v+"\tnode_u = "+node_u+"\ts_port = "+s_port+"\n")
                self.__connection.update(node_v, node_u, s_port)
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

    def process_tokens(self, tokens):

        self.__count += 1

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

            if(self.__state == 0):
                self.__state = 1
                print("Parsing wires")
            self.__add_wire(tokens[1])
            return
        
        if(tokens[0] == "assign"):

            if(self.__state == 1):
                self.__state = 2
                print("Parsing asignments")   

            self.__add_edge(tokens[3], tokens[1])
            return
        
        if("MED_LUT" in tokens[0]):

            if(self.__state == 2):
                self.__state = 3
                print("Parsing LUT")

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

            self.f.write("Parsed line count = "+str(self.__count)+"\n")
            self.f.write("Total no of Graph node = "+str(len(self.__Graph.nodes))+"\n")
            self.f.write("Wire size ::")
            self.__wire.get_size()
            self.f.write("Connection size::")
            self.__connection.get_size()

            self.__add_node(tokens[1], Type = "LUT", tot_port = (len(tokens) -2 )/2)

            # Process the .Q port
            self.__add_edge(tokens[1], tokens[3], s_port = tokens[2])

            i = 4

            # takes 2 tokens at a time and processes
            while(i < len(tokens)):

                self.__add_edge(tokens[i+1], tokens[1], d_port = tokens[i])
                i += 2

            return