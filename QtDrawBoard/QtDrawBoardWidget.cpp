#include "QtDrawBoardWidget.h"

#include <QPainter>
#include <QMouseEvent>

#define pixMapSize QSize(800, 600)	// ǿ�����û�����С


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

// ���û滭ģʽ
void QtDrawBoardWidget::setDrawType(const DrawType& type)
{
	m_DrawType = type;
}

// ��ȡ�滭ģʽ
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
	m_drawPath = QPainterPath(m_pointStart);	// ���path
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
	m_drawPath = QPainterPath(m_pointStart);	// ���path
	m_drawPath.lineTo(m_pointEnd);
	painter.drawPath(m_drawPath);
	painter.drawLine(m_pointStart, m_pointEnd);
}

void QtDrawBoardWidget::drawRound()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_drawPix);
	m_drawPath = QPainterPath();	// ���path
	m_drawPath.addEllipse(QRectF(m_pointStart, m_pointEnd));
	painter.drawPath(m_drawPath);
}

void QtDrawBoardWidget::drawRect()
{
	QPainter painter(&m_drawPixTemp);
	painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_drawPix);
	m_drawPath = QPainterPath();	// ���path
	m_drawPath.addRect(QRectF(m_pointStart, m_pointEnd));
	painter.drawPath(m_drawPath);
}

void QtDrawBoardWidget::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	//���ÿ����
	p.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
	if (m_DrawState == false)
	{
		// �ǻ���״̬��ֱ�ӻ���pixmap
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
	// �������ݻ���ͼ��
	m_drawPixTemp = m_drawPix;
	m_drawPath = QPainterPath(m_pointStart);
	m_pts.clear();	// ��վ��������
}

void QtDrawBoardWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_DrawType == DrawType::None)
		return;
	m_DrawState = false;
	if (!m_drawPixTemp.isNull()) //���ڻ�ͼ �Ҹ��������Ѿ�����ͼƬ �� �滭�����
	{
		m_drawPix = m_drawPixTemp; // ��ͼ���̽��� ��ʱm_tempPicΪ���ջ���ͼ��
		m_drawPixTemp = QPixmap(); //���������ձ��� 
	}
	this->update();
}

void QtDrawBoardWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (m_DrawType == DrawType::None)
		return;
	if (event->buttons() & Qt::LeftButton) //���������µ�ͬʱ�ƶ����    
	{
		m_pointEnd = event->pos();
		m_pts.push_back(m_pointEnd);
		this->update(); //������ͼ�¼�  
	}
}