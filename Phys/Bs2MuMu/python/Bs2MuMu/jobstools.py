import os
subfolder = "/stp13/"

DATAPATH = os.environ["BS2MUMUDATACARDSROOT"] +"/python/"+subfolder


def partir(datacards,piecesize=10):
    f=open(DATAPATH+datacards+".opts","r")
    lines=f.readlines()
    startfile = "#pragma print off\nEventSelector.Input   = {\n"
    endfile = "};\n"
    i = 0
    for line in lines:
        # w = line[:5]
        if line[:5] == '"DATA' or line[:8] == '"   DATA':
            break
        i+=1

    fn,j = 0,0
    aux = []
    for line in lines[i:]:
        aux.append(line)
        j+=1
        if j == piecesize:
            out = open(DATAPATH + datacards +"_"+ str(fn) +".opts","w")
            out.write(startfile)
            for i in range(len(aux) - 1 ):
                line = aux[i]
                print line[len(line)-5:] #  \n is just one caracter
               
                out.write(line)
            line = aux[len(aux)-1]
            ddd=line.replace(",","")
            out.write(ddd)
                
            j,aux = 0,[]
            out.write(endfile)
            out.close()
            fn+=1
    f.close()

def partirpy(datacards,piecesize=10):
    f=open(DATAPATH+datacards+".py","r")
    lines=f.readlines()
    startfile = "from Gaudi.Configuration import *\nEventSelector().Input   = [\n"
    endfile = "]\n"
    i = 0
    for line in lines:
        # w = line[:5]
        if line[:5] == '"DATA' or line[:8] == '"   DATA':
            break
        i+=1

    fn,j = 0,0
    aux = []
    for line in lines[i:]:
        aux.append(line)
        j+=1
        if j == piecesize:
            out = open(DATAPATH + datacards +"_"+ str(fn) +".py","w")
            out.write(startfile)
            for i in range(len(aux) - 1 ):
                line = aux[i]
                print line[len(line)-5:] #  \n is just one caracter
               
                out.write(line)
            line = aux[len(aux)-1]
            ddd=line.replace(",","")
            out.write(ddd)
                
            j,aux = 0,[]
            out.write(endfile)
            out.close()
            fn+=1
    f.close()
