#pragma once
#include "Node.h"

namespace DuiLib
{
struct FriendListItemInfo			//�����б����Ϣ �ṹ��
{
	bool folder;	
	bool empty;		//�Ƿ��
	NodeType id;	
	CDuiString logo;		//ͼ����Դ
	CDuiString nick_name;	//�ǳ���Դ
	int			weixing_id;
	//CDuiString description;	//����������Դ
};

class CFriendListUI : public CListUI
{
public:
	CFriendListUI(CPaintManagerUI& paint_manager);
	~CFriendListUI(void);
public:
	enum {SCROLL_TIMERID = 10};
	Node* AddNode(const FriendListItemInfo& item, Node* parent,int insertIndex=-1);
	void DoEvent(TEventUI& event);
	void RemoveAll();
	bool RemoveNode(Node* node);			//ɾ���ڵ�
	//bool SelectItem(int iIndex, bool bTakeFocus);
	Node* GetRoot();
private:
	CDialogBuilder m_dlgBuilder;
	CPaintManagerUI& paint_manager_;
	LONG	delay_deltaY_;			//������������ٶ��й�
	DWORD	delay_number_;		
	DWORD	delay_left_;
	Node*	root_node_;				//���ڵ�
};
}