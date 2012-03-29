#include<QtDBus/QDBusConnection>
#include<QtDBus/QDBusMessage>
#include<QtDBus/QDBusVariant>
#include<QtDBus/QDBusMetaType>
#include "focus.h"

QDBusArgument& operator<< (QDBusArgument& argument, const SpiReference& address)
{
	qDebug() << "<< was called\n";
	argument.beginStructure();
	argument << address.service;
	argument << address.path;
	argument.endStructure();
	return argument;
}

const QDBusArgument& operator>> (const QDBusArgument& argument, SpiReference& address)
{
	qDebug() << ">> was called\n";
	argument.beginStructure();
	argument >> address.service;
	argument >> address.path;
	argument.endStructure();
	return argument;
}

Focus::Focus()
{
	qDBusRegisterMetaType<SpiReference>();
	if(!dbc.connection().registerService("org.aman.focustracker"))
		qWarning() << "Could not register service";
	
	QVariantList subscriptions;
	subscriptions << QString("object:state-changed") << QString("focus:");
	
		QDBusMessage m = QDBusMessage::createMethodCall("org.a11y.atspi.Registry", //service
														"/org/a11y/atspi/registry", //path
														"org.a11y.atspi.Registry", //interface
														"RegisterEvent"); //Method
		m.setArguments(subscriptions);

		QDBusMessage reply = dbc.connection().call(m);
		if(reply.type() == QDBusMessage::ErrorMessage)
			qWarning() << "focus :: Could not register subscriptions\n";
	
	if(!dbc.connection().connect(QString(),	//service
							"",	//path
							"org.a11y.atspi.Event.Object", //interface
							"StateChanged",
							this, //reciever
						SLOT(stateChanged(QString,int,int,QDBusVariant,SpiReference)))){
		qWarning() << "Could not connect the signal\n";
	}

}

void Focus::stateChanged(const QString& state,
							int detail1,
							int detail2,
							const QDBusVariant& arg,
							const SpiReference& ref)
{
	qDebug() << "Signal Recieved\n";
}
