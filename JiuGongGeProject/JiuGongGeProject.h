#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include <vector>
#include <qtextedit.h>
//#include <qkeyeventtransition.h>
#include <qevent.h>
#include <qtimer.h>
#include <qfiledialog.h>
#include <qdialog.h>
#include "Solution.h"
#include "ShowImageWidget.h"
#include "ui_JiuGongGeProject.h"
#include "SetSizeWidget.h"
#include "EditMatWidget.h"
#include "SetTimeWidget.h"
using namespace std;
class JiuGongGeProject : public QMainWindow
{
	Q_OBJECT

public:
	JiuGongGeProject(QWidget* parent = Q_NULLPTR);
	void btnSlot_Genarate();
	void btnSlot_BeginSearch();
	void btnSlot_ChooseSize();
	void btnSlot_EditMat();
	void btnSlot_Stop();
	void btnSlot_End();
	void btnSlot_Begin();
	void chooseMatSlot_Change();
	void btnSlot_SetTime();
	void btnSlot_SetPicture();
	void btnSlot_ClearPic();

private:
	void initBoxChooseMat();
	void initBoxChooseAuto();
	void initBoxChooseSearch();
private:
	void initMyFocus();
	void initMyUiFace();
	void initMySlot();

private:
	void initMyStatusBar();
	void appendInfoString(QString s);
	QTextEdit* m_statusEdit;

private:
	void timerSlot();

private:
	//��ʼ�Զ��ָ�
	void beginAuto();
	void beginManual();

private:
	void keyPressEvent(QKeyEvent* keyevent);

private:
	//���� 0 - n-1�ڵ�n���������һ�����ͬ
	vector<int> randomVector(int n);

private:
	SetTimeWidget* m_setMaxTimeWidget;
	void setTimeConfirm();
	void setTimeQuit();
	int m_MaxTime;
private:
	SetSizeWidget* m_setSizeWidget;
	void setSizeConfirm();
	void setSizeQuit();

private:
	EditMatWidget* m_EditMatWidget;
	void editMatConfirm();
	void editMatQuit();

private:
	Ui::JiuGongGeProjectClass ui;
private:
	vector<MyDirection> m_Solution;
	int m_SolutionIndex;
	int m_ManualTime;

private:
	QTimer* m_ShowTimer;
private:
	int m_MoveTime;

private:
	JIUGONGGESTATE m_state;

};
