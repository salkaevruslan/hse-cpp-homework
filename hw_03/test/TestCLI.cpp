#include "doctest.h"
#include "CLI.h"
#include <vector>
#include <string>

namespace TestCLI {

TEST_CASE ("Normal Input") {
    SUBCASE("Use --file") {
        std::vector<std::string> args = {"-u", "--file", "in.txt", "-o", "out.txt"};
        CLI::CLI parser(args);
        CHECK(parser.getMode() == CLI::ArchiverMode::Decode);
        CHECK(!parser.getInputFile().compare("in.txt"));
        CHECK(!parser.getOutputFile().compare("out.txt"));
    }
    SUBCASE("Use --output") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "--output", "out.txt"};
        CLI::CLI parser(args);
        CHECK(parser.getMode() == CLI::ArchiverMode::Decode);
        CHECK(!parser.getInputFile().compare("in.txt"));
        CHECK(!parser.getOutputFile().compare("out.txt"));
    }
    SUBCASE("Compress mode ") {
        std::vector<std::string> args = {"-c", "-f", "in.txt", "-o", "out.txt"};
        CLI::CLI parser(args);
        CHECK(parser.getMode() == CLI::ArchiverMode::Encode);
        CHECK(!parser.getInputFile().compare("in.txt"));
        CHECK(!parser.getOutputFile().compare("out.txt"));
    }
    SUBCASE("Extract mode") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o", "out.txt"};
        CLI::CLI parser(args);
        CHECK(parser.getMode() == CLI::ArchiverMode::Decode);
        CHECK(!parser.getInputFile().compare("in.txt"));
        CHECK(!parser.getOutputFile().compare("out.txt"));
    }
}

TEST_CASE ("Wrong input") {
    SUBCASE("No mode") {
        std::vector<std::string> args = {"-f", "in.txt", "-o", "out.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "No archiver mode");
    }
    SUBCASE("No input file") {
        std::vector<std::string> args = {"-u", "-o", "out.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "No input file");
    }
    SUBCASE("No input file") {
        std::vector<std::string> args = {"-u", "-f", "in.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "No output file");
    }
    SUBCASE("Multiple archiver mode") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o", "out.txt", "-c"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Multiple archiver mode");
    }
    SUBCASE("Multiple input file") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o", "out.txt", "-f", "in2.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Multiple input file");
    }
    SUBCASE("Multiple output file") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o", "out.txt", "--output", "in2.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Multiple output file");
    }
    SUBCASE("Not enough arguments") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Not enough arguments");
    }
    SUBCASE("Same input and output") {
        std::vector<std::string> args = {"-u", "-f", "in.txt", "-o", "in.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Input and output files can't be same");
    }
    SUBCASE("Unknown parameter") {
        std::vector<std::string> args = {"-c", "-f", "in.txt", "foo", "-o", "out.txt"};
        CHECK_THROWS_WITH(CLI::CLI parser(args), "Unknown parameter");
    }
}
}
