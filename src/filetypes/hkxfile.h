#ifndef HKXFILE_H
#define HKXFILE_H

#include "src/utility.h"
#include "src/xml/hkxxmlreader.h"
#include "src/xml/hkxxmlwriter.h"
#include "src/hkxclasses/hkxobject.h"
//#include "generators.h"
//#include "modifiers.h"

#include <QList>
#include <QFile>

class hkbGenerator;
class hkbModifier;
class hkbOther;
class hkRootLevelContainer;
class MainWindow;

class HkxFile: public QFile
{
    friend class BehaviorGraphView;
public:
    void writeToLog(const QString & message, bool isError = false);
    void setProgressData(const QString & message, int value);
    HkxFile(MainWindow *window, const QString & name);
    virtual ~HkxFile();
    void closeFile();
    HkxObjectExpSharedPtr & getRootObject();
protected:
    virtual bool parse();
    virtual bool link();
    void setRootObject(HkxObjectExpSharedPtr & obj);
    MainWindow * getUI();
private:
    MainWindow *ui;
    HkxObjectExpSharedPtr rootObject;
};

class BehaviorFile: public HkxFile
{
    friend class hkbBehaviorGraphData;
    friend class BehaviorGraphView;
    friend class hkbBehaviorGraph;
    template <typename T>
    bool appendAndReadData(int ind, T * obj);
public:
    BehaviorFile(MainWindow *window, const QString & name);
    virtual ~BehaviorFile();
    HkxObjectExpSharedPtr * findHkxObject(long ref);
    HkxObjectExpSharedPtr * findGenerator(long ref);
    HkxObjectExpSharedPtr * findGeneratorChild(long ref);
    HkxObjectExpSharedPtr * findModifier(long ref);
    HkxObjectExpSharedPtr * findBehaviorGraph(long ref);
    QVector<int> removeGeneratorData();
    QVector<int> removeModifierData();
    QVector<int> removeOtherData();
    int getIndexOfGenerator(const HkxObjectExpSharedPtr & obj) const;
    bool setGeneratorData(HkxObjectExpSharedPtr & ptrToSet, int index);
    hkbGenerator * getGeneratorDataAt(int index);
    int getIndexOfModifier(const HkxObjectExpSharedPtr & obj) const;
    bool setModifierData(HkxObjectExpSharedPtr & ptrToSet, int index);
    HkxObject* getModifierDataAt(int index);
    QStringList getVariableNames() const;
    QStringList getEventNames() const;
    QStringList getGeneratorNamesAndTypeNames() const;
    HkxObject * getBehaviorGraphData() const;
    void removeBindings(int varIndex);
    hkVariableType getVariableTypeAt(int index) const;
    bool addObjectToFile(HkxObject *obj, long ref = -1);
    //For compatability for now... will be removed later...
    QStringList getGeneratorNames(){return QStringList();}
    QStringList getModifierNames(){return QStringList();}
    //
    void write();
    QString getRootObjectReferenceString();
protected:
    bool parse();
    bool link();
private:
    HkxXmlReader reader;
    HkxXMLWriter writer;
    HkxObjectExpSharedPtr behaviorGraph;
    HkxObjectExpSharedPtr stringData;
    HkxObjectExpSharedPtr variableValues;
    HkxObjectExpSharedPtr graphData;
    QList <HkxObjectExpSharedPtr> generators;
    QList <HkxObjectExpSharedPtr> generatorChildren;
    QList <HkxObjectExpSharedPtr> modifiers;
    QList <HkxObjectExpSharedPtr> otherTypes;
    long largestRef;
};

#endif // HKXFILE_H
