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

#endif // CONSTANTS_TYPES_H
