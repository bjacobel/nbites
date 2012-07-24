#include <vector>
#include "SocketReader.h"
#include "CommDef.h"
#include <QtNetwork/QUdpSocket>
#include <QByteArray>
#include <QtNetwork/QHostAddress>
#include <QtDebug>

namespace qtool {
namespace network {

SocketReader::SocketReader(QObject* parent) : QObject(parent) {
}

void SocketReader::startListening(){
    udpSocket.bind(QHostAddress("0.0.0.0"), UDP_PORT);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void SocketReader::stopListening(){
    udpSocket.close();
}

void SocketReader::readSocket(){
    while(udpSocket.hasPendingDatagrams()){
        qint64 datagram_size = udpSocket.pendingDatagramSize();
        QHostAddress datagram_source;
        quint16 datagram_port;
        char* data = new char[datagram_size];

        udpSocket.readDatagram(data, datagram_size, &datagram_source, &datagram_port);

        if(datagram_size==112){ //this needs to be here to ignore
            //the 60-byte discovery messages
            CommPacketHeader* head = (CommPacketHeader*)data;
            data+=sizeof(CommPacketHeader); //cut off the header bytes
            float* floatdata = (float*) data;
            Bot newBot;

            newBot.address = datagram_source;
            newBot.xPos = floatdata[0];
            newBot.yPos = floatdata[1];
            newBot.heading = floatdata[2];
            newBot.xUncert = floatdata[3];
            newBot.yUncert = floatdata[4];
            newBot.headingUncert = floatdata[5];
            newBot.xBall = floatdata[6];
            newBot.yBall = floatdata[7];
            newBot.xBallUncert = floatdata[8];
            newBot.yBallUncert = floatdata[9];
			newBot.teamNum = head->team;
			newBot.teamColor = head->color;
			newBot.playerNum = head->player;

            robotExistsAlready = 0;
			for(int i = 0; i < connectedBots.size(); i++){
                //if this robot is already in the array, delete the instance of it that's older
				if(connectedBots[i].address == newBot.address){
                    connectedBots.erase(connectedBots.begin() + i);
					emit replacedRobot();
					robotExistsAlready = 1;
                }
            }
			//if the robot wasn't a duplicate, add it but emit a different signal
			if(!robotExistsAlready)
				emit addedNewRobot();
            connectedBots.push_back(newBot);
        }
    }
}

int SocketReader::getX(int i){
    return connectedBots[i].xPos;
}
int SocketReader::getY(int i){
    return connectedBots[i].yPos;
}
int SocketReader::getHeading(int i){
    return connectedBots[i].heading;
}
int SocketReader::getXUncert(int i){
    return connectedBots[i].xUncert;
}
int SocketReader::getYUncert(int i){
    return connectedBots[i].yUncert;
}
int SocketReader::getheadUncert(int i){
    return connectedBots[i].headingUncert;
}
int SocketReader::getBallX(int i){
    return connectedBots[i].xBall;
}
int SocketReader::getBallY(int i){
    return connectedBots[i].yBall;
}
int SocketReader::getBallXUncert(int i){
    return connectedBots[i].xBallUncert;
}
int SocketReader::getBallYUncert(int i){
    return connectedBots[i].yBallUncert;
}
int SocketReader::getTeamNum(int i){
	return connectedBots[i].teamNum;
}
int SocketReader::getTeamColor(int i){//0=blue, 1=red
	return connectedBots[i].teamColor;
}
int SocketReader::getPlayerNum(int i){
	return connectedBots[i].playerNum;
}
QString SocketReader::getName(int i){
	return connectedBots[i].name;
}
QHostAddress SocketReader::getHostAddress(int i){
	return connectedBots[i].address;
}
int SocketReader::getSize(){
	return connectedBots.size();
}
SocketReader::Bot SocketReader::findRobot(QString s){
}
}
}
