
#include <QtCore/QStateMachine>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QStackedWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QAction>


class PlaybackWidget : public QWidget
{
public:

    PlaybackWidget(QWidget *parent = 0)
        : QWidget(parent)
    {
        QVBoxLayout *vlayout = new QVBoxLayout;

        QHBoxLayout *hlayout = new QHBoxLayout;

        QPushButton *mode = new QPushButton(this);
        mode->setText(tr("Camera"));

        hlayout->addWidget(mode);

        QStackedWidget *stack = new QStackedWidget(this);

        QWidget *playBack = new QWidget(stack);

        QHBoxLayout *hlayout_2 = new QHBoxLayout;

        QPushButton *playBackwards = new QPushButton(playBack);
        playBackwards->setIcon(QIcon(":/statemachine/resources/png/Play Backwards.png"));
        QPushButton *play = new QPushButton(playBack);
        play->setIcon(QIcon(":/statemachine/resources/png/Play.png"));
        hlayout_2->addWidget(playBackwards);
        hlayout_2->addWidget(play);

        playBack->setLayout(hlayout_2);

        QPushButton *record = new QPushButton(playBack);
        record->setIcon(QIcon(":/statemachine/resources/png/Record Button.png"));

        stack->addWidget(playBack);
        stack->addWidget(record);
        hlayout->addWidget(stack);

        QLabel *label = new QLabel(tr("Idle"), this);

        vlayout->addLayout(hlayout);
        vlayout->addWidget(label);

        setLayout(vlayout);

        m_sourceMachine = new QStateMachine(this);
        QState *idle = new QState(m_sourceMachine);
        QState *recording = new QState(m_sourceMachine);
        QState *playing = new QState(m_sourceMachine);
        QState *playingBackwards = new QState(m_sourceMachine);

        idle->assignProperty(label, "text", "Idle");
        idle->assignProperty(record, "enabled", true);
        idle->assignProperty(record, "icon", QIcon(":/statemachine/resources/png/Record Button.png"));
        idle->assignProperty(playBackwards, "enabled", true);
        idle->assignProperty(playBackwards, "icon", QIcon(":/statemachine/resources/png/Play Backwards.png"));
        idle->assignProperty(play, "enabled", true);
        idle->assignProperty(play, "icon", QIcon(":/statemachine/resources/png/Play.png"));
        recording->assignProperty(label, "text", "Recording");
        recording->assignProperty(play, "enabled", false);
        recording->assignProperty(playBackwards, "enabled", false);
        recording->assignProperty(record, "icon", QIcon(":/statemachine/resources/png/Stop.png"));
        playingBackwards->assignProperty(label, "text", "Playing backwards");
        playingBackwards->assignProperty(record, "enabled", false);
        playingBackwards->assignProperty(playBackwards, "icon", QIcon(":/statemachine/resources/png/Pause.png"));
        playing->assignProperty(label, "text", "Playing");
        playing->assignProperty(record, "enabled", false);
        playing->assignProperty(play, "icon", QIcon(":/statemachine/resources/png/Pause.png"));

        idle->addTransition(record, SIGNAL(clicked()), recording);
        idle->addTransition(playBackwards, SIGNAL(clicked()), playingBackwards);
        idle->addTransition(play, SIGNAL(clicked()), playing);
        recording->addTransition(record, SIGNAL(clicked()), idle);
        playingBackwards->addTransition(playBackwards, SIGNAL(clicked()), idle);
        playing->addTransition(play, SIGNAL(clicked()), idle);

        m_sourceMachine->setInitialState(idle);
        m_sourceMachine->start();

        setWindowTitle(tr("Playback"));
    }

private:

    QStateMachine *m_sourceMachine;

};


int
main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PlaybackWidget widget;
    widget.show();
    return app.exec();
}
