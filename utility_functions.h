#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H
#include "includes.h"
#include "constants_types.h"


// Utility function to split the string by delimiter
inline std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    size_t start = 0, end = 0;
    std::vector<std::string> result;

    while ((end = s.find(delimiter, start)) != std::string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
    }
    result.push_back(s.substr(start));

    return result;
}

inline std::string createTaskString_Plan(Task task){
    return task.taskName + " |TASK| " + task.tag + " |TAG| " + task.dueDate + " |DUEDATE| " + task.status + " |STATUS| " + std::to_string(task.priority) + " |PRIORITY| " + task.id + " |ID| ";
}

inline std::string createTaskString_History(Task task, std::string dateCompleted, int points){
    return task.taskName + " |TASK| " + task.tag + " |TAG| " + task.dueDate + " |DUEDATE| " + task.status + " |STATUS| " + std::to_string(task.priority) + " |PRIORITY| " + task.id + " |ID| " + dateCompleted + " |DATECOMPLETED| " + std::to_string(points) + " |POINTS| ";
}


// For parsing the task string
inline std::string getTask(std::string task) {
    return split(task, " |TASK| ")[0];
}

inline std::string getTag(std::string task) {
    std::vector<std::string> parts = split(task, " |TAG| ");
    return parts.size() > 1 ? split(parts[0], " |TASK| ")[1] : "";
}

inline std::string getDueDate(std::string task) {
    std::vector<std::string> parts = split(task, " |DUEDATE| ");
    return parts.size() > 1 ? split(parts[0], " |TAG| ")[1] : "";
}

inline std::string getStatus(std::string task) {
    std::vector<std::string> parts = split(task, " |STATUS| ");
    return parts.size() > 1 ? split(parts[0], " |DUEDATE| ")[1] : "";
}

inline std::string getPriority(std::string task) {
    std::vector<std::string> parts = split(task, " |PRIORITY| ");
    return parts.size() > 1 ? split(parts[0], " |STATUS| ")[1] : "";
}

inline std::string getID(std::string task) {
    std::vector<std::string> parts = split(task, " |ID| ");
    return parts.size() > 1 ? split(parts[0], " |PRIORITY| ")[1] : "";
}

inline std::string getDateCompleted(std::string task) {
    std::vector<std::string> parts = split(task, " |DATECOMPLETED| ");
    return parts.size() > 1 ? split(parts[0], " |ID| ")[1] : "";
}

inline std::string getPoints(std::string task) {
    std::vector<std::string> parts = split(task, " |POINTS| ");
    return parts.size() > 1 ? split(parts[0], " |DATECOMPLETED| ")[1] : "";
}



inline Task createTaskFromString(std::string task_string){
    Task task;
    task.taskName = getTask(task_string);
    task.dueDate = getDueDate(task_string);
    task.id = getID(task_string);
    std::cout << "id:" << task_string << "here" << std::endl;
    task.priority = atoi(getPriority(task_string).c_str());
    task.status = getStatus(task_string);
    task.tag = getTag(task_string);

    return task;
}

// ----------------------------

// Additional utility functions
inline std::string getCurrentDate(){
    auto now = std::chrono::system_clock::now();

    // Convert to time_t which represents calendar time
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Convert to tm struct for formatting
    std::tm now_tm = *std::localtime(&now_time);

    // Use stringstream to format date
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d"); // Format: YYYY-MM-DD

    return oss.str();
}

inline std::string getSaveFilePath() {
    std::string homeDir;
    std::string appDirName = "/FocusApp/"; // Name of your app's directory

#if defined(_WIN32) || defined(_WIN64)
    // Windows: Use USERPROFILE as home directory
    char* userProfile = std::getenv("USERPROFILE");
    if (userProfile) {
        homeDir = userProfile;
    }
#else
    // macOS and other Unix-like systems: Use HOME as home directory
    char* home = std::getenv("HOME");
    if (home) {
        homeDir = home;
    }
#endif

    // Construct the full path for the app directory
    std::string appDirPath = homeDir + appDirName;

    // Use std::filesystem to create the directory if it doesn't exist
    std::filesystem::path dirPath(appDirPath);
    std::filesystem::create_directories(dirPath);

    // Construct the full path for the save file within the app directory
    std::string saveFilePath = appDirPath + "save_file.json";

    return saveFilePath;
}

#endif // UTILITY_FUNCTIONS_H
