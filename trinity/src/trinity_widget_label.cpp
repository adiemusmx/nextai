#include "stdafx.h"
#include "base/nextai_string.h"
#include "trinity/trinity_widget_label.h"

namespace NextAI
{
	WidgetLabel::WidgetLabel(ObjectId id) : WidgetObject(id)
	{
		m_text = L"";
		m_color = PIXEL_COLOR_BLACK;
		m_alignment = Alignment::LeftCenter;
		m_overflow = Overflow::Clip;
	}
	
	WidgetLabel::~WidgetLabel()
	{
	}
	
	void WidgetLabel::setText(std::string text)
	{
		NEXTAI_TRACE_LOG(L"id[{}] text[{}]", getId(), m_text);
		m_text = StringUtil::s2ws(text);
	}
	
	void WidgetLabel::setText(std::wstring text)
	{
		NEXTAI_TRACE_LOG(L"id[{}] text[{}]", getId(), m_text);
		m_text = text;
	}
	
	std::string WidgetLabel::getText()
	{
		return StringUtil::ws2s(m_text);
	}
	
	std::wstring WidgetLabel::getTextW()
	{
		return m_text;
	}
	
	void WidgetLabel::setColor(PixelColor color)
	{
		NEXTAI_TRACE_LOG(L"id[{}] color[#{:x}]", getId(), color);
		m_color = color;
	}
	
	PixelColor WidgetLabel::getColor()
	{
		return m_color;
	}
	
	void WidgetLabel::setFont(std::shared_ptr<Font> font)
	{
		NEXTAI_TRACE_LOG(L"id[{}] name[{}]", getId(), font->getName());
		m_font = font;
	}
	
	std::shared_ptr<Font> WidgetLabel::getFont()
	{
		return m_font;
	}
	
	void WidgetLabel::setAlignment(WidgetLabel::Alignment align)
	{
		NEXTAI_TRACE_LOG(L"id[{}] align[{}]", getId(), align);
		m_alignment = align;
	}
	
	WidgetLabel::Alignment WidgetLabel::getAlignment()
	{
		return m_alignment;
	}
	
	void WidgetLabel::setOverflow(WidgetLabel::Overflow overflow)
	{
		NEXTAI_TRACE_LOG(L"id[{}] overflow[{}]", getId(), overflow);
		m_overflow = overflow;
	}
	
	WidgetLabel::Overflow WidgetLabel::getOverflow()
	{
		return m_overflow;
	}
	
	void WidgetLabel::drawImpl()
	{
		Rect area = getDrawableArea();
		ScreenPoint start = { area.left, area.top };
		
		/* 根据对齐设定，决定起始描画位置 */
		if (m_alignment == WidgetLabel::Alignment::LeftTop ||
				m_alignment == WidgetLabel::Alignment::LeftCenter ||
				m_alignment == WidgetLabel::Alignment::LeftBottom)
		{
			start.x = area.left;
		}
		else if (m_alignment == WidgetLabel::Alignment::CenterTop ||
				 m_alignment == WidgetLabel::Alignment::CenterCenter ||
				 m_alignment == WidgetLabel::Alignment::CenterBottom)
		{
			/* TODO */
		}
		else
		{
			/* TODO */
		}
		
		if (m_alignment == WidgetLabel::Alignment::LeftTop ||
				m_alignment == WidgetLabel::Alignment::CenterTop ||
				m_alignment == WidgetLabel::Alignment::RightTop)
		{
			start.y = area.top;
		}
		else if (m_alignment == WidgetLabel::Alignment::LeftCenter ||
				 m_alignment == WidgetLabel::Alignment::CenterCenter ||
				 m_alignment == WidgetLabel::Alignment::RightCenter)
		{
			/* TODO */
		}
		else
		{
			/* TODO */
		}
		
		/* 进行描画 */
		if (m_font)
		{
			m_font->drawText(start, m_color, m_text);
		}
	}
}

std::wostream& operator<<(std::wostream& os, NextAI::WidgetLabel::Alignment obj)
{
	switch (obj)
	{
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::LeftTop);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::LeftCenter);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::LeftBottom);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::CenterTop);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::CenterCenter);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::CenterBottom);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::RightTop);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::RightCenter);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Alignment::RightBottom);
	}
	
	return os << L"WidgetLabel::Alignment::Unknown";
}

std::wostream& operator<<(std::wostream& os, NextAI::WidgetLabel::Overflow obj)
{
	switch (obj)
	{
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Overflow::Clip);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Overflow::Ellipsis);
		OUT_STREAM_ENUM_CLASS_CASE(WidgetLabel::Overflow::AutoMarquee);
	}
	
	return os << L"WidgetLabel::Overflow::Unknown";
}
