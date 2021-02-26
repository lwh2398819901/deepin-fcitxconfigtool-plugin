/*
* Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
*
* Author:     liuwenhao <liuwenhao@uniontech.com>
*
* Maintainer: liuwenhao <liuwenhao@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "keysettingsitem.h"
#include <QComboBox>
#include <QMouseEvent>
#include <DFontSizeManager>
namespace dcc_fcitx_configtool {
namespace widgets {
KeyLabelWidget::KeyLabelWidget(QStringList list, QWidget *p)
    : QWidget(p)
{
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_mainLayout);

    if (list.isEmpty()) {
        list << "";
    }

    int w = 0;
    for (const QString &key : list) {
        KeyLabel *label = new KeyLabel(key);
        label->setAccessibleName("LABEL");
        m_list << label;
        m_mainLayout->addWidget(label);
        w += label->width() + this->layout()->spacing();
    }
    setFixedWidth(w);
}

KeyLabelWidget::~KeyLabelWidget()
{
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
}

void KeyLabelWidget::setList(const QStringList &list)
{
    for (KeyLabel *label : m_list) {
        m_mainLayout->removeWidget(label);
        label->deleteLater();
    }
    m_list.clear();

    for (const QString &key : list) {
        QString tmpKey = key.toLower();
        if (!tmpKey.isEmpty()) {
            tmpKey[0] = tmpKey[0].toUpper();
        }
        KeyLabel *label = new KeyLabel(tmpKey);
        m_list << label;
        m_mainLayout->addWidget(label);
        label->show();
    }

    adjustSize();
}

QString KeyLabelWidget::getKeyToStr()
{
    QString key;
    for (int i = 0; i < m_list.count(); ++i) {
        if (i == m_list.count() - 1) {
            key += m_list[i]->text();
        } else {
            key += (m_list[i]->text() + "+");
        }
    }
    return QKeySequence(key).toString();
}

void KeyLabelWidget::editFinish()
{
    //    m_keyEdit->hide();
    //    QString str = m_keyEdit->keySequence().toString();
    //    if (str.indexOf("Esc") != -1 || str.indexOf("Return") != -1 || str.indexOf("Enter") != -1) {
    //        for (KeyLabel *label : m_list) {
    //            label->show();
    //        }
    //        return;
    //    }

    //    if (str.isEmpty()) {
    //        for (KeyLabel *label : m_list) {
    //            label->show();
    //        }
    //        return;
    //    }
    //    for (KeyLabel *label : m_list) {
    //        m_mainLayout->removeWidget(label);
    //        label->deleteLater();
    //    }

    //    m_list.clear();

    //    for (const QString &key : str.split("+")) {
    //        KeyLabel *label = new KeyLabel(key);
    //        label->setAccessibleName("LABEL");
    //        m_list << label;
    //        m_mainLayout->addWidget(label);
    //    }
    //    emit editedFinish();
    //    adjustSize();
}

void KeyLabelWidget::mousePressEvent(QMouseEvent *event)
{
    //    if (m_keyEdit->isHidden()) {
    //        m_keyEdit->show();
    //        m_keyEdit->setFocus();
    //        m_keyEdit->clear();

    //        for (KeyLabel *label : m_list) {
    //            label->hide();
    //        }
    //    } else {
    //        m_keyEdit->hide();
    //    }
    QWidget::mousePressEvent(event);
}

KeySettingsItem::KeySettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_label = new ShortenLabel(text, this);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T7);
    m_keyWidget = new KeyLabelWidget(list, this);
    m_hLayout = new QHBoxLayout(this);
    m_hLayout->addWidget(m_label);
    m_hLayout->addWidget(m_keyWidget);
    m_hLayout->setContentsMargins(10, 0, 10, 0);
    setFixedHeight(48);
    setLayout(m_hLayout);
    connect(m_keyWidget, &KeyLabelWidget::editedFinish, this, &KeySettingsItem::editedFinish);

    m_lineEdit = new QLineEdit;
    m_lineEdit->setReadOnly(true);
    m_hLayout->addWidget(m_lineEdit, 0, Qt::AlignVCenter | Qt::AlignRight);
    m_lineEdit->setPlaceholderText(tr("Enter a new shortcut"));
    m_lineEdit->hide();
}

void KeySettingsItem::setList(const QStringList &list)
{
    m_keyWidget->setList(list);
}

void KeySettingsItem::mousePressEvent(QMouseEvent *e)
{
    if (!m_lineEdit->isVisible() && m_keyWidget->rect().contains(m_keyWidget->mapFromParent(e->pos()))) {
        //if (m_lineEdit->isHidden()) {
        m_keyWidget->hide();
        m_lineEdit->show();
    } else {
        m_keyWidget->show();
        m_lineEdit->hide();
    }
}

void KeySettingsItem::keyPressEvent(QKeyEvent *event)
{
    m_keyWidget->hide();
    SettingsItem::keyPressEvent(event);
}

ComBoboxSettingsItem::ComBoboxSettingsItem(const QString &text, const QStringList &list, QFrame *parent)
    : SettingsItem(parent)
{
    m_combox = new QComboBox(this);
    m_combox->setFixedHeight(36);
    m_combox->addItems(list);
    m_label = new ShortenLabel(text, this);
    DFontSizeManager::instance()->bind(m_label, DFontSizeManager::T7);
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_label);
    m_mainLayout->addWidget(m_combox);
    m_mainLayout->setContentsMargins(10, 0, 10, 0);
    setLayout(m_mainLayout);
    setFixedHeight(48);
}

ComBoboxSettingsItem::~ComBoboxSettingsItem()
{
}

} // namespace widgets
} // namespace dcc_fcitx_configtool
