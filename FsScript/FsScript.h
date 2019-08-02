#pragma once

#include "fsscript_global.h"
#include "dm.h"

#include <QSet>
class FSSCRIPT_EXPORT FsScript
{
public:
    FsScript();

	bool bindWindow(QString windowName = QStringLiteral(GameWindowTitle), QString className = QString());
	QString selectPlayer(QSet<QString> &playerSet, int playerCount);
	bool Reg();
	void leftClick(const QPoint &pt, int rx = -10000, int ry = -10000);
	void leftClick(int x, int y, int rx = -10000, int ry = -10000);
	QPoint findPic(QString name, int waitSec = 300, QString delta_color = QStringLiteral("000000"), double sim = 0.95, int dir = 0);

	void setUser(QString usr, QString pwd);
	QString getUser();


	void setBindSetting(QString display, QString mouse, QString keypad, int mode);


	void setGamePath(QString path);
	QString getGamePath();

	void closeLogginAD();
	void closeDaTingAD();
	bool close();
	void createBotRoom();
	bool loggin();
	bool clostWindow(QString name);

	QString gamapath_;
	QString usr_;
	QString pwd_;

	long hwnd_;
	dm::Idmsoft d_;
	


	// 窗口坐标
	int x1_; //整形数: 区域的左上X坐标
	int y1_; //整形数: 区域的左上Y坐标
	int x2_; //整形数: 区域的右下X坐标
	int y2_; //整形数: 区域的右下Y坐标



	struct Resource
	{
		Resource()
		{
			loginWindowStart = QStringLiteral("登陆窗口开始游戏.bmp");
			gameLoggin = QStringLiteral("登录界面登录按钮.bmp");
			beginFight = QStringLiteral("取消对战.bmp");
			daCaochangPt = QStringLiteral("大操场.bmp");
		}
		QString loginWindowStart; 
		QString gameLoggin;
		QString beginFight;
		QString daCaochangPt;
	}rs_;

	struct MousePos
	{
		MousePos()
		{
			createRoom = QPoint(100, 100);
			//cancelFight = QPoint(100, 100);
		}
		QPoint createRoom;
		//QPoint cancelFight;
	}mpos_;

	struct BindSetting
	{
		BindSetting() 
		{
			display = QStringLiteral("gdi");
			mouse = QStringLiteral("dx");
			keypad = QStringLiteral("dx");
			mode = 0;
		}
		// "normal" : 正常模式, 平常我们用的前台截屏模式
		// "gdi" : gdi模式, 用于窗口采用GDI方式刷新时.此模式占用CPU较大.参考SetAero  win10以上系统使用此模式，如果截图失败，尝试把目标程序重新开启再试试。
		// "gdi2" : gdi2模式, 此模式兼容性较强, 但是速度比gdi模式要慢许多, 如果gdi模式发现后台不刷新时, 可以考虑用gdi2模式.
		// "dx2" : dx2模式, 用于窗口采用dx模式刷新, 如果dx方式会出现窗口所在进程崩溃的状况, 可以考虑采用这种.采用这种方式要保证窗口有一部分在屏幕外.win7 win8或者vista不需要移动也可后台.此模式占用CPU较大.参考SetAero.win10以上系统使用此模式，如果截图失败，尝试把目标程序重新开启再试试。
		// "dx3" : dx3模式, 同dx2模式, 但是如果发现有些窗口后台不刷新时, 可以考虑用dx3模式, 此模式比dx2模式慢许多.此模式占用CPU较大.参考SetAero.win10以上系统使用此模式，如果截图失败，尝试把目标程序重新开启再试试。
		// "dx" : dx模式, 等同于BindWindowEx中，display设置的"dx.graphic.2d|dx.graphic.3d", 具体参考BindWindowEx
		QString display;

		// "normal" : 正常模式, 平常我们用的前台鼠标模式
		// "windows" : Windows模式, 采取模拟windows消息方式 同按键自带后台插件.
		// "windows2" : Windows2 模式, 采取模拟windows消息方式(锁定鼠标位置) 此模式等同于BindWindowEx中的mouse为以下组合
		// "dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.state.message"
		// "windows3" : Windows3模式，采取模拟windows消息方式, 可以支持有多个子窗口的窗口后台.
		// "dx" : dx模式, 采用模拟dx后台鼠标模式, 这种方式会锁定鼠标输入.有些窗口在此模式下绑定时，需要先激活窗口再绑定(或者绑定以后激活)，否则可能会出现绑定后鼠标无效的情况.此模式等同于BindWindowEx中的mouse为以下组合
		// "dx.public.active.api|dx.public.active.message|dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.state.api|dx.mouse.state.message|dx.mouse.api|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api|dx.mouse.cursor"
		// "dx2"：dx2模式, 这种方式类似于dx模式, 但是不会锁定外部鼠标输入.
		// 有些窗口在此模式下绑定时，需要先激活窗口再绑定(或者绑定以后手动激活)，否则可能会出现绑定后鼠标无效的情况.此模式等同于BindWindowEx中的mouse为以下组合
		// "dx.public.active.api|dx.public.active.message|dx.mouse.position.lock.api|dx.mouse.state.api|dx.mouse.api|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api| dx.mouse.cursor"
		QString mouse;

		// "normal" : 正常模式, 平常我们用的前台键盘模式
		// "windows" : Windows模式, 采取模拟windows消息方式 同按键的后台插件.
		// "dx" : dx模式, 采用模拟dx后台键盘模式。有些窗口在此模式下绑定时，需要先激活窗口再绑定(或者绑定以后激活)，否则可能会出现绑定后键盘无效的情况.此模式等同于BindWindowEx中的keypad为以下组合
		// "dx.public.active.api|dx.public.active.message| dx.keypad.state.api|dx.keypad.api|dx.keypad.input.lock.api"
		QString keypad;

		// 0 : 推荐模式此模式比较通用，而且后台效果是最好的.
		// 2 : 同模式0, 如果模式0有崩溃问题，可以尝试此模式.注意0和2模式，当主绑定(第一个绑定同个窗口的对象)绑定成功后，那么调用主绑定的线程必须一致维持, 否则线程一旦推出, 对应的绑定也会消失.
		// 101 : 超级绑定模式.可隐藏目标进程中的dm.dll.避免被恶意检测.效果要比dx.public.hide.dll好.推荐使用.
		// 103 : 同模式101，如果模式101有崩溃问题，可以尝试此模式.
		// 11 : 需要加载驱动, 适合一些特殊的窗口, 如果前面的无法绑定，可以尝试此模式.此模式不支持32位系统
		// 13 : 需要加载驱动, 适合一些特殊的窗口, 如果前面的无法绑定，可以尝试此模式.此模式不支持32位系统
		// 需要注意的是 : 模式101 103在大部分窗口下绑定都没问题。但也有少数特殊的窗口，比如有很多子窗口的窗口，对于这种窗口，在绑定时，一定要把
		// 鼠标指向一个可以输入文字的窗口，比如一个文本框，最好能激活这个文本框，这样可以保证绑定的成功.
		int mode;
	}bindSetting_;
};
