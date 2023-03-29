#include "qwaiting.h"
#include <QMovie>

QWaiting::QWaiting(QWidget *parent)
    : QDialog(parent)
    , m_Move(NULL)
{
    ui.setupUi(this);
    this->setWindowOpacity(0.9);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//ÉèÖÃÎª¶Ô»°¿ò·ç¸ñ£¬²¢ÇÒÈ¥µô±ß¿ò
    //setWindowModality(Qt::WindowModal);//ÉèÖÃÎªÄ£Ê½¶Ô»°¿ò£¬Í¬Ê±ÔÚ¹¹Ôì¸Ã¶Ô»°¿òÊ±ÒªÉèÖÃ¸¸´°¿Ú
    ui.label_gif->setStyleSheet("background-color: transparent;");

    m_Move = new QMovie(":/img/img/loading.gif");
    ui.label_gif->setMovie(m_Move);
    ui.label_gif->setScaledContents(true);
    m_Move->start();
}

QWaiting::~QWaiting()
{
    m_Move->stop();
}

void QWaiting::slot_changestate(QString state)
{
    ui.label_state->setText(state);
}
