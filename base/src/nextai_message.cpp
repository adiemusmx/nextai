#include "stdafx.h"
#include "base/nextai_message.h"

namespace NextAI
{

	MessageCenter* MessageCenter::instance()
	{
		static MessageCenter instance;
		return &instance;
	}

	void MessageCenter::send(NEXT_AI_MESSAGE_ID id, void* lParam, void* rParam)
	{
		BASE_TRACE_LOG("parameter id[{}] lParam[{}] rParam[{}]", (int32)id, (void*)lParam, (void*)rParam);

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
		BASE_TRACE_LOG("parameter listener[{}] level[{}]", (void*)listener, level);

		if (level < ListenerLevel::Low || level > ListenerLevel::High)
		{
			BASE_WARN_LOG("Invalid level[{}].", level);
			return;
		}

		if (listener != NULL)
		{
			BASE_WARN_LOG("Listener is NULL.");
			return;
		}

		m_listeners[(int32)level].push_back(listener);
	}

	void MessageCenter::removeListener(IMessageListener* listener, ListenerLevel level)
	{
		NEXTAI_TRACE_LOG("BASE", "parameter listener[{}] level[{}]", (void*)listener, level);

		if (level < ListenerLevel::Low || level > ListenerLevel::High)
		{
			BASE_WARN_LOG("Invalid level[{}].", (int32)level);
			return;
		}

		if (listener != NULL)
		{
			BASE_WARN_LOG("Listener is NULL.");
			return;
		}

		m_listeners[(int32)level].erase(std::find(m_listeners[(int32)level].begin(), m_listeners[(int32)level].end(), listener));
	}

	void MessageCenter::post(NEXT_AI_MESSAGE_ID id)
	{
		NEXTAI_TRACE_LOG("BASE", "parameter id[{}]", (int32)id);

		m_messages.push_back(id);
	}

	BOOL MessageCenter::peek(NEXT_AI_MESSAGE_ID& id, PeekMessageMode mode)
	{
		NEXTAI_TRACE_LOG("BASE", "parameter id[{}] mode[{}]", (int32)id, (int32)mode);

		if (m_messages.size() == 0)
		{
			return FALSE;
		}

		id = *(m_messages.begin());

		if (mode == PeekMessageMode::Remove)
		{
			m_messages.pop_front();
		}
		return TRUE;
	}

	void MessageCenter::clear()
	{
		BASE_TRACE_FUNC();
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

std::wostream& operator<<(std::wostream& os, NextAI::MessageCenter::ListenerLevel level)
{
	switch (level)
	{
	case NextAI::MessageCenter::ListenerLevel::Low:
		os << L"ListenerLevel::Low";
		break;
	case NextAI::MessageCenter::ListenerLevel::Medium:
		os << L"ListenerLevel::Medium";
		break;
	case NextAI::MessageCenter::ListenerLevel::High:
		os << L"ListenerLevel::High";
		break;
	case NextAI::MessageCenter::ListenerLevel::Max:
		os << L"ListenerLevel::Max";
		break;
	}
	return os;
}

std::wostream& operator<<(std::wostream& os, NextAI::MessageCenter::PeekMessageMode mode)
{
	switch (mode)
	{
	case NextAI::MessageCenter::PeekMessageMode::NoRemove:
		os << L"PeekMessageMode::NoRemove";
		break;
	case NextAI::MessageCenter::PeekMessageMode::Remove:
		os << L"PeekMessageMode::Remove";
		break;
	}
	return os;
}