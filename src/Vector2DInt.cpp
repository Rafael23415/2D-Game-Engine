#include "Vector2DInt.h"

#include <cmath>

namespace Engineering2D::Math
{
    const Vector2DInt Vector2DInt::zero()
    {
        Vector2DInt v {0, 0};
        return v;
    }

    const Vector2DInt Vector2DInt::one()
    {
        Vector2DInt v {1, 1};
        return v;
    }
    
    const Vector2DInt Vector2DInt::up()
    {
        Vector2DInt v {0, 1};
        return v;
    }

    const Vector2DInt Vector2DInt::down()
    {
        Vector2DInt v {0, -1};
        return v;
    }

    const Vector2DInt Vector2DInt::left()
    {
        Vector2DInt v {-1, 0};
        return v;
    }

    const Vector2DInt Vector2DInt::right()
    {
        Vector2DInt v {1, 0};
        return v;
    }

    Vector2DInt& Vector2DInt::operator+=(const Vector2DInt& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }
    
    Vector2DInt operator+(const Vector2DInt& a, const Vector2DInt& b)
    {
        Vector2DInt c = a;
        c += b;

        return c;
    }

    Vector2DInt operator-(const Vector2DInt& a, const Vector2DInt& b)
    {
        Vector2DInt c = a;
        c.x -= b.x;
        c.y -= b.y;

        return c;
    }

    Vector2DInt operator*(const Vector2DInt& v, int s)
    {
        Vector2DInt c = v;
        c.x *= s;
        c.y *= s;

        return c;
    }

    bool operator==(const Vector2DInt& a, const Vector2DInt& b)
    {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(const Vector2DInt& a, const Vector2DInt& b)
    {
        return !(a==b);
    }
    
    std::ostream& operator<<(std::ostream& os, const Vector2DInt& v)
    {
        return os << "X: " << v.x << "\nY: " << v.y;
    }
    
    double length(const Vector2DInt& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
}
