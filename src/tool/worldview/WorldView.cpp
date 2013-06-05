#include "WorldView.h"
#include <iostream>
#include <string>

namespace tool {
namespace worldview {


//TODO: this is kind of barely hacked together
//I don't know if Lizzie's made progress on figuring out the pool size issues
//but that needs to be fixed before this can be a reliable part
//of the code base. more explanation below

WorldView::WorldView(QWidget* parent)
    : commThread("comm", COMM_FRAME_LENGTH_uS),
	  wviewComm(16,5), // WARNING for some reason using MY_TEAM_NUMBER doesn't work so this is hard-coded
	  portals::Module(),
	  QWidget(parent)

{
	commThread.addModule(*this);
	commThread.addModule(wviewComm);

	fieldPainter = new WorldViewPainter(this);
    mainLayout = new QHBoxLayout(this);

	field = new QHBoxLayout();
    field->addWidget(fieldPainter);

	rightLayout = new QVBoxLayout();

	options = new QVBoxLayout();
    options->setAlignment(Qt::AlignTop);
	startButton = new QPushButton(QString("Start World Viewer"));
	options->addWidget(startButton);

	comboboxlayout = new QHBoxLayout();
	combolabel = new QLabel(QString("Watched Robot: "));
	robotPicker = new QComboBox();
	robotPicker->setMaxCount(NUM_PLAYERS_PER_TEAM);
	for (int i = 0; i < NUM_PLAYERS_PER_TEAM; i++) {
		robotPicker->addItem(QString::number(i+1)); //there might be a way to find their names and put them here?
	}

	comboboxlayout->addWidget(combolabel);
	comboboxlayout->addWidget(robotPicker);
	options->addLayout(comboboxlayout);

	statesBox = new QGroupBox(QString("Robot Roles"));
	statesBox->setFlat(false);
	statesLayout = new QVBoxLayout();

	createStateDisplay();

	rightLayout->addLayout(options);
	rightLayout->addWidget(statesBox);

    mainLayout->addLayout(field);
	mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));

	for (int i = 0; i < NUM_PLAYERS_PER_TEAM; ++i)
        commIn[i].wireTo(wviewComm._worldModels[i], true);
}


void WorldView::run_()
{
    //this only works when the pool size is increased by ~4x (24 works)
	//like so: SET_POOL_SIZE(messages::WorldModel, 24);
	//and even then it only really prevents the code from crashing - it doesn't
	//allow you to view more than one robot
    /*for (int i = 0; i < NUM_PLAYERS_PER_TEAM; ++i)
	  {
	  commIn[i].latch();
	  fieldPainter->updateWithLocationMessage(commIn[i].message());
	  updateStateDisplay(i, commIn[i].message();
	  }*/


	// So the hack around that is to select one robot with a drop-down
	// and display only that robot
	// which technically works but is kind of shitty
	currentlyWatchedBot=robotPicker->currentIndex();

	//if the bot changes while the viewer is running, we have to close out the old
	//connection - multiple connections at once will crash the tool because of the
	//pool size issue described above
	if(currentlyWatchedBot!=lastWatchedBot){
		commIn[lastWatchedBot]
	}

	commIn[currentlyWatchedBot].latch();
	fieldPainter->updateWithLocationMessage(commIn[currentlyWatchedBot].message());
	updateStateDisplay(currentlyWatchedBot, commIn[currentlyWatchedBot].message());

	lastWatchedBot = currentlyWatchedBot;
}

void WorldView::startButtonClicked(){
	commThread.start();
	startButton->setText(QString("Stop World Viewer"));
	disconnect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
	connect(startButton, SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
}

void WorldView::stopButtonClicked(){
	commThread.stop();
	startButton->setText(QString("Start World Viewer"));
	disconnect(startButton, SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
	connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
}

void WorldView::createStateDisplay(){
	for(int i = 0; i < NUM_PLAYERS_PER_TEAM; i++) {
		roboLabel[i] = new QLabel(QString("Player ")+
								QString::number(i+1)+
								QString("\nRole: ")+
								QString("\t\tinactive")+
								QString("\nSubrole: ")+
								QString("\t\tinactive"));
	    statesLayout->addWidget(roboLabel[i]);
	}
	statesBox->setLayout(statesLayout);
}

void WorldView::updateStateDisplay(int playerNum, messages::WorldModel wm){
	QString *tempText = new QString(QString("Player ")+
								   QString::number(playerNum+1)+
								   QString("\nRole: ")+
								   QString("\t\t")+
								   lookupRole(wm.role())+
								   QString("\nSubrole: ")+
								   QString("\t\t")+
								   lookupSubRole(wm.sub_role()));
	if(tempText == roboLabel[playerNum]->text())
		return;
	else{
		roboLabel[playerNum]->setText(*tempText);
	    roboLabel[playerNum]->update();
	}
}

//Totally violates DRY, but it wasn't worth it to try and wrap python into the
//tool in order to use the lookup table in behaviors. Deal with it.
QString WorldView::lookupRole(int role){
	switch(role){
	case 0:
		return QString("Init");
	case 1:
		return QString("Penalty");
	case 2:
		return QString("Chaser");
	case 3:
		return QString("Middle");
	case 4:
		return QString("Offender");
	case 5:
		return QString("Defender");
	case 6:
		return QString("Goalie");
	case 7:
		return QString("Defender_dub_d");
	}
}

QString WorldView::lookupSubRole(int subrole){
	switch(subrole){
	case 0:
		return QString("Init");
	case 1:
		return QString("Penalty");
	case 2:
		return QString("Left Wing");
	case 3:
		return QString("Right Wing");
	case 4:
		return QString("Striker");
	case 5:
		return QString("Forward");
	case 6:
		return QString("Defensive Middle");
	case 7:
		return QString("Offensive Middle");
	case 8:
		return QString("Dub_d Middle");
	case 9:
		return QString("Stopper");
	case 10:
		return QString("Sweeper");
	case 11:
		return QString("Center Back");
	case 12:
		return QString("Left Deep Back");
	case 13:
		return QString("Right Deep Back");
	case 14:
		return QString("Chase Normal");
	case 15:
		return QString("Goalie Center");
	case 16:
		return QString("Goalie Save");
	case 17:
		return QString("Goalie Chaser");
	case 18:
		return QString("Goalie Kickoff");
	case 19:
		return QString("Kickoff Sweeper");
	case 20:
		return QString("Kickoff Striker");
	case 21:
		return QString("Ready Goalie");
	case 22:
		return QString("Ready Chaser");
	case 23:
		return QString("Ready Defender");
	case 24:
		return QString("Ready Middie");
	case 25:
		return QString("Ready Offender");
	}
}



}
}
