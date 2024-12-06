#include "Queries_ADD.h"
#pragma warning(disable: 4996)

int AddGift(MYSQL* conn, char* name, char* cost,
	char* statusID, char* recipientID, char* eventID, char* locationID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"INSERT INTO gift "
		"(`Name`, Cost, StatusID, RecipientID, EventID, LocationID) "
		"VALUES "
		"('%s', %s, %s, %s, %s, %s);",
		name, cost, statusID, recipientID, eventID, locationID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "AddGift(): ");
		return QUERY_FAILURE;
	}
	return mysql_insert_id(conn);
}

int AddEvent(MYSQL* conn, char* name, char* date, char* categoryID, char* userID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"INSERT INTO `event` (`Name`, `Date`, CategoryID, UserID) "
		"VALUES "
		"('%s', '%s', %s, %s);",
		name, date, categoryID, userID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "AddEvent(): ");
		return QUERY_FAILURE;
	}
	return mysql_insert_id(conn);
}

int AddRecipient(MYSQL* conn, char* firstName, char* lastName, char* dateOfBirth, char* userID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"INSERT INTO recipient (FirstName, LastName, DateOfBirth, UserID) "
		"VALUES "
		"('%s', '%s', '%s', %s);",
		firstName, lastName, dateOfBirth, userID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "AddRecipient(): ");
		return QUERY_FAILURE;
	}
	return mysql_insert_id(conn);
}

int AddCategory(MYSQL* conn, char* name) {
	fprintf(stderr, "Function not implemented.");
	return QUERY_FAILURE;
}

int AddLocation(MYSQL* conn, char* name, char* webAddress, char* physicalLocation) {
	fprintf(stderr, "Function not implemented.");
	return QUERY_FAILURE;
}

int AddUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"INSERT INTO `user` (UserName, `Password`, FirstName, LastName, Email, PhoneNumber) "
		"VALUES "
		"('%s', '%s', '%s', '%s', '%s', '%s');",
		username, password, firstName, lastName, email, phoneNumber);
		

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "AddUser(): ");
		return QUERY_FAILURE;
	}
	return mysql_insert_id(conn);
}