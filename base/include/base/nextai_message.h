#ifndef _TRINITY_MESSAGE_CENTER_H_
#define _TRINITY_MESSAGE_CENTER_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"
#include "base/nextai_message_id.h"
#include <vector>
#include <list>

#define MESSAGE_CENTER() NextAI::MessageCenter::getInstance()

namespace NextAI
{
	class IMessageListener
	{
	public:
		virtual void onMessageNotify(NEXT_AI_MESSAGE_ID id, void* lParam, void* rParam) = 0;
	};

	class MessageCenter
	{
	public:
		/* �������ȼ� */
		enum class ListenerLevel
		{
			Low = 0,		/* �����ȼ���Ĭ�ϣ� */
			Medium,			/* �����ȼ� */
			High,			/* �����ȼ� */
			Max
		};

		/* ��ȡ��Ϣ��ģʽ */
		enum class PeekMessageMode
		{
			NoRemove = 0,	/* ���Ӷ������Ƴ���Ϣ */
			Remove			/* �Ӷ������Ƴ���Ϣ */
		};

	public:
		static MessageCenter* getInstance();

		/* ͬ����Ϣ�ӿ� */
		void send(NEXT_AI_MESSAGE_ID id, void* lParam, void* rParam);			/* ͬ����Ϣ���� */
		void addListener(IMessageListener* listener, ListenerLevel level);		/* ��Ӽ��� */
		void removeListener(IMessageListener* listener, ListenerLevel level);	/* ɾ������ */

		/* �첽��Ϣ�ӿ� */
		void post(NEXT_AI_MESSAGE_ID id);		/* �첽��Ϣ���� */
		BOOL peek(NEXT_AI_MESSAGE_ID& id, PeekMessageMode peekMessageMode); /* �첽��Ϣ��ȡ */
		void clear();							/* �첽��Ϣ������� */
		uint32 count();							/* �첽��Ϣ���� */

	private:
		MessageCenter();
		virtual ~MessageCenter();

		/* ���ÿ������캯�� */
		DISABLE_CLASS_COPY(MessageCenter);

		/* ͬ����Ϣ������ */
		std::vector<IMessageListener*> m_listeners[(int32)ListenerLevel::Max];

		/* �첽��Ϣ���� */
		std::list<NEXT_AI_MESSAGE_ID> m_messages;
	};
}

#endif // !_TRINITY_MESSAGE_CENTER_H_