#include "minefieldwidget.h"
#include <QApplication>

MinefieldWidget::MinefieldWidget(QWidget *parent)
    : QWidget(parent)
{
    // Widget
    setWindowTitle(trUtf8("Minefield Game"));
    setMinimumWidth(350);

    // Dialogs
    _newGameDialog = new NewGameDialog();
    connect(_newGameDialog, SIGNAL(startNewGame(GameData)), this, SLOT(newGame(GameData)));

    _endGameDialog = new EndGameDialog();
    connect(_endGameDialog, SIGNAL(newGame()), _newGameDialog, SLOT(show()));
    connect(_endGameDialog, SIGNAL(loadGame()), this, SLOT(loadGame()));
    connect(_endGameDialog, SIGNAL(quitGame()), this, SLOT(quitGame()));

    // Buttons
    _newGameButton = new QPushButton(trUtf8("New Game"));
    _newGameButton->setFocusPolicy(Qt::NoFocus);
    connect(_newGameButton, SIGNAL(clicked()), _newGameDialog, SLOT(show()));

    _saveGameButton = new QPushButton(trUtf8("Save"));
    _saveGameButton->setFocusPolicy(Qt::NoFocus);
    _saveGameButton->setEnabled(false); // disable button
    connect(_saveGameButton, SIGNAL(clicked()), this, SLOT(saveGame()));

    _loadGameButton = new QPushButton(trUtf8("Load"));
    _loadGameButton->setFocusPolicy(Qt::NoFocus);
    connect(_loadGameButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    _quitButton = new QPushButton(trUtf8("Quit"));
    _quitButton->setFocusPolicy(Qt::NoFocus);
    connect(_quitButton, SIGNAL(clicked()), this, SLOT(quitGame()));

    _pauseButton = new QPushButton(trUtf8("Pause"));
    _pauseButton->setFocusPolicy(Qt::NoFocus);
    _pauseButton->setEnabled(false);
    connect(_pauseButton, SIGNAL(clicked()), this, SLOT(pauseHandler()));

    // Labels
    _gameTimeLabel = new QLabel();
    _gameTimeLabel->setFixedHeight(15);
    _gameTimeLabel->setAlignment(Qt::AlignHCenter);

    // Gameboard
    _gameBoardLayout = new QGridLayout();

    // Model
    _model = new MinefieldModel();
    connect(_model, SIGNAL(gameWon()), this, SLOT(won()));
    connect(_model, SIGNAL(gameLost()), this, SLOT(lost()));
    connect(_model, SIGNAL(refresh()), this, SLOT(refreshGameBoard()));
    connect(this, SIGNAL(keypress(int, int)), _model, SLOT(movePlayer(int, int)));

    // Chasers' timer
    _chaserTimer = new QTimer();
    connect(_chaserTimer, SIGNAL(timeout()), _model, SLOT(moveChasers()));
    connect(_chaserTimer, SIGNAL(timeout()), this, SLOT(refreshGameTime()));

    // Layout
    _vBoxLayout = new QVBoxLayout();
    _vBoxLayout->addWidget(_newGameButton);
    _vBoxLayout->addWidget(_saveGameButton);
    _vBoxLayout->addWidget(_loadGameButton);
    _vBoxLayout->addWidget(_quitButton);
    _vBoxLayout->addLayout(_gameBoardLayout);

    setLayout(_vBoxLayout);
}

MinefieldWidget::~MinefieldWidget()
{
    delete _newGameDialog;
    delete _endGameDialog;
}

void MinefieldWidget::newGame(GameData gameData)
{
    _model->newGame(gameData);
    createGameBoard(_model->getBoardSize());

    //_gameTime->start();

    _saveGameButton->setEnabled(true);
    _pauseButton->setEnabled(true);
    _vBoxLayout->addWidget(_gameTimeLabel);
    _vBoxLayout->addWidget(_pauseButton);

    resumeGame();
}

void MinefieldWidget::saveGame()
{
    _model->saveGame();
}

void MinefieldWidget::loadGame()
{
    _model->loadGame();
}

void MinefieldWidget::quitGame()
{
    QApplication::quit();
}

void MinefieldWidget::pauseHandler()
{
    _gamePaused ? resumeGame() : pauseGame();
}

void MinefieldWidget::pauseGame()
{
    _gamePaused = true;
    _pauseButton->setText("Resume");
    if(_chaserTimer->isActive())
    {
        _chaserTimer->stop();
    }
}

void MinefieldWidget::resumeGame()
{
    _gamePaused = false;
    _pauseButton->setText("Pause");
    _chaserTimer->start(1000);
}

void MinefieldWidget::won()
{
    pauseGame();
    _endGameDialog->won();
}

void MinefieldWidget::lost()
{
    pauseGame();
    _endGameDialog->lost();
}

void MinefieldWidget::createGameBoard(int boardSize)
{   
    foreach(QVector<QPushButton*> row, _gameBoard)
    {
        qDeleteAll(row.begin(), row.end());
        row.clear();
    }

    _gameBoard.clear();
    _gameBoard.resize(boardSize);

    for (int i = 0; i < boardSize; ++i)
    {
        _gameBoard[i].clear();
        _gameBoard[i].resize(boardSize);
        for (int j = 0; j < boardSize; ++j)
        {
            _gameBoard[i][j]= new QPushButton(this);
            _gameBoard[i][j]->setFocusPolicy(Qt::NoFocus);
            _gameBoard[i][j]->setText(getFieldValue(i, j));
            _gameBoard[i][j]->setMinimumWidth(30);
            _gameBoard[i][j]->setMinimumHeight(30);
            _gameBoard[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

            _gameBoardLayout->addWidget(_gameBoard[i][j], i, j); // gombok felvétele az elhelyezésbe
        }
    }
}

void MinefieldWidget::refreshGameBoard()
{
    int boardSize = _model->getBoardSize();

    for (int i = 0; i < boardSize; ++i)
    {
        for (int j = 0; j < boardSize; ++j)
        {
            _gameBoard[i][j]->setText(getFieldValue(i, j));
        }
    }
}

void MinefieldWidget::refreshGameTime()
{
    QTime currentTime = (QTime::currentTime());
    QString time = currentTime.toString("hh:mm:ss");

    //QString time = _gameTime->toString("hh:mm:ss");
    _gameTimeLabel->setText(time);
}

QString MinefieldWidget::getFieldValue(int x, int y)
{
    Field field = _model->getField(x, y);

    switch(field)
    {
    case Empty :
        return QString::fromStdString("");
        break;
    case Player :
        return QString::fromStdString("P");
        break;
    case Chaser :
        return QString::fromStdString("C");
        break;
    case Mine :
        return QString::fromStdString("M");
        break;
    }
}

void MinefieldWidget::keyPressEvent(QKeyEvent* event)
{
    if (!_gamePaused)
    {
        switch(event->key())
        {
        case Qt::Key_Up :
            emit keypress(-1, 0);
            break;
        case Qt::Key_Right :
            emit keypress(0, 1);
            break;
        case Qt::Key_Down :
            emit keypress(1, 0);
            break;
        case Qt::Key_Left :
            emit keypress(0, -1);
            break;
        }
    }
}
