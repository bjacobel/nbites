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

            //kill the previous instance of this robot in the array
            for(int i = 0; i < botPositions.size(); i++){
                if(botPositions[i].address == newBot.address){
                    botPositions.erase(botPositions.begin() + i);
                }
            }
            botPositions.push_back(newBot);
        }
        emit newRobotLocation();
    }
}

int SocketReader::getX(int i){
    return botPositions[i].xPos;
}
int SocketReader::getY(int i){
    return botPositions[i].yPos;
}
int SocketReader::getHeading(int i){
    return botPositions[i].heading;
}
int SocketReader::getXUncert(int i){
    return botPositions[i].xUncert;
}
int SocketReader::getYUncert(int i){
    return botPositions[i].yUncert;
}
int SocketReader::getheadUncert(int i){
    return botPositions[i].headingUncert;
}
int SocketReader::getBallX(int i){
    return botPositions[i].xBall;
}
int SocketReader::getBallY(int i){
    return botPositions[i].yBall;
}
int SocketReader::getBallXUncert(int i){
    return botPositions[i].xBallUncert;
}
int SocketReader::getBallYUncert(int i){
    return botPositions[i].yBallUncert;
}
int SocketReader::getTeamNum(int i){
	return botPositions[i].teamNum;
}
int SocketReader::getTeamColor(int i){//0=blue, 1=red
	return botPositions[i].teamColor;
}
int SocketReader::getPlayerNum(int i){
	return botPositions[i].playerNum;
}
int SocketReader::getSize(){
	return botPositions.size();
}
SocketReader::Bot SocketReader::findRobot(QString s){
}
}
}
