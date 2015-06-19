"""
"""
import os
print "importing from ", os.path.abspath(__path__[0])

def AccesPackage(name):
    NAME = name.upper()+"ROOT"
    if NAME not in os.environ.keys():
        print "Unknown package"
        return 1
    path1 = os.environ[NAME] + "/python/"
    path2 = os.environ[NAME] + "/python/" + name
    if os.path.exists(path1):
        print "Adding ", path1, " to pythonpath"
        os.sys.path.append( path1 )
    else:
        print path1," does not exist"
    if os.path.exists(path1):
        print "Adding ", path2, " to pythonpath"
        os.sys.path.append( path2 )
    else:
        print path1," does not exist"

AccessPackage = AccesPackage

def collect_packages(req):
    lines = req.readlines()
    packs = []
    #hats = []
    for line in lines:
        if line.find("use"): continue
        words = line.split()
        packs.append([words[1],words[3]]) ## [Package Name, Hat ]
        
    return packs

def microsetup():
    ## try to find UraniaSys requirements file
    this = os.path.abspath(__path__[0])
    urania = os.path.abspath(__path__[0]) + "/../../../.."
    req = file(urania +"/UraniaSys/cmt/requirements")
    packs = collect_packages(req)
    raised_flag = 0
    for pack in packs:
        NAME = pack[0].upper() + "ROOT"
        if NAME not in os.environ.keys():
            if not raised_flag:
                print "Didn't you run SetupProject? ... Finding package locations"
                print "Call AccesPackage(<packagename>) to manually add a package to the pythonpath"
                raised_flag = 1
            os.environ[NAME] = urania + "/" +pack[1] + "/" + pack[0]

    
    
