#ifndef AECIUMO_H
#define AECIUMO_H

#include "qssReader.h"
#include "connectInternet.h"
#include <QLine>
#include <QCheckBox>
#include <QToolBox>
#include <QLineEdit>
#include <QComboBox>
#include <QToolButton>
#include <QLabel>
#include <QBitmap>
#include <QPainter>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

class Aeciumo : public QWidget
{
	Q_OBJECT

private:
	QPixmap *butterfly, background;
	QPoint pos_Range;
    QToolButton *button_settings, *button_minimum, *button_close, *button_login;
	QComboBox *comboBox_id;
    QLineEdit *lineEdit_password;
    QCheckBox *checkBox_remember, *checkBox_auto_login;
    QString path_lib;
    QStringList argumentList;
    QProcess *process;
    QTimer *timer;
    ConnectInternet *connectInternet;
    NetworkState *networkState;
	int m_width, m_height, horizontalSpacing;
    bool isPressedMouse, state_login;

private slots:
    void setRemember();
    void setAutoLogin();
    void clearComboBoxText();
	void settings();
    void minimum();
    void on_button_login_clicked();
    void checkState();
	void quit();

public:
	Aeciumo(QWidget *parent = 0);
	~Aeciumo();
	void initUi();
    void initLib();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *);
    QPixmap setBackgroundMask(QPixmap background);
    void login();
    void logout();
};

#endif // AECIUMO_H
