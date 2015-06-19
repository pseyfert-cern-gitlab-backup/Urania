## better execute it under your ERASMUS_HEAD folder
import datetime
from os import *
today = datetime.datetime.now()
PROJECT = "URANIA"

PATH = environ["HOME"] + "/vol5/"+PROJECT+"/"+PROJECT+"_HEAD/"
def do(package, version):
    f = file(PATH + package +"/cmt/requirements")
    lines = f.readlines()
    f2 = file(PATH + package +"/cmt/requirements2","w")
    for line in lines:
        words = line.split()
        if not words: f2.write(line)
        elif words[0] != "version": f2.write(line)
        else: f2.write ("version           " + version +"\n")
    f2.close()
    system("mv " + PATH + package +"/cmt/requirements2 " +PATH + package +"/cmt/requirements")
    system('svn ci -m "" ' + PATH + package)
    system("tag_package " + package + " " + version)
    return 1
