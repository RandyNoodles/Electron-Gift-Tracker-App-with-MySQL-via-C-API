#include "Queries_ADD.h"
#pragma warning(disable: 4996)

int AddGift(MYSQL* conn, char* name, char* cost,
	char* statusID, char* recipientID, char* eventID, char* locationID) {
	char query[QUERY_BUFFER];

	printf("QUERY:\n"
		"INSERT INTO gift "
		"(`Name`, Cost, StatusID, RecipientID, EventID, LocationID) "
		"VALUES "
		"('%s', %s, %s, %s, %s, %s);\n",
		name, cost, statusID, recipientID, eventID, locationID);


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

}

int AddRecipient(MYSQL* conn, char* firstName, char* lastName, char* dateOfBirth, char* userID) {

}

int AddCategory(MYSQL* conn, char* name) {

}

int AddLocation(MYSQL* conn, char* name, char* webAddress, char* physicalLocation) {

}

int AddUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber) {

}