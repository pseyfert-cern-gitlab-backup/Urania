import array
import numpy
def arr_to_vect(myarray):
    if isinstance(myarray[0],int): return array.array("i",myarray)
    else: return array.array("f",myarray)


def list_to_matrix(mylist):
    return numpy.array(mylist)
