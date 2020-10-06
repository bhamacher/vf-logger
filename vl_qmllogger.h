#ifndef VEINLOGGER_QMLLOGGER_H
#define VEINLOGGER_QMLLOGGER_H

#include "globalIncludes.h"
#include <QtQuick/QQuickItem>
#include <QMultiHash>
#include <QDateTime>

#include "jsoncontextloader.h"



namespace VeinLogger
{
class DatabaseLogger;

/**
 * @brief The QmlLogger class
 *
 * This class stores all imprtand logging context data.
 * - recordName name
 * - transaction name
 * - contentSet names
 * - components
 *
 * - recordId
 * - transactionId
 *
 * With this information its possible to map value changes to logging sessions.
 *
 * @todo Create base class that acts only as data storage and does not handle signals and more.
 * @todo Move jsonContextreader to vl_databaselogger
 */
class VFLOGGER_EXPORT QmlLogger : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString recordName READ recordName WRITE setRecordName NOTIFY recordNameChanged)
    Q_PROPERTY(QString transactionName READ transactionName WRITE setTransactionName NOTIFY transactionNameChanged)
    Q_PROPERTY(bool loggingEnabled READ loggingEnabled NOTIFY loggingEnabledChanged)
    Q_PROPERTY(bool initializeValues READ initializeValues WRITE setInitializeValues NOTIFY initializeValuesChanged)
    Q_PROPERTY(QStringList contentSets READ contentSets WRITE setContentSets NOTIFY contentSetsChanged)
    Q_PROPERTY(QString guiContext READ guiContext WRITE setGuiContext NOTIFY guiContextChanged)
    Q_PROPERTY(QString session READ session WRITE setSession NOTIFY sessionChanged)
public:
    explicit QmlLogger(QQuickItem *t_parent = nullptr);
    /**
     * @brief recordName
     * @return
     */
    QString recordName() const;
    QString transactionName() const;
    QStringList contentSets() const;
    QString guiContext() const;
    QString session() const;
    bool loggingEnabled() const;
    bool initializeValues() const;
    bool isLoggedComponent(int t_entityId, const QString &t_componentName) const;

    static void setStaticLogger(DatabaseLogger *t_dbLogger);
    /**
     * @brief setContentSetPaths
     * @param p_zeraPath: path to Zera contentSet file
     * @param p_customerPath: path to Customer contentSet file
     *
     * @todo remove this with association to jsonContextReader
     */
    static void setContentSetPaths(QString p_zeraPath,QString p_customerPath);

    QMultiHash<int, QString> getLoggedValues() const;

    Q_INVOKABLE QStringList readSession();
    Q_INVOKABLE QVariantMap readContentSets();

    int getTransactionId() const;
    void setTransactionId(int transactionId);

    QDateTime getStartTime() const;
    void setStartTime(const QDateTime &startTime);

    QDateTime getStopTime() const;
    void setStopTime(const QDateTime &stopTime);

public slots:
    void startLogging();
    void stopLogging();
    void addLoggerEntry(int t_entityId, const QString &t_componentName);
    void removeLoggerEntry(int t_entityId, const QString &t_componentName);
    void clearLoggerEntries();
    void setRecordName(QString t_recordName);
    void setTransactionName(const QString &t_transactionName);
    void setInitializeValues(bool t_initializeValues);
    void setContentSets(const QStringList &t_contentSets);
    void setGuiContext(const QString &t_guiContext);
    void setSession(const QString &t_session);

signals:
    void recordNameChanged(QString t_recordName);
    void transactionNameChanged(QString t_transactionName);
    void contentSetsChanged(QStringList t_contentSets);
    void sessionChanged(QString t_session);
    void guiContextChanged(QString t_guiContext);
    void loggingEnabledChanged(bool t_loggingEnabled);
    void initializeValuesChanged(bool t_initializeValues);

private:
    static DatabaseLogger *s_dbLogger;
    static QString m_zeraContentSetPath;
    static QString m_customerContentSetPath;
    QString m_session;
    QString m_recordName;
    QString m_transactionName;
    int m_transactionId;
    QDateTime m_startTime;
    QDateTime m_stopTime;
    QStringList m_contentSets;
    QString m_guiContext;
    QMultiHash<int, QString> m_loggedValues;
    bool m_initializeValues=false;
    JsonContentSetLoader m_contentSetLoader;
};
} // namespace VeinLogger

#endif // VEINLOGGER_QMLLOGGER_H
