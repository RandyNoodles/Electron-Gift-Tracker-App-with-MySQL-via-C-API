#pragma once
#include "Utils.h"
#include <mysql.h>

#define QUERY_FAILURE -1
#define NO_RESULT -2

//Login
int UserLogin(MYSQL* conn, char* username, char* password);

//Query for arrays
int GiftList(MYSQL* conn, int userId, char* rValue);


//Add stuff
int NewUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber);


#define JSON_FAILURE -1
#define JSON_BUFFER 10000
int ResultToJSON(MYSQL_RES* result, char* jsonBuffer);