#include <stdio.h>

#include "openssl/x509.h"
#include "far/plugin.hpp"

HANDLE WINAPI OpenW(const struct OpenInfo *OInfo)
{
    printf("hi!\n");
    return NULL;
}

void WINAPI ExitFARW(const struct ExitInfo *Info)
{
    printf("hi!\n");
}

void WINAPI GetPluginInfoW(struct PluginInfo *Info)
{
    printf("hi!\n");
}

void WINAPI GetGlobalInfoW(struct GlobalInfo *Info)
{
    printf("hi!\n");
}

void WINAPI SetStartupInfoW(const struct PluginStartupInfo *Info)
{
    printf("hi!\n");
}

// int main()
// {
//     printf("hi!\n");
//     //X509_PUBKEY_eq(NULL, NULL);
//     return 0;
// }