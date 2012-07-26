/**
 * @class NetMon
 *
 * Provides graphical network diagnostics 
 *
 * @author Brian Jacobel
 * @date July 2012
 */

#pragma once

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QtGui>
#include <QtNetwork/QUdpSocket>
#include <vector>

#include "data/DataManager.h"
#include "SocketReader.h"

namespace qtool {
namespace network {

class NetMon : public QWidget {
	Q_OBJECT

public:
	NetMon(data::DataManager::ptr dataManager, QWidget* parent = 0);
	~NetMon(){
		socket->stopListening();
	}

private:
	data::DataManager::ptr dataManager;
	network::SocketReader* socket;
	QHBoxLayout* mainLayout;
	QFont bold40;
	int frameWidth;

	void setupRobotView(int, int);
	void testBots();

private slots:
	void updateDisplay();

};

}
}
