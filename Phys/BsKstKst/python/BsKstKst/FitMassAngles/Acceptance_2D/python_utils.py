import array
import numpy
import ctypes

def arr_to_vect(myarray):
    if isinstance(myarray[0],int): return array.array("i",myarray)
    else: return array.array("f",myarray)



def list_to_matrix(mylist):
    return numpy.array(mylist)


def get_array_lengths(myarray,dimension):
    orders = []
    myarr = myarray
    dim=1
    while True:
        if dim>dimension: break
        orders.append(len(myarr))
        myarr = myarr[0]
        dim+=1

    return orders


def list_to_carray(mylist):
    if type(mylist)==type(list_to_matrix([0.])): myarray = mylist
    else: myarray = list_to_matrix(mylist)
    dimension = myarray.ndim
    if dimension>5:
        print "Cannot handle more than 5 dimensions... Sorry"
        return 1
    dim = 1
    myarr = myarray
    orders = []
    while True:
        if dim>dimension: break
        orders.append(len(myarr))
        myarr = myarr[0]
        dim+=1

    A = ctypes.c_double
    for o in range(dimension):
        order = orders[len(orders)-1-o]
        A = (A*order)

    mycarray = A()

    for i in range(orders[0]):
        if dimension<2:
            mycarray[i] = myarray[i]
            continue
        else:
            for j in range(orders[1]):
                if dimension<3:
                    mycarray[i][j] = myarray[i][j]
                    continue
                else:
                    for l in range(orders[2]):
                        if dimension<4:
                            mycarray[i][j][l] = myarray[i][j][l]
                            continue
                        else:
                            for n in range(orders[3]):
                                if dimension<5:
                                    mycarray[i][j][l][n] = myarray[i][j][l][n]
                                    continue
                                else:
                                    for m in range(orders[4]):
                                        mycarray[i][j][l][n][m] = myarray[i][j][l][n][m]
    

    return mycarray



def array_to_pointer(myarray):
    return ctypes.cast(myarray,ctypes.POINTER(ctypes.c_double))



def list_to_tree(mylist,fname = "myarraytree",tname="T",bname="myarray"):
    if type(mylist)==type(list_to_matrix([0.])): myarray = mylist
    else: myarray = list_to_matrix(mylist)
    dimension = myarray.ndim
    orders = get_array_lengths(myarray,dimension)
    mycarray = list_to_carray(myarray)
    if mycarray==1:
        print "Couldnt transform the list into a C array"
        return 1


    arraytype = bname+"["
    for order in orders:
        arraytype += str(order)+"]["

    arraytype = arraytype[0:-1]+"/D"

    from ROOT import TFile,TTree

    fout = TFile(fname+".root","recreate")
    tree = TTree(tname,tname)
    branch = tree.Branch(bname,mycarray,arraytype)
    tree.Fill()
    tree.Write()
    fout.Close()
    return 1
        

    

        
import sympy as sy

M1 = {}
S1 = {}

def getError( f , M = M1, S = S1):
    """
    Calculates the error of f(x1, ..., xn) from the
    correlation matrix M and the errors in xi.
    f : Sympy expression
    M : correlation matrix dictionary
    ... M = {x1:{x1: c11, x2: c12, ...},x2:{x1: c11, x2: c12, ...},...}
    ... where xi are sympy symbols, and cij the corr. coeffs    
    S : dictionary of xi errors
    ... S = {x1: s1, x2: s2, ...}
    """
    s2 = 0
    for x1 in M.keys():
        dif1 = f.diff(x1) ## df/dx1
        sx1 = S[x1]
        for x2 in M.keys():
            dif2 = f.diff(x2) ## df/dx2
            sx2 = S[x2]
            correlation = M[x1][x2]
            s2 += correlation * dif1*dif2 * sx1*sx2
    return sy.sqrt(s2)
                                        
