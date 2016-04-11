#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string encrypt(string, int);
string decrypt(string, int);
void encryptionInit();
int getPublicKey();
std::string string_to_hex(const std::string&);
std::string hex_to_string(const std::string&);
int Cypher(int, int);
string encypher(string, int);
string decypher(string, int);
int hexStr_to_int(string);
string hexInt_to_string(int);

int privateKey = 80085;
//static
int base = 66;
int mod = 99;

string encrypt(string input, int key){
	int secretKey = abs(key^privateKey%mod);
	return encypher(input, secretKey);
}
string decrypt(string input, int key){
	int secretKey = abs(key^privateKey%mod);
	return decypher(input, secretKey);
}

void encryptionInit(){
	privateKey = rand() % (9999 + 1) + (rand() % (9999 + 1) *10000);
}

int getPublicKey(){
return base^privateKey%mod;
}

string encypher(string input, int key){
	string hexStr =string_to_hex(input);
	string output = "";
	if(hexStr.size()<=8){
		int hexInt = hexStr_to_int(hexStr);
		int enHexInt = Cypher(hexInt, key);
		output = hexInt_to_string(enHexInt);
	}else{
		int last_i;
		for(int i = 0; i< (hexStr.size() -8); i+=8){
			int hexInt = hexStr_to_int(hexStr.substr(i,8));
			int enHexInt = Cypher(hexInt, key);
			output += hexInt_to_string(enHexInt);
			output += "-";
			last_i = i + 8;
		}
		int hexInt = hexStr_to_int(hexStr.substr(last_i,(hexStr.size()-last_i)));
		int enHexInt = Cypher(hexInt, key);
		output += hexInt_to_string(enHexInt);
	}
	return output;
}

string decypher(string input, int key){
	string output="";
	if(input.size()<=8){
		output = hex_to_string(hexInt_to_string(Cypher(hexStr_to_int(input), key)));
	}else{
		int k = -1;
		for(int i =0; i<input.size();i++){
			if(input[i] == '-'){
				output += hex_to_string(hexInt_to_string(Cypher(hexStr_to_int(input.substr(k+1, (i+1-k))), key)));
				k = i;
			}
		}
		output += hex_to_string(hexInt_to_string(Cypher(hexStr_to_int(input.substr(k+1, (input.size()-k+1))), key)));
	}
	return output;
}

int hexStr_to_int(string input){
	input = "0x" + input;
	return std::stoul(input, nullptr, 16);
}

string hexInt_to_string(int input){
	ostringstream convert;
	convert <<std::hex<< input;
	return convert.str();
}


int Cypher(int input, int keys){
	return input^keys;
}

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

std::string hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789abcdef";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}
