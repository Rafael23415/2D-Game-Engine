#pragma once

#include <iosfwd>

namespace Engineering2D::Math
{
    /**
     * Vector with 2 int parameters.
     * Can't be normalized.
     * 
     * @param int x
     * @param int y
     */
    struct Vector2DInt
    {
        int x{ 0 };
        int y{ 0 };

        /**
         * @return (0, 0)
         */
        static const Vector2DInt zero();
        /**
         * @return (1, 1)
         */
        static const Vector2DInt one();
        /**
         * @return (0, 1)
         */
        static const Vector2DInt up();
        /**
         * @return (0, -1)
         */
        static const Vector2DInt down();
        /**
         * @return (-1, 0)
         */
        static const Vector2DInt left();
        /**
         * @return (1, 0)
         */
        static const Vector2DInt right();
        
        Vector2DInt& operator+=(const Vector2DInt& other);
    };
    
    double length(const Vector2DInt& v);

    Vector2DInt operator+(const Vector2DInt& a, const Vector2DInt& b);

    Vector2DInt operator-(const Vector2DInt& a, const Vector2DInt& b);

    Vector2DInt operator*(const Vector2DInt& v, int s);

    bool operator==(const Vector2DInt& a, const Vector2DInt& b);

    bool operator!=(const Vector2DInt& a, const Vector2DInt& b);

    std::ostream& operator<<(std::ostream& os, const Vector2DInt& v);
}
