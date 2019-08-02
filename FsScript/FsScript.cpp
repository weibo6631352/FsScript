#include "FsScript.h"
#include <QDebug>
#include <QFile>

#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

FsScript::FsScript()
{
	x1_ = 0;
	y1_ = 0;
	x2_ = 0;
	y2_ = 0;

	
	d_.EnableRealKeypad(1);
	d_.EnableRealMouse(2, 20, 30);
}

bool FsScript::bindWindow(QString windowName, QString className)
{
	qDebug() << "bindWindow" << windowName << "\n";
	d_.UnBindWindow();
	hwnd_ = 0;
	while (!hwnd_)
	{
		hwnd_ = d_.FindWindow(className, windowName);
	}

	d_.BindWindow(hwnd_, bindSetting_.display, bindSetting_.mouse, bindSetting_.keypad, bindSetting_.mode);

	QVariant x1, y1, x2, y2;
	if (!d_.GetWindowRect(hwnd_, x1, y1, x2, y2))
		qWarning() << "bindWindow" << windowName << "fail.\n";


	x1_ = x1.toInt();
	y1_ = y1.toInt();
	x2_ = x2.toInt();
	y2_ = y2.toInt();
	return true;
}

QString FsScript::selectPlayer(QSet<QString> &playerSet, int playerCount)
{
	QString player;
	playerCount += 5;
	for (int i = 0; i < playerCount; ++i)
	{
		// todo

		// 得到角色名
		QString jueSeMing;

		QSet<QString> ::iterator it = playerSet.find(jueSeMing);
		if (it != playerSet.end())
		{
			player = *it;
			playerSet.erase(it);
			return player;
		}


		// 换下个角色
	}
	return QString();
}

bool FsScript::Reg()
{
	if (d_.Reg(QStringLiteral(DMReg), QStringLiteral("")) != 1)
	{
		qDebug() << "插件注册失败，请联系管理员" << "\n";
		return false;
	}
	else
	{
		return true;
	}
}

void FsScript::leftClick(const QPoint &pt, int rx, int ry)
{
	if (rx == -10000)
		rx = rand() % 5 + 1;
	if (ry == -10000)
		ry = rand() % 5 + 1;
	d_.MoveTo(pt.x() + rx, pt.y()+ry);
	d_.LeftClick();
}

void FsScript::leftClick(int x, int y, int rx, int ry)
{
	if (rx == -10000)
		rx = rand() % 5 + 1;
	if (ry == -10000)
		ry = rand() % 5 + 1;
	d_.MoveTo(x + rx, y + ry);
	d_.LeftClick();
}

void FsScript::setUser(QString usr, QString pwd)
{
	usr_ = usr;
	pwd_ = pwd;
}

QString FsScript::getUser()
{
	return usr_;
}

void FsScript::setBindSetting(QString display, QString mouse, QString keypad, int mode)
{
	bindSetting_.display = display;
	bindSetting_.mouse = mouse;
	bindSetting_.keypad = keypad;
	bindSetting_.mode = mode;
}

void FsScript::setGamePath(QString path)
{
	gamapath_ = path;
}

QString FsScript::getGamePath()
{
	return gamapath_;
}

void FsScript::closeLogginAD()
{
	QFile file("LoginAdCloseScript.sp");  
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString t;
		while (!file.atEnd())
		{
			t = QString::fromLocal8Bit(file.readLine());
			if (t.isEmpty())
				continue;

			QStringList ql = t.split(QStringLiteral(" "));
			if (ql.size() == 2)
			{
				leftClick(ql[0].toInt(), ql[1].toInt());
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ql[0].toInt()));
			}
		}
		file.close();
	}
}

void FsScript::closeDaTingAD()
{
	QFile file("DaTingAdCloseScript.sp");
	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QString t;
		while (!file.atEnd())
		{
			t = QString::fromLocal8Bit(file.readLine());
			if (t.isEmpty())
				continue;

			QStringList ql = t.split(QStringLiteral(" "));
			if (ql.size() == 2)
			{
				leftClick(ql[0].toInt(), ql[1].toInt());
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(ql[0].toInt()));
			}
		}
		file.close();
	}
}

bool FsScript::close()
{
	// 关闭
	qDebug() << "Close Game..." << "\n";
	if (!clostWindow(QStringLiteral(GameWindowTitle)) || !clostWindow(QStringLiteral(loginWindowTitle)))
	{
		qWarning() << "Close Game fail." << "\n";
		return false;
	}
}

void FsScript::createBotRoom()
{
	// todo
}

bool FsScript::loggin()
{
	qDebug() << "Loggin..." << "\n";
	
	close();
	// 启动
	qDebug() << "Run Game..." << "\n";
	d_.RunApp(gamapath_, 1);


	bindWindow(loginWindowTitle);
	QPoint pt = findPic(rs_.loginWindowStart);
	leftClick(pt);

	// 登录
	bindWindow(GameWindowTitle);
	bool isFindLoggin = false;
	while (isFindLoggin == false)
	{
		QPoint pt = findPic(rs_.gameLoggin);
		leftClick(pt);
		isFindLoggin = true;
	}
	d_.KeyPressStr(usr_, 50);
	d_.KeyDown(9);
	d_.KeyPressStr(pwd_, 50);

	// 关闭广告


	return true;
}

QPoint FsScript::findPic(QString name, int waitSec, QString delta_color, double sim, int dir)
{
	QPoint pt;
	QVariant x, y;
	qDebug() << QStringLiteral("findPic...") << name << "\n";

	auto start = std::chrono::system_clock::now();
	int isFind = -1;
	while (isFind == -1)
	{
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - start);
		if (duration.count() > waitSec)
		{
			qWarning() << QStringLiteral("搜索图片超时.") << name << "\n";
			return pt;
		}
		isFind = d_.FindPic(x1_, y1_, x2_, y2_, name, delta_color, sim, dir, x, y);
	}

	pt.rx() = x.toInt();
	pt.ry() = y.toInt();

	return pt;
}

bool FsScript::clostWindow(QString name)
{
	long hwnd = 0;
	long close_res = 0;
	if ((hwnd = d_.FindWindow(QStringLiteral(""), QStringLiteral(GameWindowTitle))) == 0
		|| (close_res = d_.SetWindowState(hwnd, 0) == 0))
	{
		return false;
	}

	return true;
}
