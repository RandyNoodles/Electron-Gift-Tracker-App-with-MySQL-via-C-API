#include "Queries.h"


typedef enum {
	INVALID = -1,
	USER_LOGIN = 0,
	NEW_USER = 1,
	GET_GIFT_LIST = 2,
	ADD_GIFT = 3,
	UPDATE_GIFT = 4,
	DELETE_GIFT = 5
} CommandEnum;


int main(int argc, char* args[]) {
	const char* server = "localhost";
	const char* username = "root";
	const char* password = "root";
	const char* defaultDatabase = "gifttracker";

	if (argc <= 1) {
		fprintf(stderr, "Invalid args. At minimum <commandEnum> is required.");
		return EXIT_FAILURE;
	}

	CommandEnum command = INVALID;
	int result = ParseInt(args[1], &command);
	if (result != SUCCESS) {
		fprintf(stderr, "Failed to parse valid integer from <CommandEnum> at arg[1].");
		return EXIT_FAILURE;
	}


	//DATABASE CONNECT & INIT
	MYSQL* conn = mysql_init(NULL);

	if (conn == NULL) {
		fprintf(stderr, "MySql_init failed to connect.");
		return EXIT_FAILURE;
	}

	if (!mysql_real_connect(conn, server, username, password, defaultDatabase, 3306, NULL, 0)) {
		fprintf(stderr, "mysql_real_connect failed to connect to the MySQL Server.");
		return EXIT_FAILURE;
	}

	int userId;
	//MAIN SWITCH
	switch (command) {
//User Login
	//2 args
	//username, password
//Return: userID/-1 for QUERY_FAILURE, -2 for NO_RESULT
	case USER_LOGIN:
		if (argc < 3 || argc > 4) {
			fprintf(stderr, "Invalid number of arguments for USER_LOGIN command. Requires <arg[2]:UserName> <arg[3]:Password>");
			return EXIT_FAILURE;
		}
		userId = QUERY_FAILURE;
		userId = UserLogin(conn, args[2], args[3]);

		printf("{userID: %d}", userId);
		break;
//2 Args
//Username, password, firstname, lastname, email, phone#
//Return: 0 for success, else error.
	case NEW_USER:
		if (argc < 6 || argc > 7) {
			fprintf(stderr, "Invalid number of args for NEW_USER command. Must be between 6-7 for all columns.");
		}
			
		break;


	case 3:
		if (result != SUCCESS) {
			fprintf(stderr, "Failed to parse UserID from args[2]");
			return EXIT_FAILURE;
		}
		break;



	}
	return 0;
}



