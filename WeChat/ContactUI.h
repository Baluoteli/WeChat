#pragma once
#include "Node.h"

namespace DuiLib
{
struct ContactListItemInfo			//�����б���Ϣ �ṹ��
{
	bool				folder;					//�Ƿ�Ϊ��Ŀ¼
	//bool empty;							//�Ƿ��
	NodeType		id;	
	CDuiString	logo;						//ͼ����Դ
	CDuiString	nick_name;			//�ǳ���Դ
	CDuiString	description;			//����ǩ����Դ
	CDuiString	back_name;			//��ע����Դ
	CDuiString	weixin_id;				//΢�ź�
	CDuiString	zone;					//����
	UINT				group_id;				//����ȺID  
};

class CContactUI : public CListUI
{
public:
	CContactUI(CPaintManagerUI& paint_manager);
	~CContactUI(void);
public:
public:
	enum {SCROLL_TIMERID = 10};
	Node* AddNode(const ContactListItemInfo& item, Node* parent);
	void DoEvent(TEventUI& event);
	void RemoveAll();
	bool RemoveNode(Node* node);			//ɾ���ڵ�
private:
	CDialogBuilder				m_dlgBuilder;
	CPaintManagerUI&		paint_manager_;
	LONG							delay_deltaY_;			//������������ٶ��й�
	DWORD						delay_number_;		
	DWORD						delay_left_;
	Node*							root_node_;				//���ڵ�
};
}
