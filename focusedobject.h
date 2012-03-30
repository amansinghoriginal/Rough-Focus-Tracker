#ifndef FOCUSEDOBJECT_H
#define FOCUSEDOBJECT_H

#include <QObject>

class FocusedObject : public QObject
{
	Q_OBJECT

public:
	FocusedObject(const QString& service, const QString& path, const DBusConnection&);

private:
	quint64 objectState;

}
#endif //FocusedObject
