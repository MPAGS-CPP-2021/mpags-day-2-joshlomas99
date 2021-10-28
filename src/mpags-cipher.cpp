// Standard Library includes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// For std::isalpha and std::isupper
#include <cctype>

// Our project headers
#include "MPAGSCipher/TransformChar.hpp"
#include "MPAGSCipher/ProcessCommandLine.hpp"
#include "MPAGSCipher/runCaesarCipher.hpp"

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    bool encrypt{true};
    std::string inputFile{""};
    std::string outputFile{""};
    size_t key{0};

    // Process command line arguments, exit if there is a failure
    const bool cmdLineStatus{processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, encrypt, key)};
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
            << "  -e INT (0 or 1)  Select whether to decrypt (0) or encrypt (1) input text\n"
            << "                   Defaults to 1\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -k INT (>= 0)    Specify key for Caesar cipher\n"
            << "                   No cipher will run if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --version        Print version information\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "1.0.1" << std::endl;
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
        if (in_file.good()){
            while (in_file >> inputChar){
                inputText += tranformChar(inputChar);
            }
        }
        else {
            std::cerr << "[error] input file ('" << inputFile
                      << "') not opened correctly, exiting.";
            return 1;
        }
    }
    else {
        // If no input file is specified, loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += tranformChar(inputChar);
        }
    }

    // Apply a cipher to the transliterated text if a key is given
    if (key != 0){
        inputText = runCaesarCipher(inputText, key, encrypt);
    }

    // If output file is specified, write output to it and exit
    if (!outputFile.empty()) {
        std::ofstream out_file {outputFile, std::ios::app};
        if (out_file.good()){
            out_file << inputText + "\n";
            return 0;
        }
        else {
            std::cerr << "[error] output file ('" << outputFile
                      << "') not opened correctly, exiting.";
            return 1;
        }
    }
    // If no output file is specified, write output to command line and exit
    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
