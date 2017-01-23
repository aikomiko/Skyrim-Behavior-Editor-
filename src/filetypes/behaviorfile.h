#ifndef BEHAVIORFILE_H
#define BEHAVIORFILE_H

#include "src/filetypes/hkxfile.h"

class hkbBehaviorGraph;
class CharacterFile;
class hkbModifier;

class BehaviorFile: public HkxFile
{
    friend class hkbBehaviorGraphData;
    friend class BehaviorGraphView;
    friend class hkbBehaviorGraph;
    friend class MainWindow;
    friend class HkDataUI;
public:
    BehaviorFile(MainWindow *window, CharacterFile *characterData, const QString & name);
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
    hkbModifier * getModifierDataAt(int index);
    QStringList getVariableTypenames() const;
    QStringList getEventNames() const;
    QStringList getVariableNames() const;
    QStringList getGeneratorNamesAndTypeNames() const;
    QStringList getModifierNamesAndTypeNames() const;
    QStringList getCharacterPropertyNames() const;
    QStringList getCharacterPropertyTypenames() const;
    hkVariableType getVariableTypeAt(int index) const;
    bool addObjectToFile(HkxObject *obj, long ref = -1);
    QStringList getAllReferencedBehaviorFilePaths() const;
    QStringList getRagdollBoneNames() const;
    QStringList getRigBoneNames() const;
    void addCharacterProperty(int index);
    QString getVariableNameAt(int index) const;
    QString getCharacterPropertyNameAt(int index) const;
protected:
    bool parse();
    bool link();
private:
    HkxObject * getBehaviorGraphData() const;
    hkbBehaviorGraph * getBehaviorGraph() const;
    HkxObject * getRootStateMachine() const;
    //CustomTreeGraphicsViewIcon * getRootIcon() const;
    void write();
    void removeBindings(int varIndex);
private:
    CharacterFile *character;
    HkxObjectExpSharedPtr behaviorGraph;
    HkxObjectExpSharedPtr stringData;
    HkxObjectExpSharedPtr variableValues;
    HkxObjectExpSharedPtr graphData;
    QList <HkxObjectExpSharedPtr> generators;
    QList <HkxObjectExpSharedPtr> generatorChildren;
    QList <HkxObjectExpSharedPtr> modifiers;
    QList <HkxObjectExpSharedPtr> otherTypes;
    QStringList referencedBehaviors;
    long largestRef;
};

#endif // BEHAVIORFILE_H