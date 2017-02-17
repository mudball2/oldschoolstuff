/**
* @file EngineMath.cpp
*
* @author Bobak Manavi (BM)
*/

#include "EngineMath.h"

#include <iostream>
using namespace std; 

//////////////////////////////////////////////////////////////////////////
// Common math functions
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// General Utility functions
//////////////////////////////////////////////////////////////////////////

// Are two floating point numbers equal to each other
// Floating Point Error Safe
//
// IN:		a		The first number
//			b		The second number
//
// RETURN: TRUE iff |a-b| < Tolerance
//
// NOTE:	EPSILON is tolerance
bool IsEqual(float a, float b)
{
	// NOTE: Do not modify.
	return fabs(a - b) < EPSILON;
}

// Is a floating point value equal to zero
// Floating Point Error Safe
//
// IN:		a		The number to check
//
// RETURN:	TRUE iff |a| < Tolerance
//
// NOTE:	Tolerance set by EPSILON
bool IsZero(float a)
{
	// NOTE: Do not modify
	return (fabs(a))<EPSILON;
}

// RETURN: MAX of two numbers
float Max(float a, float b)
{
	// NOTE: Do not modify.
	return (a > b) ? a : b;
}

// RETURN: MIN of two numbers
float Min(float a, float b)
{
	// NOTE: Do not modify.
	return (a < b) ? a : b;
}

// RETURN: Converts input to radian measure
float Degrees_To_Radians(float Deg)
{
	// NOTE: Do not modify.
	return Deg * PI / 180.0f;
}

// RETURN: Converts input to degree measure
float Radians_To_Degrees(float Rad)
{
	// NOTE: Do not modify.
	return Rad * 180.0f / PI;
}
////////////////////////////////////////////////////////////////////////
// Linear Algebra Functions Day 1
///////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Vector Functions
//////////////////////////////////////////////////////////////////////////

// Check if two TVECTOR's are equal to each other
//
// IN:		v		First Vector
//			w		Second Vector
//
// RETURN:  True if v==w, False otherwise
//
// NOTE:	Use's all four components
//			Should be floating point error safe.
bool Vector_IsEqual(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	
	
	if(	IsEqual( v.x, w.x ) && IsEqual( v.y, w.y ) && IsEqual( v.z, w.z ) && IsEqual( v.w, w.w ) )
		return true;
		
	return false;
	
}

// ADD two TVECTOR's togother
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v + w
//
// NOTE:	Use's all four components
TVECTOR Vector_Add(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//Make a temp TVECTOR vec for arithmetic (with a for loop?)
	
	TVECTOR vec; 
	for( int i = 0; i < 4; i++)
	{
		vec.e[i] = v.e[i] + w.e[i];
	}
	
	return vec;
}

// SUBTRACT one TVECTOR from another
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v - w
//
// NOTE:	Use's all four components
TVECTOR Vector_Sub(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//Make a temp TVECTOR vec for arithmetic
	TVECTOR vec; 
	for(int i = 0; i < 4; i++)
	{
		vec.e[i] = v.e[i]-w.e[i];
	}

	return vec;
}

// MULTIPLY all four components of a TVECTOR by a scalar
//
// IN:		v		The vector to scale
//			s		The value to scale by
//
// RETURN:  s * v
TVECTOR Vector_Scalar_Multiply(TVECTOR v, float s)
{
	// TODO LAB 1: Replace with your implementation.

	//Make a temp TVECTOR as instructed
	TVECTOR vec;
	for(int i = 0; i < 4; i++)
	{
		vec.e[i] = s * v.e[i];
	}

	return vec;
}

// NEGATE all the components of a TVECTOR
//
// IN:		v		The vector to negate
//
// RETURN:	-1 * v
//
// NOTE:	Use's all four components
TVECTOR Vector_Negate(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.

	//Create a temp TVECTOR
	TVECTOR vec; 
	for(int i = 0; i < 4; i++)
	{
		vec.e[i] = -1 * v.e[i];
	}

	return vec;
}

// Perform a Dot Product on two TVECTOR's
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v (DOT) w
//
// NOTE:	Use's all four components
float Vector_Dot(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	
	return v.x*w.x+v.y*w.y+v.z*w.z+v.w*w.w; 
}

// Perform a Cross Product on two TVECTOR's
//
// IN:		v		First Vector. Left Hand Side
//			w		Second Vector. Right Hand Side
//
// RETURN:  v (CROSS) w
//
// NOTE:	The w-component of each vector is not used.
//			The resultant vector will have a w-component of zero.
TVECTOR Vector_Cross(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//Create a temp TVECTOR vec 
	TVECTOR vec; 
	vec.x = v.y*w.z-v.z*w.y;
	vec.y = v.z*w.x-v.x*w.z;
	vec.z = v.x*w.y-v.y*w.x;
	vec.w = 0; 


	return vec;
}

// Find the squared length of a TVECTOR
//
// IN:		v		The vector to find the squared length of
//
// RETURN:	Squared Length of TVECTOR
//
// NOTE:	Use's all four components
float Vector_LengthSq(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.

	return v.x*v.x+v.y*v.y+v.z*v.z+v.w*v.w;
}

// Find the length of a TVECTOR
//
// IN:		v		The vector to find the length of
//
// RETURN:	Length of TVECTOR
//
// NOTE:	Use's all four components
float Vector_Length(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	return sqrtf(Vector_LengthSq(v));	
}

// Normalize a TVECTOR
//
// IN:		v		The vector to normalize
//
// RETURN:	Normalized version of v
//
// NOTE:	Use's all four components
TVECTOR Vector_Normalize(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	
	//A temp TVECTOR vec
	TVECTOR vec; 

	for(int i = 0; i < 4; i++)
	{
		if( IsZero(Vector_Length(v)))
		{
				v.e[i] = 0.0f;
				return v;
		} else {
			vec.e[i] = v.e[i] / Vector_Length(v); 	
		} // endelseif
	}
	return vec;	
}

// Makes a TVECTOR's w-component normalized
//
// IN:		v		The vector (point object) to homogenise
//
// RETURN:	The homogenised vector (point)
//
// NOTE:	If the w-component of the vector is 0 then the
//			function will return a zero vector with a w-component
//			of 0.
TVECTOR Vector_Homogenise(TVECTOR v)
{
	// TODO LAB 1: Replace with your implementation.
	//A temp TVECTOR vec
	TVECTOR vec; 

	for(int i = 0; i < 4; i++)
	{
		if( IsZero(v.w))
		{
			for( int j = 0; j < 4; j++)
				v.e[j] = 0.0f;
				return v;
		} else {
			vec.e[i] = v.e[i] / v.w; 	
		} // endelseif
	}
	return vec;	
}

// Get a TVECTOR made from the maximun components of two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A maximized vector
//
// NOTE:	Use's all four components
TVECTOR Vector_Maximize(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//A temp TVECTOR vec
	TVECTOR vec; 

	//float for the Max function 
	float res;

	for( int i = 0; i < 4; i++ )
	{
		res = Max(v.e[i], w.e[i]); 
		vec.e[i] = res;
	}
	return vec;
}

// Get a TVECTOR made from the minimum components of two TVECTOR's
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A minimum vector
//
// NOTE:	Use's all four components
TVECTOR Vector_Minimize(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//A temp TVECTOR vec
	TVECTOR vec; 

	//A float for the Min function 
	float res; 

	for( int i = 0; i < 4; i++ )
	{
		res = Min(v.e[i], w.e[i]);
		vec.e[i] = res; 
	}
	return vec;
}

// Get a TVECTOR made from the average of two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:	A vector made from the average of two vectors
//
// NOTE:	Use's all four components

TVECTOR Vector_Average(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//Create temp TVECTOR vec
	TVECTOR vec; 

	vec.x = (v.x+w.x)/2;
	vec.y = (v.y+w.y)/2;
	vec.z = (v.z+w.z)/2;
	vec.w = (v.w+w.w)/2;

	return vec;
}

// Find the angle between two TVECTORs
//
// IN:		v		The first vector
//			w		The second vector
//
// RETURN:  The angle in degrees between the two vectors
//
// NOTE:	If either vector is a zero vector then the return
//			value will be 0.
float Vector_AngleBetween(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	
	//A float variable for returning a value 
	//float angle; 
	int vcount = 0, wcount = 0;
	for(int i = 0; i < 4; i++)
	{
		if(IsZero(v.e[i]))
			vcount++;
		
		if(IsZero(w.e[i]))
			wcount++;
	}

	if( vcount > 3 || wcount > 3 )
		return 0;
	else
		return Radians_To_Degrees(acosf(Vector_Dot(v, w)/(Vector_Length(v)*Vector_Length(w)))); 
	//return Radians_To_Degrees(angle); 

}

// Get the distance one TVECTOR points in the direction of another
// TVECTOR
//
// IN:		v		The first vector
//			w		The direction of the component
//
// RETURN:	The distance that v points in the direction of w.
//
// NOTE:	If w or v is a zero vector then the return value is zero.
float Vector_Component(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.

	//Check if w is a zero vector
	for( int i = 0; i < 4; i++)
	{
		if(IsZero(v.e[i]) && IsZero(w.e[i]))
			return 0; 
		 else  
			return Vector_Dot(v, Vector_Normalize(w)); 	
	} // end loop 
	return Vector_Dot(v, Vector_Normalize(w)); 
}

// Get the TVECTOR that represents v projected on w.
//
// IN:		v		The first vector
//			w		The direction of the projection
//
// RETURN:	The projection of v onto w
//
// NOTE:	If w or v is a zero vector then the return value is zero.
TVECTOR Vector_Project(TVECTOR v, TVECTOR w)
{
	// TODO LAB 1: Replace with your implementation.
	float comp = 0;
	TVECTOR norm = { 0, 0, 0, 0}; 
	for( int i = 0; i < 4; i ++ )
	{
		if (IsZero(w.e[i]) && IsZero(v.e[i]))
		{
			w.e[i] = 0.0f;
			return w;
		} else {

			comp = Vector_Component(v, w);
			norm = Vector_Normalize(w);
			
			return Vector_Scalar_Multiply(norm, comp); 
		}
	}


	return Vector_Scalar_Multiply(norm, comp); 
 
}

////////////////////////////////////////////////////////////////////////
// Functions Lab  #2
///////////////////////////////////////////////////////////////////////


// Get the reflection of v across w
//
// IN:		v		The vector to reflect
//			w		The "axis" to reflect across
//
// RETURN:	v reflected across w
//
// NOTE:	If w is a zero vector then return -v.
TVECTOR Vector_Reflect(TVECTOR v, TVECTOR w)
{
	// TODO LAB 2: Replace with your implementation.
	int count = 0;
	TVECTOR vTemp = {0, 0, 0, 0};
	for( int i = 0; i < 4; i++)
	{
		if(IsZero(w.e[i]))
			count++;
		else
		{
			vTemp = Vector_Project(v, w);
			vTemp = Vector_Scalar_Multiply(vTemp, -2.0f);
			vTemp = Vector_Sub(vTemp, Vector_Negate(v));
		}
	}

	if( count > 3 )
		return Vector_Scalar_Multiply(v, -1.0f);
	else
		return Vector_Negate(vTemp);
}

//////////////////////////////////////////////////////////////////////////
// Matrix Functions
//////////////////////////////////////////////////////////////////////////

// Get a [0] matrix
//
// RETURN: A 0 4x4 matrix
TMATRIX Matrix_Zero(void)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m;
	m._e11 = 0;
	m._e12 = 0;
	m._e13 = 0; 
	m._e21 = 0;
	m._e22 = 0;
	m._e24 = 0;
	m._e31 = 0;
	m._e32 = 0;
	m._e33 = 0;
	m._e34 = 0;
	m._e44 = 0;
	m._e43 = 0;
	m._e42 = 0;
	m._e41 = 0;
	m._e14 = 0;
	m._e23 = 0;


	return m;
}

// Get a [I] matrix
//
// RETURN: A 4x4 Identity matrix
TMATRIX Matrix_Identity(void)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { 1, 0, 0, 0,
				   0, 1, 0, 0,
					0, 0, 1, 0,
					 0, 0, 0, 1};
	return m;
}

// Get a translation matrix
//
// IN:		x		Amount of translation in the x direction
//			y		Amount of translation in the y direction
//			z		Amount of translation in the z direction
//
// RETURN:	The translation matrix
TMATRIX Matrix_Create_Translation(float x, float y, float z)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { 1, 0, 0, x,
					0, 1, 0, y,
					 0, 0, 1, z,
					  0, 0, 0, 1};
	return m;
}

// Create a scale matrix
//
// IN:		x		Amount to scale in the x direction
//			y		Amount to scale in the y direction
//			z		Amount to scale in the z direction
//
// RETURN:	The scale matrix
TMATRIX Matrix_Create_Scale(float x, float y, float z)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { x, 0, 0, 0,
					0, y, 0, 0,
					   0, 0, z, 0,
						 0, 0, 0, 1};
	return m;
}

// Get a rotation matrix for rotation about the x-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A X-Rotation Matrix
TMATRIX Matrix_Create_Rotation_X(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { 1, 0, 0, 0,
					0, cos(Degrees_To_Radians(Deg)), -sin(Degrees_To_Radians(Deg)), 0,
						0, sin(Degrees_To_Radians(Deg)), cos(Degrees_To_Radians(Deg)), 0,
							0, 0, 0, 1};
	return m;
}

// Get a rotation matrix for rotation about the y-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A Y-Rotation Matrix
TMATRIX Matrix_Create_Rotation_Y(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { cos(Degrees_To_Radians(Deg)), 0, sin(Degrees_To_Radians(Deg)), 0,
					0, 1, 0, 0,
						-sin(Degrees_To_Radians(Deg)), 0, cos(Degrees_To_Radians(Deg)), 0,
							0, 0, 0, 1};
	return m;
}

// Get a rotation matrix for rotation about the z-axis
//
// IN:		Deg		Angle to rotate ( Degree measure)
//
// RETURN:	A Z-Rotation Matrix
TMATRIX Matrix_Create_Rotation_Z(float Deg)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX m = { cos(Degrees_To_Radians(Deg)), -sin(Degrees_To_Radians(Deg)), 0, 0,
					sin(Degrees_To_Radians(Deg)), cos(Degrees_To_Radians(Deg)), 0, 0,
						0, 0, 1, 0,
							0, 0, 0, 1};
	return m;
}

// ADD two matrices together
//
// IN:		m		The first matrix
//			n		The second matrix
//
// RETURN: m + n
TMATRIX Matrix_Matrix_Add(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.

	//A temp TMATRIX mat
	TMATRIX mat; 
	for( int i = 0; i < 16; i++)
	{
		mat.e[i] = m.e[i] + n.e[i];
	}
	return mat;
}

// SUBTRACT two matrices
//
// IN:		m		The first matrix (left hand side)
//			n		The second matrix (right hand side)
//
// RETURN: m - n
TMATRIX Matrix_Matrix_Sub(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.

	//Create a temp TMATRIX mat
	TMATRIX mat; 

	for( int i = 0; i < 16; i++)
	{
		mat.e[i] = m.e[i] - n.e[i];
	}

	return mat;
}

// Multiply a matrix by a scalar
//
// IN:		m		The matrix to be scaled (right hand side)
//			s		The value to scale by   (left hand side)
//
// RETURN:	The matrix formed by s*[m]
TMATRIX Matrix_Scalar_Multiply(TMATRIX m, float s)
{
	// TODO LAB 2: Replace with your implementation.

	//A temp TMATRIX mat
	TMATRIX mat; 
	for (int i = 0; i < 16; i++ )
	{
		mat.e[i] = m.e[i]*s;
	}
	return mat;
}

// Negate a matrix
//
// IN:		m		The matrix to negate
//
// RETURN:  The negation of m
TMATRIX Matrix_Negate(TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	//Another temp TMATRI...blah blah blah....
	TMATRIX mat; 

	for( int i = 0; i < 16; i++)
	{
		mat.e[i] = m.e[i]*-1; 
	}
	return mat;
}

// Transpose a matrix
//
// IN:		m		The matrix to transpose
//
// RETURN:	The transpose of m
TMATRIX Matrix_Transpose(TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	TMATRIX temp;
	temp._e11 = m._e11;
	temp._e12 = m._e21;
	temp._e13 = m._e31;
	temp._e14 = m._e41;

	temp._e21 = m._e12;
	temp._e22 = m._e22;
	temp._e23 = m._e32;
	temp._e24 = m._e42;

	temp._e31 = m._e13;
	temp._e32 = m._e23;
	temp._e33 = m._e33;
	temp._e34 = m._e43;

	temp._e41 = m._e14;
	temp._e42 = m._e24;
	temp._e43 = m._e34;
	temp._e44 = m._e44;
	
	
	return temp;
}

// Multipy a matrix and a vector
//
// IN:		m		The matrix (left hand side)
//			v		The vector (right hand side)
//
// RETURN:	[m]*v
TVECTOR Matrix_Vector_Multiply(TMATRIX m, TVECTOR v)
{
	// TODO LAB 2: Replace with your implementation.

	//A temp TVECTOR
	TVECTOR vec;
	
	vec.x = m._e11*v.x+m._e12*v.y+m._e13*v.z+m._e14*v.w;
	vec.y = m._e21*v.x+m._e22*v.y+m._e23*v.z+m._e24*v.w;
	vec.z = m._e31*v.x+m._e32*v.y+m._e33*v.z+m._e34*v.w;
	vec.w = m._e41*v.x+m._e42*v.y+m._e43*v.z+m._e44*v.w; 
	
	
	return vec;
}

// Multipy a vector and a matrix
//
// IN:		v		The vector ( left hand side)
//			m		The matrix (right hand side)
//
// RETURN:	v*[m]
TVECTOR Vector_Matrix_Multiply(TVECTOR v, TMATRIX m)
{
	// TODO LAB 2: Replace with your implementation.
	
	//A temp TVECTOR
	TVECTOR vec;
	
	vec.x = m._e11*v.x+m._e21*v.y+m._e31*v.z+m._e41*v.w;
	vec.y = m._e12*v.x+m._e22*v.y+m._e32*v.z+m._e42*v.w;
	vec.z = m._e13*v.x+m._e23*v.y+m._e33*v.z+m._e43*v.w;
	vec.w = m._e14*v.x+m._e24*v.y+m._e34*v.z+m._e44*v.w; 
	
	
	return vec;

	return vec;
}
// Multiply a matrix by a matrix
//
// IN:		m		First Matrix (left hand side)
//			n		Second Matrix (right hand side)
//
// RETURN:	[m]*[n]
TMATRIX Matrix_Matrix_Multiply(TMATRIX m, TMATRIX n)
{
	// TODO LAB 2: Replace with your implementation.

	//Temp TMATRIX mat
	TMATRIX mat = { m._e11*n._e11+m._e12*n._e21+m._e13*n._e31+m._e14*n._e41 , m._e11*n._e12+m._e12*n._e22+m._e13*n._e32+m._e14*n._e42 , m._e11*n._e13+m._e12*n._e23+m._e13*n._e33+m._e14*n._e43 , m._e11*n._e14+m._e12*n._e24+m._e13*n._e34+m._e14*n._e44 , 
					m._e21*n._e11+m._e22*n._e21+m._e23*n._e31+m._e24*n._e41 , m._e21*n._e12+m._e22*n._e22+m._e23*n._e32+m._e24*n._e42 , m._e21*n._e13+m._e22*n._e23+m._e23*n._e33+m._e24*n._e43 , m._e21*n._e14+m._e22*n._e24+m._e23*n._e34+m._e24*n._e44 ,
					m._e31*n._e11+m._e32*n._e21+m._e33*n._e31+m._e34*n._e41 , m._e31*n._e12+m._e32*n._e22+m._e33*n._e32+m._e34*n._e42 , m._e31*n._e13+m._e32*n._e23+m._e33*n._e33+m._e34*n._e43 , m._e31*n._e14+m._e32*n._e24+m._e33*n._e34+m._e34*n._e44 ,
					m._e41*n._e11+m._e42*n._e21+m._e43*n._e31+m._e44*n._e41 , m._e41*n._e12+m._e42*n._e22+m._e43*n._e32+m._e44*n._e42 , m._e41*n._e13+m._e42*n._e23+m._e43*n._e33+m._e44*n._e43 , m._e41*n._e14+m._e42*n._e24+m._e43*n._e34+m._e44*n._e44};
	return mat;
}

////////////////////////////////////////////////////////////////////////
// Matrix Functions Lab # 3
///////////////////////////////////////////////////////////////////////

// HELPER FUNCTION  *** NOT GRADED, ONLY SUGGESTED ***
// USE THIS FUNCTION TO FIND THE DETERMINANT OF A 3*3
// MATRIX. IT CAN BE USED IN THE MATRIX DETERMINANT
// AND MATRIX INVERSE FUNCTIONS BELOW
// 
// RETURN:	The determinant of a 3x3 matrix
float Matrix_Determinant(float e_11,float e_12,float e_13,
						 float e_21,float e_22,float e_23,
						 float e_31,float e_32,float e_33)
{
	return e_11*(e_22*e_33 - e_32*e_23)-e_12*(e_21*e_33-e_31*e_23)+e_13*(e_21*e_32-e_31*e_22);
}

// Get the determinant of a matrix
//
// IN:		m		The ONE!
//
// RETURN:	It's deterinant
float Matrix_Determinant(TMATRIX m)
{
	// TODO LAB 3: Replace with your implementation.
	float fDet;

	fDet = m._e11 * Matrix_Determinant(m._e22, m._e23, m._e24,
									   m._e32, m._e33, m._e34,
									   m._e42, m._e43, m._e44);

	fDet -= m._e12 * Matrix_Determinant(m._e21, m._e23, m._e24,
									    m._e31, m._e33, m._e34,
									    m._e41, m._e43, m._e44);

	fDet += m._e13 * Matrix_Determinant(m._e21, m._e22, m._e24,
									    m._e31, m._e32, m._e34,
									    m._e41, m._e42, m._e44);

	fDet -= m._e14 * Matrix_Determinant(m._e21, m._e22, m._e23,
									    m._e31, m._e32, m._e33,
									    m._e41, m._e42, m._e43);

	return fDet;
}

// Get the inverse of a matrix
//
// IN:		m		The matrix to inverse
//
// RETURN:	The Inverse of [m]
//
// NOTE: Returns the matrix itself if m is not invertable.
TMATRIX Matrix_Inverse(TMATRIX m)
{
	// TODO LAB 3: Replace with your implementation.
	TMATRIX matInv;
	
					// First set
	matInv._e11	=	 Matrix_Determinant( m._e22, m._e23, m._e24,
											 m._e32, m._e33, m._e34,
											 m._e42, m._e43, m._e44);

	matInv._e12	=	-Matrix_Determinant( m._e21, m._e23, m._e24,
											 m._e31, m._e33, m._e34,
											 m._e41, m._e43, m._e44);

	matInv._e13	=	 Matrix_Determinant( m._e21, m._e22, m._e24,
											 m._e31, m._e32, m._e34,
											 m._e41, m._e42, m._e44);
	
	matInv._e14	=	-Matrix_Determinant( m._e21, m._e22, m._e23,
											 m._e31, m._e32, m._e33,
											 m._e41, m._e42, m._e43);


					// Second Set
	matInv._e21	=	-Matrix_Determinant( m._e12, m._e13, m._e14,
											 m._e32, m._e33, m._e34,
											 m._e42, m._e43, m._e44);

	matInv._e22	=	 Matrix_Determinant( m._e11, m._e13, m._e14,
											 m._e31, m._e33, m._e34,
											 m._e41, m._e43, m._e44);

	matInv._e23	=	-Matrix_Determinant( m._e11, m._e12, m._e14,
											 m._e31, m._e32, m._e34,
											 m._e41, m._e42, m._e44);

	matInv._e24	=	 Matrix_Determinant( m._e11, m._e12, m._e13,
											 m._e31, m._e32, m._e33,
											 m._e41, m._e42, m._e43);


					// Third Set
	matInv._e31	=	 Matrix_Determinant( m._e12, m._e13, m._e14,
											 m._e22, m._e23, m._e24,
											 m._e42, m._e43, m._e44);

	matInv._e32	=	-Matrix_Determinant( m._e11, m._e13, m._e14,
											 m._e21, m._e23, m._e24,
											 m._e41, m._e43, m._e44);

	matInv._e33	=	 Matrix_Determinant( m._e11, m._e12, m._e14,
											 m._e21, m._e22, m._e24,
											 m._e41, m._e42, m._e44);

	matInv._e34	=	-Matrix_Determinant( m._e11, m._e12, m._e13,
											 m._e21, m._e22, m._e23,
											 m._e41, m._e42, m._e43);


					// Fourth Set
	matInv._e41	=	-Matrix_Determinant( m._e12, m._e13, m._e14,
											 m._e22, m._e23, m._e24,
											 m._e32, m._e33, m._e34);

	matInv._e42	=	 Matrix_Determinant( m._e11, m._e13, m._e14,
											 m._e21, m._e23, m._e24,
											 m._e31, m._e33, m._e34);

	matInv._e43	=	-Matrix_Determinant( m._e11, m._e12, m._e14,
											 m._e21, m._e22, m._e24,
											 m._e31, m._e32, m._e34);

	matInv._e44	=	 Matrix_Determinant( m._e11, m._e12, m._e13,
											 m._e21, m._e22, m._e23,
											 m._e31, m._e32, m._e33); 

	matInv = Matrix_Transpose(matInv);
	if( Matrix_Determinant(matInv) != 0 )
	{
		return Matrix_Scalar_Multiply(matInv, (1 / Matrix_Determinant(m)));
	}
	else
	{
		return m;
	}
}

