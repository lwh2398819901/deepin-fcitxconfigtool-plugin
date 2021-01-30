#ifndef IMADDWINDOW_H
#define IMADDWINDOW_H

#include "widgets/titlelabel.h"
#include "widgets/searchinput.h"
#include "widgets/buttontuple.h"
#include <QWidget>
#include <QPushButton>
#include <DCommandLinkButton>
#include <DFloatingButton>
#include <DListView>
#include <QVBoxLayout>
#include <fcitxInterface/global.h>

using namespace Fcitx;

using namespace dcc::widgets;
using namespace Dtk::Widget;
class IMAddWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMAddWindow(QWidget *parent = nullptr);
    virtual ~IMAddWindow();
    void updateUI();
signals:
    void sig_cancel();
    void sig_addIM();
    void sig_updateIMList(const FcitxQtInputMethodItemList& list);
private:
    void initUI();
    void initConnect();
    void readConfig();          //读取配置文件
    void writeConfig();         //写入配置文件
private slots:
    void slot_cancel();
    void slot_addIM();
    void slot_openStore();
    void slot_searchIM(const QString &str);
    void slot_IMViewClicked(const QModelIndex &index);

private:
    SearchInput *m_searchLEdit{nullptr};
    DCommandLinkButton *m_storeBtn{nullptr};
    ButtonTuple *m_buttonTuple{nullptr};
    QVBoxLayout *m_vLayout{nullptr};
    QList<DListView*> m_listView;
    FcitxQtInputMethodItemList m_availIMlist;
    QList<QPair<QString, FcitxQtInputMethodItemList> > filteredIMEntryList;
};

#endif // IMADDWINDOW_H
