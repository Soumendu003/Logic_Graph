import re

# yeilds a line as a list spliting it by delimeters
# Delimeters used ';', ',', '\s', '(', ')' 
def Tokenizer(file):

    try:
    
        with open(file) as fileobject:

            for line in fileobject:

                if not line:
                    return None

                tokens = re.split(r'[;,\s()]\s*',line)
                tokens = [tok for tok in tokens if len(tok) > 0 ]
        

                if(len(tokens) > 0):

                    yield tokens

    finally:

        return None

class Parser:

    def __init__(self,file):

        self.__file = file
        self.__tok = None
        #self.tokens = None

    def init_command_processor(self):

        self.__tok = Tokenizer(self.__file)

    def get_next_command(self):

        try:
            return next(self.__tok)

        except:
            return None

