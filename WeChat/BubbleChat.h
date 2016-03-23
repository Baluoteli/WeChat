#pragma once
#include "Node.h"

namespace DuiLib
{
	struct BubbleItemInfo			//�����б���Ϣ �ṹ��
	{
		//NodeType		id;	
		TCHAR buf[MAX_PATH];
	};
	class CBubbleChat : public CListUI
	{
	public:
		CBubbleChat(CPaintManagerUI& paint_manager);
		~CBubbleChat(void);
	public:
		enum {SCROLL_TIMERID = 10};
		Node* AddNode(const BubbleItemInfo& item, Node* parent);
	private:
		CDialogBuilder				m_dlgBuilder;
		CPaintManagerUI&		paint_manager_;
		LONG							delay_deltaY_;			//������������ٶ��й�
		DWORD						delay_number_;		
		DWORD						delay_left_;
		Node*							root_node_;				//���ڵ�
	};
}
