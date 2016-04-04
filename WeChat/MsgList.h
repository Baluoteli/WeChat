#pragma once
#include "Node.h"

namespace DuiLib
{
	typedef struct TroyMsgData
	{
		CDuiString	LogoPath;//ͷ����Դ·��
		CDuiString	name;		//����
		int				weixing_id;
	}TroyMsgData;
	class CMsgList : public CListUI
	{
		public:
			CMsgList(CPaintManagerUI& paint_manager);
			~CMsgList(void);
		public:
			Node* AddNode(const TroyMsgData& item, Node* parent);
			void RemoveAll();
			bool RemoveNode(Node* node);			//ɾ���ڵ�
		private:
			CDialogBuilder				m_dlgBuilder;
			CPaintManagerUI&		paint_manager_;
			Node*							root_node_;				//���ڵ�
	};
}
