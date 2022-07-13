#include <comp6771/euclidean_vector.hpp>
#include <catch2/catch.hpp>

#include <initializer_list>
#include <iostream>
/*
 * test for all Friends	functions: equal, not_equal, addition, subtraction, multiply, divide, output stream
 */
TEST_CASE("Friend Tests") {
	auto ev_a = comp6771::euclidean_vector({1, 2});
	auto ev_b = comp6771::euclidean_vector({1, 2});
	auto ev_c = comp6771::euclidean_vector({2, 4});
	auto ev_sp = comp6771::euclidean_vector({1, 2, 3, 4});

	SECTION("Equal") {
		CHECK(ev_a == ev_b);
	}
	SECTION("Not Equal") {
		CHECK(ev_a != ev_c);
	}
	SECTION("Addition") {
		auto ev_d = ev_a + ev_b;
		CHECK(ev_d == ev_c);
		// check that the function throws an exception if the dimensions of the vectors do not match
		CHECK_THROWS_WITH(ev_a + ev_sp, "Dimensions of LHS(2) and RHS(4) do not match");
	}
	SECTION("Subtraction") {
		auto ev_d = ev_c - ev_b;
		CHECK(ev_d == ev_a);
		// check that the function throws an exception if the dimensions of the vectors do not match
		CHECK_THROWS_WITH(ev_a - ev_sp, "Dimensions of LHS(2) and RHS(4) do not match");
	}
	SECTION("Multiplication") {

		auto ev_d = ev_a * 2;
		auto ev_e = 2 * ev_a;
		CHECK(ev_d == ev_c);
		CHECK(ev_e == ev_c);
	}
	SECTION("Division") {
		auto ev_d = ev_c / 2;
		CHECK(ev_d == ev_a);
		// check that the function throws an exception if division by 0
		CHECK_THROWS_WITH(ev_c / 0, "Invalid vector division by 0");
	}
	SECTION("Output Stream") {
		std::ostringstream os;
		os << ev_sp;
		std::ostringstream correct;
		correct << "[1 2 3 4]";
		CHECK(os.str() == correct.str());
	}
}