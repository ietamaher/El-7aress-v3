#ifndef CUSTOMMENUWIDGET_H
#define CUSTOMMENUWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QLabel>

class CustomMenuWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomMenuWidget(const QStringList &options, QWidget *parent = nullptr);

    void moveSelectionUp();
    void moveSelectionDown();
    void selectCurrentItem();

signals:
    void optionSelected(const QString &option);
    void menuClosed();
    void currentItemChanged(const QString &currentItem);

protected:
    void closeEvent(QCloseEvent *event) override;  // Add this line

private:
    QListWidget *m_listWidget;
    QString currentItemText() const;
};

#endif // CUSTOMMENUWIDGET_H


