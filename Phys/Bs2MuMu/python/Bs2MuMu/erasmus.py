## better execute it under your ERASMUS_HEAD folder
import datetime
from os import *
today = datetime.datetime.now()
PROJECT = "ERASMUS"
from time import sleep

def lower(s): return s.lower()
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
    sleep(2)
    system("mv " + PATH + package +"/cmt/requirements2 " +PATH + package +"/cmt/requirements")
    f = file(PATH + package +"/doc/release.notes")
    lines = f.readlines()
    f2 = file(PATH + package +"/doc/release.notes2","w")
    deit = ""
    for line in lines:
        words = line.split()
        words2 = map(lower,words)
        if not words: f2.write(line)
        elif "package" in words2: f2.write(line)
        elif "author" in words2:f2.write(line)
        elif "purpose" in words2:f2.write(line)
        elif "mantainer" in words2:f2.write(line)
        elif "responsible" in words2:f2.write(line)
        elif words[0][0] == "!" and not deit and not "-----" in words[0]:
            deit = str(today.year) + "-" + str(today.month) + "-" + str(today.day)
            f2.write("!============================================== " + version + " " + deit + " ==============================\n")
            f2.write("! " + deit + " Diego Martinez Santos\n")
            f2.write("\t Make version " + version + "\n")
            f2.write(line)
        else: f2.write(line)
    sleep(2)
    system("mv " + PATH + package +"/doc/release.notes2 " +PATH + package +"/doc/release.notes")
    sleep(5)
    system('svn ci -m "" ' + PATH + package)
    system("tag_package " + package + " " + version)
    return 1
