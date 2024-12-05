#include "Queries_GET.h"
#pragma warning(disable: 4996)



MYSQL_RES* GetGifts(MYSQL* conn, int userId) {

	char query[500];
	sprintf(query,
		"SELECT g.`name`, g.cost,  s.`status` AS `status`, CONCAT(r.firstName, r.lastName) AS 'recipient' "
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
		PrintSQLError(conn, "mysql_query");
		return;
	}

	//Grab the results
	return mysql_store_result(conn);
}

MYSQL_RES* GetRecipients(MYSQL* conn, int userId) {
	char query[256];
	sprintf(query,
		"SELECT * FROM gift WHERE user_id = %d AND rental_date >= '%s' AND return_date <= '%s';",
		userId);

	//Send query
	if (mysql_query(conn, query) != 0)
	{
		PrintSQLError(conn, "mysql_query");
		return;
	}
	//Grab the results
	MYSQL_RES* result = mysql_store_result(conn);
}