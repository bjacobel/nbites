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
	socket = new SocketReader();
	//socket->startListening();

	frameWidth = parent->size().width();
	bold40.setPointSize(40);
	bold40.setBold(true);

	connect(socket, SIGNAL(replacedRobot()), this, SLOT(updateRobot()));
	connect(socket, SIGNAL(addedNewRobot()), this, SLOT(addRobot()));

	testBots();
	display();
}

void NetMon::updateRobot(){
	display();
}

void NetMon::addRobot(){
	display();
}

void NetMon::display(){
	for(int i = 0; i < socket->getSize(); i++){
		setupRobotView(i, i);
	}
}

//display everything about a robot in one of
//five slots in the view
void NetMon::setupRobotView(int viewPos, int arrayPos){
	if(viewPos < 0 || viewPos > 4)
		return;
	else {
		QLabel* label = new QLabel(socket->getName(arrayPos));
		label->setFont(bold40);
		mainLayout->addWidget(label);
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
	testBot2.teamColor = 0;
	testBot2.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot2);

	SocketReader::Bot testBot3 = SocketReader::Bot();
	testBot3.name = QString("jayne");
	testBot3.teamNum = 69;
	testBot3.playerNum = 0;
	testBot3.teamColor = 0;
	testBot3.address = QHostAddress("139.140.218.10");
	socket->connectedBots.push_back(testBot3);

	SocketReader::Bot testBot4 = SocketReader::Bot();
	testBot4.name = QString("wash");
	testBot4.teamNum = 69;
	testBot4.playerNum = 0;
	testBot4.teamColor = 0;
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
