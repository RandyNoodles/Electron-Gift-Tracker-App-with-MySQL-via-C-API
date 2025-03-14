#include "Queries_GET.h"
#pragma warning(disable: 4996)


MYSQL_RES* GetGifts(MYSQL* conn, int userId) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT g.GiftID, g.`name`, g.cost,  s.`status` AS `status`, CONCAT(r.firstName, r.lastName) AS 'recipient', e.Name AS 'event' "
		"FROM gift g "
		"LEFT JOIN recipient r ON r.RecipientID = g.RecipientID "
		"LEFT JOIN `status` s ON s.StatusID = g.StatusID "
		"LEFT JOIN `event` e ON e.EventID = g.EventId "
		"WHERE g.UserID = %d "
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
		"FROM `event` e "
		"LEFT JOIN category c ON c.CategoryID = e.CategoryID "
		"WHERE e.UserID = %d;",
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
		"SELECT RecipientID, FirstName, LastName, DateOfBirth AS 'DOB' FROM recipient WHERE userID = %d;",
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

MYSQL_RES* GetPurchaseLocations(MYSQL* conn, int userID)
{
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT DISTINCT pl.PurchaseLocationID, pl.`Name`, pl.WebAddress, pl.PhysicalLocation "
		"FROM PurchaseLocation pl "
		"WHERE pl.Universal = 1 "
		"   OR pl.PurchaseLocationID IN ( "
		"       SELECT g.PurchaseLocationID "
		"       FROM Gift g "
		"       WHERE g.PurchaseLocationID IS NOT NULL AND EXISTS ( "
		"           SELECT 1 "
		"           FROM `Event` e "
		"           WHERE g.EventID = e.EventID AND e.UserID = %d "
		"       ) "
		");",
		userID);
	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetUser():");
		return NULL;
	}
	return mysql_store_result(conn);
}

MYSQL_RES* GetCategories(MYSQL* conn, int userID)
{
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT DISTINCT c.CategoryID, c.`Name` "
		"FROM Category c "
		"WHERE c.Universal = 1 "
		"   OR c.CategoryID IN ( "
		"       SELECT e.CategoryID "
		"       FROM `Event` e "
		"       WHERE e.UserID = %d "
		");",
		userID);

	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "GetCategories():");
		return NULL;
	}

	return mysql_store_result(conn);
}
