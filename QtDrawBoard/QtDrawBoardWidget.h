#pragma once
#include <QWidget>


class QtDrawBoardWidget :
	public QWidget
{
public:
	enum DrawType
	{
		None = 0,
		Random,
		Line,
		Round,
		Rect
	};


	QtDrawBoardWidget(QWidget* parent = nullptr);
	~QtDrawBoardWidget();

	// ���û滭ģʽ
	void setDrawType(const DrawType& type);

	// ��ȡ�滭ģʽ
	DrawType getDrawType() const;

	QPixmap getDrawPixmap() const;

protected:
	void drawRandom();
	void drawLine();
	void drawRound();
	void drawRect();
	void paintEvent(QPaintEvent* e);

	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);


private:
	QPixmap m_drawPix;
	QPixmap m_drawPixTemp;
	DrawType m_DrawType;
	bool m_DrawState;
	QPointF m_pointStart;
	QPointF m_pointEnd;

	QPainterPath m_drawPath;
	QVector<QPointF> m_pts;	// ���澭�������꣬���Ʒ������ͼ����Ҫ



};

