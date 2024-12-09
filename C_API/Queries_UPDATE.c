#include "Queries_UPDATE.h"
#pragma warning(disable: 4996)


int UpdateGift(MYSQL* conn, char* giftID, char* name, char* cost, 
	char* statusID, char* recipientID, char* eventID, char* locationID) {

	int result = ItemExists(conn, "Gift", giftID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate GiftID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "GiftID: <%s> does not exist. Abandoning Update operation.", giftID);
		return QUERY_FAILURE;
	}

	char query[QUERY_BUFFER];
	sprintf(query,
		"UPDATE gift SET "
		"`Name` = %s, "
		"Cost = %s, "
		"StatusID = %s, "
		"RecipientID = %s, "
		"EventID = %s, "
		"PurchaseLocationID = %s "
		"WHERE giftID = %s; ",
		name, cost, statusID, recipientID, eventID, locationID, giftID);

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

int UpdateEvent(MYSQL* conn, char* eventID, char* name, char* date, char* categoryID, char* userID) {
	int result = ItemExists(conn, "Event", eventID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate GiftID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "EventID: <%s> not found or does not belong to current user. Abandoning Update operation.", eventID);
		return QUERY_FAILURE;
	}

	char query[QUERY_BUFFER];
	sprintf(query,
		"UPDATE event SET "
		"`Name` = %s, "
		"`Date` = %s, "
		"CategoryID = %s, "
		"WHERE EventID = %s AND UserID = %s; ",
		name, date, categoryID, eventID, userID);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "UpdateEvent()");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}
int UpdateRecipient(MYSQL* conn, char* recipientID, char* firstName, char* lastName, char* dateOfBirth, char* userID) {
	int result = ItemExists(conn, "Recipient", recipientID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate RecipientID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "RecipientID: <%s> not found or does not belong to current user. Abandoning Update operation.", recipientID);
		return QUERY_FAILURE;
	}

	char query[QUERY_BUFFER];
	sprintf(query,
		"UPDATE recipient SET "
		"FirstName = %s, "
		"LastName = %s, "
		"DateOfBirth = %s "
		"WHERE RecipientID = %s AND UserID = %s;",
		firstName, lastName, dateOfBirth, recipientID, userID);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "UpdateRecipient()");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);

}
int UpdateCategory(MYSQL* conn, char* categoryID, char* name) {
	int result = ItemExists(conn, "Category", categoryID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure during validation of CategoryID's existence.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "CategoryID: <%s> does not exist. Abandoning Update operation.", categoryID);
		return QUERY_FAILURE;
	}

	result = IsUniversal(conn, "Category", categoryID);
	if (result == 0) {
		fprintf(stderr, "Updating of universal category listings is not allowed.");
		return QUERY_FAILURE;
	}

	char query[QUERY_BUFFER];
	sprintf(query,
		"UPDATE recipient SET "
		"`Name` = %s "
		"WHERE categoryID = %d;",
		name, categoryID);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "UpdateCategory()");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);

}
int UpdateLocation(MYSQL* conn, char* locationID, char* name, char* webAddress, char* physicalLocation) {
	int result = ItemExists(conn, "PurchaseLocation", locationID);
	if (result == QUERY_FAILURE) {
		fprintf(stderr, "Failure to validate LocationID's existence. Abandoning Update operation.");
		return QUERY_FAILURE;
	}
	if (result == NO_RESULT) {
		fprintf(stderr, "PurchaseLocationID: <%s> does not exist. Abandoning Update operation.", locationID);
		return QUERY_FAILURE;
	}

	result = IsUniversal(conn, "PurchaseLocation", locationID);
	if (result == 0) {
		fprintf(stderr, "Updating of universal purchase location listings is not allowed.");
		return QUERY_FAILURE;
	}

	char query[QUERY_BUFFER];
	sprintf(query,
		"UPDATE purchaseLocation SET "
		"`Name` = %s, "
		"WebAddress = %s ",
		"PhysicalLocation = %s "
		"WHERE PurchaseLocationID = %d; ",
		name, webAddress, physicalLocation, locationID);
		

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "UpdateLocation()");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}