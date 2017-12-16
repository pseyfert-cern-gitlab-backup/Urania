from alyabar import vector
import string


def select(event,key="ptV",number=2,mode="M"):
    if event==[]: return event 
    list=[]
    if event[len(event)-1].has_key(key):
        for thing in event:
            list.append([thing[key],thing])
        list.sort()
        if mode=="M": list.reverse()
        x=min(len(list),number)
        output=[]
        for i in range(x):
            output.append(list[i][1])
        
        return output
    
    if key=="ptV":
        for thing in event:
            thing["ptV"]=thing["pt1"]+thing["pt2"]
        return select(event,"ptV",number,mode)
    print "I don't know " + key + ".Please,construct it"
    return None


def selectionStep(channel,key="ptV",number=2,mode="M"):
    output=[]
    for event in channel:
        ev=select(event,key,number,mode)
        if ev!=[]: output.append(ev)
    return output



def agrupateInEvents(list):
    """agrupateInvents( list of dictionaries )
    Looks for the key 'evt' and agupates all the entries
    with the same value of 'evt' in lists. The output
    is a list of lists with all the entries from the sam event
    """
    print "making event-structure"
    if list == []: return list
    events=[]
    if 'has_key' in dir(list[0]):
        if  list[0].has_key("evt"):
            evt=-1
            n=-1
            for thing in list:
                if thing["evt"]!=evt:
                    evt=thing["evt"]
                    n=n+1
                    events.append([])
                events[n].append(thing)
        else:
            
            print "Impossible. 'evt' key not found"
            print "<ERROR>"
            return list

    return events

def desagrupate(events):
    """desagrupate( list of events )
    The inverse of 'agrupteInEvents'
    """
    print "breaking event structure"
    list=[]
    for event in events:
        for thing in event:
           list.append(thing)
    return list

def vectorShape(DIC):
    """vectorShape( dictionary or list of dictionaries, or list of lists of ..
    dictionaries)
    Agrupates entries in 3D vectors, looking for keys like 'k1', 'k2', 'k3'
    or 'kx', 'ky', 'kz'
    """
    
    if 'has_key' in dir(DIC):
        dic2={}
        dickeys=DIC.keys()
        for key in dickeys:
            if key[len(key)-1]=='3':
                a=string.replace(key,'3','1')
                b=string.replace(key,'3','2')
                c=key
                
                if (b in dickeys) and (a in dickeys):
                    newkey=string.replace(c,'3','')
                    if newkey=='':
                        newkey="pos"
                    while(newkey in dickeys):
                        newkey = newkey + "Vec"
                    dic2[newkey]=vector(DIC[a],DIC[b],DIC[c])
                    dickeys.remove(a)
                    dickeys.remove(b)
                    dickeys.remove(c)
            if key[len(key)-1]=='z':
                a=string.replace(key,'z','x')
                b=string.replace(key,'z','y')
                c=key
                
                if (b in dickeys) and (a in dickeys):
                    newkey=string.replace(c,'z','')
                    if newkey=='':
                        newkey="pos"
                    while(newkey in dickeys):
                        newkey = newkey + "Vec"
                    
                    dic2[newkey]=vector(DIC[a],DIC[b],DIC[c])
                    dickeys.remove(a)
                    dickeys.remove(b)
                    dickeys.remove(c)
                                
        for key in dickeys:
            dic2[key]=DIC[key]
                        
        return dic2

    elif 'append' in dir(DIC):
        #print "bringing vector-shape to the list"
        list=[]
        for thing in DIC:
            list.append(vectorShape(thing))
        return list



def rAddkey(key,list,keylist,function):
    """
    """
    if list==[]:return list
    if 'has_key' in dir(list[0]):
        if len(keylist)==1:
            for thing in list:
                thing[key]=function(thing[keylist[0]])
                
        if len(keylist)==2:
            for thing in list:
                thing[key]=function(thing[keylist[0]],thing[keylist[1]])
                
        if len(keylist)==3:
            for thing in list:
                thing[key]=function(thing[keylist[0]],thing[keylist[1]],thing[keylist[2]])
                
    else:
        
        list=desagrupate(list)
        rAddkey(key,list,keylist,function)
        list=agrupateInEvents(list)
    return "Operation addkey " + key + " finished"


