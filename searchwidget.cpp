#include "searchwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(400, 300);
    setWindowTitle(QStringLiteral(""));
    m_pSearchLineEdit = new QLineEdit();
    QPushButton *pSearchButton = new QPushButton(this);

    pSearchButton->setCursor(Qt::PointingHandCursor);
    pSearchButton->setFixedSize(22, 22);
    pSearchButton->setStyleSheet("QPushButton{border-image:url(:/images/icon_search_normal); background:transparent;} \
                                     QPushButton:hover{border-image:url(:/images/icon_search_hover)} \
                                     QPushButton:pressed{border-image:url(:/images/icon_search_press)}");

    QMargins margins = m_pSearchLineEdit->textMargins();
    m_pSearchLineEdit->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
    m_pSearchLineEdit->setPlaceholderText(QStringLiteral(""));

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(pSearchButton);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    m_pSearchLineEdit->setLayout(pSearchLayout);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(m_pSearchLineEdit);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);

    setLayout(pLayout);

    connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(search()));
}

SearchWidget::~SearchWidget()
{

}

void SearchWidget::search()
{
    QString strText = m_pSearchLineEdit->text();
    if (!strText.isEmpty())
    {
    }
}
