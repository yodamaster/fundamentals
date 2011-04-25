//            Copyright (c) Glyn Matthews 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "CustomSlider.h"
#include <QtGui/QApplication>


int
main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CustomSlider widget(Qt::Horizontal);
    widget.show();
    int rc = app.exec();
    return 0;
}
