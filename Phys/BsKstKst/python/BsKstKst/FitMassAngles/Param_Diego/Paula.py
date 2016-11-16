from Urania.Helicity import *
#AccessPackage("Urania")
#import Helicity as H
from Urania.SympyBasic import *
from Urania.LatexFunctions import *
from os import *

A0 = Symbol("A_0")
Apa = Symbol("A_{||}")
Ape = Symbol("A_{pe}")
AS = Symbol("A_{SS}")
ASplus = Symbol("A_S^{+}")
ASminus = Symbol("A_S^{-}")


def simple_test(Jlist1 = [1], Jlist2 = []):
    if not Jlist2 : Jlist2 = Jlist1
    Jlist = Jlist1+Jlist2
    A = doB2XhhYhh(Jlist1,Jlist2)
    A = A.subs([(H["Ja1_Jb1_0"], A0), (H["Ja1_Jb1_1"],1/Sqrt(2)*( Apa + Ape)),(H["Ja1_Jb1_-1"],1/Sqrt(2)*( Apa-Ape))]) ### De momentosolo te sustituyo los del PP-wave.... 
    if 0 in Jlist: A = A.subs([(H["Ja0_Jb0_0"], AS), (H["Ja1_Jb0_0"],1/Sqrt(2)*( ASplus + ASminus)),(H["Ja0_Jb1_0"],1/Sqrt(2)*( ASplus-ASminus))]) ### Y las Ss, SP
    A = A.expand()/9

    #A = doB2VX(Jlist, helicities = lep, transAng = transAng)
    #if transang : A = TransversityAngles(A)
    f = file("urania"+str(max(Jlist))+".tex","w")
    begintex(f)
    pdf_split = DecomposeAmplitudes(A,[A0,Apa,Ape,AS,ASplus,ASminus] + H.values())
    begin_multline(f)
    i = 0
    for key in pdf_split.keys():
        if i > 20:
            i = 0
            multline_break(f)
        if pdf_split[key]: f.write(latex(key) + "\t" + latex(pdf_split[key]) + "\\\\" + "\n")
        i += 1
    end_multline(f)
    f.write("\\end{document}\n")
    f.close()
    system("pdflatex " + "urania"+str(max(Jlist)))

simple_test(range(3))
