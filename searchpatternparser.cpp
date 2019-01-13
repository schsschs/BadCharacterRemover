#include "searchpatternparser.h"


QByteArray SearchPatternParser::Parse(const QString line)
{
    QByteArray result = line.toUtf8();
    QString enterKey('\n');
    QString escKey(27);
    result.replace("[enter]", enterKey.toUtf8());
    result.replace("[esc]",escKey.toUtf8());
    return result;
}
