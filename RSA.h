#pragma once

#include <C:/boost_1_75_0/boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;
class msg_padding;
class generating_key{
    protected:
    cpp_int p,q;
    cpp_int phi;
    cpp_int n;
    double d;
    int e;
    public:
    generating_key(cpp_int p,cpp_int q,int e);
    double calculate_d();
    cpp_int gcd(cpp_int x,cpp_int y);
    bool primality_check(cpp_int x);
   
};

class encrypt_decrypt: public generating_key{
    protected:
    vector<string> m;
    vector<cpp_int> padded_m;
    vector<cpp_int> c; // cipher
    vector<cpp_int>::iterator i;
    vector<char> en_text;
    cpp_int push_decrypt;
    vector<cpp_int> decrypted;
    vector<cpp_int>::iterator boost_i;

    cpp_int push_c;
    public:
    encrypt_decrypt(cpp_int p,cpp_int q, int e);
    void encrypt();
    void encrypted_text();
    void decrypt(vector<cpp_int> dec);
};

class msg_padding:public encrypt_decrypt{
public:
msg_padding();
msg_padding(cpp_int p,cpp_int q, int e);
void convert_to_int(string);
void convert_to_string();

};

class Encrypt_Decrypt_file:public msg_padding{

public:
 ofstream ofile;
 ifstream ifile;
Encrypt_Decrypt_file(cpp_int p,cpp_int q, int e);
void encryptfile(string file_name);
void decryptfile(string file_name);
};


