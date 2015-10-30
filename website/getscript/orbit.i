%module orbit
%{
    #include "../orbfinal/orbfinal/orbit.h"
    #include <vector>
%}

%include "exception.i"
%exception {
    try {
        $action
    }
    catch (std::exception &e) {
        SWIG_exception(SWIG_ValueError, e.what());
    }
}

%include "../orbfinal/orbfinal/orbit.h"
%include "std_vector.i"

namespace std
{
	%template(vector_of_part_flight_plan) vector<PartOfFlightPlan>;
	%template(vector_of_return_values) vector<ReturnValues>;
}
