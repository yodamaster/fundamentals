//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef __GLYNOS_TREEVIEW_GLYNVIEW_INC__
# define __GLYNOS_TREEVIEW_GLYNVIEW_INC__


# include <QtGui/QTreeView>


class GlynView : public QTreeView
{
public:

    GlynView(QWidget *parent = 0);

    virtual ~GlynView();

};


#endif // __GLYNOS_TREEVIEW_GLYNVIEW_INC__
