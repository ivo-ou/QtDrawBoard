#pragma once
#include <QMainwindow>

class QtDrawBoardWidget;

class MainWidget :
	public QMainWindow
{
	Q_OBJECT
public:
	MainWidget(QWidget* parent = nullptr);
	~MainWidget();

private:
	void initUI();

public slots:
	void slot_toolBarClick(QAction* action);

private:
	QtDrawBoardWidget* m_pDrawWidget;
	QToolBar* m_pToolBar;
	QAction* m_pActionRandom;
	QAction* m_pActionLine;
	QAction* m_pActionRect;
	QAction* m_pActionRound;
};

