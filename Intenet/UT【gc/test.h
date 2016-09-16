#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <typeinfo>

#define TEST_DEBUG
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE  -1
#define LOVERFLOW   -2
typedef int Status;

 
//#define RESET   "\033[0m"
//#define BLACK   "\033[30m"      /* Black */
//#define RED     "\033[31m"      /* Red */
//#define GREEN   "\033[32m"      /* Green */
//#define YELLOW  "\033[33m"      /* Yellow */
//#define MAGENTA "\033[35m"      /* Magenta */
//#define CYAN    "\033[36m"      /* Cyan */
//#define WHITE   "\033[37m"      /* White */
//#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
//#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
//#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
//#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
//#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
//#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
//#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
//#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#define TESTCASE_NAME(testcase_name) \
    testcase_name##_TEST


#define TEST(testcase_name) \
class TESTCASE_NAME(testcase_name) : public TestCase \
{ \
public: \
    TESTCASE_NAME(testcase_name)(const char* case_name) : TestCase(case_name){}; \
    virtual void Run(); \
private: \
    static TestCase* const testcase_; \
}; \
\
TestCase* const TESTCASE_NAME(testcase_name) \
    ::testcase_ = UnitTest::GetInstance()->RegisterTestCase( \
        new TESTCASE_NAME(testcase_name)(#testcase_name)); \
void TESTCASE_NAME(testcase_name)::Run()


#define RUN_ALL_TESTS() \
    UnitTest::GetInstance()->Run();

//单元测试的主体
class TestCase
{
public:
	TestCase(const char *case_name) : testcase_name(case_name) {};
	virtual void Run() = 0;
	bool test_result;
	const char *testcase_name;
};

class UnitTest
{
public:
	static UnitTest* GetInstance();
	TestCase* RegisterTestCase(TestCase *testcase);
	bool Run();

	TestCase *current_test_case;
	bool test_result;
	int passed_num;
	int failed_num;
	std::vector<TestCase*> testcases_;
};

UnitTest* UnitTest::GetInstance()
{
	static UnitTest instance;
	return &instance;
}

TestCase* UnitTest::RegisterTestCase(TestCase *testcase)
{
	testcases_.push_back(testcase);
	return testcase;
}

bool UnitTest::Run()
{
	test_result = true;

	std::cout /*<< YELLOW*/ << "[ Start Run ]" << /*RESET <<*/ "Have " << testcases_.size() << " Unit Testing" << std::endl;
	std::cout << std::endl;

	for (std::vector<TestCase*>::iterator it = testcases_.begin(); it != testcases_.end(); ++it)
	{
		TestCase *test_case = *it;
		current_test_case = test_case;
		current_test_case->test_result = true;

		std::cout << /*GREEN <<*/ "[ Run ]" << /*RESET <<*/ test_case->testcase_name << std::endl;
		test_case->Run();

		if (test_case->test_result)
			std::cout << /*GREEN <<*/ "[ Pass ]" << /*RESET <<*/ test_case->testcase_name << std::endl;
		else
			std::cout << /*RED <<*/ "[ Failed ]" << /*RESET <<*/ test_case->testcase_name << std::endl;

		if (test_case->test_result)
		{
			passed_num++;
		}
		else
		{
			failed_num++;
			test_result = false;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << /*YELLOW <<*/ "[ RUN OVER ]" << /*RESET <<*/ "Total " << testcases_.size() << " Unit Testing" << std::endl;
	std::cout << /*GREEN <<*/ "[   PASS   ]" << /*RESET <<*/ passed_num << " Units" << std::endl;
	std::cout << /*RED <<*/ "[   FAIL   ]" << /*RESET <<*/ failed_num << " Units" << std::endl;
	return test_result;
}

enum OperatorType
{
	OPERATOR_TYPE_EQ,
	OPERATOR_TYPE_NE,
	OPERATOR_TYPE_GT,
	OPERATOR_TYPE_LT,
	OPERATOR_TYPE_GE,
	OPERATOR_TYPE_LE
};

template <class ElemType>
bool CheckNumericalData(ElemType left_value,
	ElemType right_value,
	const char *str_left_value,
	const char *str_right_value,
	const char *file_name,
	const unsigned long line_num,
	OperatorType operator_type)
{
	bool condition;
	char str_operator[5];

	switch (operator_type)
	{
	case OPERATOR_TYPE_EQ:
		if (typeid(ElemType) == typeid(double))
			condition = !(fabs(left_value - right_value) < 1e-8);
		else if (typeid(ElemType) == typeid(float))
			condition = !(fabs(left_value - right_value) < 1e-6);
		else
			condition = !(left_value == right_value);
		strcpy(str_operator, " == ");
		break;

	case OPERATOR_TYPE_NE:
		if (typeid(ElemType) == typeid(double))
			condition = !(fabs(left_value - right_value) > 1e-8);
		else if (typeid(ElemType) == typeid(float))
			condition = !(fabs(left_value - right_value) > 1e-6);
		else
			condition = !(left_value != right_value);
		strcpy(str_operator, " != ");
		break;

	case OPERATOR_TYPE_GT:
		condition = !(left_value > right_value);
		strcpy(str_operator, " > ");
		break;

	case OPERATOR_TYPE_LT:
		condition = !(left_value < right_value);
		strcpy(str_operator, " < ");
		break;

	case OPERATOR_TYPE_LE:
		condition = !(left_value <= right_value);
		strcpy(str_operator, " <= ");
		break;

	case OPERATOR_TYPE_GE:
		condition = !(left_value >= right_value);
		strcpy(str_operator, " >= ");
		break;
	}


	if (condition)
	{
		UnitTest::GetInstance()->current_test_case->test_result = 0;
		std::cout << file_name << "(" << line_num << "): ";
		std::cout << "Error: Expect: " << str_left_value << str_operator << str_right_value;
		std::cout << ", Fact: " << left_value << " vs " << right_value << std::endl;
	}
	return (!condition);
}

bool CheckStrData(const char *left_value,
	const char *right_value,
	const char *str_left_value,
	const char *str_right_value,
	const char *file_name,
	const unsigned long line_num,
	OperatorType operator_type)
{
	bool condition;
	char str_operator[5];

	if (operator_type == OPERATOR_TYPE_EQ)
	{
		condition = !((strcmp(left_value, right_value) == 0));
		strcpy(str_operator, " == ");
	}
	else if (operator_type == OPERATOR_TYPE_NE)
	{
		condition = !((strcmp(left_value, right_value) != 0));
		strcpy(str_operator, " != ");
	}

	if (condition)
	{
		UnitTest::GetInstance()->current_test_case->test_result = 0;
		std::cout << file_name << "(" << line_num << "): ";
		std::cout << "Error: Expect: " << str_left_value << str_operator << str_right_value;
		std::cout << ", Fact: " << left_value << " vs " << right_value << std::endl;
	}
	return (!condition);
}

#define CHECK_NUMERICAL_DATA(left_value, right_value, operator_type) \
    CheckNumericalData(left_value, right_value, #left_value, #right_value, __FILE__, __LINE__, operator_type)
#define CHECK_STR_DATA(left_value, right_value, operator_type) \
    CheckStrData(left_value, right_value, #left_value, #right_value, __FILE__, __LINE__, operator_type)

#define EXPECT_EQ(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_EQ)
#define EXPECT_NE(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_NE)
#define EXPECT_GT(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_GT)
#define EXPECT_LT(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_LT)
#define EXPECT_GE(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_GE)
#define EXPECT_LE(left_value, right_value) CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_LE)

#define ASSERT_EQ(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_EQ)) return;
#define ASSERT_NE(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_NE)) return;
#define ASSERT_GT(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_GT)) return;
#define ASSERT_LT(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_LT)) return;
#define ASSERT_GE(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_GE)) return;
#define ASSERT_LE(left_value, right_value) if (!CHECK_NUMERICAL_DATA(left_value, right_value, OPERATOR_TYPE_LE)) return;

#define EXPECT_TRUE(condition) CHECK_NUMERICAL_DATA(static_cast<bool>(condition), true, OPERATOR_TYPE_EQ)
#define EXPECT_FALSE(condition) CHECK_NUMERICAL_DATA(static_cast<bool>(condition), false, OPERATOR_TYPE_EQ)
#define ASSERT_TRUE(condition) if (!CHECK_NUMERICAL_DATA(static_cast<bool>(condition), true, OPERATOR_TYPE_EQ)) return;
#define ASSERT_FALSE(condition) if (!CHECK_NUMERICAL_DATA(static_cast<bool>(condition), false, OPERATOR_TYPE_EQ) return;
#define EXPECT_STREQ(left_value, right_value) CHECK_STR_DATA(left_value, right_value, OPERATOR_TYPE_EQ)
#define EXPECT_STRNE(left_value, right_value) CHECK_STR_DATA(left_value, right_value, OPERATOR_TYPE_NE)
#define ASSERT_STREQ(left_value, right_value) if (!CHECK_STR_DATA(left_value, right_value, OPERATOR_TYPE_EQ)) return;
#define ASSERT_STRNE(left_value, right_value) if (!CHECK_STR_DATA(left_value, right_value, OPERATOR_TYPE_NE)) return;

#endif
