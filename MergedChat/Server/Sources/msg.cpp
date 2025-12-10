#include "msg.h"

QString Message::formated()
{
	QString sp {QString("     ")};
	QString br1 {QString("[ ")};
	QString br2 {QString(" ] ")};
	return br1 + time + br2 + userName + sp + text;
}
