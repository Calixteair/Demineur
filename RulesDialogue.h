#ifndef RULESDIALOG_H
#define RULESDIALOG_H

#include <QDialog>

class QTextBrowser;

class RulesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RulesDialog(QWidget *parent = nullptr);

private:
    QTextBrowser *rulesTextBrowser;
};

#endif // RULESDIALOG_H