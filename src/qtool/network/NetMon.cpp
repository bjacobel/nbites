#include "NetMon.h"
#include "man/memory/Memory.h"

#include <QDebug>

namespace qtool {
namespace network {

using namespace man::memory;

NetMon::NetMon(DataManager::ptr dataManager):
	dataManager(dataManager) {

}

NetMon::~NetMon(){
}

}
}
