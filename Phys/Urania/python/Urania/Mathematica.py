from sympy.printing.printer import Printer
from sympy.printing.precedence import precedence
### From Sympy Tutorial
### Added support for __Add__, __Mult__ and pi
from re import match
from sympy import sympify
import os

class MathematicaPrinter(Printer):
    """Print SymPy's expressions using Mathematica syntax. """
    printmethod = "_mathematica"

    _default_settings = {}

    _translation_table = {
        'asin': 'ArcSin',
        '_': 'u'
    }

    def parenthesize(self, item, level):
        printed = self._print(item)

        if precedence(item) <= level:
            return "(%s)" % printed
        else:
            return printed

    def emptyPrinter(self, expr):
        return str(expr)

    def _print_Pow(self, expr):
        prec = precedence(expr)

        if expr.exp == -1:
            return '1/%s' % (self.parenthesize(expr.base, prec))
        else:
            return '%s^%s' % (self.parenthesize(expr.base, prec),
                              self.parenthesize(expr.exp, prec))


    def _print_Symbol(self,expr):
        split_expr = expr.name.split("_")
        name = ""
        for arg in split_expr:
            name += arg+"underscore"

        return name[:-10]

    def _print_Function(self, expr):
        name = expr.func.__name__
        args = ", ".join([ self._print(arg) for arg in expr.args ])

        if expr.func.nargs is not None:
            try:
                name = self._translation_table[name]
            except KeyError:
                name = name.capitalize()

        return "%s[%s]" % (name, args)
    def _print_Mul(self, expr):
        prec = precedence(expr)
        return "*".join([ self.parenthesize(arg, prec) for arg in expr.args ])
    
    def _print_Add(self, expr):
        prec = precedence(expr)
        return "+".join([ self.parenthesize(arg, prec) for arg in expr.args ])
    
    def _print_Pi(self, expr): return 'Pi'

    def __call__(self, expr): return self.doprint(expr)


## def mathematica(expr, **settings):
##     """Transform an expression to a string with Mathematica syntax. """
##     p = MathematicaPrinter(settings)
##     s = p.doprint(expr)

##     return s



def MathematicaToSympy(s):
    return sympify(TranslateMathematica(s))



def TranslateMathematica(s):
    """Translate Mathematica syntax to SymPy sintax. """
    s = s.strip()

    #Begin rules
    rules = (
        (r"\A(\w+)\[([^\]]+[^\[]*)\]\Z",  # Function call
        lambda m: translateFunction(m.group(1)) + "(" + TranslateMathematica(m.group(2)) + ")" ),

        (r"\((.+)\)\((.+)\)",  # Parenthesized implied multiplication
        lambda m: "(" + TranslateMathematica(m.group(1)) + ")*(" + TranslateMathematica(m.group(2)) + ")" ),

        (r"\((.+)\)\/\((.+)\)",  # Parenthesized division
        lambda m: "(" + TranslateMathematica(m.group(1)) + ")/(" + TranslateMathematica(m.group(2)) + ")" ),

        (r"\A\((.+)\)\Z",  # Parenthesized expression
        lambda m: "(" + TranslateMathematica(m.group(1)) + ")" ),

        (r"\A(.*[\w\.])\((.+)\)\Z",  # Implied multiplication - a(b)
        lambda m: TranslateMathematica(m.group(1)) + "*(" + TranslateMathematica(m.group(2)) + ")" ),

        (r"\A\((.+)\)([\w\.].*)\Z",  # Implied multiplication - (a)b
        lambda m: "(" + TranslateMathematica(m.group(1)) + ")*" + TranslateMathematica(m.group(2)) ),

        (r"\A([\d\.]+)([a-zA-Z].*)\Z",  # Implied multiplicatin - 2a
        lambda m: TranslateMathematica(m.group(1)) + "*" + TranslateMathematica(m.group(2)) ),

        (r"\A([^=]+)(\*\^[\-\+]*)([^\]]+)\Z",  # Powers
         lambda m: TranslateMathematica(m.group(1)) + translateOperator(m.group(2)) + TranslateMathematica(m.group(3)) ),

        (r"\A([^=]+)([\^\-\*/\+=]=?)([^\]]+)\Z",  # Infix operator
        lambda m: TranslateMathematica(m.group(1)) + translateOperator(m.group(2)) + TranslateMathematica(m.group(3)) ),

        (r"(.+)\[([^\]]+[^\[]*)\](\)?)\Z", actionCompFunction))
    #End rules

    for rule, action in rules:
        m = match(rule, s)
        if m:
            return action(m)


    s_ = s.replace("underscore","_")
    s_ = s_.replace("Pi","pi")
    return s_


def actionCompFunction(m):
    
    prev = m.group(1)
    inside = m.group(2)
    after = ""
    if len(m.groups())>2: after = m.group(3)
    
    m2 = match(r"\A([^=]+)([\^\-\*/\+=]=?)([^\]]+)\Z",prev)

    if not m2:
        print prev
        print "Translation from Mathematica failed..."
        return "zero"
    
    return TranslateMathematica(m2.group(1))+translateOperator(m2.group(2))+translateFunction(m2.group(3))+"("+TranslateMathematica(inside)+")"+TranslateMathematica(after)


def translateFunction(s):
    if s.startswith("Arc"):
        return "a" + s[3:]
    return s.lower()


def translateOperator(s):
    dictionary = {'^': '**','*^':'e','*^-':'e-','*^+':'e+'}
    if s in dictionary:
        return dictionary[s]
    return s


def mathematica_script(filename):
    if os.path.exists("/afs/cern.ch/"): path = "/afs/cern.ch/project/parc/math90/bin/math"
    else: path = "math"
    os.system(path + " < " + filename);
