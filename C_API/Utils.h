#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define INVALID_ARG 1
#define SUCCESS 0

#define QUERY_FAILURE -1
#define NO_RESULT -2



int ParseInt(char* arg, int* rValue);



#define JSON_FAILURE -1
#define JSON_BUFFER 10000
int ResultToJSON(MYSQL_RES* result, char* jsonBuffer);