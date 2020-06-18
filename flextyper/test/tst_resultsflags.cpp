////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2019, Wasserman lab
///
/// FILE        tst_resultsflags.cpp
///
/// DESCRIPTION This file contains tests for the result processor
///
////////////////////////////////////////////////////////////////////////

#include <gtest/gtest.h>
#include "utils.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace ft;

namespace ft {
class TestResultsFlags : public ::testing::Test {
protected:
//    virtual void SetUp() {
//    }

//    virtual void TeadDown() {
//    }

//    bool areFileIdentical(const string& f1, const string& f2) {
//        ifstream fin1(f1);
//        string str1;
//        string line;
//        if (fin1.is_open()) {
//            while (getline(fin1, line)) {
//                str1 += line;
//            }
//            fin1.close();
//        }

//        ifstream fin2(f2);
//        string str2;
//        if (fin2.is_open()) {
//            while (getline(fin2, line)) {
//                str2 += line;
//            }
//            fin2.close();
//        }

//        return str1 == str2;
//    }

public:
    //ResultProcessor _results;
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

//======================================================================
TEST_F(TestResultsFlags, getIndexCounts)
{
    //TEST_DESCRIPTION("This test ");

    //ReaIDsMap  inputs {{{1, QueryType::REF}, {1000, 5444, 421, 74, 1021}}};

    //EXPECT_EQ(output, expectedOutput);
    //EXPECT_NO_FATAL_FAILURE();
    //EXPECT_NO_THROW();
}

}
