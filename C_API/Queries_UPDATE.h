#pragma once

#include "Queries_OTHER.h"


int UpdateGift(MYSQL* conn, const char* giftID, const char* name, const char* cost, const char* statusID, const char* recipientID, const char* eventID, const char* locationID);
int UpdateEvent(MYSQL* conn, const char* eventID, const char* name);
int UpdateRecipient(MYSQL* conn, const char* recipientID, const char* firstName, const char* lastName);
int UpdateCategory(MYSQL* conn, const char* categoryID, const char* name);
int UpdateLocation(MYSQL* conn, const char* locationID, const char* name, const char* address);
