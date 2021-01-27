#include "JiuGongGeProject.h"
using namespace std;

JiuGongGeProject::JiuGongGeProject(QWidget *parent)
	: QMainWindow(parent)
{
	m_ShowTimer = NULL;
	m_MoveTime = 300;
	m_MaxTime = 10000;
	ui.setupUi(this);
	m_state = NOTSTART;
	initMyStatusBar();
	initMySlot();
	initMyUiFace();

	initMyFocus();

	initBoxChooseMat();
	initBoxChooseAuto();
	initBoxChooseSearch();

	QString s = "JiuGongGe.jpg";
	QImage img;
	if (img.load(s))
	{
		this->ui.widget_ShowImage->setMyPicture(QPixmap::fromImage(img));
	}

}
void JiuGongGeProject::btnSlot_ClearPic()
{
	ui.widget_ShowImage->clearMyPicture();
}

void JiuGongGeProject::btnSlot_SetTime()
{
	m_setMaxTimeWidget = new SetTimeWidget(0);
	m_setMaxTimeWidget->show();
	connect(m_setMaxTimeWidget->ui.okButton, &QPushButton::clicked,
		this, &JiuGongGeProject::setTimeConfirm);
	connect(m_setMaxTimeWidget->ui.cancelButton, &QPushButton::clicked,
		this, &JiuGongGeProject::setTimeQuit);
}

void JiuGongGeProject::setTimeConfirm()
{
	int tmpTime;
	tmpTime = m_setMaxTimeWidget->ui.lineEdit->text().toInt();
	if (tmpTime >= 100 && tmpTime <= 300000)
	{
		m_MaxTime = tmpTime;
		QMessageBox::information(0, "succeed",QStringLiteral( "���óɹ�"));
	}
	else
	{
		QMessageBox::warning(0, "fail", QStringLiteral("����ʧ��"));
	}
	m_setMaxTimeWidget->deleteLater();
	m_setMaxTimeWidget = NULL;
}
void JiuGongGeProject::setTimeQuit()
{
	m_setMaxTimeWidget->deleteLater();
	m_setMaxTimeWidget = NULL;
}
void JiuGongGeProject::btnSlot_ChooseSize()
{
	appendInfoString("show window");
	//������Զ�������ģʽ
	m_setSizeWidget = new SetSizeWidget();
	m_setSizeWidget->show();
	m_setSizeWidget->setWindowModality(Qt::WindowModality::WindowModal);
	appendInfoString(QString::number(m_setSizeWidget->isModal()));
	connect(m_setSizeWidget->ui.button_ok, &QPushButton::clicked,
		this, &JiuGongGeProject::setSizeConfirm);
	connect(m_setSizeWidget->ui.button_quit, &QPushButton::clicked,
		this, &JiuGongGeProject::setSizeQuit);
}

void JiuGongGeProject::setSizeQuit()
{
	m_setSizeWidget->deleteLater();
	m_setSizeWidget = NULL;
}
void JiuGongGeProject::setSizeConfirm()
{
	int col = m_setSizeWidget->ui.lineEdit_col->text().toInt();
	int row = m_setSizeWidget->ui.lineEdit_row->text().toInt();
	if (row > 2 && row <= 20 && col>2 && col <= 20)
	{
		Map m;
		vector<int> v;
		for (int i = 0; i < row*col; i++)
		{
			v.push_back((i + 1) % (row*col));
		}
		m.initMap(col, row);
		m.setContent(v);
		ui.widget_ShowImage->setMap(m);
	}
	else
	{
		QMessageBox::warning(0, "error",
			QStringLiteral("�������ݴ�3-19"));
	}
	m_setSizeWidget->deleteLater();
	m_setSizeWidget = NULL;
}

void JiuGongGeProject::initMyStatusBar()
{
//	m_statusEdit =  new QTextEdit();
//	this->statusBar()->addWidget(m_statusEdit);
//	m_statusEdit->setFocusPolicy(Qt::NoFocus);
}

void JiuGongGeProject::appendInfoString(QString s)
{
	//this->m_statusEdit->append(s);
}

void JiuGongGeProject::initMyUiFace()
{
	appendInfoString("init Ui Face");
}
void JiuGongGeProject::btnSlot_SetPicture()
{
	QString s = QFileDialog::getOpenFileName(0, 
		"choose img", "", "Image(*.png *.bmp *.jpg *.jpeg)");
	QImage img;
	if (s != "")
	{
		if (img.load(s))
		{
			this->ui.widget_ShowImage->setMyPicture(QPixmap::fromImage(img));
		}
		else
		{
			
		}
	}
}

void JiuGongGeProject::initMySlot()
{
	connect(ui.button_generate, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_Genarate);
	connect(ui.button_beginSearch, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_BeginSearch);
	connect(ui.button_begin, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_Begin);
	connect(ui.button_stop, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_Stop);
	connect(ui.button_end, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_End);
	connect(ui.box_chooseMat,
		QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, &JiuGongGeProject::chooseMatSlot_Change);
	connect(ui.button_chooseSize, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_ChooseSize);
	connect(ui.button_edit, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_EditMat);
	connect(ui.button_setTime, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_SetTime);
	connect(ui.button_importImg, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_SetPicture);
	connect(ui.button_clearPic, &QPushButton::clicked,
		this, &JiuGongGeProject::btnSlot_ClearPic);
}
void JiuGongGeProject::btnSlot_Begin()
{
	if (m_state == SEARCHOVER)
	{
		if (ui.box_chooseAuto->currentIndex() == 1)
		{
			beginAuto();
		}
		//�ֶ�
		else if(ui.box_chooseAuto->currentIndex() == 2)
		{
			QMessageBox msg;
			msg.setWindowTitle("warning");
			msg.setText(QStringLiteral("�Ѿ����������ѡ���ֶ���ԭ����ɾ�������������ѡ��"));
			QPushButton* manualbtn = 
				msg.addButton(QStringLiteral("�����ֶ�"),
					QMessageBox::ActionRole);
			QPushButton* autobtn =
				msg.addButton(QStringLiteral("�����Զ���ԭ"),
					QMessageBox::ActionRole);
			QPushButton* quitbtn = msg.addButton(QStringLiteral("ȡ��"),
				QMessageBox::ActionRole);
			msg.exec();
			if (msg.clickedButton() == manualbtn)
			{
				beginManual();
			}
			else if (msg.clickedButton() == autobtn)
			{
				beginAuto();
			}
			else if (msg.clickedButton() == quitbtn)
			{
				//do nothing
			}
		}
		//δѡ��
		else if (ui.box_chooseAuto->currentIndex() == 0)
		{
			QMessageBox::warning(0, "warning", QStringLiteral("��ѡ��ʼģʽ"));
		}
	}
	else if (m_state == NOTSTART)
	{
		if (ui.box_chooseAuto->currentIndex() == 2)//�ֶ�ģʽ
		{
			appendInfoString("begin manual");
			beginManual();
		}
		else
		{
			QMessageBox::warning(0, "warning",
				QStringLiteral("�������������ѡ���ֶ�ģʽ"));
		}
	}
	else
	{
		QMessageBox::warning(0, "error", "error something");
	}
}
void JiuGongGeProject::initMyFocus()
{
	ui.box_chooseAuto->setFocusPolicy(Qt::NoFocus);
	ui.box_chooseMat->setFocusPolicy(Qt::NoFocus);
	ui.box_search->setFocusPolicy(Qt::NoFocus);
	ui.button_begin->setFocusPolicy(Qt::NoFocus);
	ui.button_chooseSize->setFocusPolicy(Qt::NoFocus);
	ui.button_edit->setFocusPolicy(Qt::NoFocus);
	ui.button_end->setFocusPolicy(Qt::NoFocus);
	ui.button_generate->setFocusPolicy(Qt::NoFocus);
	ui.button_stop->setFocusPolicy(Qt::NoFocus);
	ui.widget_ShowImage->setFocusPolicy(Qt::NoFocus);
	setFocusPolicy(Qt::ClickFocus);
	ui.button_setTime->setFocusPolicy(Qt::NoFocus);
	ui.button_importImg->setFocusPolicy(Qt::NoFocus);
}

void JiuGongGeProject::beginManual()
{
	m_state = ALLOWMANUAL;
	ui.box_chooseAuto->setEnabled(false);
	ui.box_chooseMat->setEnabled(false);
	ui.box_search->setEnabled(false);
	ui.button_begin->hide();
	ui.button_beginSearch->setEnabled(false);
	ui.button_chooseSize->setEnabled(false);
	ui.button_edit->setEnabled(false);

	ui.button_end->show();
	ui.button_generate->setEnabled(false);
	ui.button_stop->show();

	ui.label_time->show();
	m_ManualTime = 0;

	m_ShowTimer = new QTimer(this);
	connect(m_ShowTimer, &QTimer::timeout,
		this, &JiuGongGeProject::timerSlot);
	m_ShowTimer->start(1000);

}
void JiuGongGeProject::beginAuto()
{
	ui.box_chooseAuto->setEnabled(false);
	ui.box_chooseMat->setEnabled(false);
	ui.box_search->setEnabled(false);
	ui.button_begin->hide();
	ui.button_beginSearch->setEnabled(false);
	ui.button_chooseSize->setEnabled(false);
	ui.button_edit->setEnabled(false);
	ui.button_end->show();
	ui.button_generate->setEnabled(false);
	ui.button_stop->show();
	ui.button_stop->setText(QStringLiteral("��ͣ"));
	ui.button_end->setText(QStringLiteral("��ֹ"));

	ui.label_time->show();
	if (m_ShowTimer != NULL)
	{
		m_ShowTimer->deleteLater();
	}
	//m_ShowTimer = new QTimer(this);
	m_state = ALLOWAUTO;
	timerSlot();
	//connect(m_ShowTimer, &QTimer::timeout,
	//	this, &JiuGongGeProject::timerSlot);
	//m_ShowTimer->start(1000);
	//m_ShowTimer;
}
void JiuGongGeProject::chooseMatSlot_Change()
{
	switch (ui.box_chooseMat->currentIndex())
	{
	case 0://��ǰ����
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);

		ui.button_begin->setEnabled(true);
		ui.button_beginSearch->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		ui.button_end->hide();
		ui.button_generate->hide();
		ui.button_stop->hide();

		ui.label_time->hide();
		break;
	}
	case 1://�������
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);

		ui.button_begin->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		ui.button_end->hide();
		ui.button_generate->show();
		ui.button_stop->hide();

		ui.label_time->hide();
		break;
	}
	case 2://�Զ�������
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);

		ui.button_begin->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		ui.button_end->hide();
		ui.button_generate->hide();
		ui.button_stop->hide();

		ui.label_time->hide();
		break;
	}
	case 3:
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);
		ui.button_begin->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		Map map;
		vector<int> content = { 4,1,3,2,5,7,6,0,8 };
		map.initMap(3, 3);
		map.setContent(content);

		ui.widget_ShowImage->setMap(map);

		ui.button_end->hide();
		ui.button_generate->hide();
		ui.button_stop->hide();

		ui.label_time->hide();
		appendInfoString(QStringLiteral("���ɵ�һ��"));
		break;
	}
	case 4:
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);
		ui.button_begin->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		Map map;
		vector<int> content =
		{ 1, 10, 0, 13, 8, 3, 4, 11, 7, 12, 9, 6, 14, 5, 15, 2 };
		map.initMap(4, 4);
		map.setContent(content);

		ui.widget_ShowImage->setMap(map);

		ui.button_end->hide();
		ui.button_generate->hide();
		ui.button_stop->hide();

		ui.label_time->hide();
		appendInfoString(QStringLiteral("���ɵڶ���"));
		break;
	}
	default://�����ؿ�
	{
		ui.box_chooseAuto->setEnabled(true);
		ui.box_search->setEnabled(true);
		ui.button_begin->setEnabled(true);
		ui.button_chooseSize->setEnabled(true);
		ui.button_edit->setEnabled(true);

		Map map;
		vector<int> content = { 4,1,3,2,5,7,6,0,8 };
		map.initMap(3, 3);
		map.setContent(content);
		
		ui.widget_ShowImage->setMap(map);

		ui.button_end->hide();
		ui.button_generate->hide();
		ui.button_stop->hide();

		ui.label_time->hide();
		appendInfoString(QStringLiteral("���ɵ�һ��"));
		break;
	}
	}
}

void JiuGongGeProject::btnSlot_BeginSearch()
{
	//δѡ������ģʽ
	if (ui.box_search->currentIndex() == 0)
	{
		QMessageBox::warning(0, "warning", QStringLiteral("��ѡ������ģʽ"));
		return;
	}
	else
	{
		bool succeed = false;
		Solution s;
		s.setMaxTime(m_MaxTime);
		int w = ui.widget_ShowImage->getMapWidth();
		int h = ui.widget_ShowImage->getMapHeight();
		Map finalMap(w, h);
		vector<int> content(w * h);
		SearchType searchType;
		int ctrl = 0;
		bool timeOrSpaceOut;
		for (int i = 0; i < w*h - 1; i++)
		{
			content[i] = (i + 1) % (w*h);
		}

		finalMap.setContent(content);
		//A ����
		if (ui.box_search->currentIndex() == 1)
		{
			searchType = ASEARCH;
		}
		//�������
		else if (ui.box_search->currentIndex() == 2)
		{
			searchType = DEEPSEARCH;
		}
		else if (ui.box_search->currentIndex() == 3)
		{
			searchType = WIDTHSEARCH;
		}
		else if (ui.box_search->currentIndex() == 4)
		{
			searchType = PROGRAMSEARCH;
		}
		appendInfoString(QStringLiteral("��������"));
		m_Solution = s.getSolution(ui.widget_ShowImage->getMap(), finalMap,
			succeed, searchType, 0, timeOrSpaceOut);
		appendInfoString(QStringLiteral("�������"));
		m_SolutionIndex = 0;
		//���ʧ����
		if (!succeed)
		{
			if (timeOrSpaceOut == false)
			{
				m_Solution = s.getSolution(ui.widget_ShowImage->getMap(), finalMap,
					succeed, searchType, 1, timeOrSpaceOut);
				m_SolutionIndex = 0;
			}
			//����ɹ���
			if (succeed)
			{
				QMessageBox::StandardButton buttonResult;
				buttonResult = QMessageBox::information(0, "info",
					QStringLiteral("�ҵ���һ������Ϊ") +
					QString::number(m_Solution.size())+
					QStringLiteral("�ķ���������"));
				m_state = SEARCHOVER;
				appendInfoString("find a reverse path " +
					QString::number(m_Solution.size()) + "length");
			}
			//�����Ȼʧ����
			else
			{
				QMessageBox::warning(0, "warning",
					QStringLiteral("����������ʽ�Ҳ��������������������Χ̫���볢����������"));
				return;
			}
		}
		else
		{
			QString s = QString(QStringLiteral("�ҵ�һ������Ϊ")) +
				QString::number(m_Solution.size()) +
				QString(QStringLiteral("��·��"));
			QMessageBox::information(0, QStringLiteral("�����ɹ�"),s);
			appendInfoString("find a path " +
				QString::number(m_Solution.size()) + "length");
			m_state = SEARCHOVER;
			return;
		}
	}
}

void JiuGongGeProject::initBoxChooseMat()
{
	ui.box_chooseMat->addItem(QStringLiteral("��ǰ����"));
	ui.box_chooseMat->addItem(QStringLiteral("�������"));
	ui.box_chooseMat->addItem(QStringLiteral("�Զ�������"));
	ui.box_chooseMat->addItem(QStringLiteral("��һ��"));
	ui.box_chooseMat->addItem(QStringLiteral("�ڶ���"));
	ui.box_chooseMat->setCurrentIndex(1);
}

void JiuGongGeProject::btnSlot_Stop()
{
	if (m_state == STOPAUTO)//���������ͣ����ô������ʼ
	{
		ui.button_stop->setText(QStringLiteral("��ͣ"));
		m_state = ALLOWAUTO;
	}
	else if (m_state == ALLOWAUTO)
	{
		ui.button_stop->setText(QStringLiteral("�������"));
		m_state = STOPAUTO;
	}
	else if (m_state == STOPMANUAL)
	{
		ui.button_stop->setText(QStringLiteral("��ͣ"));
		m_state = ALLOWMANUAL;
	}
	else if (m_state == ALLOWMANUAL)
	{
		ui.button_stop->setText(QStringLiteral("�������"));
		m_state = STOPMANUAL;
	}
	else
	{
		QMessageBox::warning(0, "error", "something error");
	}
}

void JiuGongGeProject::timerSlot()
{
	appendInfoString("time slot");
	if (m_state == ALLOWAUTO)	//�����Զ���ԭ
	{
		if (m_SolutionIndex < m_Solution.size())
		{
			appendInfoString(QString::number(m_Solution[m_SolutionIndex]));
			ui.widget_ShowImage->Move(m_Solution[m_SolutionIndex]);
			m_SolutionIndex++;
			ui.label_time->setText(QStringLiteral("����") +
				QString::number(m_Solution.size() - m_SolutionIndex) 
				+ QStringLiteral("�� ") + QStringLiteral("F1���� F2���� ��ǰ�ٶȼ��� ")+
			QString::number(21 - m_MoveTime/100));
			QTimer::singleShot(m_MoveTime, this, &JiuGongGeProject::timerSlot);
		}
		else
		{
			QMessageBox::information(0, "info", QStringLiteral("�ƶ����"));
			m_state = NOTSTART;
			ui.box_chooseAuto->setEnabled(true);
			ui.box_chooseMat->setEnabled(true);
			ui.box_search->setEnabled(true);

			ui.button_begin->show();
			ui.button_beginSearch->setEnabled(true);
			ui.button_chooseSize->setEnabled(true);
			ui.button_edit->setEnabled(true);
			ui.button_generate->setEnabled(true);
			ui.button_end->hide();
			ui.button_stop->hide();
			ui.label_time->hide();
		}
	}
	else if (m_state == ALLOWMANUAL)
	{
		m_ManualTime++;
		ui.label_time->setText(QStringLiteral("����ʱ") +
			QString::number(m_ManualTime)
			+ QStringLiteral("��"));
		appendInfoString(QString::number(m_ManualTime));
	}
}

void JiuGongGeProject::keyPressEvent(QKeyEvent* keyevent)
{
	appendInfoString("press " + QString::number(keyevent->key()));
	if (m_state == ALLOWMANUAL)
	{
		switch (keyevent->key())
		{
		case Qt::Key_Up:
		{
			ui.widget_ShowImage->Move(UP);
			break;
		}
		case Qt::Key_Down:
		{
			ui.widget_ShowImage->Move(DOWN);
			break;
		}
		case Qt::Key_Left:
		{
			ui.widget_ShowImage->Move(LEFT);
			break;
		}
		case Qt::Key_Right:
		{
			ui.widget_ShowImage->Move(RIGHT);
			break;
		}
		}
	}
	else if (m_state == ALLOWAUTO || m_state == STOPAUTO)
	{
		switch (keyevent->key())
		{
		case Qt::Key_F1:
		{
			m_MoveTime = (m_MoveTime - 100 > 50)?(m_MoveTime-100):100;
			break;
		}
		case Qt::Key_F2:
		{
			m_MoveTime = (m_MoveTime + 100<2050) ? (m_MoveTime + 100) : 2000;
			break;
		}
		default:
			break;
		}
	}
}

void JiuGongGeProject::btnSlot_End()
{
	ui.button_end->hide();
	ui.button_stop->hide();
	ui.button_begin->show();

	ui.button_begin->setText(QStringLiteral("��ʼ"));
	ui.box_chooseAuto->setEnabled(true);
	ui.button_beginSearch->setEnabled(true);
	ui.box_search->setEnabled(true);
	ui.box_chooseMat->setEnabled(true);

	ui.button_chooseSize->setEnabled(true);
	ui.button_edit->setEnabled(true);
	ui.button_generate->setEnabled(true);
	ui.label_time->hide();
	m_state = NOTSTART;
}
void JiuGongGeProject::btnSlot_Genarate()
{
	switch (ui.box_chooseMat->currentIndex())
	{
	case 0:   //δѡ�����ɷ�ʽ�����ܳ���
	{
		QMessageBox::warning(NULL, "warning",
			QStringLiteral("��������"));
		break;
	}
	case 1:    //������ɣ����յ�ǰ�ĵ�ͼ��С��������
	{
		Map m;
		int h = ui.widget_ShowImage->getMapHeight();
		int w = ui.widget_ShowImage->getMapWidth();
		m.initMap(w, h);
		vector<int> content = randomVector(w*h);
		for (int i = 0; i < w*h; i++)
		{
			appendInfoString(QString::number(content[i]));
		}

		bool su = m.setContent(content);
		if (su)
		{
			appendInfoString("set map su");
		}
		else
		{
			appendInfoString("set map fail");
		}
		su = ui.widget_ShowImage->setMap(m);
		if (su)
		{
			appendInfoString("set show su");
		}
		else
		{
			appendInfoString("set show fail");
		}
		break;
	}
	case 2:
	{
		//�Զ������ɣ����ܳ���
		QMessageBox::warning(NULL, "warning",
			QStringLiteral("��������"));
		break;
	}
	default:  //ͨ������ؿ����ɣ����ܳ���
	{
		QMessageBox::warning(NULL, "warning",
			QStringLiteral("��������"));
		break;
	}
	}
}
void JiuGongGeProject::btnSlot_EditMat()
{
	if (ui.box_chooseMat->currentIndex() == 2)
	{
		m_EditMatWidget = new EditMatWidget(ui.widget_ShowImage->getMap());
		m_EditMatWidget->show();
		m_EditMatWidget->setWindowModality(Qt::WindowModality::WindowModal);
		connect(m_EditMatWidget->ui.button_ok, &QPushButton::clicked,
			this, &JiuGongGeProject::editMatConfirm);
		connect(m_EditMatWidget->ui.button_quit, &QPushButton::clicked,
			this, &JiuGongGeProject::editMatQuit);
	}
	else
	{
		QMessageBox::warning(0, "warning", QStringLiteral("��ѡ���Զ���ģʽ"));
	}
}
void JiuGongGeProject::editMatConfirm()
{
	Map map;
	int w = ui.widget_ShowImage->getMapWidth();
	int h = ui.widget_ShowImage->getMapHeight();
	map.initMap(w, h);
		
	vector<int> content(w*h);
	for (int i = 0; i < w*h; i++)
	{
		content[i]=m_EditMatWidget->m_LineEdit[i / w][i%w]->text().toInt();
	}
	if (map.setContent(content) == true)
	{
		this->ui.widget_ShowImage->setMap(map);
		m_EditMatWidget->deleteLater();
		m_EditMatWidget = NULL;
		m_state = NOTSTART;
	}
	else
	{
		QMessageBox::warning(0, "error", "input error");
	}
}
void JiuGongGeProject::editMatQuit()
{
	m_EditMatWidget->deleteLater();
	m_EditMatWidget = NULL;
}
void JiuGongGeProject::initBoxChooseSearch()
{
	ui.box_search->addItem(QStringLiteral("����ģʽ"));
	ui.box_search->addItem(QStringLiteral("A����"));
	ui.box_search->addItem(QStringLiteral("�������"));
	ui.box_search->addItem(QStringLiteral("�������"));
	ui.box_search->addItem(QStringLiteral("���ܻ�ԭ����"));
	ui.box_search->setCurrentIndex(1);
}
void JiuGongGeProject::initBoxChooseAuto()
{
	ui.box_chooseAuto->addItem(QStringLiteral("ѡ���Զ�ģʽ"));
	ui.box_chooseAuto->addItem(QStringLiteral("�Զ�ģʽ"));
	ui.box_chooseAuto->addItem(QStringLiteral("�ֶ�ģʽ"));
	ui.box_chooseAuto->setCurrentIndex(1);
}
vector<int> JiuGongGeProject::randomVector(int n)
{
	vector<int> res;
	vector<int> m(n);
	srand(time(0));
	int index;
	for (int i = 0; i < n; i++)
	{
		m[i] = i;
	}
	for (int i = 0; i < n; i++)
	{
		index = rand() % m.size();
		res.push_back(m[index]);
		m.erase(m.begin() + index);
	}
	return res;
}
