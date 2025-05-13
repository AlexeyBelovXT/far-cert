#include <stdio.h>

#include "openssl/x509.h"
#include "far/plugin.hpp"

int main()
{
    printf("hi!\n");
    X509_PUBKEY_eq(NULL, NULL);
    return 0;
}