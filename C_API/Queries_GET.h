#pragma once
#include "Queries_UPDATE.h"

MYSQL_RES* GetGifts(MYSQL* conn, int userId);
MYSQL_RES* GetEvents(MYSQL* conn, int userId);
MYSQL_RES* GetRecipients(MYSQL* conn, int userId);
MYSQL_RES* GetStatuses(MYSQL* conn, int userId);//NOTE: Statuses are global. No userID required.
												//We've included it regardless to simplify logic.

MYSQL_RES* GetUser(MYSQL* conn, int userId);

//NEED TO FIGURE OUT WHAT DO DO ABOUT THESE ERD-WISE
MYSQL_RES* GetCategories(MYSQL* conn, int userId);
MYSQL_RES* GetPurchaseLocations(MYSQL* conn, int userId);


//Do we need this? Or should we just filter client-side.
MYSQL_RES* GetEventRecipients(MYSQL* conn, int eventId); // Retrieve recipients tied to a specific event
MYSQL_RES* GetGiftById(MYSQL* conn, int giftId);
