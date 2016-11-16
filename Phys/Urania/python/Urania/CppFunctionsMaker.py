from Urania.SympyBasic import *
from sympy.utilities import codegen
def strCPP(symfunction): return codegen.ccode(symfunction)

class FunctionMaker:
    def __init__(self,  symfunction, variables,filename):
        self.filename = filename
        self.symfunction = symfunction
        self.variables = variables
        #self.integrals = {}
        self.sublist = []

    def writeSubstitutions(self):
        subs_str = ""
        for thing in self.sublist: subs_str += "Double_t " + str(thing[1]) + " = " + strCPP(thing[0]) +";\n"
        return subs_str

    def prepare(self):
        self.lines = []
        vs = "("
        for var in self.variables: vs += "Double_t " + strCPP(var) +","
        vs= vs[:-1]+ ")"
        self.lines.append("Double_t " + self.filename +vs + "\n")
        self.lines.append("{\n")
        self.lines.append(self.writeSubstitutions())
        self.lines.append("return " + strCPP(self.symfunction.subs(self.sublist)) +";\n")
        self.lines.append("}\n")
    
    def make(self):
        f = file(self.filename + ".C","w")
        f.write("#include <math.h>\n")
        self.prepare()
        for line in self.lines: f.write(line)
        
                
        
        
