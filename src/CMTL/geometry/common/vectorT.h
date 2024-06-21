#ifndef __common_vectorT_h__
#define __common_vectorT_h__

#include "number_utils.h"

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <array>

namespace CMTL{
namespace geometry{

/**
 * @brief fixed size valu type container
 * @tparam T value type
 * @tparam DIM dimension of vector
 */
template<typename T, unsigned DIM>
class VectorT
{
    protected:
        /* main container */
        typedef std::array<T, DIM> container;
        container _values;

    public:
        /* value type */
        typedef T value_type;

        /* return dimension of this vector */
        static const unsigned dimension()
        {
            return DIM;
        }

        /* alias of dimension */
        static const unsigned size()
        {
            return dimension();
        }

        /* default constructor */
        constexpr VectorT()
        {
        }

        /* construct using DIM values */
        template<typename ... TT, typename = typename std::enable_if<sizeof...(TT) == DIM>::type>
        constexpr VectorT(TT... vs) : _values{{util_cast<TT, T>(vs)...}}
        {
        }

        /* default copy constructor*/
        VectorT(const VectorT& other) = default;

        /* copy & cast constructor */
        template<typename TT>
        explicit VectorT(const VectorT<TT, DIM>& other)
        {
            operator=(other);
        }

        /* default assign operator */
        VectorT& operator=(const VectorT& other) = default;

        /* assign & cast operator */
        template<typename TT>
        VectorT& operator=(const VectorT<TT, DIM>& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] = util_cast<TT, T>(other[i]);
            return *this;
        }

        /* deconstructor */
        virtual ~VectorT()
        {
        }

        /* get the writable ith value */
        T& operator[](unsigned i)
        {
            assert(i < DIM);
            return _values[i];
        }

        /* get the const ith value */
        const T& operator[](unsigned i) const
        {
            assert(i < DIM);
            return _values[i];
        }

        /* self-addition */
        const VectorT& operator+=(const VectorT& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] += other._values[i];
            return *this;
        }

        /* add two vector */
        VectorT operator+(const VectorT& other) const
        {
            return VectorT(*this) += other;
        }

        /* self-subtract */
        const VectorT& operator-=(const VectorT& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] -= other._values[i];
            return *this;
        }

        /* subtract two vector */
        VectorT operator-(const VectorT& other) const
        {
            return VectorT(*this) -= other;
        }

        /* self-scale by multiply */
        const VectorT& operator*=(const T& scale)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] *= scale;
            return *this;
        }

        /* do scale by multiply */
        VectorT operator*(const T& scale) const
        {
            return VectorT(*this) *= scale;
        }

        /* self-scale by divide */
        const VectorT& operator/=(const T& scale)
        {
            assert(scale != T(0));
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] /= scale;
            return *this;
        }

        /* do scale by divide */
        VectorT operator/(const T& scale) const
        {
            return VectorT(*this) /= scale;
        }

        /* scalar product */
        T operator*(const VectorT& other) const
        {
            T result(0);
            for(unsigned i = 0; i < DIM; ++i)
                result += (_values[i] * other._values[i]);
            return result;
        }

        /* scalar product */
        T dot(const VectorT& other) const
        {
            return *this * other;
        }

        /* square norm */
        T norm_square() const
        {
            return (*this) * (*this);
        }

        /* square norm */
        T length_square() const
        {
            return norm_square();
        }

        /* comparator */
        bool operator==(const VectorT& other) const
        {
            for(unsigned i = 0; i < DIM; ++i)
                if(_values[i] != other[i])
                    return false;
            return true;
        }

        /* comparator */
        bool operator!=(const VectorT& other) const
        {
            return !(*this == other);
        }

        /* comparator */
        bool operator<(const VectorT& other) const
        {
            for(unsigned i = 0; i < DIM; ++i)
                if(_values[i] != other._values[i])
                    return _values[i] < other._values[i];
            return false;
        }

        friend std::ostream& operator<<(std::ostream& os, const VectorT& vec)
        {
            os << "[" << vec[0];
            for(unsigned i = 1; i < vec.dimension(); ++i)
            {
                os << "," << vec[i];
            }
            os << "]";
            return os;
        }
};

}   // namespace geometry
}   // namespace CMTL

#endif  // __common_vectorT_h__