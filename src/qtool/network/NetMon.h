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
#include <QtGui>

#include "data/DataManager.h"

namespace qtool {
namespace network {

class NetMon : public QMainWindow {
	Q_OBJECT

public:
	NetMon(data::DataManager::ptr dataManager);
	~NetMon();

private:
	data::DataManager::ptr dataManager;
};

}
}
