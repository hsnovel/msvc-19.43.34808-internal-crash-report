#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;

typedef struct
{
    char *Data;
    u32 Size;
    u32 Capacity;
} STRING;

#if defined(__unix__) || defined(__unix) || defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX
static const u32 PlatformLinux = 1;
static const u32 PlatformWindows = 0;
#elif defined(_WIN32) || defined(__WINDOWS__)
static const u32 PlatformLinux = 0;
static const u32 PlatformWindows = 1;
#define PLATFORM_WINDOWS
#else
#   error "Platform not supported"
#endif



#ifdef PLATFORM_WINDOWS
static STRING PlatformOnlyIncludes[] =
{
    // {.Data = "Test", },
};
#else  PLATFORM_LINUX
const STRING PlatformOnlyIncludes[] =
{
    MAKE_STRING("Test"),
    MAKE_STRING("Test2"),
};
#endif

#define MAKE_STRING(StringData) (STRING){ .Data = StringData, .Size = strlen(StringData), .Capacity = strlen(StringData)}
#define MAKE_STRING2(StringData) { .Data = StringData, .Size = strlen(StringData), .Capacity = strlen(StringData)}

static STRING
AllocateStringWithCapacity(char *String, u32 Capacity)
{
    u32 StringLen = strlen(String);
    STRING Result =
    {
        .Data = malloc(Capacity),
        .Size = StringLen,
        .Capacity = Capacity
    };

    memcpy(Result.Data, String, StringLen);
    return Result;
}

static STRING
AllocateString(char *String)
{
    u32 Capacity = strlen(String) * 10;
    return AllocateStringWithCapacity(String, Capacity);
}

static void
StringAppend(STRING *AppendTo, STRING Source)
{
    u32 NecesarryCap = AppendTo->Size + Source.Size;
    if(AppendTo->Capacity < NecesarryCap)
    {
        *AppendTo = AllocateStringWithCapacity(AppendTo->Data, NecesarryCap * 2);
    }

    memcpy(AppendTo->Data + AppendTo->Size, Source.Data, Source.Size);
    AppendTo->Size += Source.Size;
}

int
main(int ArgCount, char **Args)
{
    STRING Command = AllocateString("clang ");
    printf("%d\n", sizeof("Test"));

    //----------------
    // Include folders
    {
        StringAppend(&Command, MAKE_STRING(""));
        // if(PlatformWindows)
        // {
        //     StringAppend(&Command, Command2);
        // }
    }

    return 0;
}
