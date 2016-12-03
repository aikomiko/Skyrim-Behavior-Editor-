#include "hkbeventdrivenmodifier.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/hkxfile.h"

/*
 * CLASS: hkbEventDrivenModifier
*/

uint hkbEventDrivenModifier::refCount = 0;

QString hkbEventDrivenModifier::classname = "hkbEventDrivenModifier";

hkbEventDrivenModifier::hkbEventDrivenModifier(BehaviorFile *parent, long ref)
    : hkbModifier(parent, ref),
      userData(0),
      enable(true)
{
    setType(HKB_EVENT_DRIVEN_MODIFIER, TYPE_MODIFIER);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
    name = "EventDrivenModifier"+QString::number(refCount);
}

QString hkbEventDrivenModifier::getClassname(){
    return classname;
}

QString hkbEventDrivenModifier::getName() const{
    return name;
}

bool hkbEventDrivenModifier::setChildAt(HkxObject *newChild, ushort index){
    if (index == 0 && (!newChild || newChild->getType() == TYPE_MODIFIER)){
        modifier = HkxObjectExpSharedPtr(newChild);
        return true;
    }else{
        return false;
    }
}

bool hkbEventDrivenModifier::wrapObject(DataIconManager *objToInject, DataIconManager *childToReplace){
    if (objToInject->getType() != TYPE_MODIFIER){
        return false;
    }
    if (modifier.data() == childToReplace){
        if (!objToInject->setChildAt(modifier.data())){
            return false;
        }
        modifier = HkxObjectExpSharedPtr(objToInject);
        return true;
    }
    return false;
}

bool hkbEventDrivenModifier::appendObject(DataIconManager *objToAppend){
    if (objToAppend->getType() != TYPE_MODIFIER){
        return false;
    }
    modifier = HkxObjectExpSharedPtr(objToAppend);
    return true;
}

bool hkbEventDrivenModifier::removeObject(DataIconManager *objToRemove, bool removeAll){
    if (modifier.data() == objToRemove){
        modifier = HkxObjectExpSharedPtr();
        return true;
    }
    return false;
}

bool hkbEventDrivenModifier::hasChildren() const{
    if (modifier.data()){
        return true;
    }
    return false;
}

int hkbEventDrivenModifier::addChildrenToList(QList <HkxObjectExpSharedPtr> & list, bool reverseOrder){
    int objectChildCount = 0;
    if (modifier.data()){
        list.append(modifier);
        objectChildCount++;
    }
    return objectChildCount;
}

bool hkbEventDrivenModifier::readData(const HkxXmlReader &reader, long index){
    bool ok;
    QByteArray ref = reader.getNthAttributeValueAt(index - 1, 0);
    QByteArray text;
    while (index < reader.getNumElements() && reader.getNthAttributeNameAt(index, 1) != "class"){
        text = reader.getNthAttributeValueAt(index, 0);
        if (text == "variableBindingSet"){
            if (!variableBindingSet.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'variableBindingSet' reference!\nObject Reference: "+ref);
            }
        }else if (text == "userData"){
            userData = reader.getElementValueAt(index).toULong(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'userData' data field!\nObject Reference: "+ref);
            }
        }else if (text == "name"){
            name = reader.getElementValueAt(index);
            if (name == ""){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'name' data field!\nObject Reference: "+ref);
            }
        }else if (text == "enable"){
            enable = toBool(reader.getElementValueAt(index), &ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'enable' data field!\nObject Reference: "+ref);
            }
        }else if (text == "modifier"){
            if (!modifier.readReference(index, reader)){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'modifier' reference!\nObject Reference: "+ref);
            }
        }else if (text == "activateEventId"){
            activateEventId = reader.getElementValueAt(index).toInt(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'activateEventId' data field!\nObject Reference: "+ref);
            }
        }else if (text == "deactivateEventId"){
            deactivateEventId = reader.getElementValueAt(index).toInt(&ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'deactivateEventId' data field!\nObject Reference: "+ref);
            }
        }else if (text == "activeByDefault"){
            activeByDefault = toBool(reader.getElementValueAt(index), &ok);
            if (!ok){
                writeToLog(getClassname()+": readData()!\nFailed to properly read 'activeByDefault' data field!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbEventDrivenModifier::write(HkxXMLWriter *writer){
    if (!writer){
        return false;
    }
    if (!getIsWritten()){
        QString refString = "null";
        QStringList list1 = {writer->name, writer->clas, writer->signature};
        QStringList list2 = {getReferenceString(), getClassname(), "0x"+QString::number(getSignature(), 16)};
        writer->writeLine(writer->object, list1, list2, "");
        if (variableBindingSet.data()){
            refString = variableBindingSet.data()->getReferenceString();
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("variableBindingSet"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("userData"), QString::number(userData));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("name"), name);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("enable"), getBoolAsString(enable));
        if (modifier.data()){
            refString = modifier.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("modifier"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("activateEventId"), QString::number(activateEventId));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("deactivateEventId"), QString::number(deactivateEventId));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("activeByDefault"), getBoolAsString(activeByDefault));
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (variableBindingSet.data() && !variableBindingSet.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'variableBindingSet'!!!", true);
        }
        if (modifier.data() && !modifier.data()->write(writer)){
            getParentFile()->writeToLog(getClassname()+": write()!\nUnable to write 'modifier'!!!", true);
        }
    }
    return true;
}

bool hkbEventDrivenModifier::link(){
    if (!getParentFile()){
        return false;
    }
    if (!static_cast<DataIconManager *>(this)->linkVar()){
        writeToLog(getClassname()+": link()!\nFailed to properly link 'variableBindingSet' data field!\nObject Name: "+name);
    }
    HkxObjectExpSharedPtr *ptr = getParentFile()->findModifier(modifier.getReference());
    if (ptr){
        if ((*ptr)->getType() != TYPE_MODIFIER){
            writeToLog(getClassname()+": linkVar()!\nThe linked object 'modifier' is not a modifier!");
            setDataValidity(false);
        }
        modifier = *ptr;
    }
    return true;
}

void hkbEventDrivenModifier::unlink(){
    HkDynamicObject::unlink();
    modifier = HkxObjectExpSharedPtr();
}

bool hkbEventDrivenModifier::evaulateDataValidity(){    //Check if event id is valid???
    if (!HkDynamicObject::evaulateDataValidity()){
        return false;
    }else if (name == ""){
    }else if (!modifier.data()){
    }else{
        setDataValidity(true);
        return true;
    }
    setDataValidity(false);
    return false;
}

hkbEventDrivenModifier::~hkbEventDrivenModifier(){
    refCount--;
}