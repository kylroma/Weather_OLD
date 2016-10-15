#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QSettings>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void slotSettings();
    void slotUpdate();
    void slotAbout();
    void slotTimer();
private:
    QLabel *mCityLabel;
    QLabel *mTempLabel;
    QLabel *mCommentLabel;
    QLabel *mIconLabel;
    QString mCityName;
    QString mStyle;
    QPoint mPositionMouse;
    QSettings mSettings;
    QTimer *mTimer;
    unsigned mMinutes;
    bool mMove;

    void getWeather();
    void setStyleWidget();
    void writeSettings();
    void readSettings();
    unsigned minutesToMilliseconds() const;
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
};

#endif // WIDGET_H
