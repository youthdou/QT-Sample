#include "completelineedit.h"
#include <QKeyEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>

CompleteLineEdit::CompleteLineEdit(QStringList listWords, QWidget *parent)
    : QLineEdit(parent),
      m_listWords(listWords)
{
    m_pListView = new QListView(this);
    m_pModel = new QStringListModel(this);
    m_pListView->setWindowFlags(Qt::ToolTip);

    connect(this, SIGNAL(textChanged(const QString &)),
            this, SLOT(setCompleter(const QString &)));
    connect(m_pListView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(completeText(const QModelIndex &)));
}

void CompleteLineEdit::focusOutEvent(QFocusEvent *e)
{
    Q_UNUSED(e);
    m_pListView->hide();
}

void CompleteLineEdit::moveEvent(QMoveEvent *e)
{
    qDebug() << "[" << __FUNCTION__ << "]";
}

void CompleteLineEdit::keyPressEvent(QKeyEvent *e)
{
    if (!m_pListView->isHidden())
    {
        int key = e->key();
        int count = m_pListView->model()->rowCount();
        QModelIndex currentIndex = m_pListView->currentIndex();
        if (Qt::Key_Down == key)
        {
            // 按向下方向键时，移动光标选中下一个完成列表中的项
            int row = currentIndex.row() + 1;
            if (row >= count)
            {
                row = 0;
            }
            QModelIndex index = m_pListView->model()->index(row, 0);
            m_pListView->setCurrentIndex(index);
        }
        else if (Qt::Key_Up == key)
        {
            // 按向下方向键时，移动光标选中上一个完成列表中的项
            int row = currentIndex.row() - 1;
            if (row < 0) {
                row = count - 1;
            }
            QModelIndex index = m_pListView->model()->index(row, 0);
            m_pListView->setCurrentIndex(index);
        }
        else if (Qt::Key_Escape == key)
        {
            // 按下Esc键时，隐藏完成列表
            m_pListView->hide();
        }
        else if (Qt::Key_Enter == key || Qt::Key_Return == key)
        {
            // 按下回车键时，使用完成列表中选中的项，并隐藏完成列表
            if (currentIndex.isValid())
            {
                QString text = m_pListView->currentIndex().data().toString();
                setText(text);
            }
            m_pListView->hide();
        }
        else
        {
            // 其他情况，隐藏完成列表，并使用QLineEdit的键盘按下事件
            m_pListView->hide();
            QLineEdit::keyPressEvent(e);
        }
    } else {
        QLineEdit::keyPressEvent(e);
    }
}

void CompleteLineEdit::setCompleter(const QString &text)
{
    if (text.isEmpty())
    {
        m_pListView->hide();
        return;
    }
    if ((text.length() > 1) && (!m_pListView->isHidden()))
    {
        return;
    }
    // 如果完整的完成列表中的某个单词包含输入的文本，则加入要显示的完成列表串中
    QStringList sl;
    foreach(QString word, m_listWords)
    {
        if(word.contains(text))
        {
            sl << word;
        }
    }
    m_pModel->setStringList(sl);
    m_pListView->setModel(m_pModel);
    if(m_pModel->rowCount() == 0)
    {
        return;
    }

    // Position the text edit
    m_pListView->setMinimumWidth(width());
    m_pListView->setMaximumWidth(width());
    QPoint p(0, height());
    int x = mapToGlobal(p).x();
    int y = mapToGlobal(p).y() + 1;
    m_pListView->move(x, y);
    m_pListView->show();
}

void CompleteLineEdit::completeText(const QModelIndex &index)
{
    QString text = index.data().toString();
    setText(text);
    m_pListView->hide();
}

