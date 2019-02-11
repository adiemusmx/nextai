#include "stdafx.h"
#include "trinity/trinity_widget_surface.h"
#include "base/nextai_app.h"

namespace NextAI
{

	WidgetSurface::WidgetSurface(ObjectId id): WidgetObject(id)
	{
		Rect full = { 0, 0, (int32)APP_SERVICE()->getWindowsWidth(), (int32)APP_SERVICE()->getWindowsHeight() };
		setArea(full);
	}
	
	WidgetSurface::~WidgetSurface()
	{
	}
}

std::wostream& operator<<(std::wostream& os, NextAI::SurfaceId mode)
{
	switch (mode)
	{
		OUT_STREAM_ENUM_CLASS_CASE(SurfaceId::Base);
		OUT_STREAM_ENUM_CLASS_CASE(SurfaceId::View);
		OUT_STREAM_ENUM_CLASS_CASE(SurfaceId::Ons);
		OUT_STREAM_ENUM_CLASS_CASE(SurfaceId::Interrupt);
	}
	
	return os << L"SurfaceId::Unknown";
}