

f = open("/home/sghorui/Trace_Path/sample_design_file")

for line in f.read().split(";"):
    print("line is :")
    print(line)

'''with open("/home/sghorui/Trace_Path/sample_design_file") as fileobject:
    
    for line in fileobject.read().split(';'):
        print("line is :")
        print(line)'''
