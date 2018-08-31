/*
 HandmadeMath.h v1.6.0
 
 This is a single header file with a bunch of useful functions for game and
 graphics math operations.
 
 =============================================================================
 
 You MUST
 
 #define HANDMADE_MATH_IMPLEMENTATION
 
 in EXACTLY one C or C++ file that includes this header, BEFORE the
 include, like this:
 
 #define HANDMADE_MATH_IMPLEMENTATION
 #include "HandmadeMath.h"
 
 All other files should just #include "HandmadeMath.h" without the #define.
 
 =============================================================================
 
 To disable SSE intrinsics, you MUST
 
 #define HANDMADE_MATH_NO_SSE
 
 in EXACTLY one C or C++ file that includes this header, BEFORE the
 include, like this:
 
 #define HANDMADE_MATH_IMPLEMENTATION
 #define HANDMADE_MATH_NO_SSE
 #include "HandmadeMath.h"
 
 =============================================================================
 
 To use HandmadeMath without the CRT, you MUST
 
 #define HMM_SINF MySinF
 #define HMM_COSF MyCosF
 #define HMM_TANF MyTanF
 #define HMM_SQRTF MySqrtF
 #define HMM_EXPF MyExpF
 #define HMM_LOGF MyLogF
 #define HMM_ACOSF MyACosF
 #define HMM_ATANF MyATanF
 #define HMM_ATAN2F MYATan2F
 
 Provide your own implementations of SinF, CosF, TanF, ACosF, ATanF, ATan2F,
 ExpF, and LogF in EXACTLY one C or C++ file that includes this header,
 BEFORE the include, like this:
 
 #define HMM_SINF MySinF
 #define HMM_COSF MyCosF
 #define HMM_TANF MyTanF
 #define HMM_SQRTF MySqrtF
 #define HMM_EXPF MyExpF
 #define HMM_LOGF MyLogF
 #define HMM_ACOSF MyACosF
 #define HMM_ATANF MyATanF
 #define HMM_ATAN2F MyATan2F
 #define HANDMADE_MATH_IMPLEMENTATION
 #include "HandmadeMath.h"
 
 If you do not define all of these, HandmadeMath.h will use the
 versions of these functions that are provided by the CRT.
 
 =============================================================================
 
 Version History:
 0.2 (*) Updated documentation
 (*) Better C compliance
 (*) Prefix all handmade math functions
 (*) Better operator overloading
 0.2a
 (*) Prefixed Macros
 0.2b
 (*) Disabled warning 4201 on MSVC as it is legal is C11
 (*) Removed the f at the end of HMM_PI to get 64bit precision
 0.3
 (*) Added +=, -=, *=, /= for hmm_vec2, hmm_vec3, hmm_vec4
 0.4
 (*) SSE Optimized HMM_SqrtF
 (*) SSE Optimized HMM_RSqrtF
 (*) Removed CRT
 0.5
 (*) Added scalar multiplication and division for vectors
 and matrices
 (*) Added matrix subtraction and += for hmm_mat4
 (*) Reconciled all headers and implementations
 (*) Tidied up, and filled in a few missing operators
 0.5.1
 (*) Ensured column-major order for matrices throughout
 (*) Fixed HMM_Translate producing row-major matrices
 0.5.2
 (*) Fixed SSE code in HMM_SqrtF
 (*) Fixed SSE code in HMM_RSqrtF
 0.6
 (*) Added Unit testing
 (*) Made HMM_Power faster
 (*) Fixed possible efficiency problem with HMM_Normalize
 (*) RENAMED HMM_LengthSquareRoot to HMM_LengthSquared
 (*) RENAMED HMM_RSqrtF to HMM_RSquareRootF
 (*) RENAMED HMM_SqrtF to HMM_SquareRootF
 (*) REMOVED Inner function (user should use Dot now)
 (*) REMOVED HMM_FastInverseSquareRoot function declaration
 0.7
 (*) REMOVED HMM_LengthSquared in HANDMADE_MATH_IMPLEMENTATION (should
 use HMM_LengthSquaredVec3, or HANDMADE_MATH_CPP_MODE for function
 overloaded version)
 (*) REMOVED HMM_Length in HANDMADE_MATH_IMPLEMENTATION (should use
 HMM_LengthVec3, HANDMADE_MATH_CPP_MODE for function
 overloaded version)
 (*) REMOVED HMM_Normalize in HANDMADE_MATH_IMPLEMENTATION (should use
 HMM_NormalizeVec3, or HANDMADE_MATH_CPP_MODE for function
 overloaded version)
 (*) Added HMM_LengthSquaredVec2
 (*) Added HMM_LengthSquaredVec4
 (*) Addd HMM_LengthVec2
 (*) Added HMM_LengthVec4
 (*) Added HMM_NormalizeVec2
 (*) Added HMM_NormalizeVec4
 1.0
 (*) Lots of testing!
 1.1
 (*) Quaternion support
 (*) Added type hmm_quaternion
 (*) Added HMM_Quaternion
 (*) Added HMM_QuaternionV4
 (*) Added HMM_AddQuaternion
 (*) Added HMM_SubtractQuaternion
 (*) Added HMM_MultiplyQuaternion
 (*) Added HMM_MultiplyQuaternionF
 (*) Added HMM_DivideQuaternionF
 (*) Added HMM_InverseQuaternion
 (*) Added HMM_DotQuaternion
 (*) Added HMM_NormalizeQuaternion
 (*) Added HMM_Slerp
 (*) Added HMM_QuaternionToMat4
 (*) Added HMM_QuaternionFromAxisAngle
 1.1.1
 (*) Resolved compiler warnings on gcc and g++
 1.1.2
 (*) Fixed invalid HMMDEF's in the function definitions
 1.1.3
 (*) Fixed compile error in C mode
 1.1.4
 (*) Fixed SSE being included on platforms that don't support it
 (*) Fixed divide-by-zero errors when normalizing zero vectors.
 1.1.5
 (*) Add Width and Height to HMM_Vec2
 (*) Made it so you can supply your own SqrtF
 1.2.0
 (*) Added equality functions for HMM_Vec2, HMM_Vec3, and HMM_Vec4.
 (*) Added HMM_EqualsVec2, HMM_EqualsVec3, and HMM_EqualsVec4
 (*) Added C++ overloaded HMM_Equals for all three
 (*) Added C++ == and != operators for all three
 (*) SSE'd HMM_MultiplyMat4 (this is _WAY_ faster)
 (*) SSE'd HMM_Transpose
 1.3.0
 (*) Remove need to #define HANDMADE_MATH_CPP_MODE
 1.4.0
 (*) Fixed bug when using HandmadeMath in C mode
 (*) SSEd all vec4 operations
 (*) Removed all zero-ing
 1.5.0
 (*) Changed internal structure for better performance and inlining.
 (*) As a result, HANDMADE_MATH_NO_INLINE has been removed and no
 longer has any effect.
 1.5.1
 (*) Fixed a bug with uninitialized elements in HMM_LookAt.
 1.6.0
 (*) Added array subscript operators for vector and matrix types in
 C++. This is provided as a convenience, but be aware that it may
 incur an extra function call in unoptimized builds.
 LICENSE
 
 This software is in the public domain. Where that dedication is not
 recognized, you are granted a perpetual, irrevocable license to copy,
 distribute, and modify this file as you see fit.
 
 CREDITS
 
 Written by Zakary Strange (zak@strangedev.net && @strangezak)
 
 Functionality:
 Matt Mascarenhas (@miblo_)
 Aleph
 FieryDrake (@fierydrake)
 Gingerbill (@TheGingerBill)
 Ben Visness (@bvisness)
 Trinton Bullard (@Peliex_Dev)
 
 Fixes:
 Jeroen van Rijn (@J_vanRijn)
 Kiljacken (@Kiljacken)
 Insofaras (@insofaras)
 Daniel Gibson (@DanielGibson)
 */


/* let's figure out if SSE is really available (unless disabled anyway)
 (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
 => only use "#ifdef HANDMADE_MATH__USE_SSE" to check for SSE support below this block! */
#ifndef HANDMADE_MATH_NO_SSE

# ifdef _MSC_VER
/* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#  if defined(_M_AMD64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#   define HANDMADE_MATH__USE_SSE 1
#  endif
# else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#  ifdef __SSE__ /* they #define __SSE__ if it's supported */
#   define HANDMADE_MATH__USE_SSE 1
#  endif /*  __SSE__ */
# endif /* not _MSC_VER */

#endif /* #ifndef HANDMADE_MATH_NO_SSE */

#include <stdint.h> // This is for types

#ifdef HANDMADE_MATH__USE_SSE
#include <xmmintrin.h>
#endif

#ifndef HANDMADE_MATH_H
#define HANDMADE_MATH_H

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#ifdef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#endif

#ifdef __cplusplus
extern "C"
{
#endif
    
#define HMM_INLINE static inline
#define HMM_EXTERN extern
    
#if !defined(HMM_SINF) || !defined(HMM_COSF) || !defined(HMM_TANF) || \
!defined(HMM_SQRTF) || !defined(HMM_EXPF) || !defined(HMM_LOGF) || \
!defined(HMM_ACOSF) || !defined(HMM_ATANF)|| !defined(HMM_ATAN2F)
#include <math.h>
#endif
    
#ifndef HMM_SINF
#define HMM_SINF sinf
#endif
    
#ifndef HMM_COSF
#define HMM_COSF cosf
#endif
    
#ifndef HMM_TANF
#define HMM_TANF tanf
#endif
    
#ifndef HMM_SQRTF
#define HMM_SQRTF sqrtf
#endif
    
#ifndef HMM_EXPF
#define HMM_EXPF expf
#endif
    
#ifndef HMM_LOGF
#define HMM_LOGF logf
#endif
    
#ifndef HMM_ACOSF
#define HMM_ACOSF acosf
#endif
    
#ifndef HMM_ATANF
#define HMM_ATANF atanf
#endif
    
#ifndef HMM_ATAN2F
#define HMM_ATAN2F atan2f
#endif
    
#define HMM_PI32 3.14159265359f
#define HMM_PI 3.14159265358979323846
    
#define HMM_MIN(a, b) (a) > (b) ? (b) : (a)
#define HMM_MAX(a, b) (a) < (b) ? (b) : (a)
#define HMM_ABS(a) ((a) > 0 ? (a) : -(a))
#define HMM_MOD(a, m) ((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m))
#define HMM_SQUARE(x) ((x) * (x))
    
    typedef union hmm_vec2
    {
        struct
        {
            float X, Y;
        };
        
        struct
        {
            float U, V;
        };
        
        struct
        {
            float Left, Right;
        };
        
        struct
        {
            float Width, Height;
        };
        
        float Elements[2];
        
#ifdef __cplusplus
        inline float &operator[](int Index)
        {
            return Elements[Index];
        }
#endif
    } hmm_vec2;
    
    typedef union hmm_vec3
    {
        struct
        {
            float X, Y, Z;
        };
        
        struct
        {
            float U, V, W;
        };
        
        struct
        {
            float R, G, B;
        };
        
        struct
        {
            hmm_vec2 XY;
            float Ignored0_;
        };
        
        struct
        {
            float Ignored1_;
            hmm_vec2 YZ;
        };
        
        struct
        {
            hmm_vec2 UV;
            float Ignored2_;
        };
        
        struct
        {
            float Ignored3_;
            hmm_vec2 VW;
        };
        
        float Elements[3];
        
#ifdef __cplusplus
        inline float &operator[](int Index)
        {
            return Elements[Index];
        }
#endif
    } hmm_vec3;
    
    typedef union hmm_vec4
    {
        struct
        {
            union
            {
                hmm_vec3 XYZ;
                struct
                {
                    float X, Y, Z;
                };
            };
            
            float W;
        };
        struct
        {
            union
            {
                hmm_vec3 RGB;
                struct
                {
                    float R, G, B;
                };
            };
            
            float A;
        };
        
        struct
        {
            hmm_vec2 XY;
            float Ignored0_;
            float Ignored1_;
        };
        
        struct
        {
            float Ignored2_;
            hmm_vec2 YZ;
            float Ignored3_;
        };
        
        struct
        {
            float Ignored4_;
            float Ignored5_;
            hmm_vec2 ZW;
        };
        
        float Elements[4];
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 InternalElementsSSE;
#endif
        
#ifdef __cplusplus
        inline float &operator[](int Index)
        {
            return Elements[Index];
        }
#endif
    } hmm_vec4;
    
    typedef union hmm_mat4
    {
        float Elements[4][4];
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 Rows[4];
#endif
        
#ifdef __cplusplus
        inline hmm_vec4 operator[](const int Index)
        {
            float* col = Elements[Index];
            
            hmm_vec4 result;
            result.Elements[0] = col[0];
            result.Elements[1] = col[1];
            result.Elements[2] = col[2];
            result.Elements[3] = col[3];
            
            return result;
        }
#endif
    } hmm_mat4;
    
    typedef union hmm_quaternion
    {
        struct
        {
            union
            {
                hmm_vec3 XYZ;
                struct
                {
                    float X, Y, Z;
                };
            };
            
            float W;
        };
        
        float Elements[4];
    } hmm_quaternion;
    
    typedef int32_t hmm_bool;
    
    typedef hmm_vec2 hmm_v2;
    typedef hmm_vec3 hmm_v3;
    typedef hmm_vec4 hmm_v4;
    typedef hmm_mat4 hmm_m4;
    
    
    /*
     * Floating-point math functions
     */
    
    HMM_INLINE float HMM_SinF(float Radians)
    {
        float Result = HMM_SINF(Radians);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_CosF(float Radians)
    {
        float Result = HMM_COSF(Radians);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_TanF(float Radians)
    {
        float Result = HMM_TANF(Radians);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_ACosF(float Radians)
    {
        float Result = HMM_ACOSF(Radians);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_ATanF(float Radians)
    {
        float Result = HMM_ATANF(Radians);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_ATan2F(float Left, float Right)
    {
        float Result = HMM_ATAN2F(Left, Right);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_ExpF(float Float)
    {
        float Result = HMM_EXPF(Float);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_LogF(float Float)
    {
        float Result = HMM_LOGF(Float);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_SquareRootF(float Float)
    {
        float Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 In = _mm_set_ss(Float);
        __m128 Out = _mm_sqrt_ss(In);
        Result = _mm_cvtss_f32(Out);
#else
        Result = HMM_SQRTF(Float);
#endif
        
        return(Result);
    }
    
    HMM_INLINE float HMM_RSquareRootF(float Float)
    {
        float Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 In = _mm_set_ss(Float);
        __m128 Out = _mm_rsqrt_ss(In);
        Result = _mm_cvtss_f32(Out);
#else
        Result = 1.0f/HMM_SquareRootF(Float);
#endif
        
        return(Result);
    }
    
    HMM_EXTERN float HMM_Power(float Base, int Exponent);
    
    HMM_INLINE float HMM_PowerF(float Base, float Exponent)
    {
        float Result = HMM_EXPF(Exponent * HMM_LOGF(Base));
        
        return (Result);
    }
    
    
    /*
     * Utility functions
     */
    HMM_INLINE float HMM_ToRadians(float Degrees)
    {
        float Result = Degrees * (HMM_PI32 / 180.0f);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_Lerp(float A, float Time, float B)
    {
        float Result = (1.0f - Time) * A + Time * B;
        
        return (Result);
    }
    
    HMM_INLINE float HMM_Clamp(float Min, float Value, float Max)
    {
        float Result = Value;
        
        if(Result < Min)
        {
            Result = Min;
        }
        else if(Result > Max)
        {
            Result = Max;
        }
        
        return (Result);
    }
    
    
    /*
     * Vector initialization
     */
    
    HMM_INLINE hmm_vec2 HMM_Vec2(float X, float Y)
    {
        hmm_vec2 Result;
        
        Result.X = X;
        Result.Y = Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_Vec2i(int X, int Y)
    {
        hmm_vec2 Result;
        
        Result.X = (float)X;
        Result.Y = (float)Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_Vec3(float X, float Y, float Z)
    {
        hmm_vec3 Result;
        
        Result.X = X;
        Result.Y = Y;
        Result.Z = Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_Vec3i(int X, int Y, int Z)
    {
        hmm_vec3 Result;
        
        Result.X = (float)X;
        Result.Y = (float)Y;
        Result.Z = (float)Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_Vec4(float X, float Y, float Z, float W)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_setr_ps(X, Y, Z, W);
#else
        Result.X = X;
        Result.Y = Y;
        Result.Z = Z;
        Result.W = W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_Vec4i(int X, int Y, int Z, int W)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_setr_ps((float)X, (float)Y, (float)Z, (float)W);
#else
        Result.X = (float)X;
        Result.Y = (float)Y;
        Result.Z = (float)Z;
        Result.W = (float)W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_Vec4v(hmm_vec3 Vector, float W)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#else
        Result.XYZ = Vector;
        Result.W = W;
#endif
        
        return (Result);
    }
    
    
    /*
     * Binary vector operations
     */
    
    HMM_INLINE hmm_vec2 HMM_AddVec2(hmm_vec2 Left, hmm_vec2 Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_AddVec3(hmm_vec3 Left, hmm_vec3 Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        Result.Z = Left.Z + Right.Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_AddVec4(hmm_vec4 Left, hmm_vec4 Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_add_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        Result.Z = Left.Z + Right.Z;
        Result.W = Left.W + Right.W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_SubtractVec2(hmm_vec2 Left, hmm_vec2 Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_SubtractVec3(hmm_vec3 Left, hmm_vec3 Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_SubtractVec4(hmm_vec4 Left, hmm_vec4 Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_sub_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;
        Result.W = Left.W - Right.W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_MultiplyVec2(hmm_vec2 Left, hmm_vec2 Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_MultiplyVec2f(hmm_vec2 Left, float Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_MultiplyVec3(hmm_vec3 Left, hmm_vec3 Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;
        Result.Z = Left.Z * Right.Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_MultiplyVec3f(hmm_vec3 Left, float Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;
        Result.Z = Left.Z * Right;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_MultiplyVec4(hmm_vec4 Left, hmm_vec4 Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_mul_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
        Result.X = Left.X * Right.X;
        Result.Y = Left.Y * Right.Y;
        Result.Z = Left.Z * Right.Z;
        Result.W = Left.W * Right.W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_MultiplyVec4f(hmm_vec4 Left, float Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Right);
        Result.InternalElementsSSE = _mm_mul_ps(Left.InternalElementsSSE, Scalar);
#else
        Result.X = Left.X * Right;
        Result.Y = Left.Y * Right;
        Result.Z = Left.Z * Right;
        Result.W = Left.W * Right;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_DivideVec2(hmm_vec2 Left, hmm_vec2 Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X / Right.X;
        Result.Y = Left.Y / Right.Y;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_DivideVec2f(hmm_vec2 Left, float Right)
    {
        hmm_vec2 Result;
        
        Result.X = Left.X / Right;
        Result.Y = Left.Y / Right;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_DivideVec3(hmm_vec3 Left, hmm_vec3 Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X / Right.X;
        Result.Y = Left.Y / Right.Y;
        Result.Z = Left.Z / Right.Z;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_DivideVec3f(hmm_vec3 Left, float Right)
    {
        hmm_vec3 Result;
        
        Result.X = Left.X / Right;
        Result.Y = Left.Y / Right;
        Result.Z = Left.Z / Right;
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_DivideVec4(hmm_vec4 Left, hmm_vec4 Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        Result.InternalElementsSSE = _mm_div_ps(Left.InternalElementsSSE, Right.InternalElementsSSE);
#else
        Result.X = Left.X / Right.X;
        Result.Y = Left.Y / Right.Y;
        Result.Z = Left.Z / Right.Z;
        Result.W = Left.W / Right.W;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_DivideVec4f(hmm_vec4 Left, float Right)
    {
        hmm_vec4 Result;
        
#ifdef HANDMADE_MATH__USE_SSE
        __m128 Scalar = _mm_set1_ps(Right);
        Result.InternalElementsSSE = _mm_div_ps(Left.InternalElementsSSE, Scalar);
#else
        Result.X = Left.X / Right;
        Result.Y = Left.Y / Right;
        Result.Z = Left.Z / Right;
        Result.W = Left.W / Right;
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_bool HMM_EqualsVec2(hmm_vec2 Left, hmm_vec2 Right)
    {
        hmm_bool Result = (Left.X == Right.X && Left.Y == Right.Y);
        
        return (Result);
    }
    
    HMM_INLINE hmm_bool HMM_EqualsVec3(hmm_vec3 Left, hmm_vec3 Right)
    {
        hmm_bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);
        
        return (Result);
    }
    
    HMM_INLINE hmm_bool HMM_EqualsVec4(hmm_vec4 Left, hmm_vec4 Right)
    {
        hmm_bool Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_DotVec2(hmm_vec2 VecOne, hmm_vec2 VecTwo)
    {
        float Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_DotVec3(hmm_vec3 VecOne, hmm_vec3 VecTwo)
    {
        float Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_DotVec4(hmm_vec4 VecOne, hmm_vec4 VecTwo)
    {
        float Result;
        
        // NOTE(zak): IN the future if we wanna check what version SSE is support
        // we can use _mm_dp_ps (4.3) but for now we will use the old way.
        // Or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for SSE3
#ifdef HANDMADE_MATH__USE_SSE
        __m128 SSEResultOne = _mm_mul_ps(VecOne.InternalElementsSSE, VecTwo.InternalElementsSSE);
        __m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
        SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
        SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
        SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
        _mm_store_ss(&Result, SSEResultOne);
#else
        Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z) + (VecOne.W * VecTwo.W);
#endif
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_Cross(hmm_vec3 VecOne, hmm_vec3 VecTwo)
    {
        hmm_vec3 Result;
        
        Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
        Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
        Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);
        
        return (Result);
    }
    
    
    /*
     * Unary vector operations
     */
    
    HMM_INLINE float HMM_LengthSquaredVec2(hmm_vec2 A)
    {
        float Result = HMM_DotVec2(A, A);
        
        return(Result);
    }
    
    HMM_INLINE float HMM_LengthSquaredVec3(hmm_vec3 A)
    {
        float Result = HMM_DotVec3(A, A);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_LengthSquaredVec4(hmm_vec4 A)
    {
        float Result = HMM_DotVec4(A, A);
        
        return (Result);
    }
    
    HMM_INLINE float HMM_LengthVec2(hmm_vec2 A)
    {
        float Result = HMM_SquareRootF(HMM_LengthSquaredVec2(A));
        
        return (Result);
    }
    
    HMM_INLINE float HMM_LengthVec3(hmm_vec3 A)
    {
        float Result = HMM_SquareRootF(HMM_LengthSquaredVec3(A));
        
        return (Result);
    }
    
    HMM_INLINE float HMM_LengthVec4(hmm_vec4 A)
    {
        float Result = HMM_SquareRootF(HMM_LengthSquaredVec4(A));
        
        return(Result);
    }
    
    HMM_INLINE hmm_vec2 HMM_NormalizeVec2(hmm_vec2 A)
    {
        hmm_vec2 Result = {0};
        
        float VectorLength = HMM_LengthVec2(A);
        
        /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
        if (VectorLength != 0.0f)
        {
            Result.X = A.X * (1.0f / VectorLength);
            Result.Y = A.Y * (1.0f / VectorLength);
        }
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec3 HMM_NormalizeVec3(hmm_vec3 A)
    {
        hmm_vec3 Result = {0};
        
        float VectorLength = HMM_LengthVec3(A);
        
        /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
        if (VectorLength != 0.0f)
        {
            Result.X = A.X * (1.0f / VectorLength);
            Result.Y = A.Y * (1.0f / VectorLength);
            Result.Z = A.Z * (1.0f / VectorLength);
        }
        
        return (Result);
    }
    
    HMM_INLINE hmm_vec4 HMM_NormalizeVec4(hmm_vec4 A)
    {
        hmm_vec4 Result = {0};
        
        float VectorLength = HMM_LengthVec4(A);
        
        /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
        if (VectorLength != 0.0f)
        {
            float Multiplier = 1.0f / VectorLength;
            
#ifdef HANDMADE_MATH__USE_SSE
            __m128 SSEMultiplier = _mm_set1_ps(Multiplier);
            Result.InternalElementsSSE = _mm_mul_ps(A.InternalElementsSSE, SSEMultiplier);
#else
            Result.X = A.X * Multiplier;
            Result.Y = A.Y * Multiplier;
            Result.Z = A.Z * Multiplier;
            Result.W = A.W * Multiplier;
#endif
        }
        
        return (Result);
    }
    
    
    /*
     * SSE stuff
     */
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE __m128 HMM_LinearCombineSSE(__m128 Left, hmm_mat4 Right)
    {
        __m128 Result;
        Result = _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x00), Right.Rows[0]);
        Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x55), Right.Rows[1]));
        Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xaa), Right.Rows[2]));
        Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xff), Right.Rows[3]));
        
        return (Result);
    }
#endif
    
    
    /*
     * Matrix functions
     */
    
    HMM_INLINE hmm_mat4 HMM_Mat4(void)
    {
        hmm_mat4 Result = {0};
        
        return (Result);
    }
    
    HMM_INLINE hmm_mat4 HMM_Mat4d(float Diagonal)
    {
        hmm_mat4 Result = HMM_Mat4();
        
        Result.Elements[0][0] = Diagonal;
        Result.Elements[1][1] = Diagonal;
        Result.Elements[2][2] = Diagonal;
        Result.Elements[3][3] = Diagonal;
        
        return (Result);
    }
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE hmm_mat4 HMM_Transpose(hmm_mat4 Matrix)
    {
        hmm_mat4 Result = Matrix;
        
        _MM_TRANSPOSE4_PS(Result.Rows[0], Result.Rows[1], Result.Rows[2], Result.Rows[3]);
        
        return (Result);
    }
#else
    HMM_EXTERN hmm_mat4 HMM_Transpose(hmm_mat4 Matrix);
#endif
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE hmm_mat4 HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right)
    {
        hmm_mat4 Result;
        
        Result.Rows[0] = _mm_add_ps(Left.Rows[0], Right.Rows[0]);
        Result.Rows[1] = _mm_add_ps(Left.Rows[1], Right.Rows[1]);
        Result.Rows[2] = _mm_add_ps(Left.Rows[2], Right.Rows[2]);
        Result.Rows[3] = _mm_add_ps(Left.Rows[3], Right.Rows[3]);
        
        return (Result);
    }
#else
    HMM_EXTERN hmm_mat4 HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right);
#endif
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE hmm_mat4 HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right)
    {
        hmm_mat4 Result;
        
        Result.Rows[0] = _mm_sub_ps(Left.Rows[0], Right.Rows[0]);
        Result.Rows[1] = _mm_sub_ps(Left.Rows[1], Right.Rows[1]);
        Result.Rows[2] = _mm_sub_ps(Left.Rows[2], Right.Rows[2]);
        Result.Rows[3] = _mm_sub_ps(Left.Rows[3], Right.Rows[3]);
        
        return (Result);
    }
#else
    HMM_EXTERN hmm_mat4 HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right);
#endif
    
    HMM_EXTERN hmm_mat4 HMM_MultiplyMat4(hmm_mat4 Left, hmm_mat4 Right);
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE hmm_mat4 HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar)
    {
        hmm_mat4 Result;
        
        __m128 SSEScalar = _mm_set1_ps(Scalar);
        Result.Rows[0] = _mm_mul_ps(Matrix.Rows[0], SSEScalar);
        Result.Rows[1] = _mm_mul_ps(Matrix.Rows[1], SSEScalar);
        Result.Rows[2] = _mm_mul_ps(Matrix.Rows[2], SSEScalar);
        Result.Rows[3] = _mm_mul_ps(Matrix.Rows[3], SSEScalar);
        
        return (Result);
    }
#else
    HMM_EXTERN hmm_mat4 HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar);
#endif
    
    HMM_EXTERN hmm_vec4 HMM_MultiplyMat4ByVec4(hmm_mat4 Matrix, hmm_vec4 Vector);
    
#ifdef HANDMADE_MATH__USE_SSE
    HMM_INLINE hmm_mat4 HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar)
    {
        hmm_mat4 Result;
        
        __m128 SSEScalar = _mm_set1_ps(Scalar);
        Result.Rows[0] = _mm_div_ps(Matrix.Rows[0], SSEScalar);
        Result.Rows[1] = _mm_div_ps(Matrix.Rows[1], SSEScalar);
        Result.Rows[2] = _mm_div_ps(Matrix.Rows[2], SSEScalar);
        Result.Rows[3] = _mm_div_ps(Matrix.Rows[3], SSEScalar);
        
        return (Result);
    }
#else
    HMM_EXTERN hmm_mat4 HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar);
#endif
    
    
    /*
     * Common graphics transformations
     */
    
    HMM_INLINE hmm_mat4 HMM_Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far)
    {
        hmm_mat4 Result = HMM_Mat4();
        
        Result.Elements[0][0] = 2.0f / (Right - Left);
        Result.Elements[1][1] = 2.0f / (Top - Bottom);
        Result.Elements[2][2] = 2.0f / (Near - Far);
        Result.Elements[3][3] = 1.0f;
        
        Result.Elements[3][0] = (Left + Right) / (Left - Right);
        Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
        Result.Elements[3][2] = (Far + Near) / (Near - Far);
        
        return (Result);
    }
    
    HMM_INLINE hmm_mat4 HMM_Perspective(float FOV, float AspectRatio, float Near, float Far)
    {
        hmm_mat4 Result = HMM_Mat4();
        
        float TanThetaOver2 = HMM_TanF(FOV * (HMM_PI32 / 360.0f));
        
        Result.Elements[0][0] = 1.0f / TanThetaOver2;
        Result.Elements[1][1] = AspectRatio / TanThetaOver2;
        Result.Elements[2][3] = -1.0f;
        Result.Elements[2][2] = (Near + Far) / (Near - Far);
        Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
        Result.Elements[3][3] = 0.0f;
        
        return (Result);
    }
    
    HMM_INLINE hmm_mat4 HMM_Translate(hmm_vec3 Translation)
    {
        hmm_mat4 Result = HMM_Mat4d(1.0f);
        
        Result.Elements[3][0] = Translation.X;
        Result.Elements[3][1] = Translation.Y;
        Result.Elements[3][2] = Translation.Z;
        
        return (Result);
    }
    
    HMM_EXTERN hmm_mat4 HMM_Rotate(float Angle, hmm_vec3 Axis);
    
    HMM_INLINE hmm_mat4 HMM_Scale(hmm_vec3 Scale)
    {
        hmm_mat4 Result = HMM_Mat4d(1.0f);
        
        Result.Elements[0][0] = Scale.X;
        Result.Elements[1][1] = Scale.Y;
        Result.Elements[2][2] = Scale.Z;
        
        return (Result);
    }
    
    HMM_EXTERN hmm_mat4 HMM_LookAt(hmm_vec3 Eye, hmm_vec3 Center, hmm_vec3 Up);
    
    
    /*
     * Quaternion operations
     */
    
    HMM_INLINE hmm_quaternion HMM_Quaternion(float X, float Y, float Z, float W)
    {
        hmm_quaternion Result;
        
        Result.X = X;
        Result.Y = Y;
        Result.Z = Z;
        Result.W = W;
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_QuaternionV4(hmm_vec4 Vector)
    {
        hmm_quaternion Result;
        
        Result.X = Vector.X;
        Result.Y = Vector.Y;
        Result.Z = Vector.Z;
        Result.W = Vector.W;
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_AddQuaternion(hmm_quaternion Left, hmm_quaternion Right)
    {
        hmm_quaternion Result;
        
        Result.X = Left.X + Right.X;
        Result.Y = Left.Y + Right.Y;
        Result.Z = Left.Z + Right.Z;
        Result.W = Left.W + Right.W;
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_SubtractQuaternion(hmm_quaternion Left, hmm_quaternion Right)
    {
        hmm_quaternion Result;
        
        Result.X = Left.X - Right.X;
        Result.Y = Left.Y - Right.Y;
        Result.Z = Left.Z - Right.Z;
        Result.W = Left.W - Right.W;
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_MultiplyQuaternion(hmm_quaternion Left, hmm_quaternion Right)
    {
        hmm_quaternion Result;
        
        Result.X = (Left.X * Right.W) + (Left.Y * Right.Z) - (Left.Z * Right.Y) + (Left.W * Right.X);
        Result.Y = (-Left.X * Right.Z) + (Left.Y * Right.W) + (Left.Z * Right.X) + (Left.W * Right.Y);
        Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X) + (Left.Z * Right.W) + (Left.W * Right.Z);
        Result.W = (-Left.X * Right.X) - (Left.Y * Right.Y) - (Left.Z * Right.Z) + (Left.W * Right.W);
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_MultiplyQuaternionF(hmm_quaternion Left, float Multiplicative)
    {
        hmm_quaternion Result;
        
        Result.X = Left.X * Multiplicative;
        Result.Y = Left.Y * Multiplicative;
        Result.Z = Left.Z * Multiplicative;
        Result.W = Left.W * Multiplicative;
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_DivideQuaternionF(hmm_quaternion Left, float Dividend)
    {
        hmm_quaternion Result;
        
        Result.X = Left.X / Dividend;
        Result.Y = Left.Y / Dividend;
        Result.Z = Left.Z / Dividend;
        Result.W = Left.W / Dividend;
        
        return (Result);
    }
    
    HMM_EXTERN hmm_quaternion HMM_InverseQuaternion(hmm_quaternion Left);
    
    HMM_INLINE float HMM_DotQuaternion(hmm_quaternion Left, hmm_quaternion Right)
    {
        float Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_NormalizeQuaternion(hmm_quaternion Left)
    {
        hmm_quaternion Result;
        
        float Length = HMM_SquareRootF(HMM_DotQuaternion(Left, Left));
        Result = HMM_DivideQuaternionF(Left, Length);
        
        return (Result);
    }
    
    HMM_INLINE hmm_quaternion HMM_NLerp(hmm_quaternion Left, float Time, hmm_quaternion Right)
    {
        hmm_quaternion Result;
        
        Result.X = HMM_Lerp(Left.X, Time, Right.X);
        Result.Y = HMM_Lerp(Left.Y, Time, Right.Y);
        Result.Z = HMM_Lerp(Left.Z, Time, Right.Z);
        Result.W = HMM_Lerp(Left.W, Time, Right.W);
        
        Result = HMM_NormalizeQuaternion(Result);
        
        return (Result);
    }
    
    HMM_EXTERN hmm_quaternion HMM_Slerp(hmm_quaternion Left, float Time, hmm_quaternion Right);
    HMM_EXTERN hmm_mat4 HMM_QuaternionToMat4(hmm_quaternion Left);
    HMM_EXTERN hmm_quaternion HMM_QuaternionFromAxisAngle(hmm_vec3 Axis, float AngleOfRotation);
    
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

HMM_INLINE float HMM_Length(hmm_vec2 A)
{
    float Result = HMM_LengthVec2(A);
    
    return (Result);
}

HMM_INLINE float HMM_Length(hmm_vec3 A)
{
    float Result = HMM_LengthVec3(A);
    
    return (Result);
}

HMM_INLINE float HMM_Length(hmm_vec4 A)
{
    float Result = HMM_LengthVec4(A);
    
    return (Result);
}

HMM_INLINE float HMM_LengthSquared(hmm_vec2 A)
{
    float Result = HMM_LengthSquaredVec2(A);
    
    return (Result);
}

HMM_INLINE float HMM_LengthSquared(hmm_vec3 A)
{
    float Result = HMM_LengthSquaredVec3(A);
    
    return (Result);
}

HMM_INLINE float HMM_LengthSquared(hmm_vec4 A)
{
    float Result = HMM_LengthSquaredVec4(A);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Normalize(hmm_vec2 A)
{
    hmm_vec2 Result = HMM_NormalizeVec2(A);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Normalize(hmm_vec3 A)
{
    hmm_vec3 Result = HMM_NormalizeVec3(A);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Normalize(hmm_vec4 A)
{
    hmm_vec4 Result = HMM_NormalizeVec4(A);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Normalize(hmm_quaternion A)
{
    hmm_quaternion Result = HMM_NormalizeQuaternion(A);
    
    return (Result);
}

HMM_INLINE float HMM_Dot(hmm_vec2 VecOne, hmm_vec2 VecTwo)
{
    float Result = HMM_DotVec2(VecOne, VecTwo);
    
    return (Result);
}

HMM_INLINE float HMM_Dot(hmm_vec3 VecOne, hmm_vec3 VecTwo)
{
    float Result = HMM_DotVec3(VecOne, VecTwo);
    
    return (Result);
}

HMM_INLINE float HMM_Dot(hmm_vec4 VecOne, hmm_vec4 VecTwo)
{
    float Result = HMM_DotVec4(VecOne, VecTwo);
    
    return (Result);
}

HMM_INLINE float HMM_Dot(hmm_quaternion QuatOne, hmm_quaternion QuatTwo)
{
    float Result = HMM_DotQuaternion(QuatOne, QuatTwo);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Add(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_AddVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Add(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_AddVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Add(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_AddVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 HMM_Add(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_AddMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Add(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_AddQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Subtract(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_SubtractVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Subtract(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_SubtractVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Subtract(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_SubtractVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 HMM_Subtract(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_SubtractMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Subtract(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_SubtractQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Multiply(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_MultiplyVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Multiply(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = HMM_MultiplyVec2f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Multiply(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_MultiplyVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Multiply(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = HMM_MultiplyVec3f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Multiply(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_MultiplyVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Multiply(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = HMM_MultiplyVec4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 HMM_Multiply(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_MultiplyMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 HMM_Multiply(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = HMM_MultiplyMat4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Multiply(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = HMM_MultiplyMat4ByVec4(Matrix, Vector);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Multiply(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_MultiplyQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Multiply(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = HMM_MultiplyQuaternionF(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Divide(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_DivideVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 HMM_Divide(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = HMM_DivideVec2f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Divide(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_DivideVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 HMM_Divide(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = HMM_DivideVec3f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Divide(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_DivideVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 HMM_Divide(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = HMM_DivideVec4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 HMM_Divide(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = HMM_DivideMat4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion HMM_Divide(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = HMM_DivideQuaternionF(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_bool HMM_Equals(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_bool Result = HMM_EqualsVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_bool HMM_Equals(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_bool Result = HMM_EqualsVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_bool HMM_Equals(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_bool Result = HMM_EqualsVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator+(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_AddVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator+(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_AddVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator+(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_AddVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator+(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_AddMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator+(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_AddQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator-(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_SubtractVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator-(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_SubtractVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator-(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_SubtractVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator-(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_SubtractMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator-(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_SubtractQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator*(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_MultiplyVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator*(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_MultiplyVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator*(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_MultiplyVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator*(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_MultiplyMat4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator*(hmm_quaternion Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_MultiplyQuaternion(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator*(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = HMM_MultiplyVec2f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator*(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = HMM_MultiplyVec3f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator*(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = HMM_MultiplyVec4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator*(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = HMM_MultiplyMat4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator*(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = HMM_MultiplyQuaternionF(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator*(float Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_MultiplyVec2f(Right, Left);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator*(float Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_MultiplyVec3f(Right, Left);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator*(float Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_MultiplyVec4f(Right, Left);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator*(float Left, hmm_mat4 Right)
{
    hmm_mat4 Result = HMM_MultiplyMat4f(Right, Left);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator*(float Left, hmm_quaternion Right)
{
    hmm_quaternion Result = HMM_MultiplyQuaternionF(Right, Left);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator*(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result = HMM_MultiplyMat4ByVec4(Matrix, Vector);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator/(hmm_vec2 Left, hmm_vec2 Right)
{
    hmm_vec2 Result = HMM_DivideVec2(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator/(hmm_vec3 Left, hmm_vec3 Right)
{
    hmm_vec3 Result = HMM_DivideVec3(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator/(hmm_vec4 Left, hmm_vec4 Right)
{
    hmm_vec4 Result = HMM_DivideVec4(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 operator/(hmm_vec2 Left, float Right)
{
    hmm_vec2 Result = HMM_DivideVec2f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec3 operator/(hmm_vec3 Left, float Right)
{
    hmm_vec3 Result = HMM_DivideVec3f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec4 operator/(hmm_vec4 Left, float Right)
{
    hmm_vec4 Result = HMM_DivideVec4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_mat4 operator/(hmm_mat4 Left, float Right)
{
    hmm_mat4 Result = HMM_DivideMat4f(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_quaternion operator/(hmm_quaternion Left, float Right)
{
    hmm_quaternion Result = HMM_DivideQuaternionF(Left, Right);
    
    return (Result);
}

HMM_INLINE hmm_vec2 &operator+=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left + Right);
}

HMM_INLINE hmm_vec3 &operator+=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left + Right);
}

HMM_INLINE hmm_vec4 &operator+=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left + Right);
}

HMM_INLINE hmm_mat4 &operator+=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left + Right);
}

HMM_INLINE hmm_quaternion &operator+=(hmm_quaternion &Left, hmm_quaternion Right)
{
    return (Left = Left + Right);
}

HMM_INLINE hmm_vec2 &operator-=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left - Right);
}

HMM_INLINE hmm_vec3 &operator-=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left - Right);
}

HMM_INLINE hmm_vec4 &operator-=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left - Right);
}

HMM_INLINE hmm_mat4 &operator-=(hmm_mat4 &Left, hmm_mat4 Right)
{
    return (Left = Left - Right);
}

HMM_INLINE hmm_quaternion &operator-=(hmm_quaternion &Left, hmm_quaternion Right)
{
    return (Left = Left - Right);
}

HMM_INLINE hmm_vec2 &operator*=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec3 &operator*=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec4 &operator*=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec2 &operator*=(hmm_vec2 &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec3 &operator*=(hmm_vec3 &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec4 &operator*=(hmm_vec4 &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_mat4 &operator*=(hmm_mat4 &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_quaternion &operator*=(hmm_quaternion &Left, float Right)
{
    return (Left = Left * Right);
}

HMM_INLINE hmm_vec2 &operator/=(hmm_vec2 &Left, hmm_vec2 Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_vec3 &operator/=(hmm_vec3 &Left, hmm_vec3 Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_vec4 &operator/=(hmm_vec4 &Left, hmm_vec4 Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_vec2 &operator/=(hmm_vec2 &Left, float Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_vec3 &operator/=(hmm_vec3 &Left, float Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_vec4 &operator/=(hmm_vec4 &Left, float Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_mat4 &operator/=(hmm_mat4 &Left, float Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_quaternion &operator/=(hmm_quaternion &Left, float Right)
{
    return (Left = Left / Right);
}

HMM_INLINE hmm_bool operator==(hmm_vec2 Left, hmm_vec2 Right)
{
    return HMM_EqualsVec2(Left, Right);
}

HMM_INLINE hmm_bool operator==(hmm_vec3 Left, hmm_vec3 Right)
{
    return HMM_EqualsVec3(Left, Right);
}

HMM_INLINE hmm_bool operator==(hmm_vec4 Left, hmm_vec4 Right)
{
    return HMM_EqualsVec4(Left, Right);
}

HMM_INLINE hmm_bool operator!=(hmm_vec2 Left, hmm_vec2 Right)
{
    return !HMM_EqualsVec2(Left, Right);
}

HMM_INLINE hmm_bool operator!=(hmm_vec3 Left, hmm_vec3 Right)
{
    return !HMM_EqualsVec3(Left, Right);
}

HMM_INLINE hmm_bool operator!=(hmm_vec4 Left, hmm_vec4 Right)
{
    return !HMM_EqualsVec4(Left, Right);
}

#endif /* __cplusplus */

#ifdef __clang__
#pragma GCC diagnostic pop
#endif

#endif /* HANDMADE_MATH_H */

#ifdef HANDMADE_MATH_IMPLEMENTATION

float HMM_Power(float Base, int Exponent)
{
    float Result = 1.0f;
    float Mul = Exponent < 0 ? 1.f / Base : Base;
    unsigned int X = Exponent < 0 ? -Exponent : Exponent;
    while (X)
    {
        if (X & 1)
        {
            Result *= Mul;
        }
        
        Mul *= Mul;
        X >>= 1;
    }
    
    return (Result);
}

#ifndef HANDMADE_MATH__USE_SSE
hmm_mat4 HMM_Transpose(hmm_mat4 Matrix)
{
    hmm_mat4 Result;
    
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }
    
    return (Result);
}
#endif

#ifndef HANDMADE_MATH__USE_SSE
hmm_mat4 HMM_AddMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result;
    
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }
    
    return (Result);
}
#endif

#ifndef HANDMADE_MATH__USE_SSE
hmm_mat4 HMM_SubtractMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result;
    
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }
    
    return (Result);
}
#endif

hmm_mat4 HMM_MultiplyMat4(hmm_mat4 Left, hmm_mat4 Right)
{
    hmm_mat4 Result;
    
#ifdef HANDMADE_MATH__USE_SSE
    
    Result.Rows[0] = HMM_LinearCombineSSE(Right.Rows[0], Left);
    Result.Rows[1] = HMM_LinearCombineSSE(Right.Rows[1], Left);
    Result.Rows[2] = HMM_LinearCombineSSE(Right.Rows[2], Left);
    Result.Rows[3] = HMM_LinearCombineSSE(Right.Rows[3], Left);
    
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            float Sum = 0;
            int CurrentMatrice;
            for(CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
            {
                Sum += Left.Elements[CurrentMatrice][Rows] * Right.Elements[Columns][CurrentMatrice];
            }
            
            Result.Elements[Columns][Rows] = Sum;
        }
    }
#endif
    
    return (Result);
}

#ifndef HANDMADE_MATH__USE_SSE
hmm_mat4 HMM_MultiplyMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result;
    
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }
    
    return (Result);
}
#endif

hmm_vec4 HMM_MultiplyMat4ByVec4(hmm_mat4 Matrix, hmm_vec4 Vector)
{
    hmm_vec4 Result;
    
#ifdef HANDMADE_MATH__USE_SSE
    Result.InternalElementsSSE = HMM_LinearCombineSSE(Vector.InternalElementsSSE, Matrix);
#else
    int Columns, Rows;
    for(Rows = 0; Rows < 4; ++Rows)
    {
        float Sum = 0;
        for(Columns = 0; Columns < 4; ++Columns)
        {
            Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }
        
        Result.Elements[Rows] = Sum;
    }
#endif
    
    return (Result);
}

#ifndef HANDMADE_MATH__USE_SSE
hmm_mat4 HMM_DivideMat4f(hmm_mat4 Matrix, float Scalar)
{
    hmm_mat4 Result;
    
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }
    
    return (Result);
}
#endif

hmm_mat4 HMM_Rotate(float Angle, hmm_vec3 Axis)
{
    hmm_mat4 Result = HMM_Mat4d(1.0f);
    
    Axis = HMM_NormalizeVec3(Axis);
    
    float SinTheta = HMM_SinF(HMM_ToRadians(Angle));
    float CosTheta = HMM_CosF(HMM_ToRadians(Angle));
    float CosValue = 1.0f - CosTheta;
    
    Result.Elements[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
    Result.Elements[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
    Result.Elements[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);
    
    Result.Elements[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
    Result.Elements[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
    Result.Elements[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);
    
    Result.Elements[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
    Result.Elements[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
    Result.Elements[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;
    
    return (Result);
}

hmm_mat4 HMM_LookAt(hmm_vec3 Eye, hmm_vec3 Center, hmm_vec3 Up)
{
    hmm_mat4 Result;
    
    hmm_vec3 F = HMM_NormalizeVec3(HMM_SubtractVec3(Center, Eye));
    hmm_vec3 S = HMM_NormalizeVec3(HMM_Cross(F, Up));
    hmm_vec3 U = HMM_Cross(S, F);
    
    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;
    Result.Elements[0][3] = 0.0f;
    
    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;
    Result.Elements[1][3] = 0.0f;
    
    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;
    Result.Elements[2][3] = 0.0f;
    
    Result.Elements[3][0] = -HMM_DotVec3(S, Eye);
    Result.Elements[3][1] = -HMM_DotVec3(U, Eye);
    Result.Elements[3][2] = HMM_DotVec3(F, Eye);
    Result.Elements[3][3] = 1.0f;
    
    return (Result);
}

hmm_quaternion HMM_InverseQuaternion(hmm_quaternion Left)
{
    hmm_quaternion Conjugate;
    hmm_quaternion Result;
    float Norm = 0;
    float NormSquared = 0;
    
    Conjugate.X = -Left.X;
    Conjugate.Y = -Left.Y;
    Conjugate.Z = -Left.Z;
    Conjugate.W = Left.W;
    
    Norm = HMM_SquareRootF(HMM_DotQuaternion(Left, Left));
    NormSquared = Norm * Norm;
    
    Result.X = Conjugate.X / NormSquared;
    Result.Y = Conjugate.Y / NormSquared;
    Result.Z = Conjugate.Z / NormSquared;
    Result.W = Conjugate.W / NormSquared;
    
    return (Result);
}

hmm_quaternion HMM_Slerp(hmm_quaternion Left, float Time, hmm_quaternion Right)
{
    hmm_quaternion Result;
    hmm_quaternion QuaternionLeft;
    hmm_quaternion QuaternionRight;
    
    float Cos_Theta = HMM_DotQuaternion(Left, Right);
    float Angle = HMM_ACosF(Cos_Theta);
    
    float S1 = HMM_SinF((1.0f - Time) * Angle);
    float S2 = HMM_SinF(Time * Angle);
    float Is = 1.0f / HMM_SinF(Angle);
    
    QuaternionLeft = HMM_MultiplyQuaternionF(Left, S1);
    QuaternionRight = HMM_MultiplyQuaternionF(Right, S2);
    
    Result = HMM_AddQuaternion(QuaternionLeft, QuaternionRight);
    Result = HMM_MultiplyQuaternionF(Result, Is);
    
    return (Result);
}

hmm_mat4 HMM_QuaternionToMat4(hmm_quaternion Left)
{
    hmm_mat4 Result;
    Result = HMM_Mat4d(1);
    
    hmm_quaternion NormalizedQuaternion = HMM_NormalizeQuaternion(Left);
    
    float XX, YY, ZZ,
    XY, XZ, YZ,
    WX, WY, WZ;
    
    XX = NormalizedQuaternion.X * NormalizedQuaternion.X;
    YY = NormalizedQuaternion.Y * NormalizedQuaternion.Y;
    ZZ = NormalizedQuaternion.Z * NormalizedQuaternion.Z;
    XY = NormalizedQuaternion.X * NormalizedQuaternion.Y;
    XZ = NormalizedQuaternion.X * NormalizedQuaternion.Z;
    YZ = NormalizedQuaternion.Y * NormalizedQuaternion.Z;
    WX = NormalizedQuaternion.W * NormalizedQuaternion.X;
    WY = NormalizedQuaternion.W * NormalizedQuaternion.Y;
    WZ = NormalizedQuaternion.W * NormalizedQuaternion.Z;
    
    Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
    Result.Elements[0][1] = 2.0f * (XY + WZ);
    Result.Elements[0][2] = 2.0f * (XZ - WY);
    
    Result.Elements[1][0] = 2.0f * (XY - WZ);
    Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
    Result.Elements[1][2] = 2.0f * (YZ + WX);
    
    Result.Elements[2][0] = 2.0f * (XZ + WY);
    Result.Elements[2][1] = 2.0f * (YZ - WX);
    Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);
    
    return (Result);
}

hmm_quaternion HMM_QuaternionFromAxisAngle(hmm_vec3 Axis, float AngleOfRotation)
{
    hmm_quaternion Result;
    
    hmm_vec3 RotatedVector;
    
    float AxisNorm = 0;
    float SineOfRotation = 0;
    
    AxisNorm = HMM_SquareRootF(HMM_DotVec3(Axis, Axis));
    SineOfRotation = HMM_SinF(AngleOfRotation / 2.0f);
    RotatedVector = HMM_MultiplyVec3f(Axis, SineOfRotation);
    
    Result.W = HMM_CosF(AngleOfRotation / 2.0f);
    Result.XYZ = HMM_DivideVec3f(RotatedVector, AxisNorm);
    
    return (Result);
}

#endif /* HANDMADE_MATH_IMPLEMENTATION */






/*
 :::    :::  ::::::::                  :::   :::       ::: ::::::::::: :::    :::
 :+:    :+: :+:    :+:                :+:+: :+:+:    :+: :+:   :+:     :+:    :+:
 +:+  +:+  +:+    +:+               +:+ +:+:+ +:+  +:+   +:+  +:+     +:+    +:+
 +#++:+   +#+    +:+ +#++:++#++:++ +#+  +:+  +#+ +#++:++#++: +#+     +#++:++#++
 +#+  +#+  +#+    +#+               +#+       +#+ +#+     +#+ +#+     +#+    +#+
 #+#    #+# #+#    #+#               #+#       #+# #+#     #+# #+#     #+#    #+#
 ###    ###  ########                ###       ### ###     ### ###     ###    ###
 v. alpha
 Fast math for game developers. No headaches, no cruft.
 !! Warnings
 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 - xo-math is in alpha. Contribute, test, but don't integrate yet.
 - Documentation does not exist yet.
 - Source code is untested.
 // Contributing
 //////////////////////////////////////////////////////////////////////////////////////////
 - There is no contributing guide yet.
 - Basically: keep it simple.
 - Repo: https://github.com/xoorath/xo-math
 // About
 //////////////////////////////////////////////////////////////////////////////////////////
 xo-math is being developed by Jared Thomson (better known as Xoorath) in an effort to
 make games a little faster and a little easier to make. Twitter: @xoorath
 xo-math is pronounced non-phonetically "ex oh math", and spelled without
 capitalization where fonts permit.
 // License
 //////////////////////////////////////////////////////////////////////////////////////////
 See also: third-party-licenses.h
 Copyright 2018 Jared Thomson
 Permission is hereby granted, free of charge, to any person obtaining a copy of this
 software and associated documentation files (the "Software"), to deal in the Software
 without restriction, including without limitation the rights to use, copy, modify,
 merge, publish, distribute, sub license, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to the following
 conditions:
 The above copyright notice and this permission notice shall be included in all copies
 or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include <inttypes.h>
#include <limits>
////////////////////////////////////////////////////////////////////////////////////////// xo-math-constants.h inlined
#line 5 "xo-math-constants.h"
namespace xo{
    
    // please read about epsilon before using it
    // see: http://realtimecollisiondetection.net/blog/?p=89
    constexpr float MachineEpsilon = std::numeric_limits<float>::epsilon();
    
    constexpr float Deg2Rad = 0.0174532925f;
    constexpr float Rad2Deg = 57.2957795f;
    
} // ::xo

////////////////////////////////////////////////////////////////////////////////////////// end xo-math-constants.h inline
////////////////////////////////////////////////////////////////////////////////////////// xo-math-macros.h inlined
#line 4 "xo-math-macros.h"
#include <new.h>
#include <cstdlib>
// xo-math calling convention.
// See License in third-party-licenses.h for https://github.com/Microsoft/DirectXMath
// applies to the exact version checking for __vectorcall
#if defined(_MSC_VER) && !defined(_M_ARM) && \
(((_MSC_FULL_VER >= 170065501) && (_MSC_VER < 1800)) || (_MSC_FULL_VER >= 180020418))
#   define XO_CC __vectorcall
#else
#   define XO_CC
#endif

#if defined(_MSC_VER)
#   define XO_INL __forceinline
#elif defined(__clang__) || defined (__GNUC__)
#   define XO_INL __attribute__((always_inline)) inline
#else
#   define XO_INL inline
#endif

#define XO_ALN_16               alignas(16)
#define XO_ALN_16_MALLOC(size)  _aligned_malloc(size, 16)
#define XO_ALN_16_FREE(mem)     free(mem)

// will never call a constructor, as it's intended for our math types...
#define XO_NEW_DEL_16(typeName) \
void* operator new(size_t count) { \
void* m = XO_ALN_16_MALLOC(count); \
return static_cast<typeName*>(m); \
} \
void* operator new[](size_t count) { \
void* m = XO_ALN_16_MALLOC(count*sizeof(typeName)); \
return static_cast<typeName*>(m); \
}

#define XO_UNUSED(code) (void)code
////////////////////////////////////////////////////////////////////////////////////////// end xo-math-macros.h inline
////////////////////////////////////////////////////////////////////////////////////////// xo-math-utilities.h inlined
#line 7 "xo-math-utilities.h"
namespace xo
{
    template<typename T> constexpr XO_INL T Abs(T num)          { return num >= 0 ? num : -num; }
    template<typename T> constexpr XO_INL T Max(T a, T b)       { return a > b ? a : b; }
    template<typename T> constexpr XO_INL T Max(T a, T b, T c)  { return Max(Max(a, b), c); }
    template<typename T> constexpr XO_INL T Min(T a, T b)       { return a < b ? a : b; }
    template<typename T> constexpr XO_INL T Min(T a, T b, T c)  { return Min(Min(a, b), c); }
    
    constexpr XO_INL float Clamp(float val, float minVal, float maxVal) {
        return Max(Min(val, maxVal), minVal);
    }
    
    float WrapMinMax(float val, float minVal, float maxVal);
    
    constexpr XO_INL float Lerp(float start, float end, float t) {
        return start + t * (end-start);
    }
    
    constexpr XO_INL float RelativeEpsilon(float a)          { return MachineEpsilon * Max(1.f, Abs(a)); }
    constexpr XO_INL float RelativeEpsilon(float a, float b) { return MachineEpsilon * Max(1.f, Abs(a), Abs(b)); }
    
    // See: http://realtimecollisiondetection.net/blog/?p=89
    // Example accuracy:
    // CloseEnough(0.00000001f, 0.00000009f) == true
    // CloseEnough(0.0000001f,  0.0000009f) == false
    constexpr XO_INL bool CloseEnough(float left, float right) {
        return Abs(left - right) <= RelativeEpsilon(left, right);
    }
    
    float Sqrt(float val);
    float Pow(float val, int power);
    template<int power> XO_INL float Pow(float val) { return Pow(val, power); }
    template<> float XO_INL Pow<2>(float val) { return val*val; }
    template<> float XO_INL Pow<3>(float val) { return val * val * val; }
    
    float Sin(float val);
    float Cos(float val);
    float ASin(float val);
    float ACos(float val);
    void SinCos(float val, float& sinOut, float& cosOut);
    void ASinACos(float val, float& asinOut, float& acosOut);
    
#if defined(XO_MATH_IMPL)
    float WrapMinMax(float val, float minVal, float maxVal) {
        if (CloseEnough(val, minVal) || CloseEnough(val, maxVal)) {
            return val;
        }
        else if (val > 0.f) {
            return fmod(val, maxVal) + minVal;
        }
        else {
            return maxVal - fmod(Abs(val), maxVal) + minVal;
        }
    }
    
    float Sqrt(float val) { return std::sqrt(val); }
    float Pow(float val, int power) { return std::pow(val, power); }
    float Sin(float val) { return std::sin(val); }
    float Cos(float val) { return std::cos(val); }
    float ASin(float val) { return std::asin(val); }
    float ACos(float val) { return std::acos(val); }
    
    void SinCos(float val, float& sinOut, float& cosOut) {
        sinOut = Sin(val);
        cosOut = Cos(val);
    }
    
    void ASinACos(float val, float& asinOut, float& acosOut) {
        asinOut = ASin(val);
        acosOut = ACos(val);
    }
#endif
    
    XO_INL constexpr float operator "" _deg2rad(long double num) {
        return static_cast<float>(num) * xo::Deg2Rad;
    }
    
} // ::xo

////////////////////////////////////////////////////////////////////////////////////////// end xo-math-utilities.h inline
////////////////////////////////////////////////////////////////////////////////////////// xo-math-detect-simd.h inlined
#line 4 "xo-math-detect-simd.h"
namespace xo { namespace simd {
    
#define XO_SSE_NONE 0x00
#define XO_SSE1     0x10
#define XO_SSE2     0x20
#define XO_SSE3     0x30
#define XO_SSSE3    0x31
#define XO_SSE4_1   0x41
#define XO_SSE4_2   0x42
#define XO_AVX      0x50
#define XO_AVX2     0x60
#define XO_AVX512   0x70
    
#if defined(_MSC_VER)
#   if defined(__AVX512__) // this define is a guess.
#       define XO_SSE_CURRENT XO_AVX512
#   elif defined(__AVX2__)
#       define XO_SSE_CURRENT XO_AVX2
#   elif defined(__AVX__)
#       define XO_SSE_CURRENT XO_AVX
#   elif defined(_M_IX86_FP)
#       if _M_IX86_FP == 1
#           define XO_SSE_CURRENT XO_SSE1
#       elif _M_IX86_FP == 2
#           define XO_SSE_CURRENT XO_SSE2
#       else
#           define XO_SSE_CURRENT XO_SSE1
#       endif
#   else
#       define XO_SSE_CURRENT XO_SSE_NONE
#       define XO_HAS_SSE 0
#   endif
#elif defined(__clang__) || defined (__GNUC__)
#   if defined(__AVX512__) || defined(__AVX512F__)
#       define XO_SSE_CURRENT XO_AVX512
#   elif defined(__AVX2__)
#       define XO_SSE_CURRENT XO_AVX2
#   elif defined(__AVX__)
#       define XO_SSE_CURRENT XO_AVX
#   elif defined(__SSE4_2__)
#       define XO_SSE_CURRENT XO_SSE4_2
#   elif defined(__SSE4_1__)
#       define XO_SSE_CURRENT XO_SSE4_1
#   elif defined(__SSSE3__)
#       define XO_SSE_CURRENT XO_SSSE3
#   elif defined(__SSE3__)
#       define XO_SSE_CURRENT XO_SSE3
#   elif defined(__SSE2__)
#       define XO_SSE_CURRENT XO_SSE2
#   elif defined(__SSE__)
#       define XO_SSE_CURRENT XO_SSE1
#else
#       define XO_SSE_CURRENT XO_SSE_NONE
#       define XO_HAS_SSE 0
#   endif
#else
#   define XO_SSE_CURRENT XO_SSE_NONE
#   define XO_HAS_SSE 0
#endif
    
#if !defined(XO_HAS_SSE)
#    define XO_HAS_SSE 1
#endif
    
    enum class eXO_SSE : uint8_t
    {
        eXO_SSE_NONE    = XO_SSE_NONE,
        eXO_SSE1        = XO_SSE1,
        eXO_SSE2        = XO_SSE2,
        eXO_SSE3        = XO_SSE3,
        eXO_SSSE3       = XO_SSSE3,
        eXO_SSE4_1      = XO_SSE4_1,
        eXO_SSE4_2      = XO_SSE4_2,
        eXO_AVX         = XO_AVX,
        eXO_AVX2        = XO_AVX2,
        eXO_AVX512      = XO_AVX512,
        eXO_SSE_CURRENT = XO_SSE_CURRENT
    };
    
    constexpr char const* SSEGetName(eXO_SSE version = eXO_SSE::eXO_SSE_CURRENT)
    {
        switch (version)
        {
            case eXO_SSE::eXO_SSE_NONE: return "none";
            case eXO_SSE::eXO_SSE1:     return "SSE1";
            case eXO_SSE::eXO_SSE2:     return "SSE2";
            case eXO_SSE::eXO_SSE3:     return "SSE3";
            case eXO_SSE::eXO_SSSE3:    return "SSSE3";
            case eXO_SSE::eXO_SSE4_1:   return "SSE4.1";
            case eXO_SSE::eXO_SSE4_2:   return "SSE4.2";
            case eXO_SSE::eXO_AVX:      return "AVX";
            case eXO_SSE::eXO_AVX2:     return "AVX2";
            case eXO_SSE::eXO_AVX512:   return "AVX512";
            default:                    return "unknown";
        }
    }
    
    constexpr char const* SSEVersionName = SSEGetName();
    
#define XO_NEON_NONE 0x00
#define XO_NEON7     0x70
    
#if XO_HAS_SSE == 0
#   if defined(_MSC_VER)
#       if defined(_M_ARM)
#           define XO_NEON_CURRENT XO_NEON7
#       else
#           define XO_NEON_CURRENT XO_NEON_NONE
#           define XO_HAS_NEON 0
#       endif
#   elif defined(__clang__) || defined (__GNUC__)
#       if defined(__arm__) && defined(__ARM_NEON__)
#           define XO_NEON_CURRENT XO_NEON7
#       else
#           define XO_NEON_CURRENT XO_NEON_NONE
#           define XO_HAS_NEON 0
#       endif
#   else
#       define XO_NEON_CURRENT XO_NEON_NONE
#       define XO_HAS_NEON 0
#   endif
#else
#   define XO_NEON_CURRENT XO_NEON_NONE
#   define XO_HAS_NEON 0
#endif
    
#if !defined(XO_HAS_NEON)
#    define XO_HAS_NEON 1
#endif
    
    enum class eXO_NEON : uint8_t
    {
        eXO_NEON_NONE    = XO_NEON_NONE,
        eXO_NEON7        = XO_NEON7,
        eXO_NEON_CURRENT = XO_NEON_CURRENT
    };
    
    constexpr char const* NEONGetName(eXO_NEON version = eXO_NEON::eXO_NEON_CURRENT)
    {
        switch (version)
        {
            case eXO_NEON::eXO_NEON_NONE: return "none";
            case eXO_NEON::eXO_NEON7:     return "v7";
            default:                      return "unknown";
        }
    }
    
    constexpr char const* NEONVersionName = NEONGetName();
    
} } // ::xo::simd
////////////////////////////////////////////////////////////////////////////////////////// end xo-math-detect-simd.h inline

// As an end user you can configure these values
#define XO_CONFIG_LEFT_HANDED 1
#define XO_CONFIG_Y_UP 1
#define XO_CONFIG_DEFAULT_NEAR_PLANE 0.1f
#define XO_CONFIG_DEFAULT_FAR_PLANE 1000.f

// These configs can set themselves up based on the other configs above...
#define XO_CONFIG_RIGHT_HANDED (XO_CONFIG_LEFT_HANDED == 0 ? 1 : 0)
#define XO_CONFIG_Z_UP (XO_CONFIG_Y_UP == 0 ? 1 : 0)

#if XO_SSE_CURRENT >= XO_SSE4_1
////////////////////////////////////////////////////////////////////////////////////////// xo-math-sse4.h inlined
#line 5 "xo-math-sse4.h"
namespace xo {
    
} // ::xo
////////////////////////////////////////////////////////////////////////////////////////// end xo-math-sse4.h inline
#else
////////////////////////////////////////////////////////////////////////////////////////// xo-math-reference.h inlined
#line 18 "xo-math-reference.h"
#if !defined(XO_CONFIG_DEFAULT_NEAR_PLANE)
#   define XO_CONFIG_DEFAULT_NEAR_PLANE 0.1f
#endif
#if !defined(XO_CONFIG_DEFAULT_FAR_PLANE)
#   define XO_CONFIG_DEFAULT_FAR_PLANE 1000.f
#endif

#define XO_REF_ALN                  XO_ALN_16
#define XO_REF_NEW_DEL(typeName)    XO_NEW_DEL_16(typeName)

namespace xo {
    //////////////////////////////////////////////////////////////////////////////////////////
    struct Vector3 {
        float x, y, z;
        constexpr Vector3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
        { }
        
        constexpr explicit Vector3(float all)
        : x(all)
        , y(all)
        , z(all)
        { }
        
        Vector3() = default;
        ~Vector3() = default;
        Vector3(Vector3 const& other) = default;
        Vector3(Vector3&& ref) = default;
        Vector3& operator = (Vector3 const& other) = default;
        Vector3& operator = (Vector3&& ref) = default;
        
        Vector3 XO_CC operator + (Vector3 const& other) const;
        Vector3 XO_CC operator - (Vector3 const& other) const;
        Vector3 XO_CC operator * (Vector3 const& other) const;
        Vector3 XO_CC operator / (Vector3 const& other) const;
        Vector3& XO_CC operator += (Vector3 const& other);
        Vector3& XO_CC operator -= (Vector3 const& other);
        Vector3& XO_CC operator *= (Vector3 const& other);
        Vector3& XO_CC operator /= (Vector3 const& other);
        
        Vector3 operator -() const;
        
        float Sum() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        
        Vector3& Normalize();
        Vector3 Normalized() const;
        
        static bool XO_CC RoughlyEqual(Vector3 const& left, Vector3 const& right);
        static bool XO_CC ExactlyEqual(Vector3 const& left, Vector3 const& right);
        static bool XO_CC RoughlyEqual(Vector3 const& left, float magnitude);
        static bool XO_CC ExactlyEqual(Vector3 const& left, float magnitude);
        
        static float XO_CC DotProduct(Vector3 const& left, Vector3 const& right);
        static Vector3 XO_CC CrossProduct(Vector3 const& left, Vector3 const& right);
        static Vector3 XO_CC Lerp(Vector3 const& left, Vector3 const& right, float t);
        static float XO_CC DistanceSquared(Vector3 const& left, Vector3 const& right);
        static float XO_CC Distance(Vector3 const& left, Vector3 const& right);
        
        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 Up;
        static const Vector3 Down;
        static const Vector3 Left;
        static const Vector3 Right;
        static const Vector3 Forward;
        static const Vector3 Backward;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    struct Vector4 {
        union {
            struct { float x, y, z, w; };
            float v[4];
        };
        constexpr Vector4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
        { }
        
        constexpr explicit Vector4(float all)
        : x(all)
        , y(all)
        , z(all)
        , w(all)
        { }
        
        Vector4() = default;
        ~Vector4() = default;
        Vector4(Vector4 const& other) = default;
        Vector4(Vector4&& ref) = default;
        Vector4& operator = (Vector4 const& other) = default;
        Vector4& operator = (Vector4&& ref) = default;
        
        Vector4 XO_CC operator + (Vector4 const& other) const;
        Vector4 XO_CC operator - (Vector4 const& other) const;
        Vector4 XO_CC operator * (Vector4 const& other) const;
        Vector4 XO_CC operator / (Vector4 const& other) const;
        Vector4& XO_CC operator += (Vector4 const& other);
        Vector4& XO_CC operator -= (Vector4 const& other);
        Vector4& XO_CC operator *= (Vector4 const& other);
        Vector4& XO_CC operator /= (Vector4 const& other);
        
        Vector4 operator -() const;
        
        float operator[] (int index) const;
        float& operator[] (int index);
        
        float Sum() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        Vector4 Normalized() const;
        Vector4& Normalize();
        
        static bool XO_CC RoughlyEqual(Vector4 const& left, Vector4 const& right);
        static bool XO_CC ExactlyEqual(Vector4 const& left, Vector4 const& right);
        static bool XO_CC RoughlyEqual(Vector4 const& left, float magnitude);
        static bool XO_CC ExactlyEqual(Vector4 const& left, float magnitude);
        
        static float XO_CC DotProduct(Vector4 const& left, Vector4 const& right);
        static Vector4 XO_CC Lerp(Vector4 const& left, Vector4 const& right, float t);
        
        static const Vector4 Zero;
        static const Vector4 One;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    struct Matrix4x4 {
        union {
            Vector4 rows[4];
            float v[16];
        };
        constexpr Matrix4x4(Vector4 const rows[4])
        : rows {
            rows[0],
            rows[1],
            rows[2],
            rows[3] }
        { }
        
        constexpr Matrix4x4(Vector4 const& row0,
                            Vector4 const& row1,
                            Vector4 const& row2,
                            Vector4 const& row3)
        : rows{
            row0,
            row1,
            row2,
            row3 }
        { }
        
        constexpr explicit Matrix4x4(float all)
        : rows{
            Vector4(all),
            Vector4(all),
            Vector4(all),
            Vector4(all) }
        { }
        
        Matrix4x4() = default;
        ~Matrix4x4() = default;
        Matrix4x4(Matrix4x4 const& other) = default;
        Matrix4x4(Matrix4x4&& ref) = default;
        Matrix4x4& operator = (Matrix4x4 const& other) = default;
        Matrix4x4& operator = (Matrix4x4&& ref) = default;
        
        Matrix4x4 XO_CC operator * (Matrix4x4 const& other) const;
        Matrix4x4& XO_CC operator *= (Matrix4x4 const& other);
        
        Vector4 operator[] (int index) const;
        Vector4& operator[] (int index);
        
        Vector3 Up() const;
        Vector3 Down() const;
        Vector3 Left() const;
        Vector3 Right() const;
        Vector3 Forward() const;
        Vector3 Backward() const;
        
        static Matrix4x4 XO_CC Transpose(Matrix4x4 const& matrixIn);
        static Matrix4x4 XO_CC Invert(Matrix4x4 const& matrixIn);
        static bool XO_CC InvertSafe(Matrix4x4 const& matrixIn, Matrix4x4& matrixOut);
        static Matrix4x4 XO_CC Translation(Vector3 const& pos);
        static Matrix4x4 XO_CC Scale(Vector3 const& scale);
        static Matrix4x4 XO_CC RotationYaw(float yaw);
        static Matrix4x4 XO_CC RotationPitch(float pitch);
        static Matrix4x4 XO_CC RotationRoll(float roll);
        static Matrix4x4 XO_CC RotationYawPitchRoll(float yaw, float pitch, float roll);
        static Matrix4x4 XO_CC RotationAxisAngle(Vector3 const& axis, float angle);
        static Matrix4x4 XO_CC PerspectiveFOV(float fov,
                                              float aspect,
                                              float nearPlane = XO_CONFIG_DEFAULT_NEAR_PLANE,
                                              float farPlane = XO_CONFIG_DEFAULT_FAR_PLANE);
        static Matrix4x4 XO_CC Perspective(float width,
                                           float height,
                                           float aspect,
                                           float nearPlane = XO_CONFIG_DEFAULT_NEAR_PLANE,
                                           float farPlane = XO_CONFIG_DEFAULT_FAR_PLANE);
        static Matrix4x4 XO_CC Orthographic(float width,
                                            float height,
                                            float nearPlane,
                                            float farPlane);
        static Matrix4x4 XO_CC LookAt(Vector3 const& from,
                                      Vector3 const& to,
                                      Vector3 const& up = Vector3::Up);
        
        static bool XO_CC RoughlyEqual(Matrix4x4 const& left, Matrix4x4 const& right);
        static bool XO_CC ExactlyEqual(Matrix4x4 const& left, Matrix4x4 const& right);
        
        static const Matrix4x4 One;
        static const Matrix4x4 Zero;
        static const Matrix4x4 Identity;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    struct Quaternion {
        union {
            struct { float i, j, k, r; };
            Vector4 vec4;
        };
        
        constexpr Quaternion(float i, float j, float k, float r)
        : i(i)
        , j(j)
        , k(k)
        , r(r)
        { }
        
        constexpr explicit Quaternion(float all)
        : i(all)
        , j(all)
        , k(all)
        , r(all)
        { }
        
        constexpr explicit Quaternion(Vector4 const& v4)
        : vec4(v4)
        { }
        
        Quaternion() = default;
        ~Quaternion() = default;
        Quaternion(Quaternion const& other) = default;
        Quaternion(Quaternion&& ref) = default;
        Quaternion& operator = (Quaternion const& other) = default;
        Quaternion& operator = (Quaternion&& ref) = default;
        
        Quaternion operator + (Quaternion other) const;
        Quaternion operator * (float scalar) const;
        Quaternion operator -() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        Quaternion Normalized() const;
        Quaternion& Normalize();
        
        Matrix4x4 ToMatrix() const;
        
        static Quaternion XO_CC Invert(Quaternion const& quat);
        static Quaternion XO_CC RotationAxisAngle(Vector3 const& axis, float angle);
        static Quaternion XO_CC RotationEuler(Vector3 const& angles);
        static float XO_CC DotProduct(Quaternion const& left, Quaternion const& right);
        static Quaternion XO_CC Lerp(Quaternion const& start, Quaternion const& end, float t);
        static Quaternion XO_CC Slerp(Quaternion const& start,
                                      Quaternion const& end,
                                      float t);
        
        static bool XO_CC RoughlyEqual(Quaternion const& left, Quaternion const& right);
        static bool XO_CC ExactlyEqual(Quaternion const& left, Quaternion const& right);
        
        static const Quaternion Zero;
        static const Quaternion Identity;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // vector 3, aligned for cpu specific optimizations (where applicable)
    struct XO_REF_ALN AVector3 {
        XO_REF_NEW_DEL(AVector3);
        float x, y, z;
        constexpr AVector3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
        { }
        
        constexpr explicit AVector3(float all)
        : x(all)
        , y(all)
        , z(all)
        { }
        
        AVector3() = default;
        ~AVector3() = default;
        AVector3(AVector3 const& other) = default;
        AVector3(AVector3&& ref) = default;
        AVector3& operator = (AVector3 const& other) = default;
        AVector3& operator = (AVector3&& ref) = default;
        
        AVector3 XO_CC operator + (AVector3 const& other) const;
        AVector3 XO_CC operator - (AVector3 const& other) const;
        AVector3 XO_CC operator * (AVector3 const& other) const;
        AVector3 XO_CC operator / (AVector3 const& other) const;
        AVector3& XO_CC operator += (AVector3 const& other);
        AVector3& XO_CC operator -= (AVector3 const& other);
        AVector3& XO_CC operator *= (AVector3 const& other);
        AVector3& XO_CC operator /= (AVector3 const& other);
        
        AVector3 operator -() const;
        
        float Sum() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        
        AVector3& Normalize();
        AVector3 Normalized() const;
        
        static bool XO_CC RoughlyEqual(AVector3 const& left, AVector3 const& right);
        static bool XO_CC ExactlyEqual(AVector3 const& left, AVector3 const& right);
        static bool XO_CC RoughlyEqual(AVector3 const& left, float magnitude);
        static bool XO_CC ExactlyEqual(AVector3 const& left, float magnitude);
        
        static float XO_CC DotProduct(AVector3 const& left, AVector3 const& right);
        static AVector3 XO_CC CrossProduct(AVector3 const& left, AVector3 const& right);
        static AVector3 XO_CC Lerp(AVector3 const& left, AVector3 const& right, float t);
        static float XO_CC DistanceSquared(AVector3 const& left, AVector3 const& right);
        static float XO_CC Distance(AVector3 const& left, AVector3 const& right);
        
        static const AVector3 Zero;
        static const AVector3 One;
        static const AVector3 Up;
        static const AVector3 Down;
        static const AVector3 Left;
        static const AVector3 Right;
        static const AVector3 Forward;
        static const AVector3 Backward;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // vector 4, aligned for cpu specific optimizations (where applicable)
    struct XO_REF_ALN AVector4 {
        XO_REF_NEW_DEL(AVector4);
        union {
            struct { float x, y, z, w; };
            float v[4];
        };
        constexpr AVector4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
        { }
        
        constexpr explicit AVector4(float all)
        : x(all)
        , y(all)
        , z(all)
        , w(all)
        { }
        
        AVector4() = default;
        ~AVector4() = default;
        AVector4(AVector4 const& other) = default;
        AVector4(AVector4&& ref) = default;
        AVector4& operator = (AVector4 const& other) = default;
        AVector4& operator = (AVector4&& ref) = default;
        
        AVector4 XO_CC operator + (AVector4 const& other) const;
        AVector4 XO_CC operator - (AVector4 const& other) const;
        AVector4 XO_CC operator * (AVector4 const& other) const;
        AVector4 XO_CC operator / (AVector4 const& other) const;
        AVector4& XO_CC operator += (AVector4 const& other);
        AVector4& XO_CC operator -= (AVector4 const& other);
        AVector4& XO_CC operator *= (AVector4 const& other);
        AVector4& XO_CC operator /= (AVector4 const& other);
        
        AVector4 operator -() const;
        
        float operator[] (int index) const;
        float& operator[] (int index);
        
        float Sum() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        AVector4 Normalized() const;
        AVector4& Normalize();
        
        static bool XO_CC RoughlyEqual(AVector4 const& left, AVector4 const& right);
        static bool XO_CC ExactlyEqual(AVector4 const& left, AVector4 const& right);
        static bool XO_CC RoughlyEqual(AVector4 const& left, float magnitude);
        static bool XO_CC ExactlyEqual(AVector4 const& left, float magnitude);
        
        static float XO_CC DotProduct(AVector4 const& left, AVector4 const& right);
        static AVector4 XO_CC Lerp(AVector4 const& left, AVector4 const& right, float t);
        
        static const AVector4 Zero;
        static const AVector4 One;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // matrix4x4, aligned for cpu specific optimizations (where applicable)
    struct XO_REF_ALN AMatrix4x4 {
        XO_REF_NEW_DEL(AMatrix4x4);
        union {
            AVector4 rows[4];
            float v[16];
        };
        constexpr AMatrix4x4(AVector4 const rows[4])
        : rows{
            rows[0],
            rows[1],
            rows[2],
            rows[3] }
        { }
        
        constexpr AMatrix4x4(AVector4 const& row0,
                             AVector4 const& row1,
                             AVector4 const& row2,
                             AVector4 const& row3)
        : rows{
            row0,
            row1,
            row2,
            row3 }
        { }
        
        constexpr explicit AMatrix4x4(float all)
        : rows{
            AVector4(all),
            AVector4(all),
            AVector4(all),
            AVector4(all) }
        { }
        
        AMatrix4x4() = default;
        ~AMatrix4x4() = default;
        AMatrix4x4(AMatrix4x4 const& other) = default;
        AMatrix4x4(AMatrix4x4&& ref) = default;
        AMatrix4x4& operator = (AMatrix4x4 const& other) = default;
        AMatrix4x4& operator = (AMatrix4x4&& ref) = default;
        
        AMatrix4x4 XO_CC operator * (AMatrix4x4 const& other) const;
        AMatrix4x4& XO_CC operator *= (AMatrix4x4 const& other);
        
        AVector4 operator[] (int index) const;
        AVector4& operator[] (int index);
        
        AVector3 Up() const;
        AVector3 Down() const;
        AVector3 Left() const;
        AVector3 Right() const;
        AVector3 Forward() const;
        AVector3 Backward() const;
        
        static AMatrix4x4 XO_CC Transpose(AMatrix4x4 const& matrixIn);
        static AMatrix4x4 XO_CC Invert(AMatrix4x4 const& matrixIn);
        static bool XO_CC InvertSafe(AMatrix4x4 const& matrixIn, AMatrix4x4& matrixOut);
        static AMatrix4x4 XO_CC Translation(AVector3 const& pos);
        static AMatrix4x4 XO_CC Scale(AVector3 const& scale);
        static AMatrix4x4 XO_CC RotationYaw(float yaw);
        static AMatrix4x4 XO_CC RotationPitch(float pitch);
        static AMatrix4x4 XO_CC RotationRoll(float roll);
        static AMatrix4x4 XO_CC RotationYawPitchRoll(float yaw, float pitch, float roll);
        static AMatrix4x4 XO_CC RotationAxisAngle(AVector3 const& axis, float angle);
        static AMatrix4x4 XO_CC PerspectiveFOV(float fov,
                                               float aspect,
                                               float nearPlane = XO_CONFIG_DEFAULT_NEAR_PLANE,
                                               float farPlane = XO_CONFIG_DEFAULT_FAR_PLANE);
        static AMatrix4x4 XO_CC Perspective(float width,
                                            float height,
                                            float aspect,
                                            float nearPlane = XO_CONFIG_DEFAULT_NEAR_PLANE,
                                            float farPlane = XO_CONFIG_DEFAULT_FAR_PLANE);
        static AMatrix4x4 XO_CC Orthographic(float width,
                                             float height,
                                             float nearPlane,
                                             float farPlane);
        static AMatrix4x4 XO_CC LookAt(AVector3 const& from,
                                       AVector3 const& to,
                                       AVector3 const& up = AVector3::Up);
        
        static bool XO_CC RoughlyEqual(AMatrix4x4 const& left, AMatrix4x4 const& right);
        static bool XO_CC ExactlyEqual(AMatrix4x4 const& left, AMatrix4x4 const& right);
        
        static const AMatrix4x4 One;
        static const AMatrix4x4 Zero;
        static const AMatrix4x4 Identity;
    };
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // quaternion, aligned for cpu specific optimizations (where applicable)
    struct XO_REF_ALN AQuaternion {
        XO_REF_NEW_DEL(AQuaternion);
        union {
            struct { float i, j, k, r; };
            AVector4 vec4;
        };
        
        constexpr AQuaternion(float i, float j, float k, float r)
        : i(i)
        , j(j)
        , k(k)
        , r(r)
        { }
        
        constexpr explicit AQuaternion(float all)
        : i(all)
        , j(all)
        , k(all)
        , r(all)
        { }
        
        constexpr explicit AQuaternion(AVector4 const& v4)
        : vec4(v4)
        { }
        
        AQuaternion() = default;
        ~AQuaternion() = default;
        AQuaternion(AQuaternion const& other) = default;
        AQuaternion(AQuaternion&& ref) = default;
        AQuaternion& operator = (AQuaternion const& other) = default;
        AQuaternion& operator = (AQuaternion&& ref) = default;
        
        AQuaternion operator + (AQuaternion other) const;
        AQuaternion operator * (float scalar) const;
        AQuaternion operator -() const;
        
        float Magnitude() const;
        float MagnitudeSquared() const;
        AQuaternion Normalized() const;
        AQuaternion& Normalize();
        
        AMatrix4x4 ToMatrix() const;
        
        static AQuaternion XO_CC Invert(AQuaternion const& quat);
        static AQuaternion XO_CC RotationAxisAngle(AVector3 const& axis, float angle);
        static AQuaternion XO_CC RotationEuler(AVector3 const& angles);
        static float XO_CC DotProduct(AQuaternion const& left, AQuaternion const& right);
        static AQuaternion XO_CC Lerp(AQuaternion const& start, AQuaternion const& end, float t);
        static AQuaternion XO_CC Slerp(AQuaternion const& start,
                                       AQuaternion const& end,
                                       float t);
        
        static bool XO_CC RoughlyEqual(AQuaternion const& left, AQuaternion const& right);
        static bool XO_CC ExactlyEqual(AQuaternion const& left, AQuaternion const& right);
        
        static const AQuaternion Zero;
        static const AQuaternion Identity;
    };
    
    ////////////////////////////////////////////////////////////////////////////////////////// Vector 3
#if defined(XO_MATH_IMPL)
    /*static*/ const Vector3 Vector3::Zero(0.f);
    /*static*/ const Vector3 Vector3::One(1.f);
    /*static*/ const Vector3 Vector3::Left(-1.f, 0.f, 0.f);
    /*static*/ const Vector3 Vector3::Right(1.f, 0.f, 0.f);
    
#   if !defined(XO_CONFIG_Y_UP) || !defined(XO_CONFIG_Z_UP)
    static_assert(false,
                  "define both XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a value of 1, and\
                  the other should have a value of 0");
#   endif
    
#   if !defined(XO_CONFIG_LEFT_HANDED) || !defined(XO_CONFIG_RIGHT_HANDED)
    static_assert(false,
                  "define both XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One should have a \
                  value of 1, and the other should have a value of 0");
#   endif
    
#   if XO_CONFIG_Y_UP
    static_assert(XO_CONFIG_Z_UP == 0,
                  "XO_CONFIG_Z_UP should be 0 if XO_CONFIG_Y_UP is 1");
    /*static*/ const Vector3 Vector3::Up(0.f, 1.f, 0.f);
    /*static*/ const Vector3 Vector3::Down(0.f, -1.f, 0.f);
#       if XO_CONFIG_LEFT_HANDED
    static_assert(XO_CONFIG_RIGHT_HANDED == 0,
                  "XO_CONFIG_RIGHT_HANDED should be 0 if XO_CONFIG_LEFT_HANDED is 1");
    /*static*/ const Vector3 Vector3::Forward(0.f, 0.f, 1.f);
    /*static*/ const Vector3 Vector3::Backward(0.f, 0.f, -1.f);
#       elif XO_CONFIG_RIGHT_HANDED
    static_assert(XO_CONFIG_LEFT_HANDED == 0,
                  "XO_CONFIG_LEFT_HANDED should be 0 if XO_CONFIG_RIGHT_HANDED is 1");
    /*static*/ const Vector3 Vector3::Forward(0.f, 0.f, -1.f);
    /*static*/ const Vector3 Vector3::Backward(0.f, 0.f, 1.f);
#       else
    static_assert(false,
                  "XO_CONFIG_LEFT_HANDED or XO_CONFIG_RIGHT_HANDED should have a non zero \
                  value...");
#       endif
#   elif XO_CONFIG_Z_UP
    // no static assert here about XO_CONFIG_Y_UP, because it's been checked.
    /*static*/ const Vector3 Vector3::Up(0.f, 0.f, 1.f);
    /*static*/ const Vector3 Vector3::Down(0.f, 0.f, -1.f);
#       if XO_CONFIG_LEFT_HANDED
    static_assert(XO_CONFIG_RIGHT_HANDED == 0,
                  "XO_CONFIG_RIGHT_HANDED should be 0 if XO_CONFIG_LEFT_HANDED is 1");
    /*static*/ const Vector3 Vector3::Forward(0.f, -1.f, 0.f);
    /*static*/ const Vector3 Vector3::Backward(0.f, 1.f, 0.f);
#       elif XO_CONFIG_RIGHT_HANDED
    static_assert(XO_CONFIG_LEFT_HANDED == 0,
                  "XO_CONFIG_LEFT_HANDED should be 0 if XO_CONFIG_RIGHT_HANDED is 1");
    /*static*/ const Vector3 Vector3::Forward(0.f, 1.f, 0.f);
    /*static*/ const Vector3 Vector3::Backward(0.f, -1.f, 0.f);
#       else
    static_assert(false,
                  "XO_CONFIG_LEFT_HANDED or XO_CONFIG_RIGHT_HANDED should have a non zero \
                  value...");
#       endif
#   else
    static_assert(false,
                  "XO_CONFIG_Y_UP or XO_CONFIG_Z_UP should have a non zero value...");
#   endif
#endif
    
    XO_INL
    Vector3 XO_CC Vector3::operator + (Vector3 const& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    XO_INL
    Vector3 XO_CC Vector3::operator - (Vector3 const& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
    
    XO_INL
    Vector3 XO_CC Vector3::operator * (Vector3 const& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }
    
    XO_INL
    Vector3 XO_CC Vector3::operator / (Vector3 const& other) const {
        return Vector3(x / other.x, y / other.y, z / other.z);
    }
    
    XO_INL
    Vector3& XO_CC Vector3::operator += (Vector3 const& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    
    XO_INL
    Vector3& XO_CC Vector3::operator -= (Vector3 const& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    
    XO_INL
    Vector3& XO_CC Vector3::operator *= (Vector3 const& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }
    
    XO_INL
    Vector3& XO_CC Vector3::operator /= (Vector3 const& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }
    
    XO_INL Vector3 Vector3::operator -() const { return Vector3(-x, -y, -z); };
    
    XO_INL float Vector3::Sum() const { return x + y + z; }
    
    XO_INL float Vector3::MagnitudeSquared() const { return ((*this) * (*this)).Sum(); }
    XO_INL float Vector3::Magnitude() const { return xo::Sqrt(MagnitudeSquared()); }
    
    XO_INL Vector3& Vector3::Normalize() { return (*this) /= Vector3(Magnitude()); }
    XO_INL Vector3 Vector3::Normalized() const { return Vector3(*this).Normalize(); }
    
    /*static*/ XO_INL
    bool XO_CC Vector3::RoughlyEqual(Vector3 const& left, Vector3 const& right) {
        return CloseEnough(left.x, right.x)
        && CloseEnough(left.y, right.y)
        && CloseEnough(left.z, right.z);
    }
    
    /*static*/ XO_INL
    bool XO_CC Vector3::ExactlyEqual(Vector3 const& left, Vector3 const& right) {
        return left.x == right.x
        && left.y == right.y
        && left.z == right.z;
    }
    /*static*/ XO_INL
    bool XO_CC Vector3::RoughlyEqual(Vector3 const& left, float magnitude) {
        return CloseEnough(left.MagnitudeSquared(), Pow<2>(magnitude));
    }
    
    /*static*/ XO_INL
    bool XO_CC Vector3::ExactlyEqual(Vector3 const& left, float magnitude) {
        return left.MagnitudeSquared() == Pow<2>(magnitude);
    }
    
    /*static*/ XO_INL
    float XO_CC Vector3::DotProduct(Vector3 const& left, Vector3 const& right) {
        return (left * right).Sum();
    }
    
    /*static*/ XO_INL
    Vector3 XO_CC Vector3::CrossProduct(Vector3 const& left, Vector3 const& right) {
        return Vector3(
                       left.y * right.z - left.z * right.y,
                       left.z * right.x - left.x * right.z,
                       left.x * right.y - left.y * right.x);
    }
    
    /*static*/ XO_INL
    Vector3 XO_CC Vector3::Lerp(Vector3 const& left, Vector3 const& right, float t) {
        return left + Vector3(t) * (right - left);
    }
    
    /*static*/ XO_INL
    float XO_CC Vector3::DistanceSquared(Vector3 const& left, Vector3 const& right) {
        return (right - left).MagnitudeSquared();
    }
    
    /*static*/ XO_INL
    float XO_CC Vector3::Distance(Vector3 const& left, Vector3 const& right) {
        return (right - left).Magnitude();
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////// Vector 4
    
    XO_INL
    Vector4 XO_CC Vector4::operator + (Vector4 const& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    
    XO_INL
    Vector4 XO_CC Vector4::operator - (Vector4 const& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    XO_INL
    Vector4 XO_CC Vector4::operator * (Vector4 const& other) const {
        return Vector4(x*other.x, y*other.y, z*other.z, w*other.w);
    }
    
    XO_INL
    Vector4 XO_CC Vector4::operator / (Vector4 const& other) const {
        return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }
    
    XO_INL
    Vector4& XO_CC Vector4::operator += (Vector4 const& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    };
    
    XO_INL
    Vector4& XO_CC Vector4::operator -= (Vector4 const& other) {
        x -=other.x;
        y -=other.y;
        z -= other.z;
        w -= other.w;
        return *this; };
    
    XO_INL
    Vector4& XO_CC Vector4::operator *= (Vector4 const& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    };
    
    XO_INL
    Vector4& XO_CC Vector4::operator /= (Vector4 const& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    };
    
    XO_INL Vector4 Vector4::operator -() const { return Vector4(-x, -y, -z, -w); }
    
    XO_INL float Vector4::operator[] (int index) const { return v[index]; }
    XO_INL float& Vector4::operator[] (int index) { return v[index]; }
    
    XO_INL float Vector4::Sum() const { return x + y + z + w; }
    
    XO_INL float Vector4::MagnitudeSquared() const { return x * x + y * y + z * z + w * w; }
    XO_INL float Vector4::Magnitude() const { return Sqrt(MagnitudeSquared()); }
    XO_INL Vector4 Vector4::Normalized() const { return Vector4(*this).Normalize(); }
    XO_INL Vector4& Vector4::Normalize() { return (*this) /= Vector4(Magnitude()); };
    
    /*static*/ XO_INL
    bool XO_CC Vector4::RoughlyEqual(Vector4 const& left, Vector4 const& right) {
        return CloseEnough(left.x, right.x)
        && CloseEnough(left.y, right.y)
        && CloseEnough(left.z, right.z)
        && CloseEnough(left.w, right.w);
    }
    
    /*static*/ XO_INL
    bool XO_CC Vector4::ExactlyEqual(Vector4 const& left, Vector4 const& right) {
        return left.x == right.x
        && left.y == right.y
        && left.z == right.z
        && left.w == right.w;
    }
    
    /*static*/ XO_INL
    bool XO_CC Vector4::RoughlyEqual(Vector4 const& left, float magnitude) {
        return CloseEnough(left.MagnitudeSquared(), Pow<2>(magnitude));
    }
    
    /*static*/ XO_INL
    bool XO_CC Vector4::ExactlyEqual(Vector4 const& left, float magnitude) {
        return left.MagnitudeSquared() == Pow<2>(magnitude);
    }
    
    /*static*/ XO_INL
    float XO_CC Vector4::DotProduct(Vector4 const& left, Vector4 const& right) {
        return (left * right).Sum();
    }
    
    /*static*/ XO_INL
    Vector4 XO_CC Vector4::Lerp(Vector4 const& left, Vector4 const& right, float t) {
        return left + Vector4(t) * (right - left);
    }
    
#if defined(XO_MATH_IMPL)
    /*static*/ const Vector4 Vector4::Zero(0.f);
    /*static*/ const Vector4 Vector4::One(1.f);
#endif
    
    ////////////////////////////////////////////////////////////////////////////////////////// Matrix4x4
    
#if defined(XO_MATH_IMPL)
    /*static*/ const Matrix4x4 Matrix4x4::One(1.f);
    /*static*/ const Matrix4x4 Matrix4x4::Zero(0.f);
    /*static*/ const Matrix4x4 Matrix4x4::Identity(
                                                   Vector4(1.f, 0.f, 0.f, 0.f),
                                                   Vector4(0.f, 1.f, 0.f, 0.f),
                                                   Vector4(0.f, 0.f, 1.f, 0.f),
                                                   Vector4(0.f, 0.f, 0.f, 1.f));
#endif
    
    XO_INL
    Matrix4x4 XO_CC Matrix4x4::operator * (Matrix4x4 const& other) const {
        return Matrix4x4(*this) *= other;
    }
    
    XO_INL
    Matrix4x4& XO_CC Matrix4x4::operator *= (Matrix4x4 const& other) {
        Matrix4x4 transposed = Transpose(other);
        return (*this) = Matrix4x4(
                                   Vector4(Vector4::DotProduct(rows[0], transposed[0]),
                                           Vector4::DotProduct(rows[0], transposed[1]),
                                           Vector4::DotProduct(rows[0], transposed[2]),
                                           Vector4::DotProduct(rows[0], transposed[3])),
                                   
                                   Vector4(Vector4::DotProduct(rows[1], transposed[0]),
                                           Vector4::DotProduct(rows[1], transposed[1]),
                                           Vector4::DotProduct(rows[1], transposed[2]),
                                           Vector4::DotProduct(rows[1], transposed[3])),
                                   
                                   Vector4(Vector4::DotProduct(rows[2], transposed[0]),
                                           Vector4::DotProduct(rows[2], transposed[1]),
                                           Vector4::DotProduct(rows[2], transposed[2]),
                                           Vector4::DotProduct(rows[2], transposed[3])),
                                   
                                   Vector4(Vector4::DotProduct(rows[3], transposed[0]),
                                           Vector4::DotProduct(rows[3], transposed[1]),
                                           Vector4::DotProduct(rows[3], transposed[2]),
                                           Vector4::DotProduct(rows[3], transposed[3])));
    }
    
    XO_INL Vector4 Matrix4x4::operator[] (int index) const { return rows[index]; }
    XO_INL Vector4& Matrix4x4::operator[] (int index) { return rows[index]; }
    
    XO_INL
    Vector3 Matrix4x4::Up() const {
#if defined(XO_CONFIG_Y_UP) && XO_CONFIG_Y_UP
        return Vector3(rows[1][0], rows[1][1], rows[1][2]);
#elif defined(XO_CONFIG_Z_UP) && XO_CONFIG_Z_UP
        return Vector3(rows[2][0], rows[2][1], rows[2][2]);
#else
        static_assert(false, "Define XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a \
                      value of 1, the other should have a value of 0.");
#endif
    }
    
    XO_INL
    Vector3 Matrix4x4::Down() const {
        return -Up();
    }
    
    XO_INL
    Vector3 Matrix4x4::Left() const {
        return -Right();
    }
    XO_INL
    Vector3 Matrix4x4::Right() const {
        return Vector3(rows[0][0], rows[0][1], rows[0][2]);
    }
    
    XO_INL
    Vector3 Matrix4x4::Forward() const {
#if defined(XO_CONFIG_Y_UP) && XO_CONFIG_Y_UP
#   if defined(XO_CONFIG_LEFT_HANDED) && XO_CONFIG_LEFT_HANDED
        return Vector3(rows[2][0], rows[2][1], rows[2][2]);
#   elif defined(XO_CONFIG_RIGHT_HANDED) && XO_CONFIG_RIGHT_HANDED
        return Vector3(-rows[2][0], -rows[2][1], -rows[2][2]);
#   else
        static_assert(false, "Define XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One \
                      should have a value of 1, the other should have a value of 0.");
#   endif
#elif defined(XO_CONFIG_Z_UP) && XO_CONFIG_Z_UP
#   if defined(XO_CONFIG_LEFT_HANDED) && XO_CONFIG_LEFT_HANDED
        return Vector3(-rows[1][0], -rows[1][1], -rows[1][2]);
#   elif defined(XO_CONFIG_RIGHT_HANDED) && XO_CONFIG_RIGHT_HANDED
        return Vector3(rows[1][0], rows[1][1], rows[1][2]);
#   else
        static_assert(false, "Define XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One \
                      should have a value of 1, the other should have a value of 0.");
#   endif
#else
        static_assert(false, "Define XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a \
                      value of 1, the other should have a value of 0.");
#endif
    }
    
    XO_INL
    Vector3 Matrix4x4::Backward() const {
        return -Forward();
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Transpose(Matrix4x4 const& matrixIn) {
        Matrix4x4 transposed = Matrix4x4(matrixIn);
        float t;
#define XO_TRANSPOSE_SWAP(i,j) \
t = transposed.rows[i][j];\
transposed.rows[i][j] = transposed.rows[j][i]; \
transposed.rows[j][i] = t;
        
        XO_TRANSPOSE_SWAP(0, 1);
        XO_TRANSPOSE_SWAP(0, 2);
        XO_TRANSPOSE_SWAP(0, 3);
        XO_TRANSPOSE_SWAP(1, 2);
        XO_TRANSPOSE_SWAP(1, 3);
        XO_TRANSPOSE_SWAP(2, 3);
#undef XO_TRANSPOSE_SWAP
        return transposed;
    }
    
    namespace {
        XO_INL
        void XO_CC EarlyInverse(float tmp[12], float src[16], float& det, float m[16]) {
            // http://download.intel.com/design/PentiumIII/sml/24504301.pdf
            // transpose matrix
            for (int i = 0; i < 4; i++) {
                src[i] = m[i * 4];
                src[i + 4] = m[i * 4 + 1];
                src[i + 8] = m[i * 4 + 2];
                src[i + 12] = m[i * 4 + 3];
            }
            // calculate pairs for first 8 elements (cofactors)
            tmp[0] = src[10] * src[15];
            tmp[1] = src[11] * src[14];
            tmp[2] = src[9] * src[15];
            tmp[3] = src[11] * src[13];
            tmp[4] = src[9] * src[14];
            tmp[5] = src[10] * src[13];
            tmp[6] = src[8] * src[15];
            tmp[7] = src[11] * src[12];
            tmp[8] = src[8] * src[14];
            tmp[9] = src[10] * src[12];
            tmp[10] = src[8] * src[13];
            tmp[11] = src[9] * src[12];
            // calculate first 8 elements (cofactors)
            m[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
            m[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
            m[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
            m[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
            m[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
            m[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
            m[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
            m[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
            m[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
            m[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
            m[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
            m[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
            m[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
            m[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
            m[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
            m[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];
            // calculate pairs for second 8 elements (cofactors)
            tmp[0] = src[2] * src[7];
            tmp[1] = src[3] * src[6];
            tmp[2] = src[1] * src[7];
            tmp[3] = src[3] * src[5];
            tmp[4] = src[1] * src[6];
            tmp[5] = src[2] * src[5];
            tmp[6] = src[0] * src[7];
            tmp[7] = src[3] * src[4];
            tmp[8] = src[0] * src[6];
            tmp[9] = src[2] * src[4];
            tmp[10] = src[0] * src[5];
            tmp[11] = src[1] * src[4];
            // calculate second 8 elements (cofactors)
            m[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
            m[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
            m[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
            m[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
            m[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
            m[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
            m[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
            m[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
            m[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
            m[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
            m[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
            m[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
            m[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
            m[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
            m[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
            m[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
            // calculate determinant
            det = src[0] * m[0] + src[1] * m[1] + src[2] * m[2] + src[3] * m[3];
        }
        
        XO_INL
        void XO_CC LateInverse(float &det, float m[16]) {
            // http://download.intel.com/design/PentiumIII/sml/24504301.pdf
            // calculate matrix inverse
            det = 1.0f / det;
            for (int j = 0; j < 16; j++) {
                m[j] *= det;
            }
        }
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Invert(Matrix4x4 const& matrixIn) {
        float tmp[12]; // temp array for pairs
        float src[16]; // array of transpose source matrix
        float det; // determinant
        Matrix4x4 inverted(matrixIn);
        EarlyInverse(tmp, src, det, inverted.v);
        LateInverse(det, inverted.v);
        return inverted;
    }
    
    /*static*/ XO_INL
    bool XO_CC Matrix4x4::InvertSafe(Matrix4x4 const& matrixIn, Matrix4x4& matrixOut) {
        float tmp[12]; // temp array for pairs
        float src[16]; // array of transpose source matrix
        float det; // determinant
        Matrix4x4 inverted(matrixIn);
        EarlyInverse(tmp, src, det, inverted.v);
        if (CloseEnough(det, 0.f))
            return false;
        LateInverse(det, inverted.v);
        matrixOut = inverted;
        return true;
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Translation(Vector3 const& pos) {
        return Matrix4x4(
                         Vector4(1.f,   0.f,   0.f,   0.f),
                         Vector4(0.f,   1.f,   0.f,   0.f),
                         Vector4(0.f,   0.f,   1.f,   0.f),
                         Vector4(pos.x, pos.y, pos.z, 1.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Scale(Vector3 const& scale) {
        return Matrix4x4(
                         Vector4(scale.x, 0.f,     0.f,     0.f),
                         Vector4(0.f,     scale.y, 0.f,     0.f),
                         Vector4(0.f,     0.f,     scale.z, 0.f),
                         Vector4(0.f,     0.f,     0.f,     1.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::RotationYaw(float yaw) {
        float s, c;
        SinCos(yaw, s, c);
        return Matrix4x4(
                         Vector4(c,   0.f, -s,  0.f),
                         Vector4(0.f, 1.f, 0.f, 0.f),
                         Vector4(s,   0.f, c,   0.f),
                         Vector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::RotationPitch(float pitch) {
        float s, c;
        SinCos(pitch, s, c);
        return Matrix4x4(
                         Vector4(1.f, 0.f, 0.f, 0.f),
                         Vector4(0.f, c,   -s,  0.f),
                         Vector4(0.f, s,   c,   0.f),
                         Vector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::RotationRoll(float roll) {
        float s, c;
        SinCos(roll, s, c);
        return Matrix4x4(
                         Vector4(c,   -s,  0.f, 0.f),
                         Vector4(s,   c,   0.f, 0.f),
                         Vector4(0.f, 0.f, 1.f, 0.f),
                         Vector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::RotationYawPitchRoll(float yaw, float pitch, float roll) {
        return RotationYaw(yaw) * RotationPitch(pitch) * RotationRoll(roll);
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::RotationAxisAngle(Vector3 const& axis, float angle) {
        float s, c;
        SinCos(angle, s, c);
        float t = 1.f - c;
        Vector3 a = axis.Normalized();
        Matrix4x4 rotation(Matrix4x4::Identity);
        
        rotation[0][0] = c + a.x*a.x*t;
        rotation[1][1] = c + a.y*a.y*t;
        rotation[2][2] = c + a.z*a.z*t;
        
        
        float tmp1 = a.x*a.y*t;
        float tmp2 = a.z*s;
        rotation[1][0] = tmp1 + tmp2;
        rotation[0][1] = tmp1 - tmp2;
        
        tmp1 = a.x*a.z*t;
        tmp2 = a.y*s;
        rotation[2][0] = tmp1 - tmp2;
        rotation[0][2] = tmp1 + tmp2;    tmp1 = a.y*a.z*t;
        
        tmp2 = a.x*s;
        rotation[2][1] = tmp1 + tmp2;
        rotation[1][2] = tmp1 - tmp2;
        
        return rotation;
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::PerspectiveFOV(float fov,
                                              float aspect,
                                              float nearPlane,
                                              float farPlane) {
        float s, c;
        SinCos(fov*0.5f, s, c);
        float h = c / s;                             // height
        float w = h / aspect;                        // width
        float r = farPlane / (nearPlane - farPlane); // range
        float rn = r * nearPlane;                    // range*near
        return Matrix4x4(
                         Vector4(w,   0.f, 0.f, 0.f),
                         Vector4(0.f, h,   0.f, 0.f),
                         Vector4(0.f, 0.f, r,  -1.f),
                         Vector4(0.f, 0.f, rn,  0.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Perspective(float width,
                                           float height,
                                           float aspect,
                                           float nearPlane,
                                           float farPlane) {
        float n2 = Pow<2>(nearPlane);
        float r = farPlane / (nearPlane - farPlane);
        float w = n2 / width;
        float h = n2 / height;
        float rn = r * nearPlane;
        return Matrix4x4(
                         Vector4(w,   0.f, 0.f, 0.f),
                         Vector4(0.f, h,   0.f, 0.f),
                         Vector4(0.f, 0.f, r,  -1.f),
                         Vector4(0.f, 0.f, rn,  0.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::Orthographic(float width,
                                            float height,
                                            float nearPlane,
                                            float farPlane) {
        float r = 1.f / (nearPlane - farPlane);
        float w = 2.f / width;
        float h = 2.f / height;
        float rn = r * nearPlane;
        return Matrix4x4(
                         Vector4(w, 0.f, 0.f, 0.f),
                         Vector4(0.f, h, 0.f, 0.f),
                         Vector4(0.f, 0.f, r, 0.f),
                         Vector4(0.f, 0.f, rn, 0.f));
    }
    
    /*static*/ XO_INL
    Matrix4x4 XO_CC Matrix4x4::LookAt(Vector3 const& from,
                                      Vector3 const& to,
                                      Vector3 const& up) {
        Vector3 dir = from - to;
        Vector3 r2 = dir.Normalized();
        Vector3 r0 = Vector3::CrossProduct(up, r2).Normalized();
        Vector3 r1 = Vector3::CrossProduct(r2, r0);
        
        float d0 = -Vector3::DotProduct(r0, from);
        float d1 = -Vector3::DotProduct(r1, from);
        float d2 = -Vector3::DotProduct(r2, from);
        return Matrix4x4(
                         Vector4(r0.x, r1.x, r2.x, 0.f),
                         Vector4(r0.y, r1.y, r2.y, 0.f),
                         Vector4(r0.z, r1.z, r2.z, 0.f),
                         Vector4(d0,   d1,   d2,   1.f));
    }
    
    /*static*/ XO_INL
    bool XO_CC Matrix4x4::RoughlyEqual(Matrix4x4 const& left, Matrix4x4 const& right) {
        return Vector4::RoughlyEqual(left[0], right[0])
        && Vector4::RoughlyEqual(left[1], right[1])
        && Vector4::RoughlyEqual(left[2], right[2])
        && Vector4::RoughlyEqual(left[3], right[3]);
    }
    
    /*static*/ XO_INL
    bool XO_CC Matrix4x4::ExactlyEqual(Matrix4x4 const& left, Matrix4x4 const& right) {
        return Vector4::ExactlyEqual(left[0], right[0])
        && Vector4::ExactlyEqual(left[1], right[1])
        && Vector4::ExactlyEqual(left[2], right[2])
        && Vector4::ExactlyEqual(left[3], right[3]);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////// Quaternion
#if defined(XO_MATH_IMPL)
    /*static*/ const Quaternion Quaternion::Zero(0.f);
    /*static*/ const Quaternion Quaternion::Identity(0.f, 0.f, 0.f, 1.f);
#endif
    
    XO_INL
    Quaternion Quaternion::operator + (Quaternion other) const {
        return Quaternion(i + other.i, j + other.j, k + other.k, r + other.r);
    }
    
    XO_INL
    Quaternion Quaternion::operator *(float s) const {
        return Quaternion(i*s, j*s, k*s, r*s);
    }
    
    XO_INL
    Quaternion Quaternion::operator -() const {
        return Quaternion(-i, -j, -k, -r);
    }
    
    XO_INL
    float Quaternion::Magnitude() const {
        return vec4.Magnitude();
    }
    
    XO_INL
    float Quaternion::MagnitudeSquared() const {
        return vec4.MagnitudeSquared();
    };
    
    XO_INL
    Quaternion Quaternion::Normalized() const {
        return Quaternion(vec4.Normalized());
    };
    
    XO_INL
    Quaternion& Quaternion::Normalize() {
        vec4.Normalize(); return *this;
    };
    
    XO_INL
    Matrix4x4 Quaternion::ToMatrix() const {
        // See: https://www.flipcode.com/documents/matrfaq.html#Q54
        float ii = i * i;
        float ij = i * j;
        float ik = i * k;
        float ir = i * r;
        float jj = j * j;
        float jk = j * k;
        float jr = j * r;
        float kk = k * k;
        float kr = k * r;
        return Matrix4x4(
                         Vector4(1.f - 2.f * (jj + kk), 2.f * (ij - kr), 2.f * (ik + jr), 0.f),
                         Vector4(2.f * (ij + kr), 1.f - 2.f * (ii + kk), 2.f * (jk - ir), 0.f),
                         Vector4(2.f * (ik - jr), 2.f * (jk + ir), 1.f - 2.f * (ii + jj), 0.f),
                         Vector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    Quaternion XO_CC Quaternion::Invert(Quaternion const& quat) {
        return Quaternion(-quat.i, -quat.j, -quat.k, quat.r);
    }
    
    /*static*/ XO_INL
    Quaternion XO_CC Quaternion::RotationAxisAngle(Vector3 const& axis, float angle) {
        float s, c;
        SinCos(angle*0.5f, s, c);
        return Quaternion(axis.x*s, axis.y*s, axis.z*s, c);
    }
    
    /*static*/ XO_INL
    Quaternion XO_CC Quaternion::RotationEuler(Vector3 const& angles) {
        float sr, cp, sp, cy, sy, cr;
        SinCos(angles.x * 0.5f, sy, cy);
        SinCos(angles.y * 0.5f, sp, cp);
        SinCos(angles.z * 0.5f, sr, cr);
        return Quaternion(cy * cr * cp + sy * sr * sp,
                          cy * sr * cp - sy * cr * sp,
                          cy * cr * sp + sy * sr * cp,
                          sy * cr * cp - cy * sr * sp);
    }
    
    /*static*/ XO_INL
    float XO_CC Quaternion::DotProduct(Quaternion const& left, Quaternion const& right) {
        return Vector4::DotProduct(left.vec4, right.vec4);
    }
    
    /*static*/ XO_INL
    Quaternion XO_CC Quaternion::Lerp(Quaternion const& start,
                                      Quaternion const& end,
                                      float t) {
        return Quaternion(Vector4::Lerp(start.vec4, end.vec4, t));
    }
    
    /*static*/ XO_INL
    Quaternion XO_CC Quaternion::Slerp(Quaternion const& start,
                                       Quaternion const& end,
                                       float t) {
        Quaternion s = start.Normalized();
        Quaternion e = end.Normalized();
        float d = Quaternion::DotProduct(s, e);
        if (d < 0.f) {
            e = -e;
            d = -d;
        }
        
        if (CloseEnough(d, 1.f)) {
            return Lerp(s, e, t).Normalize();
        }
        
        float th0 = ACos(d);
        float th = th0 * t;
        
        float st, ct, sth0;
        SinCos(th, st, ct);
        sth0 = Sin(th0);
        float s0 = ct - d * st / sth0;
        float s1 = st / sth0;
        return (s * s0) + (e * s1);
    }
    
    /*static*/ XO_INL
    bool XO_CC Quaternion::RoughlyEqual(Quaternion const& left, Quaternion const& right) {
        return CloseEnough(left.i, right.i)
        && CloseEnough(left.j, right.j)
        && CloseEnough(left.k, right.k)
        && CloseEnough(left.r, right.r);
    }
    
    /*static*/ XO_INL
    bool XO_CC Quaternion::ExactlyEqual(Quaternion const& left, Quaternion const& right) {
        return left.i == right.i
        && left.j == right.j
        && left.k == right.k
        && left.r == right.r;
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////// AVector 3
#if defined(XO_MATH_IMPL)
    /*static*/ const AVector3 AVector3::Zero(0.f);
    /*static*/ const AVector3 AVector3::One(1.f);
    /*static*/ const AVector3 AVector3::Left(-1.f, 0.f, 0.f);
    /*static*/ const AVector3 AVector3::Right(1.f, 0.f, 0.f);
    
#   if !defined(XO_CONFIG_Y_UP) || !defined(XO_CONFIG_Z_UP)
    static_assert(false,
                  "define both XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a value of 1, and\
                  the other should have a value of 0");
#   endif
    
#   if !defined(XO_CONFIG_LEFT_HANDED) || !defined(XO_CONFIG_RIGHT_HANDED)
    static_assert(false,
                  "define both XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One should have a \
                  value of 1, and the other should have a value of 0");
#   endif
    
#   if XO_CONFIG_Y_UP
    static_assert(XO_CONFIG_Z_UP == 0,
                  "XO_CONFIG_Z_UP should be 0 if XO_CONFIG_Y_UP is 1");
    /*static*/ const AVector3 AVector3::Up(0.f, 1.f, 0.f);
    /*static*/ const AVector3 AVector3::Down(0.f, -1.f, 0.f);
#       if XO_CONFIG_LEFT_HANDED
    static_assert(XO_CONFIG_RIGHT_HANDED == 0,
                  "XO_CONFIG_RIGHT_HANDED should be 0 if XO_CONFIG_LEFT_HANDED is 1");
    /*static*/ const AVector3 AVector3::Forward(0.f, 0.f, 1.f);
    /*static*/ const AVector3 AVector3::Backward(0.f, 0.f, -1.f);
#       elif XO_CONFIG_RIGHT_HANDED
    static_assert(XO_CONFIG_LEFT_HANDED == 0,
                  "XO_CONFIG_LEFT_HANDED should be 0 if XO_CONFIG_RIGHT_HANDED is 1");
    /*static*/ const AVector3 AVector3::Forward(0.f, 0.f, -1.f);
    /*static*/ const AVector3 AVector3::Backward(0.f, 0.f, 1.f);
#       else
    static_assert(false,
                  "XO_CONFIG_LEFT_HANDED or XO_CONFIG_RIGHT_HANDED should have a non zero \
                  value...");
#       endif
#   elif XO_CONFIG_Z_UP
    // no static assert here about XO_CONFIG_Y_UP, because it's been checked.
    /*static*/ const AVector3 AVector3::Up(0.f, 0.f, 1.f);
    /*static*/ const AVector3 AVector3::Down(0.f, 0.f, -1.f);
#       if XO_CONFIG_LEFT_HANDED
    static_assert(XO_CONFIG_RIGHT_HANDED == 0,
                  "XO_CONFIG_RIGHT_HANDED should be 0 if XO_CONFIG_LEFT_HANDED is 1");
    /*static*/ const AVector3 AVector3::Forward(0.f, -1.f, 0.f);
    /*static*/ const AVector3 AVector3::Backward(0.f, 1.f, 0.f);
#       elif XO_CONFIG_RIGHT_HANDED
    static_assert(XO_CONFIG_LEFT_HANDED == 0,
                  "XO_CONFIG_LEFT_HANDED should be 0 if XO_CONFIG_RIGHT_HANDED is 1");
    /*static*/ const AVector3 AVector3::Forward(0.f, 1.f, 0.f);
    /*static*/ const AVector3 AVector3::Backward(0.f, -1.f, 0.f);
#       else
    static_assert(false,
                  "XO_CONFIG_LEFT_HANDED or XO_CONFIG_RIGHT_HANDED should have a non zero \
                  value...");
#       endif
#   else
    static_assert(false,
                  "XO_CONFIG_Y_UP or XO_CONFIG_Z_UP should have a non zero value...");
#   endif
#endif
    
    XO_INL
    AVector3 XO_CC AVector3::operator + (AVector3 const& other) const {
        return AVector3(x + other.x, y + other.y, z + other.z);
    }
    
    XO_INL
    AVector3 XO_CC AVector3::operator - (AVector3 const& other) const {
        return AVector3(x - other.x, y - other.y, z - other.z);
    }
    
    XO_INL
    AVector3 XO_CC AVector3::operator * (AVector3 const& other) const {
        return AVector3(x * other.x, y * other.y, z * other.z);
    }
    
    XO_INL
    AVector3 XO_CC AVector3::operator / (AVector3 const& other) const {
        return AVector3(x / other.x, y / other.y, z / other.z);
    }
    
    XO_INL
    AVector3& XO_CC AVector3::operator += (AVector3 const& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    
    XO_INL
    AVector3& XO_CC AVector3::operator -= (AVector3 const& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    
    XO_INL
    AVector3& XO_CC AVector3::operator *= (AVector3 const& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }
    
    XO_INL
    AVector3& XO_CC AVector3::operator /= (AVector3 const& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }
    
    XO_INL AVector3 AVector3::operator -() const { return AVector3(-x, -y, -z); };
    
    XO_INL float AVector3::Sum() const { return x + y + z; }
    
    XO_INL float AVector3::MagnitudeSquared() const { return ((*this) * (*this)).Sum(); }
    XO_INL float AVector3::Magnitude() const { return xo::Sqrt(MagnitudeSquared()); }
    
    XO_INL AVector3& AVector3::Normalize() { return (*this) /= AVector3(Magnitude()); }
    XO_INL AVector3 AVector3::Normalized() const { return AVector3(*this).Normalize(); }
    
    /*static*/ XO_INL
    bool XO_CC AVector3::RoughlyEqual(AVector3 const& left, AVector3 const& right) {
        return CloseEnough(left.x, right.x)
        && CloseEnough(left.y, right.y)
        && CloseEnough(left.z, right.z);
    }
    
    /*static*/ XO_INL
    bool XO_CC AVector3::ExactlyEqual(AVector3 const& left, AVector3 const& right) {
        return left.x == right.x
        && left.y == right.y
        && left.z == right.z;
    }
    /*static*/ XO_INL
    bool XO_CC AVector3::RoughlyEqual(AVector3 const& left, float magnitude) {
        return CloseEnough(left.MagnitudeSquared(), Pow<2>(magnitude));
    }
    
    /*static*/ XO_INL
    bool XO_CC AVector3::ExactlyEqual(AVector3 const& left, float magnitude) {
        return left.MagnitudeSquared() == Pow<2>(magnitude);
    }
    
    /*static*/ XO_INL
    float XO_CC AVector3::DotProduct(AVector3 const& left, AVector3 const& right) {
        return (left * right).Sum();
    }
    
    /*static*/ XO_INL
    AVector3 XO_CC AVector3::CrossProduct(AVector3 const& left, AVector3 const& right) {
        return AVector3(
                        left.y * right.z - left.z * right.y,
                        left.z * right.x - left.x * right.z,
                        left.x * right.y - left.y * right.x);
    }
    
    /*static*/ XO_INL
    AVector3 XO_CC AVector3::Lerp(AVector3 const& left, AVector3 const& right, float t) {
        return left + AVector3(t) * (right - left);
    }
    
    /*static*/ XO_INL
    float XO_CC AVector3::DistanceSquared(AVector3 const& left, AVector3 const& right) {
        return (right - left).MagnitudeSquared();
    }
    
    /*static*/ XO_INL
    float XO_CC AVector3::Distance(AVector3 const& left, AVector3 const& right) {
        return (right - left).Magnitude();
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////// AVector 4
    
    XO_INL
    AVector4 XO_CC AVector4::operator + (AVector4 const& other) const {
        return AVector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }
    
    XO_INL
    AVector4 XO_CC AVector4::operator - (AVector4 const& other) const {
        return AVector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }
    
    XO_INL
    AVector4 XO_CC AVector4::operator * (AVector4 const& other) const {
        return AVector4(x*other.x, y*other.y, z*other.z, w*other.w);
    }
    
    XO_INL
    AVector4 XO_CC AVector4::operator / (AVector4 const& other) const {
        return AVector4(x / other.x, y / other.y, z / other.z, w / other.w);
    }
    
    XO_INL
    AVector4& XO_CC AVector4::operator += (AVector4 const& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    };
    
    XO_INL
    AVector4& XO_CC AVector4::operator -= (AVector4 const& other) {
        x -=other.x;
        y -=other.y;
        z -= other.z;
        w -= other.w;
        return *this; };
    
    XO_INL
    AVector4& XO_CC AVector4::operator *= (AVector4 const& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        w *= other.w;
        return *this;
    };
    
    XO_INL
    AVector4& XO_CC AVector4::operator /= (AVector4 const& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        w /= other.w;
        return *this;
    };
    
    XO_INL AVector4 AVector4::operator -() const { return AVector4(-x, -y, -z, -w); }
    
    XO_INL float AVector4::operator[] (int index) const { return v[index]; }
    XO_INL float& AVector4::operator[] (int index) { return v[index]; }
    
    XO_INL float AVector4::Sum() const { return x + y + z + w; }
    
    XO_INL float AVector4::MagnitudeSquared() const { return x * x + y * y + z * z + w * w; }
    XO_INL float AVector4::Magnitude() const { return Sqrt(MagnitudeSquared()); }
    XO_INL AVector4 AVector4::Normalized() const { return AVector4(*this).Normalize(); }
    XO_INL AVector4& AVector4::Normalize() { return (*this) /= AVector4(Magnitude()); };
    
    /*static*/ XO_INL
    bool XO_CC AVector4::RoughlyEqual(AVector4 const& left, AVector4 const& right) {
        return CloseEnough(left.x, right.x)
        && CloseEnough(left.y, right.y)
        && CloseEnough(left.z, right.z)
        && CloseEnough(left.w, right.w);
    }
    
    /*static*/ XO_INL
    bool XO_CC AVector4::ExactlyEqual(AVector4 const& left, AVector4 const& right) {
        return left.x == right.x
        && left.y == right.y
        && left.z == right.z
        && left.w == right.w;
    }
    
    /*static*/ XO_INL
    bool XO_CC AVector4::RoughlyEqual(AVector4 const& left, float magnitude) {
        return CloseEnough(left.MagnitudeSquared(), Pow<2>(magnitude));
    }
    
    /*static*/ XO_INL
    bool XO_CC AVector4::ExactlyEqual(AVector4 const& left, float magnitude) {
        return left.MagnitudeSquared() == Pow<2>(magnitude);
    }
    
    /*static*/ XO_INL
    float XO_CC AVector4::DotProduct(AVector4 const& left, AVector4 const& right) {
        return (left * right).Sum();
    }
    
    /*static*/ XO_INL
    AVector4 XO_CC AVector4::Lerp(AVector4 const& left, AVector4 const& right, float t) {
        return left + AVector4(t) * (right - left);
    }
    
#if defined(XO_MATH_IMPL)
    /*static*/ const AVector4 AVector4::Zero(0.f);
    /*static*/ const AVector4 AVector4::One(1.f);
#endif
    
    ////////////////////////////////////////////////////////////////////////////////////////// AMatrix4x4
    
#if defined(XO_MATH_IMPL)
    /*static*/ const AMatrix4x4 AMatrix4x4::One(1.f);
    /*static*/ const AMatrix4x4 AMatrix4x4::Zero(0.f);
    /*static*/ const AMatrix4x4 AMatrix4x4::Identity(
                                                     AVector4(1.f, 0.f, 0.f, 0.f),
                                                     AVector4(0.f, 1.f, 0.f, 0.f),
                                                     AVector4(0.f, 0.f, 1.f, 0.f),
                                                     AVector4(0.f, 0.f, 0.f, 1.f));
#endif
    
    XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::operator * (AMatrix4x4 const& other) const {
        return AMatrix4x4(*this) *= other;
    }
    
    XO_INL
    AMatrix4x4& XO_CC AMatrix4x4::operator *= (AMatrix4x4 const& other) {
        AMatrix4x4 transposed = Transpose(other);
        return (*this) = AMatrix4x4(
                                    AVector4(AVector4::DotProduct(rows[0], transposed[0]),
                                             AVector4::DotProduct(rows[0], transposed[1]),
                                             AVector4::DotProduct(rows[0], transposed[2]),
                                             AVector4::DotProduct(rows[0], transposed[3])),
                                    
                                    AVector4(AVector4::DotProduct(rows[1], transposed[0]),
                                             AVector4::DotProduct(rows[1], transposed[1]),
                                             AVector4::DotProduct(rows[1], transposed[2]),
                                             AVector4::DotProduct(rows[1], transposed[3])),
                                    
                                    AVector4(AVector4::DotProduct(rows[2], transposed[0]),
                                             AVector4::DotProduct(rows[2], transposed[1]),
                                             AVector4::DotProduct(rows[2], transposed[2]),
                                             AVector4::DotProduct(rows[2], transposed[3])),
                                    
                                    AVector4(AVector4::DotProduct(rows[3], transposed[0]),
                                             AVector4::DotProduct(rows[3], transposed[1]),
                                             AVector4::DotProduct(rows[3], transposed[2]),
                                             AVector4::DotProduct(rows[3], transposed[3])));
    }
    
    XO_INL AVector4 AMatrix4x4::operator[] (int index) const { return rows[index]; }
    XO_INL AVector4& AMatrix4x4::operator[] (int index) { return rows[index]; }
    
    XO_INL
    AVector3 AMatrix4x4::Up() const {
#if defined(XO_CONFIG_Y_UP) && XO_CONFIG_Y_UP
        return AVector3(rows[1][0], rows[1][1], rows[1][2]);
#elif defined(XO_CONFIG_Z_UP) && XO_CONFIG_Z_UP
        return AVector3(rows[2][0], rows[2][1], rows[2][2]);
#else
        static_assert(false, "Define XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a \
                      value of 1, the other should have a value of 0.");
#endif
    }
    
    XO_INL
    AVector3 AMatrix4x4::Down() const {
        return -Up();
    }
    
    XO_INL
    AVector3 AMatrix4x4::Left() const {
        return -Right();
    }
    XO_INL
    AVector3 AMatrix4x4::Right() const {
        return AVector3(rows[0][0], rows[0][1], rows[0][2]);
    }
    
    XO_INL
    AVector3 AMatrix4x4::Forward() const {
#if defined(XO_CONFIG_Y_UP) && XO_CONFIG_Y_UP
#   if defined(XO_CONFIG_LEFT_HANDED) && XO_CONFIG_LEFT_HANDED
        return AVector3(rows[2][0], rows[2][1], rows[2][2]);
#   elif defined(XO_CONFIG_RIGHT_HANDED) && XO_CONFIG_RIGHT_HANDED
        return AVector3(-rows[2][0], -rows[2][1], -rows[2][2]);
#   else
        static_assert(false, "Define XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One \
                      should have a value of 1, the other should have a value of 0.");
#   endif
#elif defined(XO_CONFIG_Z_UP) && XO_CONFIG_Z_UP
#   if defined(XO_CONFIG_LEFT_HANDED) && XO_CONFIG_LEFT_HANDED
        return AVector3(-rows[1][0], -rows[1][1], -rows[1][2]);
#   elif defined(XO_CONFIG_RIGHT_HANDED) && XO_CONFIG_RIGHT_HANDED
        return AVector3(rows[1][0], rows[1][1], rows[1][2]);
#   else
        static_assert(false, "Define XO_CONFIG_LEFT_HANDED and XO_CONFIG_RIGHT_HANDED. One \
                      should have a value of 1, the other should have a value of 0.");
#   endif
#else
        static_assert(false, "Define XO_CONFIG_Y_UP and XO_CONFIG_Z_UP. One should have a \
                      value of 1, the other should have a value of 0.");
#endif
    }
    
    XO_INL
    AVector3 AMatrix4x4::Backward() const {
        return -Forward();
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Transpose(AMatrix4x4 const& AMatrixIn) {
        AMatrix4x4 transposed = AMatrix4x4(AMatrixIn);
        float t;
#define XO_TRANSPOSE_SWAP(i,j) \
t = transposed.rows[i][j];\
transposed.rows[i][j] = transposed.rows[j][i]; \
transposed.rows[j][i] = t;
        
        XO_TRANSPOSE_SWAP(0, 1);
        XO_TRANSPOSE_SWAP(0, 2);
        XO_TRANSPOSE_SWAP(0, 3);
        XO_TRANSPOSE_SWAP(1, 2);
        XO_TRANSPOSE_SWAP(1, 3);
        XO_TRANSPOSE_SWAP(2, 3);
#undef XO_TRANSPOSE_SWAP
        return transposed;
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Invert(AMatrix4x4 const& AMatrixIn) {
        float tmp[12]; // temp array for pairs
        float src[16]; // array of transpose source AMatrix
        float det; // determinant
        AMatrix4x4 inverted(AMatrixIn);
        EarlyInverse(tmp, src, det, inverted.v);
        LateInverse(det, inverted.v);
        return inverted;
    }
    
    /*static*/ XO_INL
    bool XO_CC AMatrix4x4::InvertSafe(AMatrix4x4 const& AMatrixIn, AMatrix4x4& AMatrixOut) {
        float tmp[12]; // temp array for pairs
        float src[16]; // array of transpose source AMatrix
        float det; // determinant
        AMatrix4x4 inverted(AMatrixIn);
        EarlyInverse(tmp, src, det, inverted.v);
        if (CloseEnough(det, 0.f))
            return false;
        LateInverse(det, inverted.v);
        AMatrixOut = inverted;
        return true;
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Translation(AVector3 const& pos) {
        return AMatrix4x4(
                          AVector4(1.f,   0.f,   0.f,   0.f),
                          AVector4(0.f,   1.f,   0.f,   0.f),
                          AVector4(0.f,   0.f,   1.f,   0.f),
                          AVector4(pos.x, pos.y, pos.z, 1.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Scale(AVector3 const& scale) {
        return AMatrix4x4(
                          AVector4(scale.x, 0.f,     0.f,     0.f),
                          AVector4(0.f,     scale.y, 0.f,     0.f),
                          AVector4(0.f,     0.f,     scale.z, 0.f),
                          AVector4(0.f,     0.f,     0.f,     1.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::RotationYaw(float yaw) {
        float s, c;
        SinCos(yaw, s, c);
        return AMatrix4x4(
                          AVector4(c,   0.f, -s,  0.f),
                          AVector4(0.f, 1.f, 0.f, 0.f),
                          AVector4(s,   0.f, c,   0.f),
                          AVector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::RotationPitch(float pitch) {
        float s, c;
        SinCos(pitch, s, c);
        return AMatrix4x4(
                          AVector4(1.f, 0.f, 0.f, 0.f),
                          AVector4(0.f, c,   -s,  0.f),
                          AVector4(0.f, s,   c,   0.f),
                          AVector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::RotationRoll(float roll) {
        float s, c;
        SinCos(roll, s, c);
        return AMatrix4x4(
                          AVector4(c,   -s,  0.f, 0.f),
                          AVector4(s,   c,   0.f, 0.f),
                          AVector4(0.f, 0.f, 1.f, 0.f),
                          AVector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::RotationYawPitchRoll(float yaw, float pitch, float roll) {
        return RotationYaw(yaw) * RotationPitch(pitch) * RotationRoll(roll);
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::RotationAxisAngle(AVector3 const& axis, float angle) {
        float s, c;
        SinCos(angle, s, c);
        float t = 1.f - c;
        AVector3 a = axis.Normalized();
        AMatrix4x4 rotation(AMatrix4x4::Identity);
        
        rotation[0][0] = c + a.x*a.x*t;
        rotation[1][1] = c + a.y*a.y*t;
        rotation[2][2] = c + a.z*a.z*t;
        
        
        float tmp1 = a.x*a.y*t;
        float tmp2 = a.z*s;
        rotation[1][0] = tmp1 + tmp2;
        rotation[0][1] = tmp1 - tmp2;
        
        tmp1 = a.x*a.z*t;
        tmp2 = a.y*s;
        rotation[2][0] = tmp1 - tmp2;
        rotation[0][2] = tmp1 + tmp2;    tmp1 = a.y*a.z*t;
        
        tmp2 = a.x*s;
        rotation[2][1] = tmp1 + tmp2;
        rotation[1][2] = tmp1 - tmp2;
        
        return rotation;
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::PerspectiveFOV(float fov,
                                                float aspect,
                                                float nearPlane,
                                                float farPlane) {
        float s, c;
        SinCos(fov*0.5f, s, c);
        float h = c / s;                             // height
        float w = h / aspect;                        // width
        float r = farPlane / (nearPlane - farPlane); // range
        float rn = r * nearPlane;                    // range*near
        return AMatrix4x4(
                          AVector4(w,   0.f, 0.f, 0.f),
                          AVector4(0.f, h,   0.f, 0.f),
                          AVector4(0.f, 0.f, r,  -1.f),
                          AVector4(0.f, 0.f, rn,  0.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Perspective(float width,
                                             float height,
                                             float aspect,
                                             float nearPlane,
                                             float farPlane) {
        float n2 = Pow<2>(nearPlane);
        float r = farPlane / (nearPlane - farPlane);
        float w = n2 / width;
        float h = n2 / height;
        float rn = r * nearPlane;
        return AMatrix4x4(
                          AVector4(w,   0.f, 0.f, 0.f),
                          AVector4(0.f, h,   0.f, 0.f),
                          AVector4(0.f, 0.f, r,  -1.f),
                          AVector4(0.f, 0.f, rn,  0.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::Orthographic(float width,
                                              float height,
                                              float nearPlane,
                                              float farPlane) {
        float r = 1.f / (nearPlane - farPlane);
        float w = 2.f / width;
        float h = 2.f / height;
        float rn = r * nearPlane;
        return AMatrix4x4(
                          AVector4(w, 0.f, 0.f, 0.f),
                          AVector4(0.f, h, 0.f, 0.f),
                          AVector4(0.f, 0.f, r, 0.f),
                          AVector4(0.f, 0.f, rn, 0.f));
    }
    
    /*static*/ XO_INL
    AMatrix4x4 XO_CC AMatrix4x4::LookAt(AVector3 const& from,
                                        AVector3 const& to,
                                        AVector3 const& up) {
        AVector3 dir = from - to;
        AVector3 r2 = dir.Normalized();
        AVector3 r0 = AVector3::CrossProduct(up, r2).Normalized();
        AVector3 r1 = AVector3::CrossProduct(r2, r0);
        
        float d0 = -AVector3::DotProduct(r0, from);
        float d1 = -AVector3::DotProduct(r1, from);
        float d2 = -AVector3::DotProduct(r2, from);
        return AMatrix4x4(
                          AVector4(r0.x, r1.x, r2.x, 0.f),
                          AVector4(r0.y, r1.y, r2.y, 0.f),
                          AVector4(r0.z, r1.z, r2.z, 0.f),
                          AVector4(d0,   d1,   d2,   1.f));
    }
    
    /*static*/ XO_INL
    bool XO_CC AMatrix4x4::RoughlyEqual(AMatrix4x4 const& left, AMatrix4x4 const& right) {
        return AVector4::RoughlyEqual(left[0], right[0])
        && AVector4::RoughlyEqual(left[1], right[1])
        && AVector4::RoughlyEqual(left[2], right[2])
        && AVector4::RoughlyEqual(left[3], right[3]);
    }
    
    /*static*/ XO_INL
    bool XO_CC AMatrix4x4::ExactlyEqual(AMatrix4x4 const& left, AMatrix4x4 const& right) {
        return AVector4::ExactlyEqual(left[0], right[0])
        && AVector4::ExactlyEqual(left[1], right[1])
        && AVector4::ExactlyEqual(left[2], right[2])
        && AVector4::ExactlyEqual(left[3], right[3]);
    }
    
    ////////////////////////////////////////////////////////////////////////////////////////// AQuaternion
#if defined(XO_MATH_IMPL)
    /*static*/ const AQuaternion AQuaternion::Zero(0.f);
    /*static*/ const AQuaternion AQuaternion::Identity(0.f, 0.f, 0.f, 1.f);
#endif
    
    XO_INL
    AQuaternion AQuaternion::operator + (AQuaternion other) const {
        return AQuaternion(i + other.i, j + other.j, k + other.k, r + other.r);
    }
    
    XO_INL
    AQuaternion AQuaternion::operator *(float s) const {
        return AQuaternion(i*s, j*s, k*s, r*s);
    }
    
    XO_INL
    AQuaternion AQuaternion::operator -() const {
        return AQuaternion(-i, -j, -k, -r);
    }
    
    XO_INL
    float AQuaternion::Magnitude() const {
        return vec4.Magnitude();
    }
    
    XO_INL
    float AQuaternion::MagnitudeSquared() const {
        return vec4.MagnitudeSquared();
    };
    
    XO_INL
    AQuaternion AQuaternion::Normalized() const {
        return AQuaternion(vec4.Normalized());
    };
    
    XO_INL
    AQuaternion& AQuaternion::Normalize() {
        vec4.Normalize(); return *this;
    };
    
    XO_INL
    AMatrix4x4 AQuaternion::ToMatrix() const {
        // See: https://www.flipcode.com/documents/matrfaq.html#Q54
        float ii = i * i;
        float ij = i * j;
        float ik = i * k;
        float ir = i * r;
        float jj = j * j;
        float jk = j * k;
        float jr = j * r;
        float kk = k * k;
        float kr = k * r;
        return AMatrix4x4(
                          AVector4(1.f - 2.f * (jj + kk), 2.f * (ij - kr), 2.f * (ik + jr), 0.f),
                          AVector4(2.f * (ij + kr), 1.f - 2.f * (ii + kk), 2.f * (jk - ir), 0.f),
                          AVector4(2.f * (ik - jr), 2.f * (jk + ir), 1.f - 2.f * (ii + jj), 0.f),
                          AVector4(0.f, 0.f, 0.f, 1.f));
    }
    
    /*static*/ XO_INL
    AQuaternion XO_CC AQuaternion::Invert(AQuaternion const& quat) {
        return AQuaternion(-quat.i, -quat.j, -quat.k, quat.r);
    }
    
    /*static*/ XO_INL
    AQuaternion XO_CC AQuaternion::RotationAxisAngle(AVector3 const& axis, float angle) {
        float s, c;
        SinCos(angle*0.5f, s, c);
        return AQuaternion(axis.x*s, axis.y*s, axis.z*s, c);
    }
    
    /*static*/ XO_INL
    AQuaternion XO_CC AQuaternion::RotationEuler(AVector3 const& angles) {
        float sr, cp, sp, cy, sy, cr;
        // todo: rename. yaw, pitch, roll are misnomers here. switch yaw and pitch.
        SinCos(angles.x * 0.5f, sy, cy);
        SinCos(angles.y * 0.5f, sp, cp);
        SinCos(angles.z * 0.5f, sr, cr);
        return AQuaternion(cy * cr * cp + sy * sr * sp,
                           cy * sr * cp - sy * cr * sp,
                           cy * cr * sp + sy * sr * cp,
                           sy * cr * cp - cy * sr * sp);
    }
    
    /*static*/ XO_INL
    float XO_CC AQuaternion::DotProduct(AQuaternion const& left, AQuaternion const& right) {
        return AVector4::DotProduct(left.vec4, right.vec4);
    }
    
    /*static*/ XO_INL
    AQuaternion XO_CC AQuaternion::Lerp(AQuaternion const& start,
                                        AQuaternion const& end,
                                        float t) {
        return AQuaternion(AVector4::Lerp(start.vec4, end.vec4, t));
    }
    
    /*static*/ XO_INL
    AQuaternion XO_CC AQuaternion::Slerp(AQuaternion const& start,
                                         AQuaternion const& end,
                                         float t) {
        AQuaternion s = start.Normalized();
        AQuaternion e = end.Normalized();
        float d = AQuaternion::DotProduct(s, e);
        if (d < 0.f) {
            e = -e;
            d = -d;
        }
        
        if (CloseEnough(d, 1.f)) {
            return Lerp(s, e, t).Normalize();
        }
        
        float th0 = ACos(d);
        float th = th0 * t;
        
        float st, ct, sth0;
        SinCos(th, st, ct);
        sth0 = Sin(th0);
        float s0 = ct - d * st / sth0;
        float s1 = st / sth0;
        return (s * s0) + (e * s1);
    }
    
    /*static*/ XO_INL
    bool XO_CC AQuaternion::RoughlyEqual(AQuaternion const& left, AQuaternion const& right) {
        return CloseEnough(left.i, right.i)
        && CloseEnough(left.j, right.j)
        && CloseEnough(left.k, right.k)
        && CloseEnough(left.r, right.r);
    }
    
    /*static*/ XO_INL
    bool XO_CC AQuaternion::ExactlyEqual(AQuaternion const& left, AQuaternion const& right) {
        return left.i == right.i
        && left.j == right.j
        && left.k == right.k
        && left.r == right.r;
    }
    
} // ::xo
////////////////////////////////////////////////////////////////////////////////////////// end xo-math-reference.h inline
#endif

////////////////////////////////////////////////////////////////////////////////////////// third-party-licenses.h inlined
#line 3 "third-party-licenses.h"
/*****************************************************************************************
 License for: https://github.com/Microsoft/DirectXMath
 This license only applies to parts of xo-math where explicitly indicated
 The MIT License (MIT)
 Copyright (c) 2018 Microsoft Corp
 Permission is hereby granted, free of charge, to any person obtaining a copy of this
 software and associated documentation files (the "Software"), to deal in the Software
 without restriction, including without limitation the rights to use, copy, modify, merge,
 publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 *****************************************************************************************/
/*****************************************************************************************
 License for: https://github.com/Polytonic/Glitter
 This license only applies to parts of xo-math where explicitly indicated
 The MIT License (MIT)
 Copyright (c) 2015 Kevin Fung
 Permission is hereby granted, free of charge, to any person obtaining a copy of this
 software and associated documentation files (the "Software"), to deal in the Software
 without restriction, including without limitation the rights to use, copy, modify, merge,
 publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 to whom the Software is furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 *****************************************************************************************/
////////////////////////////////////////////////////////////////////////////////////////// end third-party-licenses.h inline



/** Fast inverse square root.
 */
inline float fastInvSqrt(float x)
{
    GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                       Union_type_sizes_do_not_match);
    
    // Use an approach to data type reinterpretation that is safe with GCC
    // strict aliasing enabled. This is called type-punning, and it is valid
    // when done with a union where the value read (int_value) is different
    // than the one most recently written to (float_value).
    union
    {
        float float_value;
        int   int_value;
    } data;
    
    const float xhalf(0.5f*x);
    data.float_value = x;
    // This hides a good amount of math
    data.int_value = 0x5f3759df - (data.int_value >> 1);
    x = data.float_value;
    x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
    return x;
}

inline float fastInvSqrt2(float x)
{
    GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                       Union_type_sizes_do_not_match);
    
    // Use an approach to data type reinterpretation that is safe with GCC
    // strict aliasing enabled. This is called type-punning, and it is valid
    // when done with a union where the value read (int_value) is different
    // than the one most recently written to (float_value).
    union
    {
        float float_value;
        int   int_value;
    } data;
    
    const float xhalf(0.5f*x);
    data.float_value = x;
    // This hides a good amount of math
    data.int_value = 0x5f3759df - (data.int_value >> 1);
    x = data.float_value;
    x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
    x = x*(1.5f - xhalf*x*x);
    return x;
}

inline float fastInvSqrt3(float x)
{
    GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                       Union_type_sizes_do_not_match);
    
    // Use an approach to data type reinterpretation that is safe with GCC
    // strict aliasing enabled. This is called type-punning, and it is valid
    // when done with a union where the value read (int_value) is different
    // than the one most recently written to (float_value).
    union
    {
        float float_value;
        int   int_value;
    } data;
    
    const float xhalf(0.5f*x);
    data.float_value = x;
    // This hides a good amount of math
    data.int_value = 0x5f3759df - (data.int_value >> 1);
    x = data.float_value;
    x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
    x = x*(1.5f - xhalf*x*x);
    x = x*(1.5f - xhalf*x*x);
    return x;
}
