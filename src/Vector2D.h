#pragma once

namespace Engineering2D::Math
{
    /**
     * Vector with 2 double parameters.
     * Can be normalized.
     * 
     * @param double x
     * @param double y
     */
    struct Vector2D
    {
        double x{ 0.0 };
        double y{ 0.0 };
        
        /**
         * @return (0, 0)
         */
        static Vector2D zero();
        /**
         * @return (1, 1)
         */
        static Vector2D one();
        /**
         * @return (0, 1)
         */
        static Vector2D up();
        /**
         * @return (0, -1)
         */
        static Vector2D down();
        /**
         * @return (-1, 0)
         */
        static Vector2D left();
        /**
         * @return (1, 0)
         */
        static Vector2D right();
        
        Vector2D& operator+=(const Vector2D& other);
        
        
        /**
         * @return Vector with the same direction, but lenght of 1
         */
        Vector2D normalize() const;
    };
    
    double length(const Vector2D& v);
    
    Vector2D operator+(const Vector2D& a, const Vector2D& b);
    
    Vector2D operator-(const Vector2D& a, const Vector2D& b);
    
    Vector2D operator*(const Vector2D& v, double s);
    
    bool operator==(const Vector2D& a, const Vector2D& b);
    
    bool operator!=(const Vector2D& a, const Vector2D& b);
}