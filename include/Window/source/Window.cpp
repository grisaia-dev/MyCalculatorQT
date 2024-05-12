#include <Window/include/Window.hpp>
#include "ui_Window.h"
#include <QFile>
#include <QFileInfo>
#include <QColor>
#include <QMouseEvent>

Window::Window(QWidget* parent) :
QWidget(parent), ui(new Ui::Window), shadowEffect(new QGraphicsDropShadowEffect(this)),
icon (new QPixmap(getResourcePath() + "icon.png")) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    ui->text->setText("0");
    ui->name->setText(qApp->applicationName());

    // Стилизация окна
    set_style();
    set_shadow();
    set_icon();

    // Коннекты
    connect(ui->btn_close, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->btn_minimize, &QPushButton::clicked, [this](){
        if(this->isMinimized()) { this->showNormal();}
        else { this->showMinimized(); }
    });
}

Window::~Window() {
    delete icon;
    delete shadowEffect;
    delete ui;
}

void Window::set_style() {
    QString file(getResourcePath() + "window.qss");
    if(QFileInfo::exists(file)) {
        QFile style(file);
        if(style.open(QIODevice::ReadOnly)) {
            this->setStyleSheet(style.readAll());
            style.close();
        }
    } else {
        qDebug() << "can't find file : " + file;
    }
}

void Window::set_shadow() {
    shadowEffect->setBlurRadius(11.0f); // Радиус размытия тени
    shadowEffect->setColor(QColor(0, 0, 0, 160));
    shadowEffect->setOffset(0);
    ui->Interface->setGraphicsEffect(shadowEffect);
}

void Window::set_icon() {
    ui->icon->setPixmap(*icon);
    ui->icon->setScaledContents(true);
    ui->icon->setFixedSize(25, 15);
}

QString Window::getResourcePath() {
#if defined (Q_OS_APPLE)
    return QApplication::applicationDirPath() + "/../Resources/";
#else
    return QApplication::applicationDirPath() + "/";
#endif
}

Window::MouseType Window::checkResizableField(QMouseEvent* event) {
    QPointF position = event->globalPosition();
    qreal x = this->x();
    qreal y = this->y();
    qreal width = this->width();
    qreal height = this->height();

    QRectF rectInterface(x, y, width, height - 370);

    if (rectInterface.contains(position)) {
        setCursor(QCursor());
        return MouseType::Move;
    } else {
        setCursor(QCursor());
        return MouseType::None;
    }
}

QPoint Window::previousPosition() const { return m_previous_mouse_position; }

void Window::setPreviousPosition(QPoint previousPosition) {
    if (m_previous_mouse_position == previousPosition)
        return;
    m_previous_mouse_position = previousPosition;
    emit previousPositionChanged(previousPosition);
}

void Window::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_mouse_type = checkResizableField(event);
        setPreviousPosition(event->pos());
    }
    return QWidget::mousePressEvent(event);
}

void Window::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_mouse_type = MouseType::None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void Window::mouseMoveEvent(QMouseEvent* event) {
    switch (m_mouse_type) {
        case MouseType::Move: {
            auto dx = event->position().x() - m_previous_mouse_position.x();
            auto dy = event->position().y() - m_previous_mouse_position.y();
            setGeometry(x() + dx, y() + dy, width(), height());
            break;
        }
        default:
            checkResizableField(event);
            break;
    }
    return QWidget::mouseMoveEvent(event);
}
