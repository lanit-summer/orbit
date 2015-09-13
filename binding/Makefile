PYINC = /usr/include/python3.4
LIBPATH = ../orbfinal/orbfinal/

_orbit.so: orbit_wrap.o orbit.o
	g++ -shared orbit_wrap.o orbit.o -o $@

orbit_wrap.o: orbit_wrap.cxx $(LIBPATH)orbit.h
	g++ -fPIC orbit_wrap.cxx -g -I$(PYINC) -c -o $@

orbit_wrap.cxx orbit.py: orbit.i $(LIBPATH)orbit.h
	swig -c++ -python orbit.i

orbit.o: $(LIBPATH)orbit.cpp $(LIBPATH)orbit.h
	g++ $(LIBPATH)orbit.cpp -g -c -o orbit.o -fpic
clean:
	rm -f *.so *.o *.pyc core
force:
	rm -f *.so *.o *.pyc core orbit_wrap.cxx orbit.py
