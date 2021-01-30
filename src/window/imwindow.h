#ifndef IMWIDOW_H
#define IMWIDOW_H
#include "imaddwindow.h"
#include "imsettingwindow.h"
#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <fcitxqtinputmethoditem.h>
#include <fcitx/addon.h>


class IMWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IMWindow(QWidget *parent = nullptr);
    virtual ~IMWindow();
private:
    void initUI();
    void initConnect();
    void initFcitxInterface();
private:
    QStackedWidget *m_stackedWidget{};
    IMSettingWindow *m_settingWindow{};
    IMAddWindow *m_addWindow{};
};

#endif // IMWIDOW_H
