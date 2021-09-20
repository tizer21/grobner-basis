#pragma once

#include "monomial.h"

namespace NLibPoly {

template<typename CoefficientType>
class TTerm {
public:
	using TVariableDegree = TMonomial::TVariableDegree;
	using TVariableIndex = TMonomial::TVariableIndex;

	using iterator = TMonomial::iterator;
	using const_iterator = TMonomial::const_iterator;
	using reverse_iterator = TMonomial::reverse_iterator;
	using const_reverse_iterator = TMonomial::const_reverse_iterator;

	TTerm() {
		Coefficient_ = CoefficientType(0);
		Monomial_ = TMonomial();
	}

	explicit TTerm(CoefficientType coefficient)
    : Coefficient_(std::move(coefficient))
	{
		Monomial_ = TMonomial();
	}

	explicit TTerm(const TMonomial& monomial) {
		Coefficient_ = CoefficientType(1);
		Monomial_ = monomial;
	}

	TTerm(CoefficientType coefficient, TMonomial monomial)
    : Coefficient_(std::move(coefficient))
    , Monomial_(std::move(monomial))
	{
		Reduce();
	}

	template<typename OtherCoefficientType>
	explicit TTerm(const TTerm<OtherCoefficientType>& other) {
		Coefficient_ = static_cast<CoefficientType>(other.Coefficient_);
		Monomial_ = other.Monomial_;
		Reduce();
	}

	TVariableDegree GetDegree() const {
		return Monomial_.GetDegree();
	}

	TVariableDegree GetDegreeOf(TMonomial::TVariableIndex i) const {
		return Monomial_.GetDegreeOf(i);
	}

	bool IsDivisibleBy(const TTerm& other) const {
		return Monomial_.IsDivisibleBy(other.Monomial_);
	}

	TVariableIndex GetEndIndex() {
		return Monomial_.GetEndIndex();
	}

	const CoefficientType& GetCoefficient() const {
		return Coefficient_;
	}

	const TMonomial& GetMonomial() const {
		return Monomial_;
	}

	bool IsZero() const {
		return Coefficient_ == CoefficientType(0);
	}

	TTerm operator-() const {
		return TTerm(-Coefficient_, Monomial_);
	}

	TTerm& operator+=(const TTerm& other) {
		assert(Monomial_ == other.Monomial_);
		Coefficient_ += other.Coefficient_;
		Reduce();

		return *this;
	}

	TTerm& operator-=(const TTerm& other) {
		*this += -other;

		return *this;
	}

	TTerm& operator*=(const TTerm& other) {
		Coefficient_ *= other.Coefficient_;
		Monomial_ *= other.Monomial_;
		Reduce();

		return *this;
	}

	TTerm& operator/=(const TTerm& other) {
		assert(!IsZero());
		Coefficient_ /= other.Coefficient_;
		Monomial_ /= other.Monomial_;

		return *this;
	}

	iterator begin() {
		return Monomial_.begin();
	}

	iterator end() {
		return Monomial_.end();
	}

	const_iterator begin() const {
		return Monomial_.begin();
	}

	const_iterator end() const {
		return Monomial_.end();
	}

	reverse_iterator rbegin() {
		return Monomial_.rbegin();
	}

	reverse_iterator rend() {
		return Monomial_.rend();
	}

	const_reverse_iterator rbegin() const {
		return Monomial_.rbegin();
	}

	const_reverse_iterator rend() const {
		return Monomial_.rend();
	}

	friend TTerm operator+(const TTerm& lhs, const TTerm& rhs) {
		auto res = lhs;
		res += rhs;
		return res;
	}

	friend TTerm operator-(const TTerm& lhs, const TTerm& rhs) {
		auto res = lhs;
		res -= rhs;
		return res;
	}

	friend TTerm operator*(const TTerm& lhs, const TTerm& rhs) {
		auto res = lhs;
		res *= rhs;
		return res;
	}

	friend TTerm operator/(const TTerm& lhs, const TTerm& rhs) {
		auto res = lhs;
		res /= rhs;
		return res;
	}

	friend bool operator==(const TTerm& lhs, const TTerm& rhs) {
		return (lhs.Coefficient_==rhs.Coefficient_) && (lhs.Monomial_==rhs.Monomial_);
	}

	friend bool operator!=(const TTerm& lhs, const TTerm& rhs) {
		return !(lhs == rhs);
	}

private:
	void Reduce() {
		if (IsZero()) {
			Monomial_ = TMonomial();
		}
	}

private:
	CoefficientType Coefficient_;
	TMonomial Monomial_;
};

}

#include <boost/functional/hash.hpp>

namespace NLibPoly {

template<typename CoefficientType>
size_t hash_value(const TTerm<CoefficientType>& term)
{
	boost::hash<CoefficientType> coefficientHasher;
	boost::hash<TMonomial> monomialHasher;

	size_t seed = 0;
	boost::hash_combine(seed, coefficientHasher(term.GetCoefficient()));
	boost::hash_combine(seed, monomialHasher(term.GetMonomial()));

	return seed;
}

}

