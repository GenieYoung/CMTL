#ifndef __common_vectorT_h__
#define __common_vectorT_h__

#include "number_utils.h"

#include <iostream>
#include <assert.h>
#include <array>
#include <algorithm>

namespace CMTL{

/**
 * @brief fixed size value type container
 * @tparam T value type
 * @tparam DIM dimension of vector
 */
template<typename T, unsigned DIM, typename Derived>
class VectorT
{
    protected:
        /* main container */
        typedef std::array<T, DIM> container;
        container _values;

    public:
        /* value type */
        typedef T value_type;

        /* origin vector */
        static Derived Origin;

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

        /* set all values to v */
        explicit VectorT(const T& v)
        {
            fill(v);
        }

        /* construct using DIM values */
        template<typename ... TT, typename = typename std::enable_if<sizeof...(TT) == DIM>::type>
        constexpr VectorT(TT... vs) : _values{{util_cast<TT, T>(vs)...}}
        {
        }

        /* default copy constructor*/
        VectorT(const VectorT& other) = default;

        /* copy & cast constructor */
        template<typename TT, unsigned DIM2, typename Derived2>
        explicit VectorT(const VectorT<TT, DIM2, Derived2>& other)
        {
            operator=(other);
        }

        /* assign operator */
        Derived& operator=(const VectorT& other)
        {
            _values = other._values;
            return static_cast<Derived &>(*this);
        }

        /* assign & cast operator */
        template<typename TT, unsigned DIM2, typename Derived2>
        Derived& operator=(const VectorT<TT, DIM2, Derived2>& other)
        {
            for(unsigned i = 0; i < std::min(DIM, DIM2); ++i)
                _values[i] = util_cast<TT, T>(other[i]);
            return static_cast<Derived &>(*this);
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

        /* set all valuest to v */
        Derived& fill(const T& v)
        {
            std::fill(_values.begin(), _values.end(), v);
            return static_cast<Derived &>(*this);
        }

        /* self-addition */
        const Derived& operator+=(const VectorT& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] += other._values[i];
            return static_cast<const Derived &>(*this);
        }

        /* add two vector */
        Derived operator+(const VectorT& other) const
        {
            return VectorT(*this) += other;
        }

        /* self-subtract */
        const Derived& operator-=(const VectorT& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] -= other._values[i];
            return static_cast<const Derived &>(*this);
        }

        /* subtract two vector */
        Derived operator-(const VectorT& other) const
        {
            return VectorT(*this) -= other;
        }

        /* self-scale by multiply */
        const Derived& operator*=(const T& scale)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] *= scale;
            return static_cast<const Derived &>(*this);
        }

        /* do scale by multiply */
        Derived operator*(const T& scale) const
        {
            return VectorT(*this) *= scale;
        }

        /* self-scale by divide */
        const Derived& operator/=(const T& scale)
        {
            assert(scale != T(0));
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] /= scale;
            return static_cast<const Derived &>(*this);
        }

        /* do scale by divide */
        Derived operator/(const T& scale) const
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

        /* access to scalar array*/
        T* data()
        {
            return _values.data();
        }

        /* access to const scalar array*/
        const T* data() const
        {
            return _values.data();
        }

        /* return the first maximal component and corresponding index*/
        std::pair<unsigned, T> max() const
        {
            auto max_iter = std::max_element(_values.cbegin(), _values.cend());
            return std::make_pair(max_iter - _values.begin(), *max_iter);
        }

        /* return the first minimal component and corresponding index*/
        std::pair<unsigned, T> min() const
        {
            auto min_iter = std::min_element(_values.cbegin(), _values.cend());
            return std::make_pair(min_iter - _values.begin(), *min_iter);
        }
        
        /* return the first maximal absolute component and corresponding index*/
        std::pair<unsigned, T> max_abs() const
        {
            auto max_iter = std::max_element(_values.cbegin(), _values.cend(), 
                            [](const T& a, const T& b) { return absolute(a) < absolute(b); });
            return std::make_pair(max_iter - _values.begin(), absolute(*max_iter));
        }

        /* return the first minimal absolute component and corresponding index*/
        std::pair<unsigned, T> min_abs() const
        {
            auto min_iter = std::min_element(_values.cbegin(), _values.cend(), 
                            [](const T& a, const T& b) { return absolute(a) < absolute(b); });
            return std::make_pair(min_iter - _values.begin(), absolute(*min_iter));
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

template<typename T, unsigned DIM, typename Derived>
Derived VectorT<T, DIM, Derived>::Origin = Derived(T(0));

template<typename T, unsigned DIM>
class VecTBase : public VectorT<T, DIM, VecTBase<T, DIM>>
{
    public:
        /* number type */
        typedef T NT;
        typedef typename VectorT<T, DIM, VecTBase<T, DIM>>::value_type value_type;

    public:
        using VectorT<T, DIM, VecTBase<T, DIM>>::VectorT;
        using VectorT<T, DIM, VecTBase<T, DIM>>::operator=;

        /* set all values to v */
        explicit VecTBase(const T& v = 0) : VectorT<T, DIM, VecTBase>(v)
        {
        }

        /* deconstructor */
        ~VecTBase()
        {
        }
};

/* specialized versions */
typedef VecTBase<float, 1>  Vec1f;
typedef VecTBase<double, 1> Vec1d;

typedef VecTBase<float, 2>  Vec2f;
typedef VecTBase<double, 2> Vec2d;

typedef VecTBase<float, 3>  Vec3f;
typedef VecTBase<double, 3> Vec3d;

template<typename T, unsigned DIM>
using VecXT = VecTBase<T, DIM>;

}   // namespace CMTL

#endif  // __common_vectorT_h__