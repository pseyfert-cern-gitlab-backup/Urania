from math import *
def GetKey(list,ki):
    """GetKey(list,key) From a list of dictionaries, this function
    takes the list of dict[i][key]
    """
    out = []
    for thing in list:
        out.append(thing[ki])
    return out

def allvariables(data):
    """Returns all the keys form a dictionary, list of dictionaries,
    and other classes
    """
    if isinstance(data,dict): vars = data.keys()
    elif isinstance(data,list): vars = data[0].keys()
    
    elif "getKeys" in dir(data): vars = data.getKeys()
    
    return vars
    
def changeKey(old,new,listdic):
    """changeKey(oldName, newName, List of Dictionaries)
    """
    out=[]
    kis = listdic[0].keys()
    kis.remove(old)
   
    
    for thing in listdic:
        dic={}
        for key in kis:
            dic[key]=thing[key]
        dic[new]=thing[old]
        out.append(dic)
    return(out)
def getASCII(name):
    f = file(name,"r")
    lines = f.readlines()
    keys = lines[0].split()
    out = {}
    N = len(lines) -1
    n = len(keys)
    rangen = range(n)
    for key in keys:
        out[key] = N*[0.]
    j = 0
    for line in lines[1:]:
        things = line.split()
        nums = map(float,things)
        for i in rangen:
            out[keys[i]][j] = nums[i]
        j += 1

    f.close()
    return out
    
def getEntry(dct, index):
    out = {}
    for key in dct.keys():
        out[key] = dct[key][index]
    return out
def dicToList(dc):
    #out = []
    keys = dc.keys()
    N = len(dc[keys[0]])
    examp = {}
    for key in keys:
        examp[key] = 0.
    out = N*[examp]
    for i in range(N):
        thing = {}
        for key in keys:
            thing[key] = dc[key][i]
        out[i] = thing
    return out
    
## def computeYrms(file,x,y):
##     output = {}
##     datos = getASCII(file)
##     N = len(datos[x])
##     for i in range(N):
##         X = datos[x][i]
##         if X not in output.keys():
##             output[X] = {"m":0.,"RMS":0.,"m2" : 0.}
##     for i in range(N):
##         X = datos[x][i]
##         Y = datos[y][i]
##         output[X]["m"] += Y
##     for key in output.keys():
##         output[key]["m"] = output[key]["m"]*(1./N)
##         output[key]["m2"] = output[key]["m"] * output[key]["m"]

    
##     for i in range(N):
##         X = datos[x][i]
##         Y = datos[y][i]
##         M2 = output[X]["m2"]
##         output[X]["RMS"] += sqrt(M2 - Y*Y)
##     for key in output.keys():
##         output[key]["m"] = output[key]["m"]*(1./N)
        
def rms(datos):
     Ni = 1./len(datos)
     M = 0.
     for entry in datos:
         M += entry
     M = M*Ni
     RMS = 0.
     for entry in datos:
         delta = entry-M
         RMS += delta*delta
     RMS = RMS*Ni
     RMS = RMS 
     RMS = sqrt(RMS)
     return M, RMS
