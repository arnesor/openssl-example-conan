#include "OpensslWrapper.h"
#include <gtest/gtest.h>

TEST(OpensslWrapper, encrypt_decrypt)
{
    OpensslWrapper ow;

    // plaintext, ciphertext, recovered text
    secure_string ptext, ctext, rtext;
    ptext = "Now is the time for all good men to come to the aide of their country";

    ow.aes_encrypt(ptext, ctext);
    ow.aes_decrypt(ctext, rtext);

    EXPECT_EQ(ptext, rtext);
    EXPECT_NE(ptext, ctext);
}


