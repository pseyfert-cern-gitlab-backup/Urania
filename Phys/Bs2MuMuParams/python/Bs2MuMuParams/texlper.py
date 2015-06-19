#============================================================
# Helper for writing numbers in tex format
from errors import * 
def _rexp(num):
    if num != 0 :
        exp = int(log10(abs(num)))
        m = num / 10**exp
        return m, exp
    else : 
        return 0., 0.

def _printex(m, p, merr, digits):
    form = "%."+str(digits)+"f"
    if p == 0: 
        _s = "$"+form +"\\pm "+form+"$"
        return _s %(m,merr)
    else : 
        _s = "$("+form +"\\pm "+form+") \\cdot 10^{%i}$"
        return _s  %(m,merr,p)

def _printexasym(m, p, merrup, merrdown, digits): 
    form = "%."+str(digits)+"f"
    if ( form %(merrup) ) == (form %(merrdown)):#its symmetric
        return _printex (m, p, merrup, digits)
    else : 
        if p==0:
            _s = "$"+form+"^{+"+form+"}_{-"+form+"}$"
            return _s %(m,merrup, merrdown)
        else:
            _s = "$"+form+"^{+"+form+"}_{-"+form+"}\\cdot 10^{%i}$"
            return _s %(m,merrup, merrdown,p)

            
def tex(x, digits=2):
    if x.__class__ == EVal :
        m, p = _rexp(x.value)
        merr = x.get_error()/ 10**p
        return _printex(m, p, merr, digits)
    elif x.__class__ == EValAsym :
        m, p = _rexp( x.get_value())
        merrup = x.get_error_up()/ 10**p
        merrdown = x.get_error_down()/ 10**p
        return _printexasym(m, p, merrup, merrdown, digits)
