#include "HuffmanArchiver.h"
#include "CLI.h"
#include <iostream>

int main(int argc, char *argv[]) {
    static_assert(CHAR_BIT == 8);
    std::vector<std::string> arguments(argv + 1, argv + argc);
    CLI::CLI parser(arguments);
    std::ifstream in(parser.getInputFile(), std::ios::binary);
    std::ofstream out(parser.getOutputFile(), std::ios::binary);
    Archiver::HuffmanArchiver archiver(in, out);
    if (parser.getMode() == CLI::ArchiverMode::Encode)
        archiver.compress();
    if (parser.getMode() == CLI::ArchiverMode::Decode)
        archiver.extract();
    auto stats = archiver.getStats();
    std::cout << stats.getInputSize() << '\n';
    std::cout << stats.getOutputSize() << '\n';
    std::cout << stats.getExtraDataSize() << '\n';
    return 0;
}
