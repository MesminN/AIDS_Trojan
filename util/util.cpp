#include <openssl/buffer.h>
#include <openssl/evp.h>
#include "util.h"

using namespace std;

std::string hex_encode(const std::string& input) {
    static const char hex_lookup[] = "0123456789abcdef";
    std::string output;
    output.reserve(input.size() * 2);

    for (unsigned char c : input) {
        output.push_back(hex_lookup[c >> 4]);
        output.push_back(hex_lookup[c & 0x0F]);
    }

    return output;
}
std::string hex_decode(const std::string& hex_string) {
    std::string output;
    output.reserve(hex_string.size() / 2);

    for (std::string::size_type i = 0; i < hex_string.size(); i += 2) {
        std::string byte = hex_string.substr(i, 2);
        char chr = (char)strtol(byte.c_str(), nullptr, 16);
        output.push_back(chr);
    }

    return output;
}