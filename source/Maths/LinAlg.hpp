// LinAlg2D_colmajor.hpp
#pragma once

#include <cmath>
#include <concepts>
#include <iostream>
#include <limits>
#include <utility>
#include <cassert>

namespace linalg {

// ---------------------------
// Vector2D
// ---------------------------
template<std::floating_point T>
class Vector2D {
public:
    T x;
    T y;

    // ctors
    constexpr Vector2D() noexcept : x{T(0)}, y{T(0)} {}
    constexpr Vector2D(T xx, T yy) noexcept : x{xx}, y{yy} {}

    Vector2D(const Vector2D&) = default;
    Vector2D(Vector2D&&) noexcept = default;

    void swap(Vector2D& other) noexcept {
        using std::swap;
        swap(x, other.x);
        swap(y, other.y);
    }

    Vector2D& operator=(Vector2D rhs) noexcept {
        swap(rhs);
        return *this;
    }

    // index access
    T& operator[](std::size_t i) & {
        assert(i < 2);
        return (i == 0) ? x : y;
    }
    const T& operator[](std::size_t i) const & {
        assert(i < 2);
        return (i == 0) ? x : y;
    }

    // compound assignments (members)
    Vector2D& operator+=(const Vector2D& rhs) noexcept {
        x += rhs.x; y += rhs.y;
        return *this;
    }
    Vector2D& operator-=(const Vector2D& rhs) noexcept {
        x -= rhs.x; y -= rhs.y;
        return *this;
    }
    Vector2D& operator*=(T s) noexcept {
        x *= s; y *= s;
        return *this;
    }
    Vector2D& operator/=(T s) {
        assert(s != T(0));
        x /= s; y /= s;
        return *this;
    }

    Vector2D operator-() const noexcept { return Vector2D{-x, -y}; }

    // vector ops
    T dot(const Vector2D& rhs) const noexcept { return x * rhs.x + y * rhs.y; }
    T cross(const Vector2D& rhs) const noexcept { return x * rhs.y - y * rhs.x; }

    T length() const noexcept { return std::sqrt(x * x + y * y); }

    // length_reciprocal: 1 / sqrt(x*x + y*y)
    // returns +inf when vector is zero-length
    T length_reciprocal() const noexcept {
        T lsq = x * x + y * y;
        return T(1) / std::sqrt(lsq);
    }

    Vector2D normalized() const noexcept {
        T lr = length_reciprocal();
        if (!std::isfinite(lr)) return Vector2D{T(0), T(0)};
        return *this * lr;
    }

};

// non-member vector binary ops (built from compound assignments)
template<std::floating_point T>
inline Vector2D<T> operator+(Vector2D<T> lhs, const Vector2D<T>& rhs) { lhs += rhs; return lhs; }

template<std::floating_point T>
inline Vector2D<T> operator-(Vector2D<T> lhs, const Vector2D<T>& rhs) { lhs -= rhs; return lhs; }

template<std::floating_point T>
inline Vector2D<T> operator*(Vector2D<T> v, T s) { v *= s; return v; }

template<std::floating_point T>
inline Vector2D<T> operator*(T s, Vector2D<T> v) { v *= s; return v; }

template<std::floating_point T>
inline Vector2D<T> operator/(Vector2D<T> v, T s) { v /= s; return v; }

template<std::floating_point T>
bool operator==(const Vector2D<T>& a, const Vector2D<T>& b) noexcept {
        return a.x == b.x && a.y == b.y;
}

template<std::floating_point T>
bool operator!=(const Vector2D<T>& a, const Vector2D<T>& b) noexcept {
    return !(a == b);
}


// stream operators (friends)
template<std::floating_point T>
std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v) {
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

template<std::floating_point T>
std::istream& operator>>(std::istream& is, Vector2D<T>& v) {
    T xx, yy;
    if (is >> xx >> yy) {
        v.x = xx; v.y = yy;
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

template<std::floating_point T>
bool approx_equal(const Vector2D<T>& a, const Vector2D<T>& b, T eps = T(1e-12)) noexcept {
    return (std::abs(a.x - b.x) <= eps) && (std::abs(a.y - b.y) <= eps);
}

// ---------------------------
// Matrix2D (column-major storage)
// Members are declared in memory-order (column-major): a, c, b, d
// Mathematically the matrix is:
//   [ a  b ]
//   [ c  d ]
// where first column = (a, c), second column = (b, d).
// ---------------------------
template<std::floating_point T>
class Matrix2D {
public:
    // Declared in column-major memory order:
    //  first column (a, c), then second column (b, d)
    T a; // m00
    T c; // m10
    T b; // m01
    T d; // m11

    // default ctor -> identity
    constexpr Matrix2D() noexcept : a{T(1)}, c{T(0)}, b{T(0)}, d{T(1)} {}

    // constructor from matrix elements in natural math order (a, b, c, d)
    // where the matrix is [[a, b], [c, d]]
    constexpr Matrix2D(T aa, T bb, T cc, T dd) noexcept
        : a{aa}, c{cc}, b{bb}, d{dd} {}

    Matrix2D(const Matrix2D&) = default;
    Matrix2D(Matrix2D&&) noexcept = default;

    void swap(Matrix2D& other) noexcept {
        using std::swap;
        swap(a, other.a);
        swap(c, other.c);
        swap(b, other.b);
        swap(d, other.d);
    }

    Matrix2D& operator=(Matrix2D rhs) noexcept {
        swap(rhs);
        return *this;
    }

    // compound-assignment members
    Matrix2D& operator+=(const Matrix2D& rhs) noexcept {
        a += rhs.a; c += rhs.c; b += rhs.b; d += rhs.d;
        return *this;
    }

    Matrix2D& operator-=(const Matrix2D& rhs) noexcept {
        a -= rhs.a; c -= rhs.c; b -= rhs.b; d -= rhs.d;
        return *this;
    }

    Matrix2D& operator*=(T s) noexcept {
        a *= s; c *= s; b *= s; d *= s;
        return *this;
    }

    // matrix multiplication: this = this * rhs
    // math: M = M * R  ; both in math form [[a b],[c d]]
    Matrix2D& operator*=(const Matrix2D& rhs) noexcept {
        // compute using math-order aliases:
        // this math elements: A = a, B = b, C = c, D = d
        // rhs math elements: RA = rhs.a, RB = rhs.b, RC = rhs.c, RD = rhs.d
        T A = a; T B = b; T C = c; T D = d;
        T RA = rhs.a; T RB = rhs.b; T RC = rhs.c; T RD = rhs.d;

        T na = A * RA + B * RC; // m00
        T nb = A * RB + B * RD; // m01
        T nc = C * RA + D * RC; // m10
        T nd = C * RB + D * RD; // m11

        // store in column-major member order (a, c, b, d)
        a = na; c = nc; b = nb; d = nd;
        return *this;
    }

    // determinant (mathematical)
    T det() const noexcept {
        // det = a*d - b*c   (using math-order)
        return a * d - b * c;
    }

    // inverse (throws if nearly singular)
    Matrix2D inverse() const {
        T determinant = det();
        if (std::abs(determinant) < std::numeric_limits<T>::epsilon() * T(10)) {
            throw std::runtime_error("Matrix2D::inverse(): matrix is singular or nearly singular");
        }
        T invdet = T(1) / determinant;
        // inverse math-order: [[ d, -b ], [ -c, a ]] * invdet
        return Matrix2D(d, -b, -c, a) *  invdet;
    }

    Matrix2D transpose() const {
        return Matrix2D(a, c, b, d);
    }

    // apply to vector: result = M * v
    Vector2D<T> apply(const Vector2D<T>& v) const noexcept {
        // math-order:
        // x' = a * v.x + b * v.y
        // y' = c * v.x + d * v.y
        return Vector2D<T>{ a * v.x + b * v.y, c * v.x + d * v.y };
    }

    // factory helpers (convenience)
    static constexpr Matrix2D rotation(T radians) noexcept {
        T sins = std::sin(radians);
        T coss = std::cos(radians);
        // math-order a=coss, b=-s, c=s, d=coss
        return Matrix2D{ coss, -sins, sins, coss };
    }
    static constexpr Matrix2D scale(T sx, T sy) noexcept {
        return Matrix2D{ sx, T(0), T(0), sy };
    }

};

// non-member matrix ops using compound-assignment idiom
template<std::floating_point T>
inline Matrix2D<T> operator+(Matrix2D<T> lhs, const Matrix2D<T>& rhs) { lhs += rhs; return lhs; }

template<std::floating_point T>
inline Matrix2D<T> operator-(Matrix2D<T> lhs, const Matrix2D<T>& rhs) { lhs -= rhs; return lhs; }

template<std::floating_point T>
inline Matrix2D<T> operator*(Matrix2D<T> lhs, T s) { lhs *= s; return lhs; }

template<std::floating_point T>
inline Matrix2D<T> operator*(T s, Matrix2D<T> rhs) { rhs *= s; return rhs; }

template<std::floating_point T>
inline Matrix2D<T> operator*(Matrix2D<T> lhs, const Matrix2D<T>& rhs) { lhs *= rhs; return lhs; }

template<std::floating_point T>
inline Vector2D<T> operator*(const Matrix2D<T>& M, const Vector2D<T>& v) { return M.apply(v); }

// stream IO
template<std::floating_point T>
std::ostream& operator<<(std::ostream& os, const Matrix2D<T>& m) {
    // print in mathematical row-major layout for readability
    os << "[[" << m.a << ", " << m.b << "], [" << m.c << ", " << m.d << "]]";
    return os;
}

template<std::floating_point T>
std::istream& operator>>(std::istream& is, Matrix2D<T>& m) {
    T aa, bb, cc, dd;
    if (is >> aa >> bb >> cc >> dd) {
        // input assumed in math-order [a b c d]
        m.a = aa; m.b = bb; m.c = cc; m.d = dd;
    } else {
        is.setstate(std::ios::failbit);
    }
    return is;
}

} // namespace linalg
