#include "Queries.h"

typedef enum {
	TEST = -2,
	INVALID = -1,

	USER_LOGIN = 0,

	GET_GIFTS = 100,
	GET_EVENTS = 101,
	GET_RECIPIENTS = 102,
	GET_STATUSES = 103,
	GET_CATEGORIES = 104,
	GET_LOCATIONS = 105,

	ADD_GIFT = 200,
	ADD_EVENT = 201,
	ADD_RECIPIENT = 202,
	ADD_CATEGORY = 203,
	ADD_LOCATION = 204,
	ADD_USER = 205,

	UPDATE_GIFT = 300,
	UPDATE_EVENT = 301,
	UPDATE_RECIPIENT = 302,
	UPDATE_CATEGORY = 303,
	UPDATE_LOCATION = 304,

	DELETE_GIFT = 400,
	DELETE_EVENT = 401,
	DELETE_RECIPIENT = 402,
	DELETE_STATUS = 403,
	DELETE_CATEGORY = 404,
	DELETE_LOCATION = 405,
	DELETE_USER = 406
} CommandEnum;

int main(int argc, char* argv[]) {
	const char* server = "localhost";
	const char* username = "root";
	const char* password = "root";
	const char* defaultDatabase = "gifttracker";

	if (argc <= 1) {
		fprintf(stderr, "Invalid args. At minimum <commandEnum> is required.");
		return EXIT_FAILURE;
	}

    //Check for command - REQUIRED!
	CommandEnum command = INVALID;
	int result = ParseInt(argv[1], &command);
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


    //MAIN SWITCH
    if (command == USER_LOGIN) {
        if (argc < 3 || argc > 4) {
            fprintf(stderr, "Invalid number of arguments for USER_LOGIN command. Requires <arg[2]:UserName> <arg[3]:Password>");
            return EXIT_FAILURE;
        }
        int userId = QUERY_FAILURE;
        userId = UserLogin(conn, argv[2], argv[3]);
        printf("{userID: %d}", userId);
    }
    ///TESTING

    if (command == TEST) {
        fprintf(stderr, "Error log here");
        printf("This will be ignored.");
        return EXIT_FAILURE;
    }



    ///END TESTING




    //GET COMMANDS
    else if (command >= 100 && command < 200) {
        

        if (argc != 3) {
            fprintf(stderr, "Invalid command count. All GET commands require <arg[1]: Command> <arg[2]: UserID>");
            return EXIT_FAILURE;
        }
        
        
        switch (command) {
        case GET_GIFTS:
            // Handle GET_GIFTS
            break;
        case GET_EVENTS:
            // Handle GET_EVENTS
            break;
        case GET_RECIPIENTS:
            // Handle GET_RECIPIENTS
            break;
        case GET_STATUSES:
            // Handle GET_STATUSES
            break;
        case GET_CATEGORIES:
            // Handle GET_CATEGORIES
            break;
        case GET_LOCATIONS:
            // Handle GET_LOCATIONS
            break;
        default:
            // Handle unknown GET command
            break;
        }
    }

    //ADD COMMANDS
    else if (command >= 200 && command < 300) {
        switch (command) {
        case ADD_GIFT:
            // Handle ADD_GIFT
            break;
        case ADD_EVENT:
            // Handle ADD_EVENT
            break;
        case ADD_RECIPIENT:
            // Handle ADD_RECIPIENT
            break;
        case ADD_CATEGORY:
            // Handle ADD_CATEGORY
            break;
        case ADD_LOCATION:
            // Handle ADD_LOCATION
            break;
        case ADD_USER:
            // Handle ADD_USER
            break;
        default:
            // Handle unknown ADD command
            break;
        }
    }

    //UPDATE COMMANDS
    else if (command >= 300 && command < 400) {
        switch (command) {
        case UPDATE_GIFT:
            // Handle UPDATE_GIFT
            break;
        case UPDATE_EVENT:
            // Handle UPDATE_EVENT
            break;
        case UPDATE_RECIPIENT:
            // Handle UPDATE_RECIPIENT
            break;
        case UPDATE_CATEGORY:
            // Handle UPDATE_CATEGORY
            break;
        case UPDATE_LOCATION:
            // Handle UPDATE_LOCATION
            break;
        default:
            // Handle unknown UPDATE command
            break;
        }
    }

    //DELETE COMMANDS
    else if (command >= 400 && command < 500) {
        switch (command) {
        case DELETE_GIFT:
            // Handle DELETE_GIFT
            break;
        case DELETE_EVENT:
            // Handle DELETE_EVENT
            break;
        case DELETE_RECIPIENT:
            // Handle DELETE_RECIPIENT
            break;
        case DELETE_STATUS:
            // Handle DELETE_STATUS
            break;
        case DELETE_CATEGORY:
            // Handle DELETE_CATEGORY
            break;
        case DELETE_LOCATION:
            // Handle DELETE_LOCATION
            break;
        case DELETE_USER:
            // Handle DELETE_USER
            break;
        default:
            // Handle unknown DELETE command
            break;
        }
    }
    else {
        fprintf(stderr, "Command not recognized.");
        return EXIT_FAILURE;
    }





	return 0;
}



