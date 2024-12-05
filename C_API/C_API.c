#include "C_API.h"


int main(int argc, char* argv[]) {
	const char* server = "localhost";
	const char* username = "root";
	const char* password = "root";
	const char* defaultDatabase = "gifttracker";
    
    printf("ArgC = %d", argc);


    //Check for ZERO args
	if (argc <= 1) {
		fprintf(stderr, "Invalid args. At minimum <commandEnum> is required.");
		return EXIT_FAILURE;
	}
    //Ensure ARG[1] is an INT
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

//-----------------------------------------------------------------------------------------------------------------
    //MAIN SWITCH

    //Everything past here MUST:
        //NOT return an exit code (done at the end.)
        //Write SUCCESSFUL results to stdout -> use printf("")
        //Write FAILED results to stderr     -> use fprintf(stderr, "")
        //free any dynamically allocated memory (MYSQL_RES, jsonBuffers, etc..)


    if (command == USER_LOGIN) {
        if (argc != 4) {
            fprintf(stderr, "Invalid number of arguments for USER_LOGIN command.");
        }

        int userId = QUERY_FAILURE;
        userId = UserLogin(conn, argv[2], argv[3]);
        printf("{userID: %d}", userId);
    }
    ///////////////
    //GET COMMANDS
    else if (command >= 100 && command < 200) {
        if (argc != 3) {
            fprintf(stderr, "Invalid command count. All GET commands require <arg[1]: Command> <arg[2]: UserID>");
            return EXIT_FAILURE;
        }
        int userID = -1;
        if (ParseInt(argv[2], &userID) != SUCCESS) {
            fprintf(stderr, "Unable to parse int from user id: %s", argv[2]);
            return EXIT_FAILURE;
        }

        MYSQL_RES* queryResult = NULL;
        switch (command) {
            case GET_GIFTS:
                queryResult = GetGifts(conn, userID);
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
                fprintf(stderr, "Unrecognized command from the GET family. [%d]", command);
        }
        
        //Handle results of the GET query
        if (queryResult == NULL) {
            (conn, "SQL result == NULL: ");
            return EXIT_FAILURE;
        }
        
        //If empty, send blank array.
        if (mysql_num_rows(queryResult) == 0) {
            printf("[]");
            return SUCCESS;
        }        
        //Else, convert result to JSON and print to stdout
        char* jsonBuffer = (char*)malloc(JSON_BUFFER);
        if (jsonBuffer == NULL) {
            fprintf(stderr, "json buffer failed to allocate.");
            return EXIT_FAILURE;
        }
        else {
            if (ResultToJSON(queryResult, jsonBuffer) == SUCCESS) {
                printf(jsonBuffer);
            }
            else {
                fprintf(stderr, "Failure parsing query results to JSON.");
            }

            if (result != NULL) {
                free(result);
            }
            free(jsonBuffer);
            //Success.
        }

    }

    ///////////////
    //ADD COMMANDS
    else if (command >= 200 && command < 300) {

        int addedItemID = QUERY_FAILURE;

        switch (command) {
        case ADD_GIFT:
            //name, cost, statusID, recipientID, eventID, locationID
            if (argc != 8) {
                fprintf(stderr, "Invalid arg count for ADD_GIFT command.");
            }
            else {
                addedItemID = AddGift(conn, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
            }
            break;
        case ADD_EVENT:
            //name, date, categoryID, userID
            if (argc != 6) {
                fprintf(stderr, "Invalid arg count for ADD_EVENT command.");
            }
            else {
                addedItemID = AddEvent(conn, argv[2], argv[3], argv[4], argv[5]);
            }
            break;
        case ADD_RECIPIENT:
            //FirstName, lastName, DOB, userID
            if (argc != 6) {
                fprintf(stderr, "Invalid arg count for ADD_RECIPIENT command.");
            }
            else {
                addedItemID = AddRecipient(conn, argv[2], argv[3], argv[4], argv[5]);
            }
            break;
        case ADD_CATEGORY:
            //Does this need to be associated with the user?
            // Or maybe we just make it locked down.           
            //name
            if (argc != 3) {
                fprintf(stderr, "Invalid arg count for ADD_CATEGORY command.");
            }
            else {
                addedItemID = AddCategory(conn, argv[2]);
            }
            break;
        case ADD_LOCATION:
            //name, webAddress, physicalLocation
            if (argc != 5) {
                fprintf(stderr, "Invalid arg count for ADD_LOCATION command.");
            }
            else {
                addedItemID = AddLocation(conn, argv[2], argv[3], argv[4]);
            }
            break;
        case ADD_USER:
            //username, password, firstname, lastname, email, phone#
            if (argc != 8) {
                fprintf(stderr, "Invalid arg count for ADD_USER command.");
            }
            else {
                addedItemID = AddUser(conn, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
            }
            break;
        default:
            fprintf(stderr, "Unrecognized ADD command: %d", command);
            break;
        }

        if (addedItemID != QUERY_FAILURE) {
            printf("{ AddedItemID: %d }", addedItemID);
        }
        //Success.
    }

    //////////////////
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

    //////////////////
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
    }
    
    mysql_close(conn);

	return 0;
}



