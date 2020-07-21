#include <gtest/gtest.h>
#include "writerbridge.cpp"

using namespace std;
using namespace ft;

namespace ft {
class TestWriterBridge : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {
    }

public:
    WriterBridge _writerBridge;
};

#define TEST_DESCRIPTION(desc) RecordPro perty("description", desc)

//======================================================================
TEST_F(TestWriterBridge, saveQueryOutput)
{

    EXPECT_NO_FATAL_FAILURE();
    EXPECT_NO_THROW();
}
}
