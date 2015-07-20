PYINC = /usr/include/python3.4

_orbit.so: orbit_wrap.o orbit.o
	g++ -shared orbit_wrap.o orbit.o -o $@

orbit_wrap.o: orbit_wrap.cxx orbit.h
	g++ -fPIC orbit_wrap.cxx -g -I$(PYINC) -c -o $@

orbit_wrap.cxx orbit.py: orbit.i orbit.h
	swig -c++ -python orbit.i

orbit.o: orbit.cpp orbit.h
	g++ orbit.cpp -g -c -o orbit.o -fpic
clean:
	rm -f *.so *.o *.pyc core
force:
	rm -f *.so *.o *.pyc core orbit_wrap.cxx orbit.py
