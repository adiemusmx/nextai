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
		/* 监听优先级 */
		enum class ListenerLevel
		{
			Low = 0,		/* 低优先级（默认） */
			Medium,			/* 中优先级 */
			High,			/* 高优先级 */
			Max
		};

		/* 提取消息的模式 */
		enum class PeekMessageMode
		{
			NoRemove = 0,	/* 不从队列中移除消息 */
			Remove			/* 从队列中移除消息 */
		};

	public:
		static MessageCenter* getInstance();

		/* 同步消息接口 */
		void send(NEXT_AI_MESSAGE_ID id, void* lParam, void* rParam);			/* 同步消息发送 */
		void addListener(IMessageListener* listener, ListenerLevel level);		/* 添加监听 */
		void removeListener(IMessageListener* listener, ListenerLevel level);	/* 删除监听 */

		/* 异步消息接口 */
		void post(NEXT_AI_MESSAGE_ID id);		/* 异步消息发送 */
		BOOL peek(NEXT_AI_MESSAGE_ID& id, PeekMessageMode peekMessageMode); /* 异步消息提取 */
		void clear();							/* 异步消息队列清空 */
		uint32 count();							/* 异步消息数量 */

	private:
		MessageCenter();
		virtual ~MessageCenter();

		/* 禁用拷贝构造函数 */
		DISABLE_CLASS_COPY(MessageCenter);

		/* 同步消息监听者 */
		std::vector<IMessageListener*> m_listeners[(int32)ListenerLevel::Max];

		/* 异步消息队列 */
		std::list<NEXT_AI_MESSAGE_ID> m_messages;
	};
}

#endif // !_TRINITY_MESSAGE_CENTER_H_