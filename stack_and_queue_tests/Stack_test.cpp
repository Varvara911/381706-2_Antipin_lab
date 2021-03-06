#include <gtest.h>
#include "Stack.h"

TEST(Stack, can_create_stack_with_positive_len)
{
  ASSERT_NO_THROW(Stack<int> A(5));
}

TEST(Stack, can_create_stack_with_negative_len)
{
  ASSERT_ANY_THROW(Stack<int> A(-2));
}

#define SETMEMORY
#ifdef SETMEMORY

//TEST(Stack, can_set_memory)
//{
//  Stack<int> A(3);
//  int* B = new int[10];
//  A.SetMem(B, 10);
//  EXPECT_EQ(10, A.GetLen());
//  EXPECT_EQ(B, A.GetMem());
//}

//TEST(Stack, can_set_memory_in_new_stack)
//{
//  int B[5];
//  ASSERT_NO_THROW(Stack<int> A(B, 5));
//}

#endif

TEST(Stack, can_return_index)
{
  Stack<int> A(3);
  A.Put(10);
  EXPECT_EQ(1, A.GetIndex());
}

TEST(Stack, can_return_len)
{
  Stack<int> A(3);
  EXPECT_EQ(3, A.GetLen());
}

TEST(Stack, can_put_item)
{
  Stack<int> A(3);
  A.Put(10);
  EXPECT_EQ(10, A.Get());
}

TEST(Stack, can_throw_when_put_item_in_full_stack)
{
  Stack<int> A(3);
  A.Put(10);
  A.Put(5);
  A.Put(1);
  ASSERT_ANY_THROW(A.Put(3));
}

TEST(Stack, can_get_item)
{
  Stack<int> A(3);
  A.Put(10);
  A.Put(5);
  A.Put(2);
  EXPECT_EQ(2, A.Get());
}

TEST(Stack, can_throw_when_get_item_in_empty_stack)
{
  Stack<int> A(3);
  ASSERT_ANY_THROW(A.Get());
}

TEST(Stack, can_get_item_without_delete)
{
  Stack<int> A(3);
  A.Put(10);
  A.Put(5);
  A.Put(2);
  EXPECT_EQ(2, A.GetWithoutDelete());
  EXPECT_EQ(2, A.GetWithoutDelete());
}

TEST(Stack, can_throw_when_get_item_without_delete_in_empty_stack)
{
  Stack<int> A(3);
  ASSERT_ANY_THROW(A.GetWithoutDelete());
}

TEST(Stack, can_report_if_stack_is_full)
{
  Stack<int> A(3);
  A.Put(10);
  A.Put(5);
  A.Put(2);
  EXPECT_EQ(1, A.IsFull());
}

TEST(Stack, can_report_if_stack_is_not_full)
{
  Stack<int> A(3);
  A.Put(10);
  EXPECT_EQ(0, A.IsFull());
}

TEST(Stack, can_report_if_stack_is_empty)
{
  Stack<int> A(3);
  EXPECT_EQ(1, A.IsEmpty());
}

TEST(Stack, can_report_if_stack_is_not_empty)
{
  Stack<int> A(3);
  A.Put(10);
  EXPECT_EQ(0, A.IsEmpty());
}