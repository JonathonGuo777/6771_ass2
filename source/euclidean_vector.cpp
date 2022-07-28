#include <cassert>
#include <cmath>
#include <comp6771/euclidean_vector.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
namespace comp6771 {

	// Implement solution here
	// constuctors
	euclidean_vector::euclidean_vector() noexcept {
		this->ev_dim = 1;
		this->magnitudes_ = std::make_unique<double[]>(1);
	}
	euclidean_vector::euclidean_vector(int dim) noexcept {
		this->ev_dim = dim;
//		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim)); // another approach
		for (auto i = 0; i < dim; ++i) {
//			magnitudes_[static_cast<size_t>(i)] = 0;
			magnitudes_[static_cast<size_t>(i)] = 0;
		}
	}
	euclidean_vector::euclidean_vector(int dim, double mag) noexcept {
		this->ev_dim = dim;
//		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim));
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(dim));// another approach
		for (auto i = 0; i < dim; i++) {
//			this->magnitudes_[static_cast<size_t>(i)] = mag;
			this->magnitudes_[static_cast<size_t>(i)] = mag;
		}
	}
	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) noexcept {
		auto counter1 = 0;
		auto temp1 = begin;
		while (temp1 != end) {
			++counter1;
			++temp1;
		}
		this->ev_dim = counter1;

		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->ev_dim));
		auto counter2 = 0;
		auto temp2 = begin;
		while (temp2 != end)
		{
			this->magnitudes_[static_cast<size_t>(counter2)] = *temp2;
			++counter2;
			++temp2;
		}
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> input_list) noexcept {
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(input_list.size()));
		auto counter = 0;
		for (auto temp : input_list) {
			magnitudes_[static_cast<size_t>(counter)] = temp;
			++counter;
		}
		this->ev_dim = counter;
	}
	euclidean_vector::euclidean_vector(const euclidean_vector& source) noexcept {
		this->ev_dim = source.ev_dim;
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(source.ev_dim));
		for (int i = 0; i < source.ev_dim; ++i) {
			this->magnitudes_[static_cast<size_t>(i)] = source.magnitudes_[static_cast<size_t>(i)];
		}
	}
	euclidean_vector::euclidean_vector(euclidean_vector&& source) noexcept {
		this->magnitudes_ = std::exchange(source.magnitudes_, nullptr);
		this->ev_dim = std::exchange(source.ev_dim, 0);
//    Another approach:
//		this->magnitudes_ = std::move(source.magnitudes_);
//		this->ev_dim = source.ev_dim;
//		source.magnitudes_ = nullptr;
//		source.ev_dim = 0;
	}

	// destructor
	euclidean_vector::~euclidean_vector() noexcept = default;

	// member function
	int euclidean_vector::dimensions() const noexcept {
		return this->ev_dim;
	}
	double euclidean_vector::get_magnitudes(int i) const noexcept {
		auto temp = this->magnitudes_[static_cast<size_t>(i)];
		return temp;
	}

	double euclidean_vector::at(int index) const {
		if (index < 0 || index >= this->dimensions()) {
			throw euclidean_vector_error("Index " + std::to_string(index) + " is not valid for this euclidean_vector object");
		}
		return this->magnitudes_[static_cast<size_t>(index)];
	}
	double& euclidean_vector::at(int index) {
		if (index < 0 || index >= this->dimensions()) {
			throw euclidean_vector_error("Index " + std::to_string(index) + " is not valid for this euclidean_vector object");
		}
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	// operator
	euclidean_vector& euclidean_vector::operator=(const euclidean_vector& source) noexcept { // copy assignment
		this->ev_dim = source.ev_dim;
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(source.ev_dim));
		for (int i = 0; i < source.ev_dim; ++i)
			this->magnitudes_[static_cast<size_t>(i)] = source.magnitudes_[static_cast<size_t>(i)];
		return *this;
	}
	euclidean_vector& euclidean_vector::operator=(euclidean_vector&& source) noexcept { // move assignment
		this->ev_dim = std::exchange(source.ev_dim, 0);
		this->magnitudes_ = std::exchange(source.magnitudes_, nullptr);
		return *this;
	}
	double& euclidean_vector::operator[](int index) noexcept {
		assert(index >= 0 && index < this->dimensions());
		return this->magnitudes_[static_cast<size_t>(index)];
	}
	double euclidean_vector::operator[](int index) const noexcept {
		assert(index >= 0 && index < this->dimensions());
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	euclidean_vector euclidean_vector::operator+() noexcept {
		// copy of this euclidean_vector object
		auto result = euclidean_vector(this->dimensions());
		for (int i = 0; i < this->dimensions(); ++i) {
			result.magnitudes_[static_cast<size_t>(i)] = this->magnitudes_[static_cast<size_t>(i)];
		}
		return result;
	}
	euclidean_vector euclidean_vector::operator-() noexcept {

		// Returns a copy of the current object, where each scalar value has its sign negated
		auto result = euclidean_vector(this->dimensions());
		for (int i = 0; i < this->dimensions(); ++i) {
			result.magnitudes_[static_cast<size_t>(i)] = -this->magnitudes_[static_cast<size_t>(i)];
		}
		return result;
	}

	euclidean_vector& euclidean_vector::operator+=(const euclidean_vector& source) {
		if (this->dimensions() != source.dimensions())
		{
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->dimensions()) + ") and RHS(" + std::to_string(source.dimensions()) +
			                             ") do not match");
		}
		for (int i = 0; i < source.dimensions(); ++i)
		{
			this->magnitudes_[static_cast<size_t>(i)] += source.magnitudes_[static_cast<size_t>(i)];
		}
		return *this;
	}
	euclidean_vector& euclidean_vector::operator-=(const euclidean_vector& source) {
		if (this->dimensions() != source.dimensions())
		{
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(this->dimensions()) + ") and RHS(" + std::to_string(source.dimensions()) +
			                           ") do not match");
//			throw euclidean_vector_error("Dimensions of LHS(X) and RHS(Y) do not match");
		}
		for (int i = 0; i < source.dimensions(); ++i)
		{
			this->magnitudes_[static_cast<size_t>(i)] -= source.magnitudes_[static_cast<size_t>(i)];
		}
		return *this;
	}

	euclidean_vector& euclidean_vector::operator*=(double scalar) noexcept {
		for (int i = 0; i < this->dimensions(); ++i)
		{
			this->magnitudes_[static_cast<size_t>(i)] *= scalar;
		}
		return *this;
	}

	euclidean_vector& euclidean_vector::operator/=(double scalar) {
		if (scalar == 0.0)
		{
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		for (int i = 0; i < this->dimensions(); ++i)
		{
			this->magnitudes_[static_cast<size_t>(i)] /= scalar;
		}
		return *this;
	}

	euclidean_vector::operator std::vector<double>() const noexcept {
		auto result = std::vector<double>();
		result.reserve(this->dimensions());
		for (int i = 0; i < this->dimensions(); ++i) {
			result.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return result;
	}
	euclidean_vector::operator std::list<double>() const noexcept {
		auto result = std::list<double>();
		for (int i = 0; i < this->dimensions(); ++i)
		{
			result.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return result;
	}

	// friend function
	bool operator==(euclidean_vector const& ev_a, euclidean_vector const& ev_b) noexcept {
		if (ev_a.dimensions() != ev_b.dimensions()) return false;
		for (int i = 0; i < ev_a.dimensions(); ++i)
		{
			if (ev_a.magnitudes_[static_cast<size_t>(i)] != ev_b.magnitudes_[static_cast<size_t>(i)]) return false;
		}
		return true;
	}
	bool operator!=(const euclidean_vector& ev_a, const euclidean_vector& ev_b) noexcept {
		if (ev_a.dimensions() != ev_b.dimensions()) return true;
		for (int i = 0; i < ev_a.dimensions(); ++i)
		{
			if (ev_a.magnitudes_[static_cast<size_t>(i)] != ev_b.magnitudes_[static_cast<size_t>(i)]) return true;
		}
		return false;
	}
	euclidean_vector operator+(const euclidean_vector& ev_a, const euclidean_vector& ev_b) {
		if (ev_a.dimensions() != ev_b.dimensions())
				{
					throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(ev_a.dimensions()) + ") and RHS(" + std::to_string(ev_b.dimensions()) +
														  ") do not match");
				}
		auto result = euclidean_vector(ev_a);
		result += ev_b;
		return result;
	}
	euclidean_vector operator-(const euclidean_vector& ev_a, const euclidean_vector& ev_b) {
		if (ev_a.dimensions() != ev_b.dimensions())
		{
			throw euclidean_vector_error("Dimensions of LHS(" + std::to_string(ev_a.dimensions()) + ") and RHS(" + std::to_string(ev_b.dimensions()) +
			                             ") do not match");
		}
		auto result = euclidean_vector(ev_a);
		result -= ev_b;
		return result;
	}
	euclidean_vector operator*(const euclidean_vector& ev_a, double scalar) noexcept {
		auto result = euclidean_vector(ev_a);
		return result*=scalar;
	}
	euclidean_vector operator*(double scalar, const euclidean_vector& ev_a) noexcept {
		auto result = euclidean_vector(ev_a);
		return result*=scalar;
	}
	euclidean_vector operator/(const euclidean_vector& ev_a, double scalar) {
		if (scalar == 0) {
			throw euclidean_vector_error{"Invalid vector division by 0"};
		}
		auto result = euclidean_vector(ev_a);
		return result/=scalar;
	}
	std::ostream& operator<<(std::ostream& os, const euclidean_vector& ev_a) noexcept {
		os << '[';
		for (int i = 0; i < ev_a.dimensions(); ++i) {
			os << ev_a.magnitudes_[static_cast<size_t>(i)];
			if (i != (ev_a.dimensions() - 1)) {
				os << ' ';
			}
		}
		os << ']';
		return os;
	}


	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.dimensions() == 0) return 0;
		auto norm = 0.0;
		for (int i = 0; i < v.dimensions(); ++i)
		{
			norm += v.get_magnitudes(i)*v.get_magnitudes(i);
		}
		return sqrt(norm);
	}


	auto unit(const euclidean_vector& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error{"euclidean_vector with no dimensions does not have a unit vector"};
		}
		auto norm = euclidean_norm(v);
		if (norm == 0) {
			throw euclidean_vector_error{"euclidean_vector with zero euclidean normal does not have a unit vector"};
		}
		auto result = euclidean_vector(v.dimensions());
		for (int i = 0; i < v.dimensions(); ++i)
		{
			double temp = v.get_magnitudes(i)/norm;
			result[i] = temp;
		}
		return result;
	}
	auto dot(const euclidean_vector& x, const euclidean_vector& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			throw euclidean_vector_error{"Dimensions of LHS(" + std::to_string(x.dimensions()) + ") and RHS(" + std::to_string(y.dimensions()) +
			                             ") do not match"};
		}
		auto result = 0.0;
		for (int i = 0; i < x.dimensions(); ++i) {
			result += (x[i] * y[i]);
		}
		return result;
	}


} // namespace comp6771
