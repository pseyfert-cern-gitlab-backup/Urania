from ROOT import *
from Urania.SympyBasic import *
from Urania.LatexFunctions import *
from Urania.CppFunctionsMaker import strCPP
from math import pi
from os import environ, system as shell
from sympy.utilities import codegen
from time import sleep

def RooGenericfy(symfunction, variables, name = "f"):
    """ Creates a RooGenericPdf from s Sympy expression,
    as well as the necesary RooRealVars
    """
    a = str(symfunction.subs(Pi,pi))
    a = a.replace("**","^")
    dc = {}
    varset = RooArgList()
    
    for i in range(len(variables)):
        varthings = variables[i]
        
        var = varthings[0]
        varmin = varthings[1]
        varmax = varthings[2]
        
        dc[i] = RooRealVar(str(var),str(var),varmin,varmax)
        varset.add(dc[i])
    
    return dc, varset, RooGenericPdf(name,a,varset)

def makeVarString(variables):
    out = str(variables[0])
    for var in variables[1:]: out += ","+ str(var)
    return out

class RooClassEditor:
    def __init__(self,  symfunction, variables,filename):
        self.filename = filename
        

        self.symfunction = symfunction
        self.variables = variables
        for var in self.variables:
            if 'useFirstName' in dir(var): var.useFirstName()
        self.integrals = {}
        self.sublist = []
    def doIntegral(self, code, *vars_and_ranges):
        usedvars = []
        for var in vars_and_ranges: usedvars.append(var[0])
        self.integrals[code] = [usedvars,iter_integrate(self.symfunction,*vars_and_ranges)]
    def doIntegralM(self, code, *vars_and_ranges):
        usedvars = []
        for var in vars_and_ranges: usedvars.append(var[0])
        self.integrals[code] = [usedvars,math_integrate(self.symfunction,*vars_and_ranges)]
    def forceIntegral(self, code, usedvars, integral_val): self.integrals[code] = [usedvars,integral_val]
    
    def copyname(self): return self.filename.replace(".cxx","_copy.cxx")
    def cleanUnresolvedIntegrals(self):
        initial_codes = self.integrals.keys()
        for code in initial_codes:
            if not didIntegralWork(self.integrals[code][1]):
                print "integral with code ", code, " over " , self.integrals[code][0], "not done. Deleting"
                self.integrals.pop(code)
    def addSubstitutions(self, sublist):
        for thing in sublist:
            if isinstance(thing[1],str): s = Symbol(thing[1])
            else : s = thing[1]
            self.sublist.append((thing[0],s))
    
    def printToLatex(self, lengthline = 40, linespage = 60):
        lengthline = int(lengthline)
        texfilename = self.filename.replace(".cxx",".tex")
        f = file(texfilename,"w")
        sym_lines = self.symfunction.as_ordered_terms()
        ll = []
        for line in sym_lines:
            ll.append(len(Ulatex(line)))
        ll.sort()
        ll.reverse()
        
        begintex(f, width = round(0.02*ll[0])) ## estimate the paper width as 0.1 inches per character of the longest line
        f.write("Evaluate: \n")
        do_multline(self.symfunction, f, lengthline,linespage)
        page_break(f)
        for code in self.integrals.keys():
            f.write("Integral " + str(code) + ": \n")
            do_multline(self.integrals[code][1],f, lengthline,linespage)
        f.write("\\end{document}\n")
        #sleep(10)
        #shell("pdflatex " + texfilename)
        
        #return
        
    def writeSubstitutions(self):
        subs_str = ""
        for thing in self.sublist: subs_str += "Double_t " + str(thing[1]) + " = " + strCPP(thing[0]) +";\n"
        return subs_str
            
    def saveCopy(self):
        self.cleanUnresolvedIntegrals()
        f = file(self.filename)
        lines = f.readlines()
        #copyname = self.filename.replace(".cxx","_copy.cxx")
        fcopy = file(self.copyname(), "w")
        search_int_bracket, search_code_bracket, search_eval_bracket = 0, 0, 0
        for line in lines:
            if " This code was autogenerated by RooClassFactory " in line:
                fcopy.write(" * This code was autogenerated by Urania using RooClassFactory               *\n")
                continue
            if len(line) >6:
                if line.split()[0][0:2] != "//" and ("Int_t" in line) and ("::getAnalyticalIntegral(" in line): search_code_bracket = 1
                elif line.split()[0][0:2] != "//" and ("Double_t" in line) and ("::analyticalIntegral(Int_t code, const cha" in line):search_int_bracket = 1
                elif line.split()[0][0:2] != "//" and ("Double_t" in line) and ("::evaluate()" in line):search_eval_bracket = 1
            fcopy.write(line)
            if not line.split():continue
            if line.split()[0] != "{" : continue
            if search_eval_bracket:
                fcopy.write(self.writeSubstitutions())
                #fcopy.write("return " + strCPP(self.func.subs(self.sublist) +";\n")
                search_eval_bracket = 0
            if search_code_bracket:
                for code in self.integrals: fcopy.write(" if ( matchArgs(allVars, analVars, "+ makeVarString(self.integrals[code][0])+" ) )  return "+ str(code)+";\n")
                search_code_bracket = 0
            if search_int_bracket:
                codes = self.integrals.keys()
                codes.sort()
                code = codes[0]
                #fcopy.write("
                fcopy.write(self.writeSubstitutions())
                fcopy.write("if ( code == "+ str(code)+")\n")
                fcopy.write("{\n")
                fcopy.write("Double_t Integral = " + strCPP(self.integrals[code][1].subs(self.sublist)) +";\n")
                fcopy.write("return Integral;\n")
                fcopy.write("}\n")
                for code in codes[1:]:
                    fcopy.write("else if ( code == "+ str(code)+")\n")
                    fcopy.write("{\n")
                    fcopy.write("Double_t Integral = " + strCPP(self.integrals[code][1].subs(self.sublist)) +";\n")
                    fcopy.write("return Integral;\n")
                    fcopy.write("}\n")
                search_int_bracket = 0
                fcopy.write("}")
                fcopy.close()
                break

    def overwrite(self):
        self.saveCopy()
        shell("mv " + self.copyname() + " " + self.filename)

class RooClassGenerator(RooClassEditor):
    def __init__(self, symfunction, variables,name):
        #vs = []
        #for var in variables: vs.append(var)
        RooClassEditor.__init__(self, symfunction, variables,name +".cxx")
        self.var_string = makeVarString(variables)
        self.func_string = strCPP(symfunction)
        self.name = name
        self.subs_used = False
        #self.filename = name
        #self.symfunction = symfunction
        self.variables = variables
    def applySubstitutions(self): self.func_string = strCPP(self.symfunction.subs(self.sublist))
        
    def makePdf(self, integrable = kFALSE, use_subs = 1):
        if use_subs:
            self.subs_used = True
            self.applySubstitutions()
        RooClassFactory.makePdf(self.name,self.var_string,"",self.func_string, integrable)
    def makeFunc(self,integrable = kFALSE): RooClassFactory.makePdf(self.name,self.var_string,"",self.func_string, integrable)
    def move(self, destination_folder = environ["URANIAROOT"] + " /src"):
        shell ("mv " + self.name + " " + destination_folder)
        self.filename = destination_folder + self.name
    def invoke(self): gROOT.ProcessLine(".x " + self.filename + "+")
    

def RooRangeLimits(x):
    xmin = Symbol(str(x) + ".min(rangeName)")
    xmax = Symbol(str(x) + ".max(rangeName)")
    return [xmin, xmax]