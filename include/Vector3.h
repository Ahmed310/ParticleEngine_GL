#ifndef VECTOR3_H
#define VECTOR3_H
#include <math.h>

class Vector3
{
    public:
        Vector3(float X ,float Y , float Z );        // Constructor
        Vector3 operator+(const Vector3 &vec);       // overload operator +
        Vector3 operator+=(const Vector3 &vec);      // overload operator +=
        Vector3 operator-(const Vector3 &vec);
        Vector3 operator-=(const Vector3 &vec);
        Vector3 operator*(float num);
        Vector3 operator*=(float num);
        Vector3 operator/(float num);
        Vector3 operator/=(float num);
        Vector3 operator~(void);
        Vector3 operator*(const Vector3 &vec);
        bool operator== (Vector3 &vec);
        bool operator!= (Vector3 &vec);
        float Dot(Vector3 &vec);                      // Perform Dot product
        float Length(void);
        Vector3 Normalize(void);
        float Distance(Vector3 &vec);

public:
        float x, y, z;
};

#endif // VECTOR3_H
