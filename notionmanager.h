#ifndef NOTIONMANAGER_H
#define NOTIONMANAGER_H

#include "includes.h"
#include "constants_types.h"

class NotionManager : public QObject
{
    Q_OBJECT
public:
    explicit NotionManager(QObject *parent = nullptr);
    void fetchTasks(std::string database, std::string API_TOKEN, std::vector<Task>& tasks);
    void updateTask(std::string API_TOKEN, Task task);

private:
    QNetworkAccessManager* networkManager;

private slots:
    void onTasksFetched(QNetworkReply* reply, std::vector<Task>& tasks);
};

#endif // NOTIONMANAGER_H
