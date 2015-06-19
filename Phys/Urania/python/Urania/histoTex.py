
from ROOT import *

def nb_digit(val, nb_sig_digit=2):
    """ compute the number of digit after the point that needs to be
    considered to get 2 significant digits.
    """
    val = abs( val )
    nb_digit = nb_sig_digit-3

    if val == 0. : return 2
    
    while True:
        nb_digit +=1
        if val/10 >=1.:
            return nb_digit
        val *= 10.

def nb_digit_PDG(val):
    """ compute the number of digit after the point that needs to be
    considered according to pdg rules.
    """        
    n_digit = nb_digit( val, 3 )
    #print n_digit
    val_3dig = int( val  *( pow(10, n_digit ))) / float( pow(10, n_digit ) )
    #print val_3dig     
    val_3dig = val_3dig * pow(10, n_digit-3 ) % 1
    #print val_3dig
    
    if   0.100 < val_3dig <= 0.354:
        return 2
    elif 0.354 < val_3dig <= 0.949:
        return 1
    else : return 2



def get_significant_digit(value, err_pos, err_neg, method='2digit'):
    """ return the value and errors and the number of digits
        method can be '2digit' : take 2 significant digits
                      'PDG'    : along the PDG recommendations
    """
    
    if method == '2digit':
        digit_pos = nb_digit( err_pos )
        digit_neg = nb_digit( err_neg )
    if method == 'PDG':
        digit_pos = nb_digit_PDG( err_pos )
        digit_neg = nb_digit_PDG( err_neg )
        
    nb_digit_all = max( digit_pos, digit_neg )
    value   = round( value  , nb_digit_all )
    err_pos = round( err_pos, nb_digit_all )
    err_neg = round( err_neg, nb_digit_all )
    
    return (value, err_pos, err_neg, nb_digit_all)

#the info is in a dictionary a list of dictionaries bkg_dic[bin] = {'value': 43, 'errHi': 1,'errLo':2 }
# in my case the lenght of the list is (len(bdt_binning)-1)*(len(m_binning)-1)
  

def doTex(h, title="\epsilon "):
    hx = h.ProjectionX()
    hy = h.ProjectionY()
    table = '\n\n'
    
    table +='%\\begin{sidewaystable}[t]\n'
    table += '\\begin{table}[t]\n'
    table += '\\tabcaption{}\n'
    table += '\\begin{center}\n'
    table += '\\resizebox {\\textwidth }{!}{%\n'
    table += '\\begin{tabular}{cc '+'c'*h.GetNbinsX()+'}\n'
    table += '\\hline\n'
    table += '\\multicolumn{2}{c}{\\multirow{2}{*}{Invariant mass [\\MeVcc]}} & \\multicolumn{'+str(h.GetNbinsX())+'}{c}{BDT \\TTstrut\\BBstrut}  \\\\\n'
    #table+='\\cline{3-'+str(len(bdt_binning)+1)+'}\n'
    tmp_str = '& '
    
    for i in range(h.GetNbinsX()):
        tmp_str += '& '+str(hx.GetBinLowEdge(i+1))+' -- '+str(hx.GetBinLowEdge(i+2))+' '
    tmp_str += '\\TTstrut\\BBstrut \\\\\n'
    table += tmp_str
    table += '\\hline\n'
    table += '\\hline\n'
    for i in range(h.GetNbinsY()):
        comb = []
        comb_tuple = ()
        table += str(hy.GetBinLowEdge(i+1))+' -- '+str(hy.GetBinLowEdge(i+2))
        for j in range(h.GetNbinsX()):
        
            x = get_significant_digit(h.GetBinContent(j+1,i+1), h.GetBinError(j+1,i+1) ,h.GetBinError(j+1,i+1))
            #comb_tuple += ( comb[-1][3], comb[-1][0], comb[-1][3], comb[-1][1], comb[-1][3], comb[-1][2] )
            table+=  "&$" + str(x[0])  + "\pm" + str(x[1]) +"$"
            
        table+=' \\TTstrut\\\\\n'
        
    #this is the first column of your table            
   ##  table+='\\multirow{%(n_row).i}{*}{%(n1).i -- %(n2).i }\n'%\
##             { 'n_row': 1
##              ,'n1': m_binning[i  ]
##              ,'n2': m_binning[i+1]}
    
    #_str = ' & '+title+''+'& $%.*f \pm %.*f$ '*(h.GetNbinsX())+' \\TTstrut\\\\\n'
   # table+= _str%comb_tuple
    

    table+= '\\hline\n'
    table+= '\\end{tabular}\n\n'
    table+= '}\n'
    table+= '\\end{center}\n'
    table+= '\\label{tab:XXlabel}\n'
    table+= '\\end{table}\n'
    table+= '%\\end{sidewaystable}\n\n'
    
    print table
    name_  =  'table.tex'
   
    file = open(name_, 'wb')
    file.write(table)
    file.close()


def doTex1(h, title="\epsilon ", justn = 0):
    
    table = '\n\n'
    
    table +='%\\begin{sidewaystable}[t]\n'
    table += '\\begin{table}[t]\n'
    table += '\\tabcaption{}\n'
    table += '\\begin{center}\n'
    table += '\\resizebox {\\textwidth }{!}{%\n'
    table += '\\begin{tabular}{|c|c|}\n'
    table += '\\hline\n'
    #table += '\\multicolumn{2}{c}{\\multirow{2}{*}{Invariant mass [\\MeVcc]}} & \\multicolumn{'+str(h.GetNbinsX())+'}{c}{BDT \\TTstrut\\BBstrut}  \\\\\n'
    #table+='\\cline{3-'+str(len(bdt_binning)+1)+'}\n'
    tmp_str = '& '
    if not justn:
        for i in range(h.GetNbinsX()):
            zz = get_significant_digit(h.GetBinContent(i+1), h.GetBinError(i+1),h.GetBinError(i+1))
            tmp_str += "bin " + str(i+1) + '& $'+ str(zz[0]) + " \pm "+ str(zz[1]) +  '$\\TTstrut\\BBstrut \\\\\n'
    else:
        for i in range(h.GetNbinsX()):
            zz = get_significant_digit(h.GetBinContent(i+1), h.GetBinError(i+1),h.GetBinError(i+1))
            print '&  $'+ str(zz[0]) + " \pm "+ str(zz[1])  + "$"
        return
    #tmp_str += '\\TTstrut\\BBstrut \\\\\n'
    table += tmp_str
    table += '\\hline\n'
    table += '\\hline\n'
   

    table+= '\\hline\n'
    table+= '\\end{tabular}\n\n'
    table+= '}\n'
    table+= '\\end{center}\n'
    table+= '\\label{tab:XXlabel}\n'
    table+= '\\end{table}\n'
    
    print table
    name_  =  'table.tex'
   
    file = open(name_, 'wb')
    file.write(table)
    file.close()
