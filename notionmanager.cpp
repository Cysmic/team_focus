#include "notionmanager.h"

NotionManager::NotionManager(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
}

void NotionManager::fetchTasks(std::string database, std::string API_TOKEN, std::vector<Task>& tasks) {
    std::string url_string = "https://api.notion.com/v1/databases/" + database + "/query";
    std::string bearer = "Bearer " + API_TOKEN;


    QUrl url(url_string.c_str());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", bearer.c_str());
    request.setRawHeader("Notion-Version", "2021-08-16");

    // Construct the JSON payload - filters for tasks that are not complete
    QJsonObject statusEqualsNotStarted;
    statusEqualsNotStarted["equals"] = "Not started";

    QJsonObject statusEqualsInProgress;
    statusEqualsInProgress["equals"] = "In progress";

    QJsonObject statusFilterNotStarted;
    statusFilterNotStarted["property"] = "Status";
    statusFilterNotStarted["status"] = statusEqualsNotStarted;

    QJsonObject statusFilterInProgress;
    statusFilterInProgress["property"] = "Status";
    statusFilterInProgress["status"] = statusEqualsInProgress;

    QJsonArray orFilters;
    orFilters.append(statusFilterNotStarted);
    orFilters.append(statusFilterInProgress);

    QJsonObject filter;
    filter["or"] = orFilters;

    QJsonObject data;
    data["filter"] = filter;

    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();

    // // Send the POST request with the JSON payload
    // QNetworkReply* reply = networkManager->post(request, jsonData);

    // //QNetworkReply* reply = networkManager->post(request, QByteArray());
    // connect(reply, &QNetworkReply::finished, this, [this, reply, &tasks]() {
    //     onTasksFetched(reply, tasks);
    // });

    // this is preventing it from being handled asynchronously. The commented out version above is the async version.
    // I am doing this so that data loads before page change. what shouuld really happen is
    // if data changes, all pages change accordingly via signal emission
    QNetworkReply* reply = networkManager->post(request, jsonData);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    onTasksFetched(reply, tasks);
}

void NotionManager::onTasksFetched(QNetworkReply* reply, std::vector<Task>& tasks) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray resultsArray = jsonObject["results"].toArray();

        std::cout << "Results Array size: " << resultsArray.size() << std::endl;

        for (auto result : resultsArray){
            QJsonObject obj = result.toObject();
            Task task;
            task.id = obj["id"].toString().toStdString();
            task.taskName = obj["properties"].toObject()["Name"].toObject()["title"].toArray()[0].toObject()["text"].toObject()["content"].toString().toStdString();
            task.dueDate = obj["properties"].toObject()["Due Date"].toObject()["date"].toObject()["start"].toString().toStdString();
            task.priority = atoi(obj["properties"].toObject()["Priority"].toObject()["select"].toObject()["name"].toString().toStdString().c_str());
            task.status = obj["properties"].toObject()["Status"].toObject()["status"].toObject()["name"].toString().toStdString();
            // assuming here that we will only store one tag per task.
            task.tag = obj["properties"].toObject()["Tags"].toObject()["multi_select"].toArray()[0].toObject()["name"].toString().toStdString();

            tasks.push_back(task);
            std::cout << "task: " << task.taskName << std::endl;
            std::cout << "id: " << task.id << std::endl;
            std::cout << "due Date: " << task.dueDate << std::endl;
            std::cout << "priority: " << task.priority << std::endl;
            std::cout << "Status: " << task.status << std::endl;
            std::cout << "Tag: " << task.tag << std::endl;
        }
    }
    reply->deleteLater();
}

void NotionManager::updateTask(std::string API_TOKEN, Task task){
    std::cout << "are there spaces for this task?" << task.id << "what about here" << std::endl;
    std::string url_string = "https://api.notion.com/v1/pages/" + task.id;
    std::string bearer = "Bearer " + API_TOKEN;


    QUrl url(url_string.c_str());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", bearer.c_str());
    request.setRawHeader("Notion-Version", "2022-06-28");

    // Construct the JSON payload for the PATCH request
    QJsonObject statusName;
    statusName["name"] = "Done";

    QJsonObject status;
    status["status"] = statusName;

    QJsonObject properties;
    properties["Status"] = status;

    QJsonObject data;
    data["properties"] = properties;

    QJsonDocument doc(data);
    QByteArray jsonData = doc.toJson();

    // Perform the PATCH request
    QNetworkReply* reply = networkManager->sendCustomRequest(request, "PATCH", jsonData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        // Handle the response
        if (reply->error() == QNetworkReply::NoError) {
            std::cout << "Successfully updated task" << std::endl;
        } else {
            // Error, handle accordingly
            std::cerr << "Failed to update task" << std::endl;
        }
        reply->deleteLater();
    });
}
