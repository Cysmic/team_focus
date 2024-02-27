#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "includes.h"
#include "utility_functions.h"
#include "notionmanager.h"

class DataManager : public QObject
{
    Q_OBJECT
private:
    std::vector<Task> tasks;
    // for the sake of speeed I will define tasks to be of this format:
    // task |;;| date created |;;;| date completed |;;;;| points awarded |;;;;;| priority level |;;;;;;|
    // we will use nlohmann/json library for serialization/deserialization of the map above
    std::vector<std::string> plan;
    std::vector<std::string> history;

    std::string API_KEY;
    std::string DATABASE;

    NotionManager *notionManager;
public:
    explicit DataManager(QObject *parent = nullptr);

    //if no save file on system then return false. if there is a save file then return true
    bool retrieveSaveData();
    bool hasValidPlan();

    void saveData();
    void updateData();

    void markTaskAsComplete(std::string task); // would still require searching through vector, but who cares

signals:
    void tasksUpdated();
    void planUpdated();
};

#endif // DATAMANAGER_H
