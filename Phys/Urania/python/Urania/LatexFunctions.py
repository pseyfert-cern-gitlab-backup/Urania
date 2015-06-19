def begintex(f):
    """ adds some lines at the startup to make a tex file
    """
    f.write("\\documentclass[11pt,a4paper]{article}\n")
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

def page_break(f):
    f.write("\\clearpage\n")
    f.write("\\newpage\n")
    
