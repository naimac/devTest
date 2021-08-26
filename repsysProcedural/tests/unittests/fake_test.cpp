#include <cppunit/config/SourcePrefix.h>
#include <cppunit/extensions/HelperMacros.h>

#include <iostream>

class fake_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(fake_test);

    CPPUNIT_TEST(repsysSetFault_test);

	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// List of tests
	void repsysSetFault_test();
};


CPPUNIT_TEST_SUITE_REGISTRATION(fake_test);

void fake_test::setUp()
{
    std::cout << "STARTING UNITTEST" << std::endl;
}

void fake_test::tearDown()
{
    std::cout << "ENDING UNITTEST" << std::endl;
}

void fake_test::repsysSetFault_test() {

    std::cout << "EXEC UNITTEST" << std::endl;

    bool retCode = false;

    CPPUNIT_ASSERT_EQUAL_MESSAGE("fake test", true, true);
}
