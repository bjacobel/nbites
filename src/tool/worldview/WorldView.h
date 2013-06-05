#pragma once

#include <QtGui>

#include "WorldModel.pb.h"

#include "WorldViewPainter.h"

#include "comm/CommModule.h"
#include "RobotConfig.h"
#include "RoboGrams.h"
#include "DiagramThread.h"

namespace tool {
namespace worldview {

class WorldView : public QWidget, public portals::Module {

	Q_OBJECT;

public:
	WorldView(QWidget* parent = 0);

	portals::InPortal<messages::WorldModel> commIn[NUM_PLAYERS_PER_TEAM];

protected:
	virtual void run_();

protected:
	WorldViewPainter* fieldPainter;

	QHBoxLayout* mainLayout;
	QHBoxLayout* field;
	QVBoxLayout* rightLayout;
	QVBoxLayout* options;
	QGroupBox* statesBox;
	QVBoxLayout* statesLayout;
	QComboBox* robotPicker;
	QHBoxLayout* comboboxlayout;
	QLabel* combolabel;
	QPushButton* startButton;
	QLabel* roboLabel[NUM_PLAYERS_PER_TEAM];

	man::comm::CommModule wviewComm;
	man::DiagramThread commThread;

	void updateStateDisplay(int playerNum, messages::WorldModel wm);
	void createStateDisplay();

	QString lookupRole(int role);
	QString lookupSubRole(int subrole);

    int currentlyWatchedBot;
	int lastWatchedBot;

protected slots:
	void startButtonClicked();
	void stopButtonClicked();
};

}
}
