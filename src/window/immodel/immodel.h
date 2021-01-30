#ifndef IMMODEL_H
#define IMMODEL_H
#include <QStandardItemModel>
#include <DStyledItemDelegate>
#include <DStandardItem>
#include <QDebug>
#include <QMimeData>
#include <DStyledItemDelegate>
#include <DStyle>
// Fcitx
#include <fcitxqtinputmethoditem.h>

DTK_USE_NAMESPACE
using Dtk::Widget::DStandardItem;
using Dtk::Widget::DViewItemAction;
using Dtk::Widget::DStyle;
using Dtk::Widget::DViewItemActionList;


class IMModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit IMModel(QObject* parent = nullptr);
    virtual ~IMModel();
    Qt::DropActions supportedDropActions()const override;
    QStringList mimeTypes()const override;
    QMimeData *mimeData(const QModelIndexList&index)const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setEdit(bool flag);
    bool isEdit(){return m_isDeleteEdit;}
public Q_SLOTS:
    void slot_filterIMEntryList(const FcitxQtInputMethodItemList &imEntryList);
signals:
    void sig_curIMchanged(FcitxQtInputMethodItemList);
private:
    void loadItem();
    void deleteItem(DStandardItem*item);
    void itemUp(DStandardItem*item);
    void itemDown(DStandardItem*item);
    void itemSawp(int index,int index2);
    void configShow(DStandardItem*item);
private:
    FcitxQtInputMethodItemList m_curIMList;
    bool m_isDeleteEdit{false};
};

#endif // IMMODEL_H