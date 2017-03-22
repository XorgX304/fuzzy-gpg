#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QString>
#include <QProcess>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("fuzzy-gpg");
    QCoreApplication::setApplicationVersion("0.9");

    QCommandLineParser parser;
    QCommandLineOption keyOption("k", QCoreApplication::translate("main", "Encryption Key"), "key", "");
    QCommandLineOption decryptOption("d", QCoreApplication::translate("main", "Decript"));

    QProcess gpg;
    QStringList args;

    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(keyOption);
    parser.addOption(decryptOption);
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Source to encrypt"));

    // Process the actual command line arguments given by the user
    parser.process(a);

    QString password = parser.value(keyOption);
    if (!parser.isSet(keyOption))
        password = "PASSKEY";

    if (parser.isSet(decryptOption))
        args << "--yes" << "--batch" << "--passphrase="+password << parser.positionalArguments()[0];
    else
        args << "--yes" << "--batch" << "--passphrase="+password << "-c" << parser.positionalArguments()[0];

    gpg.setArguments(args);
    gpg.setProgram("gpg");
    gpg.start();
    gpg.waitForFinished();

    return 0;
}
