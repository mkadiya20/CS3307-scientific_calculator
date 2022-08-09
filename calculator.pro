TARGET = calculator
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17

QT += core widgets printsupport

DESTDIR = main/bin
OBJECTS_DIR = main/obj
MOC_DIR = main/moc

HEADERS += main/include/model/analyser/Interpreter.h
SOURCES += main/src/model/analyser/Interpreter.cpp
HEADERS += main/include/model/analyser/Lexer.h
SOURCES += main/src/model/analyser/Lexer.cpp
HEADERS += main/include/model/analyser/Node.h
SOURCES += main/src/model/analyser/Node.cpp
HEADERS += main/include/model/analyser/Parser.h
SOURCES += main/src/model/analyser/Parser.cpp
HEADERS += main/include/model/analyser/Token.h
SOURCES += main/src/model/analyser/Token.cpp



HEADERS += main/include/model/functions/Constant.h
SOURCES += main/src/model/functions/Constant.cpp
HEADERS += main/include/model/functions/Factorial.h
SOURCES += main/src/model/functions/Factorial.cpp
SOURCES += main/include/model/functions/Fraction.h
SOURCES += main/src/model/functions/Fraction.cpp
HEADERS += main/include/model/functions/Function.h
SOURCES += main/src/model/functions/Function.cpp
HEADERS += main/include/model/functions/Log.h
SOURCES += main/src/model/functions/Log.cpp
HEADERS += main/include/model/functions/Polynomial.h
SOURCES += main/src/model/functions/Polynomial.cpp
HEADERS += main/include/model/functions/Trig.h
SOURCES += main/src/model/functions/Trig.cpp

HEADERS += main/include/model/matrices/Matrix.h
SOURCES += main/src/model/matrices/Matrix.cpp
HEADERS += main/include/model/sets/Sets.h
SOURCES += main/src/model/sets/Sets.cpp

HEADERS += main/include/controller/ButtonResponder.h
SOURCES += main/src/controller/ButtonResponder.cpp

HEADERS += main/include/controller/compute/Compute.h
HEADERS += main/include/controller/compute/ComputeEquation.h
HEADERS += main/include/controller/compute/ComputeSysOfLinearEqn.h
HEADERS += main/include/controller/compute/ComputeMatrix.h
HEADERS += main/include/controller/compute/ComputeSet.h
HEADERS += main/include/controller/compute/ComputeFunction.h
SOURCES += main/src/controller/compute/ComputeEquation.cpp
SOURCES += main/src/controller/compute/ComputeMatrix.cpp
SOURCES += main/src/controller/compute/ComputeSet.cpp
SOURCES += main/src/controller/compute/ComputeSysOfLinearEqn.cpp
SOURCES += main/src/controller/compute/ComputeFunction.cpp

HEADERS += main/include/view/button.h
HEADERS += main/include/view/calculatorGUI.h
HEADERS += main/include/view/MainWindow.h
SOURCES += main/src/view/button.cpp
SOURCES += main/src/view/calculatorGUI.cpp
SOURCES += main/src/view/MainWindow.cpp
HEADERS += main/include/view/matrixGUI.h
SOURCES += main/src/view/matrixGUI.cpp
HEADERS += main/include/view/setsGUI.h
SOURCES += main/src/view/setsGUI.cpp
HEADERS += main/include/view/stepsGUI.h
SOURCES += main/src/view/stepsGUI.cpp
HEADERS += main/include/view/History.h
SOURCES += main/src/view/History.cpp
HEADERS += main/include/view/graphGUI.h
SOURCES += main/src/view/graphGUI.cpp
HEADERS += main/include/view/qcustomplot.h
SOURCES += main/src/view/qcustomplot.cpp

HEADERS += main/include/model/utilities/Utilities.h
SOURCES += main/src/model/utilities/Utilities.cpp