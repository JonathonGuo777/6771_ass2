#include <comp6771/euclidean_vector.hpp>
#include <catch2/catch.hpp>


/*
 * double at (int index) const; double& at (int index)
 * should return the value of the magnitude in the dimension given as the function parameter
 */

 TEST_CASE("at()") {
 	comp6771::euclidean_vector vec1(2, 5.45);
 	CHECK(vec1.at(0) == 5.45);
 	CHECK(vec1.at(1) == 5.45);
	// check reference
	vec1.at(0) = 0.0;
	CHECK(vec1.at(0) == 0.0);
	// check that the function throws an exception if the index is out of bounds
	CHECK_THROWS_WITH(vec1.at(2), "Index 2 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(vec1.at(-1), "Index -1 is not valid for this euclidean_vector object");
 }

/*
 * int dimensions()
 * should return the number of dimensions in the vector
 */
 TEST_CASE("dimensions()") {
 	comp6771::euclidean_vector vec1(2, 5.45);
 	CHECK(vec1.dimensions() == 2);
 }

