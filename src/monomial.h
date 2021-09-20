#pragma once

#include <cassert>
#include <vector>

namespace NLibPoly
{
class TMonomial
{
public:
    using TVariableDegree = size_t;
    using TVariableIndex = size_t;

    using DegreeContainer = std::vector<TVariableDegree>;

    using iterator = DegreeContainer::iterator;
    using const_iterator = DegreeContainer::const_iterator;
    using reverse_iterator = DegreeContainer::reverse_iterator;
    using const_reverse_iterator = DegreeContainer::const_reverse_iterator;

    TMonomial() = default;

    TMonomial(std::initializer_list<TVariableDegree> initList) : Variables_(initList) { DeleteLastZeroPowers(); }

    TVariableDegree GetDegree() const
    {
        TVariableDegree res = 0;
        for (const auto variable : Variables_)
        {
            res += variable;
        }
        return res;
    }

    TVariableDegree GetDegreeOf(TVariableIndex i) const { return (i < GetEndIndex() ? Variables_[i] : 0); }

    bool IsDivisibleBy(const TMonomial & other) const
    {
        for (TVariableIndex i = 0; i != other.GetEndIndex(); ++i)
        {
            if (GetDegreeOf(i) < other.GetDegreeOf(i))
            {
                return false;
            }
        }

        return true;
    }

    TVariableIndex GetEndIndex() const { return Variables_.size(); }

    TMonomial & operator*=(const TMonomial & other)
    {
        if (GetEndIndex() < other.GetEndIndex())
        {
            Variables_.resize(other.GetEndIndex());
        }

        for (TVariableIndex i = 0; i != other.GetEndIndex(); ++i)
        {
            Variables_[i] += other.Variables_[i];
        }

        return *this;
    }

    TMonomial & operator/=(const TMonomial & other)
    {
        assert(IsDivisibleBy(other));

        for (TVariableIndex i = 0; i != other.GetEndIndex(); ++i)
        {
            Variables_[i] -= other.Variables_[i];
        }
        DeleteLastZeroPowers();

        return *this;
    }

    iterator begin() { return Variables_.begin(); }

    iterator end() { return Variables_.end(); }

    const_iterator begin() const { return Variables_.begin(); }

    const_iterator end() const { return Variables_.end(); }

    reverse_iterator rbegin() { return Variables_.rbegin(); }

    reverse_iterator rend() { return Variables_.rend(); }

    const_reverse_iterator rbegin() const { return Variables_.rbegin(); }

    const_reverse_iterator rend() const { return Variables_.rend(); }

    friend TMonomial operator*(const TMonomial & lhs, const TMonomial & rhs)
    {
        auto res = lhs;
        res *= rhs;
        return res;
    }

    friend TMonomial operator/(const TMonomial & lhs, const TMonomial & rhs)
    {
        auto res = lhs;
        res /= rhs;
        return res;
    }

    friend bool operator==(const TMonomial & lhs, const TMonomial & rhs) { return lhs.Variables_ == rhs.Variables_; }

    friend bool operator!=(const TMonomial & lhs, const TMonomial & rhs) { return !(lhs == rhs); }

    static TMonomial Gcd(const TMonomial & lhs, const TMonomial & rhs)
    {
        TMonomial res;

        for (TVariableIndex i = 0; i != std::min(lhs.GetEndIndex(), rhs.GetEndIndex()); ++i)
        {
            res.Variables_.push_back(std::min(lhs.GetDegreeOf(i), rhs.GetDegreeOf(i)));
        }

        return res;
    }

    static TMonomial Lcm(const TMonomial & lhs, const TMonomial & rhs) { return lhs * rhs / Gcd(lhs, rhs); }

private:
    void DeleteLastZeroPowers()
    {
        while (!Variables_.empty() && Variables_.back() == 0)
        {
            Variables_.pop_back();
        }
    }

private:
    DegreeContainer Variables_;
};

}

#include <boost/functional/hash.hpp>

namespace NLibPoly
{
size_t hash_value(const TMonomial & monomial)
{
    size_t seed = 0;

    size_t i = 0;
    for (const auto degree : monomial)
    {
        if (degree)
        {
            boost::hash_combine(seed, degree);
            boost::hash_combine(seed, i);
        }
        ++i;
    }

    return seed;
}

}
