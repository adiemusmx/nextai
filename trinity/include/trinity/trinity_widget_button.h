#ifndef _TRINITY_WIDGET_BUTTON_H_
#define _TRINITY_WIDGET_BUTTON_H_

#include "trinity/trinity_widget_object.h"
#include "trinity/trinity_widget_picture.h"

namespace NextAI
{
	class WidgetGroup;
	
	/*
	 * 按钮控件，支持Normal, Pressed, Selected, Disabled状态
	 * 内部使用WidgetPicture支持图片的加载
	 */
	class WidgetButton : public WidgetObject
	{
	public:
	
		/* 按钮的四状态 */
		enum class Status
		{
			Normal = 0,             /* 通常态 */
			Pressed,                /* 压下态 */
			Selected,               /* 选中态 */
			Disabled,               /* 无效态 */
			Max
		};
		
	public:
	
		/* 构造函数 */
		WidgetButton(ObjectId id);
		virtual ~WidgetButton();
		
		/* 描画 */
		virtual void drawImpl();
		
		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]) = 0;
		
		/*
		 * 设定图片路径
		 * 不要频繁调用本函数，会涉及到纹理的申请和释放
		 */
		virtual void setPath(const std::wstring& path);
		virtual void setPath(Status status, const std::wstring& path);
		virtual std::wstring getPath(Status status);
		
		/* 设定控件的描画区域 */
		virtual void setDrawableArea(const Rect& area);
		virtual void setHitableArea(const Rect& area);
		
		/* 按钮状态 */
		virtual Status getStatus();
		
	private:
	
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetButton);
		
	protected:
	
		/* 是否被压下 */
		bool m_isPressed;
		
		/* 图片资源纹理 */
		std::vector<std::shared_ptr<WidgetPicture>> m_pictures;
		
	};
	
	/*
	 * 普通压下按钮
	 */
	class WidgetPushButton : public WidgetButton
	{
	public:
	
		/* 构造函数 */
		WidgetPushButton(ObjectId id);
		virtual ~WidgetPushButton();
		
		/* 点击处理 */
		HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		
	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetPushButton);
		
	};
	
	/*
	 * 单选按钮
	 */
	class WidgetRadioButton : public WidgetButton
	{
	public:
	
		/* 构造函数 */
		WidgetRadioButton(ObjectId id);
		virtual ~WidgetRadioButton();
		
		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		
		/* 按钮状态 */
		virtual Status getStatus();
		
		/* 设定选中状态 */
		virtual void setChecked(bool checked);
		virtual bool isChecked() { return m_isChecked; }
		
	private:
	
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetRadioButton);
		
		/* 组 */
		std::shared_ptr<WidgetGroup> m_group;
		
		/* 选中状态 */
		bool m_isChecked;
		
	};
	
	/*
	 * 多选按钮
	 */
	class WidgetCheckButton : public WidgetButton
	{
	public:
	
		/* 构造函数 */
		WidgetCheckButton(ObjectId id);
		virtual ~WidgetCheckButton();
		
		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
		
		/* 按钮状态 */
		virtual Status getStatus();
		
		/* 设定选中状态 */
		virtual void setChecked(bool checked);
		virtual bool isChecked() { return m_isChecked; }
		
	private:
	
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetCheckButton);
		
		/* 选中状态 */
		bool m_isChecked;
		
	};
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::WidgetButton::Status);

#endif // !_TRINITY_WIDGET_BUTTON_H_