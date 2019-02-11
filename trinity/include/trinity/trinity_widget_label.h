#ifndef _TRINITY_WIDGET_LABEL_H_
#define _TRINITY_WIDGET_LABEL_H_

#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	/*
	 * 文本控件
	 */
	class WidgetLabel : public WidgetObject
	{
	public:
	
		/* 对齐状态 */
		enum class Alignment
		{
			LeftTop = 0,		/* 左上对齐 */
			LeftCenter,			/* 左中对齐 */
			LeftBottom,			/* 左下对齐 */
			CenterTop,			/* 中上对齐 */
			CenterCenter,		/* 中中对齐 */
			CenterBottom,		/* 中下对齐 */
			RightTop,			/* 右上对齐 */
			RightCenter,		/* 右中对齐 */
			RightBottom,		/* 右下对齐 */
			Max
		};
		
		/* 文字超出范围时的处理方案 */
		enum class Overflow
		{
			Clip = 0,			/* 裁剪 */
			Ellipsis,			/* 省略符号 */
			AutoMarquee,		/* 自动滚动 */
			Max
		};
		
	public:
	
		/* 构造函数和析构函数 */
		WidgetLabel(ObjectId id);
		virtual ~WidgetLabel();
		
		/* 设定文本 */
		virtual void setText(std::string text);
		virtual void setText(std::wstring text);
		virtual std::string getText();
		virtual std::wstring getTextW();
		
		/* 设定颜色 */
		virtual void setColor(PixelColor color);
		virtual PixelColor getColor();
		
		/* 设定字体 */
		virtual void setFont(std::shared_ptr<Font> font);
		virtual std::shared_ptr<Font> getFont();
		
		/* 对齐状态 */
		virtual void setAlignment(Alignment align);
		virtual Alignment getAlignment();
		
		/* 文字超出范围时的处理方案 */
		virtual void setOverflow(Overflow overflow);
		virtual Overflow getOverflow();
		
		/* 描画文本 */
		virtual void drawImpl();
		
	private:
		/* 禁用拷贝构造 */
		DISABLE_CLASS_COPY(WidgetLabel);
		
		std::wstring m_text;				/* 文字 */
		std::shared_ptr<Font> m_font;		/* 字体 */
		PixelColor m_color;					/* 颜色，默认PIXEL_COLOR_BLACK */
		Alignment m_alignment;				/* 对齐，默认Alignment::LeftCenter */
		Overflow m_overflow;				/* 文字过长，默认Overflow::Clip */
	};
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::WidgetLabel::Alignment);
OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::WidgetLabel::Overflow);

#endif // !_TRINITY_WIDGET_LABEL_H_