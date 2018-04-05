#include "OpensslWrapper.h"
#include <string>
#include <gtest/gtest.h>

TEST(OpensslWrapper, encrypt_decrypt)
{
    OpensslWrapper ow;

    // plaintext, ciphertext, recovered text
    const std::string ptext = "Now is the time for all good men to come to the aide of their country";
	std::string ctext;
	std::string rtext;

    ow.aes_encrypt(ptext, ctext);
    ow.aes_decrypt(ctext, rtext);

    EXPECT_EQ(ptext, rtext);
    EXPECT_NE(ptext, ctext);
}


