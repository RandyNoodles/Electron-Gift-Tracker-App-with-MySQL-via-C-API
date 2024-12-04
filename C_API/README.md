# API USAGE

## NULL args
Pass -1 in the event of a null arg.

## Command Arg
When calling C_API.exe, arg1 is always the command, an int indicating the operation to complete.

Priority:
- Login
- Get gift list
- Add new gift
  - Get recipients (for the dropdown)
- Delete gift


| Command Name       | Value | ArgList                                       |
|--------------------|-------|-----------------------------------------------|
| INVALID            | -1    | ???                                           |
| USER_LOGIN         | 0     | username, password                            |
| GET_GIFTS          | 1     | userID                                        |
| GET_RECIPIENTS     | 2     | userID                                        |
| GET_STATUSES       | 3     | userID                                        |
| GET_EVENTS         | 4     | userID                                        |
| GET_CATEGORIES     | 5     | userID                                        |
| GET_LOCATIONS      | 6     | userID                                        |
| ADD_USER           | 7     | username, password, firstName, lastName, email, phone# |
| ADD_GIFT           | 8     | name, cost, statusID, recipientID, eventID, locationID |
| ADD_EVENT          | 9     | name, userID                                          |
| ADD_EVENTCATEGORY  | 10    | name                                          |
| ADD_LOCATION       | 11    | name, address                                 |
| ADD_RECIPIENT      | 12    | firstName, lastName, dateOfBirth              |
| UPDATE_GIFT        | 13    | giftID, name, cost, statusID, recipientID, eventID, locationID |
| UPDATE_EVENT       | 14    | eventID, name                                 |
| UPDATE_CATEGORY    | 15    | categoryID, name                              |
| UPDATE_LOCATION    | 16    | locationID, name, address                     |
| UPDATE_RECIPIENT   | 17    | recipientID, firstName, lastName              |
| DELETE_USER        | 18    | userID                                        |
| DELETE_GIFT        | 19    | giftID                                        |
| DELETE_RECIPIENT   | 20    | recipientID                                   |
| DELETE_STATUS      | 21    | statusID                                      |
| DELETE_EVENT       | 22    | eventID                                       |
| DELETE_CATEGORY    | 23    | categoryID                                    |
| DELETE_LOCATION    | 24    | locationID                                    |