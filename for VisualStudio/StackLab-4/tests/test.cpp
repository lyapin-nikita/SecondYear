#include "pch.h"
//#include "C:\Users\SystemX\Documents\GitHub\SecondYear\StackLab-4\StackLab\stack.h"
#include "../StackLab/stack.h"
#include "../StackLab/formula.h"



//EMPTY AND FULL TESTS
TEST(CreateStack, EmptyTest1)
{
	TStack <int> test1;
	EXPECT_TRUE(test1.isEmpty());
}

TEST(CreateStack, FullTest1)
{
	TStack <int> test1;
	EXPECT_FALSE(test1.isFull());
}

TEST(CreateStack, EmptyTest2)
{
	TStack <int> test1(3);
	test1.put(1);
	test1.put(2);
	test1.put(3);
	EXPECT_FALSE(test1.isEmpty());
}

TEST(CreateStack, FullTest2)
{
	TStack <int> test1(3);
	test1.put(1);
	test1.put(2);
	test1.put(3);
	EXPECT_TRUE(test1.isFull());
}

TEST(MetodsStack, ResizeTest1)
{
	TStack <int> test1(3);
	test1.put(1);
	test1.put(2);
	test1.put(3);
	test1.put(4);
	EXPECT_EQ(6, test1.getMemSize());
}