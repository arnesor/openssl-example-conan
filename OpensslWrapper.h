#ifndef OPENSSLWRAPPER_H
#define OPENSSLWRAPPER_H

#include <string>

class OpensslWrapper
{
public:
    OpensslWrapper();
    ~OpensslWrapper();

    static constexpr unsigned int KEY_SIZE = 32;
    static constexpr unsigned int BLOCK_SIZE = 16;

    void gen_params();
    void aes_encrypt(const std::string& ptext, std::string& ctext) const;
    void aes_decrypt(const std::string& ctext, std::string& rtext) const;

private:
    unsigned char key[KEY_SIZE];
    unsigned char iv[BLOCK_SIZE];
};

#endif

