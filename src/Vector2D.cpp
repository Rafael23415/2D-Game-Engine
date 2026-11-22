#include "Vector2D.h"

#include <cmath>

namespace Engineering2D::Math
{
    Vector2D Vector2D::zero()
    {
        Vector2D v {0, 0};
        return v;
    }

    Vector2D Vector2D::one()
    {
        Vector2D v {1, 1};
        return v;
    }
    
    Vector2D Vector2D::up()
    {
        Vector2D v {0, 1};
        return v;
    }

    Vector2D Vector2D::down()
    {
        Vector2D v {0, -1};
        return v;
    }

    Vector2D Vector2D::left()
    {
        Vector2D v {-1, 0};
        return v;
    }

    Vector2D Vector2D::right()
    {
        Vector2D v {1, 0};
        return v;
    }
    
    Vector2D& Vector2D::operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    Vector2D Vector2D::normalize() const
    {
        if (length(*this) != 0)
        {
            Vector2D n = *this;
            n.x /= length(*this);
            n.y /= length(*this);
            
            return n;
        }
        return Vector2D::zero();
    }

    Vector2D operator+(const Vector2D& a, const Vector2D& b)
    {
        Vector2D c = a;
        c += b;

        return c;
    }

    Vector2D operator-(const Vector2D& a, const Vector2D& b)
    {
        Vector2D c = a;
        c.x -= b.x;
        c.y -= b.y;

        return c;
    }

    Vector2D operator*(const Vector2D& v, double s)
    {
        Vector2D c = v;
        c.x *= s;
        c.y *= s;

        return c;
    }

    bool operator==(const Vector2D& a, const Vector2D& b)
    {
        return a.x == b.x && a.y == b.y;
    }

    bool operator!=(const Vector2D& a, const Vector2D& b)
    {
        return !(a==b);
    }

    double length(const Vector2D& v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
}