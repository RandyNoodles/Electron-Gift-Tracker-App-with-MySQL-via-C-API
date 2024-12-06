#pragma once
#include "Utils.h"

#define QUERY_BUFFER 1000

//Login
int UserLogin(MYSQL* conn, char* username, char* password);

int ItemExists(MYSQL* conn, char* tableName, char* id);





