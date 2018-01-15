#ifndef SKYRIMANIMSETDATA_H
#define SKYRIMANIMSETDATA_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QTextStream>

#include "animcacheprojectdata.h"

class SkyrimAnimSetData
{
public:
    SkyrimAnimSetData();
    bool parse(QFile * file);
    bool write(const QString & filename);
    bool addAnimationToCache(const QString & projectname, const QString & eventname, const QVector <AnimCacheAnimationInfo> & animations, const QVector <AnimCacheVariable> & vars = QVector <AnimCacheVariable> (), const QVector <AnimCacheClipInfo> & clips = QVector <AnimCacheClipInfo> ());
    bool removeAnimationFromCache(const QString & projectname, const QString & animationname, const QString & variablename = "", const QString & clipname = "");
    //bool extractProject(const QString & projectname);
    AnimCacheProjectData *getProjectCacheData(const QString &name);
private:
    QStringList projectNames;
    QVector <AnimCacheProjectData *> projects;
};

#endif // SKYRIMANIMSETDATA_H
