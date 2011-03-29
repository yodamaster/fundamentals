//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_TREEVIEW_GLYNMODEL_INC__
# define __GLYNOS_TREEVIEW_GLYNMODEL_INC__


# include <QtGui/QAbstractProxyModel>


class GlynModel : public QAbstractProxyModel
{
public:

    GlynModel(QObject *parent);

    virtual ~GlynModel();

    virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;

    virtual QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

    virtual int rowCount(const QModelIndex &parent) const;

    virtual int columnCount(const QModelIndex &parent) const;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex parent(const QModelIndex &index = QModelIndex()) const;

private:

};


#endif // __GLYNOS_TREEVIEW_GLYNMODEL_INC__
