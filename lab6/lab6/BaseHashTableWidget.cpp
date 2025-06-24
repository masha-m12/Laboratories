#include "BaseHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

BaseHashTableWidget::BaseHashTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseHashTableWidget)
{
    ui->setupUi(this);
    connect(ui->spinBox_size, &QSpinBox::editingFinished, this, &BaseHashTableWidget::resizeTable);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &BaseHashTableWidget::addKeyValue);
    connect(ui->pushButton_find, &QPushButton::clicked, this, &BaseHashTableWidget::findKey);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &BaseHashTableWidget::deleteByKey);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &BaseHashTableWidget::changeFunction);
}

BaseHashTableWidget::~BaseHashTableWidget()
{
    delete ui;
}

void BaseHashTableWidget::onValueChanged(int key, const QString &value)
{
//    value.toStdString()
    // TODO: записать новое значение в хеш-таблицу
    m_hashTable[key] = value.toStdString();
}
