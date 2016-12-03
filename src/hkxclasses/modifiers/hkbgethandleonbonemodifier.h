#ifndef HKBGETHANDLEONBONEMODIFIER_H
#define HKBGETHANDLEONBONEMODIFIER_H

#include "hkbmodifier.h"

class hkbGetHandleOnBoneModifier: public hkbModifier
{
    friend class BehaviorGraphView;
public:
    hkbGetHandleOnBoneModifier(BehaviorFile *parent, long ref = 0);
    virtual ~hkbGetHandleOnBoneModifier();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaulateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
private:
    hkbGetHandleOnBoneModifier& operator=(const hkbGetHandleOnBoneModifier&);
    hkbGetHandleOnBoneModifier(const hkbGetHandleOnBoneModifier &);
private:
    static uint refCount;
    static QString classname;
    long userData;
    QString name;
    bool enable;
    HkxObjectExpSharedPtr handleOut;
    QString localFrameName;
    int ragdollBoneIndex;
    int animationBoneIndex;
};

#endif // HKBGETHANDLEONBONEMODIFIER_H