import networkx as nx
import Util.Parser as P
import Util.Graph_Processor as GP

class Graph_Application:
    
    def __init__(self,file):

        self.__file = file
        self.__Graph = None

    def Load_Graph(self):

        CmdProcessor = P.Parser(self.__file)
        CmdProcessor.init_command_processor()
        GProcessor = GP.Graph_Processor(nx.DiGraph())

        tokens = CmdProcessor.get_next_command()

        while(tokens != None):

            GProcessor.process_tokens(tokens)    
            tokens = CmdProcessor.get_next_command()

        GProcessor.resolve_edges()
        
        self.__Graph = GProcessor.get_Graph()

    