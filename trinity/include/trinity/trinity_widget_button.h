#ifndef _TRINITY_WIDGET_BUTTON_H_
#define _TRINITY_WIDGET_BUTTON_H_

#include "base/nextai_object.h"
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
			Normal = 0,		/* 通常态 */
			Pressed,		/* 压下态 */
			Selected,		/* 选中态 */
			Disabled,		/* 无效态 */
			Max
		};

	public:
		/* 构造函数 */
		WidgetButton(ObjectId id);
		virtual ~WidgetButton();

		/* 描画 */
		virtual void drawImpl();

		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

		/* 设定图片路径
		 * 不要频繁调用本函数，会涉及到纹理的申请和释放 */
		virtual void setPath(Status status, const WCHAR* path);
		virtual const WCHAR* getPath(Status status);

		/* 设定按钮的状态 */
		virtual void setStatus(Status status);
		virtual Status getStatus();

	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetButton);

	protected:
		/* 状态 */
		Status m_status;

		/* 图片资源纹理 */
		WidgetPicture* m_pictures[(int32)Status::Max];
	};

	/* 
	 * 普通压下按钮 
	 */
	class WidgetPushButton : public WidgetButton
	{
	public:
		WidgetPushButton(ObjectId id);
		virtual ~WidgetPushButton();

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
		WidgetRadioButton(ObjectId id);
		virtual ~WidgetRadioButton();

		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

		/* 设定选中状态 */
		virtual void setChecked();

		/* 加入组 */
		virtual void setGroup(SMART_PTR<WidgetGroup>& group);

	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetRadioButton);

		/* 组 */
		SMART_PTR<WidgetGroup> m_group;

		/* 选中状态 */
		BOOL m_check;
	};

	/* 
	 * 多选按钮 
	 */
	class WidgetCheckButton : public WidgetButton
	{
	public:
		WidgetCheckButton(ObjectId id);
		virtual ~WidgetCheckButton();

		/* 点击处理 */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

	private:
		/* 禁用构造函数 */
		DISABLE_CLASS_COPY(WidgetCheckButton);

		/* 选中状态 */
		BOOL m_check;
	};
}

#endif // !_TRINITY_WIDGET_BUTTON_H_