#include "imsettingwindow.h"
#include "widgets/utils.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QComboBox>
#include <QCheckBox>
#include <DListView>
#include "fcitxInterface/global.h"
#include "fcitxInterface/config.h"
#include <QScrollArea>
#include <QSize>
#include <QTreeView>
#include <libintl.h>


DTK_USE_NAMESPACE
using namespace Fcitx;
using namespace dcc;

#define for_int(count) for(int i =0;i<count;++i)


IMSettingWindow::IMSettingWindow(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnect();
    updateUI();
}

IMSettingWindow::~IMSettingWindow()
{
    writeConfig();
}

void IMSettingWindow::updateUI()
{
    if (Global::instance()->inputMethodProxy()) {
        auto m_list = Global::instance()->inputMethodProxy()->iMList();
        emit sig_updateIMList(m_list);
        readConfig();
    }
}

void IMSettingWindow::initUI()
{

    auto createTitle=[this](QString str){
        TitleLabel*title = new TitleLabel(str,this);
        DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
        return title;
    };

    auto createGroup=[this](QWidget*widget){
        QGroupBox *groupBox =new QGroupBox();
        QVBoxLayout *layout =new QVBoxLayout();
        layout->setContentsMargins(0,0,0,0);
        layout->addWidget(widget);
        groupBox->setLayout(layout);
        return groupBox;
    };

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(createTitle(tr("输入法")));

    m_defualtIMCbox = new ComboxWidget("默认");
    mainLayout->addWidget(createGroup(m_defualtIMCbox));

    m_switchSystem =new SwitchWidget("使用系统托盘",this);
    mainLayout->addWidget(createGroup(m_switchSystem));
    mainLayout->addSpacing(20);

    QVBoxLayout *mainLayout2 =  new QVBoxLayout(this);
    mainLayout2->setContentsMargins(0,0,0,0);
    QHBoxLayout *headLayout = new QHBoxLayout(this);
    headLayout->setContentsMargins(0,0,0,0);
    headLayout->addWidget(createTitle(tr("输入法管理")));
    m_editBtn = new DCommandLinkButton(tr("编辑"));
    headLayout->addStretch();
    headLayout->addWidget(m_editBtn);
    mainLayout2->addLayout(headLayout);
    m_IMCurrentView = new DListView(this);
    mainLayout2->addWidget(m_IMCurrentView);
    mainLayout->addLayout(mainLayout2);
    mainLayout->addWidget(createTitle(tr("快捷键")));

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget * scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 382, 209));
    QGridLayout * gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(6);
    gridLayout_2->addLayout(vLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    mainLayout->addWidget(scrollArea);

    m_systemAppCbox = new ComboxWidget(tr("切换方式"));
    m_systemAppCbox->comboBox()->addItems({"系统","应用"});
    mainLayout->addWidget(m_systemAppCbox);

    QHBoxLayout *headLayout2 = new QHBoxLayout(this);
    headLayout2->setContentsMargins(0,0,0,0);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    m_addIMBtn =new DFloatingButton(DStyle::SP_IncreaseElement,this);
    headLayout2->addWidget(m_addIMBtn);
    headLayout2->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(headLayout2);

    this->setLayout(mainLayout);

    m_curIMModel = new IMModel(this);
    m_IMCurrentView->setModel(m_curIMModel);
    m_defualtIMCbox->comboBox()->setModel(m_curIMModel);

    m_IMCurrentView->setDragEnabled(true);
    m_IMCurrentView->setAcceptDrops(true);
    m_IMCurrentView->setDropIndicatorShown(true);
    m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_IMCurrentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_IMCurrentView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_IMCurrentView->setItemSpacing(2);
    m_IMCurrentView->setItemSize(QSize(100,48));
}

void IMSettingWindow::initConnect()
{
    connect(m_addIMBtn,&DFloatingButton::clicked,[=](){emit sig_popIMListWindow();});
    connect(m_defualtIMCbox,&ComboxWidget::onSelectChanged,this,&IMSettingWindow::slot_defualtIMChanged);
    connect(m_switchSystem,&SwitchWidget::checkedChanged,this,&IMSettingWindow::slot_switchSystem);
    connect(m_editBtn,&DCommandLinkButton::clicked,this,&IMSettingWindow::slot_editBtnClicked);
    connect(m_systemAppCbox,&ComboxWidget::onSelectChanged,this,&IMSettingWindow::slot_defualtIMChanged);
    connect(this,&IMSettingWindow::sig_updateIMList,m_curIMModel,&IMModel::slot_filterIMEntryList);
}

void IMSettingWindow::readConfig()
{

}

void IMSettingWindow::writeConfig()
{

}

void IMSettingWindow::slot_defualtIMChanged(const QString &selected)
{

}

void IMSettingWindow::slot_switchSystem(const bool &checked)
{

}

void IMSettingWindow::slot_editBtnClicked()
{
    bool flag = m_curIMModel->isEdit();
    if(!flag){
        m_editBtn->setText(tr("完成"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::NoSelection);
    }else {
        m_editBtn->setText(tr("编辑"));
        m_IMCurrentView->setSelectionMode(QAbstractItemView::SingleSelection);
    }

    m_IMCurrentView->setDragEnabled(flag);
    m_IMCurrentView->setAcceptDrops(flag);
    m_IMCurrentView->setDropIndicatorShown(flag);
    m_curIMModel->setEdit(!flag);
}

void IMSettingWindow::slot_systemAppChanged(const QString &selected)
{

}


