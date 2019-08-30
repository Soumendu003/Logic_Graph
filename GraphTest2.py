import networkx as nx
import Util.Parser as P
import Util.Graph_Processor as GP

CmdProcessor = P.Parser("/home/sghorui/Trace_Path/sample_design_file")

CmdProcessor.init_command_processor()


#tok = P.Tokenizer("/home/sghorui/Trace_Path/sample_design_file")

#Processor = GP.Graph_Processor(nx.DiGraph())

D = {}

tokens = CmdProcessor.get_next_command()

while(tokens != None):

    if("MED_" in tokens[0]):
        
        if(tokens[0][0:8] not in D):
            print(tokens)
            D.update({tokens[0][0:8]:1})

    elif(tokens[0] not in D):
        print(tokens[0])
        D.update({tokens[0]:1})
    #Processor.process_tokens(tokens)    
    tokens = CmdProcessor.get_next_command()

#print(Processor.Graph.nodes(data = True))
    
