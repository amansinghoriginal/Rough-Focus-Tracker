#ifndef ACCESSIBLEOBJECT_H
#define ACCESSIBLEOBJECT_H

class AccessibleObject : public QObject
{
	Q_OBJECT
public:
	AccessibleObject(const QString& service, const QString& path);

private:
	QString objService;
	QString objPath;
	QDBusConnection objConn;

	QString objName;
};
#endif
