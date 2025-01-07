/* =============================================================================== */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/*               -------------------------------------------------                 */
/*                PROJET: DrackEngine   PAR: Dracken24                             */
/*               -------------------------------------------------                 */
/*                CREATED: 11-12th-2024                                            */
/*                MODIFIED BY: Dracken24                                           */
/*                LAST MODIFIED: 11-12th-2024                                      */
/*               -------------------------------------------------                 */
/*                FILE: de_math.h                                                  */
/*               -------------------------------------------------                 */
/* ---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~--- */
/* =============================================================================== */

#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

#include <raylib.h>
#include <math.h>

//******************************************************************************//
//***                                 defines                                ***//
//******************************************************************************//

#ifndef PI
    #define PI 3.14159265358979323846f
#endif
#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif
#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

//******************************************************************************//
//***                                 Matrix                                 ***//
//******************************************************************************//

// Return m1 + m2
Matrix  matrix_add_matrix(Matrix m1, Matrix m2)
{
    Matrix ret_m;
    ret_m.m0 = m1.m0 + m2.m0;
    ret_m.m1 = m1.m1 + m2.m1;
    ret_m.m2 = m1.m2 + m2.m2;
    ret_m.m3 = m1.m3 + m2.m3;

    ret_m.m4 = m1.m4 + m2.m4;
    ret_m.m5 = m1.m5 + m2.m5;
    ret_m.m6 = m1.m6 + m2.m6;
    ret_m.m7 = m1.m7 + m2.m7;

    ret_m.m8 = m1.m8 + m2.m8;
    ret_m.m9 = m1.m9 + m2.m9;
    ret_m.m10 = m1.m10 + m2.m10;
    ret_m.m11 = m1.m11+ m2.m11;

    ret_m.m12 = m1.m12 + m2.m12;
    ret_m.m13 = m1.m13 + m2.m13;
    ret_m.m14 = m1.m14 + m2.m14;
    ret_m.m15 = m1.m15 + m2.m15;

    return ret_m;
}

// Return m1 - m2
Matrix  matrix_sub_matrix(Matrix m1, Matrix m2)
{
    Matrix ret_m;
    ret_m.m0 = m1.m0 - m2.m0;
    ret_m.m1 = m1.m1 - m2.m1;
    ret_m.m2 = m1.m2 - m2.m2;
    ret_m.m3 = m1.m3 - m2.m3;

    ret_m.m4 = m1.m4 - m2.m4;
    ret_m.m5 = m1.m5 - m2.m5;
    ret_m.m6 = m1.m6 - m2.m6;
    ret_m.m7 = m1.m7 - m2.m7;

    ret_m.m8 = m1.m8 - m2.m8;
    ret_m.m9 = m1.m9 - m2.m9;
    ret_m.m10 = m1.m10 - m2.m10;
    ret_m.m11 = m1.m11 - m2.m11;

    ret_m.m12 = m1.m12 - m2.m12;
    ret_m.m13 = m1.m13 - m2.m13;
    ret_m.m14 = m1.m14 - m2.m14;
    ret_m.m15 = m1.m15 - m2.m15;

    return ret_m;
}

// Return m1 * m2
Matrix  matrix_x_matrix(Matrix m1, Matrix m2)
{
    Matrix result = { 0 };
    
    result.m0 = m1.m0*m2.m0 + m1.m1*m2.m4 + m1.m2*m2.m8 + m1.m3*m2.m12;
    result.m1 = m1.m0*m2.m1 + m1.m1*m2.m5 + m1.m2*m2.m9 + m1.m3*m2.m13;
    result.m2 = m1.m0*m2.m2 + m1.m1*m2.m6 + m1.m2*m2.m10 + m1.m3*m2.m14;
    result.m3 = m1.m0*m2.m3 + m1.m1*m2.m7 + m1.m2*m2.m11 + m1.m3*m2.m15;

    result.m4 = m1.m4*m2.m0 + m1.m5*m2.m4 + m1.m6*m2.m8 + m1.m7*m2.m12;
    result.m5 = m1.m4*m2.m1 + m1.m5*m2.m5 + m1.m6*m2.m9 + m1.m7*m2.m13;
    result.m6 = m1.m4*m2.m2 + m1.m5*m2.m6 + m1.m6*m2.m10 + m1.m7*m2.m14;
    result.m7 = m1.m4*m2.m3 + m1.m5*m2.m7 + m1.m6*m2.m11 + m1.m7*m2.m15;

    result.m8 = m1.m8*m2.m0 + m1.m9*m2.m4 + m1.m10*m2.m8 + m1.m11*m2.m12;
    result.m9 = m1.m8*m2.m1 + m1.m9*m2.m5 + m1.m10*m2.m9 + m1.m11*m2.m13;
    result.m10 = m1.m8*m2.m2 + m1.m9*m2.m6 + m1.m10*m2.m10 + m1.m11*m2.m14;
    result.m11 = m1.m8*m2.m3 + m1.m9*m2.m7 + m1.m10*m2.m11 + m1.m11*m2.m15;

    result.m12 = m1.m12*m2.m0 + m1.m13*m2.m4 + m1.m14*m2.m8 + m1.m15*m2.m12;
    result.m13 = m1.m12*m2.m1 + m1.m13*m2.m5 + m1.m14*m2.m9 + m1.m15*m2.m13;
    result.m14 = m1.m12*m2.m2 + m1.m13*m2.m6 + m1.m14*m2.m10 + m1.m15*m2.m14;
    result.m15 = m1.m12*m2.m3 + m1.m13*m2.m7 + m1.m14*m2.m11 + m1.m15*m2.m15;

    return result;
}

// Calcul the determinant of a matrix 4x4
float matrix_determinant(Matrix m)
{
    float det;
    det = m.m0 * (m.m5 * (m.m10 * m.m15 - m.m11 * m.m14) -
                  m.m6 * (m.m9 * m.m15 - m.m11 * m.m13) +
                  m.m7 * (m.m9 * m.m14 - m.m10 * m.m13)) -
          m.m1 * (m.m4 * (m.m10 * m.m15 - m.m11 * m.m14) -
                  m.m6 * (m.m8 * m.m15 - m.m11 * m.m12) +
                  m.m7 * (m.m8 * m.m14 - m.m10 * m.m12)) +
          m.m2 * (m.m4 * (m.m9 * m.m15 - m.m11 * m.m13) -
                  m.m5 * (m.m8 * m.m15 - m.m11 * m.m12) +
                  m.m7 * (m.m8 * m.m13 - m.m9 * m.m12)) -
          m.m3 * (m.m4 * (m.m9 * m.m14 - m.m10 * m.m13) -
                  m.m5 * (m.m8 * m.m14 - m.m10 * m.m12) +
                  m.m6 * (m.m8 * m.m13 - m.m9 * m.m12));
    return det;
}

// Calculate the inverse of a matrix 4x4
Matrix matrix_inverse(Matrix m)
{
    Matrix inv = { 0 };
    float det = matrix_determinant(m);
    
    if (det == 0) // Return the original matrix if not invertible
        return m; 

    float invDet = 1.0f / det;

    inv.m0 = (m.m5 * (m.m10 * m.m15 - m.m11 * m.m14) - m.m6 * (m.m9 * m.m15 - m.m11 * m.m13) + m.m7 * (m.m9 * m.m14 - m.m10 * m.m13)) * invDet;
    inv.m1 = -(m.m1 * (m.m10 * m.m15 - m.m11 * m.m14) - m.m2 * (m.m9 * m.m15 - m.m11 * m.m13) + m.m3 * (m.m9 * m.m14 - m.m10 * m.m13)) * invDet;
    inv.m2 = (m.m1 * (m.m6 * m.m15 - m.m7 * m.m14) - m.m2 * (m.m5 * m.m15 - m.m7 * m.m13) + m.m3 * (m.m5 * m.m14 - m.m6 * m.m13)) * invDet;
    inv.m3 = -(m.m1 * (m.m6 * m.m11 - m.m7 * m.m10) - m.m2 * (m.m5 * m.m11 - m.m7 * m.m9) + m.m3 * (m.m5 * m.m10 - m.m6 * m.m9)) * invDet;

    inv.m4 = -(m.m4 * (m.m10 * m.m15 - m.m11 * m.m14) - m.m6 * (m.m8 * m.m15 - m.m11 * m.m12) + m.m7 * (m.m8 * m.m14 - m.m10 * m.m12)) * invDet;
    inv.m5 = (m.m0 * (m.m10 * m.m15 - m.m11 * m.m14) - m.m2 * (m.m8 * m.m15 - m.m11 * m.m12) + m.m3 * (m.m8 * m.m14 - m.m10 * m.m12)) * invDet;
    inv.m6 = -(m.m0 * (m.m6 * m.m15 - m.m7 * m.m14) - m.m2 * (m.m4 * m.m15 - m.m7 * m.m12) + m.m3 * (m.m4 * m.m14 - m.m6 * m.m12)) * invDet;
    inv.m7 = (m.m0 * (m.m6 * m.m11 - m.m7 * m.m10) - m.m2 * (m.m4 * m.m11 - m.m7 * m.m8) + m.m3 * (m.m4 * m.m10 - m.m6 * m.m8)) * invDet;

    inv.m8 = (m.m4 * (m.m9 * m.m15 - m.m11 * m.m13) - m.m5 * (m.m8 * m.m15 - m.m11 * m.m12) + m.m7 * (m.m8 * m.m13 - m.m9 * m.m12)) * invDet;
    inv.m9 = -(m.m0 * (m.m9 * m.m15 - m.m11 * m.m13) - m.m1 * (m.m8 * m.m15 - m.m11 * m.m12) + m.m3 * (m.m8 * m.m13 - m.m9 * m.m12)) * invDet;
    inv.m10 = (m.m0 * (m.m5 * m.m15 - m.m7 * m.m13) - m.m1 * (m.m4 * m.m15 - m.m7 * m.m12) + m.m3 * (m.m4 * m.m13 - m.m5 * m.m12)) * invDet;
    inv.m11 = -(m.m0 * (m.m5 * m.m11 - m.m7 * m.m9) - m.m1 * (m.m4 * m.m11 - m.m7 * m.m8) + m.m3 * (m.m4 * m.m9 - m.m5 * m.m8)) * invDet;

    inv.m12 = -(m.m4 * (m.m9 * m.m14 - m.m10 * m.m13) - m.m5 * (m.m8 * m.m14 - m.m10 * m.m12) + m.m6 * (m.m8 * m.m13 - m.m9 * m.m12)) * invDet;
    inv.m13 = (m.m0 * (m.m9 * m.m14 - m.m10 * m.m13) - m.m1 * (m.m8 * m.m14 - m.m10 * m.m12) + m.m2 * (m.m8 * m.m13 - m.m9 * m.m12)) * invDet;
    inv.m14 = -(m.m0 * (m.m5 * m.m14 - m.m6 * m.m13) - m.m1 * (m.m4 * m.m14 - m.m6 * m.m12) + m.m2 * (m.m4 * m.m13 - m.m5 * m.m12)) * invDet;
    inv.m15 = (m.m0 * (m.m5 * m.m10 - m.m6 * m.m9) - m.m1 * (m.m4 * m.m10 - m.m6 * m.m8) + m.m2 * (m.m4 * m.m9 - m.m5 * m.m8)) * invDet;

    return inv;
}

// Division of matrices (multiplication by the inverse)
// Return m1 / m2
Matrix matrix_div_matrix(Matrix m1, Matrix m2)
{
    // 1. Calculate the inverse of m2
    Matrix m2_inverse = matrix_inverse(m2);
    
    // 2. Multiply m1 by the inverse of m2
    return matrix_x_matrix(m1, m2_inverse);
}

// Return matrix initialize
Matrix  matrix_identity(void)
{
    Matrix m = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    return m;
}

//******************************************************************************//
//***                               Quaternion                               ***//
//******************************************************************************//

// Return quaternion1 + quaternion2
Quaternion  quaternion_add_quaternion(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w + q2.w;
    ret_q.x = q1.x + q2.x;
    ret_q.y = q1.y + q2.y;
    ret_q.z = q1.z + q2.z;

    return ret_q;
}

// Return quaternion1 - quaternion2
Quaternion  quaternion_sub_quaternion(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w - q2.w;
    ret_q.x = q1.x - q2.x;
    ret_q.y = q1.y - q2.y;
    ret_q.z = q1.z - q2.z;

    return ret_q;
}

// Return quaternion1 * quaternion2
Quaternion  quaternion_x_quaternion(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    ret_q.x = q1.x * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    ret_q.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    ret_q.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;

    return ret_q;
}


// Auxiliary function to calculate the inverse of a quaternion
Quaternion quaternion_inverse(Quaternion q)
{
    // Calculate the square of the norm
    float norm_squared = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    
    // If the norm is too close to zero, return an identity quaternion
    if (norm_squared < 1e-6f)
    {
        return quaternion_identity();
    }

    // Calculer l'inverse
    float inv_norm_squared = 1.0f / norm_squared;

    Quaternion result;
    result.w = q.w * inv_norm_squared;
    result.x = -q.x * inv_norm_squared;
    result.y = -q.y * inv_norm_squared;
    result.z = -q.z * inv_norm_squared;

    return result;
}

// Return quaternion1 / quaternion2
Quaternion  quaternion_div_quaternion(Quaternion q1, Quaternion q2)
{
    // To divide, multiply q1 by the inverse of q2
    Quaternion q2_inverse = quaternion_inverse(q2);
    return quaternion_x_quaternion(q1, q2_inverse);
}

// Normalization of a quaternion
Quaternion quaternion_normalize(Quaternion q)
{
    float length = sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    
    if (length == 0.0f)
        return quaternion_identity();
    
    float ilength = 1.0f / length;
    Quaternion result = {
        .x = q.x * ilength,
        .y = q.y * ilength,
        .z = q.z * ilength,
        .w = q.w * ilength
    };
    return result;
}

// Creation of a quaternion from an axis and an angle
Quaternion quaternion_from_axis_angle(Vector3 axis, float angle)
{
    float half_angle = angle * 0.5f;
    float sin_half = sinf(half_angle);
    
    Quaternion result = {
        .x = axis.x * sin_half,
        .y = axis.y * sin_half,
        .z = axis.z * sin_half,
        .w = cosf(half_angle)
    };
    return quaternion_normalize(result);
}

// Return quaternion initialize
Quaternion  quaternion_identity(void)
{
    Quaternion q = { 0, 0, 0, 1 };

    return q;
}

#ifdef __cplusplus
    }
#endif
