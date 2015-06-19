
import sys
import ROOT

inname = sys.argv[1]   
tpath = sys.argv[2]   
cname = sys.argv[3]
soutname = sys.argv[4]

print "---------------------  Strip Columns  -------------------" 
print "only columns:		" , cname 
print	"to ntuple:		" , tpath 
print	"in file:		" , inname 
print "output file:		" , soutname 
  
print "-------------------------------------------------------" 

inFile = ROOT.TFile.Open( inname )
if not inFile:
    print "Error opening the specified file is the path you specified correct?"
    sys.exit(1)
  
inTree = inFile.Get(tpath)
if not inTree:
    print "Error opening the specified ntuple- is the path you specified correct?"
    sys.exit(1)

print "setting branch statuses"
  
inTree.SetBranchStatus("*",0)

delimeters=" \t\n;,:"

for delimeter in delimeters:
    if delimeter==',':
        continue
    while delimeter in cname:
        cname=cname.replace(delimeter,',')

while ",," in cname:
    cname=cname.replace(',,',',')

cols=cname.split(',')
for col in cols:
    inTree.SetBranchStatus(col,1)

sout = ROOT.TFile(soutname,"RECREATE")
if not sout:
    print "Error creating the destination ntuple- is the path you specified correct?"
    sys.exit(1)

sout.mkdir(tpath.split('/')[0])
sout.cd(tpath.split('/')[0])	
print "copying ntuple"
soutTree = inTree.CloneTree(-1)

soutTree.Write()	
sout.Write()

print "-------------------------------------------------------" 

print "done."
