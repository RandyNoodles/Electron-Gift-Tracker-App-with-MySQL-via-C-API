#include "Queries.h"
#pragma warning(disable: 4996)

void PrintSQLError(MYSQL* conn, const char* functionName) {
	fprintf(stderr, "%s failed|Error: %u: %s",
		functionName, mysql_errno(conn), mysql_error(conn));
}

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

int NewUser(MYSQL* conn, char* username, char* password,
	char* firstName, char* lastName, char* email, char* phoneNumber) {




}




int ResultToJSON(MYSQL_RES* result, char* jsonBuffer) {
	if (result == NULL) {
		strcpy(jsonBuffer, "[]");
		return JSON_FAILURE;
	}

	if (mysql_num_rows(result) == 0) {
		strcpy(jsonBuffer, "[]");
		return NO_RESULT;
	}

	MYSQL_ROW row;
	MYSQL_FIELD* fields = mysql_fetch_field(result);
	int columnCount = mysql_num_fields(result);
	
	//start of JSON array
	strcpy(jsonBuffer, "[\n");

	int rowCount = 0;
	while ((row = mysql_fetch_rows(result)) != NULL) {
		//Append commas between each row
		if (rowCount > 0) {
			strcat(jsonBuffer, ",\n");
		}
		strcat(jsonBuffer, " {\n");

		for (int i = 0; i < columnCount; i++){
			char field[256];
			
			//Print line in format:  "<fieldName>": "<value||null>"<comma(EXCEPT last row.)>
			sprintf(field, "\"%s\": \"%s\"%s\n",
				fields[i].name,
				row[i] ? row[i] : "null",
				i < (columnCount - 1) ? "," : "");
			strcat(jsonBuffer, field);
		}

		strcat(jsonBuffer, "  }");
		rowCount++;
	}

	strcat(jsonBuffer, "\n]");
	return SUCCESS;
}