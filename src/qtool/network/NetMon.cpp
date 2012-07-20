#include "NetMon.h"
#include "man/memory/Memory.h"

#include <QDebug>

namespace qtool {
namespace network {

using namespace data;
using namespace man::memory;

NetMon::NetMon(DataManager::ptr dataManager) :
	dataManager(dataManager) {

	QHBoxLayout* mainLayout = new QHBoxLayout;
	QWidget* mainWidget = new QWidget;
	QLabel* test = new QLabel(QString("OH HEY THURR"));

	mainLayout->addWidget(test);
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);
}



}
}
