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

#ifndef KEYLABEL_H
#define KEYLABEL_H

#include <QLabel>
#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DKeySequenceEdit>
#include <DFrame>
#include <DLabel>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <DApplicationHelper>

#include <QHBoxLayout>
#include <DTipLabel>
DWIDGET_USE_NAMESPACE
namespace dcc_fcitx_configtool {
namespace widgets {

class KeyLabel : public DFrame
{
public:
    KeyLabel(QString text, QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void drawShadow(QPainter *p, const QRect &rect, const QColor &color) const;
    QString text()
    {
        return label->text();
    }

private:
    DLabel *label;
};

} // namespace widgets
} // namespace dcc_fcitx_configtool
#endif // KEYLABEL_H
