#include "Queries_GET.h"
#pragma warning(disable: 4996)



MYSQL_RES* GetGifts(MYSQL* conn, int userId) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT g.GiftID, g.`name`, g.cost,  s.`status` AS `status`, CONCAT(r.firstName, r.lastName) AS 'recipient' "
		"FROM gift g "
		"JOIN recipient r ON r.RecipientID = g.RecipientID "
		"JOIN `user` u ON u.UserID = r.UserID "
		"JOIN `status` s ON s.StatusID = g.StatusID "
		"WHERE u.UserID = %d "
		"ORDER BY s.StatusID;",
		userId);

	//Send query
	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetGifts():");
		return NULL;
	}

	//Grab the results
	return mysql_store_result(conn);
}

MYSQL_RES* GetEvents(MYSQL* conn, int userId) {
	char query[QUERY_BUFFER];
	//First grabs the event table filtered by ID, then resolves the Category IDs to Category Name.
	sprintf(query,
		"SELECT e.EventID, e.Name, e.Date, c.Name AS 'Category' "
		"FROM (SELECT * FROM `event` e2 WHERE e2.UserID = %d) AS e "
		"LEFT JOIN category c ON e.EventID = c.CategoryID;",
		userId);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetEvents():");
		return NULL;
	}

	return mysql_store_result(conn);
}
MYSQL_RES* GetRecipients(MYSQL* conn, int userId) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT FirstName, LastName, DateOfBirth AS 'DOB' FROM recipient WHERE userID = %d;",
		userId);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetRecipients():");
		return NULL;
	}

	return mysql_store_result(conn);
}

//NOTE: Statuses are global. No userID required.
MYSQL_RES* GetStatuses(MYSQL* conn, int userID) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT * FROM `status`;");
	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetStatuses():");
		return NULL;
	}
	return mysql_store_result(conn);
}




MYSQL_RES* GetUser(MYSQL* conn, int userID) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT * FROM `user` WHERE userID = %d",
		userID);
	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetUser():");
		return NULL;
	}
	return mysql_store_result(conn);
}