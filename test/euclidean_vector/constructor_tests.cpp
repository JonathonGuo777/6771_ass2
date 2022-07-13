#include <comp6771/euclidean_vector.hpp>
#include <catch2/catch.hpp>

/*
 * Constructors, Operations, Member Functions, Friends, Utility functions, are divided into different .cpp files for testing.
 * Each function is provided with a corresponding test case for the function that needs to throw an exception,
 * while testing whether the exception thrown is correct.
 */



/*
 * This is a test for the default constructor.
 * Dimension should be 1, magnitudes[0] should be 0
 */
TEST_CASE("Creating Default Constructor") {
	 comp6771::euclidean_vector vec;
	 THEN("dimension should be 1, magnitudes[0] is 0") {
		 CHECK(vec.dimensions() == 1);
		 CHECK(vec[0] == 0);
	 }
 }

 /*
 * This is a test for the Single-argument Constructor
 * The number of dimensions (as an int) but no magnitudes,
 * sets the magnitude in each dimension as 0.0
  */
 TEST_CASE("Single-argument Constructor") {
	 comp6771::euclidean_vector vec1(5);
	 THEN("-> dimension = 5 and magnitudes are all 0") {
		 CHECK(vec1.dimensions() == 5);
		 for (int i = 0; i < 5; ++i) {
			 CHECK(vec1[i] == 0);
		 }
	 }
 }

 /*
 * Test the constructor (int, double)
 * check the dimension and magnitude of the vector
  */
 TEST_CASE("constructor (int, double)") {
	 auto a = comp6771::euclidean_vector(2, 4.0);
	 auto x = int{3};
	 auto y = double{3.24};
	 auto b = comp6771::euclidean_vector(x, y);

	 THEN("check with expected output") {
		 CHECK(a.dimensions() == 2);
		 for (int i = 0; i < 2; ++i) {
			 CHECK(a[i] == 4.0);
		 }
		 CHECK(b.dimensions() == 3);
		 for (int i = 0; i < 3; ++i) {
			 CHECK(b[i] == 3.24);
		 }
	 }
 }

 /*
* Test range constructor, with given a pair of vector iterator.
 * Check the dimension and magnitude of the vector.
  */

 TEST_CASE("range constructor") {

	 std::vector<double> v{1, 2, 3.1, 4, 5.2, 0};
	 auto b = comp6771::euclidean_vector(v.begin(),v.end());

	 THEN(
	    "-> dimension = std::vector.size(), magnitudes should be same as the std::vector value") {
		 CHECK(b.dimensions() == static_cast<int>(v.size()));
		 for (int i = 0; i < b.dimensions(); ++i) {
			 CHECK(v[i] == b[i]);
		 }
	 }
 }

 /*
 * Test copy constructor
 * compare old and new Euclidean vector
  */
 TEST_CASE("copy constructor") {
	 comp6771::euclidean_vector a(3, 4.0);
	 comp6771::euclidean_vector b(a);
	 THEN("-> dimension = 3, magnitudes should be same as the old vector") {
		 CHECK(b.dimensions() == 3);
		 for (int i = 0; i < 3; ++i) {
			 CHECK(b[i] == 4.0);
		 }
	 }
 }

 /*
 * Test move constructor
 * check dimension and move
  */
 TEST_CASE("move constructor") {
	 std::vector<double> test_vector = {3.1, 4.2, 5.3, 1.5};
	 comp6771::euclidean_vector vector_object(test_vector.begin(), test_vector.end());
	 comp6771::euclidean_vector copy_object = vector_object;
	 comp6771::euclidean_vector other_object = std::move(vector_object);

	 THEN("EV is successfully moved") {
		 CHECK(other_object == copy_object);
		 CHECK(vector_object.dimensions() == 0);
	 }
 }