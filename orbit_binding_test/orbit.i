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
	%template(vector_of_rotation) vector<Rotation>;
	%template(vector_of_position) vector<Position>;
}
/*
%pythoncode 
%{
	def numberVectorFromList(list_of_Numbers):
		v = numberVector(len(list_of_Numbers))
		for i in range(v.size()):
			v[i] = list_of_Numbers[i]
		return v
%}
*/
