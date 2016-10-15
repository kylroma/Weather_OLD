#include "settings.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QTabWidget>

Settings::Settings(QString city, QString style, unsigned minutes,  QWidget *parent) : QDialog(parent,
                                                                                         Qt::WindowTitleHint |
                                                                                         Qt::WindowSystemMenuHint),
                                                                                  mCityLine(new QLineEdit(city)),
                                                                                  mStyle(new QComboBox),
                                                                                  mMinutes(new QSpinBox)

{
    //first page
    QLabel *minutesLabel = new QLabel("minutes");
    QLabel *updateLabel = new QLabel("&Update every");
    mMinutes->setValue(minutes);
    updateLabel->setBuddy(mMinutes);
    //second page
    mStyle->addItem("Light");
    mStyle->addItem("Dark");
    mStyle->setCurrentText(style);
    //##################
    QPushButton *ok = new QPushButton("&Ok");
    QPushButton *cancel = new QPushButton("&Cancel");

    connect(ok, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(cancel, SIGNAL(clicked(bool)), SLOT(reject()));

    QGridLayout *pWeatherLayout = new QGridLayout;
    pWeatherLayout->addWidget(mCityLine, 0, 0, 1, 3);
    pWeatherLayout->addWidget(updateLabel, 1, 0);
    pWeatherLayout->addWidget(mMinutes, 1, 1);
    pWeatherLayout->addWidget(minutesLabel, 1, 2);
    QWidget *wgtWeather = new QWidget;
    wgtWeather->setLayout(pWeatherLayout);

    QVBoxLayout *pStyleLayout = new QVBoxLayout;
    pStyleLayout->addWidget(mStyle);
    QWidget *wgtStyle = new QWidget;
    wgtStyle->setLayout(pStyleLayout);

    QTabWidget *tab = new QTabWidget;
    tab->addTab(wgtWeather, "&Weather");
    tab->addTab(wgtStyle, "&Style");

    QFormLayout *pfLayout = new QFormLayout;
    pfLayout->addRow(tab);
    pfLayout->addRow(ok, cancel);
    setLayout(pfLayout);
}

QString Settings::getCity() const
{
    return mCityLine->text();
}

QString Settings::getStyle() const
{
    return mStyle->currentText();
}

unsigned Settings::getMinutes() const
{
    return mMinutes->value();
}
