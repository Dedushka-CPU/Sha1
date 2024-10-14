#include <sstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <bitset>
#include <iomanip>

using std::cin;
using std::cout;

std::vector<std::string> sha1(const std::string& mes){
    std::vector<uint8_t> message(mes.begin(), mes.end());
    uint64_t lenght = message.size() * 8;
    message.push_back(0x80);
    while ((message.size() * 8) % 512 != 448) 
	{
		message.push_back(0x00); 
	}
    uint32_t A,B,C,D,E;
    A=0x67452301;
    B=0xEFCDAB89;
    C=0x98BADCFE;
    D=0x10325476;
    E=0xC3D2E1F0;
}

int main(){
    
    return 0;
}