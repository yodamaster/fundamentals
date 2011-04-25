
#include <QtCore/QStateMachine>
#include <QtGui/QApplication>
#include <QtGui/QWidget>
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

        QPushButton *record = new QPushButton(this);
        record->setIcon(QIcon(":/statemachine/resources/png/Record Button.png"));
        QPushButton *play = new QPushButton(this);
        play->setIcon(QIcon(":/statemachine/resources/png/Play.png"));
        QPushButton *stop = new QPushButton(this);
        stop->setIcon(QIcon(":/statemachine/resources/png/Stop.png"));
        hlayout->addWidget(record);
        hlayout->addWidget(play);
        hlayout->addWidget(stop);

        QLabel *label = new QLabel(tr("Idle"), this);

        vlayout->addLayout(hlayout);
        vlayout->addWidget(label);

        setLayout(vlayout);

        m_sourceMachine = new QStateMachine(this);
        QState *idle = new QState;
        QState *recording = new QState;
        QState *playing = new QState;
        QState *paused = new QState;

        idle->assignProperty(label, "text", "Idle");
        idle->assignProperty(record, "enabled", true);
        idle->assignProperty(play, "enabled", true);
        idle->assignProperty(stop, "enabled", true);
        idle->assignProperty(play, "icon", QIcon(":/statemachine/resources/png/Play.png"));
        recording->assignProperty(label, "text", "Recording");
        recording->assignProperty(play, "enabled", false);
        playing->assignProperty(label, "text", "Playing");
        playing->assignProperty(record, "enabled", false);
        playing->assignProperty(play, "icon", QIcon(":/statemachine/resources/png/Pause.png"));
        paused->assignProperty(label, "text", "Paused");
        paused->assignProperty(play, "icon", QIcon(":/statemachine/resources/png/Play.png"));

        idle->addTransition(record, SIGNAL(clicked()), recording);
        idle->addTransition(play, SIGNAL(clicked()), playing);
        recording->addTransition(stop, SIGNAL(clicked()), idle);
        playing->addTransition(play, SIGNAL(clicked()), paused);
        playing->addTransition(stop, SIGNAL(clicked()), idle);
        paused->addTransition(play, SIGNAL(clicked()), playing);
        paused->addTransition(stop, SIGNAL(clicked()), idle);

        m_sourceMachine->addState(idle);
        m_sourceMachine->addState(recording);
        m_sourceMachine->addState(playing);
        m_sourceMachine->addState(paused);

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
