#include "imaddwindow.h"
#include "imaddwindow.h"
#include <QGroupBox>
#include <QProcess>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QApplication>


static QString languageName(const QString& langCode)
{
    if (langCode.isEmpty()) {
        return QString("Unknown");
    }
    else if (langCode == "*")
        return QString("Multilingual");
    else {
        QLocale locale(langCode);
        if (locale.language() == QLocale::C) {
            return langCode;
        }
        const bool hasCountry = langCode.indexOf("_") != -1 && locale.country() != QLocale::AnyCountry;
        QString languageName;
        if (hasCountry) {
            languageName = locale.nativeLanguageName();
        }
        if (languageName.isEmpty()) {
            //languageName = i18nd("iso_639", QLocale::languageToString(locale.language()).toUtf8());
            languageName = "iso_639";
        }
        if (languageName.isEmpty()) {
            languageName = QString("Other");
        }
        QString countryName;
        // QLocale will always assign a default country for us, check if our lang code

        if (langCode.indexOf("_") != -1 && locale.country() != QLocale::AnyCountry) {
            countryName = locale.nativeCountryName();
            if (countryName.isEmpty()) {
                countryName = QLocale::countryToString(locale.country());
            }
        }

        if (countryName.isEmpty()) {
            return languageName;
        } else {
            return languageName;
            //return i18nc("%1 is language name, %2 is country name", "%1 (%2)", languageName, countryName);
        }
    }
}

IMAddWindow::IMAddWindow(QWidget *parent) : QWidget(parent)
{

    initUI();
    initConnect();
    updateUI();
}

IMAddWindow::~IMAddWindow()
{
    writeConfig();
}

void IMAddWindow::initUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QHBoxLayout *hlayout = new QHBoxLayout();
    TitleLabel*title = new TitleLabel(tr("添加输入法"),this);
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T5, QFont::DemiBold); // 设置label字体
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    hlayout->addWidget(title);
    hlayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    mainLayout->addLayout(hlayout);

    m_searchLEdit = new SearchInput(this);
    m_searchLEdit->setIcon("");
    m_searchLEdit->setSearchText(tr("搜索"));
    mainLayout->addWidget(m_searchLEdit);
    mainLayout->addSpacing(20);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    QWidget * scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 382, 209));
    QGridLayout * gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    m_vLayout = new QVBoxLayout();
    m_vLayout->setSpacing(6);
    gridLayout_2->addLayout(m_vLayout, 0, 0, 1, 1);
    scrollArea->setWidget(scrollAreaWidgetContents);
    mainLayout->addWidget(scrollArea);


    QHBoxLayout *hlayout2 = new QHBoxLayout();
    hlayout2->addStretch();
    m_storeBtn = new DCommandLinkButton(tr("前往商店下载"),this);
    hlayout2->addWidget(m_storeBtn);
    mainLayout->addLayout(hlayout2);

    m_buttonTuple = new ButtonTuple(ButtonTuple::Save);
    auto ok = m_buttonTuple->rightButton();
    ok->setText(tr("添加"));
    ok->setEnabled(false);
    auto cancel = m_buttonTuple->leftButton();
    cancel->setText(tr("取消"));

    mainLayout->addWidget(m_buttonTuple, 0, Qt::AlignBottom);
    mainLayout->setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
}

void IMAddWindow::initConnect()
{
    auto ok = m_buttonTuple->rightButton();
    auto cancel = m_buttonTuple->leftButton();
    connect(ok,&QPushButton::clicked,this,&IMAddWindow::slot_addIM);
    connect(cancel,&QPushButton::clicked,this,&IMAddWindow::slot_cancel);
    connect(m_storeBtn,&DCommandLinkButton::clicked,this,&IMAddWindow::slot_openStore);
    connect(m_searchLEdit,&SearchInput::textChanged,this,&IMAddWindow::slot_searchIM);
}

void IMAddWindow::readConfig()
{

}

void IMAddWindow::writeConfig()
{

}

void IMAddWindow::slot_cancel()
{
    emit sig_cancel();
}

void IMAddWindow::slot_addIM()
{
    emit sig_addIM();
}

void IMAddWindow::slot_openStore()
{
    QProcess::startDetached("deepin-app-store");
}

void IMAddWindow::slot_searchIM(const QString &str)
{

}

void IMAddWindow::slot_IMViewClicked(const QModelIndex &index)
{

}

void IMAddWindow::updateUI()
{
    if (Global::instance()->inputMethodProxy()) {
        FcitxQtInputMethodItemList list = Global::instance()->inputMethodProxy()->iMList();
        Q_FOREACH(const FcitxQtInputMethodItem & im, list) {
            if (!im.enabled()) {
                m_availIMlist.push_back(im);
            }
        }

        QMap<QString, int> languageMap;
        filteredIMEntryList.clear();
        Q_FOREACH(const FcitxQtInputMethodItem & im, m_availIMlist) {
            if (!im.enabled()) {
                int idx;
                if (!languageMap.contains(im.langCode())) {
                    idx = filteredIMEntryList.count();
                    languageMap[im.langCode()] = idx;
                    filteredIMEntryList.append(QPair<QString, FcitxQtInputMethodItemList>(im.langCode(), FcitxQtInputMethodItemList()));
                } else {
                    idx = languageMap[im.langCode()];
                }
                filteredIMEntryList[idx].second.append(im);
            }
        }

        for(auto it = languageMap.begin();it!=languageMap.end();++it) {
            qDebug()<<it.key() <<it.value();
        }

        for(auto it = filteredIMEntryList.begin();it!=filteredIMEntryList.end();++it) {
             qDebug()<<it->first;
             for(auto it2 = it->second.begin();it2 != it->second.end();++it2)
                 qDebug()<<it2->name();
        }

        qDebug()<<filteredIMEntryList.count();

        QSet<QString>tmp;
        for(auto it = filteredIMEntryList.begin();it!=filteredIMEntryList.end();++it) {
             for(auto it2 = it->second.begin();it2 != it->second.end();++it2)
                 tmp.insert(languageName(it2->langCode()));
        }

        foreach(QString str,tmp){
             qDebug()<<str;
        }




        readConfig();
    }
}
