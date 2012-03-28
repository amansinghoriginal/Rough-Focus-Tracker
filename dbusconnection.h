#ifndef DBUSCONNECTION_H
#define DBUSCONNECTION_H

#include <QtDBus/QDBusConnection>
/**
 * class DBusConnection
 * Connects to accessibility bus and maintains reference 
 * to the connection in private. The connection can be 
 * obtained via public function connection.
 */
class DBusConnection
{
public:
	DBusConnection();
	QDBusConnection connection() const;
private:
	QString getAccessibilityBusAddress() const;
	QDBusConnection connect() const;

	QDBusConnection dbusConnection;
};

#endif
