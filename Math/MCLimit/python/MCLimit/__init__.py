"""
"""
import os
print "importing from ", os.path.abspath(__path__[0])
from GaudiPython.Bindings import gbl
csm_template = gbl.csm_template
csm_model = gbl.csm_model
mclimit_csm = gbl.mclimit_csm
csm = gbl.csm
