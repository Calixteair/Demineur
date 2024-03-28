// ModifyProfileDialog.h
#ifndef MODIFYPROFILEDIALOG_H
#define MODIFYPROFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

class ModifyProfileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyProfileDialog(QWidget *parent = nullptr);

signals:
    void profileModified(const QString &name, const QString &avatarPath);

private slots:
    void handleAvatarButtonClicked();

private:
    QLineEdit *nameLineEdit;
    QLabel *avatarLabel;
    QPushButton *avatarButton;
    QPushButton *saveButton;
    QPushButton *cancelButton;
};

#endif // MODIFYPROFILEDIALOG_H
