#pragma once

#include <iostream>
#include <limits>

namespace Kantarion::Geometry {

/**
 * @typedef Scalar_t
 * @brief Type alias for scalar values used in geometric computations.
 */
using Scalar_t = double;

/**
 * @typedef Coordinate_t
 * @brief Type alias for coordinate values in 3D space.
 */
using Coordinate_t = Scalar_t;

/**
 * @typedef Distance_t
 * @brief Type alias for distance measurement in 3D space.
 */
using Distance_t = Coordinate_t;

/**
 * @typedef InputStream_t
 * @brief Type alias for deserialization from an input stream.
 */
using InputStream_t = std::istream;

/**
 * @typedef OutputStream_t
 * @brief Type alias for serialization to an output stream.
 */
using OutputStream_t = std::ostream;

/**
 * @brief Precision value based on the floating-point type.
 */
static constexpr Scalar_t sc_Precision = std::numeric_limits<Scalar_t>::epsilon();

/**
 * @brief Paramatric low limit.
 */
static constexpr Scalar_t sc_ParametricL = 0.0;

/**
 * @brief Paramatric high limit.
 */
static constexpr Scalar_t sc_ParametricH = 1.0;

} // namespace Kantarion::Geometry
