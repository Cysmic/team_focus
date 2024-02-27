#include "datamanager.h"

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
    this->notionManager = new NotionManager();
}


bool DataManager::retrieveSaveData(){
    std::string saveFile = getSaveFilePath();

    std::ifstream inFile(saveFile);
    if (!inFile.is_open()) {
        return false; // File doesn't exist
    }

    nlohmann::json j;
    inFile >> j;

    // Extract data from JSON object
    API_KEY = j["API_KEY"];
    DATABASE = j["DATABASE"];
    plan = j["plan"];
    this->notionManager->fetchTasks(DATABASE, API_KEY, tasks);
    //j["tags_tasks"].get<std::unordered_map<std::string, std::vector<std::string>>>(); // maybe remove this?

    inFile.close();
    return true;
}

bool DataManager::hasValidPlan(){
    if (this->plan.size() < 1) return false;
    return true;
}

void DataManager::updateData(){
    this->notionManager->fetchTasks(this->DATABASE, this->API_KEY, tasks);

    emit this->tasksUpdated(); // sends signal that tasks data structure updated

    // perform check here to see if plan needs updating and add/subtract from current plan.
    std::vector<std::string> taskNames;
    std::vector<std::string> newPlan;
    std::vector<std::string> newTasks;
    std::unordered_map<std::string, std::string> planHash;

    for (std::string task : this->plan){
        taskNames.push_back(getTask(task));
        planHash[taskNames.back()] = task;
    }

    for (Task task : this->tasks){
        if (!planHash.at(task.taskName).empty()){
            newPlan.push_back(createTaskString_Plan(task));
        }
        else{
            newTasks.push_back(createTaskString_Plan(task));
        }
    }

    newPlan.insert(newPlan.end(), newTasks.begin(), newTasks.end()); // appends new tasks to the end. current method removes tasks that do not belong in plan

    this->plan = newPlan;

    emit this->planUpdated(); // sends signal that plan has been updated
}

void DataManager::saveData(){
    nlohmann::json j;
    j["API_KEY"] = API_KEY;
    j["DATABASE"] = DATABASE;
    j["plan"] = plan;
    //j["tags_tasks"] = tags_tasks;

    std::string saveFile = getSaveFilePath(); //gets file save path and create directory if necessary
    std::ofstream outFile(saveFile);
    outFile << j.dump(4); // Write with pretty-printing
    outFile.close();
}

void DataManager::markTaskAsComplete(std::string task){
    for (auto& item : this->tasks) {
        if (item.taskName == task){
            item.status = "Done";
            this->notionManager->updateTask(API_KEY, item);
            return;
        }
    }
}
