#ifndef _TRINITY_WIDGET_SURFACE_H_
#define _TRINITY_WIDGET_SURFACE_H_

#include "base/nextai_basic_types.h"
#include "trinity/trinity_widget_object.h"

namespace NextAI
{
	enum class SurfaceId
	{
		Base,			// Background
		View,			// usser view
		Ons,			// ons view
		Interrupt,		// interrup view
		Max
	};
	
	class WidgetSurface : public WidgetObject
	{
	public:
		WidgetSurface(ObjectId id);
		virtual ~WidgetSurface();
		
	private:
		// Disable copy constructor
		DISABLE_CLASS_COPY(WidgetSurface);
	};
	
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::SurfaceId);

#endif // !_TRINITY_WIDGET_SURFACE_H_