from CondDBUI import CondDB
from PyCool import cool
import re

from bisect import bisect_left, bisect_right
from itertools import izip

class intervalmap(object):
    """
        This class maps a set of intervals to a set of values.
    """

    def __init__(self):
        """
            Initializes an empty intervalmap.
        """
        self._bounds = []
        self._items = []
        self._upperitem = None
        
    def __setitem__(self,_slice,_value):
        """
            Sets an interval mapping.
        """
        assert isinstance(_slice,slice), 'The key must be a slice object'
    
        if _slice.start is None:
            start_point = -1
        else:
            start_point = bisect_left(self._bounds,_slice.start)
        
        if _slice.stop is None:
            end_point = -1
        else:
            end_point = bisect_left(self._bounds,_slice.stop)
        
        if start_point>=0:
            if start_point < len(self._bounds) and self._bounds[start_point]<_slice.start:
                start_point += 1 

            if end_point>=0:        
                self._bounds[start_point:end_point] = [_slice.start,_slice.stop]
                if start_point < len(self._items):
                    self._items[start_point:end_point] = [self._items[start_point],_value]
                else:
                    self._items[start_point:end_point] = [self._upperitem,_value]
            else:
                self._bounds[start_point:] = [_slice.start]
                if start_point < len(self._items):
                    self._items[start_point:] = [self._items[start_point],_value]
                else:
                    self._items[start_point:] = [self._upperitem]
                self._upperitem = _value
        else:
            if end_point>=0:
                self._bounds[:end_point] = [_slice.stop]
                self._items[:end_point] = [_value]
            else:
                self._bounds[:] = []
                self._items[:] = []
                self._upperitem = _value
    
    def __getitem__(self,_point):
        """
            Gets a value from the mapping.
        """
        assert not isinstance(_point,slice), 'The key cannot be a slice object'  
            
        index = bisect_right(self._bounds,_point)
        if index < len(self._bounds):
            return self._items[index]
        else:
            return self._upperitem

    def items(self):
        """
            Returns an iterator with each item being
            ((low_bound,high_bound), value). The items are returned
            in order.
        """
        previous_bound = None
        for b,v in izip(self._bounds,self._items):
            if v is not None:
                yield (previous_bound,b), v
            previous_bound = b
        if self._upperitem is not None:
            yield (previous_bound,None), self._upperitem

    def values(self):
        """
            Returns an iterator with each item being a stored value. The items
            are returned in order.
        """
        for v in self._items:
            if v is not None:
                yield v
        if self._upperitem is not None:
            yield self._upperitem

    def __repr__(self):
        s = []
        for b,v in self.items():
            if v is not None:
                s.append('[%r, %r] => %r'%(
                    b[0],
                    b[1],
                    v
                ))
        return '{'+', '.join(s)+'}'
        

def readItems( db, condition, param, type ) :
    x = intervalmap()
    expr = re.compile('<param name="%s" type="%s">([^<]+)</param>' % (param,type))
    for c in db.getPayloadList(condition,cool.ValidityKeyMin,cool.ValidityKeyMax) :
        d = c[0] # dict
        if 'data' not in d : continue
        t = expr.search(d['data'])
        if not t : continue
        x[ c[1] : c[2] ] = t.group(1)
    return x


db = CondDB('sqlite_file:$SQLITEDBPATH/ONLINE-2012.db/ONLINE', readOnly = True)

CondDBTag = readItems( db, '/Conditions/Online/LHCb/RunInfo/Trigger', 'CondDBTag',    'string' )
DDDBTag   = readItems( db, '/Conditions/Online/LHCb/RunInfo/Trigger', 'DDDBTag',      'string' )
TCK       = readItems( db, '/Conditions/Online/LHCb/RunInfo/Trigger', 'TCKLabel',     'string' )
RunNr     = readItems( db, '/Conditions/Online/LHCb/RunParameters',   'RunNumber',    'int'    )
MooreVersion= readItems( db, '/Conditions/Online/LHCb/RunInfo/Trigger', 'MooreVersion', 'string' )

for (interval,r) in RunNr.items() :
        middle =  (interval[0]+interval[1])/2 
        print '%10s | %10s | %10s | %10s | %10s | %10s | %80s | '%(interval[0],interval[1],r, CondDBTag[ middle ], DDDBTag[middle], MooreVersion[middle], TCK[ middle ])

