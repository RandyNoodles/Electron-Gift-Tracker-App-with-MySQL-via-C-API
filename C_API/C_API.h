#pragma once

#include "Queries_ADD.h"
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
    DELETE_CATEGORY = 403,
    DELETE_LOCATION = 404,
    DELETE_USER = 405
} CommandEnum;