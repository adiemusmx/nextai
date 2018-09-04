#ifndef _TRINITY_WIDGET_BUTTON_H_
#define _TRINITY_WIDGET_BUTTON_H_

#include "base/nextai_object.h"
#include "trinity/trinity_widget_object.h"
#include "trinity/trinity_widget_picture.h"

namespace NextAI
{
	class WidgetGroup;

	/* 
	 * ��ť�ؼ���֧��Normal, Pressed, Selected, Disabled״̬
	 * �ڲ�ʹ��WidgetPicture֧��ͼƬ�ļ���	
	 */
	class WidgetButton : public WidgetObject
	{
	public:
		/* ��ť����״̬ */
		enum class Status
		{
			Normal = 0,		/* ͨ��̬ */
			Pressed,		/* ѹ��̬ */
			Selected,		/* ѡ��̬ */
			Disabled,		/* ��Ч̬ */
			Max
		};

	public:
		/* ���캯�� */
		WidgetButton(ObjectId id);
		virtual ~WidgetButton();

		/* �軭 */
		virtual void drawImpl();

		/* ������� */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

		/* �趨ͼƬ·��
		 * ��ҪƵ�����ñ����������漰�������������ͷ� */
		virtual void setPath(Status status, const WCHAR* path);
		virtual const WCHAR* getPath(Status status);

		/* �趨��ť��״̬ */
		virtual void setStatus(Status status);
		virtual Status getStatus();

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetButton);

	protected:
		/* ״̬ */
		Status m_status;

		/* ͼƬ��Դ���� */
		WidgetPicture* m_pictures[(int32)Status::Max];
	};

	/* 
	 * ��ͨѹ�°�ť 
	 */
	class WidgetPushButton : public WidgetButton
	{
	public:
		WidgetPushButton(ObjectId id);
		virtual ~WidgetPushButton();

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetPushButton);
	};

	/* 
	 * ��ѡ��ť
	 */
	class WidgetRadioButton : public WidgetButton
	{
	public:
		WidgetRadioButton(ObjectId id);
		virtual ~WidgetRadioButton();

		/* ������� */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

		/* �趨ѡ��״̬ */
		virtual void setChecked();

		/* ������ */
		virtual void setGroup(SMART_PTR<WidgetGroup>& group);

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetRadioButton);

		/* �� */
		SMART_PTR<WidgetGroup> m_group;

		/* ѡ��״̬ */
		BOOL m_check;
	};

	/* 
	 * ��ѡ��ť 
	 */
	class WidgetCheckButton : public WidgetButton
	{
	public:
		WidgetCheckButton(ObjectId id);
		virtual ~WidgetCheckButton();

		/* ������� */
		virtual HitResult hitImpl(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetCheckButton);

		/* ѡ��״̬ */
		BOOL m_check;
	};
}

#endif // !_TRINITY_WIDGET_BUTTON_H_