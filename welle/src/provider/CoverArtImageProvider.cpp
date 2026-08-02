#include "provider/CoverArtImageProvider.h"

namespace welle::provider {
    QImage CoverArtImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
        const auto path = m_Client->downloadCoverArt(id.toStdString());
        return QImage(path.c_str()).scaled(64, 64);
    }

    void CoverArtImageProvider::setClient(medialib::client::OpenSubsonicClient *client) {
        m_Client = client;
    }
}
