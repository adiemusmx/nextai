#ifndef _TRINITY_WIDGET_LIST_H_
#define _TRINITY_WIDGET_LIST_H_

namespace Trinity
{

class WidgetList : public WidgetObject
{
public:
	WidgetList();
	virtual ~WidgetList();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetList);
}

}

#endif // !_TRINITY_WIDGET_LIST_H_