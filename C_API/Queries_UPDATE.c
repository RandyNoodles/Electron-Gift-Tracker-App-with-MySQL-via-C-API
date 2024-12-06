#include "Queries_UPDATE.h"
#pragma warning(disable: 4996)


int UpdateGift(MYSQL* conn, const char* giftID, const char* name, const char* cost, 
	const char* statusID, const char* recipientID, const char* eventID, const char* locationID) {

	int result = ItemExists(conn, "Gift", giftID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate GiftID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "GiftID: <%s> does not exist. Abandoning Update operation.", giftID);
		return QUERY_FAILURE;
	}

	//NEED TO WRITE QUERY IN HERE
	char query[QUERY_BUFFER];
	sprintf(query,
		"");

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "UpdateGift()");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}


///
//EVERYTHING PAST HERE ONLY HAS "Does this Item Exist?"
//Still need to do queries, error handle, and return value.
///

int UpdateEvent(MYSQL* conn, const char* eventID, const char* name) {
	int result = ItemExists(conn, "Event", eventID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate GiftID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "EventID: <%s> does not exist. Abandoning Update operation.", eventID);
		return QUERY_FAILURE;
	}
}
int UpdateRecipient(MYSQL* conn, const char* recipientID, const char* firstName, const char* lastName) {
	int result = ItemExists(conn, "Recipient", recipientID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate RecipientID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "RecipientID: <%s> does not exist. Abandoning Update operation.", recipientID);
		return QUERY_FAILURE;
	}
}
int UpdateCategory(MYSQL* conn, const char* categoryID, const char* name) {
	int result = ItemExists(conn, "Category", categoryID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate CategoryID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "CategoryID: <%s> does not exist. Abandoning Update operation.", categoryID);
		return QUERY_FAILURE;
	}
}
int UpdateLocation(MYSQL* conn, const char* locationID, const char* name, const char* address) {
	int result = ItemExists(conn, "PurchaseLocation", locationID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate LocationID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "PurchaseLocationID: <%s> does not exist. Abandoning Update operation.", locationID);
		return QUERY_FAILURE;
	}
}