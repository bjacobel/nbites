#include "NetMon.h"
#include "man/memory/Memory.h"

#include <QDebug>

namespace qtool {
namespace network {

using namespace data;
using namespace man::memory;

NetMon::NetMon(DataManager::ptr dataManager, QWidget* parent) :
	QWidget(parent), dataManager(dataManager) {

	mainLayout = new QHBoxLayout(this);
	mainLayout->setSpacing(10);
	socket = new SocketReader();
	//socket->startListening();

	frameWidth = parent->size().width();
	bold40.setPointSize(40);
	//bold40.setBold(true);
	bold40.setWeight(100);

	connect(socket, SIGNAL(socketUpdate()), this, SLOT(updateDisplay()));
	connect(socket, SIGNAL(socketUpdate()), this, SLOT(updateDisplay()));

	testBots();
	updateDisplay();
}

void NetMon::updateDisplay(){
	for(int i = 0; i < socket->getSize(); i++){

		QVBoxLayout* robotLayout = new QVBoxLayout;
		robotLayout->setContentsMargins(10, 10, 10, 10);

		QGroupBox* robotBox = new QGroupBox;
		robotBox->setObjectName("robotBox");

		if(socket->getTeamColor(i)==0) //blue team
			robotBox->setStyleSheet(
				"QGroupBox#robotBox { border: 5px solid rgb(54,166,237) ; border-radius: 5px }");
		else if(socket->getTeamColor(i)==1)  //red team
			robotBox->setStyleSheet(
				"QGroupBox#robotBox { border: 5px solid rgb(255,140,135) ; border-radius: 5px}");
		else //if the robot isn't on a team
			robotBox->setStyleSheet(
				"QGroupBox#robotBox { border: 2px solid gray ; border-radius: 5px }");

		QLabel* robName = new QLabel(socket->getName(i));
		QLabel* robotIP = new QLabel(QString("IP:  ") +
									 (socket->getHostAddress(i)).toString());
		QLabel* teamNum = new QLabel(QString("Team #:  ") +
									 QString::number(socket->getTeamNum(i)));
		QLabel* playNum = new QLabel(QString("Player #:  ") +
									 QString::number(socket->getPlayerNum(i)));

		robName->setFont(bold40);
		robotLayout->addWidget(robName, Qt::AlignHCenter);
		robotLayout->addWidget(robotIP, Qt::AlignJustify);
		robotLayout->addWidget(teamNum, Qt::AlignJustify);
		robotLayout->addWidget(playNum, Qt::AlignJustify);

		QSpacerItem* spacer = new QSpacerItem(0,500,QSizePolicy::Minimum,QSizePolicy::Maximum);
		robotLayout->addItem(spacer);

		robotBox->setLayout(robotLayout);
		mainLayout->addWidget(robotBox);
	}
}

void NetMon::testBots(){
	SocketReader::Bot testBot1 = SocketReader::Bot();
	testBot1.name = QString("zoe");
	testBot1.teamNum = 69;
	testBot1.playerNum = 0;
	testBot1.teamColor = 0;
	testBot1.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot1);

	SocketReader::Bot testBot2 = SocketReader::Bot();
	testBot2.name = QString("mal");
	testBot2.teamNum = 69;
	testBot2.playerNum = 0;
	testBot2.teamColor = 1;
	testBot2.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot2);

	SocketReader::Bot testBot3 = SocketReader::Bot();
	testBot3.name = QString("jayne");
	testBot3.teamNum = 69;
	testBot3.playerNum = 0;
	testBot3.teamColor = 2;
	testBot3.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot3);

	SocketReader::Bot testBot4 = SocketReader::Bot();
	testBot4.name = QString("wash");
	testBot4.teamNum = 69;
	testBot4.playerNum = 0;
	testBot4.teamColor = 3;
	testBot4.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot4);

	SocketReader::Bot testBot5 = SocketReader::Bot();
	testBot5.name = QString("river");
	testBot5.teamNum = 69;
	testBot5.playerNum = 0;
	testBot5.teamColor = 0;
	testBot5.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot5);

}

}
}
