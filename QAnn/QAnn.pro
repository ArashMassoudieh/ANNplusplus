QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

INCLUDEPATH += ../include

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += Q_version
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/ANN_class.cpp \
    ../src/BTC.cpp \
    ../src/BTCSet.cpp \
    ../src/DistributionNUnif.cpp \
    ../src/Link.cpp \
    ../src/ML.cpp \
    ../src/Matrix.cpp \
    ../src/Matrix_arma.cpp \
    ../src/Node.cpp \
    ../src/NormalDist.cpp \
    ../src/QuickSort.cpp \
    ../src/StringOP.cpp \
    ../src/Vector.cpp \
    ../src/Vector_arma.cpp \
    ../src/errorhandler.cpp \
    ../src/utils.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../include/ANN_class.h \
    ../include/BTC.h \
    ../include/BTCSet.h \
    ../include/DistributionNUnif.h \
    ../include/ErrorHandler.h \
    ../include/Link.h \
    ../include/ML.h \
    ../include/Matrix.h \
    ../include/Matrix_arma.h \
    ../include/Node.h \
    ../include/NormalDist.h \
    ../include/QuickSort.h \
    ../include/StringOP.h \
    ../include/Vector.h \
    ../include/Vector_arma.h \
    ../include/utils.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {

    LAPACK_INCLUDE = $$PWD/include
    #64 bits build
    contains(QMAKE_TARGET.arch, x86_64) {
        #debug
        CONFIG(debug, debug|release) {
            LAPACK_LIB_DIR = $$PWD/libs/lapack-blas_lib_win64/debug
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MTd \
                    -lblas_win64_MTd
        }
        #release
        CONFIG(release, debug|release) {
            LAPACK_LIB_DIR = $$PWD/libs/lapack-blas_lib_win64/release
            LIBS +=  -L$${LAPACK_LIB_DIR} -llapack_win64_MT \
                    -lblas_win64_MT
        }
    }

    INCLUDEPATH += $${LAPACK_INCLUDE}

    DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS

}


linux {
    #sudo apt-get install libblas-dev liblapack-dev
     DEFINES += ARMA_USE_LAPACK ARMA_USE_BLAS
     LIBS += -larmadillo -llapack -lblas
}
