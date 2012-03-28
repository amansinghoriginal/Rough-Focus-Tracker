#include "dbusconnection.h"
#include <QtCore/QDebug>
#include <QtDBus/QDBusMessage>

DBusConnection::DBusConnection()
	: dbusConnection(connect())
{}

QDBusConnection DBusConnection::connection() const
{
	return dbusConnection;
}

QString DBusConnection::getAccessibilityBusAddress() const
{
	if(!QDBusConnection::sessionBus().isConnected()){
		qCritical() << "dbusconnection :: Not connected to session bus\n";
		return "";
	}

	QDBusMessage m = QDBusMessage::createMethodCall("org.a11y.Bus",
		"/org/a11y/bus",
		"org.a11y.Bus",
		"GetAddress");
	
	QDBusMessage reply = QDBusConnection::sessionBus().call(m);

	if(reply.type() == QDBusMessage::ErrorMessage){
		qCritical() << "dbusconnection :: Error in calling GetAddress\n";
		return "";
	}
	
	qDebug() << "Bus : " << reply.arguments().at(0).toString();
	return reply.arguments().at(0).toString();
}

QDBusConnection DBusConnection::connect() const
{
	QString busAddress = getAccessibilityBusAddress();
	if(busAddress.isEmpty()){
		qCritical() << "dbusconnection :: Failed to get accessibility bus address\n";
		qCritical() << "dbusconnection :: Falling back to session bus\n";
		return QDBusConnection::sessionBus();
	}

	return QDBusConnection::sessionBus().connectToBus(busAddress,"a11y");
		qDebug() <<"dbusconnection :: connected successfully to a11y";
}
