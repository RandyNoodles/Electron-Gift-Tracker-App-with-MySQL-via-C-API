#pragma once


#include "Queries_GET.h"

//ALL FUNCTIONS:
//Delete Item ID

//Return:
	//Stderr message if error
	//Rows affected
		//!This could be 0 if no matching ID


int DeleteGift(MYSQL* conn, int giftID);
int DeleteEvent(MYSQL* conn, int eventID);
int DeleteRecipient(MYSQL* conn, int recipientID);
int DeleteCategory(MYSQL* conn, int categoryID);
int DeleteLocation(MYSQL* conn, int locationID);
int DeleteUser(MYSQL* conn, int userID);