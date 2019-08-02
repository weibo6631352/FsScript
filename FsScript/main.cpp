#include "FsScript.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds



void run()
{
	QString players = QStringLiteral("p1\np2");
	int playerCount = 10;


	QSet<QString> playerSet = players.split(QStringLiteral(" ")).toSet();


	FsScript fs;
	if (!fs.Reg())
		return;
	fs.setBindSetting(QStringLiteral("gdi"), QStringLiteral("dx"), QStringLiteral("dx"), 0);
	fs.setUser(QStringLiteral("18937962212"), QStringLiteral("66313527a"));
	

	QString cur_player;
	while (playerSet.count())
	{
		fs.loggin();
		fs.closeLogginAD();
		cur_player = fs.selectPlayer(playerSet, playerCount);  // todo
		if (cur_player.isEmpty())
			break;
		fs.closeDaTingAD();

		fs.createBotRoom(); // todo


		QPoint beginPt(0, 0);
		while (beginPt.x() == 0 && beginPt.y() == 0)
		{
			beginPt = fs.findPic(fs.rs_.beginFight, 20);
		}
		fs.leftClick(beginPt);
		std::this_thread::sleep_for(std::chrono::milliseconds(8000));

		QPoint enterGamePt(0, 0);
		while (enterGamePt.x() == 0 && enterGamePt.y() == 0)
		{
			enterGamePt = fs.findPic(fs.rs_.daCaochangPt, 20);
		}
		fs.close();
	}
}