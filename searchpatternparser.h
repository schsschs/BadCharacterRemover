#ifndef SEARCHPATTERNPARSER_H
#define SEARCHPATTERNPARSER_H
#include <QString>

class SearchPatternParser
{
public:

    static QByteArray Parse(const QString line);

};

#endif // SEARCHPATTERNPARSER_H
