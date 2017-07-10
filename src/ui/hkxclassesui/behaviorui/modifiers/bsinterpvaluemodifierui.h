#ifndef BSINTERPVALUEMODIFIERUI_H
#define BSINTERPVALUEMODIFIERUI_H

#include <QGroupBox>

#include "src/utility.h"

class HkxObject;
class QGridLayout;
class TableWidget;
class BSInterpValueModifier;
class LineEdit;
class QuadVariableWidget;
class CheckBox;
class GenericTableWidget;
class hkbVariableBindingSet;
class DoubleSpinBox;

class BSInterpValueModifierUI: QGroupBox
{
    Q_OBJECT
    friend class HkDataUI;
public:
    BSInterpValueModifierUI();
    virtual ~BSInterpValueModifierUI(){}
    void loadData(HkxObject *data);
signals:
    void viewVariables(int index);
    void viewProperties(int index);
    void modifierNameChanged(const QString & newName, int index);
private slots:
    void setName();
    void setEnable();
    void setSource();
    void setTarget();
    void setResult();
    void setGain();
    void viewSelected(int row, int column);
    void setBindingVariable(int index, const QString & name);
private:
    void connectSignals();
    void disconnectSignals();
    void connectToTables(GenericTableWidget *variables, GenericTableWidget *properties);
    void variableRenamed(const QString & name, int index);
    void selectTableToView(bool viewproperties, const QString & path);
    bool setBinding(int index, int row, const QString & variableName, const QString & path, hkVariableType type, bool isProperty);
    void loadBinding(int row, int colunm, hkbVariableBindingSet *varBind, const QString & path);
private:
    static QStringList headerLabels;
    BSInterpValueModifier *bsData;
    QGridLayout *topLyt;
    TableWidget *table;
    LineEdit *name;
    CheckBox *enable;
    DoubleSpinBox *source;
    DoubleSpinBox *target;
    DoubleSpinBox *result;
    DoubleSpinBox *gain;
};

#endif // BSINTERPVALUEMODIFIERUI_H