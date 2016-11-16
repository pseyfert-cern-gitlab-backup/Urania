
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
  
table = '\n\n'
table += '%% Produced by Marco\'s function '+this_function_name+' from  '+__file__+' script on '+datestamp+'.\n'
table +='%\\begin{sidewaystable}[t]\n'
table += '\\begin{table}[t]\n'
table += '\\tabcaption{XX caption for discriminant '+discriminant+' for channel '+CHANNEL+'}\n'
table += '\\begin{center}\n'
table += '\\resizebox {\\textwidth }{!}{%\n'
table += '\\begin{tabular}{cc '+'c'*(len(bdt_binning)-1)+'}\n'
table += '\\hline\n'
table += '\\multicolumn{2}{c}{\\multirow{2}{*}{Invariant mass [\\MeVcc]}} & \\multicolumn{'+str(len(bdt_binning)-1)+'}{c}{BDT \\TTstrut\\BBstrut}  \\\\\n'
table+='\\cline{3-'+str(len(bdt_binning)+1)+'}\n'
tmp_str = '& '
for i in range(len(bdt_binning)-1):
    tmp_str += '& '+str(bdt_binning[i])+' -- '+str(bdt_binning[i+1])+' '
tmp_str   += '\\TTstrut\\BBstrut \\\\\n'
table += tmp_str
table += '\\hline\n'
for i in range(len(mass_binning[CHANNEL])-1):
    comb, misid, sig = [], [], []
    comb_tuple, misid_tuple, sig_tuple = (), (), ()
    
    for bin_bdt in range(len(bdt_binning)-1):
        #chhhheck
        comb.append(get_significant_digit( bkg_dic[i+bin_bdt*(len(m_binning)-1)]['value']
                                          ,bkg_dic[i+bin_bdt*(len(m_binning)-1)]['errHi']
                                          ,bkg_dic[i+bin_bdt*(len(m_binning)-1)]['errLo'] ))
        comb_tuple += ( comb[-1][3], comb[-1][0], comb[-1][3], comb[-1][1], comb[-1][3], comb[-1][2] )
        
        
    #this is the first column of your table            
    table+='\\multirow{%(n_row).i}{*}{%(n1).i -- %(n2).i }\n'%\
            { 'n_row': 1
             ,'n1': m_binning[i  ]
             ,'n2': m_binning[i+1]}
    
    _str = ' & Exp. comb. bkg '+'& $%.*f^{+%.*f}_{-%.*f}$ '*(len(bdt_binning)-1)+' \\TTstrut\\\\\n'
    table+= _str%comb_tuple
    

    table+= '\\hline\n'
        


    
table+= '\\end{tabular}\n\n'
table+= '}\n'
table+= '\\end{center}\n'
table+= '\\label{tab:XXlabel}\n'
table+= '\\end{table}\n'
table+= '%\\end{sidewaystable}\n\n'
    
print table
name_  =  'table_'+CHANNEL+'_'+discriminant+'_'+datestamp+'.tex'
if ShowXfeed :
    name_  =  'table_'+CHANNEL+'_'+discriminant+'_WithCrossPollution_'+datestamp+'.tex'
file = open(name_, 'wb')
file.write(table)
file.close()
