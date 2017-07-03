from B2DXFitters import *
from ROOT import *
from optparse import OptionParser
from  os.path import exists
import os, sys, gc

def setEnv():
    config = "../data/settings/set.py"
    last = config.rfind("/")
    directory = config[:last+1]
    configName = config[last+1:]
    p = configName.rfind(".")
    configName = configName[:p]

    import sys
    sys.path.append(directory)

    myconfigfilegrabber = __import__(configName,fromlist=['getconfig']).getconfig
    myconfigfile = myconfigfilegrabber()

    from B2DXFitters.MDFitSettingTranslator import Translator
    mdt = Translator(myconfigfile,"fakeMDSet",False)
    MDSettings = mdt.getConfig()
