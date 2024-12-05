#include "Queries_OTHER.h"
#pragma warning(disable: 4996)


int UserLogin(MYSQL* conn, char* username, char* password) {
	char query[200];
	sprintf(query,
		"SELECT userID FROM `user` WHERE username = '%s' AND `password` = '%s';",
		username, password);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "mysql_query");
		return QUERY_FAILURE;
	}


	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL) {
		return QUERY_FAILURE;
	}

	MYSQL_ROW row;
	int rowCount = 0;
	char stringId[100];

	while ((row = mysql_fetch_row(result)) != NULL) {
		for (int i = 0; i < 1; i++) {
			rowCount++;
			strcpy(stringId, row[i] ? row[i] : "null");
		}
	}

	if (rowCount == 0) {
		return NO_RESULT;
	}
	if (rowCount > 1) {
		fprintf(stderr, "Multiple rows found with matching userID and password");
		return QUERY_FAILURE;
	}
	
	int userId;
	if (ParseInt(stringId, &userId) != SUCCESS) {
		return QUERY_FAILURE;
	}

	return userId;
}






