folder = "."
from SomeUtils.alyabar import *
def read9095toy(filename):
    f = file(filename)
    lines = f.readlines()
    if not(len(lines)):
        print "error 1"
        return 0, 0, 0, 0
    for i in range(len(lines)):
        line = lines[i]
        if line.find("C90")== 0: c90 = float(line[4:])
        if line.find("c95")== 0:
            c95 = float(line[4:])
            return c90, c95      
            break


def read_9095all(folder=folder):
    import os
    
    x = os.walk(folder)
    z = x.next()
    l = z[1]
    q = []
    for thing in l:
        if thing.find("LSFJOB") ==0 : q.append(thing)
    c90,c95 = [], []
    for j in q:
       # print j
        a = read9095toy(folder + "/" + j + "/STDOUT")
        if not a:
            print j, " is skrewed up"
            continue
        c90.append(a[0])
        c95.append(a[1])

    return c90, c95
        
   
def read_all(tuplename = "experiments",folder=folder):
    import os
    from BsMuMuPy.pyMyRoot.XTuple import XTuple
    x = os.walk(folder)
    z = x.next()
    l = z[1]
    q = []
    for thing in l:
        if thing.find("LSFJOB") ==0 : q.append(thing)
    print q
    tup = XTuple(folder + "/"+ tuplename,["ns/F","br/F","cls/F","clb/F","alpha/F"])
    w = []
    for j in q:
        ns, cls, clb ,alpha = readfile(folder + "/" + j + "/STDOUT")
        ns = float(ns)
        cls = float(cls)
        clb = float(clb)
        alpha = float(alpha)
        w.append([ns,cls,clb,alpha])
    w.sort()
    for entry in w:
        ns = entry[0]
        cls = entry[1]
        clb = entry[2]
        alpha = entry[3]
        print ns*alpha, cls
        tup.fillItem("ns",ns)
        tup.fillItem("br",ns*alpha)
        tup.fillItem("cls",cls)
        tup.fillItem("clb",clb)
        tup.fillItem("alpha",alpha)
        
        
        tup.fill()
    tup.close()
        
def readfile(filename):
    f = file(filename)
    lines = f.readlines()
    if not(len(lines)):
        print "error 1"
        return 0, 0, 0, 0
    for i in range(len(lines)):
        line = lines[i]
        if line.find("\\" + "\\"+"\\")== 0:
            print i
            break
    if (i+3) > len(lines)-1:
        print "error 2"
        return 0, 0, 0, 0
    
    thing = lines[i+3]
    words = thing.split()
    print words
    ns = words[0]
    cls = words[1]
    clb = words[2]
    alpha = words[3]

    return ns, cls,clb, alpha

