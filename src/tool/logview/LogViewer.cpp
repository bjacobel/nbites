#include "LogViewer.h"

namespace tool {
namespace logview {

LogViewer::LogViewer(QWidget* parent) : QMainWindow(parent),
                                        imageTabs(this)
{
	QHBoxLayout* mainLayout = new QHBoxLayout;
	QWidget* mainWidget = new QWidget;

	mainLayout->addWidget(&imageTabs);
	mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);

    //corner ownership
    this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void LogViewer::newDisplayWidget(QWidget* widget, std::string title)
{
	if (title != "Top Image" && title != "Bottom Image")
    {
		LogViewer::removeDisplayWidgets();
		QDockWidget* dockWidget =
            new QDockWidget(QString(title.data()), this);
        dockWidget->setMinimumWidth(300);
        dockWidget->setMaximumHeight(125);

        dockWidget->setWidget(widget);
        this->addDockWidget(Qt::RightDockWidgetArea, dockWidget);
		addedWidgets.push_back(dockWidget);
    }
    else
    {
        imageTabs.addTab(widget, QString(title.data()));
    }
}

//remove all currently active display widgets
void LogViewer::removeDisplayWidgets(){
	for(std::vector<QDockWidget*>::iterator i = addedWidgets.begin(); i != addedWidgets.end(); i++)
		delete *i;
}

}
}
