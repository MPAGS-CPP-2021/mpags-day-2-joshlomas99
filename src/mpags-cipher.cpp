// Standard Library includes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    // Process command line arguments, exit if there is a failure
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)};
    if (!cmdLineStatus){
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText{""};
    std::string RawinputText{""};

    // Read in user input from stdin/file
    // If input file is specified, read to input_text variable
    if (!inputFile.empty()) {
        std::ifstream in_file {inputFile};
        bool ok_to_read = in_file.good();
        if (ok_to_read){
            in_file >> RawinputText;
            for (size_t i{0}; i < RawinputText.length(); i++){
                inputChar = RawinputText[i];
                inputText += tranformChar(inputChar);
            }
        }
        else {
            std::cerr << "[error] input file ('" << inputFile
                      << "') not opened correctly, exiting.";
        }
    }
    else {
        // If no input file is specified, loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += tranformChar(inputChar);
        }
    }

    // Print out the transliterated text

    // If output file is specified, write output to it and exit
    if (!outputFile.empty()) {
        std::ofstream out_file {outputFile, std::ios::app};
        bool ok_to_write = out_file.good();
        if (ok_to_write){
            out_file << inputText + "\n";
            return 0;
        }
        else {
            std::cerr << "[error] output file ('" << outputFile
                      << "') not opened correctly, exiting.";
        }
    }
    // If no output file is specified, write output to command line and exit
    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
