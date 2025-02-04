/**
 * @file Point.h
 * @brief Defines the Point class for representing a 3D point or vector in space.
 *
 * @copyright Copyright (c) 2025 Kantarion. All rights reserved.
 *
 * @author Andrey Miroshnichenko
 * @date 2025.01.30
 *
 * Licensed under the MIT License. See LICENSE file in the project root for full license
 * information.
 */

#pragma once

#include "Geometry.h"

#include <cmath>
#include <utility>

namespace Kantarion::Geometry {

/**
 * @class Point
 * @brief Represents a point or vector in 3D space.
 */
class Point {
    /**
     * @brief Compares two scalar values with relative tolerance.
     * @param p_ValueA First value.
     * @param p_ValueB Second value.
     * @param p_Epsilon Allowed error tolerance.
     * @return True if values are nearly equal.
     */
    static constexpr bool nearlyEqual(
        Scalar_t p_ValueA, Scalar_t p_ValueB, Scalar_t p_Epsilon = sc_Precision)
    {
        return std::fabs(p_ValueA - p_ValueB)
            <= p_Epsilon * std::max(std::fabs(p_ValueA), std::fabs(p_ValueB));
    }

public:
    /**
     * @brief Default constructor.
     * @param p_X X-coordinate.
     * @param p_Y Y-coordinate.
     * @param p_Z Z-coordinate.
     */
    explicit Point(
        Coordinate_t p_X = Coordinate_t{},
        Coordinate_t p_Y = Coordinate_t{},
        Coordinate_t p_Z = Coordinate_t{})
        : m_X(p_X)
        , m_Y(p_Y)
        , m_Z(p_Z)
    {
    }

    /**
     * @brief Copy constructor.
     * @param p_Other Another Point object to copy.
     */
    Point(const Point& p_Other)
        : m_X(p_Other.m_X)
        , m_Y(p_Other.m_Y)
        , m_Z(p_Other.m_Z)
    {
    }

    /**
     * @brief Copy assignment operator.
     * @param p_Other Another Point object to assign.
     * @return Reference to this Point.
     */
    Point& operator=(const Point& p_Other)
    {
        if (this != &p_Other) {
            m_X = p_Other.m_X;
            m_Y = p_Other.m_Y;
            m_Z = p_Other.m_Z;
        }
        return *this;
    }

    /**
     * @brief Move constructor.
     * @param p_Other Another Point object to move.
     */
    Point(Point&& p_Other) noexcept
        : m_X(std::exchange(p_Other.m_X, Coordinate_t{}))
        , m_Y(std::exchange(p_Other.m_Y, Coordinate_t{}))
        , m_Z(std::exchange(p_Other.m_Z, Coordinate_t{}))
    {
    }

    /**
     * @brief Move assignment operator.
     * @param p_Other Another Point object to move-assign.
     * @return Reference to this Point.
     */
    Point& operator=(Point&& p_Other) noexcept
    {
        if (this != &p_Other) {
            m_X = std::exchange(p_Other.m_X, Coordinate_t{});
            m_Y = std::exchange(p_Other.m_Y, Coordinate_t{});
            m_Z = std::exchange(p_Other.m_Z, Coordinate_t{});
        }
        return *this;
    }

    /**
     * @brief Destructor.
     */
    virtual ~Point() noexcept = default;

    /**
     * @brief Gets the X-coordinate.
     * @return X-coordinate value.
     */
    Coordinate_t getX() const
    {
        return m_X;
    }

    /**
     * @brief Gets the Y-coordinate.
     * @return Y-coordinate value.
     */
    Coordinate_t getY() const
    {
        return m_Y;
    }

    /**
     * @brief Gets the Z-coordinate.
     * @return Z-coordinate value.
     */
    Coordinate_t getZ() const
    {
        return m_Z;
    }

    /**
     * @brief Sets the X-coordinate.
     * @param p_Value New X-coordinate value.
     */
    void setX(Coordinate_t p_Value)
    {
        m_X = p_Value;
    }

    /**
     * @brief Sets the Y-coordinate.
     * @param p_Value New Y-coordinate value.
     */
    void setY(Coordinate_t p_Value)
    {
        m_Y = p_Value;
    }

    /**
     * @brief Sets the Z-coordinate.
     * @param p_Value New Z-coordinate value.
     */
    void setZ(Coordinate_t p_Value)
    {
        m_Z = p_Value;
    }

    /**
     * @brief Computes the magnitude (length) of the vector.
     * @return Magnitude of the vector.
     */
    Distance_t magnitude() const
    {
        return std::sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
    }

    /**
     * @brief Normalizes the vector.
     * @return Unit vector in the same direction.
     */
    Point normalize() const
    {
        // Get magnitude of the Vector
        auto l_Magnitude = magnitude();

        // Prevent division by zero
        if (l_Magnitude > sc_Precision) {
            return Point(m_X / l_Magnitude, m_Y / l_Magnitude, m_Z / l_Magnitude);
        } else {
            // If the magnitude is zero, return the zero vector
            return Point{};
        }
    }

    /**
     * @brief Equality comparison.
     * @param p_Other Another Point object.
     * @return True if both points are nearly equal.
     */
    bool operator==(const Point& p_Other) const
    {
        return nearlyEqual(m_X, p_Other.m_X) && nearlyEqual(m_Y, p_Other.m_Y)
            && nearlyEqual(m_Z, p_Other.m_Z);
    }

    /**
     * @brief Inequality comparison.
     * @param p_Other Another Point object.
     * @return True if points are not equal.
     */
    bool operator!=(const Point& p_Other) const
    {
        return !(*this == p_Other);
    }

    /**
     * @brief Computes the distance to another Point.
     * @param p_Other Another Point.
     * @return Euclidean distance.
     */
    Distance_t distance(const Point& p_Other) const
    {
        Scalar_t l_dX = p_Other.m_X - m_X;
        Scalar_t l_dY = p_Other.m_Y - m_Y;
        Scalar_t l_dZ = p_Other.m_Z - m_Z;
        return std::sqrt(l_dX * l_dX + l_dY * l_dY + l_dZ * l_dZ);
    }

    /**
     * @brief Adds two points (vector addition).
     * @param p_Other Another Point.
     * @return Resulting Point.
     */
    Point operator+(const Point& p_Other) const
    {
        return Point(m_X + p_Other.m_X, m_Y + p_Other.m_Y, m_Z + p_Other.m_Z);
    }

    /**
     * @brief Subtracts two points (vector subtraction).
     * @param p_Other Another Point.
     * @return Resulting Point.
     */
    Point operator-(const Point& p_Other) const
    {
        return Point(m_X - p_Other.m_X, m_Y - p_Other.m_Y, m_Z - p_Other.m_Z);
    }

    /**
     * @brief Scales the point by a scalar value.
     * @param p_Scalar Scaling factor.
     * @return Scaled Point.
     */
    Point operator*(Scalar_t p_Scalar) const
    {
        return Point(m_X * p_Scalar, m_Y * p_Scalar, m_Z * p_Scalar);
    }

    /**
     * @brief Computes the dot product with another Point.
     * @param p_Other Another Point.
     * @return Dot product result.
     */
    Scalar_t dot(const Point& p_Other) const
    {
        return m_X * p_Other.m_X + m_Y * p_Other.m_Y + m_Z * p_Other.m_Z;
    }

    /**
     * @brief Computes the cross product with another Point.
     * @param p_Other Another Point.
     * @return Cross product result.
     */
    Point cross(const Point& p_Other) const
    {
        return Point(
            m_Y * p_Other.m_Z - m_Z * p_Other.m_Y,
            m_Z * p_Other.m_X - m_X * p_Other.m_Z,
            m_X * p_Other.m_Y - m_Y * p_Other.m_X);
    }

    /**
     * @brief Overloads the stream insertion operator for serialization.
     * @param p_Stream Output stream.
     * @param p_Point Point to serialize.
     * @return Reference to the modified stream.
     */
    friend OutputStream_t& operator<<(OutputStream_t& p_Stream, const Point& p_Point)
    {
        p_Stream << "Point[" << p_Point.m_X << ", " << p_Point.m_Y << ", " << p_Point.m_Z << "]";
        return p_Stream;
    }

    /**
     * @brief Overloads the stream extraction operator for deserialization.
     * @param p_Stream Input stream.
     * @param p_Point Point to deserialize.
     * @return Reference to the modified stream.
     */
    friend InputStream_t& operator>>(InputStream_t& p_Stream, Point& p_Point)
    {
        Coordinate_t x{Coordinate_t{}};
        Coordinate_t y{Coordinate_t{}};
        Coordinate_t z{Coordinate_t{}};
        if (p_Stream >> x >> y >> z) {
            p_Point.m_X = x;
            p_Point.m_Y = y;
            p_Point.m_Z = z;
        } else {
            p_Point.m_X = x;
            p_Point.m_Y = y;
            p_Point.m_Z = z;
        }
        return p_Stream;
    }

private:
    Coordinate_t m_X; ///< X-coordinate.
    Coordinate_t m_Y; ///< Y-coordinate.
    Coordinate_t m_Z; ///< Z-coordinate.
};

} // namespace Kantarion::Geometry
