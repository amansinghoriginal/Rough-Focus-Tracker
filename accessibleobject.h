#ifndef ACCESSIBLEOBJECT_H
#define ACCESSIBLEOBJECT_H

class AccessibleObject : public QObject
{
	Q_OBJECT
public:
	AccessibleObject(const QString& service, const QString& path);

private:
	QString service;
	QString path;
	QDBusConnection conn;

	QString name;
};
#endif
