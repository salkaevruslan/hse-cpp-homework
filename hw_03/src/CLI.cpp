#include "CLI.h"
#include <string>

namespace CLI {

CLI::CLI(std::vector<std::string> args) {
    mode_ = ArchiverMode::None;
    for (std::size_t i = 0; i < args.size(); ++i) {
        if (args[i] == "-c") {
            if (mode_ != ArchiverMode::None)
                throw ParserException("Multiple archiver mode");
            mode_ = ArchiverMode::Encode;
        } else if (args[i] == "-u") {
            if (mode_ != ArchiverMode::None)
                throw ParserException("Multiple archiver mode");
            mode_ = ArchiverMode::Decode;
        } else if (args[i] == "-f" || args[i] == "--file") {
            if (!input_file_name_.empty()) {
                throw ParserException("Multiple input file");
            }
            if (i == args.size() - 1)
                throw ParserException("Not enough arguments");
            input_file_name_ = args[++i];
        } else if (args[i] == "-o" || args[i] == "--output") {
            if (!output_file_name_.empty()) {
                throw ParserException("Multiple output file");
            }
            if (i == args.size() - 1)
                throw ParserException("Not enough arguments");
            output_file_name_ = args[++i];
        } else
            throw ParserException("Unknown parameter");
    }
    if (mode_ == ArchiverMode::None)
        throw ParserException("No archiver mode");
    if (input_file_name_.empty())
        throw ParserException("No input file");
    if (output_file_name_.empty())
        throw ParserException("No output file");
    if (input_file_name_ == output_file_name_)
        throw ParserException("Input and output files can't be same");
}

std::string CLI::getOutputFile() const {
    return output_file_name_;
}

std::string CLI::getInputFile() const {
    return input_file_name_;
}

ArchiverMode CLI::getMode() const {
    return mode_;
}

ParserException::ParserException(const char *msg) : std::logic_error(msg) {
}

}