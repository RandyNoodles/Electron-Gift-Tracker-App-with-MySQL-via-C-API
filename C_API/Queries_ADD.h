#pragma once

#include "Queries_DELETE.h"

//Command enums start at 200
//Should be in order here. (i.e. AddEvent = 201, AddRecipient = 202 etc..)

//All queries here return QUERY_FAILURE on failure (-1)
//Return ID of added row in case of success (positive int)

int AddGift(MYSQL* conn, char* name, char* cost, 
	char* statusID, char* recipientID, char* eventID, char* locationID, char* userID);

int AddEvent(MYSQL* conn, char* name, char* date, char* categoryID, char* userID);

int AddRecipient(MYSQL* conn, char* firstName, char* lastName, char* dateOfBirth, char* userID);

int AddCategory(MYSQL* conn, char* name);

int AddLocation(MYSQL* conn, char* name, char* webAddress, char* physicalLocation);

int AddUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber);