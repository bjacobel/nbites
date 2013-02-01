#include "NewMan.h"
#include <iostream>

namespace man {

Man::Man(boost::shared_ptr<AL::ALBroker> broker, const std::string &name)
    : AL::ALModule(broker, name),
      cognitionThread()
{
    setModuleDescription("The Northern Bites' soccer player.");
    std::cout << "Man constructor." << std::endl;
    cognitionThread.start();
}

Man::~Man()
{
    std::cout << "Man destructor." << std::endl;
}

}
