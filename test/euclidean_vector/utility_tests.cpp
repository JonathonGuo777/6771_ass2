#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>

/*
 *  Euclidean norm
 * should return the Euclidean norm of the vector as a double
 */
TEST_CASE("Euclidean norm") {

//	auto ev_a = comp6771::euclidean_vector{1, 2, 3};
	auto norm_list = {1.0, 2.0, 3.0};
	auto e_vector = comp6771::euclidean_vector(norm_list);
	double ev_norm = sqrt(pow(1, 2) + pow(2, 2) + pow(3, 2));
//	comp6771::euclidean_norm(e_vector) == ev_norm
	CHECK(comp6771::euclidean_norm(e_vector) == ev_norm);

}

/*
 *  Unit
 * should return a Euclidean vector that is the unit vector of v
 */
TEST_CASE("Unit") {
	auto norm_list = {1.0, 2.0, 3.0};
	auto e_vector = comp6771::euclidean_vector(norm_list);
	auto unit_vector = comp6771::euclidean_vector(norm_list);
	unit_vector /= sqrt(14);
	CHECK(comp6771::unit(e_vector) == unit_vector);
   //
	CHECK_THROWS_WITH(comp6771::unit(comp6771::euclidean_vector()),
							"euclidean_vector with zero euclidean normal does not have a unit "
							"vector");
}

/*
 * Dot product
 * should return the sum of two vectors
 */
TEST_CASE("Dot product") {
	auto dot_vector = comp6771::euclidean_vector({1, 2});
	auto dot_vector2 = comp6771::euclidean_vector({3, 4});
	auto dot_vector3 = comp6771::euclidean_vector({5});

	CHECK(comp6771::dot(dot_vector, dot_vector2) == 11);
	SECTION("Checking Exceptions") {
		CHECK_NOTHROW(comp6771::dot(dot_vector, dot_vector2));
		CHECK_THROWS_WITH(comp6771::dot(dot_vector, dot_vector3),
								"Dimensions of LHS(2) and RHS(1) do not match");
	}
}