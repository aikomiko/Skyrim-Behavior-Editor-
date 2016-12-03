#ifndef BSCOMPUTEADDBONEANIMMODIFIER_H
#define BSCOMPUTEADDBONEANIMMODIFIER_H

#include "hkbmodifier.h"

class BSComputeAddBoneAnimModifier: public hkbModifier
{
    friend class BehaviorGraphView;
public:
    BSComputeAddBoneAnimModifier(BehaviorFile *parent, long ref = 0);
    virtual ~BSComputeAddBoneAnimModifier();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaulateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
private:
    BSComputeAddBoneAnimModifier& operator=(const BSComputeAddBoneAnimModifier&);
    BSComputeAddBoneAnimModifier(const BSComputeAddBoneAnimModifier &);
private:
    static uint refCount;
    static QString classname;
    long userData;
    QString name;
    bool enable;
    int boneIndex;
    hkQuadVariable translationLSOut;
    hkQuadVariable rotationLSOut;
    hkQuadVariable scaleLSOut;
};

#endif // BSCOMPUTEADDBONEANIMMODIFIER_H