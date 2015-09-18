#include "GuiBase.h"

GuiBase::GuiBase(GuiTypes type, GuiObjId id)
	:m_eUiType(type), m_iId(id)
{

}

GuiTypes GuiBase::getGuiType() const
{
	return m_eUiType;
}

GuiObjId GuiBase::getId() const
{
	return m_iId;
}
