/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "codeeditor.h"
#include "exception.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addPositionalArgument(QStringLiteral("source"), QStringLiteral("The source file to highlight."));
    parser.process(app);

    syntaxhl::Repository *repository = nullptr;
    try {
        repository = new syntaxhl::Repository("../data/syntax", "../data/themes");


    } catch (syntaxhl::Exception &e) {
        delete repository;
        QMessageBox::warning(nullptr, "Warning", e.what(),
                                        QMessageBox::Ok);
        repository = new syntaxhl::Repository("", "");
    }
    CodeEditor edit(repository);
    edit.resize(1024, 1024);
    edit.show();
    if (parser.positionalArguments().size() == 1)
        edit.openFile(parser.positionalArguments().at(0));
    return app.exec();
}
