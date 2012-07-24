/**
 *
 *@class Network
 *
 * This class reads a variety of robot information through
 * a socket and provides it to other classes
 *
 * @author Brian Jacobel
 * @date Jul 2012
 *
 */

#pragma once

#include <vector>
#include <QString>
#include <QtNetwork/QUdpSocket>
#include "data/DataManager.h"

namespace qtool {
namespace network {

class SocketReader: public QObject {
	Q_OBJECT

public:
    SocketReader(QObject* parent = 0);
    ~SocketReader(){}

	int getX(int);
    int getY(int);
    int getHeading(int);
    int getXUncert(int);
    int getYUncert(int);
    int getheadUncert(int);
    int getBallX(int);
    int getBallY(int);
    int getBallXUncert(int);
    int getBallYUncert(int);
    int getTeamNum(int);
	int getTeamColor(int);
	int getPlayerNum(int);
	QString getName(int);
	QHostAddress getHostAddress(int);
    int getSize();

	struct Bot {
        QHostAddress address;
        float xPos;
        float yPos;
        float heading;
        float xUncert;
        float yUncert;
        float headingUncert;
        float xBall;
        float yBall;
        float xBallUncert;
        float yBallUncert;
		int teamNum;
        int teamColor; //0=blue,  1=red
		int playerNum;
		QString name;
    };
	std::vector<Bot> connectedBots;

    void startListening();
    void stopListening();

	Bot findRobot(QString);

public slots:
    void readSocket();

signals:
    void addedNewRobot();
	void replacedRobot();

private:
    QUdpSocket udpSocket;
	bool robotExistsAlready;
};
}
}
