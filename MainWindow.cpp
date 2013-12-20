#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , _msgBox(new QMessageBox(this))
  , _stackedWidget(new QStackedWidget(this))
  , _mainMenu(new MenuWidget(_stackedWidget))
  , _mikuni(new MikuniWidget(_stackedWidget))
  , _gw250Widget(new GW250Widget(_stackedWidget))
  , _hj125t_16a(new HJ125T_16APresenter(this))
  , _hj125t_16c(new HJ125T_16CPresenter(this))
  , _hj125t_10(new HJ125T_10Presenter(this))
  , _gw250(new GW250Presenter(this))
  , _mainMenuPresenter(new MainMenuPresenter(_hj125t_16a
                                             , _hj125t_16c
                                             , _hj125t_10
                                             , _gw250
                                             , this))
{
  setWindowTitle("");
  setWindowState(Qt::WindowMaximized);
  setCentralWidget(_stackedWidget);

  _stackedWidget->addWidget(_mainMenu);
  _stackedWidget->addWidget(_mikuni);
  _stackedWidget->addWidget(_gw250Widget);

  _mainMenuPresenter->setWidget(_mainMenu);
  _hj125t_16a->setMikuniWidget(_mikuni);
  _hj125t_16c->setMikuniWidget(_mikuni);
  _hj125t_10->setMikuniWidget(_mikuni);
  _gw250->setWidget(_gw250Widget);

  initPresenter(_mainMenuPresenter);
  initPresenter(_hj125t_16a);
  initPresenter(_hj125t_16c);
  initPresenter(_hj125t_10);
  initPresenter(_gw250);

  _mainMenu->setDataContext(_mainMenuPresenter);
  _mainMenuPresenter->show();
}

QMessageBox* MainWindow::msgBox() const
{
  return _msgBox;
}

void MainWindow::showStatus(const QString &text)
{
  _msgBox->setText(text);
  _msgBox->setStandardButtons(QMessageBox::NoButton);
  _msgBox->setIcon(QMessageBox::Information);
  _msgBox->show();
}

void MainWindow::hideStatus()
{
  _msgBox->hide();
}

void MainWindow::showCritical(const QString &text)
{
  _msgBox->setText(text);
  _msgBox->setStandardButtons(QMessageBox::Ok);
  _msgBox->setIcon(QMessageBox::Critical);
  _msgBox->show();
}

void MainWindow::showInfo(const QString &text)
{
  _msgBox->setText(text);
  _msgBox->setStandardButtons(QMessageBox::Ok);
  _msgBox->setIcon(QMessageBox::Information);
  _msgBox->show();
}

void MainWindow::switchPage(QWidget *page)
{
  if (page == nullptr) return;
  _stackedWidget->setCurrentWidget(page);
}

void MainWindow::initPresenter(MenuPresenter *p)
{
  connect(p, SIGNAL(switchPage(QWidget*)), this, SLOT(switchPage(QWidget*)));
  connect(p, SIGNAL(showCritical(QString)), this, SLOT(showCritical(QString)));
  connect(p, SIGNAL(showInfo(QString)), this, SLOT(showInfo(QString)));
  connect(p, SIGNAL(showStatus(QString)), this, SLOT(showStatus(QString)));
  connect(p, SIGNAL(hideStatus()), this, SLOT(hideStatus()));
}
