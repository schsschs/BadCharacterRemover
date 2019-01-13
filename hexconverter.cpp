#include "hexconverter.h"

QString HexConverter::ToHex(const QString &input)
{
    QString result;
    result = input.toLatin1().toHex();
    return result;
}

QString HexConverter::ToString(const QString &input)
{
    QString result;
    QByteArray hex = QByteArray::fromHex(input.toUtf8());
    result = QString::fromUtf16((char16_t*)hex.data());
    return result;
}
