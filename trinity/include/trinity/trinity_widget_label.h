#ifndef _TRINITY_WIDGET_LABEL_H_
#define _TRINITY_WIDGET_LABEL_H_

#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	/*
	 * �ı��ؼ�
	 */
	class WidgetLabel : public WidgetObject
	{
	public:
	
		/* ����״̬ */
		enum class Alignment
		{
			LeftTop = 0,		/* ���϶��� */
			LeftCenter,			/* ���ж��� */
			LeftBottom,			/* ���¶��� */
			CenterTop,			/* ���϶��� */
			CenterCenter,		/* ���ж��� */
			CenterBottom,		/* ���¶��� */
			RightTop,			/* ���϶��� */
			RightCenter,		/* ���ж��� */
			RightBottom,		/* ���¶��� */
			Max
		};
		
		/* ���ֳ�����Χʱ�Ĵ����� */
		enum class Overflow
		{
			Clip = 0,			/* �ü� */
			Ellipsis,			/* ʡ�Է��� */
			AutoMarquee,		/* �Զ����� */
			Max
		};
		
	public:
	
		/* ���캯������������ */
		WidgetLabel(ObjectId id);
		virtual ~WidgetLabel();
		
		/* �趨�ı� */
		virtual void setText(std::string text);
		virtual void setText(std::wstring text);
		virtual std::string getText();
		virtual std::wstring getTextW();
		
		/* �趨��ɫ */
		virtual void setColor(PixelColor color);
		virtual PixelColor getColor();
		
		/* �趨���� */
		virtual void setFont(std::shared_ptr<Font> font);
		virtual std::shared_ptr<Font> getFont();
		
		/* ����״̬ */
		virtual void setAlignment(Alignment align);
		virtual Alignment getAlignment();
		
		/* ���ֳ�����Χʱ�Ĵ����� */
		virtual void setOverflow(Overflow overflow);
		virtual Overflow getOverflow();
		
		/* �軭�ı� */
		virtual void drawImpl();
		
	private:
		/* ���ÿ������� */
		DISABLE_CLASS_COPY(WidgetLabel);
		
		std::wstring m_text;				/* ���� */
		std::shared_ptr<Font> m_font;		/* ���� */
		PixelColor m_color;					/* ��ɫ��Ĭ��PIXEL_COLOR_BLACK */
		Alignment m_alignment;				/* ���룬Ĭ��Alignment::LeftCenter */
		Overflow m_overflow;				/* ���ֹ�����Ĭ��Overflow::Clip */
	};
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::WidgetLabel::Alignment);
OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::WidgetLabel::Overflow);

#endif // !_TRINITY_WIDGET_LABEL_H_