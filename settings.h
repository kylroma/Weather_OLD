#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QString city, QString style, unsigned minutes, QWidget *parent = 0);

    QString getCity() const;
    QString getStyle() const;
    unsigned getMinutes() const;
private:
    QLineEdit *mCityLine;
    QComboBox *mStyle;
    QSpinBox *mMinutes;
};

#endif // SETTINGS_H
