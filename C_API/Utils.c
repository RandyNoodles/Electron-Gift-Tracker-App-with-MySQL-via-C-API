#include "Utils.h"
#pragma warning(disable: 4996)

int IsUDouble(char* arg) {
	double temp;

	char validChars[] = ".0123456789\0";

	//Make sure we can scanf it.
	if (sscanf(arg, "%lf", &temp) != 1) {
		return INVALID_ARG;
	}

	//Loop through and make sure there's no extra non-numeric chars.
	bool valid = false;
	for (int i = 0; i < strlen(arg); i++) {
		for (int k = 0; k < strlen(validChars); k++) {
			if (arg[i] == validChars[k]) {
				valid = true;
				break;
			}
		}

		if (!valid) {
			return INVALID_ARG;
		}
		valid = false;
	}
	return SUCCESS;
}

int IsUInt(char* arg) {
	int result;
	int temp;
	
	result = ParseInt(arg, &temp);
	if (result != SUCCESS) {
		return INVALID_ARG;
	}
	if (temp < 0) {
		return INVALID_ARG;
	}
	return SUCCESS;

}
int IsNull(char* arg) {

	char targetValue[] = "null";

	for (int i = 0; i < strlen(arg); i++) {
		arg[i] = tolower(arg[i]);
		if (arg[i] != targetValue[i]) {
			return INVALID_ARG;
		}
	}
	return SUCCESS;
}


void PrintSQLError(MYSQL* conn, const char* functionName) {
	fprintf(stderr, "%s failed|Error: %u: %s",
		functionName, mysql_errno(conn), mysql_error(conn));
}

//Check arg list?

int ParseInt(char* arg, int* rValue) {

    //Points to first char after int parsed
    char* endPtr;
    //Try to parse int
    int temp = strtol(arg, &endPtr, 10);

    //Check first char after int was end of string
    if (*endPtr != '\n' && *endPtr != '\0') {
        return INVALID_ARG; //Input was not a valid integer
    }

    //Success
    *rValue = temp;
    return SUCCESS;
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
	while ((row = mysql_fetch_row(result)) != NULL) {
		//Append commas between each row
		if (rowCount > 0) {
			strcat(jsonBuffer, ",\n");
		}
		strcat(jsonBuffer, " {\n");

		for (int i = 0; i < columnCount; i++) {
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