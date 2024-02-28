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
    history = j["history"];

    if (plan.size() > 0)
        emit this->planUpdated(this->plan);

    this->notionManager->fetchTasks(DATABASE, API_KEY, tasks);
    emit this->tasksUpdated(this->tasks);

    inFile.close();
    return true;
}

bool DataManager::hasValidPlan(){
    if (this->plan.size() < 1) return false;
    return true;
}

void DataManager::updateData(){
    this->notionManager->fetchTasks(this->DATABASE, this->API_KEY, tasks);

    emit this->tasksUpdated(this->tasks); // sends signal that tasks data structure updated

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

    emit this->planUpdated(this->plan); // sends signal that plan has been updated
}

void DataManager::saveData(){
    nlohmann::json j;
    j["API_KEY"] = API_KEY;
    j["DATABASE"] = DATABASE;
    j["plan"] = plan;
    j["history"] = history;

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

            this->history.push_back(createTaskString_History(item, getCurrentDate(), 3));
            return;
        }
    }
}

void DataManager::setAPI_Database(std::string API, std::string Database){
    this->API_KEY = API;
    this->DATABASE = Database;
    this->saveData();
    this->retrieveSaveData();
    emit ChangeMenu(Menu::PLANGENERATION_M);

    std::cout << "API AND DATABASE SET" << std::endl;
    //emit signal here for mainmenu to switch again? or perhaps do that via submit signal emission.
}

void DataManager::receivePlanInfo(std::vector<std::string> filters, int numTasks){
    // will just do brute force for this.

    for (int i = 0; i < numTasks; i++){
        for (int j = 0; j<this->tasks.size(); j++){
            std::string prior = "";
            switch (tasks[j].priority){
            case 1:
                prior = "*";
                break;
            case 2:
                prior = "**";
                break;
            case 3:
                prior = "***";
                break;
            }

            if (filters[i] == this->tasks[j].tag || filters[i] == prior){
                this->plan.push_back(createTaskString_Plan(tasks[j])); //maybe need to break?
            }
        }
    }
}
