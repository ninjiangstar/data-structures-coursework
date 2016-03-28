#include "llistint.h"
#include "gtest/gtest.h"

class LListIntTest : public testing::Test {
protected:
	LListIntTest() {
		// nothing happens
	}

	virtual ~LListIntTest() { 
		// nothing happens
	}

	virtual void SetUp() {
		list.insert(0, 0);
		list.insert(1, 1);
		list.insert(3, 3);
	}

	virtual void TearDown() { 
		// nothing happens
	}

	LListInt list;
};

// COPY CONSTRUCTOR WITH EMPTY LIST
TEST_F(LListIntTest, CopyEmptyNominal){
	list.clear(); // expect list to be empty

	LListInt newList(list);

	EXPECT_EQ(newList.size(), 0);
}

// COPY CONSTRUCTOR WITH NONEMPTY LIST
TEST_F(LListIntTest, CopyNominal){
	LListInt newList(list);

	EXPECT_EQ(newList.size(), list.size());

	for(int i=0; i<newList.size(); i++)
		EXPECT_EQ(newList[i], list[i]);
}

// ASSIGNMENT OPERATOR (COPY) WITH EMPTY LIST ONTO UNINITIALIZED LIST
TEST_F(LListIntTest, AssignmentEmptyNominal){
	LListInt newList;
	list.clear();

	newList = list;

	EXPECT_EQ(newList.size(), 0);

}

// ASSIGNMENT OPERATOR (COPY) WITH NONEMPTY LIST ONTO UNINITIALIZED LIST
TEST_F(LListIntTest, AssignmentNominal){
	LListInt newList;

	newList = list;

	EXPECT_EQ(newList.size(), list.size());

	for(int i=0; i<newList.size(); i++)
		EXPECT_EQ(newList[i], list[i]);
}

// ASSIGNMENT OPERATOR (COPY) WITH NONEMPTY LIST ONTO NONEMPTY LIST
TEST_F(LListIntTest, AssignmentOffNominal){
	LListInt newList;
	newList.insert(0, 5);
	newList.insert(1, 9);

	newList = list;

	EXPECT_EQ(newList.size(), list.size());

	for(int i=0; i<newList.size(); i++)
		EXPECT_EQ(newList[i], list[i]);
}

// CONCATENATE TWO NONEMPTY LISTS
TEST_F(LListIntTest, ConcatenationENominal){
	LListInt newList;
	LListInt finalList;
	newList.insert(0, 3);
	newList.insert(1, 4);
	newList.insert(2, 5);
	finalList = list + newList;

	EXPECT_EQ(finalList.size(), list.size() + newList.size());

	for(int i=0; i<list.size(); i++)
		EXPECT_EQ(finalList[i], list[i]);

	for(int i=0; i<newList.size(); i++)
		EXPECT_EQ(finalList[i+list.size()], newList[i]);
}

// CONCATENATE TWO EMPTY LISTS
TEST_F(LListIntTest, ConcatenationEmptyNominal){
	LListInt newList;
	LListInt finalList;
	list.clear();
	finalList = list + newList;

	EXPECT_EQ(finalList.size(), 0);
}


// ACCESS OPERATOR ON NONEMPTY LIST
TEST_F(LListIntTest, AccessNominal){
	for(int i=0; i<list.size(); i++)
		EXPECT_EQ(list[i], list.get(i));
}

// ACCESS OPERATOR ON EMPTY LIST
TEST_F(LListIntTest, AccessOffNominal){
	LListInt newList;

	try {
		newList[0];
		FAIL();
	}
	catch(const std::exception& e) {
		ASSERT_STREQ("bad location", e.what());
	}
}