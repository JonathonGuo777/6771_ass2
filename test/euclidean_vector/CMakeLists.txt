cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector
)

cxx_test(
        TARGET constructor_tests
        FILENAME "constructor_tests.cpp"
        LINK euclidean_vector 
)
cxx_test(
        TARGET operator_overloading_tests
        FILENAME "operator_overloading_tests.cpp"
        LINK euclidean_vector 
)
cxx_test(
        TARGET member_functions_tests
        FILENAME "member_functions_tests.cpp"
        LINK euclidean_vector 
)
cxx_test(
        TARGET friends_tests
        FILENAME "friends_tests.cpp"
        LINK euclidean_vector 
)
cxx_test(
        TARGET utility_tests
        FILENAME "utility_tests.cpp"
        LINK euclidean_vector 
)