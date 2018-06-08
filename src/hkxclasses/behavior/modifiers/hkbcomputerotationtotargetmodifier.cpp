#include "hkbcomputerotationtotargetmodifier.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/behaviorfile.h"

/*
 * CLASS: hkbComputeRotationToTargetModifier
*/

uint hkbComputeRotationToTargetModifier::refCount = 0;

QString hkbComputeRotationToTargetModifier::classname = "hkbComputeRotationToTargetModifier";

hkbComputeRotationToTargetModifier::hkbComputeRotationToTargetModifier(HkxFile *parent, long ref)
    : hkbModifier(parent, ref),
      userData(0),
      enable(true),
      resultIsDelta(true)
{
    setType(HKB_COMPUTE_ROTATION_TO_TARGET_MODIFIER, TYPE_MODIFIER);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
    name = "ComputeRotationToTargetModifier"+QString::number(refCount);
}

QString hkbComputeRotationToTargetModifier::getClassname(){
    return classname;
}

QString hkbComputeRotationToTargetModifier::getName() const{
    return name;
}

bool hkbComputeRotationToTargetModifier::readData(const HkxXmlReader &reader, long index){
    bool ok;
    QByteArray ref = reader.getNthAttributeValueAt(index - 1, 0);
    QByteArray text;
    while (index < reader.getNumElements() && reader.getNthAttributeNameAt(index, 1) != "class"){
        text = reader.getNthAttributeValueAt(index, 0);
        if (text == "variableBindingSet"){
            if (!variableBindingSet.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'variableBindingSet' reference!\nObject Reference: "+ref);
            }
        }else if (text == "userData"){
            userData = reader.getElementValueAt(index).toULong(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'userData' data field!\nObject Reference: "+ref);
            }
        }else if (text == "name"){
            name = reader.getElementValueAt(index);
            if (name == ""){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'name' data field!\nObject Reference: "+ref);
            }
        }else if (text == "enable"){
            enable = toBool(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'enable' data field!\nObject Reference: "+ref);
            }
        }else if (text == "rotationOut"){
            rotationOut = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'rotationOut' data field!\nObject Reference: "+ref);
            }
        }else if (text == "targetPosition"){
            targetPosition = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'targetPosition' data field!\nObject Reference: "+ref);
            }
        }else if (text == "currentPosition"){
            currentPosition = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'currentPosition' data field!\nObject Reference: "+ref);
            }
        }else if (text == "currentRotation"){
            currentRotation = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'currentRotation' data field!\nObject Reference: "+ref);
            }
        }else if (text == "localAxisOfRotation"){
            localAxisOfRotation = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'localAxisOfRotation' data field!\nObject Reference: "+ref);
            }
        }else if (text == "localFacingDirection"){
            localFacingDirection = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'localFacingDirection' data field!\nObject Reference: "+ref);
            }
        }else if (text == "resultIsDelta"){
            resultIsDelta = toBool(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'resultIsDelta' data field!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbComputeRotationToTargetModifier::write(HkxXMLWriter *writer){
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
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("rotationOut"), rotationOut.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("targetPosition"), targetPosition.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("currentPosition"), currentPosition.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("currentRotation"), currentRotation.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("localAxisOfRotation"), localAxisOfRotation.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("localFacingDirection"), localFacingDirection.getValueAsString());
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("resultIsDelta"), getBoolAsString(resultIsDelta));
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (variableBindingSet.data() && !variableBindingSet.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'variableBindingSet'!!!");
        }
    }
    return true;
}

bool hkbComputeRotationToTargetModifier::link(){
    if (!getParentFile()){
        return false;
    }
    if (!static_cast<HkDynamicObject *>(this)->linkVar()){
        WRITE_TO_LOG(getClassname()+": link()!\nFailed to properly link 'variableBindingSet' data field!\nObject Name: "+name);
    }
    return true;
}

void hkbComputeRotationToTargetModifier::unlink(){
    HkDynamicObject::unlink();
}

bool hkbComputeRotationToTargetModifier::evaluateDataValidity(){
    if (!HkDynamicObject::evaluateDataValidity() || (name == "")){
        setDataValidity(false);
        return false;
    }else{
        setDataValidity(true);
        return true;
    }
}

hkbComputeRotationToTargetModifier::~hkbComputeRotationToTargetModifier(){
    refCount--;
}
