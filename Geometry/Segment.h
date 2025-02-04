/**
 * @file Segment.h
 * @brief Defines the Segment class for representing a segment in 3D space.
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

#include "Point.h"

#include <algorithm>
#include <cmath>

namespace Kantarion::Geometry {

/**
 * @class Segment
 * @brief Represents a segment in 3D space.
 */
class Segment {
public:
    /**
     * @brief Start point of the segment.
     */
    Point m_Start;

    /**
     * @brief End point of the segment.
     */
    Point m_End;

    /**
     * @brief Constructs a Segment from two points.
     * @param p_Start The starting point of the segment.
     * @param p_End The ending point of the segment.
     */
    Segment(const Point& p_Start, const Point& p_End)
        : m_Start(p_Start)
        , m_End(p_End)
    {
    }

    /**
     * @brief Computes the closest distance between two segments.
     *
     * This function calculates the shortest distance between two segments using vector projections
     * and clamping the results to ensure the closest points lie within the segment bounds.
     * The computation follows the approach outlined in AndreyMiroshnichenkoGeom.pdf.
     *
     * @param p_Segment1 The first segment.
     * @param p_Segment2 The second segment.
     * @return The shortest distance between the two segments.
     */
    static Distance_t closestDistance(const Segment& p_Segment1, const Segment& p_Segment2)
    {
        // Direction vector of first segment
        Point l_D1 = p_Segment1.m_End - p_Segment1.m_Start;

        // Direction vector of second segment
        Point l_D2 = p_Segment2.m_End - p_Segment2.m_Start;

        Point l_R = p_Segment1.m_Start - p_Segment2.m_Start;

        Scalar_t l_A = l_D1.dot(l_D1);
        Scalar_t l_E = l_D2.dot(l_D2);
        Scalar_t l_F = l_D2.dot(l_R);

        Scalar_t l_B = l_D1.dot(l_D2);
        Scalar_t l_C = l_D1.dot(l_R);

        Scalar_t l_Denominator = l_A * l_E - l_B * l_B;

        Scalar_t l_S, l_T;

        // If segments are not parallel
        if (std::fabs(l_Denominator) > sc_Precision) {
            l_S = (l_B * l_F - l_C * l_E) / l_Denominator;
            l_T = (l_A * l_F - l_B * l_C) / l_Denominator;
        } else {
            // Segments are parallel, pick arbitrary values
            l_S = Scalar_t{};
            l_T = l_F / l_E;
        }

        // Clamp values of s and t within [0, 1] to ensure closest points are within segment bounds
        l_S = std::clamp(l_S, sc_ParametricL, sc_ParametricH);
        l_T = std::clamp(l_T, sc_ParametricL, sc_ParametricH);

        // Closest points on each segment
        Point l_ClosestPoint1 = p_Segment1.m_Start + l_D1 * l_S;
        Point l_ClosestPoint2 = p_Segment2.m_Start + l_D2 * l_T;

        return l_ClosestPoint1.distance(l_ClosestPoint2);
    }
};

} // namespace Kantarion::Geometry
