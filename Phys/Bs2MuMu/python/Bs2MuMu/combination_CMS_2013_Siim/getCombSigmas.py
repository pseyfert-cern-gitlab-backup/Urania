##############################
# Credits                   #
# Author: Siim Tolk         #
# Date: Autumn 2014         #
# Mail: siim.tolk@cern.ch   #
#############################

#########################################
# The significances for LHCb and CMS fit
# a) Perform the 3 hypothesis fits
# b) Get NLLs
# c) Use the shi square with nDOF to
#    calculate the significanses
##########################################

from combine import *
from getSignificance import *

#Those I just copied from the results
#null_ll = -39415.6842314

#brs_ll = -53805.2028891 #fixBRd
#brd_ll = -53791.5569097 #fixBRs

#Poly OK, checked 23 May 2014
#brs_ll = -53805.4848215
#brd_ll = -53791.5582368
#br_ll = -53810.5234453

#Exponential fit
brs_ll = -53804.7827845
brd_ll = -53790.2210281
br_ll = -53810.2867986


#LHCb only 23May 2014
#brs_ll = -39422.5465049 #brd fix 0
#brd_ll = -39416.8635339 #bs = 0
#br_ll = -39424.0895137



#getSignificance(null_ll, brs_ll, ndf = 1, comment = ' Hyp: BRd fix VS. BRd&BRs fix')
#getSignificance(null_ll, brd_ll, ndf = 1, comment = ' Hyp: BRs fix VS. BRd&BRs fix')
#getSignificance(null_ll, br_ll, ndf = 2, comment = ' Hyp: BRs&BRd fix VS. BRd&BRs fix')

#print '--------------- CHANGE OF HYPO TESTING ------------------'
getSignificance(brs_ll, br_ll, ndf = 1, comment = ' Hyp: BRs&BRd free VS. BRd fix')
getSignificance(brd_ll, br_ll, ndf = 1, comment = ' Hyp: BRs&BRd free VS. BRs fix')



