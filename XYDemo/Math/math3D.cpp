// Math3d.h
// Math3D Library, version 0.95

/*
 MIT License
 Copyright (c) 2007-2017 Richard S. Wright Jr.
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 Contact GitHub API Training Shop Blog About
 */

// Header file for the Math3D library. The C-Runtime has math.h, this file and the
// accompanying math3d.cpp are meant to suppliment math.h by adding geometry/math routines
// useful for graphics, simulation, and physics applications (3D stuff).
// This library is meant to be useful on Win32, Mac OS X, various Linux/Unix distros,
// and mobile platforms. Although designed with OpenGL in mind, there are no OpenGL
// dependencies. Other than standard math routines, the only other outside routine
// used is memcpy (for faster copying of vector arrays).
// Richard S. Wright Jr.

#ifndef _MATH3D_LIBRARY__
#define _MATH3D_LIBRARY__

#include <math.h>
#include <string.h>    // Memcpy lives here on most systems

///////////////////////////////////////////////////////////////////////////////
// Data structures and containers
// Much thought went into how these are declared. Many libraries declare these
// as structures with x, y, z data members. However structure alignment issues
// could limit the portability of code based on such structures, or the binary
// compatibility of data files (more likely) that contain such structures across
// compilers/platforms. Arrays are always tightly packed, and are more efficient
// for moving blocks of data around (usually).
// Sigh... yes, I probably should use GLfloat, etc. But that requires that we
// always include OpenGL. Since this library is also useful for non-graphical
// applications, I shall risk the wrath of the portability gods...

typedef float    M3DVector2f[2];        // 3D points = 3D Vectors, but we need a
typedef double    M3DVector2d[2];        // 2D representations sometimes... (x,y) order

typedef float    M3DVector3f[3];        // Vector of three floats (x, y, z)
typedef double    M3DVector3d[3];        // Vector of three doubles (x, y, z)

typedef float    M3DVector4f[4];        // Lesser used... Do we really need these?
typedef double    M3DVector4d[4];        // Yes, occasionaly we do need a trailing w component



// 3x3 matrix - column major. X vector is 0, 1, 2, etc.
//        0    3    6
//        1    4    7
//        2    5    8
typedef float    M3DMatrix33f[9];        // A 3 x 3 matrix, column major (floats) - OpenGL Style
typedef double    M3DMatrix33d[9];        // A 3 x 3 matrix, column major (doubles) - OpenGL Style


// 4x4 matrix - column major. X vector is 0, 1, 2, etc.
//    0    4    8    12
//    1    5    9    13
//    2    6    10    14
//    3    7    11    15
typedef float M3DMatrix44f[16];        // A 4 X 4 matrix, column major (floats) - OpenGL style
typedef double M3DMatrix44d[16];    // A 4 x 4 matrix, column major (doubles) - OpenGL style


///////////////////////////////////////////////////////////////////////////////
// Useful constants
#define M3D_PI (3.14159265358979323846)
#define M3D_2PI (2.0 * M3D_PI)
#define M3D_PI_DIV_180 (0.017453292519943296)
#define M3D_INV_PI_DIV_180 (57.2957795130823229)


///////////////////////////////////////////////////////////////////////////////
// Useful shortcuts and macros
// Radians are king... but we need a way to swap back and forth for programmers and presentation.
// Leaving these as Macros instead of inline functions, causes constants
// to be evaluated at compile time instead of run time, e.g. m3dDegToRad(90.0)
#define m3dDegToRad(x)    ((x)*M3D_PI_DIV_180)
#define m3dRadToDeg(x)    ((x)*M3D_INV_PI_DIV_180)

// Hour angles
#define m3dHrToDeg(x)    ((x) * (1.0 * 15.0))
#define m3dHrToRad(x)    m3dDegToRad(m3dHrToDeg(x))

#define m3dDegToHr(x)    ((x) / 15.0))
#define m3dRadToHr(x)    m3dDegToHr(m3dRadToDeg(x))


// Returns the same number if it is a power of
// two. Returns a larger integer if it is not a
// power of two. The larger integer is the next
// highest power of two.
inline unsigned int m3dIsPOW2(unsigned int iValue)
{
    unsigned int nPow2 = 1;
    
    while(iValue > nPow2)
        nPow2 = (nPow2 << 1);
    
    return nPow2;
}


///////////////////////////////////////////////////////////////////////////////
// Inline accessor functions (Macros) for people who just can't count to 3 or 4
// Really... you should learn to count before you learn to program ;-)
// 0 = x
// 1 = y
// 2 = z
// 3 = w
#define    m3dGetVectorX(v) (v[0])
#define m3dGetVectorY(v) (v[1])
#define m3dGetVectorZ(v) (v[2])
#define m3dGetVectorW(v) (v[3])

#define m3dSetVectorX(v, x)    ((v)[0] = (x))
#define m3dSetVectorY(v, y)    ((v)[1] = (y))
#define m3dSetVectorZ(v, z)    ((v)[2] = (z))
#define m3dSetVectorW(v, w)    ((v)[3] = (w))

///////////////////////////////////////////////////////////////////////////////
// Inline vector functions
// Load Vector with (x, y, z, w).
inline void m3dLoadVector2(M3DVector2f v, const float x, const float y)
{ v[0] = x; v[1] = y; }
inline void m3dLoadVector2(M3DVector2d v, const float x, const float y)
{ v[0] = x; v[1] = y; }
inline void m3dLoadVector3(M3DVector3f v, const float x, const float y, const float z)
{ v[0] = x; v[1] = y; v[2] = z; }
inline void m3dLoadVector3(M3DVector3d v, const double x, const double y, const double z)
{ v[0] = x; v[1] = y; v[2] = z; }
inline void m3dLoadVector4(M3DVector4f v, const float x, const float y, const float z, const float w)
{ v[0] = x; v[1] = y; v[2] = z; v[3] = w;}
inline void m3dLoadVector4(M3DVector4d v, const double x, const double y, const double z, const double w)
{ v[0] = x; v[1] = y; v[2] = z; v[3] = w;}


////////////////////////////////////////////////////////////////////////////////
// Copy vector src into vector dst
inline void    m3dCopyVector2(M3DVector2f dst, const M3DVector2f src) { memcpy(dst, src, sizeof(M3DVector2f)); }
inline void    m3dCopyVector2(M3DVector2d dst, const M3DVector2d src) { memcpy(dst, src, sizeof(M3DVector2d)); }

inline void    m3dCopyVector3(M3DVector3f dst, const M3DVector3f src) { memcpy(dst, src, sizeof(M3DVector3f)); }
inline void    m3dCopyVector3(M3DVector3d dst, const M3DVector3d src) { memcpy(dst, src, sizeof(M3DVector3d)); }

inline void    m3dCopyVector4(M3DVector4f dst, const M3DVector4f src) { memcpy(dst, src, sizeof(M3DVector4f)); }
inline void    m3dCopyVector4(M3DVector4d dst, const M3DVector4d src) { memcpy(dst, src, sizeof(M3DVector4d)); }


////////////////////////////////////////////////////////////////////////////////
// Add Vectors (r, a, b) r = a + b
inline void m3dAddVectors2(M3DVector2f r, const M3DVector2f a, const M3DVector2f b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1];  }
inline void m3dAddVectors2(M3DVector2d r, const M3DVector2d a, const M3DVector2d b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1];  }

inline void m3dAddVectors3(M3DVector3f r, const M3DVector3f a, const M3DVector3f b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }
inline void m3dAddVectors3(M3DVector3d r, const M3DVector3d a, const M3DVector3d b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; }

inline void m3dAddVectors4(M3DVector4f r, const M3DVector4f a, const M3DVector4f b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }
inline void m3dAddVectors4(M3DVector4d r, const M3DVector4d a, const M3DVector4d b)
{ r[0] = a[0] + b[0];    r[1] = a[1] + b[1]; r[2] = a[2] + b[2]; r[3] = a[3] + b[3]; }

////////////////////////////////////////////////////////////////////////////////
// Subtract Vectors (r, a, b) r = a - b
inline void m3dSubtractVectors2(M3DVector2f r, const M3DVector2f a, const M3DVector2f b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1];  }
inline void m3dSubtractVectors2(M3DVector2d r, const M3DVector2d a, const M3DVector2d b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; }

inline void m3dSubtractVectors3(M3DVector3f r, const M3DVector3f a, const M3DVector3f b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }
inline void m3dSubtractVectors3(M3DVector3d r, const M3DVector3d a, const M3DVector3d b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; }

inline void m3dSubtractVectors4(M3DVector4f r, const M3DVector4f a, const M3DVector4f b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; }
inline void m3dSubtractVectors4(M3DVector4d r, const M3DVector4d a, const M3DVector4d b)
{ r[0] = a[0] - b[0]; r[1] = a[1] - b[1]; r[2] = a[2] - b[2]; r[3] = a[3] - b[3]; }



///////////////////////////////////////////////////////////////////////////////////////
// Scale Vectors (in place)
inline void m3dScaleVector2(M3DVector2f v, const float scale)
{ v[0] *= scale; v[1] *= scale; }
inline void m3dScaleVector2(M3DVector2d v, const double scale)
{ v[0] *= scale; v[1] *= scale; }

inline void m3dScaleVector3(M3DVector3f v, const float scale)
{ v[0] *= scale; v[1] *= scale; v[2] *= scale; }
inline void m3dScaleVector3(M3DVector3d v, const double scale)
{ v[0] *= scale; v[1] *= scale; v[2] *= scale; }

inline void m3dScaleVector4(M3DVector4f v, const float scale)
{ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }
inline void m3dScaleVector4(M3DVector4d v, const double scale)
{ v[0] *= scale; v[1] *= scale; v[2] *= scale; v[3] *= scale; }


//////////////////////////////////////////////////////////////////////////////////////
// Cross Product
// u x v = result
// 3 component vectors only.
inline void m3dCrossProduct3(M3DVector3f result, const M3DVector3f u, const M3DVector3f v)
{
    result[0] = u[1]*v[2] - v[1]*u[2];
    result[1] = -u[0]*v[2] + v[0]*u[2];
    result[2] = u[0]*v[1] - v[0]*u[1];
}

inline void m3dCrossProduct3(M3DVector3d result, const M3DVector3d u, const M3DVector3d v)
{
    result[0] = u[1]*v[2] - v[1]*u[2];
    result[1] = -u[0]*v[2] + v[0]*u[2];
    result[2] = u[0]*v[1] - v[0]*u[1];
}

//////////////////////////////////////////////////////////////////////////////////////
// Dot Product, only for three component vectors
// return u dot v
inline float m3dDotProduct3(const M3DVector3f u, const M3DVector3f v)
{ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }

inline double m3dDotProduct3(const M3DVector3d u, const M3DVector3d v)
{ return u[0]*v[0] + u[1]*v[1] + u[2]*v[2]; }

//////////////////////////////////////////////////////////////////////////////////////
// Angle between vectors, only for three component vectors. Angle is in radians...
inline float m3dGetAngleBetweenVectors3(const M3DVector3f u, const M3DVector3f v)
{
    float dTemp = m3dDotProduct3(u, v);
    return float(acos(double(dTemp)));    // Double cast just gets rid of compiler warning, no real need
}

inline double m3dGetAngleBetweenVectors3(const M3DVector3d u, const M3DVector3d v)
{
    double dTemp = m3dDotProduct3(u, v);
    return acos(dTemp);
}

//////////////////////////////////////////////////////////////////////////////////////
// Get Square of a vectors length
// Only for three component vectors
inline float m3dGetVectorLengthSquared3(const M3DVector3f u)
{ return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }

inline double m3dGetVectorLengthSquared3(const M3DVector3d u)
{ return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]); }

//////////////////////////////////////////////////////////////////////////////////////
// Get lenght of vector
// Only for three component vectors.
inline float m3dGetVectorLength3(const M3DVector3f u)
{ return sqrtf(m3dGetVectorLengthSquared3(u)); }

inline double m3dGetVectorLength3(const M3DVector3d u)
{ return sqrt(m3dGetVectorLengthSquared3(u)); }

//////////////////////////////////////////////////////////////////////////////////////
// Normalize a vector
// Scale a vector to unit length. Easy, just scale the vector by it's length
inline void m3dNormalizeVector3(M3DVector3f u)
{ m3dScaleVector3(u, 1.0f / m3dGetVectorLength3(u)); }

inline void m3dNormalizeVector3(M3DVector3d u)
{ m3dScaleVector3(u, 1.0 / m3dGetVectorLength3(u)); }


//////////////////////////////////////////////////////////////////////////////////////
// Get the distance between two points. The distance between two points is just
// the magnitude of the difference between two vectors
// Located in math.cpp
float m3dGetDistanceSquared3(const M3DVector3f u, const M3DVector3f v);
double m3dGetDistanceSquared3(const M3DVector3d u, const M3DVector3d v);

inline double m3dGetDistance3(const M3DVector3d u, const M3DVector3d v)
{ return sqrt(m3dGetDistanceSquared3(u, v)); }

inline float m3dGetDistance3(const M3DVector3f u, const M3DVector3f v)
{ return sqrtf(m3dGetDistanceSquared3(u, v)); }

inline float m3dGetMagnitudeSquared3(const M3DVector3f u) { return u[0]*u[0] + u[1]*u[1] + u[2]*u[2]; }
inline double m3dGetMagnitudeSquared3(const M3DVector3d u) { return u[0]*u[0] + u[1]*u[1] + u[2]*u[2]; }

inline float m3dGetMagnitude3(const M3DVector3f u) { return sqrtf(m3dGetMagnitudeSquared3(u)); }
inline double m3dGetMagnitude3(const M3DVector3d u) { return sqrt(m3dGetMagnitudeSquared3(u)); }



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matrix functions
// Both floating point and double precision 3x3 and 4x4 matricies are supported.
// No support is included for arbitrarily dimensioned matricies on purpose, since
// the 3x3 and 4x4 matrix routines are the most common for the purposes of this
// library. Matrices are column major, like OpenGL matrices.
// Unlike the vector functions, some of these are going to have to not be inlined,
// although many will be.

// Copy Matrix
// Brain-dead memcpy
inline void m3dCopyMatrix33(M3DMatrix33f dst, const M3DMatrix33f src)
{ memcpy(dst, src, sizeof(M3DMatrix33f)); }

inline void m3dCopyMatrix33(M3DMatrix33d dst, const M3DMatrix33d src)
{ memcpy(dst, src, sizeof(M3DMatrix33d)); }

inline void m3dCopyMatrix44(M3DMatrix44f dst, const M3DMatrix44f src)
{ memcpy(dst, src, sizeof(M3DMatrix44f)); }

inline void m3dCopyMatrix44(M3DMatrix44d dst, const M3DMatrix44d src)
{ memcpy(dst, src, sizeof(M3DMatrix44d)); }

// LoadIdentity
// Implemented in Math3d.cpp
void m3dLoadIdentity33(M3DMatrix33f m);
void m3dLoadIdentity33(M3DMatrix33d m);
void m3dLoadIdentity44(M3DMatrix44f m);
void m3dLoadIdentity44(M3DMatrix44d m);

/////////////////////////////////////////////////////////////////////////////
// Get/Set Column.
inline void m3dGetMatrixColumn33(M3DVector3f dst, const M3DMatrix33f src, const int column)
{ memcpy(dst, src + (3 * column), sizeof(float) * 3); }

inline void m3dGetMatrixColumn33(M3DVector3d dst, const M3DMatrix33d src, const int column)
{ memcpy(dst, src + (3 * column), sizeof(double) * 3); }

inline void m3dSetMatrixColumn33(M3DMatrix33f dst, const M3DVector3f src, const int column)
{ memcpy(dst + (3 * column), src, sizeof(float) * 3); }

inline void m3dSetMatrixColumn33(M3DMatrix33d dst, const M3DVector3d src, const int column)
{ memcpy(dst + (3 * column), src, sizeof(double) * 3); }

inline void m3dGetMatrixColumn44(M3DVector4f dst, const M3DMatrix44f src, const int column)
{ memcpy(dst, src + (4 * column), sizeof(float) * 4); }

inline void m3dGetMatrixColumn44(M3DVector4d dst, const M3DMatrix44d src, const int column)
{ memcpy(dst, src + (4 * column), sizeof(double) * 4); }

inline void m3dSetMatrixColumn44(M3DMatrix44f dst, const M3DVector4f src, const int column)
{ memcpy(dst + (4 * column), src, sizeof(float) * 4); }

inline void m3dSetMatrixColumn44(M3DMatrix44d dst, const M3DVector4d src, const int column)
{ memcpy(dst + (4 * column), src, sizeof(double) * 4); }


///////////////////////////////////////////////////////////////////////////////
// Extract a rotation matrix from a 4x4 matrix
// Extracts the rotation matrix (3x3) from a 4x4 matrix
inline void m3dExtractRotationMatrix33(M3DMatrix33f dst, const M3DMatrix44f src)
{
    memcpy(dst, src, sizeof(float) * 3); // X column
    memcpy(dst + 3, src + 4, sizeof(float) * 3); // Y column
    memcpy(dst + 6, src + 8, sizeof(float) * 3); // Z column
}

// Ditto above, but for doubles
inline void m3dExtractRotationMatrix33(M3DMatrix33d dst, const M3DMatrix44d src)
{
    memcpy(dst, src, sizeof(double) * 3); // X column
    memcpy(dst + 3, src + 4, sizeof(double) * 3); // Y column
    memcpy(dst + 6, src + 8, sizeof(double) * 3); // Z column
}

// Inject Rotation (3x3) into a full 4x4 matrix...
inline void m3dInjectRotationMatrix44(M3DMatrix44f dst, const M3DMatrix33f src)
{
    memcpy(dst, src, sizeof(float) * 4);
    memcpy(dst + 4, src + 4, sizeof(float) * 4);
    memcpy(dst + 8, src + 8, sizeof(float) * 4);
}

// Ditto above for doubles
inline void m3dInjectRotationMatrix44(M3DMatrix44d dst, const M3DMatrix33d src)
{
    memcpy(dst, src, sizeof(double) * 4);
    memcpy(dst + 4, src + 4, sizeof(double) * 4);
    memcpy(dst + 8, src + 8, sizeof(double) * 4);
}

////////////////////////////////////////////////////////////////////////////////
// MultMatrix
// Implemented in Math.cpp
void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b);
void m3dMatrixMultiply44(M3DMatrix44d product, const M3DMatrix44d a, const M3DMatrix44d b);
void m3dMatrixMultiply33(M3DMatrix33f product, const M3DMatrix33f a, const M3DMatrix33f b);
void m3dMatrixMultiply33(M3DMatrix33d product, const M3DMatrix33d a, const M3DMatrix33d b);


// Transform - Does rotation and translation via a 4x4 matrix. Transforms
// a point or vector.
// By-the-way __inline means I'm asking the compiler to do a cost/benefit analysis. If
// these are used frequently, they may not be inlined to save memory. I'm experimenting
// with this....
// Just transform a 3 compoment vector
__inline void m3dTransformVector3(M3DVector3f vOut, const M3DVector3f v, const M3DMatrix44f m)
{
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12];// * v[3];    // Assuming 1
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13];// * v[3];
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];
    //vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}

// Ditto above, but for doubles
__inline void m3dTransformVector3(M3DVector3d vOut, const M3DVector3d v, const M3DMatrix44d m)
{
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12];// * v[3];
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13];// * v[3];
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14];// * v[3];
    //vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}

// Full four component transform
__inline void m3dTransformVector4(M3DVector4f vOut, const M3DVector4f v, const M3DMatrix44f m)
{
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
    vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}

// Ditto above, but for doubles
__inline void m3dTransformVector4(M3DVector4d vOut, const M3DVector4d v, const M3DMatrix44d m)
{
    vOut[0] = m[0] * v[0] + m[4] * v[1] + m[8] *  v[2] + m[12] * v[3];
    vOut[1] = m[1] * v[0] + m[5] * v[1] + m[9] *  v[2] + m[13] * v[3];
    vOut[2] = m[2] * v[0] + m[6] * v[1] + m[10] * v[2] + m[14] * v[3];
    vOut[3] = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15] * v[3];
}



// Just do the rotation, not the translation... this is usually done with a 3x3
// Matrix.
__inline void m3dRotateVector(M3DVector3f vOut, const M3DVector3f p, const M3DMatrix33f m)
{
    vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
    vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
    vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
}

// Ditto above, but for doubles
__inline void m3dRotateVector(M3DVector3d vOut, const M3DVector3d p, const M3DMatrix33d m)
{
    vOut[0] = m[0] * p[0] + m[3] * p[1] + m[6] * p[2];
    vOut[1] = m[1] * p[0] + m[4] * p[1] + m[7] * p[2];
    vOut[2] = m[2] * p[0] + m[5] * p[1] + m[8] * p[2];
}


// Create a Scaling Matrix
inline void m3dScaleMatrix33(M3DMatrix33f m, float xScale, float yScale, float zScale)
{ m3dLoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale; }

inline void m3dScaleMatrix33(M3DMatrix33f m, const M3DVector3f vScale)
{ m3dLoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2]; }

inline void m3dScaleMatrix33(M3DMatrix33d m, double xScale, double yScale, double zScale)
{ m3dLoadIdentity33(m); m[0] = xScale; m[4] = yScale; m[8] = zScale; }

inline void m3dScaleMatrix33(M3DMatrix33d m, const M3DVector3d vScale)
{ m3dLoadIdentity33(m); m[0] = vScale[0]; m[4] = vScale[1]; m[8] = vScale[2]; }

inline void m3dScaleMatrix44(M3DMatrix44f m, float xScale, float yScale, float zScale)
{ m3dLoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale; }

inline void m3dScaleMatrix44(M3DMatrix44f m, const M3DVector3f vScale)
{ m3dLoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2]; }

inline void m3dScaleMatrix44(M3DMatrix44d m, double xScale, double yScale, double zScale)
{ m3dLoadIdentity44(m); m[0] = xScale; m[5] = yScale; m[10] = zScale; }

inline void m3dScaleMatrix44(M3DMatrix44d m, const M3DVector3d vScale)
{ m3dLoadIdentity44(m); m[0] = vScale[0]; m[5] = vScale[1]; m[10] = vScale[2]; }


void m3dMakePerspectiveMatrix(M3DMatrix44f mProjection, float fFov, float fAspect, float zMin, float zMax);
void m3dMakeOrthographicMatrix(M3DMatrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);


// Create a Rotation matrix
// Implemented in math3d.cpp
void m3dRotationMatrix33(M3DMatrix33f m, float angle, float x, float y, float z);
void m3dRotationMatrix33(M3DMatrix33d m, double angle, double x, double y, double z);
void m3dRotationMatrix44(M3DMatrix44f m, float angle, float x, float y, float z);
void m3dRotationMatrix44(M3DMatrix44d m, double angle, double x, double y, double z);

// Create a Translation matrix. Only 4x4 matrices have translation components
inline void m3dTranslationMatrix44(M3DMatrix44f m, float x, float y, float z)
{ m3dLoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z; }

inline void m3dTranslationMatrix44(M3DMatrix44d m, double x, double y, double z)
{ m3dLoadIdentity44(m); m[12] = x; m[13] = y; m[14] = z; }

void m3dInvertMatrix44(M3DMatrix44f mInverse, const M3DMatrix44f m);
void m3dInvertMatrix44(M3DMatrix44d mInverse, const M3DMatrix44d m);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Other Miscellaneous functions

// Find a normal from three points
// Implemented in math3d.cpp
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2,
                   const M3DVector3f point3);
void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2,
                   const M3DVector3d point3);


// Calculates the signed distance of a point to a plane
inline float m3dGetDistanceToPlane(const M3DVector3f point, const M3DVector4f plane)
{ return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3]; }

inline double m3dGetDistanceToPlane(const M3DVector3d point, const M3DVector4d plane)
{ return point[0]*plane[0] + point[1]*plane[1] + point[2]*plane[2] + plane[3]; }


// Get plane equation from three points
void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3);
void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3);

// Determine if a ray intersects a sphere
// Return value is < 0 if the ray does not intersect
// Return value is 0.0 if ray is tangent
// Positive value is distance to the intersection point
double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius);
float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius);


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Faster (and one shortcut) replacements for gluProject
void m3dProjectXY( M3DVector2f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);
void m3dProjectXYZ(M3DVector3f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn);


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom "spline" interpolation between p1 and p2
void m3dCatmullRom(M3DVector3f vOut, const M3DVector3f vP0, const M3DVector3f vP1, const M3DVector3f vP2, const M3DVector3f vP3, float t);
void m3dCatmullRom(M3DVector3d vOut, const M3DVector3d vP0, const M3DVector3d vP1, const M3DVector3d vP2, const M3DVector3d vP3, double t);
void m3dCatmullRom2D(M3DVector2d vOut, const M3DVector2d vP0, const M3DVector2d vP1, const M3DVector2d vP2, const M3DVector2d vP3, double t);
void m3dCatmullRom2D(M3DVector2f vOut, const M3DVector2f vP0, const M3DVector2f vP1, const M3DVector2f vP2, const M3DVector2f vP3, float t);


//////////////////////////////////////////////////////////////////////////////////////////////////
// Compare floats and doubles...
inline bool m3dCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon)
{
    return (fabs(fCandidate - fCompare) < fEpsilon);
}

inline bool m3dCloseEnough(const double dCandidate, const double dCompare, const double dEpsilon)
{
    return (fabs(dCandidate - dCompare) < dEpsilon);
}

////////////////////////////////////////////////////////////////////////////
// Used for normal mapping. Finds the tangent bases for a triangle...
// Only a floating point implementation is provided. This has no practical use as doubles.
void m3dCalculateTangentBasis(M3DVector3f vTangent, const M3DVector3f pvTriangle[3], const M3DVector2f pvTexCoords[3], const M3DVector3f N);

////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
double m3dSmoothStep(const double edge1, const double edge2, const double x);
float m3dSmoothStep(const float edge1, const float edge2, const float x);

/////////////////////////////////////////////////////////////////////////////
// Planar shadow Matrix
void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3d vLightPos);
void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos);

/////////////////////////////////////////////////////////////////////////////
// Closest point on a ray to another point in space
double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir,
                            const M3DVector3d vPointInSpace);

float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir,
                           const M3DVector3f vPointInSpace);

//////////////////////////////////////////////////////////////////////////////
// Miscellany...
void m3dPerform2DRotationOnPoint(const double inXY[2], double outXY[2], double rotDegrees);



#endif

// math3d.cpp
// Math3D Library

/* Copyright (c) 2007-2009, Richard S. Wright Jr.
 MIT License
 Copyright (c) 2007-2017 Richard S. Wright Jr.
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 Contact GitHub API Training Shop Blog About
 */

// Implementation file for the Math3d library. The C-Runtime has math.h, these routines
// are meant to suppliment math.h by adding geometry/math routines
// useful for graphics, simulation, and physics applications (3D stuff).
// This library is meant to be useful on Win32, Mac OS X, various Linux/Unix distros,
// and mobile platforms. Although designed with OpenGL in mind, there are no OpenGL
// dependencies. Other than standard math routines, the only other outside routine
// used is memcpy (for faster copying of vector arrays).
// Most of the library is inlined. Some functions however are here as I judged them
// too big to be inlined all over the place... nothing prevents anyone from changing
// this if it better fits their project requirements.
// Richard S. Wright Jr.

// Most functions are in-lined... and are defined here
//#include <math3d.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Rotates an XY coordiante around the origin. Rotation angle is in degrees for convienience. Positive angles rotate
// counterclockwise around the origin. Negative angles rotate clockwise.
void m3dPerform2DRotationOnPoint(const double inXY[2], double outXY[2], double rotDegrees)
{
    M3DMatrix33d mRot;
    double rotRadians = m3dRadToDeg(rotDegrees);
    m3dRotationMatrix33(mRot, rotRadians, 0.0, 0.0, 1.0);
    M3DVector3d vIn, vOut;
    
    vIn[0] = inXY[0];
    vIn[1] = inXY[1];
    vIn[2] = 0.0;
    
    m3dTransformVector3(vOut, vIn, mRot);
    outXY[0] = vOut[0];
    outXY[1] = vOut[1];
}


////////////////////////////////////////////////////////////
// LoadIdentity
// For 3x3 and 4x4 float and double matricies.
// 3x3 float
void m3dLoadIdentity33(M3DMatrix33f m)
{
    // Don't be fooled, this is still column major
    static M3DMatrix33f    identity = { 1.0f, 0.0f, 0.0f ,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };
    
    memcpy(m, identity, sizeof(M3DMatrix33f));
}

// 3x3 double
void m3dLoadIdentity33(M3DMatrix33d m)
{
    // Don't be fooled, this is still column major
    static M3DMatrix33d    identity = { 1.0, 0.0, 0.0 ,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0 };
    
    memcpy(m, identity, sizeof(M3DMatrix33d));
}

// 4x4 float
void m3dLoadIdentity44(M3DMatrix44f m)
{
    // Don't be fooled, this is still column major
    static M3DMatrix44f    identity = { 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    memcpy(m, identity, sizeof(M3DMatrix44f));
}

// 4x4 double
void m3dLoadIdentity44(M3DMatrix44d m)
{
    static M3DMatrix44d    identity = { 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 };
    
    memcpy(m, identity, sizeof(M3DMatrix44d));
}


////////////////////////////////////////////////////////////////////////
// Return the square of the distance between two points
// Should these be inlined...?
float m3dGetDistanceSquared3(const M3DVector3f u, const M3DVector3f v)
{
    float x = u[0] - v[0];
    x = x*x;
    
    float y = u[1] - v[1];
    y = y*y;
    
    float z = u[2] - v[2];
    z = z*z;
    
    return (x + y + z);
}

// Ditto above, but for doubles
double m3dGetDistanceSquared3(const M3DVector3d u, const M3DVector3d v)
{
    double x = u[0] - v[0];
    x = x*x;
    
    double y = u[1] - v[1];
    y = y*y;
    
    double z = u[2] - v[2];
    z = z*z;
    
    return (x + y + z);
}

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 4x4 matricies
void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b )
{
    for (int i = 0; i < 4; i++) {
        float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
        P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
        P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
        P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
        P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
    }
}

// Ditto above, but for doubles
void m3dMatrixMultiply44(M3DMatrix44d product, const M3DMatrix44d a, const M3DMatrix44d b )
{
    for (int i = 0; i < 4; i++) {
        double ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
        P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
        P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
        P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
        P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
    }
}
#undef A
#undef B
#undef P


#define A33(row,col)  a[(col*3)+row]
#define B33(row,col)  b[(col*3)+row]
#define P33(row,col)  product[(col*3)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 3x3 matricies
void m3dMatrixMultiply33(M3DMatrix33f product, const M3DMatrix33f a, const M3DMatrix33f b )
{
    for (int i = 0; i < 3; i++) {
        float ai0=A33(i,0), ai1=A33(i,1),  ai2=A33(i,2);
        P33(i,0) = ai0 * B33(0,0) + ai1 * B33(1,0) + ai2 * B33(2,0);
        P33(i,1) = ai0 * B33(0,1) + ai1 * B33(1,1) + ai2 * B33(2,1);
        P33(i,2) = ai0 * B33(0,2) + ai1 * B33(1,2) + ai2 * B33(2,2);
    }
}

// Ditto above, but for doubles
void m3dMatrixMultiply33(M3DMatrix33d product, const M3DMatrix33d a, const M3DMatrix33d b )
{
    for (int i = 0; i < 3; i++) {
        double ai0=A33(i,0),  ai1=A33(i,1),  ai2=A33(i,2);
        P33(i,0) = ai0 * B33(0,0) + ai1 * B33(1,0) + ai2 * B33(2,0);
        P33(i,1) = ai0 * B33(0,1) + ai1 * B33(1,1) + ai2 * B33(2,1);
        P33(i,2) = ai0 * B33(0,2) + ai1 * B33(1,2) + ai2 * B33(2,2);
    }
}

#undef A33
#undef B33
#undef P33



////////////////////////////////////////////////////////////////////////////////////////////
// Create a projection matrix
// Similiar to the old gluPerspective... fov is in radians btw...
void m3dMakePerspectiveMatrix(M3DMatrix44f mProjection, float fFov, float fAspect, float zMin, float zMax)
{
    m3dLoadIdentity44(mProjection); // Fastest way to get most valid values already in place
    
    float yMax = zMin * tanf(fFov * 0.5f);
    float yMin = -yMax;
    float xMin = yMin * fAspect;
    float xMax = -xMin;
    
    mProjection[0] = (2.0f * zMin) / (xMax - xMin);
    mProjection[5] = (2.0f * zMin) / (yMax - yMin);
    mProjection[8] = (xMax + xMin) / (xMax - xMin);
    mProjection[9] = (yMax + yMin) / (yMax - yMin);
    mProjection[10] = -((zMax + zMin) / (zMax - zMin));
    mProjection[11] = -1.0f;
    mProjection[14] = -((2.0f * (zMax*zMin))/(zMax - zMin));
    mProjection[15] = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
// Make a orthographic projection matrix
void m3dMakeOrthographicMatrix(M3DMatrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
{
    m3dLoadIdentity44(mProjection);
    
    mProjection[0] = 2.0f / (xMax - xMin);
    mProjection[5] = 2.0f / (yMax - yMin);
    mProjection[10] = -2.0f / (zMax - zMin);
    mProjection[12] = -((xMax + xMin)/(xMax - xMin));
    mProjection[13] = -((yMax + yMin)/(yMax - yMin));
    mProjection[14] = -((zMax + zMin)/(zMax - zMin));
    mProjection[15] = 1.0f;
}



#define M33(row,col)  m[col*3+row]
///////////////////////////////////////////////////////////////////////////////
// Creates a 3x3 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix33(M3DMatrix33f m, float angle, float x, float y, float z)
{
    
    float mag, s, c;
    float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    
    s = float(sin(angle));
    c = float(cos(angle));
    
    mag = float(sqrt( x*x + y*y + z*z ));
    
    // Identity matrix
    if (mag == 0.0f) {
        m3dLoadIdentity33(m);
        return;
    }
    
    // Rotation matrix is normalized
    x /= mag;
    y /= mag;
    z /= mag;
    
    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0f - c;
    
    M33(0,0) = (one_c * xx) + c;
    M33(0,1) = (one_c * xy) - zs;
    M33(0,2) = (one_c * zx) + ys;
    
    M33(1,0) = (one_c * xy) + zs;
    M33(1,1) = (one_c * yy) + c;
    M33(1,2) = (one_c * yz) - xs;
    
    M33(2,0) = (one_c * zx) - ys;
    M33(2,1) = (one_c * yz) + xs;
    M33(2,2) = (one_c * zz) + c;
}

#undef M33

///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44f m, float angle, float x, float y, float z)
{
    float mag, s, c;
    float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    
    s = float(sin(angle));
    c = float(cos(angle));
    
    mag = float(sqrt( x*x + y*y + z*z ));
    
    // Identity matrix
    if (mag == 0.0f) {
        m3dLoadIdentity44(m);
        return;
    }
    
    // Rotation matrix is normalized
    x /= mag;
    y /= mag;
    z /= mag;
    
#define M(row,col)  m[col*4+row]
    
    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0f - c;
    
    M(0,0) = (one_c * xx) + c;
    M(0,1) = (one_c * xy) - zs;
    M(0,2) = (one_c * zx) + ys;
    M(0,3) = 0.0f;
    
    M(1,0) = (one_c * xy) + zs;
    M(1,1) = (one_c * yy) + c;
    M(1,2) = (one_c * yz) - xs;
    M(1,3) = 0.0f;
    
    M(2,0) = (one_c * zx) - ys;
    M(2,1) = (one_c * yz) + xs;
    M(2,2) = (one_c * zz) + c;
    M(2,3) = 0.0f;
    
    M(3,0) = 0.0f;
    M(3,1) = 0.0f;
    M(3,2) = 0.0f;
    M(3,3) = 1.0f;
    
#undef M
}



///////////////////////////////////////////////////////////////////////////////
// Ditto above, but for doubles
void m3dRotationMatrix33(M3DMatrix33d m, double angle, double x, double y, double z)
{
    double mag, s, c;
    double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    
    s = sin(angle);
    c = cos(angle);
    
    mag = sqrt( x*x + y*y + z*z );
    
    // Identity matrix
    if (mag == 0.0) {
        m3dLoadIdentity33(m);
        return;
    }
    
    // Rotation matrix is normalized
    x /= mag;
    y /= mag;
    z /= mag;
    
#define M(row,col)  m[col*3+row]
    
    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0 - c;
    
    M(0,0) = (one_c * xx) + c;
    M(0,1) = (one_c * xy) - zs;
    M(0,2) = (one_c * zx) + ys;
    
    M(1,0) = (one_c * xy) + zs;
    M(1,1) = (one_c * yy) + c;
    M(1,2) = (one_c * yz) - xs;
    
    M(2,0) = (one_c * zx) - ys;
    M(2,1) = (one_c * yz) + xs;
    M(2,2) = (one_c * zz) + c;
    
#undef M
}


///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44d m, double angle, double x, double y, double z)
{
    double mag, s, c;
    double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
    
    s = sin(angle);
    c = cos(angle);
    
    mag = sqrt( x*x + y*y + z*z );
    
    // Identity matrix
    if (mag == 0.0) {
        m3dLoadIdentity44(m);
        return;
    }
    
    // Rotation matrix is normalized
    x /= mag;
    y /= mag;
    z /= mag;
    
#define M(row,col)  m[col*4+row]
    
    xx = x * x;
    yy = y * y;
    zz = z * z;
    xy = x * y;
    yz = y * z;
    zx = z * x;
    xs = x * s;
    ys = y * s;
    zs = z * s;
    one_c = 1.0f - c;
    
    M(0,0) = (one_c * xx) + c;
    M(0,1) = (one_c * xy) - zs;
    M(0,2) = (one_c * zx) + ys;
    M(0,3) = 0.0;
    
    M(1,0) = (one_c * xy) + zs;
    M(1,1) = (one_c * yy) + c;
    M(1,2) = (one_c * yz) - xs;
    M(1,3) = 0.0;
    
    M(2,0) = (one_c * zx) - ys;
    M(2,1) = (one_c * yz) + xs;
    M(2,2) = (one_c * zz) + c;
    M(2,3) = 0.0;
    
    M(3,0) = 0.0;
    M(3,1) = 0.0;
    M(3,2) = 0.0;
    M(3,3) = 1.0;
    
#undef M
}

////////////////////////////////////////////////////////////////////////////
/// This function is not exported by library, just for this modules use only
// 3x3 determinant
static float DetIJ(const M3DMatrix44f m, const int i, const int j)
{
    int x, y, ii, jj;
    float ret, mat[3][3];
    
    x = 0;
    for (ii = 0; ii < 4; ii++)
    {
        if (ii == i) continue;
        y = 0;
        for (jj = 0; jj < 4; jj++)
        {
            if (jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            y++;
        }
        x++;
    }
    
    ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    
    return ret;
}


////////////////////////////////////////////////////////////////////////////
/// This function is not exported by library, just for this modules use only
// 3x3 determinant
static double DetIJ(const M3DMatrix44d m, const int i, const int j)
{
    int x, y, ii, jj;
    double ret, mat[3][3];
    
    x = 0;
    for (ii = 0; ii < 4; ii++)
    {
        if (ii == i) continue;
        y = 0;
        for (jj = 0; jj < 4; jj++)
        {
            if (jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            y++;
        }
        x++;
    }
    
    ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);
    
    return ret;
}

////////////////////////////////////////////////////////////////////////////
///
// Invert matrix
void m3dInvertMatrix44(M3DMatrix44f mInverse, const M3DMatrix44f m)
{
    int i, j;
    float det, detij;
    
    // calculate 4x4 determinant
    det = 0.0f;
    for (i = 0; i < 4; i++)
    {
        det += (i & 0x1) ? (-m[i] * DetIJ(m, 0, i)) : (m[i] * DetIJ(m, 0,i));
    }
    det = 1.0f / det;
    
    // calculate inverse
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            detij = DetIJ(m, j, i);
            mInverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det);
        }
    }
}

////////////////////////////////////////////////////////////////////////////
///
// Invert matrix
void m3dInvertMatrix44(M3DMatrix44d mInverse, const M3DMatrix44d m)
{
    int i, j;
    double det, detij;
    
    // calculate 4x4 determinant
    det = 0.0;
    for (i = 0; i < 4; i++)
    {
        det += (i & 0x1) ? (-m[i] * DetIJ(m, 0, i)) : (m[i] * DetIJ(m, 0,i));
    }
    det = 1.0 / det;
    
    // calculate inverse
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            detij = DetIJ(m, j, i);
            mInverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det);
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////
// Get Window coordinates, discard Z...
void m3dProjectXY(M3DVector2f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn)
{
    M3DVector4f vBack, vForth;
    
    memcpy(vBack, vPointIn, sizeof(float)*3);
    vBack[3] = 1.0f;
    
    m3dTransformVector4(vForth, vBack, mModelView);
    m3dTransformVector4(vBack, vForth, mProjection);
    
    if(!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
        float div = 1.0f / vBack[3];
        vBack[0] *= div;
        vBack[1] *= div;
        //vBack[2] *= div;
    }
    
    vPointOut[0] = float(iViewPort[0])+(1.0f+float(vBack[0]))*float(iViewPort[2])/2.0f;
    vPointOut[1] = float(iViewPort[1])+(1.0f+float(vBack[1]))*float(iViewPort[3])/2.0f;
    
    // This was put in for Grand Tour... I think it's right.
    // .... please report any bugs
    if(iViewPort[0] != 0)     // Cast to float is expensive... avoid if posssible
        vPointOut[0] -= float(iViewPort[0]);
    
    if(iViewPort[1] != 0)
        vPointOut[1] -= float(iViewPort[1]);
}

///////////////////////////////////////////////////////////////////////////////////////
// Get window coordinates, we also want Z....
void m3dProjectXYZ(M3DVector3f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn)
{
    M3DVector4f vBack, vForth;
    
    memcpy(vBack, vPointIn, sizeof(float)*3);
    vBack[3] = 1.0f;
    
    m3dTransformVector4(vForth, vBack, mModelView);
    m3dTransformVector4(vBack, vForth, mProjection);
    
    if(!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
        float div = 1.0f / vBack[3];
        vBack[0] *= div;
        vBack[1] *= div;
        vBack[2] *= div;
    }
    
    vPointOut[0] = float(iViewPort[0])+(1.0f+float(vBack[0]))*float(iViewPort[2])/2.0f;
    vPointOut[1] = float(iViewPort[1])+(1.0f+float(vBack[1]))*float(iViewPort[3])/2.0f;
    
    if(iViewPort[0] != 0)     // Cast to float is expensive... avoid if posssible
        vPointOut[0] -= float(iViewPort[0]);
    
    if(iViewPort[1] != 0)
        vPointOut[1] -= float(iViewPort[1]);
    
    vPointOut[2] = vBack[2];
}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Misc. Utilities
///////////////////////////////////////////////////////////////////////////////
// Calculates the normal of a triangle specified by the three points
// p1, p2, and p3. Each pointer points to an array of three floats. The
// triangle is assumed to be wound counter clockwise.
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2,
                   const M3DVector3f point3)
{
    M3DVector3f v1,v2;        // Temporary vectors
    
    // Calculate two vectors from the three points. Assumes counter clockwise
    // winding!
    //    v1[0] = point1[0] - point2[0];
    //    v1[1] = point1[1] - point2[1];
    //    v1[2] = point1[2] - point2[2];
    //
    //    v2[0] = point2[0] - point3[0];
    //    v2[1] = point2[1] - point3[1];
    //    v2[2] = point2[2] - point3[2];
    
    
    v1[0] = point2[0] - point1[0];
    v1[1] = point2[1] - point1[1];
    v1[2] = point2[2] - point1[2];
    
    v2[0] = point3[0] - point1[0];
    v2[1] = point3[1] - point1[1];
    v2[2] = point3[2] - point1[2];
    
    
    // Take the cross product of the two vectors to get
    // the normal vector.
    m3dCrossProduct3(result, v1, v2);
}



// Ditto above, but for doubles
void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2,
                   const M3DVector3d point3)
{
    M3DVector3d v1,v2;        // Temporary vectors
    
    // Calculate two vectors from the three points. Assumes counter clockwise
    // winding!
    v1[0] = point1[0] - point2[0];
    v1[1] = point1[1] - point2[1];
    v1[2] = point1[2] - point2[2];
    
    v2[0] = point2[0] - point3[0];
    v2[1] = point2[1] - point3[1];
    v2[2] = point2[2] - point3[2];
    
    // Take the cross product of the two vectors to get
    // the normal vector.
    m3dCrossProduct3(result, v1, v2);
}



/////////////////////////////////////////////////////////////////////////////////////////
// Calculate the plane equation of the plane that the three specified points lay in. The
// points are given in clockwise winding order, with normal pointing out of clockwise face
// planeEq contains the A,B,C, and D of the plane equation coefficients
void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3)
{
    // Get two vectors... do the cross product
    M3DVector3f v1, v2;
    
    // V1 = p3 - p1
    v1[0] = p3[0] - p1[0];
    v1[1] = p3[1] - p1[1];
    v1[2] = p3[2] - p1[2];
    
    // V2 = P2 - p1
    v2[0] = p2[0] - p1[0];
    v2[1] = p2[1] - p1[1];
    v2[2] = p2[2] - p1[2];
    
    // Unit normal to plane - Not sure which is the best way here
    m3dCrossProduct3(planeEq, v1, v2);
    m3dNormalizeVector3(planeEq);
    
    // Back substitute to get D
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


// Ditto above, but for doubles
void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3)
{
    // Get two vectors... do the cross product
    M3DVector3d v1, v2;
    
    // V1 = p3 - p1
    v1[0] = p3[0] - p1[0];
    v1[1] = p3[1] - p1[1];
    v1[2] = p3[2] - p1[2];
    
    // V2 = P2 - p1
    v2[0] = p2[0] - p1[0];
    v2[1] = p2[1] - p1[1];
    v2[2] = p2[2] - p1[2];
    
    // Unit normal to plane - Not sure which is the best way here
    m3dCrossProduct3(planeEq, v1, v2);
    m3dNormalizeVector3(planeEq);
    // Back substitute to get D
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom(M3DVector3f vOut, const M3DVector3f vP0, const M3DVector3f vP1, const M3DVector3f vP2, const M3DVector3f vP3, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    
    // X
    vOut[0] = 0.5f * ( ( 2.0f * vP1[0]) +
                      (-vP0[0] + vP2[0]) * t +
                      (2.0f * vP0[0] - 5.0f *vP1[0] + 4.0f * vP2[0] - vP3[0]) * t2 +
                      (-vP0[0] + 3.0f*vP1[0] - 3.0f *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5f * ( ( 2.0f * vP1[1]) +
                      (-vP0[1] + vP2[1]) * t +
                      (2.0f * vP0[1] - 5.0f *vP1[1] + 4.0f * vP2[1] - vP3[1]) * t2 +
                      (-vP0[1] + 3.0f*vP1[1] - 3.0f *vP2[1] + vP3[1]) * t3);
    
    // Z
    vOut[2] = 0.5f * ( ( 2.0f * vP1[2]) +
                      (-vP0[2] + vP2[2]) * t +
                      (2.0f * vP0[2] - 5.0f *vP1[2] + 4.0f * vP2[2] - vP3[2]) * t2 +
                      (-vP0[2] + 3.0f*vP1[2] - 3.0f *vP2[2] + vP3[2]) * t3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a two dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom2D(M3DVector2f vOut, const M3DVector2f vP0, const M3DVector2f vP1, const M3DVector2f vP2, const M3DVector2f vP3, float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    
    // X
    vOut[0] = 0.5 * ( ( 2.0 * vP1[0]) +
                     (-vP0[0] + vP2[0]) * t +
                     (2.0 * vP0[0] - 5.0 *vP1[0] + 4.0 * vP2[0] - vP3[0]) * t2 +
                     (-vP0[0] + 3.0*vP1[0] - 3.0 *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5 * ( ( 2.0 * vP1[1]) +
                     (-vP0[1] + vP2[1]) * t +
                     (2.0 * vP0[1] - 5.0 *vP1[1] + 4.0 * vP2[1] - vP3[1]) * t2 +
                     (-vP0[1] + 3*vP1[1] - 3.0 *vP2[1] + vP3[1]) * t3);
    
}



//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom(M3DVector3d vOut, const M3DVector3d vP0, const M3DVector3d vP1, const M3DVector3d vP2, const M3DVector3d vP3, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;
    
    // X
    vOut[0] = 0.5 * ( ( 2.0 * vP1[0]) +
                     (-vP0[0] + vP2[0]) * t +
                     (2.0 * vP0[0] - 5.0 *vP1[0] + 4.0 * vP2[0] - vP3[0]) * t2 +
                     (-vP0[0] + 3.0*vP1[0] - 3.0 *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5 * ( ( 2.0 * vP1[1]) +
                     (-vP0[1] + vP2[1]) * t +
                     (2.0 * vP0[1] - 5.0 *vP1[1] + 4.0 * vP2[1] - vP3[1]) * t2 +
                     (-vP0[1] + 3*vP1[1] - 3.0 *vP2[1] + vP3[1]) * t3);
    
    // Z
    vOut[2] = 0.5 * ( ( 2.0 * vP1[2]) +
                     (-vP0[2] + vP2[2]) * t +
                     (2.0 * vP0[2] - 5.0 *vP1[2] + 4.0 * vP2[2] - vP3[2]) * t2 +
                     (-vP0[2] + 3.0*vP1[2] - 3.0 *vP2[2] + vP3[2]) * t3);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a two dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom2D(M3DVector2d vOut, const M3DVector2d vP0, const M3DVector2d vP1, const M3DVector2d vP2, const M3DVector2d vP3, double t)
{
    double t2 = t * t;
    double t3 = t2 * t;
    
    // X
    vOut[0] = 0.5 * ( ( 2.0 * vP1[0]) +
                     (-vP0[0] + vP2[0]) * t +
                     (2.0 * vP0[0] - 5.0 *vP1[0] + 4.0 * vP2[0] - vP3[0]) * t2 +
                     (-vP0[0] + 3.0*vP1[0] - 3.0 *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5 * ( ( 2.0 * vP1[1]) +
                     (-vP0[1] + vP2[1]) * t +
                     (2.0 * vP0[1] - 5.0 *vP1[1] + 4.0 * vP2[1] - vP3[1]) * t2 +
                     (-vP0[1] + 3*vP1[1] - 3.0 *vP2[1] + vP3[1]) * t3);
    
}


///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// sphereCenter with radius sphereRadius
// Return value is < 0 if the ray does not intersect
// Return value is 0.0 if ray is tangent
// Positive value is distance to the intersection point
// Algorithm from "3D Math Primer for Graphics and Game Development"
double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius)
{
    //m3dNormalizeVector(ray);    // Make sure ray is unit length
    
    M3DVector3d rayToCenter;    // Ray to center of sphere
    rayToCenter[0] =  sphereCenter[0] - point[0];
    rayToCenter[1] =  sphereCenter[1] - point[1];
    rayToCenter[2] =  sphereCenter[2] - point[2];
    
    // Project rayToCenter on ray to test
    double a = m3dDotProduct3(rayToCenter, ray);
    
    // Distance to center of sphere
    double distance2 = m3dDotProduct3(rayToCenter, rayToCenter);    // Or length
    
    
    double dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);
    
    if(dRet > 0.0)            // Return distance to intersection
        dRet = a - sqrt(dRet);
    
    return dRet;
}

///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// ditto above, but uses floating point math
float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius)
{
    //m3dNormalizeVectorf(ray);    // Make sure ray is unit length
    
    M3DVector3f rayToCenter;    // Ray to center of sphere
    rayToCenter[0] =  sphereCenter[0] - point[0];
    rayToCenter[1] =  sphereCenter[1] - point[1];
    rayToCenter[2] =  sphereCenter[2] - point[2];
    
    // Project rayToCenter on ray to test
    float a = m3dDotProduct3(rayToCenter, ray);
    
    // Distance to center of sphere
    float distance2 = m3dDotProduct3(rayToCenter, rayToCenter);    // Or length
    
    float dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);
    
    if(dRet > 0.0)            // Return distance to intersection
        dRet = a - sqrtf(dRet);
    
    return dRet;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate the tangent basis for a triangle on the surface of a model
// This vector is needed for most normal mapping shaders
void m3dCalculateTangentBasis(M3DVector3f vTangent, const M3DVector3f vTriangle[3], const M3DVector2f vTexCoords[3], const M3DVector3f N)
{
    M3DVector3f dv2v1, dv3v1;
    float dc2c1t, dc2c1b, dc3c1t, dc3c1b;
    float M;
    
    m3dSubtractVectors3(dv2v1, vTriangle[1], vTriangle[0]);
    m3dSubtractVectors3(dv3v1, vTriangle[2], vTriangle[0]);
    
    dc2c1t = vTexCoords[1][0] - vTexCoords[0][0];
    dc2c1b = vTexCoords[1][1] - vTexCoords[0][1];
    dc3c1t = vTexCoords[2][0] - vTexCoords[0][0];
    dc3c1b = vTexCoords[2][1] - vTexCoords[0][1];
    
    M = (dc2c1t * dc3c1b) - (dc3c1t * dc2c1b);
    M = 1.0f / M;
    
    m3dScaleVector3(dv2v1, dc3c1b);
    m3dScaleVector3(dv3v1, dc2c1b);
    
    m3dSubtractVectors3(vTangent, dv2v1, dv3v1);
    m3dScaleVector3(vTangent, M);  // This potentially changes the direction of the vector
    m3dNormalizeVector3(vTangent);
    
    M3DVector3f B;
    m3dCrossProduct3(B, N, vTangent);
    m3dCrossProduct3(vTangent, B, N);
    m3dNormalizeVector3(vTangent);
}


////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
double m3dSmoothStep(const double edge1, const double edge2, const double x)
{
    double t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1.0)
        t = 1.0;
    
    if(t < 0.0)
        t = 0.0f;
    
    return t * t * ( 3.0 - 2.0 * t);
}

////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
float m3dSmoothStep(const float edge1, const float edge2, const float x)
{
    float t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1.0f)
        t = 1.0f;
    
    if(t < 0.0)
        t = 0.0f;
    
    return t * t * ( 3.0f - 2.0f * t);
}



///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationf(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos)
{
    // These just make the code below easier to read. They will be
    // removed by the optimizer.
    float a = planeEq[0];
    float b = planeEq[1];
    float c = planeEq[2];
    float d = planeEq[3];
    
    float dx = -vLightPos[0];
    float dy = -vLightPos[1];
    float dz = -vLightPos[2];
    
    // Now build the projection matrix
    proj[0] = b * dy + c * dz;
    proj[1] = -a * dy;
    proj[2] = -a * dz;
    proj[3] = 0.0;
    
    proj[4] = -b * dx;
    proj[5] = a * dx + c * dz;
    proj[6] = -b * dz;
    proj[7] = 0.0;
    
    proj[8] = -c * dx;
    proj[9] = -c * dy;
    proj[10] = a * dx + b * dy;
    proj[11] = 0.0;
    
    proj[12] = -d * dx;
    proj[13] = -d * dy;
    proj[14] = -d * dz;
    proj[15] = a * dx + b * dy + c * dz;
    // Shadow matrix ready
}


///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationd(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3d vLightPos)
{
    // These just make the code below easier to read. They will be
    // removed by the optimizer.
    double a = planeEq[0];
    double b = planeEq[1];
    double c = planeEq[2];
    double d = planeEq[3];
    
    double dx = -vLightPos[0];
    double dy = -vLightPos[1];
    double dz = -vLightPos[2];
    
    // Now build the projection matrix
    proj[0] = b * dy + c * dz;
    proj[1] = -a * dy;
    proj[2] = -a * dz;
    proj[3] = 0.0;
    
    proj[4] = -b * dx;
    proj[5] = a * dx + c * dz;
    proj[6] = -b * dz;
    proj[7] = 0.0;
    
    proj[8] = -c * dx;
    proj[9] = -c * dy;
    proj[10] = a * dx + b * dy;
    proj[11] = 0.0;
    
    proj[12] = -d * dx;
    proj[13] = -d * dy;
    proj[14] = -d * dz;
    proj[15] = a * dx + b * dy + c * dz;
    // Shadow matrix ready
}


/////////////////////////////////////////////////////////////////////////////
// I want to know the point on a ray, closest to another given point in space.
// As a bonus, return the distance squared of the two points.
// In: vRayOrigin is the origin of the ray.
// In: vUnitRayDir is the unit vector of the ray
// In: vPointInSpace is the point in space
// Out: vPointOnRay is the poing on the ray closest to vPointInSpace
// Return: The square of the distance to the ray
double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir,
                            const M3DVector3d vPointInSpace)
{
    M3DVector3d v;
    m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);
    
    double t = m3dDotProduct3(vUnitRayDir, v);
    
    // This is the point on the ray
    vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
    vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
    vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);
    
    return m3dGetDistanceSquared3(vPointOnRay, vPointInSpace);
}

// ditto above... but with floats
float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir,
                           const M3DVector3f vPointInSpace)
{
    M3DVector3f v;
    m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);
    
    float t = m3dDotProduct3(vUnitRayDir, v);
    
    // This is the point on the ray
    vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
    vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
    vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);
    
    return m3dGetDistanceSquared3(vPointOnRay, vPointInSpace);
    }





#ifndef GRAPHICS_MATH_H
#define GRAPHICS_MATH_H
#define _USE_MATH_DEFINES
#include <math.h>

#define TAU 2.0*M_PI
#define ONE_DEG_IN_RAD (2.0*M_PI)/360.0
#define ONE_RAD_IN_DEG 360.0/(2.0*M_PI)


struct vec2;
struct vec3;
struct vec4;
struct versor;

struct vec2 {
    vec2 ();
    vec2 (float x, float y);
    float v[2];
};

struct vec3 {
    vec3 ();
    // create from 3 scalars
    vec3 (float x, float y, float z);
    // create from vec2 and a scalar
    vec3 (const vec2& vv, float z);
    // create from truncated vec4
    vec3 (const vec4& vv);
    // add vector to vector
    vec3 operator+ (const vec3& rhs);
    // add scalar to vector
    vec3 operator+ (float rhs);
    // because user's expect this too
    vec3& operator+= (const vec3& rhs);
    // subtract vector from vector
    vec3 operator- (const vec3& rhs);
    // add vector to vector
    vec3 operator- (float rhs);
    // because users expect this too
    vec3& operator-= (const vec3& rhs);
    // multiply with scalar
    vec3 operator* (float rhs);
    // because users expect this too
    vec3& operator*= (float rhs);
    // divide vector by scalar
    vec3 operator/ (float rhs);
    // because users expect this too
    vec3& operator= (const vec3& rhs);
    
    // internal data
    float v[3];
};

struct vec4 {
    vec4 ();
    vec4 (float x, float y, float z, float w);
    vec4 (const vec2& vv, float z, float w);
    vec4 (const vec3& vv, float w);
    float v[4];
};

/* stored like this:
 a d g
 b e h
 c f i */
struct mat3 {
    mat3 ();
    mat3 (float a, float b, float c,
          float d, float e, float f,
          float g, float h, float i);
    float m[9];
};

/* stored like this:
 0 4 8  12
 1 5 9  13
 2 6 10 14
 3 7 11 15*/
struct mat4 {
    mat4 ();
    // note! this is entering components in ROW-major order
    mat4 (float a, float b, float c, float d,
          float e, float f, float g, float h,
          float i, float j, float k, float l,
          float mm, float n, float o, float p);
    vec4 operator* (const vec4& rhs);
    mat4 operator* (const mat4& rhs);
    mat4& operator= (const mat4& rhs);
    float m[16];
};

struct versor {
    versor ();
    versor operator/ (float rhs);
    versor operator* (float rhs);
    versor operator* (const versor& rhs);
    versor operator+ (const versor& rhs);
    float q[4];
};

void print (const vec2& v);
void print (const vec3& v);
void print (const vec4& v);
void print (const mat3& m);
void print (const mat4& m);
// vector functions
float length (const vec3& v);
float length2 (const vec3& v);
vec3 normalise (const vec3& v);
float dot (const vec3& a, const vec3& b);
vec3 cross (const vec3& a, const vec3& b);
float get_squared_dist (vec3 from, vec3 to);
float direction_to_heading (vec3 d);
vec3 heading_to_direction (float degrees);
// matrix functions
mat3 zero_mat3 ();
mat3 identity_mat3 ();
mat4 zero_mat4 ();
mat4 identity_mat4 ();
float determinant (const mat4& mm);
mat4 inverse (const mat4& mm);
mat4 transpose (const mat4& mm);
// affine functions
mat4 translate (const mat4& m, const vec3& v);
mat4 rotate_x_deg (const mat4& m, float deg);
mat4 rotate_y_deg (const mat4& m, float deg);
mat4 rotate_z_deg (const mat4& m, float deg);
mat4 scale (const mat4& m, const vec3& v);
// camera functions
mat4 look_at (const vec3& cam_pos, vec3 targ_pos, const vec3& up);
mat4 perspective (float fovy, float aspect, float near, float far);
// quaternion functions
versor quat_from_axis_rad (float radians, float x, float y, float z);
versor quat_from_axis_deg (float degrees, float x, float y, float z);
mat4 quat_to_mat4 (const versor& q);
float dot (const versor& q, const versor& r);
versor slerp (const versor& q, const versor& r);
// stupid overloading wouldn't let me use const
versor normalise (versor& q);
void print (const versor& q);
versor slerp (versor& q, versor& r, float t);

void QuatFromAngle(float* quaternion, vec3& rotations);

void CreateVersor(float* q, float a, float x, float y, float z);
void QuatToMat4(float* m, float* q);
void MultQuatQuat(float* result, float* r, float* s);
void NormalizeQuat(float* q);

#endif

//#include "graphicsmath.h"
#include <stdio.h>


/*--------------------------------CONSTRUCTORS--------------------------------*/
vec2::vec2 () {}

vec2::vec2 (float x, float y) {
    v[0] = x;
    v[1] = y;
}

vec3::vec3 () {}

vec3::vec3 (float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

vec3::vec3 (const vec2& vv, float z) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = z;
}

vec3::vec3 (const vec4& vv) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = vv.v[2];
}

vec4::vec4 () {}

vec4::vec4 (float x, float y, float z, float w) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
}

vec4::vec4 (const vec2& vv, float z, float w) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = z;
    v[3] = w;
}

vec4::vec4 (const vec3& vv, float w) {
    v[0] = vv.v[0];
    v[1] = vv.v[1];
    v[2] = vv.v[2];
    v[3] = w;
}

mat3::mat3 () {}

/* note: entered in COLUMNS */
mat3::mat3 (float a, float b, float c,
            float d, float e, float f,
            float g, float h, float i) {
    m[0] = a;
    m[1] = b;
    m[2] = c;
    m[3] = d;
    m[4] = e;
    m[5] = f;
    m[6] = g;
    m[7] = h;
    m[8] = i;
}

mat4::mat4 () {}

/* note: entered in COLUMNS */
mat4::mat4 (float a, float b, float c, float d,
            float e, float f, float g, float h,
            float i, float j, float k, float l,
            float mm, float n, float o, float p) {
    m[0] = a;
    m[1] = b;
    m[2] = c;
    m[3] = d;
    m[4] = e;
    m[5] = f;
    m[6] = g;
    m[7] = h;
    m[8] = i;
    m[9] = j;
    m[10] = k;
    m[11] = l;
    m[12] = mm;
    m[13] = n;
    m[14] = o;
    m[15] = p;
}

/*-----------------------------PRINT FUNCTIONS--------------------------------*/
void print (const vec2& v) {
    printf ("[%.2f, %.2f]\n", v.v[0], v.v[1]);
}

void print (const vec3& v) {
    printf ("[%.2f, %.2f, %.2f]\n", v.v[0], v.v[1], v.v[2]);
}

void print (const vec4& v) {
    printf ("[%.2f, %.2f, %.2f, %.2f]\n", v.v[0], v.v[1], v.v[2], v.v[3]);
}

void print (const mat3& m) {
    printf("\n");
    printf ("[%.2f][%.2f][%.2f]\n", m.m[0], m.m[3], m.m[6]);
    printf ("[%.2f][%.2f][%.2f]\n", m.m[1], m.m[4], m.m[7]);
    printf ("[%.2f][%.2f][%.2f]\n", m.m[2], m.m[5], m.m[8]);
}

void print (const mat4& m) {
    printf("\n");
    printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[0], m.m[4], m.m[8], m.m[12]);
    printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[1], m.m[5], m.m[9], m.m[13]);
    printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[2], m.m[6], m.m[10], m.m[14]);
    printf ("[%.2f][%.2f][%.2f][%.2f]\n", m.m[3], m.m[7], m.m[11], m.m[15]);
}

/*------------------------------VECTOR FUNCTIONS------------------------------*/
float length (const vec3& v) {
    return sqrt (v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2]);
}

// squared length
float length2 (const vec3& v) {
    return v.v[0] * v.v[0] + v.v[1] * v.v[1] + v.v[2] * v.v[2];
}

// note: proper spelling (hehe)
vec3 normalise (const vec3& v) {
    vec3 vb;
    float l = length (v);
    if (0.0f == l) {
        return vec3 (0.0f, 0.0f, 0.0f);
    }
    vb.v[0] = v.v[0] / l;
    vb.v[1] = v.v[1] / l;
    vb.v[2] = v.v[2] / l;
    return vb;
}

vec3 vec3::operator+ (const vec3& rhs) {
    vec3 vc;
    vc.v[0] = v[0] + rhs.v[0];
    vc.v[1] = v[1] + rhs.v[1];
    vc.v[2] = v[2] + rhs.v[2];
    return vc;
}

vec3& vec3::operator+= (const vec3& rhs) {
    v[0] += rhs.v[0];
    v[1] += rhs.v[1];
    v[2] += rhs.v[2];
    return *this; // return self
}

vec3 vec3::operator- (const vec3& rhs) {
    vec3 vc;
    vc.v[0] = v[0] - rhs.v[0];
    vc.v[1] = v[1] - rhs.v[1];
    vc.v[2] = v[2] - rhs.v[2];
    return vc;
}

vec3& vec3::operator-= (const vec3& rhs) {
    v[0] -= rhs.v[0];
    v[1] -= rhs.v[1];
    v[2] -= rhs.v[2];
    return *this;
}

vec3 vec3::operator+ (float rhs) {
    vec3 vc;
    vc.v[0] = v[0] + rhs;
    vc.v[1] = v[1] + rhs;
    vc.v[2] = v[2] + rhs;
    return vc;
}

vec3 vec3::operator- (float rhs) {
    vec3 vc;
    vc.v[0] = v[0] - rhs;
    vc.v[1] = v[1] - rhs;
    vc.v[2] = v[2] - rhs;
    return vc;
}

vec3 vec3::operator* (float rhs) {
    vec3 vc;
    vc.v[0] = v[0] * rhs;
    vc.v[1] = v[1] * rhs;
    vc.v[2] = v[2] * rhs;
    return vc;
}

vec3 vec3::operator/ (float rhs) {
    vec3 vc;
    vc.v[0] = v[0] / rhs;
    vc.v[1] = v[1] / rhs;
    vc.v[2] = v[2] / rhs;
    return vc;
}

vec3& vec3::operator*= (float rhs) {
    v[0] = v[0] * rhs;
    v[1] = v[1] * rhs;
    v[2] = v[2] * rhs;
    return *this;
}

vec3& vec3::operator= (const vec3& rhs) {
    v[0] = rhs.v[0];
    v[1] = rhs.v[1];
    v[2] = rhs.v[2];
    return *this;
}

float dot (const vec3& a, const vec3& b) {
    return a.v[0] * b.v[0] + a.v[1] * b.v[1] + a.v[2] * b.v[2];
}

vec3 cross (const vec3& a, const vec3& b) {
    float x = a.v[1] * b.v[2] - a.v[2] * b.v[1];
    float y = a.v[2] * b.v[0] - a.v[0] * b.v[2];
    float z = a.v[0] * b.v[1] - a.v[1] * b.v[0];
    return vec3 (x, y, z);
}

float get_squared_dist (vec3 from, vec3 to) {
    float x = (to.v[0] - from.v[0]) * (to.v[0] - from.v[0]);
    float y = (to.v[1] - from.v[1]) * (to.v[1] - from.v[1]);
    float z = (to.v[2] - from.v[2]) * (to.v[2] - from.v[2]);
    return x + y + z;
}

/* converts an un-normalised direction into a heading in degrees
 NB i suspect that the z is backwards here but i've used in in
 several places like this. d'oh! */
float direction_to_heading (vec3 d) {
    return atan2 (-d.v[0], -d.v[2]) * ONE_RAD_IN_DEG;
}

vec3 heading_to_direction (float degrees) {
    float rad = degrees * ONE_DEG_IN_RAD;
    return vec3 (-sinf (rad), 0.0f, -cosf (rad));
}

/*-----------------------------MATRIX FUNCTIONS-------------------------------*/
mat3 zero_mat3 () {
    return mat3 (
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f
                 );
}

mat3 identity_mat3 () {
    return mat3 (
                 1.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 1.0f
                 );
}

mat4 zero_mat4 () {
    return mat4 (
                 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 0.0f
                 );
}

mat4 identity_mat4 () {
    return mat4 (
                 1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f
                 );
}

/* mat4 array layout
 0  4  8 12
 1  5  9 13
 2  6 10 14
 3  7 11 15
 */

vec4 mat4::operator* (const vec4& rhs) {
    // 0x + 4y + 8z + 12w
    float x =
    m[0] * rhs.v[0] +
    m[4] * rhs.v[1] +
    m[8] * rhs.v[2] +
    m[12] * rhs.v[3];
    // 1x + 5y + 9z + 13w
    float y = m[1] * rhs.v[0] +
    m[5] * rhs.v[1] +
    m[9] * rhs.v[2] +
    m[13] * rhs.v[3];
    // 2x + 6y + 10z + 14w
    float z = m[2] * rhs.v[0] +
    m[6] * rhs.v[1] +
    m[10] * rhs.v[2] +
    m[14] * rhs.v[3];
    // 3x + 7y + 11z + 15w
    float w = m[3] * rhs.v[0] +
    m[7] * rhs.v[1] +
    m[11] * rhs.v[2] +
    m[15] * rhs.v[3];
    return vec4 (x, y, z, w);
}

mat4 mat4::operator* (const mat4& rhs) {
    mat4 r = zero_mat4 ();
    int r_index = 0;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            float sum = 0.0f;
            for (int i = 0; i < 4; i++) {
                sum += rhs.m[i + col * 4] * m[row + i * 4];
            }
            r.m[r_index] = sum;
            r_index++;
        }
    }
    return r;
}

mat4& mat4::operator= (const mat4& rhs) {
    for (int i = 0; i < 16; i++) {
        m[i] = rhs.m[i];
    }
    return *this;
}

// returns a scalar value with the determinant for a 4x4 matrix
// see http://www.euclideanspace.com/maths/algebra/matrix/functions/determinant/fourD/index.htm
float determinant (const mat4& mm) {
    return
    mm.m[12] * mm.m[9] * mm.m[6] * mm.m[3] -
    mm.m[8] * mm.m[13] * mm.m[6] * mm.m[3] -
    mm.m[12] * mm.m[5] * mm.m[10] * mm.m[3] +
    mm.m[4] * mm.m[13] * mm.m[10] * mm.m[3] +
    mm.m[8] * mm.m[5] * mm.m[14] * mm.m[3] -
    mm.m[4] * mm.m[9] * mm.m[14] * mm.m[3] -
    mm.m[12] * mm.m[9] * mm.m[2] * mm.m[7] +
    mm.m[8] * mm.m[13] * mm.m[2] * mm.m[7] +
    mm.m[12] * mm.m[1] * mm.m[10] * mm.m[7] -
    mm.m[0] * mm.m[13] * mm.m[10] * mm.m[7] -
    mm.m[8] * mm.m[1] * mm.m[14] * mm.m[7] +
    mm.m[0] * mm.m[9] * mm.m[14] * mm.m[7] +
    mm.m[12] * mm.m[5] * mm.m[2] * mm.m[11] -
    mm.m[4] * mm.m[13] * mm.m[2] * mm.m[11] -
    mm.m[12] * mm.m[1] * mm.m[6] * mm.m[11] +
    mm.m[0] * mm.m[13] * mm.m[6] * mm.m[11] +
    mm.m[4] * mm.m[1] * mm.m[14] * mm.m[11] -
    mm.m[0] * mm.m[5] * mm.m[14] * mm.m[11] -
    mm.m[8] * mm.m[5] * mm.m[2] * mm.m[15] +
    mm.m[4] * mm.m[9] * mm.m[2] * mm.m[15] +
    mm.m[8] * mm.m[1] * mm.m[6] * mm.m[15] -
    mm.m[0] * mm.m[9] * mm.m[6] * mm.m[15] -
    mm.m[4] * mm.m[1] * mm.m[10] * mm.m[15] +
    mm.m[0] * mm.m[5] * mm.m[10] * mm.m[15];
}

/* returns a 16-element array that is the inverse of a 16-element array (4x4
 matrix). see http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm */
mat4 inverse (const mat4& mm) {
    float det = determinant (mm);
    /* there is no inverse if determinant is zero (not likely unless scale is
     broken) */
    if (0.0f == det) {
        fprintf (stderr, "WARNING. matrix has no determinant. can not invert\n");
        return mm;
    }
    float inv_det = 1.0f / det;
    
    return mat4 (
                 inv_det * (
                            mm.m[9] * mm.m[14] * mm.m[7] - mm.m[13] * mm.m[10] * mm.m[7] +
                            mm.m[13] * mm.m[6] * mm.m[11] - mm.m[5] * mm.m[14] * mm.m[11] -
                            mm.m[9] * mm.m[6] * mm.m[15] + mm.m[5] * mm.m[10] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[13] * mm.m[10] * mm.m[3] - mm.m[9] * mm.m[14] * mm.m[3] -
                            mm.m[13] * mm.m[2] * mm.m[11] + mm.m[1] * mm.m[14] * mm.m[11] +
                            mm.m[9] * mm.m[2] * mm.m[15] - mm.m[1] * mm.m[10] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[5] * mm.m[14] * mm.m[3] - mm.m[13] * mm.m[6] * mm.m[3] +
                            mm.m[13] * mm.m[2] * mm.m[7] - mm.m[1] * mm.m[14] * mm.m[7] -
                            mm.m[5] * mm.m[2] * mm.m[15] + mm.m[1] * mm.m[6] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[9] * mm.m[6] * mm.m[3] - mm.m[5] * mm.m[10] * mm.m[3] -
                            mm.m[9] * mm.m[2] * mm.m[7] + mm.m[1] * mm.m[10] * mm.m[7] +
                            mm.m[5] * mm.m[2] * mm.m[11] - mm.m[1] * mm.m[6] * mm.m[11]
                            ),
                 inv_det * (
                            mm.m[12] * mm.m[10] * mm.m[7] - mm.m[8] * mm.m[14] * mm.m[7] -
                            mm.m[12] * mm.m[6] * mm.m[11] + mm.m[4] * mm.m[14] * mm.m[11] +
                            mm.m[8] * mm.m[6] * mm.m[15] - mm.m[4] * mm.m[10] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[8] * mm.m[14] * mm.m[3] - mm.m[12] * mm.m[10] * mm.m[3] +
                            mm.m[12] * mm.m[2] * mm.m[11] - mm.m[0] * mm.m[14] * mm.m[11] -
                            mm.m[8] * mm.m[2] * mm.m[15] + mm.m[0] * mm.m[10] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[12] * mm.m[6] * mm.m[3] - mm.m[4] * mm.m[14] * mm.m[3] -
                            mm.m[12] * mm.m[2] * mm.m[7] + mm.m[0] * mm.m[14] * mm.m[7] +
                            mm.m[4] * mm.m[2] * mm.m[15] - mm.m[0] * mm.m[6] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[4] * mm.m[10] * mm.m[3] - mm.m[8] * mm.m[6] * mm.m[3] +
                            mm.m[8] * mm.m[2] * mm.m[7] - mm.m[0] * mm.m[10] * mm.m[7] -
                            mm.m[4] * mm.m[2] * mm.m[11] + mm.m[0] * mm.m[6] * mm.m[11]
                            ),
                 inv_det * (
                            mm.m[8] * mm.m[13] * mm.m[7] - mm.m[12] * mm.m[9] * mm.m[7] +
                            mm.m[12] * mm.m[5] * mm.m[11] - mm.m[4] * mm.m[13] * mm.m[11] -
                            mm.m[8] * mm.m[5] * mm.m[15] + mm.m[4] * mm.m[9] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[12] * mm.m[9] * mm.m[3] - mm.m[8] * mm.m[13] * mm.m[3] -
                            mm.m[12] * mm.m[1] * mm.m[11] + mm.m[0] * mm.m[13] * mm.m[11] +
                            mm.m[8] * mm.m[1] * mm.m[15] - mm.m[0] * mm.m[9] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[4] * mm.m[13] * mm.m[3] - mm.m[12] * mm.m[5] * mm.m[3] +
                            mm.m[12] * mm.m[1] * mm.m[7] - mm.m[0] * mm.m[13] * mm.m[7] -
                            mm.m[4] * mm.m[1] * mm.m[15] + mm.m[0] * mm.m[5] * mm.m[15]
                            ),
                 inv_det * (
                            mm.m[8] * mm.m[5] * mm.m[3] - mm.m[4] * mm.m[9] * mm.m[3] -
                            mm.m[8] * mm.m[1] * mm.m[7] + mm.m[0] * mm.m[9] * mm.m[7] +
                            mm.m[4] * mm.m[1] * mm.m[11] - mm.m[0] * mm.m[5] * mm.m[11]
                            ),
                 inv_det * (
                            mm.m[12] * mm.m[9] * mm.m[6] - mm.m[8] * mm.m[13] * mm.m[6] -
                            mm.m[12] * mm.m[5] * mm.m[10] + mm.m[4] * mm.m[13] * mm.m[10] +
                            mm.m[8] * mm.m[5] * mm.m[14] - mm.m[4] * mm.m[9] * mm.m[14]
                            ),
                 inv_det * (
                            mm.m[8] * mm.m[13] * mm.m[2] - mm.m[12] * mm.m[9] * mm.m[2] +
                            mm.m[12] * mm.m[1] * mm.m[10] - mm.m[0] * mm.m[13] * mm.m[10] -
                            mm.m[8] * mm.m[1] * mm.m[14] + mm.m[0] * mm.m[9] * mm.m[14]
                            ),
                 inv_det * (
                            mm.m[12] * mm.m[5] * mm.m[2] - mm.m[4] * mm.m[13] * mm.m[2] -
                            mm.m[12] * mm.m[1] * mm.m[6] + mm.m[0] * mm.m[13] * mm.m[6] +
                            mm.m[4] * mm.m[1] * mm.m[14] - mm.m[0] * mm.m[5] * mm.m[14]
                            ),
                 inv_det * (
                            mm.m[4] * mm.m[9] * mm.m[2] - mm.m[8] * mm.m[5] * mm.m[2] +
                            mm.m[8] * mm.m[1] * mm.m[6] - mm.m[0] * mm.m[9] * mm.m[6] -
                            mm.m[4] * mm.m[1] * mm.m[10] + mm.m[0] * mm.m[5] * mm.m[10]
                            )
                 );
}

// returns a 16-element array flipped on the main diagonal
mat4 transpose (const mat4& mm) {
    return mat4 (
                 mm.m[0], mm.m[4], mm.m[8], mm.m[12],
                 mm.m[1], mm.m[5], mm.m[9], mm.m[13],
                 mm.m[2], mm.m[6], mm.m[10], mm.m[14],
                 mm.m[3], mm.m[7], mm.m[11], mm.m[15]
                 );
}

/*--------------------------AFFINE MATRIX FUNCTIONS---------------------------*/
// translate a 4d matrix with xyz array
mat4 translate (const mat4& m, const vec3& v) {
    mat4 m_t = identity_mat4 ();
    m_t.m[12] = v.v[0];
    m_t.m[13] = v.v[1];
    m_t.m[14] = v.v[2];
    return m_t * m;
}

// rotate around x axis by an angle in degrees
mat4 rotate_x_deg (const mat4& m, float deg) {
    // convert to radians
    float rad = deg * ONE_DEG_IN_RAD;
    mat4 m_r = identity_mat4 ();
    m_r.m[5] = cos (rad);
    m_r.m[9] = -sin (rad);
    m_r.m[6] = sin (rad);
    m_r.m[10] = cos (rad);
    return m_r * m;
}

// rotate around y axis by an angle in degrees
mat4 rotate_y_deg (const mat4& m, float deg) {
    // convert to radians
    float rad = deg * ONE_DEG_IN_RAD;
    mat4 m_r = identity_mat4 ();
    m_r.m[0] = cos (rad);
    m_r.m[8] = sin (rad);
    m_r.m[2] = -sin (rad);
    m_r.m[10] = cos (rad);
    return m_r * m;
}

// rotate around z axis by an angle in degrees
mat4 rotate_z_deg (const mat4& m, float deg) {
    // convert to radians
    float rad = deg * ONE_DEG_IN_RAD;
    mat4 m_r = identity_mat4 ();
    m_r.m[0] = cos (rad);
    m_r.m[4] = -sin (rad);
    m_r.m[1] = sin (rad);
    m_r.m[5] = cos (rad);
    return m_r * m;
}

// scale a matrix by [x, y, z]
mat4 scale (const mat4& m, const vec3& v) {
    mat4 a = identity_mat4 ();
    a.m[0] = v.v[0];
    a.m[5] = v.v[1];
    a.m[10] = v.v[2];
    return a * m;
}

/*-----------------------VIRTUAL CAMERA MATRIX FUNCTIONS----------------------*/
// returns a view matrix using the opengl lookAt style. COLUMN ORDER.
mat4 look_at (const vec3& cam_pos, vec3 targ_pos, const vec3& up) {
    // inverse translation
    mat4 p = identity_mat4 ();
    p = translate (p, vec3 (-cam_pos.v[0], -cam_pos.v[1], -cam_pos.v[2]));
    // distance vector
    vec3 d = targ_pos - cam_pos;
    // forward vector
    vec3 f = normalise (d);
    // right vector
    vec3 r = normalise (cross (f, up));
    // real up vector
    vec3 u = normalise (cross (r, f));
    mat4 ori = identity_mat4 ();
    ori.m[0] = r.v[0];
    ori.m[4] = r.v[1];
    ori.m[8] = r.v[2];
    ori.m[1] = u.v[0];
    ori.m[5] = u.v[1];
    ori.m[9] = u.v[2];
    ori.m[2] = -f.v[0];
    ori.m[6] = -f.v[1];
    ori.m[10] = -f.v[2];
    
    return ori * p;//p * ori;
}

// returns a perspective function mimicking the opengl projection style.
mat4 perspective (float fovy, float aspect, float near, float far) {
    float fov_rad = fovy * ONE_DEG_IN_RAD;
    float range = tan (fov_rad / 2.0f) * near;
    float sx = (2.0f * near) / (range * aspect + range * aspect);
    float sy = near / range;
    float sz = -(far + near) / (far - near);
    float pz = -(2.0f * far * near) / (far - near);
    mat4 m = zero_mat4 (); // make sure bottom-right corner is zero
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    m.m[14] = pz;
    m.m[11] = -1.0f;
    return m;
}

/*----------------------------HAMILTON IN DA HOUSE!---------------------------*/
versor::versor () { }

versor versor::operator/ (float rhs) {
    versor result;
    result.q[0] = q[0] / rhs;
    result.q[1] = q[1] / rhs;
    result.q[2] = q[2] / rhs;
    result.q[3] = q[3] / rhs;
    return result;
}

versor versor::operator* (float rhs) {
    versor result;
    result.q[0] = q[0] * rhs;
    result.q[1] = q[1] * rhs;
    result.q[2] = q[2] * rhs;
    result.q[3] = q[3] * rhs;
    return result;
}

void print (const versor& q) {
    printf ("[%.2f ,%.2f, %.2f, %.2f]\n", q.q[0], q.q[1], q.q[2], q.q[3]);
}

versor versor::operator* (const versor& rhs) {
    versor result;
    result.q[0] = rhs.q[0] * q[0] - rhs.q[1] * q[1] -
    rhs.q[2] * q[2] - rhs.q[3] * q[3];
    result.q[1] = rhs.q[0] * q[1] + rhs.q[1] * q[0] -
    rhs.q[2] * q[3] + rhs.q[3] * q[2];
    result.q[2] = rhs.q[0] * q[2] + rhs.q[1] * q[3] +
    rhs.q[2] * q[0] - rhs.q[3] * q[1];
    result.q[3] = rhs.q[0] * q[3] - rhs.q[1] * q[2] +
    rhs.q[2] * q[1] + rhs.q[3] * q[0];
    // re-normalise in case of mangling
    return normalise (result);
}

versor versor::operator+ (const versor& rhs) {
    versor result;
    result.q[0] = rhs.q[0] + q[0];
    result.q[1] = rhs.q[1] + q[1];
    result.q[2] = rhs.q[2] + q[2];
    result.q[3] = rhs.q[3] + q[3];
    // re-normalise in case of mangling
    return normalise (result);
}

versor quat_from_axis_rad (float radians, float x, float y, float z) {
    versor result;
    result.q[0] = cos (radians / 2.0);
    result.q[1] = sin (radians / 2.0) * x;
    result.q[2] = sin (radians / 2.0) * y;
    result.q[3] = sin (radians / 2.0) * z;
    return result;
}

versor quat_from_axis_deg (float degrees, float x, float y, float z) {
    return quat_from_axis_rad (ONE_DEG_IN_RAD * degrees, x, y, z);
}

mat4 quat_to_mat4 (const versor& q) {
    float w = q.q[0];
    float x = q.q[1];
    float y = q.q[2];
    float z = q.q[3];
    return mat4 (
                 1.0f - 2.0f * y * y - 2.0f * z * z,
                 2.0f * x * y + 2.0f * w * z,
                 2.0f * x * z - 2.0f * w * y,
                 0.0f,
                 2.0f * x * y - 2.0f * w * z,
                 1.0f - 2.0f * x * x - 2.0f * z * z,
                 2.0f * y * z + 2.0f * w * x,
                 0.0f,
                 2.0f * x * z + 2.0f * w * y,
                 2.0f * y * z - 2.0f * w * x,
                 1.0f - 2.0f * x * x - 2.0f * y * y,
                 0.0f,
                 0.0f,
                 0.0f,
                 0.0f,
                 1.0f
                 );
}

versor normalise (versor& q) {
    // norm(q) = q / magnitude (q)
    // magnitude (q) = sqrt (w*w + x*x...)
    // only compute sqrt if interior sum != 1.0
    float sum =
    q.q[0] * q.q[0] + q.q[1] * q.q[1] +
    q.q[2] * q.q[2] + q.q[3] * q.q[3];
    // NB: floats have min 6 digits of precision
    const float thresh = 0.0001f;
    if (fabs (1.0f - sum) < thresh) {
        return q;
    }
    float mag = sqrt (sum);
    return q / mag;
}

float dot (const versor& q, const versor& r) {
    return q.q[0] * r.q[0] + q.q[1] * r.q[1] + q.q[2] * r.q[2] + q.q[3] * r.q[3];
}

versor slerp (versor& q, versor& r, float t) {
    // angle between q0-q1
    float cos_half_theta = dot (q, r);
    // as found here http://stackoverflow.com/questions/2886606/flipping-issue-when-interpolating-rotations-using-quaternions
    // if dot product is negative then one quaternion should be negated, to make
    // it take the short way around, rather than the long way
    // yeah! and furthermore Susan, I had to recalculate the d.p. after this
    if (cos_half_theta < 0.0f) {
        for (int i = 0; i < 4; i++) {
            q.q[i] *= -1.0f;
        }
        cos_half_theta = dot (q, r);
    }
    // if qa=qb or qa=-qb then theta = 0 and we can return qa
    if (fabs (cos_half_theta) >= 1.0f) {
        return q;
    }
    // Calculate temporary values
    float sin_half_theta = sqrt (1.0f - cos_half_theta * cos_half_theta);
    // if theta = 180 degrees then result is not fully defined
    // we could rotate around any axis normal to qa or qb
    versor result;
    if (fabs (sin_half_theta) < 0.001f) {
        for (int i = 0; i < 4; i++) {
            result.q[i] = (1.0f - t) * q.q[i] + t * r.q[i];
        }
        return result;
    }
    float half_theta = acos (cos_half_theta);
    float a = sin ((1.0f - t) * half_theta) / sin_half_theta;
    float b = sin (t * half_theta) / sin_half_theta;
    for (int i = 0; i < 4; i++) {
        result.q[i] = q.q[i] * a + r.q[i] * b;
    }
    return result;
    
}
/* create a unit quaternion q from an angle in degrees a, and an axis x,y,z */
void CreateVersor (float* q, float a, float x, float y, float z) {
    float rad = ONE_DEG_IN_RAD * a;
    q[0] = cosf (rad / 2.0f);
    q[1] = sinf (rad / 2.0f) * x;
    q[2] = sinf (rad / 2.0f) * y;
    q[3] = sinf (rad / 2.0f) * z;
}

//rotation coordinates in x,y,z
void QuatFromAngle(float* quaternion, vec3& rotations)
{
    float x=rotations.v[0];
    float y=rotations.v[1];
    float z=rotations.v[2];
    
    float rad = ONE_DEG_IN_RAD;
    quaternion[0]=cosf(rad*x/2)*cosf(rad*y/2)*cosf(rad*z/2)+sinf(rad*x/2)*sinf(rad*y/2)*sinf(rad*z/2);
    quaternion[1]=sinf(rad*x/2)*cosf(rad*y/2)*cosf(rad*z/2)-cosf(rad*x/2)*sinf(rad*y/2)*sinf(rad*z/2);
    quaternion[2]=cosf(rad*x/2)*sinf(rad*y/2)*cosf(rad*z/2)+sinf(rad*x/2)*cosf(rad*y/2)*sinf(rad*z/2);
    quaternion[3]=cosf(rad*x/2)*cosf(rad*y/2)*sinf(rad*z/2)-sinf(rad*x/2)*sinf(rad*y/2)*cosf(rad*z/2);
}

/* convert a unit quaternion q to a 4x4 matrix m */
void QuatToMat4 (float* m, float* q) {
    float w = q[0];
    float x = q[1];
    float y = q[2];
    float z = q[3];
    m[0] = 1.0f - 2.0f * y * y - 2.0f * z * z;
    m[1] = 2.0f * x * y + 2.0f * w * z;
    m[2] = 2.0f * x * z - 2.0f * w * y;
    m[3] = 0.0f;
    m[4] = 2.0f * x * y - 2.0f * w * z;
    m[5] = 1.0f - 2.0f * x * x - 2.0f * z * z;
    m[6] = 2.0f * y * z + 2.0f * w * x;
    m[7] = 0.0f;
    m[8] = 2.0f * x * z + 2.0f * w * y;
    m[9] = 2.0f * y * z - 2.0f * w * x;
    m[10] = 1.0f - 2.0f * x * x - 2.0f * y * y;
    m[11] = 0.0f;
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

/* normalise a quaternion in case it got a bit mangled */
void NormalizeQuat(float* q) {
    // norm(q) = q / magnitude (q)
    // magnitude (q) = sqrt (w*w + x*x...)
    // only compute sqrt if interior sum != 1.0
    float sum = q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3];
    // NB: floats have min 6 digits of precision
    const float thresh = 0.0001f;
    if (fabs (1.0f - sum) < thresh) {
        return;
    }
    float mag = sqrt (sum);
    for (int i = 0; i < 4; i++) {
        q[i] = q[i] / mag;
    }
}

/* multiply quaternions to get another one. result=R*S */
void MultQuatQuat(float* result, float* r, float* s) {
    result[0] = s[0] * r[0] - s[1] * r[1] -
    s[2] * r[2] - s[3] * r[3];
    result[1] = s[0] * r[1] + s[1] * r[0] -
    s[2] * r[3] + s[3] * r[2];
    result[2] = s[0] * r[2] + s[1] * r[3] +
    s[2] * r[0] - s[3] * r[1];
    result[3] = s[0] * r[3] - s[1] * r[2] +
    s[2] * r[1] + s[3] * r[0];
    // re-normalise in case of mangling
    NormalizeQuat(result);
}




//double quadraticBezierAngle(const double t, const Point2f& control1, const Point2f& control2, const Point2f& point)
//{
//    const auto invt = 1 - t;
//
//    const auto c1 = -3 * invt * invt;
//    const auto c2 = 3 * invt * invt * -6 * t * invt;
//    const auto c3 = -3 * t * t + 6 * t * invt;
//    const auto c4 = 3 * t * t;
//
//    const auto dx = (c1 * 0) + (c2 * control1.x) + (c3 * control2.x) + (c4 * point.x);
//    const auto dy = (c1 * 0) + (c2 * control1.y) + (c3 * control2.y) + (c4 * point.y);
//
//    return atan2(dx, dy);
//}
