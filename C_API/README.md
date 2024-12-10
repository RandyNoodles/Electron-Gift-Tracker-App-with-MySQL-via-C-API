# API USAGE

## ARGLIST

NOTE: argv[0] is set automatically when C_API.exe is called.
In the context of Javascript and args[] it DOES NOT EXIST.

| Argv[x]	| Usage					|
|---------	|-----------------------|
| 0			| Program name			|
| 1			| CommandEnum			|
| 2 -> 9	| Query-specific args	| 

## NULL args
Pass the string 'null' in the event of a null arg.

In javascript, the value *null* will convert to this automatically when calling C_API.exe.

## CommandEnums & Arglists

| CommandEnum       | Value | Argv[2] -> Argv[9]                            |
|-------------------|-------|-----------------------------------------------|
| TEST              | -2    | ???                                           |
| INVALID           | -1    | ???                                           |
| USER_LOGIN        | 0     | username, password                            |
|					|		|												|
| GET_GIFTS         | 100   | userID                                        |
| GET_EVENTS        | 101   | userID                                        |
| GET_RECIPIENTS    | 102   | userID                                        |
| GET_STATUSES      | 103   | userID (not needed, but it simplifies logic)	|
| GET_CATEGORIES    | 104   | userID                                        |
| GET_LOCATIONS     | 105   | userID                                        |
| GET_USER			| 106	| userID										|
|					|		|												|
| ADD_GIFT          | 200   | name, cost, statusID, recipientID, eventID, locationID |
| ADD_EVENT         | 201   | name, userID, date, categoryID                |
| ADD_RECIPIENT     | 202   | firstName, lastName, dateOfBirth              |
| ADD_CATEGORY      | 203   | name                                          |
| ADD_LOCATION      | 204   | name, address                                 |
| ADD_USER          | 205   | username, password, firstName, lastName, email, phone# |
|					|		|												|
| UPDATE_GIFT       | 300   | giftID, name, cost, statusID, recipientID, eventID, locationID |
| UPDATE_EVENT      | 301   | eventID, name, date, categoryID               |
| UPDATE_RECIPIENT  | 302   | recipientID, firstName, lastName, dateOfBirth, userID      |
| UPDATE_CATEGORY   | 303   | categoryID, name                              |
| UPDATE_LOCATION   | 304   | locationID, name, address                     |
|					|		|												|
| DELETE_GIFT       | 400   | giftID                                        |
| DELETE_EVENT      | 401   | eventID                                       |
| DELETE_RECIPIENT  | 402   | recipientID                                   |
| DELETE_CATEGORY   | 404   | categoryID                                    |
| DELETE_LOCATION   | 405   | locationID                                    |
| DELETE_USER       | 406   | userID                                        |


## Return Values

| CommandEnum		| OnSuccess			| OnFailure		|
|---------------	|---------------	|---------------|
| TEST				| ???				| ???			|
| INVALID_COMMAND	| <N/a>				| stderr string |
| USER_LOGIN		| { UserID: %d }	| stderr string |
| GET				| JsonArray			| stderr string |
| Add				| {AddedItemID: %d}	| stderr string |
| UPDATE		    | stdout string		| stderr string |
| DELETE			| stdout string		| stderr string |