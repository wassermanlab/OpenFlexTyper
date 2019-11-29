////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2018, Wasserman lab
///
/// FILE        tst_performances.cpp
///
/// DESCRIPTION This file will test performances of FlexTyper. It's used to
///             assess search speed against regular searching tools like
///             grep.
///
/// Initial version @
///
////////////////////////////////////////////////////////////////////////

#include "stats.h"
#include "fmindex.h"
#include "ftsearch.h"
#include <gtest/gtest.h>
#include "utils.h"
#include <iostream>
#include "writerbridge.h"
#include "kmergenerator.h"

#include <chrono>

using namespace std;
using namespace sdsl;
using namespace chrono;

namespace ft {
class TestPerformances : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TeadDown() {
    }

    set<string> generateKmersFromQueries(size_t numberOfKmers, const string& queryString, uint kmerSize, uint stride) {
        ft::KmerGenerator ftSearchObj;
        set<string> result, tmp;
        int i = 0;
        tmp = ftSearchObj.genSlidingSearchStrings(queryString, kmerSize, stride);

        // cout << "tmp size : " << tmp.size() << endl;

        for (auto e : tmp) {
            result.insert(e);
            i++;
            if (i == numberOfKmers)
                break;
        }
        return result;
    }
};

#define TEST_DESCRIPTION(desc) RecordProperty("description", desc)

// 1, 10, 100, 1000, 2000, 3000, 4000, 5000

//======================================================================
TEST_F(TestPerformances, TestPerformancesFor1Kmer) {

    string queryString = "TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCT"
                         "TACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGA"
                         "AAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT";
    set<string> testStrings = generateKmersFromQueries(1, queryString, 31, 1);
    cout << "testStrings size : " << testStrings.size() << endl;

    algo::FmIndex fmIndex;
    string indexFile = "/var/tmp/TestData/ERR194147/ERR194147.fm9";
    fmIndex.loadIndexFromFile(indexFile);
    steady_clock::time_point start = steady_clock::now();
    for (auto e : testStrings) {
        cout << e << endl;
        fmIndex.search(e, {});
    }

    steady_clock::time_point end = steady_clock::now();
    std::cout << "Searching took "
              << duration_cast<microseconds>(end - start).count()
              << "us.\n";
}

//======================================================================
TEST_F(TestPerformances, TestPerformancesFor10Kmer) {
    string queryString = "TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCT"
                         "TACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGA"
                         "AAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT";
    set<string> testStrings = generateKmersFromQueries(10, queryString, 31, 1);
    cout << "testStrings size : " << testStrings.size() << endl;

    algo::FmIndex fmIndex;
    string indexFile = "/var/tmp/TestData/ERR194147/ERR194147.fm9";
    fmIndex.loadIndexFromFile(indexFile);
    steady_clock::time_point start = steady_clock::now();
    for (auto e : testStrings) {
        cout << e << endl;
        fmIndex.search(e, {});
    }

    steady_clock::time_point end = steady_clock::now();
    std::cout << "Searching took "
              << duration_cast<microseconds>(end - start).count()
              << "us.\n";
}

//======================================================================
TEST_F(TestPerformances, TestPerformancesFor100Kmer) {
    string queryString = "TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCT"
                         "TACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGA"
                         "AAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT";
    set<string> testStrings = generateKmersFromQueries(100, queryString, 31, 1);
    cout << "testStrings size : " << testStrings.size() << endl;

    algo::FmIndex fmIndex;
    string indexFile = "/var/tmp/TestData/ERR194147/ERR194147.fm9";
    fmIndex.loadIndexFromFile(indexFile);
    steady_clock::time_point start = steady_clock::now();
    for (auto e : testStrings) {
        cout << e << endl;
        fmIndex.search(e, {});
    }

    steady_clock::time_point end = steady_clock::now();
    std::cout << "Searching took "
              << duration_cast<microseconds>(end - start).count()
              << "us.\n";
}

//======================================================================
TEST_F(TestPerformances, TestPerformancesFor1KKmer) {
    set<string> queryString = { "TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCT"
                                "TACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGA"
                                "AAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT",
                                "ATTAATAAAATATGACATGATTAAATCTATTTAAATTGAATATTTTCTTTAAAATTTCGGTGAAAACAAAATGAAAGAAAATTGGAGCACTCCAAATGAGTAATA"
                                "AAGTTGATCAAGGAATAAAACTGACCTAATGGAGTTTTCGTTCTCGACCCTAGTTATTCAATATTGGCATTTAAAAACCTTTTATCAGAACATCTCTAGAATCAG"
                                "TAACATCGAAACGCACTGAGCTGCCTTAGGGCCTCATAAAGAGGTAAGCTTGAGAAGCTGTTTTCCAATAGATATAACCAAACATAACTGT",
                                "CTCCTTACATTCCAGCCGTAGGGGTCTTTTTGCAGTTCCCCCAAAAACATGCTATTCCCTCTGCAAGGAATGCCCCTTCCTCACCTTTCCCACGGGCTGGCTCCA"
                                "GTTCATTGACCTCAAGCTTCCTCTCCTGCTGTAGCCTCAGAAGGGAGCTATGGCATGAATTAGGGCAACTTTGGACAAAATGGTGCTGCAGATAGGCTGTCCCTG"
                                "CTCTCACAAGCTCCAGACCAGTTCTTGTCAGGGGAATTTGGGCAGAAATCTTAGCAGGAACTAAGCACCTCTGTGGCACTCTCAAATCCAA",
                                "TCAAACAAAATAGCTGATTCTCCAATGACATAAAATGTCCATGAGAAAACAGCAGCATCACACAGAAAACAAGTTACAGAAGCTGCAGTTGTTCATTCATTCACT"
                                "CAACAGACATATTTGAGGGCCTCCTGTGTACCATGTGTTGTGCTAGATGCTGACTATACAACATTAACCAAGGCCTAGTTTTGTCCTCAGGAACTTATAGCCTTA"
                                "TGAGGAAACATGCACAACAAAAATAAAAATAGCACAGGGTAAATGTTAACATGGAAACTTTGTGGGGTGAAGGGGGAATAGAGAAGAAACG"
                              };
    set<string> testStrings;
    for (auto q : queryString) {
        set<string> tmpStrings = generateKmersFromQueries(271, q, 31, 1);
        for (auto e : tmpStrings) {
            testStrings.insert(e);
        }
    }

    int i = 0;
    set<string> tmpTestString;
    for (auto e : testStrings) {
        if (i == 1000)
            break;
        tmpTestString.insert(e);
        i++;
    }

    testStrings = tmpTestString;

    cout << "testStrings size : " << testStrings.size() << endl;

    algo::FmIndex fmIndex;
    string indexFile = "/var/tmp/TestData/ERR194147/ERR194147.fm9";
    fmIndex.loadIndexFromFile(indexFile);
    steady_clock::time_point start = steady_clock::now();

    for (auto e : testStrings) {
        // cout << e << endl;
        fmIndex.search(e, {});        
    }

    steady_clock::time_point end = steady_clock::now();
    std::cout << "Searching took "
              << duration_cast<microseconds>(end - start).count()
              << "us.\n";
}

//======================================================================
TEST_F(TestPerformances, TestPerformancesFor5KKmer) {
    set<string> queryString = { "TTTCTCCAAATACAGATCCAATGTCTTCACTTGTCTATTAAATGCCTCCCATTCCAAATATGATTACCTCTCCCCAGCTCCAATTAAGTCCCTTCTTTCCCCTCT"
                                "TACTACCGCTTTCTTCCATGTGCCTCTTACAACACCATGGAGACATTTTTCATTTGTGCTTCTTTCATGCAGTTAGCCAAGCTTGTCAAGTTTTTTTTTTTTTGA"
                                "AAAAAAAAAAAAATACATACATATATATATATATAATTTTTTTTCCCCTCACTATGTTGCCCAGATTGGTCTTGAACTACCGGGCTCAAGT",
                                "ATTAATAAAATATGACATGATTAAATCTATTTAAATTGAATATTTTCTTTAAAATTTCGGTGAAAACAAAATGAAAGAAAATTGGAGCACTCCAAATGAGTAATA"
                                "AAGTTGATCAAGGAATAAAACTGACCTAATGGAGTTTTCGTTCTCGACCCTAGTTATTCAATATTGGCATTTAAAAACCTTTTATCAGAACATCTCTAGAATCAG"
                                "TAACATCGAAACGCACTGAGCTGCCTTAGGGCCTCATAAAGAGGTAAGCTTGAGAAGCTGTTTTCCAATAGATATAACCAAACATAACTGT",
                                "CTCCTTACATTCCAGCCGTAGGGGTCTTTTTGCAGTTCCCCCAAAAACATGCTATTCCCTCTGCAAGGAATGCCCCTTCCTCACCTTTCCCACGGGCTGGCTCCA"
                                "GTTCATTGACCTCAAGCTTCCTCTCCTGCTGTAGCCTCAGAAGGGAGCTATGGCATGAATTAGGGCAACTTTGGACAAAATGGTGCTGCAGATAGGCTGTCCCTG"
                                "CTCTCACAAGCTCCAGACCAGTTCTTGTCAGGGGAATTTGGGCAGAAATCTTAGCAGGAACTAAGCACCTCTGTGGCACTCTCAAATCCAA",
                                "TCAAACAAAATAGCTGATTCTCCAATGACATAAAATGTCCATGAGAAAACAGCAGCATCACACAGAAAACAAGTTACAGAAGCTGCAGTTGTTCATTCATTCACT"
                                "CAACAGACATATTTGAGGGCCTCCTGTGTACCATGTGTTGTGCTAGATGCTGACTATACAACATTAACCAAGGCCTAGTTTTGTCCTCAGGAACTTATAGCCTTA"
                                "TGAGGAAACATGCACAACAAAAATAAAAATAGCACAGGGTAAATGTTAACATGGAAACTTTGTGGGGTGAAGGGGGAATAGAGAAGAAACG",
                                "AATAAAGTTTGGAAAAGTACAGAAGAAACAAATATCACAATCCTGGACACTTCCTCTAAAGAAACTCACTCCAAATCCCACAACTAGTAAATGGCATATTTAAAA"
                                "ACTATTAGGTCTTTTAATTCCAAAGCCCATTTTCTATTATGTCACACTGTACTAAAATCATAGAATATAATCTGGTCTAAGATGACATCAAATGTAGCATCACAA"
                                "ATTATGCTACAGAAGAGCTATATGCCAAATAAATATTTAAAAAGATATATTCTCAGTCATGGAAATTACATTTTCTTTGGTTTTAGTAAAT",
                                "GCCGAGATCGTGCCACTGCACTCCAGCCTGGGCGGCAGAGGAAGACTCCGTCTCAAATAAATAAATAAATAAATAAAATTTCATGTGTTAAATGGGATGTTTTGA"
                                "CATATGTATACATGCGTCATCATTAAATCAAGCCAATTATCCCATTCAGCATCTCATCTACGAATTGTGTGTGTGTGTGTGGGGAGAAGACTTCAGATCTAGTGT"
                                "GCTGGCAATTTACCAGTAAGACACTGTTCCTATAAACCACAGTCACAGGCTGTAAAGAGCCTTGAACTTCTTCCTCCTGTCTCACTTTTTT",
                                "TGGGAGAGGTTTCCAGGCCACGGTGGGGCCTGGGCCTGCGCCTGCACCTGCGCCCCTGAGCCACACTGCCTCTCAGGGTTCTTGGTGGGACCATAGCTCAGATGG"
                                "CAGCAACTGAAAGGACAGAACTGCTGCCCAGATGAGATCCCATGACGTGTGTTCTAAATCGGCCTTTAGTAATGGTGCAGGTGGCCTGGTGCCCTCAGCCTCACC"
                                "GCACCACCCTTTTGCCTTTTGGTGATGAGGCTAAGTACATGCTTGCCATATGTTGAGGTGGGGGTGGGTCAGTGCCTCTCCAGGGGTGAGT",
                                "TGGGAGAGGTTTCCAGGCCACGGTGGGGCCTGGGCCTGCGCCTGCACCTGCGCCCCTGAGCCACACTGCCTCTCAGGGTTCTTGGTGGGACCATAGCTCAGATGG"
                                "CAGCAACTGAAAGGACAGAACTGCTGCCCAGATGAGATCCCATGACGTGTGTTCTAAATCGGCCTTTAGTAATGGTGCAGGTGGCCTGGTGCCCTCAGCCTCACC"
                                "GCACCACCCTTTTGCCTTTTGGTGATGAGGCTAAGTACATGCTTGCCATATGTTGAGGTGGGGGTGGGTCAGTGCCTCTCCAGGGGTGAGT",
                                "AGAGATCCTTGTTTTCCATCACTGCAGAGAATGCTATACCAAGGGCGAGAGGCCTCTAGGTCAGAGATCATAAAGAAGAAAAGAATGGCTGGATTTTAGGGGTGG"
                                "TGCCCAACGATTAGTTTGTGTTGTAATGTGGCATGAAGCGTCTTCAGAATGCATTTGCGATGTTTACTGGGATTTGGAAAAGGATCGTAACAAGGTCTAGCAAGG"
                                "CAGTCTAGCCCAAGGAGGGTCCAGTTGAGTTCCGAACTAGTTTCTGATATCTATCCCTTCCAAAACTGCATGTTTAATTAAAGAACAGCCC",
                                "CCGACTAATTTTGTATTTTTAGTAGAGGTGGGGTATGTCCATGTTGGTCAGGCTGGTTTCAGACTCCCAACCTCAGGAGATCCACCCTCCTCTGCTCCCCAAAGT"
                                "ACATGGTATTTGTTTGTAGTGAAGCAAATATCTACAACAGCAAGTCGAGAGAATTAGGGGGTATATCTACAAGTCAGATGAGACTGATGATTCAGAGACACATCT"
                                "CTAACCATGTGTTTTCCTCTTTAAGTATCCAGGAAGTGTGGTTTCACTTCTATTTATTTTGGGGTCTGTAAAATTACATACACATTTACTG",
                                "AAATAATCTTTTAACTTCCTTCAGTGATCTAAACTCTGATCTTGATAAAACTATATTACTAGAAACTACATCCTTGGACCACCTTAAACAAGTGAATTGCATATC"
                                "ACTTTCACTGTGTTACATTATTCACTGTGTTACATCTTAATGTTACTGGAGTTCACGACTTCAATAAAAATACTGATGTTGTTTATATAGCTTTTATTGATTGTT"
                                "GTTTATGTAGATTTTATTTACACAGGGTCTGTCATGAGAAATTCCTTTAATTTACTGCTAGGGAGAGTTTAACTTCCTCTGAAGAATTGGT",
                                "CATGTGGCTGCAAACGACAGGATTTCATTCTTTTTTATAGCTACATAGTATTCCATTGTGTACATGTACCACATTTTCTTGATCCATTCATTTGTTGATAAACAG"
                                "GCTGATTTCATATGTTGGCTACTGAGAACAATGCTACGATAAACATGGAGGTACAGGTATCTCTTTGATTCACTGATTTCTGTTTCTTTTTTAATAAACAGACAT"
                                "TAGTGGGATTGTTGGATCACATGATAGTTCTATTTTTAGTTTTCTGAGAAACTTCCAAGCTGTTTTCCATAATGGCTGTACTAGTTTACAT",
                                "CAGAGATGAAAGAGACAGGAAGAGACGGAGACACACATAGAGGCAGAGAGAGGAAAAAAGGGCAAAGCCAGCAGGTAGTCAGACAAAGATCAGTGAGAGAGGGAG"
                                "GAAAAAGGAAAAAGAGAGTACACATTTTGATTTCAGAGATCTTTCCAGTTCCTCCTTGTAGTTCTGTGAGTGGCCCAGATGTATGTTCTATCCTGATTCTATAAG"
                                "ATAGATAATCTGTGTAACAGAGAAACCTAATTTCTATAACAGTATCCAATAGAAATAGAATGCAAGCCACATGTGTAATTTAAAATTTTGT",
                                "TGGTTGTGTTGGTATTGGCTTGCTGTCTGAAAAGTCTATGCCACTGTCAAAGTGGCTGCTGAGATGGTGGCTGTGACTCGCTGGAGAATGTTGCCATCTGCATTA"
                                "ACTGGCTGGTAGACCATGATCTGTCCTACTTGCTGCCCTTGGATAGCAATCTGCTTCTTTGTGTGTCTGGCTGGTGGTGAGGGCTGTCTGCACGTGCTGGATGAC"
                                "AATCTTCTGAGTCTGGTCTTGTTGGCCCTGAACCTGTAAAGTCTTTCCCTCTGTATCTCTATCCTCCACTTTTTTTCCCCCAGACCTCGAT",
                                "GGATCATTTGTCAACATGCCAAATAAACTTTAGCTCTCAGAGCACTTGGAAAACATGTTTTGGAGAGTCTGTGTAACATTCTGGGTGGGGCAGTTTCTAAAAGGC"
                                "TCAATCTTAAACACAAAACAGAGCAGTAAGACCAGTGATTAGTATCGATGCAACAATTTTACAGCTATGCTGAATGTGCGCTGTGTTAGGAATGCTCTAAACCCA"
                                "TGCCGGGTCAACACGTCTTTCACCTTATGTTGCCCGAAGAGTGCTAAATAGTGTGTGTTACACATTTTTAATCTTTATCCAAATAAACTTA"
                              };
    // using the FmIndex
    set<string> testStrings;
    for (auto q : queryString) {
        set<string> tmpStrings = generateKmersFromQueries(271, q, 31, 1);
        for (auto e : tmpStrings) {
            cout << e << endl;
            testStrings.insert(e);
        }
    }
    cout << "testStrings size : " << testStrings.size() << endl;

    algo::FmIndex fmIndex;
    string indexFile = "/var/tmp/TestData/ERR194147/ERR194147.fm9";
    fmIndex.loadIndexFromFile(indexFile);
    steady_clock::time_point start = steady_clock::now();
    for (auto e : testStrings) {
        fmIndex.search(e, {});
    }

    steady_clock::time_point end = steady_clock::now();
    std::cout << "Searching took "
              << duration_cast<microseconds>(end - start).count()
              << "us.\n";
}
}
