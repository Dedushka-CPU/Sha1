#include <sstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <bitset>
#include <iomanip>

using std::cin;
using std::cout;

std::string sha1(const std::string& mes) {
    std::vector<uint8_t> message(mes.begin(), mes.end());
    uint64_t length = message.size() * 8;
    message.push_back(0x80);
    while ((message.size() * 8) % 512 != 448) {
        message.push_back(0x00);
    }
    for (int i = 7; i >= 0; --i) {
        message.push_back(static_cast<uint8_t>(length >> (i * 8)));
    }
    std::vector<uint32_t> h = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0 };

    for (size_t i = 0; i < message.size(); i += 64) {
        std::array<uint32_t, 80> w = {0};

        for (int j = 0; j < 16; ++j) {
            w[j] = (message[i + j * 4] << 24) | (message[i + j * 4 + 1] << 16) | (message[i + j * 4 + 2] << 8) | message[i + j * 4 + 3];
        }

        for (int j = 16; j < 80; ++j) {
            w[j] = (w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16]);
            w[j] = (w[j] << 1) | (w[j] >> 31);
        }

        uint32_t a = h[0];
        uint32_t b = h[1];
        uint32_t c = h[2];
        uint32_t d = h[3];
        uint32_t e = h[4];

        for (int j = 0; j < 80; ++j) {
            uint32_t f, k;
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = (a <<< 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = b <<< 30;
            b = a;
            a = temp;
        }

        h[0] += a;
        h[1] += b;
        h[2] += c;
        h[3] += d;
        h[4] += e;
    }

    std::ostringstream result;
    for (uint32_t value : h) {
        result << std::hex << std::setw(8) << std::setfill('0') << value;
    }

    return result.str();
}

int main() {
    std::string data = "Hello world";
    std::string hash = sha1(data);
    cout << "SHA-1: " << hash << cout<<"\n";
    return 0;
}
