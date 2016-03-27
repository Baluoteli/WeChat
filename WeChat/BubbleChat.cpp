#include "StdAfx.h"
#include "BubbleChat.h"

static double GetTextWidth(const TCHAR *text);
CBubbleChat::CBubbleChat(CPaintManagerUI& paint_manager) : paint_manager_(paint_manager), delay_deltaY_(0), delay_number_(0), delay_left_(0)
{
	root_node_ = new Node;
	root_node_->data().list_elment_ = NULL;
}


CBubbleChat::~CBubbleChat(void)
{
	RemoveAll();
	if (root_node_)
		delete root_node_;
	root_node_ = NULL;
}

Node* DuiLib::CBubbleChat::AddNode(const BubbleItemInfo& item, Node* parent)
{
	if(parent == NULL)
		parent = root_node_;

	CListContainerElementUI* pListElement = NULL;
	if( !m_dlgBuilder.GetMarkup()->IsValid() )
		pListElement = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(L"bubble_edit.xml", (UINT)0, NULL, &paint_manager_));
	else
	{
		pListElement = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create((UINT)0, &paint_manager_));
	}
	if (pListElement == NULL)
		return NULL;

	Node* node = new Node;
	node->data().list_elment_ = pListElement;		//�����б�ؼ�
	//node->data().text_ = item.text;

	CButtonUI* log_button = static_cast<CButtonUI*>(paint_manager_.FindSubControlByName(pListElement, L"chat_logo"));//��ͼ�갴ť
	if(log_button != NULL)
	{
		log_button->SetNormalImage(L"c2.png");
		log_button->SetFixedHeight(34);
		log_button->SetFixedWidth(34);
	}

	RECT rect={0,10,0,10};
	pListElement->SetInset(rect);

	CRichEditUI* log_text = static_cast<CRichEditUI*>(paint_manager_.FindSubControlByName(pListElement, L"chat_text"));
	if(log_text !=NULL)
	{
		int cx = (int)GetTextWidth(item.buf);	
		int off = cx / 337;
		if(off >=1) 
		{
			log_text->SetFixedWidth(336);
			log_text->SetFixedHeight(34*(off+1)-off*10);
			pListElement->SetFixedHeight(log_text->GetFixedHeight()+20);
			log_text->SetNormalImage(L"file='RichEdit_normal.png' corner='10,22,5,5'");
		}
		else
		{
			//log_text->SetFixedWidth(cx+15+5+5);
			log_text->SetFixedWidth(cx +15 + 3);
			log_text->SetFixedHeight(34);
			pListElement->SetFixedHeight(log_text->GetFixedHeight()+20);
			log_text->SetNormalImage(L"file='RichEdit_normal.png' corner='10,5,5,5'");
		}
		log_text->SetText(item.buf);
	}
	int index = 0;
	if(parent->has_children())
	{
		Node* prev = parent->get_last_child();
		index = prev->data().list_elment_->GetIndex()+1;
	}
	else
	{
		if(parent == root_node_)
			index = 0;
		else
			index = parent->data().list_elment_->GetIndex()+1;
	}
	bool ret = CListUI::AddAt(pListElement, index);
	if(ret == false)
	{
		delete pListElement;
		delete node;
		node = NULL;
		return NULL;
	}
	parent->add_child(node);
	return node;
}

double DuiLib::CBubbleChat::GetTextWidth(const TCHAR *text)
{
	double nLen = 0;
	int length = wcslen(text);
	for (int i=0; i<length; ++i)
	{
		switch(text[i])
		{
		case 'A':
		case 'C':
		case 'V':
			nLen+=8.5;
			break;
		case 'D':
		case 'G':
		case 'H':
		case 'U':
		//Сд
		case 'w':
		//Ӣ�ı��
		case '&':
		case '^':
		case '=':
		case '~':
		case '+':
			nLen+=10;
			break;
		case 'T':
		case 'L':
		case 'F':
		case 'E':
		//Сд
		case 'x':
		case 'y':
		case 'k':
		case 'a':
		case 'c':
		case 'v':
		case 'e':
			nLen+=7;
			break;
		case 'I':
		//�ո�
		case ' ':
		case '|':
		case '{':
		case '}':
		case '[':
		case ']':
			nLen+=4;
			break;
		case 'J':
		//Сд 
		case 'r':
		case 'f':
		case 't':
		//Ӣ�ı��
		case '\\':
			nLen +=5;
			break;
		case 'S':
		case 'R':
		case 'B':
		case 'X':
		case 'K':
		case 'P':
		case 'Y':
		case 'Z':
		//Сд
		case 'n':
		case 'o':
		case 'q':
		case 'd':
		case 'g':
		case 'h':
		case 'u':
		case 'p':
		case 'b':
		//����
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '0':
		//Ӣ�ı��
		case '#':
		case '$':
			nLen += 8;
			break;
		case 'N':
		case 'O':
		case 'Q':
			nLen += 11;
			break;
		case 'W':
		case 'M':
		//���ı��
		case '��':
		case '��':
		case '��':
		case '��':
		case '��':
		case '��':
			nLen += 13;
			break;
		//Сд
		case 'l':
		case 'i':
		case 'j':
		//Ӣ�ı��
		case '.':
		case ',':
		case '`':
		case '!':
		case '(':
		case ')':
		case ':':
		case ';':
		case '\'':
			nLen +=3;
			break;
		//Сд
		case 'm':
		//Ӣ�ı��
		case '%':
			nLen += 12;
			break;
		//Сд
		case 's':
		case 'z':
		//Ӣ�ı��
		case '*':
		case '/':
		case '-':
		case '_':
			nLen += 6;
			break;
		//Ӣ�ı��
		case '@':
			nLen += 13;
			break;
		default:
			nLen += 13;
			break;
		}
	}
	return ceil(nLen);
}

void DuiLib::CBubbleChat::RemoveAll()
{
	CListUI::RemoveAll();
	for (int i=0; i<root_node_->num_children(); ++i)
	{
		Node* child = root_node_->child(i);
		RemoveNode(child);
	}
	delete root_node_;

	root_node_ = new Node;
	root_node_->data().list_elment_ = NULL;
}

bool DuiLib::CBubbleChat::RemoveNode(Node* node)
{
	if(!node || node == root_node_)
		return false;
	for (int i=0; i<node->num_children(); ++i)
	{
		Node* child = node->child(i);
		RemoveNode(child);
	}

	CListUI::Remove(node->data().list_elment_);
	node->parent()->remove_child(node);
	delete node;
	node = NULL;
	return true;
}

void CBubbleChat::DoEvent(TEventUI& event) 
{
	// 	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	// 	{
	// 		if (m_pParent != NULL)
	// 			m_pParent->DoEvent(event);
	// 		else
	// 			CVerticalLayoutUI::DoEvent(event);
	// 		return;
	// 	}
	if( event.Type == UIEVENT_MOUSEENTER )
	{
		int a = 1;
	}
	if (event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID)
	{
		if (delay_left_ > 0)
		{
			--delay_left_;
			SIZE sz = GetScrollPos();
			LONG lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
			if ((lDeltaY > 0 && sz.cy != 0)  || (lDeltaY < 0 && sz.cy != GetScrollRange().cy ))
			{
				sz.cy -= lDeltaY;
				SetScrollPos(sz);
				return;
			}
		}
		delay_deltaY_ = 0;
		delay_number_ = 0;
		delay_left_ = 0;
		m_pManager->KillTimer(this, SCROLL_TIMERID);
		return;
	}
	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		LONG lDeltaY = 0;
		if (delay_number_ > 0)
			lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
		switch (LOWORD(event.wParam))
		{
		case SB_LINEUP:
			if (delay_deltaY_ >= 0)
				delay_deltaY_ = lDeltaY + 7;
			else
				delay_deltaY_ = lDeltaY + 11;
			break;
		case SB_LINEDOWN:
			if (delay_deltaY_ <= 0)
				delay_deltaY_ = lDeltaY - 7;
			else
				delay_deltaY_ = lDeltaY - 11 ;
			break;
		}
		if
			(delay_deltaY_ > 100) delay_deltaY_ = 100;
		else if
			(delay_deltaY_ < -100) delay_deltaY_ = -100;

		delay_number_ = (DWORD)sqrt((double)abs(delay_deltaY_)) * 5;
		delay_left_ = delay_number_;
		m_pManager->SetTimer(this, SCROLL_TIMERID, 20U);
		return;
	}

	CListUI::DoEvent(event);
}