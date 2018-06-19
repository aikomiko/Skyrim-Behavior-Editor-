#ifndef HKBSTATEMACHINESTATEINFO_H
#define HKBSTATEMACHINESTATEINFO_H

#include "hkbgenerator.h"

class hkbStateMachine;

class hkbStateMachineStateInfo: public hkbGenerator
{
    friend class HkDataUI;
    friend class BehaviorGraphView;
    friend class hkbStateMachine;
    friend class hkbStateMachineTransitionInfoArray;
    friend class StateMachineUI;
    friend class StateUI;
public:
    hkbStateMachineStateInfo(HkxFile *parent, hkbStateMachine *parentsm, long ref = 0);
    virtual ~hkbStateMachineStateInfo();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaluateDataValidity();
    static QString getClassname();
    QString getStateName(int stateId) const;
    QString getNestedStateName(int stateId, int nestedStateId) const;
    bool write(HkxXMLWriter *writer);
    bool hasChildren() const;
    bool isEventReferenced(int eventindex) const;
    void updateEventIndices(int eventindex);
    void mergeEventIndex(int oldindex, int newindex);
    void fixMergedEventIndices(BehaviorFile *dominantfile);
    bool merge(HkxObject *recessiveObject);
    void updateReferences(long &ref);
    QVector <HkxObject *> getChildrenOtherTypes() const;
private:
    QList <DataIconManager *> getChildren() const;
    int getIndexOfObj(DataIconManager *obj) const;
    bool insertObjectAt(int, DataIconManager *obj);
    bool removeObjectAt(int index);
    bool setStateId(ulong id);
    hkbStateMachine * getParentStateMachine() const;
    hkbStateMachineStateInfo& operator=(const hkbStateMachineStateInfo&);
    hkbStateMachineStateInfo(const hkbStateMachineStateInfo &);
private:
    hkbStateMachine *parentSM;
    static uint refCount;
    static QString classname;
    HkxSharedPtr enterNotifyEvents;
    HkxSharedPtr exitNotifyEvents;
    HkxSharedPtr transitions;
    HkxSharedPtr generator;
    QString name;
    ulong stateId;
    qreal probability;
    bool enable;
};

#endif // HKBSTATEMACHINESTATEINFO_H
