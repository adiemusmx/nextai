#ifndef _TRINITY_WIDGET_PICTURE_H_
#define _TRINITY_WIDGET_PICTURE_H_

#include "trinity_widget_object.h"

namespace NextAI
{
	/* ͼƬ�ؼ���֧��BMP��JPG�ȶ���ͼƬ��ʽ��
	 * �ڲ�ʹ��FreeImage֧��ͼƬ�ļ���	*/
	class WidgetPicture : public WidgetObject
	{
	public:
		/* ���캯�� */
		WidgetPicture(ObjectId id);
		virtual ~WidgetPicture();

		/* �軭 */
		virtual void drawImpl();

		/* ͼƬ·��
		 * ��ҪƵ�����ñ����������漰�������������ͷ� */
		virtual void setPath(const WCHAR* path);
		virtual const WCHAR* getPath();

	private:
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetPicture);

		/* �ͷ����� */
		void release();

	private:
		/* ͼƬ��Դ���� */
		PICTURE_TEXTURE_ID m_picture;

		/* �ļ�·�� */
		WCHAR m_path[FILE_PATH_MAX_LENGTH];
	};
}

#endif // !_TRINITY_WIDGET_PICTURE_H_