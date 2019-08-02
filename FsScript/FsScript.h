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
	


	// ��������
	int x1_; //������: ���������X����
	int y1_; //������: ���������Y����
	int x2_; //������: ���������X����
	int y2_; //������: ���������Y����



	struct Resource
	{
		Resource()
		{
			loginWindowStart = QStringLiteral("��½���ڿ�ʼ��Ϸ.bmp");
			gameLoggin = QStringLiteral("��¼�����¼��ť.bmp");
			beginFight = QStringLiteral("ȡ����ս.bmp");
			daCaochangPt = QStringLiteral("��ٳ�.bmp");
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
		// "normal" : ����ģʽ, ƽ�������õ�ǰ̨����ģʽ
		// "gdi" : gdiģʽ, ���ڴ��ڲ���GDI��ʽˢ��ʱ.��ģʽռ��CPU�ϴ�.�ο�SetAero  win10����ϵͳʹ�ô�ģʽ�������ͼʧ�ܣ����԰�Ŀ��������¿��������ԡ�
		// "gdi2" : gdi2ģʽ, ��ģʽ�����Խ�ǿ, �����ٶȱ�gdiģʽҪ�����, ���gdiģʽ���ֺ�̨��ˢ��ʱ, ���Կ�����gdi2ģʽ.
		// "dx2" : dx2ģʽ, ���ڴ��ڲ���dxģʽˢ��, ���dx��ʽ����ִ������ڽ��̱�����״��, ���Կ��ǲ�������.�������ַ�ʽҪ��֤������һ��������Ļ��.win7 win8����vista����Ҫ�ƶ�Ҳ�ɺ�̨.��ģʽռ��CPU�ϴ�.�ο�SetAero.win10����ϵͳʹ�ô�ģʽ�������ͼʧ�ܣ����԰�Ŀ��������¿��������ԡ�
		// "dx3" : dx3ģʽ, ͬdx2ģʽ, �������������Щ���ں�̨��ˢ��ʱ, ���Կ�����dx3ģʽ, ��ģʽ��dx2ģʽ�����.��ģʽռ��CPU�ϴ�.�ο�SetAero.win10����ϵͳʹ�ô�ģʽ�������ͼʧ�ܣ����԰�Ŀ��������¿��������ԡ�
		// "dx" : dxģʽ, ��ͬ��BindWindowEx�У�display���õ�"dx.graphic.2d|dx.graphic.3d", ����ο�BindWindowEx
		QString display;

		// "normal" : ����ģʽ, ƽ�������õ�ǰ̨���ģʽ
		// "windows" : Windowsģʽ, ��ȡģ��windows��Ϣ��ʽ ͬ�����Դ���̨���.
		// "windows2" : Windows2 ģʽ, ��ȡģ��windows��Ϣ��ʽ(�������λ��) ��ģʽ��ͬ��BindWindowEx�е�mouseΪ�������
		// "dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.state.message"
		// "windows3" : Windows3ģʽ����ȡģ��windows��Ϣ��ʽ, ����֧���ж���Ӵ��ڵĴ��ں�̨.
		// "dx" : dxģʽ, ����ģ��dx��̨���ģʽ, ���ַ�ʽ�������������.��Щ�����ڴ�ģʽ�°�ʱ����Ҫ�ȼ�����ٰ�(���߰��Ժ󼤻�)��������ܻ���ְ󶨺������Ч�����.��ģʽ��ͬ��BindWindowEx�е�mouseΪ�������
		// "dx.public.active.api|dx.public.active.message|dx.mouse.position.lock.api|dx.mouse.position.lock.message|dx.mouse.state.api|dx.mouse.state.message|dx.mouse.api|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api|dx.mouse.cursor"
		// "dx2"��dx2ģʽ, ���ַ�ʽ������dxģʽ, ���ǲ��������ⲿ�������.
		// ��Щ�����ڴ�ģʽ�°�ʱ����Ҫ�ȼ�����ٰ�(���߰��Ժ��ֶ�����)��������ܻ���ְ󶨺������Ч�����.��ģʽ��ͬ��BindWindowEx�е�mouseΪ�������
		// "dx.public.active.api|dx.public.active.message|dx.mouse.position.lock.api|dx.mouse.state.api|dx.mouse.api|dx.mouse.focus.input.api|dx.mouse.focus.input.message|dx.mouse.clip.lock.api|dx.mouse.input.lock.api| dx.mouse.cursor"
		QString mouse;

		// "normal" : ����ģʽ, ƽ�������õ�ǰ̨����ģʽ
		// "windows" : Windowsģʽ, ��ȡģ��windows��Ϣ��ʽ ͬ�����ĺ�̨���.
		// "dx" : dxģʽ, ����ģ��dx��̨����ģʽ����Щ�����ڴ�ģʽ�°�ʱ����Ҫ�ȼ�����ٰ�(���߰��Ժ󼤻�)��������ܻ���ְ󶨺������Ч�����.��ģʽ��ͬ��BindWindowEx�е�keypadΪ�������
		// "dx.public.active.api|dx.public.active.message| dx.keypad.state.api|dx.keypad.api|dx.keypad.input.lock.api"
		QString keypad;

		// 0 : �Ƽ�ģʽ��ģʽ�Ƚ�ͨ�ã����Һ�̨Ч������õ�.
		// 2 : ͬģʽ0, ���ģʽ0�б������⣬���Գ��Դ�ģʽ.ע��0��2ģʽ��������(��һ����ͬ�����ڵĶ���)�󶨳ɹ�����ô�������󶨵��̱߳���һ��ά��, �����߳�һ���Ƴ�, ��Ӧ�İ�Ҳ����ʧ.
		// 101 : ������ģʽ.������Ŀ������е�dm.dll.���ⱻ������.Ч��Ҫ��dx.public.hide.dll��.�Ƽ�ʹ��.
		// 103 : ͬģʽ101�����ģʽ101�б������⣬���Գ��Դ�ģʽ.
		// 11 : ��Ҫ��������, �ʺ�һЩ����Ĵ���, ���ǰ����޷��󶨣����Գ��Դ�ģʽ.��ģʽ��֧��32λϵͳ
		// 13 : ��Ҫ��������, �ʺ�һЩ����Ĵ���, ���ǰ����޷��󶨣����Գ��Դ�ģʽ.��ģʽ��֧��32λϵͳ
		// ��Ҫע����� : ģʽ101 103�ڴ󲿷ִ����°󶨶�û���⡣��Ҳ����������Ĵ��ڣ������кܶ��Ӵ��ڵĴ��ڣ��������ִ��ڣ��ڰ�ʱ��һ��Ҫ��
		// ���ָ��һ�������������ֵĴ��ڣ�����һ���ı�������ܼ�������ı����������Ա�֤�󶨵ĳɹ�.
		int mode;
	}bindSetting_;
};
