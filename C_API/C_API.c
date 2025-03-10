#include "C_API.h"


int main(int argc, char* argv[]) {
	const char* server = "localhost";
	const char* username = "root";
	const char* password = "root";
	const char* defaultDatabase = "gifttracker";


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
        printf("{\"userID\": % d }", userId);
    }
    ///////////////
    //GET COMMANDS
    //
    //1. Validate arg count
    //2. Parse User ID
    //3.  -> Call GET function
    //4. If successful, allocate JSON buffer
    //5. Convert result to JSON
    //6. Print JSON result

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
                queryResult = GetEvents(conn, userID);
                break;
            case GET_RECIPIENTS:
                queryResult = GetRecipients(conn, userID);
                break;
            case GET_STATUSES:
                queryResult = GetStatuses(conn, userID);
                break;
            case GET_CATEGORIES:
                queryResult = GetCategories(conn, userID);
                break;
            case GET_LOCATIONS:
                queryResult = GetPurchaseLocations(conn, userID);
                break;
            case GET_USER:
                queryResult = GetUser(conn, userID);
                break;
            default:
                fprintf(stderr, "Unrecognized command from the GET family. [%d]", command);
        }
        
        //Handle results of the GET query
        if (queryResult == NULL) {
            PrintSQLError(conn, "SQL result == NULL: ");
            return EXIT_FAILURE;
        }
        //Else, convert result to JSON and print to stdout
        char* jsonBuffer = (char*)malloc(JSON_BUFFER);
        if (jsonBuffer == NULL) {
            fprintf(stderr, "json buffer failed to allocate.");
            return EXIT_FAILURE;
        }
        else {
            int jsonStatus = ResultToJSON(queryResult, jsonBuffer);
            if (jsonStatus != JSON_FAILURE) {
                printf(jsonBuffer);
            }
            else {
                fprintf(stderr, "Failure parsing query results to JSON.");
            }

            free(jsonBuffer);
            //Success.
        }

    }

    ///////////////
    //ADD COMMANDS
    //
    //1. Branch to command
    //2. Validate arg count for that command
    //3. -> Call add function
    //4. If successful, print {AddedItemID: <itemId>}
    else if (command >= 200 && command < 300) {

        int addedItemID = QUERY_FAILURE;

        switch (command) {
        case ADD_GIFT:
            //name, cost, statusID, recipientID, eventID, locationID
            if (argc != 9) {
                fprintf(stderr, "Invalid arg count for ADD_GIFT command.");
            }
            else {
                addedItemID = AddGift(conn, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
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
            printf("{ \"AddedItemID\": %d }", addedItemID);
        }
        //Success.
    }

    //////////////////
    //UPDATE COMMANDS
    //
    //1. Branch to command
    //2. Validate arg count for that command
    //3. -> Call Update function
    //4. If successful printf {UpdatedItemID: <itemID>}
    else if (command >= 300 && command < 400) {
        
        int updateRowsAffected = QUERY_FAILURE;

        switch (command) {
            case UPDATE_GIFT:
                if (argc != 9) {
                    fprintf(stderr, "Invalid arg count for UPDATE_GIFT command.");
                }
                else {
                    updateRowsAffected = UpdateGift(conn, argv[2], argv[3], argv[4],
                        argv[5], argv[6], argv[7], argv[8]);
                }
                break;
            case UPDATE_EVENT:
                if (argc != 7) {
                    fprintf(stderr, "Invalid arg count for UPDATE_EVENT command.");
                }
                else {
                    updateRowsAffected = UpdateEvent(conn, argv[2], argv[3], argv[4],
                        argv[5], argv[6]);
                }
                break;
            case UPDATE_RECIPIENT:
                if (argc != 7) {
                    fprintf(stderr, "Invalid arg count for UPDATE_RECIPIENT command.");
                }
                else {
                    updateRowsAffected = UpdateRecipient(conn, argv[2], argv[3], argv[4],
                        argv[5], argv[6]);
                }
                break;
            case UPDATE_CATEGORY:
                if (argc != 4) {
                    fprintf(stderr, "Invalid arg count for UPDATE_CATEGORY command.");
                }
                else {
                    updateRowsAffected = UpdateCategory(conn, argv[2], argv[3]);
                }
                break;
            case UPDATE_LOCATION:
                if (argc != 6) {
                    fprintf(stderr, "Invalid arg count for UPDATE_LOCATION command.");
                }
                else {
                    updateRowsAffected = UpdateLocation(conn, argv[2], argv[3], argv[4], argv[5]);
                }
                break;
            case UPDATE_USER:
                if (argc != 8) {
                    fprintf(stderr, "Invalid arg count for UPDATE_USER command.");
                }
                else {
                    updateRowsAffected = UpdateUser(conn, argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
                }
            default:
                fprintf(stderr, "Unrecognized UPDATE command: %d", command);
                break;
        }
        if (updateRowsAffected != QUERY_FAILURE) {
            printf("{\"RowsAffected\": %d}", updateRowsAffected);
        }
    }

    //////////////////
    //DELETE COMMANDS
    //
    //1. Validate arg count
    //2. Parse item ID
    //3. -> Call Update function
    //4. If successful printf {UpdatedItemID: <itemID>}
    else if (command >= 400 && command < 500) {

        int deletionRowsAffected = QUERY_FAILURE;
        int idToDelete = -1;


        if (argc != 3) {
            fprintf(stderr, "Invalid Arg count for DELETE functions.");
            command = INVALID;
        }

        if (ParseInt(argv[2], &idToDelete) != SUCCESS) {
            fprintf(stderr, "Unable to parse ID for item to delete.");
            command = INVALID;
        }

        switch (command) {
        case DELETE_GIFT:
            deletionRowsAffected = DeleteGift(conn, idToDelete);
            break;
        case DELETE_EVENT:
            deletionRowsAffected = DeleteEvent(conn, idToDelete);
            break;
        case DELETE_RECIPIENT:
            deletionRowsAffected = DeleteRecipient(conn, idToDelete);
            break;
        case DELETE_CATEGORY:
            deletionRowsAffected = DeleteCategory(conn, idToDelete);
            break;
        case DELETE_LOCATION:
            deletionRowsAffected = DeleteLocation(conn, idToDelete);
            break;
        case DELETE_USER:
            deletionRowsAffected = DeleteUser(conn, idToDelete);
            break;
        default:
            fprintf(stderr, "Unrecognized DELETE command: %d", command);
            break;
        }

        if (deletionRowsAffected > 0) {
            printf("Deletion successful.");
        }

    }
    else {
        fprintf(stderr, "Command %d not recognized.", command);
    }
    
    mysql_close(conn);

	return 0;
}