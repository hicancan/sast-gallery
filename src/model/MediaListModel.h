#pragma once

#include <QAbstractTableModel>
#include <QDateTime>
#include <QList>

class MediaListModel : public QAbstractTableModel {
    Q_OBJECT

    QList<QString> path;
    QList<QDateTime> lastModifiedTime;
    QSet<QString> isFavorite;

public:
    MediaListModel(QObject* parent = nullptr);
    ~MediaListModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    enum Property { Path = 0, LastModifiedTime = 1, IsFavorite = 2 };

public slots:

    // for signals from disk scanner
    void resetEntries(const QStringList& paths);
    void appendEntries(const QStringList& paths);
    void removeEntries(const QStringList& paths);
    void modifiedEntries(const QStringList& paths);

private:
    void saveFavorites() const;
    void loadFavorites();
    QString getFavoritesFilePath() const;
};