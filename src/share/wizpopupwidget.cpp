#include "wizpopupwidget.h"
#include "wizmisc.h"

#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <QPolygon>
#include <QTimer>

#ifdef Q_OS_WIN
//#include "wizwindowshelper.h"
#endif


CWizPopupWidget::CWizPopupWidget(QWidget* parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint)
    , m_leftAlign(false)
{
    setContentsMargins(8, 20, 8, 8);
    //
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(0xff, 0xff, 0xff));
    setPalette(pal);
}

QSize CWizPopupWidget::sizeHint() const
{
    return QSize(300, 400);
}

QRect CWizPopupWidget::getClientRect() const
{
    QMargins margins = contentsMargins();
    return QRect(margins.left(), margins.top(),
                 width() - margins.left() - margins.right(),
                 height() - margins.top() - margins.bottom());
}

#ifndef Q_OS_MAC

void CWizPopupWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPen pen(QColor(0xd9, 0xdc, 0xdd));
    //pen.setWidth(3);
    painter.setPen(pen);
    //painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPolygon(m_pointsPolygon);
}

#endif

void CWizPopupWidget::resizeEvent(QResizeEvent* event)
{
    QSize sz = event->size();
    //
    m_pointsRegion.clear();
    //
    if (m_leftAlign)
    {
        m_pointsRegion.push_back(QPoint(1, 10));
        m_pointsRegion.push_back(QPoint(11, 10));
        m_pointsRegion.push_back(QPoint(21, 0));
        m_pointsRegion.push_back(QPoint(31, 10));
        m_pointsRegion.push_back(QPoint(sz.width() - 1, 10));
        m_pointsRegion.push_back(QPoint(sz.width(), 11));
        m_pointsRegion.push_back(QPoint(sz.width(), sz.height()));
        m_pointsRegion.push_back(QPoint(0, sz.height()));
        m_pointsRegion.push_back(QPoint(0, 11));
        //
        m_pointsPolygon.push_back(QPoint(1, 10));
        m_pointsPolygon.push_back(QPoint(11, 10));
        for (int i = 0; i < 9; i++)
        {
            m_pointsPolygon.push_back(QPoint(11 + i, 10 - i));
            m_pointsPolygon.push_back(QPoint(11 + i + 1, 10 - i));
        }
        m_pointsPolygon.push_back(QPoint(20, 1));
        m_pointsPolygon.push_back(QPoint(21, 1));
        for (int i = 0; i < 9; i++)
        {
            m_pointsPolygon.push_back(QPoint(21 + i, 2 + i));
            m_pointsPolygon.push_back(QPoint(21 + i + 1, 2 + i));
        }
        m_pointsPolygon.push_back(QPoint(31, 10));
        m_pointsPolygon.push_back(QPoint(sz.width() - 2, 10));
        m_pointsPolygon.push_back(QPoint(sz.width() - 1, 11));
        m_pointsPolygon.push_back(QPoint(sz.width(), sz.height() - 1));
        m_pointsPolygon.push_back(QPoint(0, sz.height() - 1));
        m_pointsPolygon.push_back(QPoint(0, 11));
        m_pointsPolygon.push_back(QPoint(1, 11));
    }
    else
    {
        m_pointsRegion.push_back(QPoint(1, 10));
        m_pointsRegion.push_back(QPoint(sz.width() - 31, 10));
        m_pointsRegion.push_back(QPoint(sz.width() - 21, 0));
        m_pointsRegion.push_back(QPoint(sz.width() - 11, 10));
        m_pointsRegion.push_back(QPoint(sz.width() - 1, 10));
        m_pointsRegion.push_back(QPoint(sz.width(), 11));
        m_pointsRegion.push_back(QPoint(sz.width(), sz.height()));
        m_pointsRegion.push_back(QPoint(0, sz.height()));
        m_pointsRegion.push_back(QPoint(0, 11));
        //
        m_pointsPolygon.push_back(QPoint(1, 10));
        m_pointsPolygon.push_back(QPoint(sz.width() - 31, 10));
        for (int i = 0; i < 9; i++)
        {
            m_pointsPolygon.push_back(QPoint(sz.width() - 31 + i, 10 - i));
            m_pointsPolygon.push_back(QPoint(sz.width() - 31 + i + 1, 10 - i));
        }
        m_pointsPolygon.push_back(QPoint(sz.width() - 22, 1));
        m_pointsPolygon.push_back(QPoint(sz.width() - 21, 1));
        for (int i = 0; i < 9; i++)
        {
            m_pointsPolygon.push_back(QPoint(sz.width() - 21 + i, 2 + i));
            m_pointsPolygon.push_back(QPoint(sz.width() - 21 + i + 1, 2 + i));
        }
        m_pointsPolygon.push_back(QPoint(sz.width() - 12, 10));
        m_pointsPolygon.push_back(QPoint(sz.width() - 2, 10));
        m_pointsPolygon.push_back(QPoint(sz.width() - 2, 11));
        m_pointsPolygon.push_back(QPoint(sz.width() - 1, 11));
        m_pointsPolygon.push_back(QPoint(sz.width(), sz.height() - 1));
        m_pointsPolygon.push_back(QPoint(0, sz.height() - 1));
        m_pointsPolygon.push_back(QPoint(0, 11));
        m_pointsPolygon.push_back(QPoint(1, 11));

    }
    //
    QPolygon polygon(m_pointsRegion);
    //
    QRegion region(polygon);
    //
    setMask(region);
}


void CWizPopupWidget::showAtPoint(const QPoint& pt)
{
    adjustSize();
    //
    QSize sz = geometry().size();
    //
    int xOffset = m_leftAlign ? 21 : sz.width() - 21;
    int yOffset = 4;
    //
    int left = pt.x() - xOffset;
    int top = pt.y() - yOffset;
    //
    move(QPoint(left, top));
    //
    show();
}
