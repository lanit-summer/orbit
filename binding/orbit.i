%module orbit
%{
    #include "../orbfinal/orbfinal/orbit.h"
    #include <vector>
%}

%include "../orbfinal/orbfinal/orbit.h"
%include "std_vector.i"
%include "exception.i"
%exception {
    try {
        $action
    }
    catch (...) {
        SWIG_exception(SWIG_RuntimeError, "unknown exception");
    }
}

namespace std
{
	%template(vector_of_double) vector<double>;
	%template(vector_of_part_flight_plan) vector<PartOfFlightPlan>;
	//%template(vector_of_rotation) vector<Rotation>;
	%template(vector_of_return_values) vector<ReturnValues>;
}
