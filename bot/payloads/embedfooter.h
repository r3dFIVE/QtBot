/*
 *  QtBot - The extensible Qt Discord Bot!
 *
 *  Copyright (C) 2020  Ross McTague - r3dFIVE
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef EMBEDFOOTER_H
#define EMBEDFOOTER_H

#include "jsonserializable.h"


class EmbedFooter : public JsonSerializable
{
    Q_OBJECT

public:
    static const QString ICON_URL;
    static const QString PROXY_ICON_URL;
    static const QString TEXT;



    QJsonValue getIconUrl() const;
    QJsonValue getProxyIconUrl() const;
    QJsonValue getText() const;
    void setIconUrl(const QJsonValue &value);
    void setProxyIconUrl(const QJsonValue &value);
    void setText(const QJsonValue &value);

    Q_PROPERTY(QJsonValue text READ getText WRITE setText)
    Q_PROPERTY(QJsonValue icon_url READ getIconUrl WRITE setIconUrl)
    Q_PROPERTY(QJsonValue proxy_icon_url READ getProxyIconUrl WRITE setProxyIconUrl)
};

Q_DECLARE_METATYPE(EmbedFooter)

#endif // EMBEDFOOTER_H
