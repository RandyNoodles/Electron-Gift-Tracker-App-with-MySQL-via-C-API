#include "Utils.h"
#pragma warning(disable: 4996)


int ParseInt(char* arg, int* rValue) {

    //Points to first char after int parsed
    char* endPtr;
    //Try to parse int
    int temp = strtol(arg, &endPtr, 10);

    //Check first char after int was end of string
    if (*endPtr != '\n' && *endPtr != '\0') {
        return INVALID_ARG; //Input was not a valid integer
    }

    //Success
    *rValue = temp;
    return SUCCESS;
}