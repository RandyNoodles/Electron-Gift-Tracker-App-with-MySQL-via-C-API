#pragma once

#include "Queries_OTHER.h"


int UpdateGift(MYSQL* conn, char* giftID, char* name, char* cost, char* statusID, char* recipientID, char* eventID, char* locationID);
int UpdateEvent(MYSQL* conn, char* eventID, char* name, char* date, char* categoryID, char* userID);
int UpdateRecipient(MYSQL* conn, char* recipientID, char* firstName, char* lastName, char* dateOfBirth, char* userID);
int UpdateCategory(MYSQL* conn, char* categoryID, char* name);
int UpdateLocation(MYSQL* conn, char* locationID, char* name, char* webAddress, char* physicalLocation);
int UpdateUser(MYSQL* conn, char* userId, char* password, char* firstName, char* lastName, char* email, char* phone);
