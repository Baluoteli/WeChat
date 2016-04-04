#pragma once
#include <set>
#include "FriendListUI.h"
#include "ContactUI.h"
#include "BubbleChat.h"
#include "DuiTrayIcon.h"
#include "History.h"
#include "MessageWnd.h"
#include "SettingFrame.h"

class CMainFrame : public WindowImplBase
{
public:
	CMainFrame(void);
	~CMainFrame(void);
public:
public:
	LPCTSTR    GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	void OnPrepare();
	virtual void Notify( TNotifyUI& msg );
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKeyReturn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnOwnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT On_TroyIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	CControlUI* CreateControl(LPCTSTR pstrClass);
	void UpgrateFriends();
	void UpgrateContacts();
	ContactListItemInfo* FindContactItem(CDuiString &name);
	std::vector<ContactListItemInfo*> FindContactItemBygroupID(UINT id);
	void OnSelectFriendList(TNotifyUI& msg, CFriendListUI* pFriendsList);
	void OnSelectContactList(TNotifyUI& msg, CContactUI* pFriendsList);
	void OnSendMessage();
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void AddMegTip(Node* ClickNode);
	void AddLastMsg(LPCTSTR buffer);
	void AddCachMsg(Node* root, int id);
	void OnSetting(bool flag=0);
	Node* FindClickNodeByID(const int id);
	void CloseALLWindows();
	void OnBegChat(TNotifyUI& msg);
	void AddNodeToFriendList();
private:
	std::vector<FriendListItemInfo> friends_;		//���������Ϣ�б�
	std::vector<ContactListItemInfo> contact_;	//����ͨѶ¼��Ϣ�б�
	std::vector<Node*> friendsNode;					//����ӵ������ϵ�˽ڵ�
	
	bool b_msg;													//�Ƿ�����Ϣ
	int Msgcount;												//��Ϣ������

	CHistory*	m_history;										//�����¼

	CDuiTrayIcon* icon;										//���̲˵�
	bool isShow;													//���̴����Ƿ񴴽�
	CMessageWnd *pMsgWnd;							//������Ϣ����

	CSettingFrame *settingFrame;						//���ô��� 

	Node* selectItemNode_Fri;							//��ǰѡ�еĺ����б�ڵ�
	Node* selectItemNode_Con;							//��ǰѡ�е���ϵ���б�ڵ�
	int weixing_id;												//��ǰѡ�еĽڵ��΢�ź�

	CButtonUI*						pButton_MsgTip;						//��Ϣ�����ؼ�
	CTabLayoutUI*					pTabLayout;							
	CFriendListUI*					pFriendsList;
	CContactUI*						pContactsList;			
	CTileLayoutUI*					m_group_list;					
	CBubbleChat*					pBubbleList;							//��ʾ�����¼�ı༭���б�
	CRichEditUI*						pInputEdit;								//���촰�ڵ�����༭��
	CButtonUI*						pButtonSet;								//����������ð�ť
	COptionUI*						pOptionChat;
	CTabLayoutUI*					pTabs;
	CLabelUI*							pChatName;	
};

