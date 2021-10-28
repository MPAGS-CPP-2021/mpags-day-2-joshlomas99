// Standard Library includes
#include <iostream>
#include <string>
#include <vector>

// Our project headers
#include "ProcessCommandLine.hpp"

bool processCommandLine(const std::vector<std::string> cmdLineArgs, bool& helpRequested,
    bool& versionRequested, std::string& inputFile, std::string& outputFile, bool& encrypt,
    size_t& key){
    
    // Store size of cmdLineArgs
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            helpRequested = true;
        }
        else if (cmdLineArgs[i] == "--version") {
            versionRequested = true;
        }
        else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with false return to indicate failure
                return false;
            }
            else {
                // Got filename, so assign value and advance past it
                inputFile = cmdLineArgs[i + 1];
                ++i;
            }
        }
        else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with false return to indicate failure
                return false;
            }
            else {
                // Got filename, so assign value and advance past it
                outputFile = cmdLineArgs[i + 1];
                ++i;
            }
        }
        else if (cmdLineArgs[i] == "-e"){
            // Handle encrypt option
            // Next element is 0 or 1 unless "-e" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -e requires either 0 or 1 as argument."
                          << std::endl;
                // exit main with false return to indicate failure
                return false;
            }
            else {
                // Got , so assign value and advance past it
                encrypt = std::stoul(cmdLineArgs[i + 1]);
                ++i;
            }
        }
        else if (cmdLineArgs[i] == "-k"){
            // Handle key option
            // Next element is key unless "-k" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -k requires an integer value."
                          << std::endl;
                // exit main with false return to indicate failure
                return false;
            }
            else {
                // Got key, so assign value and advance past it
                key = std::stoul(cmdLineArgs[i + 1]);
                ++i;
            }
        }
        else {
            // Have an unknown flag to output error message and return false
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
            return false;
        }

    }
    // Return as true if the process runs successfully
    return true;
}
