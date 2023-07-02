#include "MainWidget.h"
#include "QtDrawBoardWidget.h"

#include <QToolbar>
#include <QAction>
#include <qDebug>

MainWidget::MainWidget(QWidget* parent)
	: QMainWindow(parent)
{
	this->initUI();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initUI()
{
	this->resize(800, 600);
	m_pDrawWidget = new QtDrawBoardWidget(this);
	this->setCentralWidget(m_pDrawWidget);

	m_pToolBar = new QToolBar(this);

	m_pActionRandom = new QAction("Random", this);
	m_pActionRandom->setCheckable(true);
	m_pToolBar->addAction(m_pActionRandom);

	m_pActionLine = new QAction("Line", this);
	m_pActionLine->setCheckable(true);
	m_pToolBar->addAction(m_pActionLine);

	m_pActionRect = new QAction("Rect", this);
	m_pActionRect->setCheckable(true);
	m_pToolBar->addAction(m_pActionRect);

	m_pActionRound = new QAction("Round", this);
	m_pActionRound->setCheckable(true);
	m_pToolBar->addAction(m_pActionRound);

	connect(m_pToolBar, &QToolBar::actionTriggered, this, &MainWidget::slot_toolBarClick);
	this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, m_pToolBar);
}

void MainWidget::slot_toolBarClick(QAction* action)
{
	qDebug() << action->text();
	if (!action->isChecked())
		m_pDrawWidget->setDrawType(QtDrawBoardWidget::DrawType::None);
	else
	{
		auto acts = m_pToolBar->actions();
		for (auto a : acts)
		{
			if (a != action)
				a->setChecked(false);
		}
		if (action == m_pActionRandom)
			m_pDrawWidget->setDrawType(QtDrawBoardWidget::DrawType::Random);
		else if (action == m_pActionLine)
			m_pDrawWidget->setDrawType(QtDrawBoardWidget::DrawType::Line);
		else if (action == m_pActionRect)
			m_pDrawWidget->setDrawType(QtDrawBoardWidget::DrawType::Rect);
		else if (action == m_pActionRound)
			m_pDrawWidget->setDrawType(QtDrawBoardWidget::DrawType::Round);

	}
}