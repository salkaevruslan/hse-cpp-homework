#ifndef CLI_H
#define CLI_H

#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>

namespace CLI {

enum class ArchiverMode {
    Encode,
    Decode,
    None
};

class CLI final {
public:
    explicit CLI(std::vector<std::string> args);

    std::string getInputFile() const;

    std::string getOutputFile() const;

    ArchiverMode getMode() const;

private:
    ArchiverMode mode_;
    std::string input_file_name_;
    std::string output_file_name_;
};

class ParserException final : public std::logic_error {
public:
    explicit ParserException(const char *msg);
};

}

#endif //HUFFMAN_CLI_H
