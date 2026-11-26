#pragma once

namespace Engineering2D::Math
{
    /**
     * Vector with 2 float parameters.
     * Can be normalized.
     * 
     * @param float x
     * @param float y
     */
    struct Vector2D
    {
        float x{ 0.0 };
        float y{ 0.0 };
        
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
    
    float length(const Vector2D& v);
    
    Vector2D operator+(const Vector2D& a, const Vector2D& b);
    
    Vector2D operator-(const Vector2D& a, const Vector2D& b);
    
    Vector2D operator*(const Vector2D& v, float s);
    
    bool operator==(const Vector2D& a, const Vector2D& b);
    
    bool operator!=(const Vector2D& a, const Vector2D& b);
}