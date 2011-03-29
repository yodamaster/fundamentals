//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


# include "GlynModel.h"
# include <QtCore/QDebug>


GlynModel::GlynModel(QObject *parent)
    : QAbstractProxyModel(parent)
{

}

GlynModel::~GlynModel()
{

}


QModelIndex GlynModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    return createIndex(sourceIndex.row(), sourceIndex.column());
}

QModelIndex GlynModel::mapToSource(const QModelIndex &proxyIndex) const
{
    return sourceModel()->index(proxyIndex.row(), proxyIndex.column(), proxyIndex.parent());
}

int GlynModel::rowCount(const QModelIndex &parent) const
{
    return sourceModel()->rowCount(mapToSource(parent));
}

int GlynModel::columnCount(const QModelIndex &parent) const
{
    // return sourceModel()->columnCount(mapToSource(parent));
    // 2 rows, name & value
    return 2;
}

QModelIndex GlynModel::index(int row, int column, const QModelIndex &parent) const
{
    return sourceModel()->index(row, column, mapToSource(parent));
}

QModelIndex GlynModel::parent(const QModelIndex &index) const
{
    return sourceModel()->parent(mapToSource(index));
}
