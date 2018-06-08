#include "hkbcharacterdata.h"
#include "src/xml/hkxxmlreader.h"
#include "src/filetypes/characterfile.h"
#include "src/filetypes/projectfile.h"
#include "src/hkxclasses/behavior/hkbcharacterstringdata.h"
#include "src/hkxclasses/behavior/hkbvariablevalueset.h"

/*
 * CLASS: hkbCharacterData
*/

uint hkbCharacterData::refCount = 0;

QString hkbCharacterData::classname = "hkbCharacterData";

QStringList hkbCharacterData::Type = {
    "VARIABLE_TYPE_BOOL",
    "VARIABLE_TYPE_INT8",
    "VARIABLE_TYPE_INT16",
    "VARIABLE_TYPE_INT32",
    "VARIABLE_TYPE_REAL",
    "VARIABLE_TYPE_POINTER",
    "VARIABLE_TYPE_VECTOR4",
    "VARIABLE_TYPE_QUATERNION"
};

hkbCharacterData::hkbCharacterData(HkxFile *parent, long ref)
    : HkxObject(parent, ref),
      modelUpMS(0, 0, 1, 0),
      modelForwardMS(0, 1, 0, 0),
      modelRightMS(1, 0, 0, 0),
      scale(1)
{
    setType(HKB_CHARACTER_DATA, TYPE_OTHER);
    getParentFile()->addObjectToFile(this, ref);
    refCount++;
}

QString hkbCharacterData::getClassname(){
    return classname;
}

HkxObject * hkbCharacterData::getVariantVariable(int index) const{
    hkbVariableValueSet *variableValues = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    if (variableValues->wordVariableValues.size() > index && characterPropertyInfos.size() > index){
        int count = -1;
        for (int i = 0; i <= index; i++){
            if (characterPropertyInfos.at(i).type == "VARIABLE_TYPE_POINTER"){
                count++;
            }
        }
        if (count < variableValues->variantVariableValues.size() && count > -1){
            return variableValues->variantVariableValues.at(count).data();
        }
    }
    return nullptr;
}

void hkbCharacterData::addVariable(hkVariableType type, const QString & name){
    hkbCharacterStringData *strData = static_cast<hkbCharacterStringData *>(stringData.data());
    hkbVariableValueSet *varData = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    hkVariableInfo varInfo;
    switch (type){
    case VARIABLE_TYPE_BOOL:
        varInfo.type = "VARIABLE_TYPE_BOOL";
        break;
    case VARIABLE_TYPE_INT8:
        varInfo.type = "VARIABLE_TYPE_INT8";
        break;
    case VARIABLE_TYPE_INT16:
        varInfo.type = "VARIABLE_TYPE_INT16";
        break;
    case VARIABLE_TYPE_INT32:
        varInfo.type = "VARIABLE_TYPE_INT32";
        break;
    case VARIABLE_TYPE_REAL:
        varInfo.type = "VARIABLE_TYPE_REAL";
        break;
    case VARIABLE_TYPE_POINTER:
        varInfo.type = "VARIABLE_TYPE_POINTER";
        varData->variantVariableValues.append(HkxSharedPtr());
        break;
    case VARIABLE_TYPE_VECTOR4:
        varInfo.type = "VARIABLE_TYPE_VECTOR4";
        varData->quadVariableValues.append(hkQuadVariable());
        break;
    case VARIABLE_TYPE_QUATERNION:
        varInfo.type = "VARIABLE_TYPE_QUATERNION";
        varData->quadVariableValues.append(hkQuadVariable());
        break;
    default:
        return;
    }
    strData->characterPropertyNames.append(name);
    varData->wordVariableValues.append(0);
    characterPropertyInfos.append(varInfo);
}

void hkbCharacterData::addVariable(hkVariableType type){
    hkbCharacterStringData *strData = static_cast<hkbCharacterStringData *>(stringData.data());
    hkbVariableValueSet *varData = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    /*if (!varData){
        varData = new hkbVariableValueSet(this);
        characterPropertyValues = HkxSharedPtr(varData);
    }*/
    hkVariableInfo varInfo;
    switch (type){
    case VARIABLE_TYPE_BOOL:
        varInfo.type = "VARIABLE_TYPE_BOOL";
        break;
    case VARIABLE_TYPE_INT8:
        varInfo.type = "VARIABLE_TYPE_INT8";
        break;
    case VARIABLE_TYPE_INT16:
        varInfo.type = "VARIABLE_TYPE_INT16";
        break;
    case VARIABLE_TYPE_INT32:
        varInfo.type = "VARIABLE_TYPE_INT32";
        break;
    case VARIABLE_TYPE_REAL:
        varInfo.type = "VARIABLE_TYPE_REAL";
        break;
    case VARIABLE_TYPE_POINTER:
        varInfo.type = "VARIABLE_TYPE_POINTER";
        varData->variantVariableValues.append(HkxSharedPtr((HkxObject *)(static_cast<CharacterFile *>(getParentFile())->addNewBoneWeightArray())));
        break;
    case VARIABLE_TYPE_VECTOR4:
        varInfo.type = "VARIABLE_TYPE_VECTOR4";
        varData->quadVariableValues.append(hkQuadVariable());
        break;
    case VARIABLE_TYPE_QUATERNION:
        varInfo.type = "VARIABLE_TYPE_QUATERNION";
        varData->quadVariableValues.append(hkQuadVariable());
        break;
    default:
        return;
    }
    QString name = "NEW-"+varInfo.type;
    int num = 0;
    int index;
    for (int i = 0; i < strData->characterPropertyNames.size(); i++){
        if (strData->characterPropertyNames.at(i) == name){
            index = name.indexOf('_');
            if (index > -1){
                name.remove(name.indexOf('_'), name.size());
            }
            name.append("_"+QString::number(num));
            num++;
            if (num > 1){
                if (num > 10){
                    name = name+"_FUCKING_RENAME_YOUR_VARIABLES_PROPERLY!";
                    break;
                }
                i = 0;
            }
        }
    }
    strData->characterPropertyNames.append(name);
    varData->wordVariableValues.append(0);
    characterPropertyInfos.append(varInfo);
}

void hkbCharacterData::removeVariable(int index){
    hkbCharacterStringData *strData = static_cast<hkbCharacterStringData *>(stringData.data());
    hkbVariableValueSet *varData = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    int count = -1;
    if (index < strData->characterPropertyNames.size() && index < varData->wordVariableValues.size() && index < characterPropertyInfos.size() && index > -1){
        if (characterPropertyInfos.at(index).type == "VARIABLE_TYPE_POINTER"){
            for (int i = 0; i <= index; i++){
                if (characterPropertyInfos.at(i).type == "VARIABLE_TYPE_POINTER"){
                    count++;
                }
            }
            if (count < varData->variantVariableValues.size() && count > -1){
                varData->variantVariableValues.removeAt(count);
            }
        }else if (characterPropertyInfos.at(index).type == "VARIABLE_TYPE_VECTOR4" || characterPropertyInfos.at(index).type == "VARIABLE_TYPE_QUATERNION"){
            for (int i = 0; i <= index; i++){
                if (characterPropertyInfos.at(i).type == "VARIABLE_TYPE_VECTOR4" || characterPropertyInfos.at(i).type == "VARIABLE_TYPE_QUATERNION"){
                    count++;
                }
            }
            if (count < varData->quadVariableValues.size() && count > -1){
                varData->quadVariableValues.removeAt(count);
            }
        }
        strData->characterPropertyNames.removeAt(index);
        varData->wordVariableValues.removeAt(index);
        characterPropertyInfos.removeAt(index);
    }
}

hkVariableType hkbCharacterData::getVariableTypeAt(int index) const{
    if (characterPropertyInfos.size() > index && index > -1){
        QString type = characterPropertyInfos.at(index).type;
        if (type == "VARIABLE_TYPE_BOOL"){
            return VARIABLE_TYPE_BOOL;
        }else if (type == "VARIABLE_TYPE_INT8"){
            return VARIABLE_TYPE_INT8;
        }else if (type == "VARIABLE_TYPE_INT16"){
            return VARIABLE_TYPE_INT16;
        }else if (type == "VARIABLE_TYPE_INT32"){
            return VARIABLE_TYPE_INT32;
        }else if (type == "VARIABLE_TYPE_REAL"){
            return VARIABLE_TYPE_REAL;
        }else if (type == "VARIABLE_TYPE_POINTER"){
            return VARIABLE_TYPE_POINTER;
        }else if (type == "VARIABLE_TYPE_VECTOR4"){
            return VARIABLE_TYPE_VECTOR4;
        }else if (type == "VARIABLE_TYPE_QUATERNION"){
            return VARIABLE_TYPE_QUATERNION;
        }
    }
    return VARIABLE_TYPE_INT8;
}

void hkbCharacterData::setVariableNameAt(int index, const QString & name){
    hkbCharacterStringData *strData = static_cast<hkbCharacterStringData *>(stringData.data());
    if (strData->characterPropertyNames.size() > index && index > -1){
        strData->characterPropertyNames.replace(index, name);
    }
}

void hkbCharacterData::setWordVariableValueAt(int index, int value){
    hkbVariableValueSet *varData = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    if (varData->wordVariableValues.size() > index && index > -1){
        varData->wordVariableValues.replace(index, value);
    }
}

void hkbCharacterData::setQuadVariableValueAt(int index, hkQuadVariable value){
    hkbCharacterStringData *strData = static_cast<hkbCharacterStringData *>(stringData.data());
    hkbVariableValueSet *varData = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    int count = -1;
    if (index < strData->characterPropertyNames.size() && index < varData->wordVariableValues.size() && index < characterPropertyInfos.size()){
        if (characterPropertyInfos.at(index).type == "VARIABLE_TYPE_VECTOR4" || characterPropertyInfos.at(index).type == "VARIABLE_TYPE_QUATERNION"){
            for (int i = 0; i <= index; i++){
                if (characterPropertyInfos.at(i).type == "VARIABLE_TYPE_VECTOR4" || characterPropertyInfos.at(i).type == "VARIABLE_TYPE_QUATERNION"){
                    count++;
                }
            }
            if (count < varData->quadVariableValues.size() && count > -1){
                varData->quadVariableValues.replace(count, value);
            }
        }else{
            return;
        }
    }
}

hkQuadVariable hkbCharacterData::getQuadVariable(int index, bool *ok) const{
    *ok = false;
    hkbVariableValueSet *variableValues = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
    if (variableValues->wordVariableValues.size() > index && characterPropertyInfos.size() > index){
        int count = -1;
        for (int i = 0; i <= index; i++){
            if (characterPropertyInfos.at(i).type == "VARIABLE_TYPE_VECTOR4" || characterPropertyInfos.at(i).type == "VARIABLE_TYPE_QUATERNION"){
                count++;
            }
        }
        if (count < variableValues->quadVariableValues.size() && count > -1){
            *ok = true;
            return variableValues->quadVariableValues.at(count);
        }
    }
    return hkQuadVariable();
}


bool hkbCharacterData::readData(const HkxXmlReader &reader, long index){
    bool ok;
    int numElems = 0;
    QByteArray ref = reader.getNthAttributeValueAt(index - 1, 0);
    QByteArray text;
    while (index < reader.getNumElements() && reader.getNthAttributeNameAt(index, 1) != "class"){
        text = reader.getNthAttributeValueAt(index, 0);
        if (text == "capsuleHeight"){
            characterControllerInfo.capsuleHeight = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'capsuleHeight' data field!\nObject Reference: "+ref);
            }
        }else if (text == "capsuleRadius"){
            characterControllerInfo.capsuleRadius = reader.getElementValueAt(index).toDouble(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'capsuleRadius' data field!\nObject Reference: "+ref);
            }
        }else if (text == "collisionFilterInfo"){
            characterControllerInfo.collisionFilterInfo = reader.getElementValueAt(index).toInt(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'collisionFilterInfo' data field!\nObject Reference: "+ref);
            }
        }else if (text == "characterControllerCinfo"){
            if (!characterControllerInfo.characterControllerCinfo.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterControllerCinfo' reference!\nObject Reference: "+ref);
            }
        }else if (text == "modelUpMS"){
            modelUpMS = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'modelUpMS' data field!\nObject Reference: "+ref);
            }
        }else if (text == "modelForwardMS"){
            modelForwardMS = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'modelForwardMS' data field!\nObject Reference: "+ref);
            }
        }else if (text == "modelRightMS"){
            modelRightMS = readVector4(reader.getElementValueAt(index), &ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'modelRightMS' data field!\nObject Reference: "+ref);
            }
        }else if (text == "characterPropertyInfos"){
            numElems = reader.getNthAttributeValueAt(index, 1).toInt(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterPropertyInfos' data!\nObject Reference: "+ref);
                return false;
            }
            for (int i = 0; i < numElems; i++){
                index += 4;
                if (index >= reader.getNumElements()){
                    WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterPropertyInfos' data!\nObject Reference: "+ref);
                    return false;
                }
                hkVariableInfo temp;
                temp.role.role = reader.getElementValueAt(index);
                index++;
                if (index >= reader.getNumElements()){
                    WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterPropertyInfos' data!\nObject Reference: "+ref);
                    return false;
                }
                temp.role.flags = reader.getElementValueAt(index);
                index++;
                if (index >= reader.getNumElements()){
                    WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterPropertyInfos' data!\nObject Reference: "+ref);
                    return false;
                }
                temp.type = reader.getElementValueAt(index);
                characterPropertyInfos.append(temp);
                if (!Type.contains(temp.type)){
                    WRITE_TO_LOG(getClassname()+": readData()!\nInvalid variable type read!\nObject Reference: "+ref);
                    return false;
                }
            }
        }else if (text == "numBonesPerLod"){
            numElems = reader.getNthAttributeValueAt(index, 1).toInt(&ok);
            if (!ok){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'numBonesPerLod' data!\nObject Reference: "+ref);
                return false;
            }
            index++;
            if (index >= reader.getNumElements()){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'numBonesPerLod' data!\nObject Reference: "+ref);
                return false;
            }
            for (int i = 0; i < numElems; i++){
                index++;
                if (index >= reader.getNumElements()){
                    WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'numBonesPerLod' data!\nObject Reference: "+ref);
                    return false;
                }
                numBonesPerLod.append(reader.getElementValueAt(index).toInt(&ok));
                if (!ok){
                    WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'numBonesPerLod' data!\nObject Reference: "+ref);
                    return false;
                }
            }
            index--;
        }else if (text == "characterPropertyValues"){
            if (!characterPropertyValues.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'characterPropertyValues' reference!\nObject Reference: "+ref);
            }
        }else if (text == "footIkDriverInfo"){
            if (!footIkDriverInfo.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'footIkDriverInfo' reference!\nObject Reference: "+ref);
            }
        }else if (text == "handIkDriverInfo"){
            if (!handIkDriverInfo.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'handIkDriverInfo' reference!\nObject Reference: "+ref);
            }
        }else if (text == "stringData"){
            if (!stringData.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'stringData' reference!\nObject Reference: "+ref);
            }
        }else if (text == "mirroredSkeletonInfo"){
            if (!mirroredSkeletonInfo.readShdPtrReference(index, reader)){
                WRITE_TO_LOG(getClassname()+": readData()!\nFailed to properly read 'mirroredSkeletonInfo' reference!\nObject Reference: "+ref);
            }
        }
        index++;
    }
    return true;
}

bool hkbCharacterData::write(HkxXMLWriter *writer){
    if (!writer){
        return false;
    }
    if (!getIsWritten()){
        QString refString = "null";
        QStringList list1 = {writer->name, writer->clas, writer->signature};
        QStringList list2 = {getReferenceString(), getClassname(), "0x"+QString::number(getSignature(), 16)};
        writer->writeLine(writer->object, list1, list2, "");
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("characterControllerInfo"), "");
        writer->writeLine(writer->object, true);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("capsuleHeight"), QString::number(characterControllerInfo.capsuleHeight, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("capsuleRadius"), QString::number(characterControllerInfo.capsuleRadius, char('f'), 6));
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("collisionFilterInfo"), QString::number(characterControllerInfo.collisionFilterInfo, char('f'), 6));
        if (characterControllerInfo.characterControllerCinfo.data()){
            refString = characterControllerInfo.characterControllerCinfo.data()->getReferenceString();
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("characterControllerCinfo"), refString);
        writer->writeLine(writer->object, false);
        writer->writeLine(writer->parameter, false);
        list1 = {writer->name, writer->numelements};
        list2 = {"characterPropertyInfos", QString::number(characterPropertyInfos.size())};
        writer->writeLine(writer->parameter, list1, list2, "");
        for (int i = 0; i < characterPropertyInfos.size(); i++){
            writer->writeLine(writer->object, true);
            writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("role"), "");
            writer->writeLine(writer->object, true);
            writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("role"), characterPropertyInfos.at(i).role.role);
            writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("flags"), characterPropertyInfos.at(i).role.flags);
            writer->writeLine(writer->object, false);
            writer->writeLine(writer->parameter, false);
            writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("type"), characterPropertyInfos.at(i).type);
            writer->writeLine(writer->object, false);
        }
        if (characterPropertyInfos.size() > 0){
            writer->writeLine(writer->parameter, false);
        }
        list1 = {writer->name, writer->numelements};
        list2 = {"numBonesPerLod", QString::number(numBonesPerLod.size())};
        writer->writeLine(writer->parameter, list1, list2, "");
        for (int i = 0; i < numBonesPerLod.size(); i++){
            writer->writeLine(writer->string, QStringList(), QStringList(), QString::number(numBonesPerLod.at(i)));
        }
        if (numBonesPerLod.size() > 0){
            writer->writeLine(writer->parameter, false);
        }
        if (characterPropertyValues.data()){
            refString = characterPropertyValues.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("characterPropertyValues"), refString);
        if (footIkDriverInfo.data()){
            refString = footIkDriverInfo.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("footIkDriverInfo"), refString);
        if (handIkDriverInfo.data()){
            refString = handIkDriverInfo.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("handIkDriverInfo"), refString);
        if (stringData.data()){
            refString = stringData.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("stringData"), refString);
        if (mirroredSkeletonInfo.data()){
            refString = mirroredSkeletonInfo.data()->getReferenceString();
        }else{
            refString = "null";
        }
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("mirroredSkeletonInfo"), refString);
        writer->writeLine(writer->parameter, QStringList(writer->name), QStringList("scale"), QString::number(scale, char('f'), 6));
        writer->writeLine(writer->object, false);
        setIsWritten();
        writer->writeLine("\n");
        if (characterPropertyValues.data() && !characterPropertyValues.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'characterPropertyValues'!!!");
        }
        if (footIkDriverInfo.data() && !footIkDriverInfo.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'footIkDriverInfo'!!!");
        }
        if (handIkDriverInfo.data() && !handIkDriverInfo.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'handIkDriverInfo'!!!");
        }
        if (stringData.data() && !stringData.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'stringData'!!!");
        }
        if (mirroredSkeletonInfo.data() && !mirroredSkeletonInfo.data()->write(writer)){
            WRITE_TO_LOG(getClassname()+": write()!\nUnable to write 'mirroredSkeletonInfo'!!!");
        }
    }
    return true;
}

bool hkbCharacterData::link(){
    if (!getParentFile()){
        return false;
    }
    HkxSharedPtr *ptr = &static_cast<CharacterFile *>(getParentFile())->characterPropertyValues;
    if ((*ptr).data() && (*ptr)->getSignature() != HKB_VARIABLE_VALUE_SET){
        WRITE_TO_LOG(getClassname()+": link()!\n'characterPropertyValues' data field is linked to invalid child!\n");
        setDataValidity(false);
        characterPropertyValues = *ptr;
    }else{
        characterPropertyValues = *ptr;
    }
    ptr = &static_cast<CharacterFile *>(getParentFile())->footIkDriverInfo;
    if ((*ptr).data() && (*ptr)->getSignature() != HKB_FOOT_IK_DRIVER_INFO){
        WRITE_TO_LOG(getClassname()+": link()!\n'footIkDriverInfo' data field is linked to invalid child!\n");
        setDataValidity(false);
        footIkDriverInfo = *ptr;
    }else{
        footIkDriverInfo = *ptr;
    }
    ptr = &static_cast<CharacterFile *>(getParentFile())->handIkDriverInfo;
    if ((*ptr).data() && (*ptr)->getSignature() != HKB_HAND_IK_DRIVER_INFO){
        WRITE_TO_LOG(getClassname()+": link()!\n'handIkDriverInfo' data field is linked to invalid child!\n");
        setDataValidity(false);
        handIkDriverInfo = *ptr;
    }else{
        handIkDriverInfo = *ptr;
    }
    ptr = &static_cast<CharacterFile *>(getParentFile())->stringData;
    if ((*ptr).data() && (*ptr)->getSignature() != HKB_CHARACTER_STRING_DATA){
        WRITE_TO_LOG(getClassname()+": link()!\n'stringData' data field is linked to invalid child!\n");
        setDataValidity(false);
        stringData = *ptr;
    }else{
        stringData = *ptr;
    }
    ptr = &static_cast<CharacterFile *>(getParentFile())->mirroredSkeletonInfo;
    if ((*ptr).data() && (*ptr)->getSignature() != HKB_MIRRORED_SKELETON_INFO){
        WRITE_TO_LOG(getClassname()+": link()!\n'mirroredSkeletonInfo' data field is linked to invalid child!\n");
        setDataValidity(false);
        mirroredSkeletonInfo = *ptr;
    }else{
        mirroredSkeletonInfo = *ptr;
    }
    return true;
}

QStringList hkbCharacterData::getCharacterPropertyNames() const{
    return static_cast<hkbCharacterStringData *>(stringData.data())->characterPropertyNames;
}

QStringList hkbCharacterData::getCharacterPropertyTypenames() const{
    QStringList list;
    for (int i = 0; i < characterPropertyInfos.size(); i++){
        list.append(characterPropertyInfos.at(i).type);
    }
    return list;
}

bool hkbCharacterData::merge(HkxObject *recessiveobj){
    hkbCharacterData *otherdata;
    hkbCharacterStringData *otherstrings;
    hkbVariableValueSet *othervalues;
    hkbCharacterStringData *strings;
    hkbVariableValueSet *values;
    bool found;
    int size;
    if (recessiveobj && recessiveobj->getSignature() == HKB_CHARACTER_DATA){
        otherdata = static_cast<hkbCharacterData *>(recessiveobj);
        if (evaluateDataValidity() && recessiveobj->evaluateDataValidity()){
            strings = static_cast<hkbCharacterStringData *>(stringData.data());
            values = static_cast<hkbVariableValueSet *>(characterPropertyValues.data());
            otherstrings = static_cast<hkbCharacterStringData *>(otherdata->stringData.data());
            othervalues = static_cast<hkbVariableValueSet *>(otherdata->characterPropertyValues.data());
            size = strings->animationNames.size() - 1;
            for (auto i = otherstrings->animationNames.size() - 1; i >= 0; i--){
                found = false;
                for (auto j = size; j >= 0; j--){
                    if (strings->animationNames.at(j) == otherstrings->animationNames.at(i)){
                        found = true;
                        break;
                    }
                }
                if (!found){
                    strings->animationNames.append(otherstrings->animationNames.at(i));
                    static_cast<CharacterFile *>(getParentFile())->project->appendAnimation(&static_cast<CharacterFile *>(recessiveobj->getParentFile())->project->getAnimationMotionData(i));
                    //static_cast<BehaviorFile *>(otherdata->getParentFile())->mergeEventIndices(i, eventInfos.size() - 1);
                }
            }
            size = strings->characterPropertyNames.size() - 1;
            for (auto i = otherstrings->characterPropertyNames.size() - 1; i >= 0; i--){
                found = false;
                for (auto j = size; j >= 0; j--){
                    if (strings->characterPropertyNames.at(j) == otherstrings->characterPropertyNames.at(i)){
                        found = true;
                        break;
                    }
                }
                if (!found){    //TO DO: Support quad and pointer variables...
                    strings->characterPropertyNames.append(otherstrings->characterPropertyNames.at(i));
                    if (othervalues->wordVariableValues.size() > i){
                        values->wordVariableValues.append(othervalues->wordVariableValues.at(i));
                    }else{
                        WARNING_MESSAGE("hkbCharacterData: merge(): Mismatch in size between variableNames and wordVariableValues!!!");
                    }
                    if (otherdata->characterPropertyInfos.size() > i){
                        characterPropertyInfos.append(otherdata->characterPropertyInfos.at(i));
                    }else{
                        WARNING_MESSAGE("hkbCharacterData: merge(): Mismatch in size between variableNames and variableInfos!!!");
                    }
                    //TO DO: Support character properties...
                    //static_cast<BehaviorFile *>(otherdata->getParentFile())->mergeVariableIndices(i, variableInfos.size() - 1);
                }
            }
            return true;
        }else{
            WARNING_MESSAGE("hkbCharacterData: merge(): Invalid data detected!!!");
        }
    }else{
        WARNING_MESSAGE("hkbCharacterData: merge(): Attempting to merge invalid object type or nullptr!!!");
    }
    return false;
}

hkVariableType hkbCharacterData::getCharacterPropertyTypeAt(int index) const{
    if (index < characterPropertyInfos.size() && index >= 0){
        QString type = characterPropertyInfos.at(index).type;
        if (type == "VARIABLE_TYPE_BOOL"){
            return VARIABLE_TYPE_BOOL;
        }else if (type == "VARIABLE_TYPE_INT8"){
            return VARIABLE_TYPE_INT8;
        }else if (type == "VARIABLE_TYPE_INT16"){
            return VARIABLE_TYPE_INT16;
        }else if (type == "VARIABLE_TYPE_INT32"){
            return VARIABLE_TYPE_INT32;
        }else if (type == "VARIABLE_TYPE_REAL"){
            return VARIABLE_TYPE_REAL;
        }else if (type == "VARIABLE_TYPE_POINTER"){
            return VARIABLE_TYPE_POINTER;
        }else if (type == "VARIABLE_TYPE_VECTOR4"){
            return VARIABLE_TYPE_VECTOR4;
        }else if (type == "VARIABLE_TYPE_QUATERNION"){
            return VARIABLE_TYPE_QUATERNION;
        }
    }
    return VARIABLE_TYPE_INT8;
}

bool hkbCharacterData::evaluateDataValidity(){
    if ((!characterPropertyValues.data() || characterPropertyValues.data()->getSignature() != HKB_VARIABLE_VALUE_SET) || (footIkDriverInfo.data() && footIkDriverInfo.data()->getSignature() != HKB_FOOT_IK_DRIVER_INFO) ||
            (handIkDriverInfo.data() && handIkDriverInfo.data()->getSignature() != HKB_HAND_IK_DRIVER_INFO) || (!stringData.data() || stringData.data()->getSignature() != HKB_CHARACTER_STRING_DATA) ||
            (!mirroredSkeletonInfo.data() || mirroredSkeletonInfo.data()->getSignature() != HKB_MIRRORED_SKELETON_INFO))
    {
        setDataValidity(false);
        return false;
    }else {
        //Check other data...
        setDataValidity(true);
        return true;
    }
}

hkbCharacterData::~hkbCharacterData(){
    refCount--;
}
