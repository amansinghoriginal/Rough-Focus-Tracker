#include<QtDBus/QDBusConnection>
#include<QtDBus/QDBusMessage>
#include<QtDBus/QDBusVariant>
#include<QtDBus/QDBusMetaType>
#include "focus.h"

QDBusArgument& operator<< (QDBusArgument& argument, const SpiReference& address)
{
	argument.beginStructure();
	argument << address.service;
	argument << address.path;
	argument.endStructure();
	return argument;
}

const QDBusArgument& operator>> (const QDBusArgument& argument, SpiReference& address)
{
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
							const SpiReference& ref) const
{
	if(state=="focused" && detail1==1){
		qDebug() << "Focus signal detected\n";
		//qDebug() << "State: "<<state << detail1 << detail2 << arg.variant() << ref.service <<ref.path.path() << "\n";

		QDBusMessage m = QDBusMessage::createMethodCall(
						ref.service,
						ref.path.path(),
						"org.a11y.atspi.Accessible",
						"GetState");
		QDBusMessage reply = dbc.connection().call(m);

		if(reply.arguments().isEmpty()){
			qDebug() << "Empty reply : State not obtained\n";
			return;
		}

		QList<uint> objectState;

		const QDBusArgument returnValue = reply.arguments().at(0).value<QDBusArgument>();

		returnValue.beginArray();
		while(returnValue.atEnd()){
			int arg;
			returnValue >> arg;
			objectState << arg;
		}
		returnValue.endArray();

		Q_ASSERT(state.count()==2); //Make sure that there are only 



		

	}
}

const DBusConnection& Focus::connection() const
{
	return dbc;
}
