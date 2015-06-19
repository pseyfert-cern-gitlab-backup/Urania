from Urania.Helicity import *
from Urania.LatexFunctions import *
from os import system
def simple_test(Jlist=[0,1],lep=[1,-1], amplitudes = TransAmplitudes, transAng = 0):
    A = doB2VX(Jlist, helicities = lep, transAng = transAng)
    #if transang : A = TransversityAngles(A)
    f = file("urania"+str(max(Jlist))+".tex","w")
    begintex(f)
    pdf_split = DecomposeAmplitudes(A,amplitudes.values())
    begin_multline(f)
    i = 0
    for key in pdf_split.keys():
        if i > 20:
            i = 0
            multline_break(f)
        f.write(latex(key) + "\t" + latex(pdf_split[key]) + "\\\\" + "\n")
        i += 1
    end_multline(f)
    f.write("\\end{document}\n")
    f.close()
    system("pdflatex " + "urania"+str(max(Jlist)))

simple_test(Jlist = [0,1], lep = [1,-1])



#A = doB2VX([0,1], helicities = [1,-1], transAng = 0)

