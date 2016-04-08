%module orbit
%{
    #include "OrbitSimulator.h"
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

%include "OrbitSimulator.h"
%include "std_vector.i"
%include "vec.cpp"
%include "quaternion.cpp"
namespace std
{
	%template(vector_of_part_flight_plan) vector<PartOfFlightPlan>;
	%template(vector_of_return_values) vector<ReturnValues>;
}
