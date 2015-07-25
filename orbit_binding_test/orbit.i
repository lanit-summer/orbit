%module orbit
%{
    #include "orbit.h"
    #include <vector>
%}

%include "orbit.h"
%include "std_vector.i"

namespace std
{
	%template(vector_of_double) vector<double>;
	%template(vector_of_part_flight_plan) vector<PartOfFlightPlan>;
	//%template(vector_of_rotation) vector<Rotation>;
	%template(vector_of_position) vector<Position>;
}