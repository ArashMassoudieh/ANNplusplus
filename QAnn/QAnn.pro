QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

INCLUDEPATH += ../include
INCLUDEPATH += ../../qcustomplot/
INCLUDEPATH += ../../tiny-dnn/
INCLUDEPATH += ../ODE_model/include/


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += Q_version
DEFINES +=CNN_NO_SERIALIZATION
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../qcustomplot/qcustomplot.cpp \
    ../src/BTC.cpp \
    ../src/BTCSet.cpp \
    ../src/DistributionNUnif.cpp \
    ../src/Link.cpp \
    ../src/ML.cpp \
    ../src/Matrix.cpp \
    ../src/Matrix_arma.cpp \
    ../src/NormalDist.cpp \
    ../src/QuickSort.cpp \
    ../src/StringOP.cpp \
    ../src/Vector.cpp \
    ../src/Vector_arma.cpp \
    ../src/plotter.cpp \
    ../src/utils.cpp \
    customplotwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    multiplotwindow.cpp \
    ../src/tinydnnwrapper.cpp \
    runtimewindow.cpp \
    ../ODE_model/src/Expression.cpp \
    ../ODE_model/src/ControlParameter.cpp \
    ../ODE_model/src/ExternalForcing.cpp \
    ../ODE_model/src/Object.cpp \
    ../ODE_model/src/Parameter.cpp \
    ../ODE_model/src/StateVariable.cpp \
    ../ODE_model/src/System.cpp \
    ../ODE_model/src/ErrorHandler.cpp \
    ../ODE_model/src/rewardfunction.cpp

HEADERS += \
    ../../qcustomplot/qcustomplot.h \
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
    ../include/plotter.h \
    ../include/utils.h \
    customplotwidget.h \
    mainwindow.h \
    multiplotwindow.h \
    ../include/tinydnnwrapper.h \
    ../include/network.hpp \
    runtimewindow.h \
    ../ODE_model/include/Expression.h \
    ../ODE_model/src/rewardfunction.h \
    ../ODE_model/include/ControlParameter.h \
    ../ODE_model/include/ErrorHandler.h \
    ../ODE_model/include/ExternalForcing.h \
    ../ODE_model/include/Object.h \
    ../ODE_model/include/Objective_Function.h \
    ../ODE_model/include/rewardfunction.h \
    ../ODE_model/include/StateVariable.h \
    ../ODE_model/include/System.h

FORMS += \
    customplotwidget.ui \
    mainwindow.ui \
    multiplotwindow.ui \
    plotter.ui \
    plotterwidget.ui \
    runtimewindow.ui

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
