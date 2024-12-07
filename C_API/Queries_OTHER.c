#include "Queries_OTHER.h"
#pragma warning(disable: 4996)


int ItemExists(MYSQL* conn, char* tableName, char* itemID) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT * FROM `%s` WHERE %sID = %s",
		tableName, tableName, itemID);


	if (mysql_query(conn, query) != 0) {
		char functionName[QUERY_BUFFER];
		sprintf(functionName, "ItemExists(Table::%s, ID::%s)", tableName, itemID);

		PrintSQLError(conn, functionName);
		return QUERY_FAILURE;
	}

	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL) {
		char functionName[QUERY_BUFFER];
		sprintf(functionName, "ItemExists(Table::%s, ID::%s)", tableName, itemID);
		PrintSQLError(conn, functionName);
		return QUERY_FAILURE;
	}

	if (mysql_num_rows(result) == 0) {
		free(result);
		return NO_RESULT;
	}

	free(result);
	return SUCCESS;
}

int UserLogin(MYSQL* conn, char* username, char* password) {
	char query[200];
	sprintf(query,
		"SELECT userID FROM `user` WHERE username = '%s' AND `password` = '%s';",
		username, password);

	if (mysql_query(conn, query) != 0) {
		PrintSQLError(conn, "UserLogin()");
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

	free(result);

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


int IsUniversal(MYSQL* conn, char* tableName, char* itemID) {
	char query[QUERY_BUFFER];
	sprintf(query,
		"SELECT * "
		"FROM `%s` "
		"WHERE %sID = %s AND Universal = 1;",
		tableName, tableName, itemID);
	if (mysql_query(conn, query) != 0)
	{
		char functionName[QUERY_BUFFER];
		sprintf(functionName, "IsUniversal(Table::%s, ID::%s)", tableName, itemID);
		PrintSQLError(conn, functionName);
		return QUERY_FAILURE;
	}

	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL) {
		char functionName[QUERY_BUFFER];
		sprintf(functionName, "IsUniversal(Table::%s, ID::%s)", tableName, itemID);
		PrintSQLError(conn, functionName);
		return QUERY_FAILURE;
	}


	if (mysql_num_rows(result) == 0) {
		free(result);
		return NO_RESULT;
	}


	free(result);
	return SUCCESS;
}





