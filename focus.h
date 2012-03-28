#ifndef FOCUS_H
#define FOCUS_H

#include <QObject>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusObjectPath>
#include "dbusconnection.h"

/**
 * As is evident from output of dbus-monitor,
 * the state-changed signal will be emitted with a
 * structure type parameter.
 * This Struct is written to get the details packed
 * in the struct from the signal
 */
struct SpiReference
{
	QString service;
	QDBusObjectPath path;
	
	SpiReference()
		: path(QDBusObjectPath("/org/a11y/atspi/accessible/null"))
	{}

	SpiReference(const QDBusConnection& connection, const QDBusObjectPath& path)
		:service(connection.baseService()),path(path)
	{}
};

class Focus : public QObject
{
	Q_OBJECT

public:
	Focus();

private Q_SLOTS:
	void stateChanged(const QString& state,
						int detail1,
						int detail2,
						const QDBusVariant &arg);
private:
	DBusConnection dbc;
};

#endif //Focus