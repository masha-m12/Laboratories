#include <QGraphicsProxyWidget>

#include "TableElementWidget.h"

#include "SceneHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

SceneHashTableWidget::SceneHashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(this))
{
    m_view->setScene(m_scene);
    ui->verticalLayout->insertWidget(0, m_view);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addKeyValue()
{
    int key = ui->spinBox_key->value();
    // TODO: проверка на повтор ключа
    if (m_hashTable.contains(key)) {
        return;
    }
    // TODO: заменить определение строки, столбца, коллизий
    int size = ui->spinBox_size->value();
    int row = m_hashTable.getHashFunction()->computeHash(key, size);
    int column = 0;

    m_hashTable.add(key, ui->lineEdit_value->text().toStdString());

    if (!m_rows[row][column].widget->isEmpty())
    {
        column = m_rows[row].size();
        addBlankElement(row, column);
    }

    m_rows[row][column].widget->setKey(ui->spinBox_key->value());
    m_rows[row][column].widget->setValue(ui->lineEdit_value->text());

    //item->setFlags(item->flags() | Qt::ItemIsEditable);
}

void SceneHashTableWidget::resizeTable()
{
    // TODO: resize хеш-таблицы
    int newSize = ui->spinBox_size->value();

    m_hashTable.resize(newSize);

    for (auto& row : m_rows) {
        for (ElementData& data : row) {
            m_scene->removeItem(data.proxy);
            data.widget->deleteLater();
        }
    }

    m_rows.clear();
    m_rows.resize(newSize);

    for (int i = 0; i < newSize; ++i)
    {
        addBlankElement(i, 0);
    }
    for (int i = 0; i < newSize; ++i)
    {
        // TODO: заполнить новыми значениями из хеш-таблицы
        // (добавить/удалить элементы коллизий при необходимости)
        const auto& chain = m_hashTable.hashTable()[i];
        int col = 0;

        for (auto it = chain.begin(); it != chain.end(); ++it, ++col)
        {
            if (col > 0)
            {
                addBlankElement(i, col);
            }

            m_rows[i][col].widget->setKey(it->first);
            m_rows[i][col].widget->setValue(QString::fromStdString(it->second));
        }
    }
}

void SceneHashTableWidget::findKey()
{
    int key = ui->spinBox_key->value();

    for (auto& row : m_rows) {
        for (auto& element : row) {
            element.widget->setColor(Qt::white);
        }
    }

    int hash = m_hashTable.getHashFunction()->computeHash(key, m_rows.size());
    auto& chain = m_rows[hash];

    for (auto& element : chain) {
        if (element.widget && element.widget->key() == key) {
            element.widget->setColor(Qt::green);
            return;
        }
    }
}

void SceneHashTableWidget::deleteByKey() {
    int key = ui->spinBox_key->value();
    m_hashTable.remove(key);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::changeFunction(int index) {
    if (index == 0) {
        m_hashTable.setHashFunction(new HashFunctionFirst());
    }
    else if (index == 1) {
        m_hashTable.setHashFunction(new HashFunctionThird());
    }
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addBlankElement(int row, int column)
{
    //m_tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    TableElementWidget *item = new TableElementWidget();
    //item->setTextAlignment(Qt::AlignCenter);
    //item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    connect(item, &TableElementWidget::valueChanged, this, &SceneHashTableWidget::onValueChanged);

    QGraphicsProxyWidget* proxy = m_scene->addWidget(item);
    column = m_rows[row].size();
    int x = column * (item->width() + 50);
    int y = row * item->height();
    proxy->setX(x);
    proxy->setY(y);

    if (column)
    {
        int centerY = item->height() / 2;
        auto* line = m_scene->addLine(-50, centerY, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2 * 3, 0, centerY);
        line->setParentItem(proxy);
    }

    m_rows[row].append({item, proxy});
}
