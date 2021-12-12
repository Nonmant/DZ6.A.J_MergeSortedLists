#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("input.txt", std::ofstream::trunc);
    inputPrepare<<
                "3 6\n"
                "1 4 7 10 13 16 \n"
                "0 2 5 9 14 20 \n"
                "1 7 16 16 21 22 "
            ;
    inputPrepare.close();

    std::ifstream input( "input.txt", std::ofstream::in);
    std::ofstream output("output.txt", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();

    std::ifstream outputCheck("output.txt", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    INFO(buffer.str());
    REQUIRE(buffer.str() ==
            "7\n"
            "10\n"
            "9\n"
    );
}

TEST_CASE("1 size len", ""){
    std::stringstream input(
            "3 1\n"
            "1\n"
            "2\n"
            "3\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "1\n"
                    "1\n"
                    "2\n"
    );
}

TEST_CASE("not overlapping sequences", ""){
    std::stringstream input(
            "3 3\n"
            "1 2 3\n"
            "4 5 6\n"
            "7 8 9\n"
    );
    std::stringstream output;
    parseFile(input,output);
    REQUIRE(output.str() ==
                    "3\n"
                    "3\n"
                    "6\n"
    );
}
