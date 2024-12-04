#pragma once
#include "Utils.h"


#define QUERY_FAILURE -1
#define NO_RESULT -2

//Login
int UserLogin(MYSQL* conn, char* username, char* password);

//Query for arrays
int GiftList(MYSQL* conn, int userId, char* rValue);


//Add stuff
int NewUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber);

