#include "aeciumo.h"
#include <QApplication>

Aeciumo::Aeciumo(QWidget *parent) : QWidget(parent)
{
    state_login = false;
    process = new QProcess(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkState()));
    timer->start(8000);
    networkState = new NetworkState();
    initUi();
    initLib();
}

Aeciumo::~Aeciumo()
{
    delete butterfly;
    delete button_settings;
    delete button_minimum;
    delete button_close;
    delete button_login;
    delete comboBox_id;
    delete lineEdit_password;
    delete checkBox_remember;
    delete checkBox_auto_login;
    delete connectInternet;
}

void Aeciumo::initUi()
{
    setWindowTitle("Aeciumo");
    setWindowIcon(QIcon(":/img/logo"));
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    m_width = 330;
    m_height = 300;
    horizontalSpacing = 15;
    isPressedMouse = false;
    setGeometry(QApplication::desktop()->screenGeometry().width() / 2 - m_width / 2 - 95, QApplication::desktop()->screenGeometry().height() / 2 - m_height / 2 - 83, m_width, m_height); // 需重新调整

    // [BACKGROUND]
    background = setBackgroundMask(QPixmap(":/img/background"));
    QLabel *label_background = new QLabel(this);
    label_background->setPixmap(background);
    label_background->setGeometry(95, 83, background.width(), background.height());
    QGraphicsDropShadowEffect *dropShadowEffect_background = new QGraphicsDropShadowEffect(this);
    dropShadowEffect_background->setOffset(0, 0);
    dropShadowEffect_background->setBlurRadius(7);
    dropShadowEffect_background->setColor(QColor(0, 0, 0, 210));
    label_background->setGraphicsEffect(dropShadowEffect_background);
    // [BACKGROUND]

    // [BUTTERFLY]
    butterfly = new QPixmap(":/img/butterfly");
    QLabel *label_butterfly = new QLabel(this);
    label_butterfly->setPixmap(*butterfly);
    label_butterfly->setGeometry(21, 10, butterfly->width(), butterfly->height());
    QGraphicsDropShadowEffect *dropShadowEffect_butterfly = new QGraphicsDropShadowEffect(this);
    dropShadowEffect_butterfly->setOffset(-2, 4);
    dropShadowEffect_butterfly->setBlurRadius(30);
    dropShadowEffect_butterfly->setColor(QColor(0, 0, 0, 200));
    label_butterfly->setGraphicsEffect(dropShadowEffect_butterfly);
    // [BUTTERFLY]

    // [TITLE]
    QLabel *label_title = new QLabel(this);
    label_title->setText(windowTitle());
    label_title->setGeometry(157, 86, 55, 13);
    QGraphicsDropShadowEffect *dropShadowEffect_title = new QGraphicsDropShadowEffect(this);
    dropShadowEffect_title->setOffset(0, 0);
    dropShadowEffect_title->setBlurRadius(8);
    dropShadowEffect_title->setColor(QColor(0, 0, 0, 255));
    label_title->setGraphicsEffect(dropShadowEffect_title);
    QString styleSheet_label_title = QssReader(":/qss/styleSheet_label_title").getQssData();
    label_title->setStyleSheet(styleSheet_label_title);
    // [TITLE]

    // [BUTTON_SETTINGS]
    button_settings = new QToolButton(this);
    button_settings->setText("");
    button_settings->setGeometry(230, 82, 28, 20);
    QString styleSheet_button_settings = QssReader(":/qss/styleSheet_button_settings").getQssData();
    button_settings->setStyleSheet(styleSheet_button_settings);
    connect(button_settings, SIGNAL(clicked()), this, SLOT(settings()));
    // [BUTTON_SETTINGS]

    // [BUTTON_MINIMUM]
    button_minimum = new QToolButton(this);
    button_minimum->setText("");
    button_minimum->setGeometry(button_settings->x() + button_settings->width(), button_settings->y(), 28, 20);
    QString styleSheet_button_minimum = QssReader(":/qss/styleSheet_button_minimum").getQssData();
    button_minimum->setStyleSheet(styleSheet_button_minimum);
    connect(button_minimum, SIGNAL(clicked()), this, SLOT(minimum()));
    // [BUTTON_MINIMUM]

    // [BUTTON_CLOSE]
    button_close = new QToolButton(this);
    button_close->setText("");
    button_close->setGeometry(button_minimum->x() + button_minimum->width(), button_minimum->y(), 39, 20);
    QString styleSheet_button_close = QssReader(":/qss/styleSheet_button_close").getQssData();
    button_close->setStyleSheet(styleSheet_button_close);
    connect(button_close, SIGNAL(clicked()), this, SLOT(quit()));
    // [BUTTON_CLOSE]

    // [COMBOBOX_ID]
    comboBox_id = new QComboBox(this);
    comboBox_id->setEditable(true);
    comboBox_id->setFocus();
    comboBox_id->setGeometry(116, 121, 190, 30);
    QString styleSheet_comboBox_id = QssReader(":/qss/styleSheet_comboBox_id").getQssData();
    comboBox_id->setStyleSheet(styleSheet_comboBox_id);
    QStringList list_savedId;
    list_savedId.append("1040112115");
    list_savedId.append("1030804135");
    list_savedId.append("126021100363");
    comboBox_id->addItems(list_savedId);
    for(int i = 0; i < comboBox_id->count(); i++)
        comboBox_id->setItemData(i, QSize(10, 25), Qt::SizeHintRole);
    // [COMBOBOX_ID]

    // [LINEEDIT_PASSWORD]
    lineEdit_password = new QLineEdit(this);
    lineEdit_password->setGeometry(comboBox_id->x(), comboBox_id->y() + comboBox_id->height() + horizontalSpacing, comboBox_id->width(), comboBox_id->height());
    lineEdit_password->setEchoMode(QLineEdit::Password);
    lineEdit_password->setAlignment(Qt::AlignVCenter);
    QString styleSheet_lineEdit_password = QssReader(":/qss/styleSheet_lineEdit_password").getQssData();
    lineEdit_password->setStyleSheet(styleSheet_lineEdit_password);
    // [LINEEDIT_PASSWORD]

    // [CHECKBOX_REMEMBER]
    checkBox_remember = new QCheckBox(this);
    checkBox_remember->setText("Remember");
    checkBox_remember->setGeometry(lineEdit_password->x(), lineEdit_password->y() + lineEdit_password->height() + horizontalSpacing, 130, 22);
    QString styleSheet_checkBox = QssReader(":/qss/styleSheet_checkBox").getQssData();
    checkBox_remember->setStyleSheet(styleSheet_checkBox);
    QGraphicsDropShadowEffect *dropShadowEffect_checkBox_remember = new QGraphicsDropShadowEffect(this);
    dropShadowEffect_checkBox_remember->setOffset(0, 0);
    dropShadowEffect_checkBox_remember->setBlurRadius(10);
    dropShadowEffect_checkBox_remember->setColor(QColor(0, 0, 0, 255));
    checkBox_remember->setGraphicsEffect(dropShadowEffect_checkBox_remember);
    connect(checkBox_remember, SIGNAL(stateChanged(int)), this, SLOT(setRemember()));
    // [CHECKBOX_REMEMBER]

    // [CHECKBOX_AUTOLOGIN]
    checkBox_auto_login = new QCheckBox(this);
    checkBox_auto_login->setText("Auto Login");
    checkBox_auto_login->setGeometry(checkBox_remember->x() + 102, checkBox_remember->y(), checkBox_remember->width(), checkBox_remember->height());
    checkBox_auto_login->setStyleSheet(styleSheet_checkBox);
    QGraphicsDropShadowEffect *dropShadowEffect_checkBox_auto_login = new QGraphicsDropShadowEffect(this);
    dropShadowEffect_checkBox_auto_login->setOffset(0, 0);
    dropShadowEffect_checkBox_auto_login->setBlurRadius(10);
    dropShadowEffect_checkBox_auto_login->setColor(QColor(0, 0, 0, 130));
    checkBox_auto_login->setGraphicsEffect(dropShadowEffect_checkBox_auto_login);
    connect(checkBox_auto_login, SIGNAL(stateChanged(int)), this, SLOT(setAutoLogin()));
    // [CHECKBOX_AUTOLOGIN]

    // [BUTTON_LOGIN]
    button_login = new QToolButton(this);
    button_login->setText("Login");
    button_login->setGeometry(checkBox_remember->x(), checkBox_remember->y() + checkBox_remember->height() + horizontalSpacing, 85, 32);
    QString styleSheet_button_login = QssReader(":/qss/styleSheet_black_button").getQssData();
    button_login->setStyleSheet(styleSheet_button_login);
    connect(button_login, SIGNAL(clicked()), this, SLOT(on_button_login_clicked()));
    // [BUTTON_LOGIN]

    // [BUTTON_CLEAR]
    QToolButton *button_clear = new QToolButton(this);
    button_clear->setText("Clear");
    button_clear->setGeometry(button_login->x() + 108, button_login->y(), button_login->width(), button_login->height());
    button_clear->setStyleSheet(styleSheet_button_login);
    connect(button_clear, SIGNAL(clicked()), this, SLOT(clearComboBoxText()));
    // [BUTTON_CLEAR]
}

void Aeciumo::initLib()
{
    QString path_app = QApplication::applicationDirPath();
    path_lib = path_app + "/baslib";
    QString path_config = "/home/moky/.baslib";
    QFile *file_lib = new QFile(path_lib);
    if(!file_lib->exists())
        QFile::copy(":/lib/baslib", path_lib);
    QFile *file_config = new QFile(path_config);
    if(!file_config->exists())
        QFile::copy(":/lib/.baslib", path_config);
}

QPixmap Aeciumo::setBackgroundMask(QPixmap background)
{
    int background_width = background.width();
    int background_height = background.height();
    QBitmap *maskBitmap = new QBitmap(QSize(background_width, background_height));
    QPainter *maskPainter = new QPainter();
    maskPainter->begin(maskBitmap);
    QPen pen;
    pen.setBrush(QColor(0, 0, 0, 255));
    maskPainter->setPen(pen);
    maskPainter->fillRect(QRect(0, 0, background_width, background_height), Qt::SolidPattern);
    QPoint clipPoints[] = {QPoint(0, 0), QPoint(1, 0), QPoint(0, 1), QPoint(background_width - 1, 0), QPoint(background_width - 2, 0), QPoint(background_width - 1, 1), QPoint(0, background_height - 1), QPoint(0, background_height - 2), QPoint(1, background_height - 1), QPoint(background_width - 1, background_height - 1), QPoint(background_width - 1, background_height - 2), QPoint(background_width - 2, background_height - 1)};
    pen.setBrush(QColor(255, 255, 255, 255));
    maskPainter->setPen(pen);
    maskPainter->drawPoints(clipPoints, 12);
    maskPainter->end();
    background.setMask(*maskBitmap);
    QPainter *mPainter = new QPainter();
    mPainter->begin(&background);
    QPoint points_Shadow[] = {QPoint(2, 0), QPoint(0, 2), QPoint(0, background_height - 3), QPoint(2, background_height - 1), QPoint(background_width - 3, background_height - 1), QPoint(background_width - 1, background_height - 3), QPoint(background_width - 1, 2), QPoint(background_width - 3, 0)};
    pen.setBrush(QColor(0, 0, 0, 65));
    mPainter->setPen(pen);
    mPainter->drawConvexPolygon(points_Shadow, 8);
    pen.setBrush(QColor(255, 255, 255, 30));
    mPainter->setPen(pen);
    QPoint points_Highlight[] = {QPoint(2, 1), QPoint(1, 2), QPoint(1, background_height - 3), QPoint(2, background_height - 2), QPoint(background_width - 3, background_height - 2), QPoint(background_width - 2, background_height - 3), QPoint(background_width - 2, 2), QPoint(background_width - 3, 1)};
    mPainter->drawConvexPolygon(points_Highlight, 8);
    mPainter->end();
    return background;
}

void Aeciumo::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isPressedMouse = true;
        pos_Range = event->globalPos() - pos();
    }
}

void Aeciumo::mouseMoveEvent(QMouseEvent *event)
{
    if(isPressedMouse)
    {
        move(event->globalPos() - pos_Range);
    }
    else
        isPressedMouse = false;
}

void Aeciumo::mouseReleaseEvent(QMouseEvent *)
{
    isPressedMouse = false;
}

void Aeciumo::setRemember()
{
    int state = checkBox_remember->checkState();
    switch (state)
    {
    case Qt::Checked:
        break;
    case Qt::Unchecked:
        checkBox_auto_login->setChecked(false);
        break;
    }
}

void Aeciumo::setAutoLogin()
{
    int state = checkBox_auto_login->checkState();
    switch (state)
    {
    case Qt::Checked:
        checkBox_remember->setChecked(true);
        break;
    case Qt::Unchecked:
        break;
    }
}

void Aeciumo::clearComboBoxText()
{
    comboBox_id->clearEditText();
    lineEdit_password->setText("");
    checkBox_remember->setChecked(false);
    checkBox_auto_login->setChecked(false);
}

void Aeciumo::settings()
{
    qDebug() << "SETTINGS";
}

void Aeciumo::minimum()
{
    showMinimized();
}

void Aeciumo::quit()
{
    QApplication::quit();
}

void Aeciumo::on_button_login_clicked()
{
    if(!state_login)
        login();
    else
        logout();
}

void Aeciumo::checkState()
{
    qDebug() << "CHK:" << networkState->getNetworkState();
    if(networkState->getNetworkState())
        login();
}

void Aeciumo::login()
{
    // qDebug() << "LOGIN";
    //connectInternet = new ConnectInternet(comboBox_id->currentText(), lineEdit_password->text(), "172.16.1.180", "wlan0");
    connectInternet = new ConnectInternet(comboBox_id->currentText(), lineEdit_password->text(), "219.136.125.139", "eth0");
    connectInternet->start();
    button_login->setText("Logout");
    state_login = !state_login;
}

void Aeciumo::logout()
{
    // qDebug() << "LOGOUT";
    argumentList.clear();
    argumentList.append("-l");
    process->execute(path_lib, argumentList);
    button_login->setText("Login");
    state_login = !state_login;
}
