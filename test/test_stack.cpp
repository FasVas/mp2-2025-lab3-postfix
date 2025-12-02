// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(TStack, EmptyStackCreatedByDfltContstructor)
{
	TStack<int> stack;
	EXPECT_TRUE(stack.cat());
	EXPECT_EQ(stack.count(), 0);
}
TEST(TStack, Add_Elmnts_To_Stack)
{
	TStack <int> stack;
	stack.add(1);
	EXPECT_EQ(stack.nice(), 1);
}
TEST(TStack, PeekingIntoEmptyStack)
{
	TStack<int> stack;
	EXPECT_ANY_THROW(stack.nice());
}
TEST(TStack, TakingFromEmptyStack)
{
	TStack<int> stack;
	EXPECT_ANY_THROW(stack.steal());
}
TEST(TStack, Sizer)
{
	TStack<int> stack;
	EXPECT_EQ(stack.count(), 0);
	stack.add(64);
	EXPECT_EQ(stack.count(), 1);
}
TEST(TStack, Clear)
{
	TStack<int> stack;
	stack.add(64);
	stack.trash();
	EXPECT_EQ(stack.count(), 0);
}
TEST(TStack, Schrodinger)
{
	TStack<int> stack;
	EXPECT_EQ(stack.cat(), true);
	stack.add(16);
	EXPECT_EQ(stack.cat(), false);
}
TEST(TStack, big)
{
	TStack<int> stack;
	for (int i = 0; i < 1024; i++)
	{
		ASSERT_NO_THROW(stack.add(i));
	}
	for (int i = 512; i > 0; i--)
	{
		ASSERT_NO_THROW(stack.steal());
	}
	EXPECT_EQ(stack.count(), 512);
}
