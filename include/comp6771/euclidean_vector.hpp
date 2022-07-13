#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include <sstream>
#include <utility>


namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector() noexcept;
		explicit euclidean_vector(int) noexcept;
		euclidean_vector(int, double) noexcept;
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator) noexcept;
		euclidean_vector(std::initializer_list<double>) noexcept;
		euclidean_vector(euclidean_vector const&) noexcept;
		euclidean_vector(euclidean_vector&&) noexcept;

		// Destructor
//		~euclidean_vector() = default;
		~euclidean_vector() noexcept;

		// Operations
		euclidean_vector& operator=(euclidean_vector const&) noexcept; // copy assignment
		euclidean_vector& operator=(euclidean_vector&&) noexcept; // move assignment
		double &operator[](int index) noexcept; // modifier subscript operator
		double operator[](int index) const noexcept; // getter subscript operator
		euclidean_vector operator+() noexcept; // unary +
		euclidean_vector operator-() noexcept; // unary -
		// += Given: X = a.dimensions(), Y = b.dimensions() When: X != Y Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
		euclidean_vector& operator+=(euclidean_vector const&);
		// -= Given: X = a.dimensions(), Y = b.dimensions() When: X != Y Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
		euclidean_vector& operator-=(euclidean_vector const&);
		euclidean_vector& operator*=(double) noexcept; // *=

		// /= When: b == 0 Throw: "Invalid vector division by 0"
		euclidean_vector& operator/=(double);
//		auto operator/=(double) -> euclidean_vector&;

		explicit operator std::vector<double>() const noexcept; // cast to std::vector<double>
		explicit operator std::list<double>() const noexcept; // cast to std::list<double>

		// Friends
		friend bool operator==(euclidean_vector const&, euclidean_vector const&) noexcept; // ==
		friend bool operator!=(euclidean_vector const&, euclidean_vector const&) noexcept; // !=
		// Given: X = b.dimensions(), Y = c.dimensions() When: X != Y Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
		friend euclidean_vector operator+(euclidean_vector const&, euclidean_vector const&); // +
		// Given: X = b.dimensions(), Y = c.dimensions() When: X != Y Throw: "Dimensions of LHS(X) and RHS(Y) do not match"
		friend euclidean_vector operator-(euclidean_vector const&, euclidean_vector const&); // -
		friend euclidean_vector operator*(euclidean_vector const&, double) noexcept; // *
		friend euclidean_vector operator*(double, euclidean_vector const&) noexcept; // *
		// When: c == 0 Throw: "Invalid vector division by 0"
		friend euclidean_vector operator/(euclidean_vector const&, double); // /
		friend std::ostream& operator<<(std::ostream&, euclidean_vector const&) noexcept; // << output stream operator

		double at(int) const;
		// When: For Input X: when X is < 0 or X is >= number of dimensions Throw: "Index X is not valid for this euclidean_vector object"
		double& at(int);
		int dimensions() const noexcept; // getter dimensions

		[[nodiscard]] double get_magnitudes(int ) const noexcept; // getter dimensions


	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
	int ev_dim;
	std::unique_ptr<double[]> magnitudes_;

	};
	// Utility Functions
	auto euclidean_norm(euclidean_vector const& evector) -> double;
	auto unit(euclidean_vector const& evector) -> euclidean_vector;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
