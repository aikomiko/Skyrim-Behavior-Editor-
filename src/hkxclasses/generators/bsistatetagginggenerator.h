#ifndef BSISTATETAGGINGGENERATOR_H
#define BSISTATETAGGINGGENERATOR_H

#include "hkbgenerator.h"

class BSiStateTaggingGenerator: public hkbGenerator
{
    friend class BSiStateTaggingGeneratorUI;
    friend class BehaviorGraphView;
    friend class hkbStateMachine;
public:
    BSiStateTaggingGenerator(BehaviorFile *parent, long ref = 0);
    virtual ~BSiStateTaggingGenerator();
    bool readData(const HkxXmlReader & reader, long index);
    bool link();
    void unlink();
    QString getName() const;
    bool evaulateDataValidity();
    static QString getClassname();
    bool write(HkxXMLWriter *writer);
    bool hasChildren() const;
private:
    bool wrapObject(DataIconManager *objToInject, DataIconManager *childToReplace);
    bool setChildAt(HkxObject *newChild, ushort index = 0);
    bool appendObject(DataIconManager *objToAppend);
    bool removeObject(DataIconManager *objToRemove, bool removeAll = true);
    int addChildrenToList(QList <HkxObjectExpSharedPtr> & list, bool reverseOrder);
    BSiStateTaggingGenerator& operator=(const BSiStateTaggingGenerator&);
    BSiStateTaggingGenerator(const BSiStateTaggingGenerator &);
private:
    static uint refCount;
    static QString classname;
    ulong userData;
    QString name;
    HkxObjectExpSharedPtr pDefaultGenerator;
    int iStateToSetAs;
    int iPriority;
};

#endif // BSISTATETAGGINGGENERATOR_H
