#include "include/gui/custommenudialog.h"


CustomMenuWidget::CustomMenuWidget(const QStringList &options, QWidget *parent)
    : QWidget(parent), m_listWidget(new QListWidget(this))
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Menu", this));
    layout->addWidget(m_listWidget);

    m_listWidget->addItems(options);
    m_listWidget->setCurrentRow(0);

    // Adjust size and position as needed
    resize(300, 400);
    move(100, 100); // Position the menu appropriately
}

/*void CustomMenuWidget::moveSelectionUp() {
    int currentRow = m_listWidget->currentRow();
    if (currentRow > 0) {
        m_listWidget->setCurrentRow(currentRow - 1);
    }
}

void CustomMenuWidget::moveSelectionDown() {
    int currentRow = m_listWidget->currentRow();
    if (currentRow < m_listWidget->count() - 1) {
        m_listWidget->setCurrentRow(currentRow + 1);
    }
}*/

void CustomMenuWidget::selectCurrentItem() {
    QListWidgetItem *item = m_listWidget->currentItem();
    if (item) {
        emit optionSelected(item->text());
        close(); // Close the menu
        emit menuClosed();
    }
}

void CustomMenuWidget::moveSelectionUp()
{
    int currentRow = m_listWidget->currentRow();
    if (currentRow > 0) {
        m_listWidget->setCurrentRow(currentRow - 1);
    }
    QListWidgetItem *item = m_listWidget->currentItem();
    if (item) {
        emit currentItemChanged(item->text());
    }
}

void CustomMenuWidget::moveSelectionDown()
{
    int currentRow = m_listWidget->currentRow();
    if (currentRow < m_listWidget->count() - 1) {
        m_listWidget->setCurrentRow(currentRow + 1);
    }
    QListWidgetItem *item = m_listWidget->currentItem();
    if (item) {
        emit currentItemChanged(item->text());
    }
}

QString CustomMenuWidget::currentItemText() const
{
    QListWidgetItem *item = m_listWidget->currentItem();
    return item ? item->text() : QString();
}

void CustomMenuWidget::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit menuClosed();
}

