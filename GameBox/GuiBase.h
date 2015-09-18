#ifndef __GUIBASE__
#define __GUIBASE__

#define gb_msg			virtual

enum GuiTypes: unsigned int
{
	GT_UNKNOWN = 0U,
	GT_GWND,
	GT_GVIEW
};

typedef unsigned int GuiObjId;

class GuiBase{
public:
	GuiBase(GuiTypes type, GuiObjId id);

	GuiTypes getGuiType() const;
	GuiObjId getId() const;
private:
	const GuiTypes m_eUiType;
	const GuiObjId m_iId;
};
#endif