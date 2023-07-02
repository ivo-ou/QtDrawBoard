#include "QtDrawBoardWidget.h"

#include <QPainter>
#include <QMouseEvent>

#define pixMapSize QSize(800, 600)	// 强制设置画布大小


QtDrawBoardWidget::QtDrawBoardWidget(QWidget* parent)
	: QWidget(parent)
{
	this->setFixedSize(pixMapSize);
	m_drawPix = QPixmap(pixMapSize);
	m_drawPix.fill(Qt::white);
	m_drawPixTemp = QPixmap(pixMapSize);
	m_DrawState = false;
	m_DrawType = DrawType::None;
}
QtDrawBoardWidget::~QtDrawBoardWidget()
{
	
}

// 设置绘画模式
void QtDrawBoardWidget::setDrawType(const DrawType& type)
{
	m_DrawType = type;
}

// 获取绘画模式
QtDrawBoardWidget::DrawType QtDrawBoardWidget::getDrawType() const
{
	return m_DrawType;
}

QPixmap QtDrawBoardWidget::getDrawPixmap() const
{
	return m_drawPix;
}

void QtDrawBoardWidget::drawRandom()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	m_drawPath = QPainterPath(m_pointStart);	// 清空path
	m_drawPath.addPolygon(QPolygonF(m_pts));
	m_drawPath.closeSubpath();
	painter.setBrush(Qt::red);
	painter.drawPath(m_drawPath);
}

void QtDrawBoardWidget::drawLine()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_drawPix);
	m_drawPath = QPainterPath(m_pointStart);	// 清空path
	m_drawPath.lineTo(m_pointEnd);
	painter.drawPath(m_drawPath);
	painter.drawLine(m_pointStart, m_pointEnd);
}

void QtDrawBoardWidget::drawRound()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_drawPix);
	m_drawPath = QPainterPath();	// 清空path
	m_drawPath.addEllipse(QRectF(m_pointStart, m_pointEnd));
	painter.drawPath(m_drawPath);
}

void QtDrawBoardWidget::drawRect()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_drawPix);
	m_drawPath = QPainterPath();	// 清空path
	m_drawPath.addRect(QRectF(m_pointStart, m_pointEnd));
	painter.drawPath(m_drawPath);
}

void QtDrawBoardWidget::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	//设置抗锯齿
	p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	if (m_DrawState == false)
	{
		// 非绘制状态，直接绘制pixmap
		p.drawPixmap(0, 0, m_drawPix);
	}
	else
	{
		switch (m_DrawType)
		{
		case DrawType::Line:
			this->drawLine();
			break;
			case DrawType::Random:
			this->drawRandom();
			break;
			case DrawType::Rect:
			this->drawRect();
			break;
		case DrawType::Round:
			this->drawRound();
			break;
		default:
			break;
		}
		p.drawPixmap(0, 0, m_drawPixTemp);
	}
}

void QtDrawBoardWidget::mousePressEvent(QMouseEvent *event)
{
	if (m_DrawType == DrawType::None)
		return;
	m_DrawState = true;
	m_pointStart = event->pos();
	// 拷贝备份缓冲图像
	m_drawPixTemp = m_drawPix;
	m_drawPath = QPainterPath(m_pointStart);
	m_pts.clear();	// 清空经过坐标点
}

void QtDrawBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_DrawType == DrawType::None)
		return;
	m_DrawState = false;
	if (!m_drawPixTemp.isNull()) //不在绘图 且辅助画布已经画过图片 即 绘画已完成
	{
		m_drawPix = m_drawPixTemp; // 绘图过程结束 此时m_tempPic为最终绘制图像
		m_drawPixTemp = QPixmap(); //绘制完成清空备份 
	}
	this->update();
}

void QtDrawBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (m_DrawType == DrawType::None)
		return;
	if (event->buttons() & Qt::LeftButton) //鼠标左键按下的同时移动鼠标    
	{
		m_pointEnd = event->pos();
		m_pts.push_back(m_pointEnd);
		this->update(); //产生绘图事件  
	}
}