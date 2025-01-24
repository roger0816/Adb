#include "Common.h"

Common *Common ::m_pInstance =nullptr;

Common::Common(QObject *parent)
    : QObject{parent}
{

}

Common &Common::INS()
{
  if(m_pInstance == nullptr)
      m_pInstance = new Common();

  return *m_pInstance;
}

QString Common::toBkString(QVariantMap d)
{
    QString sRe="";
    QStringList listKey = d.keys();

    foreach(QString key,listKey)
    {
        if(key.toUpper()=="SID" || key.toUpper()=="UPDATETIME")
            continue;

        if(sRe!="")
            sRe+=",";

        QString sValue = d[key].toString();

        if(sValue.trimmed()=="")
            continue;

        sRe+=key+":"+sValue;

    }

    return sRe;

}

QString Common::toJsonString(QString sKey, QString sValue)
{

     QVariantMap variantMap;
     variantMap[sKey]=sValue;

     return toJsonString(variantMap);
}

QString Common::toJsonString(QVariantMap d)
{

    // 將 QVariantMap 轉換為 QJsonObject
    QJsonObject jsonObject = QJsonObject::fromVariantMap(d);

    // 使用 QJsonDocument 來創建 JSON 格式的 QByteArray
    QJsonDocument jsonDoc(jsonObject);

    // 使用 toJson 函數將 QJsonDocument 轉換為格式化的 JSON 字串
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // 將 QByteArray 轉換為 QString
    QString jsonString(jsonData);

    return jsonString;
}



QString Common::listToJson(QVariantList list,QStringList listKey)
{

    // Convert QVariantList to QJsonArray
    QJsonArray jsonArray;
    for (const QVariant& variant : list)
    {

        QVariant target;

        if(listKey.length()>0)
        {
            QVariantMap d=variant.toMap();

            QStringList listTmp = d.keys();

            QVariantMap dR;

            foreach(QString v,listTmp)
            {
                if(listKey.contains(v))
                    dR[v]=d[v];
            }

            target = dR;

        }
        else
        {
            target = variant;
        }

        jsonArray.append(QJsonValue::fromVariant(target));
    }

    // Convert QJsonArray to QJsonDocument
    QJsonDocument jsonDocument(jsonArray);

    // Convert QJsonDocument to JSON string
    // QString jsonString = jsonDocument.toJson(QJsonDocument::Compact);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Indented);

    return jsonString;
}

QVariantList Common::jsonToList(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    if (jsonDoc.isNull() || !jsonDoc.isArray()) {
        // 若轉換失敗或不是 JSON Array，返回空的 QVariantList
        return QVariantList();
    }

    QJsonArray jsonArray = jsonDoc.array();
    QVariantList list;
    for (const QJsonValue& jsonValue : jsonArray) {
        list.append(jsonValue.toVariant());
    }

    return list;
}

QString Common::mapToJson(QVariantMap map, QStringList listKey)
{
    QVariantMap variantMap;

    if(listKey.length()<1)
    {
        variantMap = map;
    }
    else
    {
        QStringList listTmp = map.keys();
        foreach(QString v,listTmp)
        {
            if(listKey.contains(v))
            {
                variantMap[v]=map[v];
            }
        }

    }


    // 將 QVariantMap 轉換為 QJsonObject
    QJsonObject jsonObject = QJsonObject::fromVariantMap(variantMap);

    // 使用 QJsonDocument 來創建 JSON 格式的 QByteArray
    QJsonDocument jsonDoc(jsonObject);

    // 使用 toJson 函數將 QJsonDocument 轉換為格式化的 JSON 字串
    QByteArray jsonData = jsonDoc.toJson(QJsonDocument::Indented);

    // 將 QByteArray 轉換為 QString
    QString jsonString(jsonData);

    return jsonString;
}


