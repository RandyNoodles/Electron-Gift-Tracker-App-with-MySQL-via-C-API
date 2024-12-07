#include "Queries_DELETE.h"
#pragma warning(disable: 4996)


int DeleteGift(MYSQL* conn, int giftID) {

	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM gift WHERE GiftID = %d;",
		giftID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteGift(): ");
		return QUERY_FAILURE;
	}

	//Return # of affected rows.
	//1 = success
	//2 = maybe no matching ID?
	return mysql_affected_rows(conn);

}
int DeleteEvent(MYSQL* conn, int eventID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM event WHERE EventID = %d;",
		eventID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteEvent(): ");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}
int DeleteRecipient(MYSQL* conn, int recipientID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM recipient WHERE RecipientID = %d;",
		recipientID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteRecipient(): ");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}
int DeleteCategory(MYSQL* conn, int categoryID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM category WHERE CategoryID = %d;",
		categoryID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteCategory(): ");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}
int DeleteLocation(MYSQL* conn, int locationID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM purchaseLocation WHERE PurchaseLocationID = %d;",
		locationID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteLocation(): ");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}
int DeleteUser(MYSQL* conn, int userID) {
	char query[QUERY_BUFFER];

	sprintf(query,
		"DELETE FROM user WHERE UserID = %d;",
		userID);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "DeleteUser(): ");
		return QUERY_FAILURE;
	}

	return mysql_affected_rows(conn);
}