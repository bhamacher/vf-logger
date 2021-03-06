#ifndef JSONCONTEXTLOADER_H
#define JSONCONTEXTLOADER_H

#include <QObject>




/**
 * @brief The JsonContentSetLoader class
 *
 * Reads json files of the following format.
 *
 * @code
 * {
 *   "ContentSet": {
 *      "%{contentSetName}": [
            {
                "EntityId": "${id}",
                "Components": [
                    ${componentName},
                    ...
                ]
            },
 *   },
 *  "Sessions": {
 *      "${sessionName}": [
 *          ${contentSetName},
 *          ...
 *      ]
 *   }
 * }
 * @endcode
 *
 * To files are needed. One for defualt configuration.
 * This file is not editable (zeraContentSetPath).
 * And one editable file (customerContentSetPath).
 * The ouptut of this class merges the results of both files.
 *
 * zeraContentSetPath will always be priortised in case a a contentSet is available in
 * both files.
 */
class JsonContentSetLoader : public QObject
{
    Q_OBJECT
public:

    enum class error{
        NoError,
        FileDoesNotExist,
        ObjectDoesNotExist,
        ObjectHasNoValue,
        CanNotOpenFile,
        JsonParserError
    };

    explicit JsonContentSetLoader(QObject *parent = nullptr);
    /**
     * @brief init
     * @param p_zeraContentSetPath
     * @param p_customerContentSetPath
     * @return true on success
     */
    bool init(const QString &p_zeraContentSetPath, const QString &p_customerContentSetPath);
    /**
     * @brief readContentSet
     * @param p_contentSetName: contentSet to read (<contentSetName>)
     * @return QMap<<QVector<componentName>>
     */
    QMap<QString,QVector<QString>>  readContentSet(const QString &p_contentSetName);
    /**
     * @brief addContentSet
     * @param p_contentSetName
     * @param p_session
     * @param p_entityComponentMap
     * @return true on success
     *
     * Add new contentSet to custmerContentSetPath file.
     */
    bool addContentSet(const QString &p_contentSetName, const QString &p_session, QMap<QString,QVector<QString>>  p_entityComponentMap);
    /**
     * @brief removeContentSet
     * @param p_contentSetName
     * @return true on success
     *
     * Remove contentSet from customerContentSetPath file.
     *
     * @ref error
     */
    bool removeContentSet(const QString &p_contentSetName);
    /**
     * @brief contentSetList
     * @param p_session
     * @return List with available contentSets in the give session
     */
    QVector<QString> contentSetList(const QString &p_session);
    /**
     * @brief sessionList
     * @return List of Available sessions
     */
    QVector<QString> sessionList();
    /**
     * @brief readLasterror
     * @return returns the last occured error.
     *
     *
     */
    error readLasterror();
private:
    QVector<QString> zeraContentSetList(const QString &p_session);
    QVector<QString> customerContentSetList(const QString &p_file);

    QVector<QString> zeraSessionList();
    QVector<QString> customerSessionList();

    QVector<QString> readSessionListFromFile(const QString &p_session);

    QVector<QString> readContentSetListFromFile(const QString &p_file,  const QString &p_session);
    bool hasContentSet(const QString &p_file,const QString &p_contentSetName);
    QMap<QString,QVector<QString>>  readContentSetFromFile(const QString &p_file,  const QString &p_contentSet);

private:
    QString m_zeraContentSetPath;
    QString m_customerContentSetPath;
    error m_lastError;

    const QString c_session = QLatin1String("Sessions");
    const QString c_contentSet = QLatin1String("ContentSet");
    const QString c_entity = QLatin1String("EntityId");
    const QString c_component = QLatin1String("Components");

signals:

};

#endif // JSONCONTEXTLOADER_H
