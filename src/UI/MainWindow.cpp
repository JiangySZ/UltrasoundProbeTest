#include "UI/MainWindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStatusBar>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_statusLabel(nullptr)
{
    setupUI();
    createMenus();

    setWindowTitle("Ultrasound Probe Test System");
    resize(1024, 768);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    m_statusLabel = new QLabel("Ready", this);
    statusBar()->addWidget(m_statusLabel);
}

void MainWindow::createMenus()
{
    QMenuBar* menuBar = this->menuBar();

    QMenu* fileMenu = menuBar->addMenu("&File");
    QAction* exitAction = new QAction("E&xit", this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);
    fileMenu->addAction(exitAction);

    QMenu* helpMenu = menuBar->addMenu("&Help");
    QAction* aboutAction = new QAction("&About", this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);
    helpMenu->addAction(aboutAction);
}

void MainWindow::onAbout()
{
    QMessageBox::about(this, "About",
        "Ultrasound Probe Test System\n"
        "Version 1.0.0\n\n"
        "Windows Platform Ultrasound Probe\n"
        "Automated Test and Calibration Software");
}

void MainWindow::onExit()
{
    QApplication::quit();
}
