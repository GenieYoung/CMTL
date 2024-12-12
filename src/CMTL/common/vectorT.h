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
 * @tparam Derived used for CRTP
 */
template<typename T, unsigned DIM, typename Derived>
class VectorT
{
    protected:
        typedef std::array<T, DIM> container;
        container _values;

    public:
        typedef T value_type;

        /* origin vector */
        static Derived Origin;

        /** 
         * @brief return dimension of this vector 
         */
        static const unsigned dimension()
        {
            return DIM;
        }

        /** 
         * @brief alias of dimension 
         */
        static const unsigned size()
        {
            return dimension();
        }

        constexpr VectorT()
        {
        }

        /** 
         * @brief set all values to v 
         */
        explicit VectorT(const T& v)
        {
            fill(v);
        }

        /** 
         * @brief construct using DIM values 
         */
        template<typename ... TT, typename = typename std::enable_if<sizeof...(TT) == DIM>::type>
        constexpr VectorT(TT... vs) : _values{{util_cast<TT, T>(vs)...}}
        {
        }

        VectorT(const VectorT& other) = default;

        /** 
         * @brief copy & cast constructor 
         * @tparam TT another number type
         * @tparam DIM2 another dimension
         * @tparam Derived used for CRTP
         */
        template<typename TT, unsigned DIM2, typename Derived2>
        explicit VectorT(const VectorT<TT, DIM2, Derived2>& other)
        {
            operator=(other);
        }

        Derived& operator=(const VectorT& other)
        {
            _values = other._values;
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief assign & cast operator 
         * @tparam TT another number type
         * @tparam DIM2 another dimension
         * @tparam Derived used for CRTP
         * @note this will default construct any values that cannot be filled
         *       (e.g. vec3->vec4) or leave out the last values when size of
         *       vector is shrinked(e.g. {1,2,3}->{1,2})
         */
        template<typename TT, unsigned DIM2, typename Derived2>
        Derived& operator=(const VectorT<TT, DIM2, Derived2>& other)
        {
            for(unsigned i = 0; i < std::min(DIM, DIM2); ++i)
                _values[i] = util_cast<TT, T>(other[i]);
            return static_cast<Derived &>(*this);
        }

        virtual ~VectorT()
        {
        }

        /** 
         * @brief get the writable ith value 
         */
        T& operator[](unsigned i)
        {
            assert(i < DIM);
            return _values[i];
        }

        /** 
         * @brief get the const ith value 
         */
        const T& operator[](unsigned i) const
        {
            assert(i < DIM);
            return _values[i];
        }

        /** 
         * @brief set all values to v 
         */
        Derived& fill(const T& v)
        {
            std::fill(_values.begin(), _values.end(), v);
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief self-addition 
         */
        template<typename TT, typename Derived2>
        Derived& operator+=(const VectorT<TT, DIM, Derived2>& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] += util_cast<TT, T>(other[i]);
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief add two vector 
         */
        template<typename TT, typename Derived2>
        Derived operator+(const VectorT<TT, DIM, Derived2>& other) const
        {
            return VectorT(*this) += other;
        }

        /** 
         * @brief self-subtract 
         */
        template<typename TT, typename Derived2>
        Derived& operator-=(const VectorT<TT, DIM, Derived2>& other)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] -= util_cast<TT, T>(other[i]);
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief subtract two vector 
         */
        template<typename TT, typename Derived2>
        Derived operator-(const VectorT<TT, DIM, Derived2>& other) const
        {
            return VectorT(*this) -= other;
        }

        /** 
         * @brief self-scale by multiply
         */
        Derived& operator*=(const T& scale)
        {
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] *= scale;
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief do scale by multiply 
         */
        Derived operator*(const T& scale) const
        {
            return VectorT(*this) *= scale;
        }

        /** 
         * @brief self-scale by divide
         */
        Derived& operator/=(const T& scale)
        {
            assert(scale != T(0));
            for(unsigned i = 0; i < DIM; ++i)
                _values[i] /= scale;
            return static_cast<Derived &>(*this);
        }

        /** 
         * @brief do scale by divide 
         */
        Derived operator/(const T& scale) const
        {
            return VectorT(*this) /= scale;
        }

        /** 
         * @brief scalar product 
         */
        template<typename TT, typename Derived2>
        T operator*(const VectorT<TT, DIM, Derived2>& other) const
        {
            T result(0);
            for(unsigned i = 0; i < DIM; ++i)
                result += (_values[i] * util_cast<TT, T>(other[i]));
            return result;
        }

        /** 
         * @brief scalar product 
         */
        template<typename TT, typename Derived2>
        T dot(const VectorT<TT, DIM, Derived2>& other) const
        {
            return *this * other;
        }

        bool operator==(const VectorT& other) const
        {
            for(unsigned i = 0; i < DIM; ++i)
                if(_values[i] != other[i])
                    return false;
            return true;
        }

        bool operator!=(const VectorT& other) const
        {
            return !(*this == other);
        }

        bool operator<(const VectorT& other) const
        {
            for(unsigned i = 0; i < DIM; ++i)
                if(_values[i] != other._values[i])
                    return _values[i] < other._values[i];
            return false;
        }

        /** 
         * @brief access to scalar array 
         */
        T* data()
        {
            return _values.data();
        }

        /** 
         * @brief access to const scalar array 
         */
        const T* data() const
        {
            return _values.data();
        }

        /** 
         * @brief return the first maximal component and corresponding index
         * @return a pair which first value represents the position and second value represent the maximum
         */
        std::pair<unsigned, T> max() const
        {
            auto max_iter = std::max_element(_values.cbegin(), _values.cend());
            return std::make_pair(max_iter - _values.begin(), *max_iter);
        }

        /** 
         * @brief return the first minimal component and corresponding index
         * @return a pair which first value represents the position and second value represent the minimum
         */
        std::pair<unsigned, T> min() const
        {
            auto min_iter = std::min_element(_values.cbegin(), _values.cend());
            return std::make_pair(min_iter - _values.begin(), *min_iter);
        }
        
        /** 
         * @brief return the first maximal absolute component and corresponding index
         * @return a pair which first value represents the position and second value represent the absolute maximum
         */
        std::pair<unsigned, T> max_abs() const
        {
            auto max_iter = std::max_element(_values.cbegin(), _values.cend(), 
                            [](const T& a, const T& b) { return absolute(a) < absolute(b); });
            return std::make_pair(max_iter - _values.begin(), absolute(*max_iter));
        }

        /** 
         * @brief return the first minimal absolute component and corresponding index 
         * @return a pair which first value represents the position and second value represent the absolute minimum
         */
        std::pair<unsigned, T> min_abs() const
        {
            auto min_iter = std::min_element(_values.cbegin(), _values.cend(), 
                            [](const T& a, const T& b) { return absolute(a) < absolute(b); });
            return std::make_pair(min_iter - _values.begin(), absolute(*min_iter));
        }

        /** 
         * @brief calculate square of L2-norm
         */
        T norm_square() const
        {
            return (*this) * (*this);
        }

        /** 
         * @brief calculate square of L2-norm 
         */
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

/**
 * @brief simple fixed size value type container easy for use
 * @tparam T number type
 * @tparam DIM dimension
 */
template<typename T, unsigned DIM>
class VecTBase : public VectorT<T, DIM, VecTBase<T, DIM>>
{
    public:
        typedef T NT;
        typedef typename VectorT<T, DIM, VecTBase<T, DIM>>::value_type value_type;

    public:
        using VectorT<T, DIM, VecTBase<T, DIM>>::VectorT;
        using VectorT<T, DIM, VecTBase<T, DIM>>::operator=;

        /** 
         * @brief set all values to v 
         */
        explicit VecTBase(const T& v = 0) : VectorT<T, DIM, VecTBase>(v)
        {
        }

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

/**
 * @brief simple fixed size value type container easy for use
 * @tparam T number type
 * @tparam DIM dimension
 */
template<typename T, unsigned DIM>
using VecXT = VecTBase<T, DIM>;

}   // namespace CMTL

#endif  // __common_vectorT_h__