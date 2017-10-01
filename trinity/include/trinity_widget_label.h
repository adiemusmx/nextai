#ifndef _TRINITY_WIDGET_LABEL_H_
#define _TRINITY_WIDGET_LABEL_H_

namespace Trinity
{

class WidgetLabel : public WidgetObject
{
public:
	WidgetLabel();
	~WidgetLabel();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetLabel);
}

}
#endif // !_TRINITY_WIDGET_LABEL_H_