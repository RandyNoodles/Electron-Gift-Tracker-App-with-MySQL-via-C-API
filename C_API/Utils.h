#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#define INVALID_ARG 1
#define SUCCESS 0

#define QUERY_FAILURE -1
#define NO_RESULT -2


//ALL FUNCTIONS IN THIS SECTION RETURN:
//SUCCESS or INVALID_ARG


int IsUDouble(char* arg);//Checks for positive double
int IsUInt(char* arg);//Checks for positive int

int IsNull(char* arg);//Checks if string == "null" (any case)
						//NOTE: turns 'arg' lowercase.


int ParseInt(char* arg, int* rValue);//Parsed int is stored in rValue



//Prints "functionName: <sql error>" to stderr
void PrintSQLError(MYSQL* conn, const char* functionName);


#define JSON_FAILURE -1
#define JSON_BUFFER 10000
int ResultToJSON(MYSQL_RES* result, char* jsonBuffer);