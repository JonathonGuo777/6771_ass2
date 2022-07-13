#include <comp6771/euclidean_vector.hpp>
#include <catch2/catch.hpp>
//#include <fmt/format.h>
//#include <fmt/ostream.h>
//#include <initializer_list>
//#include <iostream>

/*
 * test copy assignment operator
 *	check the dimension and magnitude of ev_a before and after assignment
 */
TEST_CASE("copy assignment operator") {
	auto list_a = {1.1, 2.2, 3.3};
	auto list_b = {3.0, 4.0};
	auto ev_a = comp6771::euclidean_vector(list_a);
	auto ev_b = comp6771::euclidean_vector(list_b);
	THEN("copy assign with two different dimensions vectors") {
		// ev_b
		CHECK(ev_b.dimensions() == 2);
		CHECK(ev_b[0] == 3.0);
		CHECK(ev_b[1] == 4.0);
		// ev_a before copy
		CHECK(ev_a.dimensions() == 3);
		CHECK(ev_a[0] == 1.1);
		CHECK(ev_a[1] == 2.2);
		CHECK(ev_a[2] == 3.3);
		// ev_b after copy
		ev_a = ev_b;
		CHECK(ev_a.dimensions() == 2);
		CHECK(ev_a[0] == 3.0);
		CHECK(ev_a[1] == 4.0);
	}
}
/*
 * move assignment operator
 *	check the dimension and magnitude of ev_a before and after assignment
 */
TEST_CASE("move assignment operator") {
	auto list_a = {1.1, 2.2, 3.3};
	auto list_b = {3.0, 4.0};
	auto ev_a = comp6771::euclidean_vector(list_a);
	auto ev_b = comp6771::euclidean_vector(list_b);
	THEN("copy assign with two different dimensions vectors") {
		// ev_b
		CHECK(ev_b.dimensions() == 2);
		CHECK(ev_b[0] == 3.0);
		CHECK(ev_b[1] == 4.0);
		// ev_a before copy
		CHECK(ev_a.dimensions() == 3);
		CHECK(ev_a[0] == 1.1);
		CHECK(ev_a[1] == 2.2);
		CHECK(ev_a[2] == 3.3);
		// ev_b after copy
		ev_a = std::move(ev_b);
		CHECK(ev_a.dimensions() == 2);
		CHECK(ev_a[0] == 3.0);
		CHECK(ev_a[1] == 4.0);

		// ev_b after move should be empty
		CHECK(ev_b.dimensions() == 0);
	}
}

/*
 * subscript operator
 * check euclidean_vector before and after subscript operator
 */
TEST_CASE("subscript operator") {
	comp6771::euclidean_vector  dimension_magnitude(2, 5.5);
	SECTION("check euclidean_vector before and after subscript operator")
	{
		// before subscript operator
		CHECK(dimension_magnitude.dimensions() == 2);
		CHECK(dimension_magnitude[0] == 5.5);
		CHECK(dimension_magnitude[1] == 5.5);

		//after subscript operator
		dimension_magnitude[0] = 1.1;
		dimension_magnitude[1] = 2.2;
		CHECK(dimension_magnitude.dimensions() == 2);
		CHECK(dimension_magnitude[0] == 1.1);
		CHECK(dimension_magnitude[1] == 2.2);
	}
}

/*
 * Unary Plus operator
 * Returns a copy of the current object.
 */
TEST_CASE("Unary Plus operator") {
	comp6771::euclidean_vector  ev(2, 5.5);
//	auto const ev = comp6771::euclidean_vector{1.1, 2.2};
	auto ev_copy = +ev;
	SECTION("check euclidean_vector before and after subscript operator")
	{
		//after subscript operator
		CHECK(ev_copy.dimensions() == 2);
		CHECK(ev_copy[0] == 5.5);
		CHECK(ev_copy[1] == 5.5);
	}
}

/*
 * Negerate operator
 * Returns a copy of the current object, where each scalar value has its sign negated.
 */
TEST_CASE("Negate operator") {
	auto const actual = comp6771::euclidean_vector{-6, 1};
	auto const expected = comp6771::euclidean_vector{6, -1};
	CHECK(expected[0] == -actual[0]);
	CHECK(expected[1] == -actual[1]);
}

/*
 * Compound Addition operator
 * For adding vectors of the same dimension
 */
TEST_CASE("Compound Addition operator") {
	auto ev_a = comp6771::euclidean_vector{1.1, 2.2};
	auto ev_b = comp6771::euclidean_vector{0.9, 0.8};
	auto ev_c = comp6771::euclidean_vector{0.2};
	ev_a += ev_b;
	//	after addition
	CHECK(ev_a[0] == 2.0);
	CHECK(ev_a[1] == 3.0);
	// check addition with different dimension vector, should throw exception
	CHECK_THROWS_WITH(ev_a += ev_c, "Dimensions of LHS(2) and RHS(1) do not match");
}

/*
 * Compound Subtraction operator
 * For subtracting vectors of the same dimension
 */
TEST_CASE("Compound Subtraction operator") {
	auto ev_a = comp6771::euclidean_vector{1.1, 2.2};
	auto ev_b = comp6771::euclidean_vector{0.1, 0.2};
	auto ev_c = comp6771::euclidean_vector{0.2};
	ev_a -= ev_b;
//		after subtraction
	CHECK(ev_a[0] == 1.0);
	CHECK(ev_a[1] == 2.0);
	// check subtraction with different dimension vector, should throw exception
	CHECK_THROWS_WITH(ev_a -= ev_c, "Dimensions of LHS(2) and RHS(1) do not match");
}

/*
 * Compound Multiplication operator
 * For multiplying vectors of the same dimension
 */
TEST_CASE("Compound Multiplication operator") {
	auto ev_a = comp6771::euclidean_vector{1.1, 2.2};
	ev_a *= 2;
	//	after addition
	CHECK(ev_a[0] == 2.2);
	CHECK(ev_a[1] == 4.4 );
}
/*
 * Compound Division operator
 * For scalar division
 */
TEST_CASE("Compound Division operator") {
	auto dividing = comp6771::euclidean_vector(3, 10.0);
	dividing /= 2.0;
//	CHECK_THROWS_WITH(dividing /= 0, "Invalid vector division by 0");
	auto ev_a = comp6771::euclidean_vector{1.1, 2.2};
	auto ev_b = comp6771::euclidean_vector{0.4, 0.5};
	ev_a /= 2;
	//	after addition
	CHECK(ev_a[0] == 0.55);
	CHECK(ev_a[1] == 1.1 );
	// check division by 0, should throw exception
	CHECK_THROWS_WITH(ev_a /= 0.0, "Invalid vector division by 0");
}

/*
 * Vector Type Conversion operator
 * Operators for type casting to a std::vector
 */
TEST_CASE("Vector Type Conversion operator") {
	std::vector<double> test_vector = {1.1, 2.2, 3.3};
	comp6771::euclidean_vector vector_object(test_vector.begin(), test_vector.end());
	auto check = std::vector<double>{vector_object};
	THEN("Conversion is successful") { REQUIRE(test_vector == check); }
}

/*
 * List Type Conversion operator
 * Operators for type casting to a std::list
 */
TEST_CASE("List Type Conversion operator") {
	std::vector<double> test_vector = {1.1, 2.2, 3.3};
	comp6771::euclidean_vector vector_object(test_vector.begin(), test_vector.end());
	auto check = std::list<double>{vector_object};
	std::list<double> test_list = {1.1, 2.2, 3.3};
	THEN("Conversion is successful") { CHECK(test_list == check); }
}