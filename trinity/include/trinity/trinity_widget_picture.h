#ifndef _TRINITY_WIDGET_PICTURE_H_
#define _TRINITY_WIDGET_PICTURE_H_

#include "trinity_widget_object.h"

namespace NextAI
{
	/*
	 * ͼƬ�ؼ���֧��BMP��JPG�ȶ���ͼƬ��ʽ��
	 * �ڲ�ʹ��FreeImage֧��ͼƬ�ļ���
	 */
	class WidgetPicture : public WidgetObject
	{
	public:
	
		/* ����һ��ͼƬ�γɶ��WidgetPicture */
		static bool allocPictures(const std::wstring& path, int32 size, std::vector<std::shared_ptr<WidgetPicture>>& pictures);
		
		/* ���캯�� */
		WidgetPicture(ObjectId id);
		virtual ~WidgetPicture();
		
		/* �軭 */
		virtual void drawImpl();
		
		/* ͼƬ·��
		 * ��ҪƵ�����ñ����������漰�������������ͷ� */
		virtual void setPath(const std::wstring& path);
		virtual std::wstring getPath();
		
		/* ��ǰ�Ƿ��ǿ��õ� */
		virtual bool isValid() { return m_picture != INVALID_TEXTURE_ID; }
		
	private:
	
		/* ���ù��캯�� */
		DISABLE_CLASS_COPY(WidgetPicture);
		
		/* �ͷ����� */
		void release();
		
	private:
	
		/* ͼƬ��Դ���� */
		PICTURE_TEXTURE_ID m_picture;
		
		/* �ļ�·�� */
		std::wstring m_path;
		
	};
}

#endif // !_TRINITY_WIDGET_PICTURE_H_