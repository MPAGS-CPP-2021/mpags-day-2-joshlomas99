// Standard Library includes
#include <string>

// Our project headers
#include "runCaesarCipher.hpp"

std::string runCaesarCipher(const std::string& inputText,
    const size_t key, const bool encrypt)
{
    // Create the alphabet container and output string
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::string outputText{""};
    // Loop over the input text
    for (size_t i{0}; i < inputText.length(); i++)
    {
        char inputChar{inputText[i]};

        // For each character find the corresponding position in the alphabet
        int j{0};
        while (inputChar != alphabet[j]){
            j++;
        }

        // Apply the shift (+ve or –ve depending on encrypt/decrypt)
        // to the position, handling correctly potential wrap-around
        // If encrypt is True (1) adds key to the alphabet position
        // If encrypt is False (0) minuses key from the alphabet position
        j += ((-1+(encrypt*2))*key);
        // Then modulus (%) finds remainder from division by 26, to ensure j is between 0 and 25
        if (j >= 0) {
            j %= 26;
        }
        // Handling negative numbers since modulus doesn't seem to work properly on them
        else {
            j += 26;
        }

        // Determine the new character and add it to the output string
        outputText += alphabet[j];
    }
    // Finally (after the loop), return the output string
    return outputText;
}
