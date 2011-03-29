//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


# include "GlynWidget.h"
# include <QtGui/QApplication>


int
main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(Glyn);

    QApplication app(argc, argv);
    GlynWidget widget;
    widget.resize(640, 480);
    widget.show();
    int rc = app.exec();
    return 0;
}
