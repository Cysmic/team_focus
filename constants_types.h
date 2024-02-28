#ifndef CONSTANTS_TYPES_H
#define CONSTANTS_TYPES_H
#include "includes.h"

struct Task{
    std::string id;
    std::string taskName;
    std::string tag;
    std::string dueDate;
    std::string status;
    int priority;
};

enum Menu{
    API_M = 0,
    PLAN_M = 1,
    PROGRESS_M = 2,
    CONGRATS_M = 3,
    PLANGENERATION_M = 4
};

#endif // CONSTANTS_TYPES_H
