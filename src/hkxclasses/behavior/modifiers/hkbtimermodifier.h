#ifndef HKBTIMERMODIFIER_H
#define HKBTIMERMODIFIER_H

#include "hkbmodifier.h"

class hkbTimerModifier: public hkbModifier
{
    friend class BehaviorGraphView;
    friend class TimerModifierUI;
public:
    hkbTimerModifier(HkxFile *parent, long ref = 0);
    virtual ~hkbTimerModifier();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaluateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
    bool isEventReferenced(int eventindex) const;
    void updateEventIndices(int eventindex);
    void mergeEventIndex(int oldindex, int newindex);
    void fixMergedEventIndices(BehaviorFile *dominantfile);
    void updateReferences(long &ref);
    QVector <HkxObject *> getChildrenOtherTypes() const;
private:
    hkbTimerModifier& operator=(const hkbTimerModifier&);
    hkbTimerModifier(const hkbTimerModifier &);
private:
    static uint refCount;
    static QString classname;
    long userData;
    QString name;
    bool enable;
    qreal alarmTimeSeconds;
    hkEventPayload alarmEvent;
};

#endif // HKBTIMERMODIFIER_H
