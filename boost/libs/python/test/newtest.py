"""
>>> from m1 import *

>>> from m2 import *

>>> n = new_noddy()
>>> s = new_simple()
>>> unwrap_int(n)
42
>>> unwrap_int_ref(n)
42
>>> unwrap_int_const_ref(n)
42
>>> unwrap_simple(s)
'hello, world'
>>> unwrap_simple_ref(s)
'hello, world'
>>> unwrap_simple_const_ref(s)
'hello, world'
>>> unwrap_int(5)
5

Can't get a non-const reference to a built-in integer object
>>> try:
...     unwrap_int_ref(7)
... except: pass
... else: print 'no exception'

>>> unwrap_int_const_ref(9)
9

>>> wrap_int(n)
42

try: wrap_int_ref(n)
... except: pass
... else: print 'no exception'

>>> wrap_int_const_ref(n)
42

>>> unwrap_simple_ref(wrap_simple(s))
'hello, world'

>>> unwrap_simple_ref(wrap_simple_ref(s))
'hello, world'

>>> unwrap_simple_ref(wrap_simple_const_ref(s))
'hello, world'

>>> f(s)
12

>>> unwrap_simple(g(s))
'hello, world'

>>> f(g(s))
12

Create an extension class which wraps "complicated" (init1 and get_n)
are a complicated constructor and member function, respectively.

>>> C = xclass('C', (xinst,), {'__init__': init1, 'get_n': get_n})
>>> c1 = C(s, 99)
>>> c1.get_n()
99
>>> c2 = C(s)
>>> c2.get_n()
0

"""

def run(args = None):

    ### Strange bug somewhere: with Metrowerks: it will crash in
    ### garbage-collection code unless traceback and sre have been
    ### loaded before m1.
    
#     import traceback
#     import sre
#     import m2
#     import m1
    import sys
    import doctest

    if args is not None:
        sys.argv = args
    # import sys
    return doctest.testmod(sys.modules.get(__name__))
    
if __name__ == '__main__':
    print "running..."
    import sys
    sys.exit(run()[0])
