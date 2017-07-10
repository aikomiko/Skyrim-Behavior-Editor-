#include "extractragdollposemodifierui.h"

#include "src/hkxclasses/behavior/modifiers/hkbExtractRagdollPoseModifier.h"
#include "src/hkxclasses/behavior/hkbvariablebindingset.h"
#include "src/filetypes/behaviorfile.h"
#include "src/ui/genericdatawidgets.h"

#include <QGridLayout>
#include <QHeaderView>

#define BASE_NUMBER_OF_ROWS 6

#define NAME_ROW 0
#define ENABLE_ROW 1
#define POSE_MATCHING_BONE_0_ROW 2
#define POSE_MATCHING_BONE_1_ROW 3
#define POSE_MATCHING_BONE_2_ROW 4
#define ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW 5

#define NAME_COLUMN 0
#define TYPE_COLUMN 1
#define BINDING_COLUMN 2
#define VALUE_COLUMN 3

#define BINDING_ITEM_LABEL QString("Use Property     ")

QStringList ExtractRagdollPoseModifierUI::headerLabels = {
    "Name",
    "Type",
    "Bound Variable",
    "Value"
};

ExtractRagdollPoseModifierUI::ExtractRagdollPoseModifierUI()
    : bsData(NULL),
      topLyt(new QGridLayout),
      table(new TableWidget(QColor(Qt::white))),
      name(new LineEdit),
      enable(new CheckBox),
      poseMatchingBone0(new ComboBox),
      poseMatchingBone1(new ComboBox),
      poseMatchingBone2(new ComboBox),
      enableComputeWorldFromModel(new CheckBox)
{
    setTitle("hkbExtractRagdollPoseModifier");
    table->setRowCount(BASE_NUMBER_OF_ROWS);
    table->setColumnCount(headerLabels.size());
    table->setHorizontalHeaderLabels(headerLabels);
    table->setItem(NAME_ROW, NAME_COLUMN, new TableWidgetItem("name"));
    table->setItem(NAME_ROW, TYPE_COLUMN, new TableWidgetItem("hkStringPtr", Qt::AlignCenter));
    table->setItem(NAME_ROW, BINDING_COLUMN, new TableWidgetItem("N/A", Qt::AlignCenter));
    table->setCellWidget(NAME_ROW, VALUE_COLUMN, name);
    table->setItem(ENABLE_ROW, NAME_COLUMN, new TableWidgetItem("enable"));
    table->setItem(ENABLE_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(ENABLE_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(ENABLE_ROW, VALUE_COLUMN, enable);
    table->setItem(POSE_MATCHING_BONE_0_ROW, NAME_COLUMN, new TableWidgetItem("poseMatchingBone0"));
    table->setItem(POSE_MATCHING_BONE_0_ROW, TYPE_COLUMN, new TableWidgetItem("hkInt32", Qt::AlignCenter));
    table->setItem(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(POSE_MATCHING_BONE_0_ROW, VALUE_COLUMN, poseMatchingBone0);
    table->setItem(POSE_MATCHING_BONE_1_ROW, NAME_COLUMN, new TableWidgetItem("poseMatchingBone1"));
    table->setItem(POSE_MATCHING_BONE_1_ROW, TYPE_COLUMN, new TableWidgetItem("hkInt32", Qt::AlignCenter));
    table->setItem(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(POSE_MATCHING_BONE_1_ROW, VALUE_COLUMN, poseMatchingBone1);
    table->setItem(POSE_MATCHING_BONE_2_ROW, NAME_COLUMN, new TableWidgetItem("poseMatchingBone2"));
    table->setItem(POSE_MATCHING_BONE_2_ROW, TYPE_COLUMN, new TableWidgetItem("hkInt32", Qt::AlignCenter));
    table->setItem(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(POSE_MATCHING_BONE_2_ROW, VALUE_COLUMN, poseMatchingBone2);
    table->setItem(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, NAME_COLUMN, new TableWidgetItem("enableComputeWorldFromModel"));
    table->setItem(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, TYPE_COLUMN, new TableWidgetItem("hkBool", Qt::AlignCenter));
    table->setItem(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN, new TableWidgetItem(BINDING_ITEM_LABEL+"NONE", Qt::AlignLeft | Qt::AlignVCenter, QColor(Qt::lightGray), QBrush(Qt::black), VIEW_VARIABLES_TABLE_TIP, true));
    table->setCellWidget(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, VALUE_COLUMN, enableComputeWorldFromModel);
    topLyt->addWidget(table, 0, 0, 8, 3);
    setLayout(topLyt);
}

void ExtractRagdollPoseModifierUI::connectSignals(){
    connect(name, SIGNAL(editingFinished()), this, SLOT(setName()), Qt::UniqueConnection);
    connect(enable, SIGNAL(released()), this, SLOT(setEnable()), Qt::UniqueConnection);
    connect(poseMatchingBone0, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone0(int)), Qt::UniqueConnection);
    connect(poseMatchingBone1, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone1(int)), Qt::UniqueConnection);
    connect(poseMatchingBone2, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone2(int)), Qt::UniqueConnection);
    connect(enableComputeWorldFromModel, SIGNAL(released()), this, SLOT(setEnableComputeWorldFromModel()), Qt::UniqueConnection);
    connect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)), Qt::UniqueConnection);
}

void ExtractRagdollPoseModifierUI::disconnectSignals(){
    disconnect(name, SIGNAL(editingFinished()), this, SLOT(setName()));
    disconnect(enable, SIGNAL(released()), this, SLOT(setEnable()));
    disconnect(poseMatchingBone0, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone0(int)));
    disconnect(poseMatchingBone1, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone1(int)));
    disconnect(poseMatchingBone2, SIGNAL(currentIndexChanged(int)), this, SLOT(setPoseMatchingBone2(int)));
    disconnect(enableComputeWorldFromModel, SIGNAL(released()), this, SLOT(setEnableComputeWorldFromModel()));
    disconnect(table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(viewSelected(int,int)));
}

void ExtractRagdollPoseModifierUI::connectToTables(GenericTableWidget *variables, GenericTableWidget *properties){
    if (variables && properties){
        disconnect(variables, SIGNAL(elementSelected(int,QString)), 0, 0);
        disconnect(properties, SIGNAL(elementSelected(int,QString)), 0, 0);
        connect(variables, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(properties, SIGNAL(elementSelected(int,QString)), this, SLOT(setBindingVariable(int,QString)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewVariables(int)), variables, SLOT(showTable(int)), Qt::UniqueConnection);
        connect(this, SIGNAL(viewProperties(int)), properties, SLOT(showTable(int)), Qt::UniqueConnection);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::connectToTables(): One or more arguments are NULL!!"))
    }
}

void ExtractRagdollPoseModifierUI::loadData(HkxObject *data){
    disconnectSignals();
    if (data){
        if (data->getSignature() == HKB_EXTRACT_RAGDOLL_POSE_MODIFIER){
            QStringList boneNames("None");
            hkbVariableBindingSet *varBind = NULL;
            bsData = static_cast<hkbExtractRagdollPoseModifier *>(data);
            name->setText(bsData->name);
            enable->setChecked(bsData->enable);
            if (poseMatchingBone0->count() == 0){
                boneNames = boneNames + static_cast<BehaviorFile *>(bsData->getParentFile())->getRigBoneNames();
                poseMatchingBone0->insertItems(0, boneNames);
            }
            poseMatchingBone0->setCurrentIndex(bsData->poseMatchingBone0 + 1);
            if (poseMatchingBone1->count() == 0){
                boneNames = boneNames + static_cast<BehaviorFile *>(bsData->getParentFile())->getRigBoneNames();
                poseMatchingBone1->insertItems(0, boneNames);
            }
            poseMatchingBone1->setCurrentIndex(bsData->poseMatchingBone1 + 1);
            if (poseMatchingBone2->count() == 0){
                boneNames = boneNames + static_cast<BehaviorFile *>(bsData->getParentFile())->getRigBoneNames();
                poseMatchingBone2->insertItems(0, boneNames);
            }
            poseMatchingBone2->setCurrentIndex(bsData->poseMatchingBone2 + 1);
            enableComputeWorldFromModel->setChecked(bsData->enableComputeWorldFromModel);
            varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
            if (varBind){
                loadBinding(ENABLE_ROW, BINDING_COLUMN, varBind, "enable");
                loadBinding(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN, varBind, "poseMatchingBone0");
                loadBinding(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN, varBind, "poseMatchingBone1");
                loadBinding(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN, varBind, "poseMatchingBone2");
                loadBinding(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN, varBind, "enableComputeWorldFromModel");
            }else{
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
                table->item(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
            }
        }else{
            CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::loadData(): The data is an incorrect type!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::loadData(): The data is NULL!!"));
    }
    connectSignals();
}

void ExtractRagdollPoseModifierUI::setName(){
    if (bsData){
        if (bsData->name != name->text()){
            bsData->name = name->text();
            static_cast<DataIconManager*>((bsData))->updateIconNames();
            bsData->getParentFile()->toggleChanged(true);
            emit modifierNameChanged(name->text(), static_cast<BehaviorFile *>(bsData->getParentFile())->getIndexOfModifier(bsData));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setName(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::setEnable(){
    if (bsData){
        if (bsData->enable != enable->isChecked()){
            bsData->enable = enable->isChecked();
            bsData->getParentFile()->toggleChanged(true);
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setEnable(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::setPoseMatchingBone0(int index){
    if (bsData){
        bsData->poseMatchingBone0 = index - 1;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setposeMatchingBone0(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::setPoseMatchingBone1(int index){
    if (bsData){
        bsData->poseMatchingBone1 = index - 1;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setposeMatchingBone1(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::setPoseMatchingBone2(int index){
    if (bsData){
        bsData->poseMatchingBone2 = index - 1;
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setposeMatchingBone2(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::setEnableComputeWorldFromModel(){
    if (bsData){
        if (bsData->enableComputeWorldFromModel != enableComputeWorldFromModel->isChecked()){
            bsData->enableComputeWorldFromModel = enableComputeWorldFromModel->isChecked();
            bsData->getParentFile()->toggleChanged(true);
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setenableComputeWorldFromModel(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::viewSelected(int row, int column){
    if (bsData){
        bool isProperty = false;
        if (column == BINDING_COLUMN){
            switch (row){
            case ENABLE_ROW:
                if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "enable");
                break;
            case POSE_MATCHING_BONE_0_ROW:
                if (table->item(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "poseMatchingBone0");
                break;
            case POSE_MATCHING_BONE_1_ROW:
                if (table->item(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "poseMatchingBone1");
                break;
            case POSE_MATCHING_BONE_2_ROW:
                if (table->item(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "poseMatchingBone2");
                break;
            case ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW:
                if (table->item(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                    isProperty = true;
                }
                selectTableToView(isProperty, "enableComputeWorldFromModel");
                break;
            default:
                return;
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::viewSelected(): The 'bsData' pointer is NULL!!"))
    }
}

void ExtractRagdollPoseModifierUI::selectTableToView(bool viewisProperty, const QString & path){
    if (bsData){
        if (viewisProperty){
            if (bsData->variableBindingSet.data()){
                emit viewProperties(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewProperties(0);
            }
        }else{
            if (bsData->variableBindingSet.data()){
                emit viewVariables(static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data())->getVariableIndexOfBinding(path) + 1);
            }else{
                emit viewVariables(0);
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::selectTableToView(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::variableRenamed(const QString & name, int index){
    if (bsData){
        index--;
        hkbVariableBindingSet *bind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
        if (bind){
            int bindIndex = bind->getVariableIndexOfBinding("enable");
            if (bindIndex == index){
                table->item(ENABLE_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("poseMatchingBone0");
            if (bindIndex == index){
                table->item(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("poseMatchingBone1");
            if (bindIndex == index){
                table->item(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("poseMatchingBone2");
            if (bindIndex == index){
                table->item(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN)->setText(name);
            }
            bindIndex = bind->getVariableIndexOfBinding("enableComputeWorldFromModel");
            if (bindIndex == index){
                table->item(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN)->setText(name);
            }
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::variableRenamed(): The 'bsData' pointer is NULL!!"))
    }
}

bool ExtractRagdollPoseModifierUI::setBinding(int index, int row, const QString &variableName, const QString &path, hkVariableType type, bool isProperty){
    hkbVariableBindingSet *varBind = static_cast<hkbVariableBindingSet *>(bsData->variableBindingSet.data());
    if (bsData){
        if (index == 0){
            varBind->removeBinding(path);
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+"NONE");
        }else if ((!isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableTypeAt(index - 1) == type) ||
                  (isProperty && static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyTypeAt(index - 1) == type)){
            if (!varBind){
                varBind = new hkbVariableBindingSet(bsData->getParentFile());
                bsData->variableBindingSet = HkxSharedPtr(varBind);
            }
            if (isProperty){
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY)){
                    CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }else{
                if (!varBind->addBinding(path, variableName, index - 1, hkbVariableBindingSet::hkBinding::BINDING_TYPE_VARIABLE)){
                    CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setBinding(): The attempt to add a binding to this object's hkbVariableBindingSet failed!!"));
                }
            }
            table->item(row, BINDING_COLUMN)->setText(BINDING_ITEM_LABEL+variableName);
            bsData->getParentFile()->toggleChanged(true);
        }else{
            WARNING_MESSAGE(QString("I'M SORRY HAL BUT I CAN'T LET YOU DO THAT.\n\nYou are attempting to bind a variable of an invalid type for this data field!!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setBinding(): The data is NULL!!"));
    }
    return true;
}

void ExtractRagdollPoseModifierUI::setBindingVariable(int index, const QString &name){
    if (bsData){
        bool isProperty = false;
        int row = table->currentRow();
        switch (row){
        case ENABLE_ROW:
            if (table->item(ENABLE_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "enable", VARIABLE_TYPE_BOOL, isProperty);
            break;
        case POSE_MATCHING_BONE_0_ROW:
            if (table->item(POSE_MATCHING_BONE_0_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "poseMatchingBone0", VARIABLE_TYPE_INT32, isProperty);
            break;
        case POSE_MATCHING_BONE_1_ROW:
            if (table->item(POSE_MATCHING_BONE_1_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "poseMatchingBone1", VARIABLE_TYPE_INT32, isProperty);
            break;
        case POSE_MATCHING_BONE_2_ROW:
            if (table->item(POSE_MATCHING_BONE_2_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "poseMatchingBone2", VARIABLE_TYPE_INT32, isProperty);
            break;
        case ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW:
            if (table->item(ENABLE_COMPUTE_WORLD_FROM_MODEL_ROW, BINDING_COLUMN)->checkState() != Qt::Unchecked){
                isProperty = true;
            }
            setBinding(index, row, name, "enableComputeWorldFromModel", VARIABLE_TYPE_BOOL, isProperty);
            break;
        default:
            return;
        }
        bsData->getParentFile()->toggleChanged(true);
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::setBindingVariable(): The data is NULL!!"));
    }
}

void ExtractRagdollPoseModifierUI::loadBinding(int row, int colunm, hkbVariableBindingSet *varBind, const QString &path){
    if (bsData){
        if (varBind){
            int index = varBind->getVariableIndexOfBinding(path);
            QString varName;
            if (index != -1){
                if (varBind->getBindingType(path) == hkbVariableBindingSet::hkBinding::BINDING_TYPE_CHARACTER_PROPERTY){
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getCharacterPropertyNameAt(index, true);
                    table->item(row, colunm)->setCheckState(Qt::Checked);
                }else{
                    varName = static_cast<BehaviorFile *>(bsData->getParentFile())->getVariableNameAt(index);
                }
                if (varName == ""){
                    varName = "NONE";
                }
                table->item(row, colunm)->setText(BINDING_ITEM_LABEL+varName);
            }
        }else{
            CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::loadBinding(): The variable binding set is NULL!!"));
        }
    }else{
        CRITICAL_ERROR_MESSAGE(QString("ExtractRagdollPoseModifierUI::loadBinding(): The data is NULL!!"));
    }
}