#include "base/nextai_message.h"
#include "base/nextai_log.h"

namespace NextAI
{

	MessageCenter* MessageCenter::getInstance()
	{
		static MessageCenter instance;
		return &instance;
	}

	void MessageCenter::send(NEXT_AI_MESSAGE_ID id, void* lParam, void* rParam)
	{
		NEXTAI_TRACE_LOG_FLAG("parameter id[%d] lParam[%p] rParam[%p]", id, lParam, rParam);

		for (int32 loopIdx = (int32)ListenerLevel::Low; loopIdx < (int32)ListenerLevel::Max; ++loopIdx)
		{
			std::vector<IMessageListener*> tmpVector = m_listeners[loopIdx];
			std::vector<IMessageListener*>::iterator iter = tmpVector.begin();
			while (iter != tmpVector.end())
			{
				(*iter)->onMessageNotify(id, lParam, rParam);
				++iter;
			}
		}
	}

	void MessageCenter::addListener(IMessageListener* listener, ListenerLevel level)
	{
		NEXTAI_TRACE_LOG_FLAG("parameter listener[%p] level[%d]", listener, level);

		if (level < ListenerLevel::Low || level > ListenerLevel::High)
		{
			NEXTAI_WARNING_LOG("Invalid level[%d].", (int32)level);
			return;
		}

		if (listener != NULL)
		{
			NEXTAI_WARNING_LOG("Listener is NULL.");
			return;
		}

		m_listeners[(int32)level].push_back(listener);
	}

	void MessageCenter::removeListener(IMessageListener* listener, ListenerLevel level)
	{
		NEXTAI_TRACE_LOG_FLAG("parameter listener[%p] level[%d]", listener, level);

		if (level < ListenerLevel::Low || level > ListenerLevel::High)
		{
			NEXTAI_WARNING_LOG("Invalid level[%d].", (int32)level);
			return;
		}

		if (listener != NULL)
		{
			NEXTAI_WARNING_LOG("Listener is NULL.");
			return;
		}

		m_listeners[(int32)level].erase(std::find(m_listeners[(int32)level].begin(), m_listeners[(int32)level].end(), listener));
	}

	void MessageCenter::post(NEXT_AI_MESSAGE_ID id)
	{
		NEXTAI_TRACE_LOG_FLAG("parameter id[%d]", id);

		m_messages.push_back(id);
	}

	BOOL MessageCenter::peek(NEXT_AI_MESSAGE_ID& id, PeekMessageMode mode)
	{
		NEXTAI_TRACE_LOG_FLAG("parameter id[%d] mode[%d]", id, mode);

		/* 消息大小 */
		if (m_messages.size() == 0)
		{
			return FALSE;
		}

		/* 取出消息 */
		id = *(m_messages.begin());

		/* 清空队列开始 */
		if (mode == PeekMessageMode::Remove)
		{
			m_messages.pop_front();
		}
		return TRUE;
	}

	void MessageCenter::clear()
	{
		NEXTAI_TRACE_LOG();

		m_messages.clear();
	}

	uint32 MessageCenter::count()
	{
		return m_messages.size();
	}

	MessageCenter::MessageCenter()
	{

	}

	MessageCenter::~MessageCenter()
	{
		for (int32 loopIdx = (int32)ListenerLevel::Low; loopIdx < (int32)ListenerLevel::Max; ++loopIdx)
		{
			m_listeners[loopIdx].clear();
		}

		m_messages.clear();
	}

}