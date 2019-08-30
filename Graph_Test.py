import networkx as nx
import Util.Parser as P
import Util.Graph_Processor as GP
import Util.Light_Graph as LG
import Util.Graph_Parser as GPr
import os


CmdProcessor = P.Parser("/home/sghorui/Trace_Path/sample_design_file")

CmdProcessor.init_command_processor()


#tok = P.Tokenizer("/home/sghorui/Trace_Path/sample_design_file")

Processor = GPr.Graph_Parser(nx.DiGraph())

tokens = CmdProcessor.get_next_command()

print(os.getpid())

while(tokens != None):

    Processor.process_tokens(tokens)    
    tokens = CmdProcessor.get_next_command()

#Processor.resolve_edges()
#Processor.print_Graph()
    
