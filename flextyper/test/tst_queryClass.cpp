#include <gtest/gtest.h>
#include <climits>
#include "queryClass.h"

using namespace std;

namespace ft {
class TestQueryClass : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TeadDown() {
    }

public:

};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestQueryClass, setProperties)
{
    TEST_DESCRIPTION("set Properties");
}
}
