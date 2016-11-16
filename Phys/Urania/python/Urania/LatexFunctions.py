from sympy import latex
from sympy.printing.latex import LatexPrinter 
from Urania import histoTex

def begintex(f, width = 5.5, height = 8.5):
    """ adds some lines at the startup to make a tex file
    """
    f.write("\\documentclass{article}\n")
    f.write("\\usepackage[paperwidth="+str(width) +"in, paperheight="+str(height)+ "in]{geometry}\n")
    #f.write("\\documentclass[11pt,a4paper]{article}\n")
    f.write("\\pdfoutput=1\n")
    #f.write("\\usepackage{jheppub}\n")
    f.write("\\usepackage{graphicx}\n") 
    f.write("\\usepackage{amsbsy}\n") 
    f.write("\\usepackage{amsfonts}\n")
    f.write("\\usepackage{amsmath}\n")
    #f.write("\\usepackage{amssymb}]\n")
    f.write("\\usepackage{wasysym}\n")
    f.write("\\usepackage{multirow}\n")
    f.write("\\usepackage{psfrag}\n")
    f.write("\\usepackage{url}\n")
    f.write("\\title{Thing}\n")
    f.write("\\renewcommand{\\thefootnote}{\\arabic{footnote}}\n")
    f.write("\\setcounter{footnote}{0}\n")
    f.write("\\vspace{0.6cm}\n")
    #f.write("\\abstract{.}\n")
    f.write("\\begin{document}\n")
    
def multline_break(f):
    """ breaks a multline and makes new page starting another multline
    """
    end_multline(f)
    page_break(f)
    begin_multline(f)
    
def begin_multline(f): f.write("\\begin{multline}\n")
def end_multline(f): f.write("\\end{multline}\n")

def begin_align(f): f.write("\\begin{align}\n")
def end_align(f): f.write("\\end{align}\n")

def align_break(f):
    """ breaks a multline and makes new page starting another multline
    """
    end_align(f)
    page_break(f)
    begin_align(f)
    
def page_break(f):
    f.write("\\clearpage\n")
    f.write("\\newpage\n")
    
def Ulatex(expr):
    if not "atoms" in dir(expr): return latex(expr)
    things = expr.atoms()
    for thing in things:
        if "useLatexName" in dir(thing):thing.useLatexName()
    out = User_latex(expr)
    for thing in things:
        if "useLatexName" in dir(thing):thing.useFirstName()
    return out

def do_multline(expr, f, lengthline = 40, linespage = 60):
    begin_multline(f)
    ##thing = Ulatex(expr)
##    Nlines = len(thing)*1./lengthline
##    Nlines = int(Nlines)+1
    sym_lines = expr.as_ordered_terms()  
    Nlines = len(sym_lines)
    page = 0
    for i in range(Nlines):
        pageline = i - page*linespage
        if pageline > linespage: 
            multline_break(f)
            page += 1
        f.write(Ulatex(sym_lines[i]) + " \\\\ \n")
    end_multline(f)

class ULatexPrinter(LatexPrinter):
        printmethod = "_ulatex"

        _default_settings = {
            "order": None,
            "mode": "plain",
            "itex": False,
            "fold_frac_powers": False,
            "fold_func_brackets": False,
            "mul_symbol": None,
            "inv_trig_style": "abbreviated",
            "mat_str": "smallmatrix",
            "mat_delim": "(",
            }

        def __init__(self, settings=None):
            LatexPrinter.__init__(self,settings)

        #def _print_conjugate(self, expr, exp=None):
         #   tex = r"{%s}^{*}" % self._print(expr.args[0])

          #  if exp is not None:
           #     return r"%s^{%s}" % (tex, exp)
           # else:
            #    return tex
                                       
                                                                                                                                                                                                                                 
def User_latex(expr, **settings):
    r"""Convert the given expression to LaTeX representation.
    
    Same as latex(expr,settings) but changing the representation
    of complex conjugate from '\overline' to '^*'
    """

    return ULatexPrinter(settings).doprint(expr)
    
def beginTable(f, NColumns):
    f.write("\\begin{table}\n")
    f.write("\\begin{center}\n")
    f.write("\\begin{tabular}{ " + "c" * NColumns + "} \n")
    f.write("\\hline\n")

def fromListToRow(things):
    line = "$" + Ulatex(things[0]) + "$"
    for thing in things[1:]:
        line += "&$" + Ulatex(thing) + "$"
    line += "\\\\ \n"
    return line

def endTable(f):
    f.write("\\end{tabular}\n")
    f.write("\\end{center}\n")
    f.write("\\end{table}\n")

def PDGzed(no): return(round(no, histoTex.nb_digit_PDG(no)))
