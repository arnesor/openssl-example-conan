#include "OpensslWrapper.h"
#include <stdexcept>
#include <openssl/rand.h>



using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

OpensslWrapper::OpensslWrapper()
{
    EVP_add_cipher(EVP_aes_256_cbc());  // Load the necessary cipher
    gen_params();                       // To initialize key and iv
}

OpensslWrapper::~OpensslWrapper()
{
}

void OpensslWrapper::gen_params()
{
    int rc = RAND_bytes(key, KEY_SIZE);
    if (rc != 1)
      throw std::runtime_error("RAND_bytes key failed");

    rc = RAND_bytes(iv, BLOCK_SIZE);
    if (rc != 1)
      throw std::runtime_error("RAND_bytes for iv failed");
}

void OpensslWrapper::aes_encrypt(const secure_string& ptext, secure_string& ctext) const
{
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptInit_ex failed");

    // Recovered text expands upto BLOCK_SIZE
    ctext.resize(ptext.size()+BLOCK_SIZE);
    int out_len1 = (int)ctext.size();

    rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1, (const byte*)&ptext[0], (int)ptext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptUpdate failed");
  
    int out_len2 = (int)ctext.size() - out_len1;
    rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw std::runtime_error("EVP_EncryptFinal_ex failed");

    // Set cipher text size now that we know it
    ctext.resize(out_len1 + out_len2);
}


void OpensslWrapper::aes_decrypt(const secure_string& ctext, secure_string& rtext) const
{
    EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
    int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptInit_ex failed");

    // Recovered text contracts upto BLOCK_SIZE
    rtext.resize(ctext.size());
    int out_len1 = (int)rtext.size();

    rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1, (const byte*)&ctext[0], (int)ctext.size());
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptUpdate failed");
  
    int out_len2 = (int)rtext.size() - out_len1;
    rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0]+out_len1, &out_len2);
    if (rc != 1)
      throw std::runtime_error("EVP_DecryptFinal_ex failed");

    // Set recovered text size now that we know it
    rtext.resize(out_len1 + out_len2);
}

