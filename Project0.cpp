#define BOOST_TEST_MODULE Project0UnitTest
#include <boost\test\unit_test.hpp>
#include "sorted_vector.hpp"
#include <iostream>

using namespace std;

BOOST_AUTO_TEST_CASE(intro) {
	cout << "\nUnit test demo.\n";
	cout << "Last compiled: " << __TIMESTAMP__ << "\n\n";
}

// test the sorting capabilities of the vector
BOOST_AUTO_TEST_CASE(sorted_vector_test)
{
	//create a vector to use as a control test if the elements are sorted correctly
	vector<int> test_vector{ 4, 3, 7, 1, 10 , 1, 3, 8, 9, 7, 5, 4};

	//sort the vector
	sort(test_vector.begin(), test_vector.end());

	//create a sorted vector 
	sorted_vector<int> test_sorted_vector;
	test_sorted_vector.insert(4);
	test_sorted_vector.insert(3);
	test_sorted_vector.insert(7);
	test_sorted_vector.insert(1);
	test_sorted_vector.insert(10);
	test_sorted_vector.insert(1);
	test_sorted_vector.insert(3);
	test_sorted_vector.insert(8);
	test_sorted_vector.insert(9);
	test_sorted_vector.insert(7);
	test_sorted_vector.insert(5);
	test_sorted_vector.insert(4);

	//create a for loop and boost check each value to see if the sorted vector sorted correctly
	for (unsigned i = 0; i < test_vector.size(); i++)
	{
		BOOST_CHECK_EQUAL(test_vector[i], test_sorted_vector[i]);
	}
}

BOOST_AUTO_TEST_CASE(sorted_vector_operator_equal)
{
	// create two sorted_vectors to test
	sorted_vector<int> test_vector_1;
	for (unsigned i = 1; i <= 10; ++i)
	{
		test_vector_1.insert(i);
	}

	sorted_vector<int> test_vector_2;
	for (unsigned i = 10; i >= 1; --i)
	{
		test_vector_2.insert(i);
	}

	// check the == operator, by checking both the size and values
	for (unsigned i = 0; i < 10; ++i)
	{
		BOOST_CHECK_EQUAL(test_vector_1[i], test_vector_2[i]);
	}
	BOOST_CHECK(test_vector_1.size() == test_vector_2.size());
}

BOOST_AUTO_TEST_CASE(sorted_vector_operator_not_equal)
{
	// create two sorted_vector's to test
	// the first sorted_vector will have a size of 10
	sorted_vector<int> test_vector_1;
	for (unsigned i = 1; i <= 10; ++i)
	{
		test_vector_1.insert(i);
	}

	// the second sorted_vector will have a size of 11
	sorted_vector<int> test_vector_2;
	for (unsigned i = 1; i <= 11; ++i)
	{
		test_vector_2.insert(i);
	}

	// check the != operator by comparing the size
	BOOST_CHECK_MESSAGE(test_vector_1.size() != test_vector_2.size(), "Error when comparing the sizes in the != operator");

	// add a number to test_vector_1 that does not correspond to the extra number in test_vector_2 (11)
	// then compare the two vectors to confirm the values in each do not equal
	test_vector_1.insert(5);

	BOOST_CHECK_MESSAGE(test_vector_1 != test_vector_2, "Error when comparing values in the != operator");
}

BOOST_AUTO_TEST_CASE(sorted_vector_erase)
{
	sorted_vector<int> test_sorted_vector;
	for (unsigned i = 1; i <= 10; ++i)
	{
		test_sorted_vector.insert(i);
	}

	test_sorted_vector.erase(test_sorted_vector.begin() + 3);

	//check the size to make sure an index was deleted
	BOOST_CHECK_EQUAL(test_sorted_vector.size(), 9);

	std::vector<int> test_vector;
	for (unsigned i = 1; i <= 9; ++i)
	{
		if (i <= 3)
			test_vector.push_back(i);
		else
			test_vector.push_back(i + 1);
	}

	for (unsigned i = 0; i < test_vector.size(); ++i)
	{
		//check to see if correct value is erased
		BOOST_CHECK_MESSAGE(test_vector[i] == test_sorted_vector[i], "Incorrect value deleted at test_sorted_vector[" << test_sorted_vector[i] << "]");
	}
}

BOOST_AUTO_TEST_CASE(sorted_vector_at)
{
	sorted_vector<int> test_sorted_vector;
	for (unsigned i = 0; i < 10; i++)
	{
		test_sorted_vector.insert(i);
	}

	//check to see if it will throw when out of range
	BOOST_CHECK_THROW(test_sorted_vector.at(11), std::out_of_range);

	//check to see if the at() method is returning the proper values
	BOOST_CHECK_MESSAGE(test_sorted_vector.at(8) == 8, "at() is not returning proper values");
}

BOOST_AUTO_TEST_CASE(sorted_vector_find)
{
	sorted_vector<int> test_sorted_vector;
	for (unsigned i = 0; i < 3; i++)
	{
		test_sorted_vector.insert(i);
	}

	//iterator value for the first element, and the memory address of that element
	auto iterator = test_sorted_vector.find(0);
	auto memoryAddress = *iterator;

	//check to see if the first element in the sorted vector matches the iterator, and if the memory addresses are the same
	BOOST_CHECK(iterator == test_sorted_vector.begin());
	BOOST_CHECK(memoryAddress == test_sorted_vector[0]);

	//check to see if the memory address of the middle element is correct
	iterator = test_sorted_vector.find(1);
	memoryAddress = *iterator;

	//check to see if the middle element in the sorted vector matches the iterator, and if the memory addresses are the same
	BOOST_CHECK(iterator == test_sorted_vector.begin() + 1);
	BOOST_CHECK(memoryAddress == test_sorted_vector[1]);

	//check to see if the memory address of the last element is correct
	iterator = test_sorted_vector.find(2);
	memoryAddress = *iterator;

	//check to see if the end element in the sorted vector matches the iterator, and if the memory addresses are the same
	BOOST_CHECK(iterator == test_sorted_vector.begin() + 2);
	BOOST_CHECK(memoryAddress == test_sorted_vector[2]);
}