#ifndef IMSETTINGWINDOW_H
#define IMSETTINGWINDOW_H
#include "widgets/comboxwidget.h"
#include "widgets/switchwidget.h"
#include "widgets/titlelabel.h"
#include "immodel/immodel.h"
#include <QWidget>
#include <DCommandLinkButton>
#include <DFloatingButton>
#include <DListView>

using namespace dcc::widgets;
using namespace Dtk::Widget;
class IMSettingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMSettingWindow(QWidget *parent = nullptr);
    virtual ~IMSettingWindow();
    void updateUI();
signals:
    void sig_popIMListWindow();
    void sig_updateIMList(const FcitxQtInputMethodItemList& list);
private:
    void initUI();
    void initConnect();
    void readConfig();          //读取配置文件
    void writeConfig();         //写入配置文件
private slots:
    void slot_defualtIMChanged(const QString &selected);
    void slot_switchSystem(const bool& checked);
    void slot_editBtnClicked();
    void slot_systemAppChanged(const QString &selected);
private:
    DCommandLinkButton *m_editBtn{nullptr};
    DFloatingButton *m_addIMBtn{nullptr};
    DListView *m_IMCurrentView{nullptr};
    ComboxWidget *m_defualtIMCbox{nullptr};
    ComboxWidget *m_systemAppCbox{nullptr};
    ComboxWidget *m_imSwitchCbox{nullptr};
    SwitchWidget *m_switchSystem{nullptr};
    IMModel *m_curIMModel{nullptr};

};

#endif // IMSETTINGWINDOW_H
