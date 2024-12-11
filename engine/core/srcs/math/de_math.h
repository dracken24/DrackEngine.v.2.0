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

#include <raylib.h>

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
    Matrix ret_m;
    ret_m.m0 = m1.m0 * m2.m0;
    ret_m.m1 = m1.m1 * m2.m1;
    ret_m.m2 = m1.m2 * m2.m2;
    ret_m.m3 = m1.m3 * m2.m3;

    ret_m.m4 = m1.m4 * m2.m4;
    ret_m.m5 = m1.m5 * m2.m5;
    ret_m.m6 = m1.m6 * m2.m6;
    ret_m.m7 = m1.m7 * m2.m7;

    ret_m.m8 = m1.m8 * m2.m8;
    ret_m.m9 = m1.m9 * m2.m9;
    ret_m.m10 = m1.m10 * m2.m10;
    ret_m.m11 = m1.m11 * m2.m11;

    ret_m.m12 = m1.m12 * m2.m12;
    ret_m.m13 = m1.m13 * m2.m13;
    ret_m.m14 = m1.m14 * m2.m14;
    ret_m.m15 = m1.m15 * m2.m15;

    return ret_m;
}

// Return m1 / m2
Matrix  matrix_div_matrix(Matrix m1, Matrix m2)
{
    Matrix ret_m;
    ret_m.m0 = m1.m0 / m2.m0;
    ret_m.m1 = m1.m1 / m2.m1;
    ret_m.m2 = m1.m2 / m2.m2;
    ret_m.m3 = m1.m3 / m2.m3;

    ret_m.m4 = m1.m4 / m2.m4;
    ret_m.m5 = m1.m5 / m2.m5;
    ret_m.m6 = m1.m6 / m2.m6;
    ret_m.m7 = m1.m7 / m2.m7;

    ret_m.m8 = m1.m8 / m2.m8;
    ret_m.m9 = m1.m9 / m2.m9;
    ret_m.m10 = m1.m10 / m2.m10;
    ret_m.m11 = m1.m11 / m2.m11;

    ret_m.m12 = m1.m12 / m2.m12;
    ret_m.m13 = m1.m13 / m2.m13;
    ret_m.m14 = m1.m14 / m2.m14;
    ret_m.m15 = m1.m15 / m2.m15;

    return ret_m;
}

// Return matrice renitialize
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
Quaternion  matrix_add_matrix(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w + q2.w;
    ret_q.x = q1.x + q2.x;
    ret_q.y = q1.y + q2.y;
    ret_q.z = q1.z + q2.z;

    return ret_q;
}

// Return quaternion1 - quaternion2
Quaternion  matrix_sud_matrix(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w - q2.w;
    ret_q.x = q1.x - q2.x;
    ret_q.y = q1.y - q2.y;
    ret_q.z = q1.z - q2.z;

    return ret_q;
}

// Return quaternion1 * quaternion2
Quaternion  matrix_x_matrix(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w * q2.w;
    ret_q.x = q1.x * q2.x;
    ret_q.y = q1.y * q2.y;
    ret_q.z = q1.z * q2.z;

    return ret_q;
}

// Return quaternion1 / quaternion2
Quaternion  matrix_div_matrix(Quaternion q1, Quaternion q2)
{
    Quaternion ret_q;
    ret_q.w = q1.w / q2.w;
    ret_q.x = q1.x / q2.x;
    ret_q.y = q1.y / q2.y;
    ret_q.z = q1.z / q2.z;

    return ret_q;
}

// Return quaternion initialize
Quaternion  quaternion_identity(void)
{
    Quaternion q = { 0, 0, 0, 1 };

    return q;
}
