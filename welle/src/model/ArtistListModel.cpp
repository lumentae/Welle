#include <model/ArtistListModel.h>
#include <QtConcurrent>

#include "Queue.h"
#include "audio/AudioPlayer.h"
#include "utility/Qt.h"

namespace welle::model {
    ArtistListModel::ArtistListModel(QQmlApplicationEngine *engine) : QAbstractListModel(engine) {}

    int ArtistListModel::rowCount(const QModelIndex &parent) const {
        return m_Entries.size();
    }

    QVariant ArtistListModel::data(const QModelIndex &index, const int role) const {
        if (!index.isValid() || index.row() >= m_Entries.size())
            return {};

        const auto& entry = m_Entries.at(index.row());
        switch (role) {
            case IdRole: return QString::fromStdString(entry.id);
            case IndexRole: return index.row() + 1;
            case NameRole: return QString::fromStdString(entry.name);
            case CoverArtRole: {
                const QString path = QDir::current().absoluteFilePath("cache/" + QString::fromStdString(entry.coverArt));
                return QUrl::fromLocalFile(path).toString();
            }
            case AlbumCountRole: return static_cast<qlonglong>(entry.albumCount);
            default: return {};
        }
    }

    QHash<int, QByteArray> ArtistListModel::roleNames() const {
        return {
            { IdRole,         "id"         },
            { IndexRole,      "index"      },
            { NameRole,       "name"       },
            { CoverArtRole,   "coverArt"   },
            { AlbumCountRole, "albumCount" },
        };
    }

    void ArtistListModel::set(const QList<medialib::types::Artist> &artists) {
        beginResetModel();
        m_Entries = artists;
        endResetModel();

        m_LoadedFromDatabase = true;
        m_Offset = m_Entries.size();
    }

    void ArtistListModel::append(const QList<medialib::types::Artist> &artists) {
        beginInsertRows(QModelIndex(), m_Entries.size(), m_Entries.size() + m_Entries.size() - 1);
        m_Entries.append(artists);
        endInsertRows();
        m_Offset += artists.size();

        m_IsLoading = false;
        emit isLoadingChanged();
    }

    void ArtistListModel::setFetchNextPageCallback(const std::function<void(uint32_t, uint32_t)> &fetchNextPageCallback) {
        m_FetchNextPageCallback = fetchNextPageCallback;
    }

    void ArtistListModel::fetchNextPage() {
        if (m_IsLoading || !m_HasMore || !m_FetchNextPageCallback) return;
        if (m_LoadedFromDatabase) {
            m_LoadedFromDatabase = false;
            return;
        }
        m_IsLoading = true;
        emit isLoadingChanged();
        QThreadPool::globalInstance()->start([this] {
            m_FetchNextPageCallback(m_Offset, m_PageSize);
        });
    }
}
