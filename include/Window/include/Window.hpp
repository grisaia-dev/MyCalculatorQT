#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGraphicsDropShadowEffect>


QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QWidget {
    Q_OBJECT
    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)
    public:
        Window(QWidget* parent = nullptr);
        ~Window();
        QPoint previousPosition() const;

    public slots:
        void setPreviousPosition(QPoint previousPosition);

    signals:
        void previousPositionChanged(QPoint previousPosition);

    protected:
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

    private: // Functions
        void set_style();
        void set_shadow();
        void set_icon();
        QString getResourcePath();

        enum class MouseType {
            None = 0,
            Move
        };
        MouseType checkResizableField(QMouseEvent* event);
    private: // Variables
        Ui::Window *ui = nullptr;
        QGraphicsDropShadowEffect *shadowEffect = nullptr;
        QPixmap* icon = nullptr;

        MouseType m_mouse_type;
        QPoint m_previous_mouse_position;
};

#endif // WINDOW_H
