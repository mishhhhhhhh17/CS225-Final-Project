add_test( [==[Data parsing from CSV]==] /root/cs225/CS225-Final-Project/build/test [==[Data parsing from CSV]==]  )
set_tests_properties( [==[Data parsing from CSV]==] PROPERTIES WORKING_DIRECTORY /root/cs225/CS225-Final-Project/build)
add_test( [==[Graph members]==] /root/cs225/CS225-Final-Project/build/test [==[Graph members]==]  )
set_tests_properties( [==[Graph members]==] PROPERTIES WORKING_DIRECTORY /root/cs225/CS225-Final-Project/build)
set( test_TESTS [==[Data parsing from CSV]==] [==[Graph members]==])
