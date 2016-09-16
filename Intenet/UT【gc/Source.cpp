#include "test.h"

int Add(int a, int b)
{
	return a + b;
}

int Minus(int a, int b)
{
	return a - b;
}


TEST(Test_PassDemo)
{
	EXPECT_EQ(3, Add(1, 2));
	EXPECT_EQ(0, Minus(1, 1));
}

TEST(Test_FailDemo)
{
	int condition = 0;
	char a[] = "acc";
	char b[] = "abc";
	EXPECT_STREQ(a, b);
	EXPECT_TRUE(condition);
	EXPECT_EQ(2, Minus(2, 2));
	ASSERT_EQ(4, Add(1, 2));
	EXPECT_EQ(2, Add(1, 2));
}

int main()
{
	return RUN_ALL_TESTS();
}
