#include "widget.h"
#include "weather.h"
#include "settings.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QMenu>
#include <QApplication>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :   QWidget(parent),
                                    mCityLabel(new QLabel),
                                    mCommentLabel(new QLabel),
                                    mTempLabel(new QLabel),
                                    mIconLabel(new QLabel),
                                    mMove(false),
                                    mCityName("Odesa"),
                                    mStyle("Dark"),
                                    mMinutes(60),
                                    mPositionMouse(0,0),
                                    mTimer(new QTimer)
{
    readSettings();
    setStyleWidget();

    QVBoxLayout *pVBLayout = new QVBoxLayout;
    pVBLayout->addWidget(mCityLabel);
    pVBLayout->addWidget(mCommentLabel);
    QFormLayout *pFLayout = new QFormLayout;
    pFLayout->addRow(mTempLabel, mIconLabel);
    pVBLayout->addLayout(pFLayout);

    setLayout(pVBLayout);

    connect(mTimer, SIGNAL(timeout()), SLOT(slotTimer()));
    mTimer->start(minutesToMilliseconds());

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint | Qt::Tool);

    getWeather();
}

void Widget::getWeather()
{
    Weather weather;
    weather.connectWeather(mCityName.toStdString());
    mCityLabel->setText(QString::fromStdString(weather.getCity()));
    mCommentLabel->setText(QString::fromStdString(weather.getComment()));
    mTempLabel->setText(QString::fromStdString(weather.getTemp()));
    QPixmap pix("icon.png");
    mIconLabel->setPixmap(pix);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu *menu = new QMenu(this);
        menu->addAction("&Settings..", this, SLOT(slotSettings()));
        menu->addAction("&Update", this, SLOT(slotUpdate()));
        menu->addAction("&About", this, SLOT(slotAbout()));
        menu->addSeparator();
        menu->addAction("&Exit", qApp, SLOT(quit()));
        menu->exec(event->globalPos());
    }
    if(event->button() == Qt::LeftButton)
    {
        mMove = true;
        mPositionMouse = event->pos();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && mMove)
        mMove = false;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if((event->buttons() & Qt::LeftButton) && mMove)
        move(event->globalPos() - mPositionMouse);
}

void Widget::slotUpdate()
{
    getWeather();
}

void Widget::slotTimer()
{
    getWeather();
}

void Widget::slotAbout()
{
    QMessageBox::about(0, "About", "Weather ver. 1.0\nAuthor Kylchitskyi Roman\ne-mail: roma1985@ukr.net");
}

void Widget::slotSettings()
{
    Settings settingsDialog(mCityName, mStyle, mMinutes);
    if(settingsDialog.exec() == QDialog::Accepted)
    {
        if(mCityName != settingsDialog.getCity())
        {
            mCityName = settingsDialog.getCity();
            getWeather();
        }
        if(mStyle != settingsDialog.getStyle())
        {
            mStyle = settingsDialog.getStyle();
            setStyleWidget();
        }
        if(mMinutes != settingsDialog.getMinutes())
        {
            mMinutes = settingsDialog.getMinutes();
            mTimer->start(minutesToMilliseconds());
        }
    }
}

unsigned Widget::minutesToMilliseconds() const
{
    return mMinutes * 1000*60;
}

void Widget::setStyleWidget()
{
    if((mStyle == "Dark") || (mStyle == "Light"))
    {
        QFile file("./Style" + mStyle + ".css");
        file.open(QFile::ReadOnly);
        QString strCSS = QLatin1String(file.readAll());
        setStyleSheet(strCSS);
    }
}

void Widget::writeSettings()
{
    QPoint positionWidget = mapToGlobal(QPoint(0, 0));
    mSettings.beginGroup("/Settings");
        mSettings.setValue("/city", mCityLabel->text());
        mSettings.setValue("/temp", mTempLabel->text());
        mSettings.setValue("/comment", mCommentLabel->text());
        mSettings.setValue("/position", positionWidget);
        mSettings.setValue("/style", mStyle);
        mSettings.setValue("/minutes", mMinutes);
    mSettings.endGroup();
}

void Widget::readSettings()
{
    QString str;
    mSettings.beginGroup("/Settings");
        str = mSettings.value("/city", mCityName).toString();
        mCityLabel->setText(str);

        str = mSettings.value("/temp", "").toString();
        mTempLabel->setText(str);

        str = mSettings.value("/comment", "").toString();
        mCommentLabel->setText(str);

        QPoint positionWidget = mSettings.value("/position", mapToGlobal(QPoint(0, 0))).toPoint();
        mStyle = mSettings.value("/style", mStyle).toString();
        move(positionWidget);

        mMinutes = mSettings.value("/minutes").toUInt();
    mSettings.endGroup();
}

 Widget::~Widget()
{
    writeSettings();
}
