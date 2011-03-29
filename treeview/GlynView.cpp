//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


# include "GlynView.h"
# include "GlynModel.h"
# include <QtGui/QStandardItemModel>
# include <QtGui/QSortFilterProxyModel>
# include <QtCore/QDebug>

GlynView::GlynView(QWidget *parent)
    : QTreeView(parent)
{
    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHeaderData(0, Qt::Horizontal, tr("Food"));
    model->setItem(0, new QStandardItem(tr("Fruit")));
    model->item(0)->setChild(0, new QStandardItem(tr("Apples")));
    model->item(0)->child(0)->setChild(0, new QStandardItem(tr("Cox's")));
    model->item(0)->child(0)->setChild(1, new QStandardItem(tr("Golden Delicious")));
    model->item(0)->child(0)->setChild(2, new QStandardItem(tr("Granny Smith's")));
    model->item(0)->setChild(1, new QStandardItem(tr("Pears")));
    model->item(0)->child(1)->setChild(0, new QStandardItem(tr("Conference")));
    model->item(0)->setChild(2, new QStandardItem(tr("Oranges")));
    model->setItem(1, new QStandardItem(tr("Veg")));

    // QAbstractProxyModel *proxyModel = new QSortFilterProxyModel(this);
    QAbstractProxyModel *proxyModel = new GlynModel(this);
    proxyModel->setSourceModel(model);
    setModel(proxyModel);

    // QList<QStandardItem *> items;
    // items.push_back(model->item(0));
    // while (!items.empty())
    // {
    //     QStandardItem *item = items.front();
    //     items.pop_front();
    //
    //     if (!item->hasChildren())
    //     {
    //         setRowHidden(item->row(), item->parent()->index(), true);
    //     }
    //
    //     int rowCount = item->rowCount();
    //     for (int i = 0; i < rowCount; ++i)
    //     {
    //         items.push_back(item->child(i));
    //     }
    // }
    setAnimated(true);
}

GlynView::~GlynView()
{

}
