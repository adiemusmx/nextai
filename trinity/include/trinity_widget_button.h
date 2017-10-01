#ifndef _TRINITY_WIDGET_BUTTON_H_
#define _TRINITY_WIDGET_BUTTON_H_

namespace Trinity
{

class WidgetButton : public WidgetObject
{
public:
	WidgetButton();
	~WidgetButton();

private:
	// Disable copy constructor
	DISABLE_CLASS_COPY(WidgetButton);
}

}

#endif // !_TRINITY_WIDGET_BUTTON_H_